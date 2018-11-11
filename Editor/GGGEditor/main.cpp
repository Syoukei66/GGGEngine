#include "GGGEditor.h"
#include <QtWidgets/QApplication>

#include <ActivityUtil.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GGGEditor w;
    w.show();

    QWindow;
    GGGEditorLibrary::Run((HWND)w.winId());

    return a.exec();
}
