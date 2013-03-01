#include <QApplication>
#include "mainwindow.h"
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); //key step 1

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/splash.png"));
    splash->show();

    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;

    splash->showMessage(QObject::tr("Setting up the main window..."),
                        topRight, Qt::white);

    MainWindow *mainWin = new MainWindow; //key step 2

    splash->showMessage(QObject::tr("Loading modules..."),
                        topRight, Qt::white);

//  loadModules();

    splash->showMessage(QObject::tr("Establishing connections..."),
                        topRight, Qt::white);
//  establishConnections();

    mainWin->show(); //key step 3

    splash->finish(mainWin);
    delete splash;

    return app.exec(); //key step4
}
