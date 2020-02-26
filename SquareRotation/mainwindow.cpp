#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cmath"

QImage image(400,400, QImage :: Format_RGB888);

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    x[0] = 100;
    x[1] = 300;
    x[2] = 100;
    x[3] = 300;
    y[0] = 100;
    y[1] = 100;
    y[2] = 300;
    y[3] = 300;
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow :: MatrixMultiplication(float a[4][3], float b[3][3]){
    float temp[4][3];
    for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
            temp[i][j] = 0;
            for(int k=0; k<3; k++){
                temp[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
            a[i][j] = temp[i][j];
        }
    }
}

void MainWindow::Draw(){
    image.fill(qRgb(0,0,0));

    Bresenham(x[0], y[0], x[1], y[1]);
    Bresenham(x[0], y[0], x[2], y[2]);
    Bresenham(x[2], y[2], x[3], y[3]);
    Bresenham(x[1], y[1], x[3], y[3]);

    ui->label->setPixmap(QPixmap :: fromImage(image));
}

int MainWindow::Sign(float a)
{
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

    for(int i=0;i<dx;i++){
        image.setPixel(x,y,qRgb(250,110,121));
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

void MainWindow::on_pushButton_clicked(){
    Draw();
}

void MainWindow::on_scale_button_clicked(){
    float scale_x, scale_y;
    scale_x = ui->Sx->toPlainText().toFloat();
    scale_y = ui->Sy->toPlainText().toFloat();

    float mat[4][3];
    float scale[3][3], translate[3][3];
    for(int i=0; i<4; i++){
        mat[i][0] = x[i];
        mat[i][1] = y[i];
        mat[i][2] = 1;
        if(i!=3){
            for(int j=0; j<3; j++){
                scale[i][j] = 0;
                translate[i][j] = 0;
                if(i==j){
                    scale[i][j] = 1;
                    translate[i][j] = 1;
                }
            }
        }
    }
    translate[2][0] = -200;
    translate[2][1] = -200;
    MatrixMultiplication(mat, translate);

    scale[0][0] = scale_x;
    scale[1][1] = scale_y;
    MatrixMultiplication(mat, scale);

    translate[2][0] = 200;
    translate[2][1] = 200;
    MatrixMultiplication(mat, translate);

    for(int i=0; i<4; i++){
        x[i] = mat[i][0];
        y[i] = mat[i][1];
    }
    Draw();
}


void MainWindow::on_rotate_button_clicked(){
    float angle, mat[4][3], rotation[3][3], translation[3][3];
    angle = ui->angle->toPlainText().toInt();

    angle /= 180;
    angle *= 3.14159;

    for(int i=0; i<4; i++){
        mat[i][0] = x[i];
        mat[i][1] = y[i];
        mat[i][2] = 1;
        if(i!=3){
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

    translation[2][0] = -(x[0]+x[3])/2;
    translation[2][1] = -(y[1]+y[2])/2;
    MatrixMultiplication(mat, translation);

    rotation[0][0] = cos(angle);
    rotation[1][1] = cos(angle);
    rotation[1][0] = sin(angle);
    rotation[0][1] = (-1*rotation[1][0]);
    MatrixMultiplication(mat, rotation);

    translation[2][0] = (x[0]+x[3])/2;
    translation[2][1] = (y[1]+y[2])/2;
    MatrixMultiplication(mat, translation);

    for(int i=0; i<4; i++){
        x[i] = mat[i][0];
        y[i] = mat[i][1];
    }
    Draw();
}

void MainWindow::on_translate_button_clicked(){
    int t_x, t_y;
    float mat[4][3];

    t_x = ui->Tx->toPlainText().toInt();
    t_y = ui->Ty->toPlainText().toInt();

    for(int i=0; i<4; i++){
        mat[i][0] = x[i];
        mat[i][1] = y[i];
        mat[i][2] = 1;
    }

    for(int i=0; i<4; i++){
        mat[i][0] += t_x;
        mat[i][1] += t_y;
    }

    for(int i=0; i<4; i++){
        x[i] = mat[i][0];
        y[i] = mat[i][1];
    }
    Draw();
}
