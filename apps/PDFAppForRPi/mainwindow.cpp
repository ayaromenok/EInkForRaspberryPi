#include "mainwindow.h"

#include <QDebug>
#include <QtWidgets>
#include <QPdfDocument>
#include <QPdfView>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    setupActions();
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

    _tbMain = new QToolBar;
    lo->addWidget(_tbMain);

    _pdfDoc = new QPdfDocument();
    _pdfDoc->load(":/res/test/test1872x1404.pdf");

    _pdfView = new QPdfView();
    _pdfView->setDocument(_pdfDoc);
    lo->addWidget(_pdfView);

    this->setLayout(lo);
}


void
MainWindow::setupActions()
{
    const QIcon iconQuit = QIcon(":/res/icons/system-log-out.png");
    _aQuit = new QAction(iconQuit, tr("&Quit"), this);
    _aQuit->setShortcut(Qt::Key_Q);
    _aQuit->setStatusTip(tr("QuitApp"));
    connect(_aQuit, &QAction::triggered, this, &MainWindow::quit);
    _tbMain->addAction(_aQuit);
}

void
MainWindow::quit()
{
    QCoreApplication::quit();
}
