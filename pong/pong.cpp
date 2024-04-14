//
// Created by Hana on 12. 4. 2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Pong.h" resolved

#include "pong.h"
#include "ui_Pong.h"
#include <QPainter>
#include <QMouseEvent>

Pong::Pong(QWidget *parent) : QWidget(parent) {
    initObjects();
    setFocus();
    startTimer(DELAY);
}

void Pong::initObjects() {
    playerPaddle = QRectF(PLAYGROUND_WIDTH - PADDLE_WIDTH, PLAYGROUND_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT);
    computerPaddle = QRect(0, PLAYGROUND_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT);
    ball = QRect(PLAYGROUND_WIDTH - PADDLE_WIDTH - 15 - BALL_RADIUS, PLAYGROUND_HEIGHT / 2 - PADDLE_HEIGHT / 2 - BALL_RADIUS, BALL_RADIUS * 2, BALL_RADIUS * 2);
}

void Pong::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    if (gameOver) {
        endGame(painter);
    } else {
        paintObjects(painter);
    }

    QWidget::paintEvent(event);
}

void Pong::paintPaddles(QPainter &painter) {
    painter.fillRect(playerPaddle, Qt::white);
    painter.fillRect(computerPaddle, Qt::white);
}

void Pong::paintNet(QPainter &painter) {
    painter.setPen(QPen(Qt::white, 12, Qt::DashDotLine, Qt::RoundCap));
    painter.drawLine(PLAYGROUND_WIDTH / 2, 0, PLAYGROUND_WIDTH / 2, PLAYGROUND_HEIGHT);
    painter.setPen(QPen());
}

void Pong::paintBall(QPainter &painter) {
    painter.setBrush(Qt::white);
    painter.drawEllipse(ball);
}

void Pong::paintScore(QPainter &painter) const {
    painter.setPen(Qt::red);
    QFont font = painter.font();
    font.setPointSize(30);
    painter.setFont(font);
    painter.drawText(PLAYGROUND_WIDTH * 3 / 4, 50, QString::number(playerScore));
    painter.drawText(PLAYGROUND_WIDTH / 4, 50, QString::number(computerScore));
}

void Pong::paintObjects(QPainter &painter) {
    paintNet(painter);
    paintPaddles(painter);
    paintBall(painter);
    paintScore(painter);
}

void Pong::timerEvent(QTimerEvent *timerEvent) {
    if (!gameOver) {
        moveBall();
        moveComputerPaddle();
        repaint();
    }
}

void Pong::moveBall() {
    ball.translate(ballSpeed.x, ballSpeed.y);

    if (ball.top() <= 0 || ball.bottom() >= PLAYGROUND_HEIGHT) {
        bounceBallFromEdge();
    } else if (ball.intersects(computerPaddle)) {
        bounceBallFromPaddle(computerPaddle.center().y(), computerPaddle.height(), false);
        computerScore++;
        return;
    } else if (ball.intersects(playerPaddle)) {
        bounceBallFromPaddle(playerPaddle.center().y(), playerPaddle.height(), true);
        playerScore++;
        return;
    } else if (ball.left() <= 0 || ball.right() >= PLAYGROUND_WIDTH) {
        gameOver = true;
    }
}

void Pong::bounceBallFromPaddle(qreal center, qreal height, bool isPlayer) {
    qreal relativePosition = (ball.center().y() - center) / (height / 2.0) * MAX_BALL_SPEED;

    if (isPlayer) {
        if (paddleBounceDirection == TOP) {
            relativePosition = -MAX_BALL_SPEED;
        } else if (paddleBounceDirection == DOWN) {
            relativePosition = MAX_BALL_SPEED;
        }
        paddleBounceDirection = NONE;
    }
    ballSpeed.y = relativePosition;
    ballSpeed.x *= -1;
}

void Pong::bounceBallFromEdge() {
    if (ball.x() < 0 || ball.x() > PLAYGROUND_WIDTH) {
        ballSpeed.x *= -1;
    } else if (ball.y() < 0 || ball.y() > PLAYGROUND_HEIGHT) {
        ballSpeed.y *= -1;
    }
}

void Pong::mouseMoveEvent(QMouseEvent *event) {
    qreal currentMouseY = event->pos().y();
    setPaddleMouseDirection(currentMouseY);

    qreal newY = currentMouseY - playerPaddle.height() / 2;

    if (newY < 0) {
        newY = 0;
    } else if (newY > PLAYGROUND_HEIGHT - playerPaddle.height()) {
        newY = PLAYGROUND_HEIGHT - playerPaddle.height();
    }
    playerPaddle.moveTo(playerPaddle.x(), newY);

    update();
}

void Pong::moveComputerPaddle() {
    qreal ballCenterX = ball.x() + ball.width() / 2;

    if (ballCenterX <= PLAYGROUND_WIDTH / 2) {
        qreal computerPaddleCenterY = computerPaddle.y() + computerPaddle.height() / 2;
        qreal ballCenterY = ball.y() + ball.height() / 2;
        if (ballCenterY < computerPaddleCenterY) {
            qreal newY = computerPaddle.y() - COMPUTER_PADDLE_SPEED;
            if (newY < 0) {
                newY = 0;
            }
            computerPaddle.moveTo(computerPaddle.x(), newY);
        } else if (ballCenterY > computerPaddleCenterY) {
            qreal newY = computerPaddle.y() + COMPUTER_PADDLE_SPEED;
            if (newY + computerPaddle.height() > PLAYGROUND_HEIGHT) {
                newY = PLAYGROUND_HEIGHT - computerPaddle.height();
            }
            computerPaddle.moveTo(computerPaddle.x(), newY);
        }
    }
}

void Pong::setPaddleMouseDirection(qreal currentMouseY) {
    if (previousMouseY != -1 && currentMouseY != previousMouseY) {
        if (currentMouseY < previousMouseY) {
            paddleBounceDirection = TOP;
        } else {
            paddleBounceDirection = DOWN;
        }
    }
    previousMouseY = currentMouseY;
}

void Pong::endGame(QPainter &painter) {
    QFont font("Arial", 20, QFont::Bold);
    painter.setFont(font);
    painter.drawText(rect(), Qt::AlignCenter, "Game Over");

    QString playerScoreText = "Player's score: " + QString::number(playerScore);
    painter.drawText(rect().adjusted(0, 50, 0, 0), Qt::AlignCenter, playerScoreText);

    QString computerScoreText = "Computer's score: " + QString::number(computerScore);
    painter.drawText(rect().adjusted(0, 100, 0, 0), Qt::AlignCenter, computerScoreText);
}
