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
    playerPaddle(PLAYGROUND_HEIGHT / 2 + PADDLE_WIDTH, PLAYGROUND_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT);
}

void Pong::paintNet(QPainter &painter) {
    painter.setPen(QPen(Qt::white, 12, Qt::DashDotLine, Qt::RoundCap));
    painter.drawLine(PLAYGROUND_WIDTH / 2, 0, PLAYGROUND_WIDTH / 2, PLAYGROUND_HEIGHT);
}

void Pong::paintObjects(QPainter &painter) {
    paintNet(painter);
}
