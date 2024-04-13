//
// Created by Hana on 12. 4. 2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Playground.h" resolved

#include "playground.h"
#include "ui_Playground.h"
#include "../pong/pong.h"
#include <QSettings>

Playground::Playground(QWidget *parent) : QMainWindow(parent), ui(new Ui::Playground) {
    ui->setupUi(this);

    auto *pongGame = new Pong(this);
    setCentralWidget(pongGame);
}

Playground::~Playground() {
    delete ui;
}

void Playground::init() {
    this->setMinimumSize(playgroundSize);
    this->setMaximumSize(playgroundSize);
}
