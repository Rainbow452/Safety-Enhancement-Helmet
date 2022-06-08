#ifndef AWAKE_DECTECTTHREAD_H
#define AWAKE_DECTECTTHREAD_H
#include <QObject>
#include <QThread>

#include <QDebug>
#include <QFileDialog>

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

class awake_dectectThread : public QThread
{
    Q_OBJECT
public:
    awake_dectectThread();
    int current_audio =1;
    int awake_f =0;
    int light_speech=0;
    int crowd_speech=0;
    /*0:未唤醒  >=1:唤醒*/
    void run() override{

        std::string line;
        std::string::size_type idx;
        std::ifstream in1("baidu_aip_result.txt");
if(awake_f==1||awake_f==2||awake_f==2)
    {system("python3 baidu-detect/baidu_aip.py");
    std::cout<<awake_f<<std::endl;
    awake_f+=1;
    std::ifstream in("awake_result.txt");
    std::string filename;
    std::string line;
    std::string::size_type idx1;
    std::string::size_type idx2;
    while (getline (in1, line)) // line中不包括每行的换行符
    {
    std::cout << line << std::endl;
    idx1 = line.find("video");
    idx2 = line.find("photo");
    if(!(idx1 == std::string::npos)) // have  "video"
        {
         std::cout<<"record_video\n"<<std::endl;
          emit record_video();

        }
    if(!(idx2 == std::string::npos)) //dont have  "photo"
        {
         std::cout<<"take_photo\n"<<std::endl;
         emit take_photo();
        }
    }


}

if(awake_f==0)
{
system("python3 snowboy_awake_python/main_snowboy_detect.py audio/3.wav snowboy_awake_python/rider.pmdl");

    std::ifstream in2("awake_result.txt");

    if(in2) // 有该文件
    {
    while (getline (in2, line)) // line中不包括每行的换行符
    {
    std::cout << line << std::endl;
    idx = line.find("no_awaked");
    if(idx == std::string::npos) //dont have  "no_awake"
        {
         std::cout<<"awaked"<<std::endl;
         awake_f+=1;
         system("aplay snowboy_awake_python/resources/ding.wav");
        }
    else{
         std::cout<<"no_awaked"<<std::endl;

         }
    }
    }
    else // 没有该文件
    {
        std::cout <<"no such file" << std::endl;
    }
}
if(awake_f>2)
{
    awake_f=0;
    system("aplay snowboy_awake_python/resources/dong.wav");
}

if(crowd_speech ==1)
{
    system("mplayer snowboy_awake_python/resources/crowd.mp3");
    crowd_speech=0;
}
if(light_speech ==1)
{
    system("mplayer snowboy_awake_python/resources/light.mp3");
    light_speech=0;
}



}

private:

signals:

        void take_photo();
        void record_video();
};


#endif // AWAKE_DECTECTTHREAD_H
