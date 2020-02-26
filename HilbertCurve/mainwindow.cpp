#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<cmath>
int level;
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::DDA(QImage &image,int x1,int y1,int x0,int y0){
    int len, dy, dx, i;
    float xinc, yinc, x, y;
    dy=(y1-y0);
    dx=(x1-x0);
    if(abs(dx)>=abs(dy))
        len=abs(dx);
    else
        len=abs(dy);
    xinc=float(dx)/len;
    yinc=float(dy)/len;
    x=x0;
    y=y0;
    for(i=0;i<abs(len);i++){
        x+=xinc;
        y+=yinc;
        image.setPixel(int(x),int(y),qRgb(50,100,100));
    }
}

void MainWindow::Hilbert(QImage &image,float P[4][2],float end[2][2],int dir,int n){
    float side;
    float PP[4][4][2];
    float M[4][2][2];
    int a,b,c,d, i;

    a=dir;
    b=(dir+1)%4;
    c=(dir+2)%4;
    d=(dir+3)%4;

    if(n==level){
        DDA(image,P[a][0],P[a][1],P[b][0],P[b][1]);
        DDA(image,P[b][0],P[b][1],P[c][0],P[c][1]);
        DDA(image,P[c][0],P[c][1],P[d][0],P[d][1]);

        end[0][0]=P[a][0];
        end[0][1]=P[a][1];
        end[1][0]=P[d][0];
        end[1][1]=P[d][1];
    }

    else{
        side=sqrt(pow((P[0][0]-P[1][0]),2)+pow((P[0][1]-P[1][1]),2))/4;
        for(i=0;i<4;i++){
            PP[i][0][0]=P[i][0]-side;
            PP[i][0][1]=P[i][1]+side;
            PP[i][1][0]=P[i][0]-side;
            PP[i][1][1]=P[i][1]-side;
            PP[i][2][0]=P[i][0]+side;
            PP[i][2][1]=P[i][1]-side;
            PP[i][3][0]=P[i][0]+side;
            PP[i][3][1]=P[i][1]+side;
        }

        Hilbert(image,PP[a],M[a],b,n+1);
        Hilbert(image,PP[b],M[b],a,n+1);
        Hilbert(image,PP[c],M[c],a,n+1);
        Hilbert(image,PP[d],M[d],d,n+1);

        DDA(image,M[a][0][0],M[a][0][1],M[b][0][0],M[b][0][1]);
        DDA(image,M[b][1][0],M[b][1][1],M[c][0][0],M[c][0][1]);
        DDA(image,M[c][1][0],M[c][1][1],M[d][1][0],M[d][1][1]);

        end[0][0]=M[a][1][0];
        end[0][1]=M[a][1][1];
        end[1][0]=M[d][0][0];
        end[1][1]=M[d][0][1];
    }
}

void MainWindow::on_pushButton_clicked(){
    QImage image(500, 500, QImage::Format_RGB888);
    level=ui->textEdit->toPlainText().toUInt();

    float P[4][2], M[2][2];
    P[0][0]=200;
    P[0][1]=300;
    P[1][0]=200;
    P[1][1]=200;
    P[2][0]=300;
    P[2][1]=200;
    P[3][0]=300;
    P[3][1]=300;

    Hilbert(image,P,M,0,0);

    ui->Canvas->setPixmap(QPixmap::fromImage(I));
}
