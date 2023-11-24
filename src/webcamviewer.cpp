#include "webcamviewer.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <QDebug>

WebcamViewer::WebcamViewer(QWidget *parent)
    : QWidget(parent), videoDevice("/dev/video0")
{
    // Open the video device
    fd = open(videoDevice.toStdString().c_str(), O_RDWR);

    if (fd == -1)
    {
        qDebug() << "Error: Unable to open the video device.";
        return;
    }

    // Set up the video format
    // (Assuming MJPEG format, adjust as needed)
    struct v4l2_format format = {};
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.width = 640;
    format.fmt.pix.height = 480;
    format.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
    ioctl(fd, VIDIOC_S_FMT, &format);

    // Set up the GUI
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *imageLabel = new QLabel(this);
    layout->addWidget(imageLabel);

    // Create a timer to update the image periodically
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateImage()));
    timer->start(33); // Update every 33 milliseconds (approx 30 fps)

    setLayout(layout);
}

WebcamViewer::~WebcamViewer()
{
    // Close the video device
    close(fd);
}

void WebcamViewer::updateImage()
{
    // Read a frame from the video device
    struct v4l2_buffer buf = {};
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    ioctl(fd, VIDIOC_DQBUF, &buf);

    // Copy the frame data to a QImage
    QImage img(
        buffers[buf.index].start,
        format.fmt.pix.width,
        format.fmt.pix.height,
        format.fmt.pix.bytesperline,
        QImage::Format_RGB32);

    // Display the image
    QLabel *imageLabel = findChild<QLabel *>();
    imageLabel->setPixmap(QPixmap::fromImage(img));

    // Re-enqueue the buffer
    ioctl(fd, VIDIOC_QBUF, &buf);
}
