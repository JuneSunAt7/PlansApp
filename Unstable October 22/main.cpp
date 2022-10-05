#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Aqua Notebook");
    MainWindow w;
    w.setFixedSize(887,753);
    w.setWindowTitle("Aqua Notebook");
    w.setWindowOpacity(0.85);
    w.show();
    return a.exec();
}
