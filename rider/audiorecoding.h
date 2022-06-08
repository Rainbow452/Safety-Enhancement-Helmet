#ifndef AUDIORECODING_H
#define AUDIORECODING_H

#include <QObject>
#include <QThread>

#include <QDebug>
#include <QFileDialog>

class AudioThread : public QThread
{
    Q_OBJECT
public:
    int current_audio =1;
    void run() override{
    while(1){
    if(current_audio == 1){
 //录音，拼接音频
    system("arecord -d2 -c1 -r16000 -twav -fS16_LE ./audio/1.wav");
    system("rm ./audio/3.wav");
    system("ffmpeg  -i ./audio/2.wav -i ./audio/1.wav -filter_complex '[0:0] [1:0] concat=n=2:v=0:a=1 [a]' -map [a] ./audio/3.wav");
    emit audio_finish();

    current_audio = 2;
    }
    if(current_audio==2){
    system("arecord -d2 -c1 -r16000 -twav -fS16_LE ./audio/2.wav");
    system("rm ./audio/3.wav");
    system("ffmpeg -i ./audio/1.wav -i ./audio/2.wav -filter_complex '[0:0] [1:0] concat=n=2:v=0:a=1 [a]' -map [a] ./audio/3.wav");
    emit audio_finish();

    current_audio = 1;
    }
    }
}
private:


signals:
        void audio_finish();
};


#endif // AUDIORECODING_H
