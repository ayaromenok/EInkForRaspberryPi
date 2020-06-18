#include "mainwindow.h"

#include <QDebug>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QPdfDocument>
#include <QPdfView>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    setGeometry(0, 0, 1404/2, 1872/2);
}

MainWindow::~MainWindow()
{
}

void
MainWindow::setupUI()
{
    QVBoxLayout *lo = new QVBoxLayout();
    QLabel *lbIp4 = new QLabel("QLabel");
    lo->addWidget(lbIp4);

    _pdfDoc = new QPdfDocument();
    _pdfDoc->load(":/res/test/test1872x1404.pdf");

    _pdfView = new QPdfView();
    _pdfView->setDocument(_pdfDoc);
    lo->addWidget(_pdfView);

    this->setLayout(lo);
}

