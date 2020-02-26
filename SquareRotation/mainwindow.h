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
    int x[4], y[4];
    explicit MainWindow(QWidget *parent = 0);
    void Draw();
    void MatrixMultiplication(float a[4][3], float b[3][3]);
    int Sign(float);
    void Bresenham(float, float, float, float);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_scale_button_clicked();
    void on_rotate_button_clicked();
    void on_translate_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
