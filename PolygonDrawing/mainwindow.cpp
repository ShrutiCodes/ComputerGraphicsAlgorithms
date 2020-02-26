#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "QColorDialog"
#include "QColor"
#include <cmath>
static QColor color1;
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

static QImage image(600, 500, QImage::Format_RGB888);
void MainWindow::mousePressEvent(QMouseEvent *ME){
    if(flag==false){
        if(ME->button() == Qt::RightButton){
            image = DDA(X[index-1],Y[index-1],X[0],Y[0],image);
            X[index-1] = X[0];
            Y[index-1] = Y[0];
            flag=true;
        }
        else if(index>0){
            X[index] = ME->pos().x();
            Y[index] = ME->pos().y();
            image = DDA(X[index-1],Y[index-1],X[index],Y[index],image);
            index++;
        }
        if(index == 0 && ME->button() != Qt::RightButton){
            X[index] = ME->pos().x();
            Y[index] = ME->pos().y();
            image.setPixel(X[0],Y[0],qRgb(255,255,255));
            index++;
        }
        ui->Canvas->setPixmap(QPixmap :: fromImage(image));
    }
}

int MainWindow::Sign(float x1,float x2)
{
    return((x2>x1)?1:-1);
}

QImage MainWindow::DDA(int x1,int y1,int x2,int y2, QImage image){
    float Dx, Dy, length, dx, dy, x, y;
    int sx, sy;
    Dx=abs(x2-x1);
    Dy=abs(x2-x1);

    length = (Dx>Dy)?Dx:Dy;
    dx=(x2-x1)/length;
    dy=(y2-y1)/length;

    sx=Sign(x2,x1);
    sy=Sign(y2,y1);

    x=x1 + sx*0.5;
    y=y1 + sy*0.5;

    for(int i=1;i<=length;i++){
        image.setPixel(int(x) ,int(y),color1.rgb() );
        x=x+dx;
        y=y+dy;
     }
     image.setPixel(int(x) ,int(y), color1.rgb());

     ui->Canvas->setPixmap(QPixmap::fromImage(image));

    return image;
}

void MainWindow::on_pushButton_clicked()
{
    color1=QColorDialog().getColor();
}
