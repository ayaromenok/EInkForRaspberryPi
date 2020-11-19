#include "mainwindow.h"

#include <QDebug>
#include <QtWidgets>
#include <QtPdf/QPdfDocument>
#include <QtPdfWidgets/QPdfView>
#include <QtPdf/QPdfPageNavigation>


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
    _pdfDoc->load(":/res/test/cm4io-product-brief.pdf");

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
//    connect (_pdfView->pageNavigation(), &QPdfPageNavigation::currentPageChanged,
//             this, &MainWindow::grabToEInk);
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


    const QIcon iconGrabToEink = QIcon(":/res/icons/grab-to-eink.png");
    _aGrabToEInk = new QAction(iconGrabToEink, tr("&Grab"), this);    
    QList<QKeySequence> scGrab = {Qt::Key_Space, Qt::Key_G};
    _aGrabToEInk->setShortcuts(scGrab);    
    _aGrabToEInk->setStatusTip(tr("Grab to E-Ink"));
    connect(_aGrabToEInk, &QAction::triggered, this, &MainWindow::grabToEInk);    
    this->addAction(_aGrabToEInk);

    const QIcon iconPdfNextPage = QIcon();
    _aPdfNextPage = new QAction(iconPdfNextPage, tr("&Next"), this);
    QList<QKeySequence> ksPdfNextPage = {Qt::Key_Right, Qt::Key_N};
    _aPdfNextPage->setShortcuts(ksPdfNextPage);
    _aPdfNextPage->setStatusTip(tr("NextPage"));
    connect(_aPdfNextPage, &QAction::triggered, this, &MainWindow::onActionPdfNextPage);
    this->addAction(_aPdfNextPage);

    const QIcon iconPdfPrevPage = QIcon();
    _aPdfPrevPage = new QAction(iconPdfPrevPage, tr("&Prev"), this);
    QList<QKeySequence> ksPdfPrevPage = {Qt::Key_Left, Qt::Key_P};
    _aPdfPrevPage->setShortcuts(ksPdfPrevPage);
    _aPdfPrevPage->setStatusTip(tr("PrevPage"));
    connect(_aPdfPrevPage, &QAction::triggered, this, &MainWindow::onActionPdfPrevPage);
    this->addAction(_aPdfPrevPage);

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
    quint64 t0,t1;
    qDebug() << __FUNCTION__;
    t0 = QDateTime::currentMSecsSinceEpoch();
    QPixmap pxmap = _pdfView->grab();
//    clearScreen(0xF0);
    QImage img(pxmap.toImage());

#ifdef HOST_RPI
    for (int i=0; i<img.width(); i++){
        for (int j=0; j<img.height(); j++){
            QColor cl = img.pixelColor(i+11,j+11); //11,11 - position of QPdfView in full-screen widget
            quint32 grey = (quint32)(cl.red()*299+cl.green()*587+cl.blue()*114+500)/1000;
            drawPixel(j, (img.width()-i), (quint8) grey);
        }
    }
    IT8951UpdateScreen();
#else
    pxmap.save("out.png");
#endif //HOSTRPI

    t1 = QDateTime::currentMSecsSinceEpoch();
    qDebug() << "done.total update time is" << (t1-t0) << "msec";
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

void
MainWindow::onActionPdfNextPage()
{
    qDebug() << __FUNCTION__;
    _pdfView->pageNavigation()->goToNextPage();
    QTimer::singleShot(200, this, &MainWindow::grabToEInk);
}

void
MainWindow::onActionPdfPrevPage()
{
    qDebug() << __FUNCTION__;
    _pdfView->pageNavigation()->goToPreviousPage();
    QTimer::singleShot(200, this, &MainWindow::grabToEInk);gc
}
