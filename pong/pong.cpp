//
// Created by Hana on 12. 4. 2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Pong.h" resolved

#include "pong.h"
#include "ui_Pong.h"
#include <QPainter>

Pong::Pong(QWidget *parent) : QWidget(parent) {

}

void Pong::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    paintObjects(painter);

    QWidget::paintEvent(event);
}

void Pong::paintPaddles(QPainter &painter) {
    playerPaddle = QRectF(PLAYGROUND_WIDTH - PADDLE_WIDTH, PLAYGROUND_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT);
    painter.fillRect(playerPaddle, Qt::white);
    computerPaddle = QRect(0, PLAYGROUND_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT);
    painter.fillRect(computerPaddle, Qt::white);
}

void Pong::paintNet(QPainter &painter) {
    painter.setPen(QPen(Qt::white, 12, Qt::DashDotLine, Qt::RoundCap));
    painter.drawLine(PLAYGROUND_WIDTH / 2, 0, PLAYGROUND_WIDTH / 2, PLAYGROUND_HEIGHT);
    painter.setPen(QPen());
}

void Pong::paintBall(QPainter &painter) {
    ball = QRect(PLAYGROUND_WIDTH - PADDLE_WIDTH - 15 - BALL_RADIUS, PLAYGROUND_HEIGHT / 2 - PADDLE_HEIGHT / 2 - BALL_RADIUS, BALL_RADIUS * 2, BALL_RADIUS * 2);
    painter.setBrush(Qt::white);
    painter.drawEllipse(ball);
}

void Pong::paintScore(QPainter &painter) const {
    painter.setPen(Qt::white);
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
