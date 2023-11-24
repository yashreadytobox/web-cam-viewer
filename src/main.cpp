#include <QApplication>
#include "webcamviewer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    WebcamViewer viewer;
    viewer.setWindowTitle("Webcam Viewer");
    viewer.setGeometry(100, 100, 640, 480);
    viewer.show();

    return app.exec();
}
