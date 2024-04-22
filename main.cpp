#include <QApplication>
#include "playground/playground.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Playground playground;
    playground.init();
    playground.show();
    return QApplication::exec();
}
