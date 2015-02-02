#ifndef PBUTTON_H
#define PBUTTON_H

#include <QObject>

class Pbutton : public QObject
{
    Q_OBJECT
public:
    explicit Pbutton(QObject *parent = 0);
    
    void change_state(quint8 newstate);
    void on_off(quint8 newstate);

signals:
    void button_changed(quint8 direction);

public slots:

private:
    quint8 pin_state;
    quint8 state;
    
};

#endif // PBUTTON_H
