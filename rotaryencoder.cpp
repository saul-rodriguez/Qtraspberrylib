#include "rotaryencoder.h"

RotaryEncoder::RotaryEncoder(QObject *parent) :
    QObject(parent)
{
    state = 0;
}

void RotaryEncoder::change_state(quint8 newstate)
{

    if (state == 1 && newstate == 3) { //UP
        emit encoder_changed(UP);
        qDebug("UP");

    }

    if (state == 2 && newstate == 3) { //DOWN
        emit encoder_changed(DOWN);
        qDebug("DOWN");
    }

    state = newstate;
}
