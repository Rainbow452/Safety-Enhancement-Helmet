#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QObject>
#include <QThread>
#include "yolo-fastestv2.h"
#include <QImage>
#include <QTimer>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class ncnnThread : public QThread
{
    Q_OBJECT
public:
    ncnnThread();
    QImage qimage;
    cv::Mat cvImg;
    int write = 1;  //0图片写入中，1图片写入完成
    double fps;
    char string[10];  // 用于存放帧率的字符串
    double t = 0;
    double t_now=0;
    int personNum=0;
    int light_exist=0;
    int crowd_speech=0;
    int light_speech=0;
    void run() override{
        static const char* class_names[] = {
        "person", "bicycle", "car", "motorcycle", "airplane", "bus", "train", "truck", "boat", "traffic light",
        "fire hydrant", "stop sign", "parking meter", "bench", "bird", "cat", "dog", "horse", "sheep", "cow",
        "elephant", "bear", "zebra", "giraffe", "backpack", "umbrella", "handbag", "tie", "suitcase", "frisbee",
        "skis", "snowboard", "sports ball", "kite", "baseball bat", "baseball glove", "skateboard", "surfboard",
        "tennis racket", "bottle", "wine glass", "cup", "fork", "knife", "spoon", "bowl", "banana", "apple",
        "sandwich", "orange", "broccoli", "carrot", "hot dog", "pizza", "donut", "cake", "chair", "couch",
        "potted plant", "bed", "dining table", "toilet", "tv", "laptop", "mouse", "remote", "keyboard", "cell phone",
        "microwave", "oven", "toaster", "sink", "refrigerator", "book", "clock", "vase", "scissors", "teddy bear",
        "hair drier", "toothbrush" };

        /* ... here is the expensive or blocking operation ... */
     /*   if(load_model==0){
            api.loadModel("./model/yolo-fastestv2-opt.param",
                          "./model/yolo-fastestv2-opt.bin");
            load_model=1;

        }
        */

       // api.loadModel("model/yolo-fastestv2-opt.param",
           //           "model/yolo-fastestv2-opt.bin");

            //cv::Mat cvImg = cv::imread("test.jpg");
        std::vector<TargetBox> boxes;

            api.detection(cvImg, boxes);

    personNum=0;
    light_exist=0;
   for (int i = 0; i < boxes.size(); i++) {
       // printf("cateNum: %d\n",boxes[i].cate );
       if(boxes[i].cate == 0)
        {personNum+=1;}
       if(boxes[i].cate == 9)
       { light_exist =1;   }
       std::cout<<boxes[i].x1<<" "<<boxes[i].y1<<" "<<boxes[i].x2<<" "<<boxes[i].y2
                  <<" "<<boxes[i].score<<" "<<boxes[i].cate<<std::endl;

         char text[256];
         sprintf(text, "%s %.1f%%", class_names[boxes[i].cate], boxes[i].score * 100);

         int baseLine = 0;
         cv::Size label_size = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);

         int x = boxes[i].x1;
         int y = boxes[i].y1 - label_size.height - baseLine;
         if (y < 0)
             y = 0;
         if (x + label_size.width > cvImg.cols)
             x = cvImg.cols - label_size.width;

         cv::rectangle(cvImg, cv::Rect(cv::Point(x, y), cv::Size(label_size.width, label_size.height + baseLine)),
                       cv::Scalar(255, 255, 255), -1);

         cv::putText(cvImg, text, cv::Point(x, y + label_size.height),
                     cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));

         cv::rectangle (cvImg, cv::Point(boxes[i].x1, boxes[i].y1),
                        cv::Point(boxes[i].x2, boxes[i].y2), cv::Scalar(255, 255, 0), 2, 2, 0);
     }
    printf("crowd: %d   light: %d\n",crowd_speech,light_speech);
    std::cout<<person_timer->isActive()<<std::endl;
   if(crowd_speech==1 && personNum==1)
   {
       emit personNum_finish();
       crowd_speech=0;
       printf("fofofofof\n\n\ngoggoog");
       person_timer->start(5000);
   }
   if(light_speech==1 && light_exist == 1)
   {
       emit light_finish();
       light_speech=0;
       light_timer->start(5000);
   }

            cv::cvtColor(cvImg, cvImg, cv::COLOR_BGR2RGB);

            t = ((double)cv::getTickCount()-t_now)/cv::getTickFrequency();
            t_now = (double)cv::getTickCount();
            fps = 1.0/t;
            sprintf(string, "%.2f",fps);  //帧率保留两位小数
            std::string fpsString("FPS:");
            fpsString += string;
            // 图像矩阵  // string型文字内容  // 文字坐标，以左下角为原点  // 字体类型
            // 字体大小    // 字体颜色
            cv::putText(cvImg, fpsString, cv::Point(5,40),
                        cv::FONT_HERSHEY_SIMPLEX,1.5,  cv::Scalar(200,0,0));

            QImage qima;
            qima = QImage((const uchar*)(cvImg.data), cvImg.cols, cvImg.rows,
                cvImg.cols * cvImg.channels(), QImage::Format_RGB888);

            qimage = qima.copy();

            write = 0;
            emit ncnn_finish();




}


private:

    yoloFastestv2 api;
    QTimer  *light_timer;
    QTimer  *person_timer;
private slots:
    void person_slot();
    void light_slot();

signals:
    void ncnn_finish();
    void personNum_finish();
    void light_finish();
};

#endif // MYTHREAD_H
