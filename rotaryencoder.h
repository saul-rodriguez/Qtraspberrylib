#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include <QObject>

#define UP 1
#define DOWN 0

class RotaryEncoder : public QObject
{
    Q_OBJECT
public:
    explicit RotaryEncoder(QObject *parent = 0);
    
    void change_state(quint8 newstate);
signals:
    void encoder_changed(quint8 direction);

public slots:

private:
    quint8 state;

    
};

#endif // ROTARYENCODER_H
