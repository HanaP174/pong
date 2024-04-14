//
// Created by Hana on 12. 4. 2024.
//

#ifndef PONG_PONG_H
#define PONG_PONG_H

#include <QWidget>
#include "paddle/Paddle.h"


class Pong : public QWidget {
Q_OBJECT

public:
    explicit Pong(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *timerEvent) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:

    struct BallSpeed {
        qreal x = 2;
        qreal y = 2;
    };

    enum PaddleBounceDirection {
        TOP,
        DOWN,
        NONE
    };

    constexpr static const qreal PLAYGROUND_WIDTH = 1000;
    constexpr static const qreal PLAYGROUND_HEIGHT = 600;
    constexpr static const qreal PADDLE_WIDTH = 30;
    constexpr static const qreal PADDLE_HEIGHT = 100;
    constexpr static const qreal BALL_RADIUS = 15;
    static const int DELAY = 5;
    constexpr static const qreal MAX_BALL_SPEED = 2;
    constexpr static const qreal COMPUTER_PADDLE_SPEED = 2;

    QRectF playerPaddle;
    QRectF computerPaddle;
    QRectF ball;

    int playerScore = 0;
    int computerScore = 0;

    BallSpeed ballSpeed = BallSpeed();
    PaddleBounceDirection paddleBounceDirection = NONE;
    qreal previousMouseY;

    bool gameOver = false;
    bool paused = false;

    void initObjects();
    void paintPaddles(QPainter &painter);
    void paintBall(QPainter &painter);
    static void paintNet(QPainter &painter);
    void paintScore(QPainter &painter) const;
    void paintObjects(QPainter &painter);
    void moveBall();
    void bounceBallFromPaddle(qreal center, qreal height, bool isPlayer);
    void bounceBallFromEdge();
    void moveComputerPaddle();
    void setPaddleMouseDirection(qreal currentMouseY);
};


#endif //PONG_PONG_H
