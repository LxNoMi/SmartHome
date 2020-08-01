#ifndef RECORDER_H
#define RECORDER_H

#include <QObject>
#include <QDebug>
#include <QBuffer>
#include <QAudioInput>
#include <QAudioDeviceInfo>

class recorder : public QObject
{
    Q_OBJECT
public:
    explicit recorder(QObject *parent = nullptr);
    void beginRcd();
    void endRcd();

    QBuffer *m_buffer;

signals:

public slots:

private:
    QString m_location;
    QAudioDeviceInfo m_currentDevice;
    QAudioInput *m_audioInput;
};

#endif // RECORDER_H
