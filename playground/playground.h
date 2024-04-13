//
// Created by Hana on 12. 4. 2024.
//

#ifndef PONG_PLAYGROUND_H
#define PONG_PLAYGROUND_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class Playground; }
QT_END_NAMESPACE

class Playground : public QMainWindow {
Q_OBJECT

public:
    explicit Playground(QWidget *parent = nullptr);

    ~Playground() override;

    void init();

private:
    Ui::Playground *ui;

    QSize playgroundSize = QSize(1000, 600);
};


#endif //PONG_PLAYGROUND_H
