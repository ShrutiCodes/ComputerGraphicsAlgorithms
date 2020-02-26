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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    float x[12],y[12];
    void Bresenham(float x1, float y1, float x2, float y2);
    int Sign(float a);
    void SeedFill(float x1,float y1);
    void Draw();
    void MatrixMultiplication(float mat1[12][3],float mat2[3][3]);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
