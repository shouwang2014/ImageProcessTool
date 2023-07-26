#include "ImageProcess.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("MobilSono");
    QCoreApplication::setApplicationName("MobilSonoImageProcess");
    QCoreApplication::setApplicationVersion("1.0");

    QApplication a(argc, argv);
    ImageProcess w;
    w.show();
    return a.exec();
}
