#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColor>
#include<math.h>
#include<QMouseEvent>
#include<QColorDialog>

QImage image(711,491,QImage::Format_RGB888);
QRgb col;

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    ver=0;
    start=true;
    color=qRgb(255,0,0);
}

MainWindow::~MainWindow(){
    delete ui;
}
int MainWindow :: Sign(int n, int m){
    if(n>m)
        return 1;
    else if(n<m)
        return -1;
    else if(n==m)
        return 0;
}

void MainWindow::dda(int x1,int y1,int x2,int y2){
    int x,y,dx,dy,s1,s2,temp,e,interchange,i;
    x=x1;
    y=y1;

    dx=abs(x2-x1);
    dy=abs(y2-y1);

    s1=Sign(x2,x1);
    s2=Sign(y2,y1);

    e=2*dy-dx;

    if(dy>dx){
        temp=dx;
        dx=dy;
        dy=temp;
        interchange=1;
    }
    else
        interchange=0;

    for(i=0;i<=dx;i++){
        image.setPixel(x,y,color);
        while(e>=0){
            if(interchange==1)
                x=x+s1;
            else
                y=y+s2;
            e=e-2*dx;
        }
        if(interchange==1)
            y=y+s2;
        else
            x=x+s1;
        e=e+2*dy;
    }
     ui->Canvas->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *ev){
    int p=ev->pos().x();
    int q=ev->pos().y();

    QRgb old=qRgb(0,0,0);
    seedfill(p,q,old,color);

    ui->Canvas->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::mousePressEvent(QMouseEvent *ev){
    if(start==true){
        int p=ev->pos().x();
        int q=ev->pos().y();
        a[ver]=p;
        b[ver]=q;
        if(ev->button()==Qt::RightButton){
            dda(a[0],b[0],a[ver-1],b[ver-1]);
            start=false;
        }
        else{
            if(ver>0)
                dda(a[ver],b[ver],a[ver-1],b[ver-1]);
        }
        ver++;
    }
}
void MainWindow::seedfill(int x,int y,QRgb old,QRgb col){
    QRgb curr=image.pixel(x,y);
    if(curr==old){
        image.setPixel(x,y,col);
        seedfill(x,y+1,old,col);
        seedfill(x-1,y,old,col);
        seedfill(x,y-1,old,col);
        seedfill(x+1,y,old,col);
    }
}

void MainWindow::on_pushButton_clicked(){
    QColor col;
    QColorDialog q;
    col=q.getColor();
    color=col.rgb();
}
