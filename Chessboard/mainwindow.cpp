#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cmath"

QImage image(600, 600, QImage::Format_RGB888);
QRgb value;

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    x[0] = 200;
    y[0] = 200;
    x[1] = 400;
    y[1] = 200;
    x[2] = 200;
    y[2] = 400;
    x[3] = 400;
    y[3] = 400;
    for(int i=0; i<2; i++){
        x[i+4] = 202 + (50*i);
        y[i+4] = 202 + (50*i);
        x[i+6] = 202 + (50*i);
        y[i+6] = 302 + (50*i);
        x[i+8] = 302 + (50*i);
        y[i+8] = 202 + (50*i);
        x[i+10] = 302 + (50*i);
        y[i+10] = 302 + (50*i);
    }
}

void MainWindow :: MatrixMultiplication(float a[12][3], float b[3][3]){
    float temp[12][3];
    for(int i=0; i<12; i++){
        for(int j=0; j<3; j++){
            temp[i][j] = 0;
            for(int k=0; k<3; k++){
                temp[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    for(int i=0; i<12; i++){
        for(int j=0; j<3; j++){
            a[i][j] = temp[i][j];
        }
    }
}

void MainWindow :: Draw(){
    float x1, y1, x2, y2, x3, y3, x4, y4;
    image.fill(qRgb(0,0,0));
    value = qRgb(10, 100, 200);
    Bresenham(300, 0, 300, 599);
    Bresenham(0, 300, 599, 300);

    value = qRgb(255, 255, 255);
    Bresenham(x[0], y[0], x[1], y[1]);
    Bresenham(x[0], y[0], x[2], y[2]);
    Bresenham(x[2], y[2], x[3], y[3]);
    Bresenham(x[1], y[1], x[3], y[3]);

    x1 = (x[0] + x[1])/2;
    y1 = (y[0] + y[1])/2;
    x2 = (x[2] + x[3])/2;
    y2 = (y[2] + y[3])/2;
    Bresenham(x1, y1, x2, y2);

    x3 = (x[0] + x1)/2;
    y3 = (y[0] + y1)/2;
    x4 = (x[2] + x2)/2;
    y4 = (y[2] + y2)/2;
    Bresenham(x3, y3, x4, y4);

    x3 = (x[1] + x1)/2;
    y3 = (y[1] + y1)/2;
    x4 = (x[3] + x2)/2;
    y4 = (y[3] + y2)/2;
    Bresenham(x3, y3, x4, y4);

    x1 = (x[0] + x[2])/2;
    y1 = (y[0] + y[2])/2;
    x2 = (x[1] + x[3])/2;
    y2 = (y[1] + y[3])/2;
    Bresenham(x1, y1, x2, y2);

    x3 = (x[0] + x1)/2;
    y3 = (y[0] + y1)/2;
    x4 = (x[1] + x2)/2;
    y4 = (y[1] + y2)/2;
    Bresenham(x3, y3, x4, y4);

    x3 = (x[2] + x1)/2;
    y3 = (y[2] + y1)/2;
    x4 = (x[3] + x2)/2;
    y4 = (y[3] + y2)/2;
    Bresenham(x3, y3, x4, y4);

    for(int i=4; i<12; i++){
        SeedFill(x[i], y[i]);
    }
    ui->label->setPixmap(QPixmap :: fromImage(image));
}

void MainWindow :: SeedFill(float x, float y){
    QRgb currentColor=image.pixel(x, y);
    if(currentColor!=value){
        image.setPixel(x, y, value);
        if(x<599 && x>0){
            SeedFill(x+1, y);
            SeedFill(x-1, y);
        }
        if(y>0 && y<599){
            SeedFill(x, y+1);
            SeedFill(x, y-1);
        }
    }
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

int MainWindow :: Sign(float a){
    if(a<0){
        return -1;
    }
    return 1;
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    Draw();
}

void MainWindow::on_pushButton_2_clicked(){
    float ang = 45;
    ang /= 180;
    ang = ang* 3.14159;

    float Matrix[12][3];
    float Rotation[3][3], Translation[3][3];
    for(int i=0; i<12; i++){
        Matrix[i][0] = x[i];
        Matrix[i][1] = y[i];
        Matrix[i][2] = 1;
        if(i<3){
            for(int j=0; j<3; j++){
                Rotation[i][j] = 0;
                Translation[i][j] = 0;
                if(i==j){
                    Rotation[i][j] = 1;
                    Translation[i][j] = 1;
                }
            }
        }
    }
    Translation[2][0] = -300;
    Translation[2][1] = -300;

    MatrixMultiplication(Matrix, Translation);

    Rotation[0][0] = cos(ang);
    Rotation[1][1] = cos(ang);
    Rotation[1][0] = sin(ang);
    Rotation[0][1] = (-1*Rotation[1][0]);
    MatrixMultiplication(Matrix, Rotation);

    Translation[2][0] = 300;
    Translation[2][1] = 300;

    MatrixMultiplication(Matrix, Translation);

    for(int i=0; i<12; i++){
        x[i] = Matrix[i][0];
        y[i] = Matrix[i][1];
    }
    Draw();
}
