#include "qssrrelaykernel.h"

QSSRrelayKernel::QSSRrelayKernel(int ssr, bool activeLow, QObject *parent) :
    QSSRrelay(parent)
{
    m_bActiveLow = activeLow;
    m_ssr = new QFile(QString("/sys/devices/platform/ssr_plug.0/ssr_%1").arg(ssr));
    m_ssr->open(QIODevice::WriteOnly);
}

void QSSRrelayKernel::Start()
{

}

void QSSRrelayKernel::SetPower(int power)
{
    char pwr[8];
    int value = m_bActiveLow ? 100 - power : power;

    sprintf(pwr, "%d\n", value);
    m_ssr->write(pwr, strlen(pwr) + 1);
    m_ssr->flush();
}
