#include "recorder.h"

recorder::recorder(QObject *parent) : QObject(parent)
{
    const auto &&availableDevices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    if(!availableDevices.isEmpty())
    {
        m_currentDevice = availableDevices.first();
        m_buffer = new QBuffer;
        QAudioFormat format;
        format.setSampleRate(16000);//设置声音的采样频率
        format.setChannelCount(1);//设置声音的声道
        format.setSampleSize(16);//16位深
        format.setSampleType(QAudioFormat::SignedInt);
        format.setByteOrder(QAudioFormat::LittleEndian);
        format.setCodec("audio/pcm");
        m_audioInput = new QAudioInput(m_currentDevice, format, this);
    }
}

//开始录音
void recorder::beginRcd()
{
    qDebug()<<"录音开始";
    m_buffer->write("");
    m_buffer->open(QIODevice::ReadWrite);
    m_audioInput->start(m_buffer);
}

//结束录音
void recorder::endRcd()
{
    qDebug()<<"录音结束";
    m_audioInput->stop();
}
