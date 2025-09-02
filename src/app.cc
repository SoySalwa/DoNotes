#include <QApplication>
#include <QMessageBox>
#include "ui/MainWindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow w;
    w.setWindowTitle("DoNotes");
    w.resize(430, 320);
    w.show();
    return app.exec();
}