#include "mainwidget.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/resources/favicon.ico"));

    // Invoke main widget
    MainWidget w;
    w.showMaximized();
    w.show();

    return a.exec();
}
