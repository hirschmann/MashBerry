#include "qtempfilter.h"

QTempFilter::QTempFilter(QObject *parent) : QObject(parent)
{
}

double QTempFilter::FilterTemperature(double temperature)
{
    int temp = (int)(temperature * PRECISION_FACTOR);

    if((abs(m_sum / m_queue.length() - temp) > TEMP_MAX_DEVIATION * PRECISION_FACTOR)
        && (m_consecOutliers < OUTLIERS_LIMIT))
    {
        m_consecOutliers++;
        return m_queue.last() / (double)PRECISION_FACTOR;
    }
    else
    {
        m_consecOutliers = 0;
        AddTemperature(temp);
        return temperature;
    }
}

void QTempFilter::AddTemperature(int temperature)
{
    m_queue.enqueue(temperature);
    m_sum += temperature;

    if(m_queue.length() > QUEUE_MAX_LENGTH)
    {
        m_sum  -= m_queue.dequeue();
    }
}
