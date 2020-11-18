#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#ifdef HOST_RPI
extern "C" {
    #include "driver/IT8951.h"
}
#endif //HOSTRPI
class QPdfDocument;
class QPdfView;
class QAction;
class QToolBar;
class QPixmap;
class QDateTime;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    void setupActions();
    void quit();
    void grabToEInk();
    void drawPixel(quint16 x, quint16 y, quint8 c);
    void clearScreen(quint8 c);

    QPdfDocument        *_pdfDoc;
    QPdfView            *_pdfView;
    QToolBar            *_tbMain;
    QAction             *_aQuit;
    QAction             *_aGrabToEInk;
    QPixmap             *_pixMap;
    QDateTime		*_time;
};
#endif // MAINWINDOW_H
