//
// Created by Hana on 13. 4. 2024.
//

#ifndef PONG_PADDLE_H
#define PONG_PADDLE_H


#include <QRectF>

class Paddle {

public:
//    Paddle(qreal left, qreal top, qreal width, qreal height);

private:
    QRectF paddle;

public:
    const QRectF &getPaddle() const;

    void move();
};


#endif //PONG_PADDLE_H
