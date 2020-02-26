#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    int x[4],y[4];
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void Draw();
    void MatrixMultiplication(float a[4][3], float b[3][3]);
    int Sign(float);
    void Bresenham(float, float, float, float);
    ~MainWindow();

private slots:
    void on_DrawShape_clicked();
    void on_ReflectX_clicked();
    void on_ReflectY_clicked();
    void on_ReflectXY_clicked();
    void on_RotateXY_clicked();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
