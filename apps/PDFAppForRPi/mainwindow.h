#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
class QPdfDocument;
class QPdfView;
class QAction;
class QToolBar;
class QPixmap;

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

    QPdfDocument        *_pdfDoc;
    QPdfView            *_pdfView;
    QToolBar            *_tbMain;
    QAction             *_aQuit;
    QAction             *_aGrabToEInk;
    QPixmap             *_pixMap;

};
#endif // MAINWINDOW_H
