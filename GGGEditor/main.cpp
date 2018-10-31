#include "GGGEditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GGGEditor w;
    w.show();
    return a.exec();
}
