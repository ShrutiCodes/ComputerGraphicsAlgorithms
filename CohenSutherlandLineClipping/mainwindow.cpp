#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"

QImage image(600, 500, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    index = 0;
    flag = true;
    cnt = 0;
    value = qRgb(0, 0, 0);
    for(int i=0; i<4; i++){
        code1[i] = 0;
        code2[i] = 0;
    }
}
MainWindow::~MainWindow(){
    delete ui;
}
bool MainWindow::Discard(int c1[], int c2[]){
    for(int i=0; i<4; i++){
        if(c1[i] == 1 && c2[i] == 1){
            return true;
        }
    }
    return false;
}
bool MainWindow::CheckIfOutside(int c[]){
    for(int i=0; i<4; i++){
        if(c[i]==1){
            return true;
        }
    }
    return false;
}
void MainWindow::Clipping(int x1, int y1, int x2, int y2){
    CodeGenerate(x1, y1, code1);
    CodeGenerate(x2, y2, code2);
    if(!Discard(code1, code2)){
        if(CheckIfOutside(code1)){
            float tempx, tempy;
            if(code1[0] == 1){
                tempx = win[0];
                tempy = (tempx-x1)/(x2-x1);
                tempy *= (y2-y1);
                x1 = tempx;
                y1 += tempy;
            }
            if(code1[1] == 1){
                tempy = win[1];
                tempx = (tempy-y1)/(y2-y1);
                tempx *= (x2-x1);
                x1 += tempx;
                y1 = tempy;
            }
            if(code1[2] == 1){
                tempx = win[2];
                tempy = (tempx-x1)/(x2-x1);
                tempy *= (y2-y1);
                x1 = tempx;
                y1 += tempy;
            }
            if(code1[3] == 1){
                tempy = win[3];
                tempx = (tempy-y1)/(y2-y1);
                tempx *= (x2-x1);
                x1 += tempx;
                y1 = tempy;
            }
        }
        if(CheckIfOutside(code2)){
            float tempx, tempy;
            if(code2[0] == 1){
                tempx = win[0];
                tempy = (tempx-x2)/(x2-x1);
                tempy *= (y2-y1);
                x2 = tempx;
                y2 += tempy;
            }
            if(code2[1] == 1){
                tempy = win[1];
                tempx = (tempy-y2)/(y2-y1);
                tempx *= (x2-x1);
                x2 += tempx;
                y2 = tempy;
            }
            if(code2[2] == 1){
                tempx = win[2];
                tempy = (tempx-x2)/(x2-x1);
                tempy *= (y2-y1);
                x2 = tempx;
                y2 += tempy;
            }
            if(code2[3] == 1){
                tempy = win[3];
                tempx = (tempy-y2)/(y2-y1);
                tempx *= (x2-x1);
                x2 += tempx;
                y2 = tempy;
            }
        }
        Bresenham(x1, y1, x2, y2);
    }
    for(int i=0; i<4; i++){
        code1[i] = 0;
        code2[i] = 0;
    }
}
void MainWindow::CodeGenerate(int x, int y, int*code){
    if(x < win[0]){
        code[0] = 1;
    }
    else if(x > win[2]){
        code[2] = 1;
    }
    if(y < win[1]){
        code[1] = 1;
    }
    else if(y > win[3]){
        code[3] = 1;
    }
}
void MainWindow :: mousePressEvent(QMouseEvent *me){
    if(cnt < 2){
        int temp = cnt*2;
        win[temp] = me->pos().x();
        win[temp+1] = me->pos().y();
        cnt++;
        if(cnt == 2){
            value = qRgb(255, 255, 255);
            Bresenham(win[0], win[1], win[2], win[1]);
            Bresenham(win[0], win[3], win[2], win[3]);
            Bresenham(win[0], win[1], win[0], win[3]);
            Bresenham(win[2], win[1], win[2], win[3]);
        }
    }
    else{
        value = qRgb(238, 130, 238);
        if(me->button() == Qt::RightButton && index!=0 && flag){
            Clipping(x[index-1], y[index-1],x[0], y[0]);
            x[index-1] = x[0];
            y[index-1] = y[0];
            flag = false;
        }
        else if(index>0 && flag){
            x[index] = me->pos().x();
            y[index] = me->pos().y();
            Clipping(x[index-1],y[index-1],x[index],y[index]);
            index++;
        }
        if(index == 0 && me->button() != Qt::RightButton && flag){
            x[0] = me->pos().x();
            y[0] = me->pos().y();
            index++;
        }
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}
int MainWindow::Sign(float a){
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
