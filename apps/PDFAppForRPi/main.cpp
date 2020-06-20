#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QRect rect = QApplication::desktop()->screenGeometry();
    qDebug() << "Screen is:" << rect.width() << "x"<<rect.height();
    return a.exec();
}
