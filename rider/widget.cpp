#include "widget.h"
#include "ui_widget.h"
#include "mythread.h"
#include "awake_dectectthread.h"
#include "video_photo.h"
#include <QImage>
#include <QPixmap>
#include<QDesktopWidget>
#include<QStyle>
#include<QRect>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->videoLB->setScaledContents(true);  // 图片自适应

    QDesktopWidget *deskTopWidget = QApplication::desktop();
    QRect deskRect  = deskTopWidget->availableGeometry();
    int appH = deskRect.height();
    int appW = deskRect.width();
    this->setFixedSize(appW,appH);
    this->setGeometry(0, 0, appW, appH);

    audio = new AudioThread();
    audio->start();
    awake_thread = new awake_dectectThread();
    connect(audio, SIGNAL(audio_finish()), this, SLOT(awake_setect()));
    connect(awake_thread, SIGNAL(record_video()), this ,SLOT(recod_video_slot()));
    connect(awake_thread, SIGNAL(take_photo()), this ,SLOT(take_photo_slot()));

   video_thread = new videoThread();
   video_thread->update();
   video_thread->start();
   connect(video_thread, SIGNAL(ncnn_mat_finish()), this, SLOT(ncnn_update()));

   ncnn_th = new ncnnThread();
   connect(ncnn_th, SIGNAL(ncnn_finish()), this, SLOT(videoLB_slot()));
   connect(ncnn_th, SIGNAL(personNum_finish()), this, SLOT(personNum_slot()));
   connect(ncnn_th, SIGNAL(light_finish()), this, SLOT(light_slot()));

}

Widget::~Widget()
{
    delete ui;
}



void Widget::videoLB_slot()
{
   video_thread->ncnn_need_mat=1;
   printf("personNum: %d\n", ncnn_th->personNum);
   ui->videoLB->setPixmap(QPixmap::fromImage(ncnn_th->qimage));

}
void Widget::ncnn_update()
{
    ncnn_th->cvImg = video_thread->ncnn_mat.clone();
    ncnn_th->write =1;
    ncnn_th->start();
}

void Widget::on_openPb_clicked()
{
    //video_thread->cam.open(-1);
   // video_thread->update();
    //video_thread->start();
    ncnn_th->cvImg=video_thread->ncnn_mat.clone();

    ncnn_th->write=1;
    ncnn_th->start();

}
void Widget::on_closePb_clicked()
{
    ncnn_th->quit();
    ui->videoLB->clear();

    ncnn_th->write=0;
    video_thread->cam.release();
//    cam.release();

}
void Widget::awake_setect()
{
    awake_thread->start();

}

void Widget::recod_video_slot(){
    video_thread->recording_f=1;
}
void Widget::take_photo_slot()
{
    video_thread->photo_f=1;
    printf("take photo slot \n");
}
void Widget::personNum_slot()
{
   awake_thread->crowd_speech=1;

}

void Widget::light_slot()
{

  awake_thread->light_speech=1;
}
