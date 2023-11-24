#ifndef WEBCAMVIEWER_H
#define WEBCAMVIEWER_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QTimer>

class WebcamViewer : public QWidget
{
    Q_OBJECT

public:
    WebcamViewer(QWidget *parent = nullptr);
    ~WebcamViewer();

public slots:
    void updateImage();

private:
    QString videoDevice;
    int fd;
    struct v4l2_format format;
    struct v4l2_requestbuffers req = {};
    struct buffer
    {
        void *start;
        size_t length;
    } *buffers;
};

#endif // WEBCAMVIEWER_H
