#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int x,y,radius;
    int Sign(float);
    QImage drawCircle(int, int, int, int, QImage);
    QImage DDALine(float,float,float,float,QImage);
    QImage BresenhamCircle(int,int,int,QImage);
    QImage DDACircle(int,int,int,QImage);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
