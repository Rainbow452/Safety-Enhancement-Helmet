
#include "audiorecoding.h"
#include <QDebug>
#include <QString>
#include <QUrl>
AudioThread::AudioThread()
{
    audioRecorder = new QAudioRecorder();

    inputs = audioRecorder->audioInputs();

}
void AudioThread::set_init(QString input,QString L_file)
{
    QAudioEncoderSettings audioSettings;

    audioSettings.setCodec("audio/pcm");
    audioSettings.setSampleRate(16000);  //采样率   XXXXXXX
    audioSettings.setQuality(QMultimedia::EncodingQuality(10));
    audioSettings.setEncodingMode(QMultimedia::ConstantBitRateEncoding);

    audioRecorder->setOutputLocation(QUrl::fromLocalFile("/test.wav"));
    audioRecorder->setAudioInput(input);

    audioRecorder->setAudioSettings(audioSettings);

}

void AudioThread::start_audio(){
    audioRecorder->record();
}
void AudioThread::stop_audio(){
    audioRecorder->stop();
}
