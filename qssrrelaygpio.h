#ifndef QSSRRELAYGPIO_H
#define QSSRRELAYGPIO_H

#include "qssrrelay.h"
#include "qgpio.h"

class QSSRrelayGPIO : public QSSRrelay
{
    Q_OBJECT
public:
    explicit QSSRrelayGPIO(int ssr, bool activeLow = false, QObject *parent = 0);
    ~QSSRrelayGPIO();

    virtual void Start();
    virtual void SetPower(int power);

protected:
    void run();

signals:
    
public slots:

private:
    QGpio m_gpio;
    int m_power;
    bool m_bEndThread;
    bool m_bActiveLow;
};

#endif // QSSRRELAYGPIO_H
