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

    // todo
    // setFocus()
    // gameLoop()

protected:
    void paintEvent(QPaintEvent *event) override;

private:

    constexpr static const qreal PLAYGROUND_WIDTH = 1000;
    constexpr static const qreal PLAYGROUND_HEIGHT = 600;
    constexpr static const qreal PADDLE_WIDTH = 30;
    constexpr static const qreal PADDLE_HEIGHT = 100;
    constexpr static const qreal BALL_RADIUS = 15;

    QRectF playerPaddle;
    QRectF computerPaddle;
    QRectF ball;

    int playerScore = 0;
    int computerScore = 0;

    void paintPaddles(QPainter &painter);
    void paintBall(QPainter &painter);
    static void paintNet(QPainter &painter);
    void paintScore(QPainter &painter) const;
    void paintObjects(QPainter &painter);
};


#endif //PONG_PONG_H
