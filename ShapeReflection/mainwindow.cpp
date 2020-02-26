#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"cmath"

QImage image(600,600, QImage::Format_RGB888);
QRgb value;

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    x[0] = 350;
    y[0] = 250;
    x[1] = 400;
    y[1] = 150;
    x[2] = 450;
    y[2] = 250;
}

void MainWindow :: MatrixMultiplication(float a[3][3], float b[3][3]){
    float temp[3][3];
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            temp[i][j] = 0;
            for(int k=0; k<3; k++){
                temp[i][j] += a[i][k]*b[k][j];
            }
        }
    }
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            a[i][j] = temp[i][j];
        }
    }
}

void MainWindow :: Draw(){
    image.fill(qRgb(0,0,0));
    value = qRgb(255, 0, 0);
    Bresenham(300, 0, 300, 599);
    Bresenham(0, 300, 599, 300);
    Bresenham(0, 599, 599, 0);

    value = qRgb(0, 255, 0);
    Bresenham(x[0], y[0], x[1], y[1]);
    Bresenham(x[0], y[0], x[2], y[2]);
    Bresenham(x[2], y[2], x[1], y[1]);

    ui->Canvas->setPixmap(QPixmap::fromImage(image));
}

int MainWindow :: Sign(float a){
    if(a<0){
        return -1;
    }
    return 1;
}

void MainWindow :: Bresenham(float x1, float y1, float x2, float y2){
    int dx,dy,s1,s2,temp,flag_interchange,e,x,y;
    x=x1;
    y=y1;
    dx=abs(x2-x1);
    dy=abs(y2-y1);
    s1=Sign(x2-x1);
    s2=Sign(y2-y1);

    if(dy>dx){
        temp=dx;
        dx=dy;
        dy=temp;
        flag_interchange=1;
    }
    else
        flag_interchange=0;

    e=2*dy-dx;

    for(int i=0;i<=dx;i++){
        image.setPixel(x,y,value);
        while(e>=0){
            if(flag_interchange==1)
                x=x+s1;
            else
                y=y+s2;
            e=e-2*dx;
        }
        if(flag_interchange==1)
            y=y+s2;
        else
            x=x+s1;
        e=e+2*dy;
    }
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_ReflectX_clicked(){
    float mat[3][3], reflection[3][3], translation[3][3];
    for(int i=0; i<3; i++){
        mat[i][0] = x[i];
        mat[i][1] = y[i];
        mat[i][2] = 1;
        for(int j=0; j<3; j++){
            reflection[i][j] = 0;
            translation[i][j] = 0;
            if(i == j){
                translation[i][j] = 1;
            }
        }
    }
    translation[2][0] = -300;
    translation[2][1] = -300;
    MatrixMultiplication(mat, translation);

    reflection[0][0] = 1;
    reflection[1][1] = -1;
    MatrixMultiplication(mat, reflection);

    translation[2][0] = 300;
    translation[2][1] = 300;
    MatrixMultiplication(mat, translation);

    for(int i=0; i<3; i++){
        x[i] = mat[i][0] + 300;
        y[i] = mat[i][1] + 300;
    }
    Draw();
}

void MainWindow::on_DrawShape_clicked(){
    Draw();
}

void MainWindow::on_ReflectY_clicked(){
    float mat[3][3], reflection[3][3], translation[3][3];
    for(int i=0; i<3; i++){
        mat[i][0] = x[i];
        mat[i][1] = y[i];
        mat[i][2] = 1;
        for(int j=0; j<3; j++){
            reflection[i][j] = 0;
            translation[i][j] = 0;
            if(i == j){
                translation[i][j] = 1;
            }
        }
    }
    translation[2][0] = -300;
    translation[2][1] = -300;
    MatrixMultiplication(mat, translation);

    reflection[0][0] = -1;
    reflection[1][1] = 1;
    MatrixMultiplication(mat, reflection);

    translation[2][0] = 300;
    translation[2][1] = 300;
    MatrixMultiplication(mat, translation);

    for(int i=0; i<3; i++){
        x[i] = mat[i][0] + 300;
        y[i] = mat[i][1] + 300;
    }
    Draw();
}

void MainWindow::on_ReflectXY_clicked(){
    float mat[3][3], reflection[3][3], translation[3][3];
    for(int i=0; i<3; i++){
        mat[i][0] = x[i];
        mat[i][1] = y[i];
        mat[i][2] = 1;
        for(int j=0; j<3; j++){
            reflection[i][j] = 0;
            translation[i][j] = 0;
            if(i == j){
                translation[i][j] = 1;
            }
        }
    }
    translation[2][0] = -300;
    translation[2][1] = -300;
    MatrixMultiplication(mat, translation);

    reflection[0][1] = -1;
    reflection[1][0] = -1;
    MatrixMultiplication(mat, reflection);

    translation[2][0] = 300;
    translation[2][1] = 300;
    MatrixMultiplication(mat, translation);

    for(int i=0; i<3; i++){
        x[i] = mat[i][0] + 300;
        y[i] = mat[i][1] + 300;
    }
    Draw();
}

void MainWindow::on_RotateXY_clicked()
{
    int refx,refy;
    float mat[3][3], rotation[3][3], translation[3][3];

    refx = ui->text_x->toPlainText().toInt();
    refy = ui->text_y->toPlainText().toInt();

    float ang = 45;
    ang /= 180;
    ang = ang* 3.14159;

    for(int i=0; i<3; i++){
        mat[i][0] = x[i];
        mat[i][1] = y[i];
        mat[i][2] = 1;
        if(i<3){
            for(int j=0; j<3; j++){
                rotation[i][j] = 0;
                translation[i][j] = 0;
                if(i==j){
                    rotation[i][j] = 1;
                    translation[i][j] = 1;
                }
            }
        }
    }
    translation[2][0] = -refx;
    translation[2][1] = -refy;
    MatrixMultiplication(mat, translation);

    rotation[0][0] = cos(ang);
    rotation[1][1] = cos(ang);
    rotation[1][0] = sin(ang);
    rotation[0][1] = (-1*rotation[1][0]);
    MatrixMultiplication(mat, rotation);

    translation[2][0] = refx;
    translation[2][1] = refy;
    MatrixMultiplication(mat, translation);

    for(int i=0; i<3; i++){
        x[i] = mat[i][0];
        y[i] = mat[i][1];
    }
    Draw();
}

