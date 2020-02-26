#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int X[10], Y[10],index=0;
    bool flag=false;

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QImage DDA(int,int,int,int,QImage);
    void mousePressEvent(QMouseEvent*);
    int Sign(float,float);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
