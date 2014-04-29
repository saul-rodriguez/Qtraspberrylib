#include "pbutton.h"

Pbutton::Pbutton(QObject *parent) :
    QObject(parent)
{
    state = 0;
    pin_state = 0;
}

void Pbutton::change_state(quint8 newstate)
{
    //Detect rising edge
    if (pin_state ==  0 && newstate == 1) {

        //Update the state of the button only on rising edge!
        if (state == 0) {
            state = 1;
        } else {
            state = 0;
        }

        emit button_changed(state);
    }

    pin_state = newstate;
}
