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
    QRgb value;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int win[4], cnt;
    int code1[4], code2[4]; //left, top, right, bottom
    void Clipping(int, int, int, int);
    void CodeGenerate(int, int, int*);
    int x[100], y[100], index;
    void mousePressEvent(QMouseEvent *me);
    bool flag;
    bool Discard(int*, int*);
    bool CheckIfOutside(int*);
    void Bresenham(float, float, float, float);
    int Sign(float);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
