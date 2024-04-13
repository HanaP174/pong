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

    // create game images
    // setFocus()
    // gameLoop()

protected:
    void paintEvent(QPaintEvent *event) override;

private:

    static const int PLAYGROUND_WIDTH = 1000;
    static const int PLAYGROUND_HEIGHT = 600;
    static const qreal PADDLE_WIDTH = 30;
    static const qreal PADDLE_HEIGHT = 100;

    Paddle playerPaddle;
    Paddle computerPaddle;

    void paintPaddles(QPainter &painter);
    void paintBall(QPainter &painter);
    void paintNet(QPainter &painter);
    void paintScore(QPainter &painter);
    void paintObjects(QPainter &painter);
};


#endif //PONG_PONG_H
