#include "mainwindow.h"

#include <QDebug>
#include <QtWidgets>
#include <QtPdf/QPdfDocument>
#include <QtPdfWidgets/QPdfView>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
#ifdef HOST_RPI
    if(IT8951_Init()) {
        qDebug() << "IT8951_Init error \n";
        QCoreApplication::exit(1);
    } else {
        qDebug() << "IT8951_Init is OK \n";
    }
#else //HOSTRPI

#endif //HOSTRPI

    _time = new QDateTime();
    setupUI();
    setupActions();

    clearScreen(0xF);
}

MainWindow::~MainWindow()
{
#ifdef HOST_RPI
    IT8951_Cancel();
#endif //HOSTRPI
}

void
MainWindow::setupUI()
{
    QVBoxLayout *lo = new QVBoxLayout();
//    QLabel *lbIp4 = new QLabel("QLabel");
//    lo->addWidget(lbIp4);

//    _tbMain = new QToolBar;
//    lo->addWidget(_tbMain);

    _pdfDoc = new QPdfDocument();
    _pdfDoc->load(":/res/test/test1872x1404.pdf");

    _pdfView = new QPdfView();
    _pdfView->setDocument(_pdfDoc);
    _pdfView->setZoomMode(QPdfView::FitInView);
#ifdef HOST_RPI
    _pdfView->setFixedSize(1404,1872);
#else //HOSTRPI
    _pdfView->setFixedSize(1404/2,1872/2);
#endif //HOSTRPI

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
    this->addAction(_aQuit);
    //_tbMain->addAction(_aQuit);

    const QIcon iconGrabToEink = QIcon(":/res/icons/grab-to-eink.png");
    _aGrabToEInk = new QAction(iconGrabToEink, tr("&Grab"), this);
    //_aGrabToEInk->setShortcut(Qt::Key_G);
    QList<QKeySequence> scGrab = {Qt::Key_Space, Qt::Key_G};
    _aGrabToEInk->setShortcuts(scGrab);
    //_aGrabToEInk->setShortcut(Qt::Key_Space);
    _aGrabToEInk->setStatusTip(tr("Grab to E-Ink"));
    connect(_aGrabToEInk, &QAction::triggered, this, &MainWindow::grabToEInk);
    //_tbMain->addAction(_aGrabToEInk);
    this->addAction(_aGrabToEInk);
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
    qint64 s0,s1,s2,s3;
    QPixmap pxmap = this->grab();
    qDebug() << "clear screen." ;
    s0=_time->currentMSecsSinceEpoch();
    clearScreen(0xF0);
    s1=_time->currentMSecsSinceEpoch();
    qDebug() << (s1-s0)<<"msec\n"<< "PixMap is:" << pxmap.width() << "x"<< pxmap.height();

    QImage img(pxmap.toImage());


    for (int i=0; i<1404; i++){
        for (int j=0; j<1872; j++){
            QColor cl = img.pixelColor(i+11,j+11); //11,11 - position of QPdfView in full-screen widget
            quint32 grey = (quint32)(cl.red()*299+cl.green()*587+cl.blue()*114+500)/1000;
            drawPixel(j, (1404-i), (quint8) grey);
        }
    }
#ifdef HOST_RPI
    s2=_time->currentMSecsSinceEpoch();
    qDebug() << "PDF grabbed to buffer: "<<(s2-s1) <<"msec";
    IT8951UpdateScreen();
    s3=_time->currentMSecsSinceEpoch();
    qDebug() << "E-Ink screen updated" << (s3-s2) <<"msec";
#else
    pxmap.save("out.png");
#endif //HOSTRPI
    qDebug() << "done.";
}
void
MainWindow::drawPixel(quint16 x, quint16 y, quint8 c)
{
#ifdef HOST_RPI
    IT8951DrawPixel(x, y, c);
#else
    //qDebug() << x << y << c;
#endif //HOSTRPI
}

void
MainWindow::clearScreen(quint8 c)
{
#ifdef HOST_RPI
    IT8951ClearScreen(c);
#endif //HOSTRPI
}
