
#include "mythread.h"

ncnnThread::ncnnThread()
{
    api.loadModel("model/yolo-fastestv2-opt.param",
                  "model/yolo-fastestv2-opt.bin");

    person_timer = new QTimer(this);
    light_timer = new QTimer(this);


    connect(person_timer, SIGNAL(timeout()), this, SLOT(person_slot()));
    connect(light_timer, SIGNAL(timeout()), this, SLOT(light_slot()));

    person_timer->start();
    light_timer->start();
}

void ncnnThread::person_slot(){
    crowd_speech = 1;
    person_timer->stop();
}

void ncnnThread::light_slot(){
    light_speech = 1;
    light_timer->stop();
}
