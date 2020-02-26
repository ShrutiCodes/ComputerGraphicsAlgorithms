#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int value,black;
    int t,x1,y1,x2,y2;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QImage DDA(int,int,int,int,QImage,int);
    QImage Draw(float X, float Y,int i, QImage image, int n);
    QImage Preset(QImage Q);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
