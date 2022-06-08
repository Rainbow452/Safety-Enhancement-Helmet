#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "yolo-fastestv2.h"
#include "mythread.h"
#include "awake_dectectthread.h"
#include "audiorecoding.h"

#include "video_photo.h"

#include <QDebug>
#include <QFileDialog>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private slots:


    void videoLB_slot();
    void on_openPb_clicked();
    void on_closePb_clicked();
    void awake_setect();
    void ncnn_update();
    void recod_video_slot();
    void take_photo_slot();
    void personNum_slot();
    void light_slot();

private:
    Ui::Widget *ui;
    QTimer *timer;
    cv::VideoCapture cam;
    cv::Mat cvImg;
    ncnnThread *ncnn_th;
    QImage  *qimage;
    AudioThread *audio;
    awake_dectectThread *awake_thread;
    videoThread *video_thread;

};

#endif // WIDGET_H
