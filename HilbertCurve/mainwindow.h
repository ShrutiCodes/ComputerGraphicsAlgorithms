#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui{
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Generate_clicked();
    void DDA(QImage &image,int x1,int y1,int x0,int y0);
    void Hilbert(QImage &image,float P[4][2],float end[2][2],int dir,int n);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
