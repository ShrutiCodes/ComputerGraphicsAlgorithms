#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow::Integer(float f){
    return(int(f));
}

int MainWindow::Sign(float f){
      if(f==0)
          return 0;
      else if(f>0)
          return 1;
      else if(f<0)
          return -1;
}

QImage MainWindow::DDALine(int x1,int y1,int x2,int y2, QImage image){

    int dx, dy, length;
    float x=x1, y=y1;
    float incx, incy;

    dx = (x2 - x1);
    dy = (y2 - y1);

    if(abs(dx)>=abs(dy))
    {
        length = dx;
    }
    else{
        length = dy;
    }

    incx = dx/length;
    incy = dy/length;

    image.setPixel(x, y, qRgb(10,3,200));
    for(int i=1; i<length; i++){
        x += incx;
        y += incy;

        x1 = x+0.5;
        y1 = y+0.5;

        image.setPixel(x1, y1, qRgb(10,3,200));
    }
    return image;
}
QImage MainWindow::BresenhamLine(int x_1,int y_1,int x_2,int y_2,QImage I){
    int dx,dy,s1,s2,temp,flag_interchange,e,x,y;
    x=x_1;
    y=y_1;
    dx=abs(x_2-x_1);
    dy=abs(y_2-y_1);
    s1=Sign(x_2-x_1);
    s2=Sign(y_2-y_1);

    if(dy>dx){
        temp=dx;
        dx=dy;
        dy=temp;
        flag_interchange=1;
    }
    else
        flag_interchange=0;

    e=2*dy-dx;

    for(int i=1;i<=dx;i++){
        I.setPixel(x,y,qRgb(100,0,150));
        while(e>=0){
            if(flag_interchange==1)
                x=x+s1;
            else
                y=y+s2;
            e=e+(2*dy)-(2*dx);
        }
        if(flag_interchange==1)
            y=y+s2;
        else
            x=x+s1;
        e=e+(2*dy);
    }
    return I;
}

void MainWindow::on_pushButton_clicked()
{
    x1=ui->T_x1->toPlainText().toFloat();
    y1=ui->T_y1->toPlainText().toFloat();
    x2=ui->T_x2->toPlainText().toFloat();
    y2=ui->T_y2->toPlainText().toFloat();

    QImage Q(400,400,QImage::Format_RGB888);
    if(x2-x1==y2-y1){
        Q=BresenhamLine(x1,y1,x2,y1,Q);
        Q=BresenhamLine(x2,y1,x2,y2,Q);
        Q=BresenhamLine(x2,y2,x1,y2,Q);
        Q=BresenhamLine(x1,y2,x1,y1,Q);
        int x3,y3,x4,y4;

        x3=(x2-x1);
        y3=(y2-y1);
        x3/=2;
        y3/=2;

        x4=x3+x1;
        y4=y3+y1;

        Q = DDALine(x4, y1, x2, y4, Q);
        Q = DDALine(x4, y2, x2, y4, Q);
        Q = DDALine(x1, y4, x4, y2, Q);
        Q = DDALine(x1, y4, x4, y1, Q);

        x3/=2;
        y3/=2;

        x1+=x3;
        x2-=x3;
        y1+=y3;
        y2-=y3;

        Q=BresenhamLine(x1,y1,x2,y1,Q);
        Q=BresenhamLine(x2,y1,x2,y2,Q);
        Q=BresenhamLine(x2,y2,x1,y2,Q);
        Q=BresenhamLine(x1,y2,x1,y1,Q);

        ui->L3->setPixmap(QPixmap::fromImage(Q));
     }
}
