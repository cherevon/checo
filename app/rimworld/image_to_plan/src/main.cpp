#include "image_to_plan_widget.h"

#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    checo::rimworld::ImageToPlanWidget mainWindow;
    mainWindow.setWindowTitle("Rimworld Image to Plan");
    mainWindow.show();

    return app.exec();
}
