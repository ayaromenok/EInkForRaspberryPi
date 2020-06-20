#include "mainwindow.h"

#include <QDebug>
#include <QtWidgets>
#include <QtPdf/QPdfDocument>
#include <QtPdfWidgets/QPdfView>

#ifdef HOST_RPI
extern "C" {
    #include "driver/IT8951.h"
}
#endif //HOSTRPI

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    _pixMap = new QPixmap(1404/2, 1872/2);
    setupUI();
    setupActions();
    setGeometry(0, 0, _pixMap->width(), _pixMap->height());
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

    const QIcon iconGrabToEink = QIcon(":/res/icons/grab-to-eink.png");
    _aGrabToEInk = new QAction(iconGrabToEink, tr("&Grab"), this);
    //_aGrabToEInk->setShortcut(Qt::Key_G);
    QList<QKeySequence> scGrab = {Qt::Key_Space, Qt::Key_G};
    _aGrabToEInk->setShortcuts(scGrab);
    //_aGrabToEInk->setShortcut(Qt::Key_Space);
    _aGrabToEInk->setStatusTip(tr("Grab to E-Ink"));
    connect(_aGrabToEInk, &QAction::triggered, this, &MainWindow::grabToEInk);
    _tbMain->addAction(_aGrabToEInk);
}

void
MainWindow::quit()
{
    qDebug() << "quit with 0...bye";
    QCoreApplication::quit();
}

void
MainWindow::grabToEInk()
{
    qDebug() << "grab to E-Ink";
    QPixmap pxmap = this->grab();
    pxmap.save("out.png");


#ifdef HOST_RPI
    if(IT8951_Init()) {
        qDebug() << "IT8951_Init error \n";
        QCoreApplication::exit(1);
    } else {
        qDebug() << "IT8951_Init is OK \n";
    }
    IT8951DisplayExample();
    IT8951_Cancel();
#endif //HOSTRPI
}
