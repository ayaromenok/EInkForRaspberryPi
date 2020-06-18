#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
class QPdfDocument;
class QPdfView;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();

    QPdfDocument*       _pdfDoc;
    QPdfView*           _pdfView;
};
#endif // MAINWINDOW_H
