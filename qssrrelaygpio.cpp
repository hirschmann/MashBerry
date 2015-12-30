#include "qssrrelaygpio.h"

QSSRrelayGPIO::QSSRrelayGPIO(int gpio, bool activeLow, QObject *parent) :
    QSSRrelay(parent)
{
    m_bActiveLow = activeLow;
    m_gpio.Open(gpio, true);
    int power = activeLow ? 100 : 0;
    m_gpio.Set(power);
}

QSSRrelayGPIO::~QSSRrelayGPIO()
{
    m_bEndThread = true;
    if(!wait(2000))
        terminate();
}

void QSSRrelayGPIO::Start()
{
    start(QThread::TimeCriticalPriority);
}

void QSSRrelayGPIO::SetPower(int power)
{
    if(m_bActiveLow)
    {
        m_power = 100 - power;
    }
    else
    {
        m_power = power;
    }
}

void QSSRrelayGPIO::run()
{
    int onTime;
    int offTime;

    while(!m_bEndThread)
    {
        if(m_power > 0)
        {
            onTime = m_power * 20;
            offTime = (100 - m_power) * 20;
            m_gpio.Set(1);
            msleep(onTime);
            if(offTime > 0)
            {
                m_gpio.Set(0);
                msleep(offTime);
            }
        }
        else
        {
            m_gpio.Set(0);
            msleep(2000);
        }
    }
}

