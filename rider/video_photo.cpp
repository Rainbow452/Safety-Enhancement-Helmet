#include "video_photo.h"

#include <time.h>


videoThread::videoThread()
{



}


void videoThread::update()
{
    cam.read(cvImg);
    ncnn_mat = cvImg.clone();
}
std::string videoThread::update_filename(){
    char pStrPath1[32];
    time_t currTime;
    struct tm *mt;
    currTime = time(NULL);
    mt = localtime(&currTime);

    //根据日期生成文件名
    sprintf(pStrPath1, "%d%02d%02d%02d%02d%02d", mt->tm_year + 1900, mt->tm_mon + 1, mt->tm_mday, mt->tm_hour, mt->tm_min, mt->tm_sec);

    //创建文件并保存内容
    return  pStrPath1;
}
