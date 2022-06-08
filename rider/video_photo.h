#ifndef VIDEO_PHOTO_H
#define VIDEO_PHOTO_H
#include <QObject>
#include <QThread>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;
class videoThread : public QThread
{
    Q_OBJECT
public:
    videoThread();
   cv::VideoCapture cam;
   cv:: Mat ncnn_mat;
   int ncnn_need_mat=0;
    void update();

    cv::Mat cvImg;
    int recording_f = 0;
    int photo_f= 0;

    std::string update_filename();
    void run() override{
        cam.open(-1);
        cam.read(cvImg);
        ncnn_mat = cvImg.clone();

        cv::VideoWriter outputVideo;

        std::string videoname ="video/" + update_filename()+".avi";
        int codec = cv::VideoWriter::fourcc('M', 'P', '4', '2');
        cv::Size sWH = cv::Size((int)cam.get(cv::CAP_PROP_FRAME_WIDTH),
                (int)cam.get(cv::CAP_PROP_FRAME_HEIGHT));
        outputVideo.open(videoname, codec, 25.0, sWH, true);

     while(1){
         cam.read(cvImg);

         if(photo_f ==  1)
         {std::string photoname = "photo/" +update_filename() +".jpg";
             cv::imwrite(photoname,cvImg);
           //  printf("photo success\n");
             photo_f =0;
             emit ncnn_photo_finish();
         }

         if(ncnn_need_mat==1)
         {
             ncnn_mat = cvImg.clone();
             ncnn_need_mat=0;
            // printf("ncnn_mat buff success\n");
             emit ncnn_mat_finish();
         }

         if(recording_f==1)
         {outputVideo.write(cvImg);}

     }
    }
private:


signals:
    void ncnn_mat_finish();
    void ncnn_photo_finish();
};

#endif
