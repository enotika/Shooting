#include "tir.h"
#include "ui_tir.h"

tir::tir(QWidget *parent)
    : QWidget(parent)
    , imgCursor("D:/QTProjects/diubko_laba_mishen-main/cursor.png")
    , imgShot("D:/QTProjects/diubko_laba_mishen-main/shot.png")
    , ui(new Ui::tir)
{
    ui->setupUi(this);
    imgShot.setDevicePixelRatio(20);
    imgCursor.setDevicePixelRatio(6);
    Cursor=new QCursor(imgCursor);
    setCursor(*Cursor);
    setWindowState(Qt::WindowFullScreen);
    mPlayer = new QMediaPlayer();
    mPlayer->setMedia(QUrl("D:/QTProjects/diubko_laba_mishen-main/AS_Dancing.mp3"));
    mPlayer->setVolume(100);
    mPlayer->play();
}
void tir::mousePressEvent(QMouseEvent*){
    QPainter ptr(this);
    tgr->paint(&ptr, QPoint(QCursor::pos(this->screen())));
    qDebug() << QColor(this->screen()->grabWindow(0).toImage().pixel(QCursor::pos(this->screen())));
    if(QColor(this->screen()->grabWindow(0).toImage().pixel(QCursor::pos(this->screen())))==Qt::green){
        shotArr.push_back(QCursor::pos(this->screen()));
    }
    repaint();
}
void tir::paintEvent(QPaintEvent *event){
    QPainter ptr(this);
    if(QMouseEvent::MouseButtonPress && isTargetPainted < 2){
        qDebug() << "Ангелина дурочка";
        if(isTargetPainted==1)
        tgr = new Target(QPoint(QCursor::pos(this->screen())), &ptr);
        isTargetPainted++;
    }
    tgr->paint(&ptr, QPoint(QCursor::pos(this->screen())));
    for(qint32 i=0;i<shotArr.size();++i)
    {
        QPointF topleftPoint,downrightPoint;
        topleftPoint.setX(shotArr[i].x()-30);
        topleftPoint.setY(shotArr[i].y()-30);
        downrightPoint.setX(shotArr[i].x()+30);
        downrightPoint.setY(shotArr[i].y()+30);
        ptr.drawImage(QRectF(topleftPoint,downrightPoint),imgShot);
    }

}
tir::~tir()
{
    delete ui;
}


Target::Target(QPoint cursorPosition, QPainter *ptr)
{
    targetPosition = cursorPosition;
//    ptr->setPen(Qt::black);
//    ptr->setBrush(QBrush(Qt::green, Qt::SolidPattern));
//    ptr->drawPie(targetPosition.x()-300, targetPosition.y()-300, 600, 600, -90*16, -45*16);
//    ptr->drawPie(targetPosition.x()-300, targetPosition.y()-300, 600, 600, 45*16, 45*16);
}

void Target::operator ()(QPainter *ptr, QPoint cursorPosition)
{

}

void Target::paint(QPainter *ptr, QPoint cursorPosition)
{
    ptr->setPen(Qt::black);
    ptr->setBrush(QBrush(Qt::green, Qt::SolidPattern));
    ptr->drawPie(targetPosition.x()-300, targetPosition.y()-300, 600, 600, -90*16, -45*16);
    ptr->drawPie(targetPosition.x()-300, targetPosition.y()-300, 600, 600, 45*16, 45*16);

}
