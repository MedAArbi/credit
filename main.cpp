#include "mainwindow.h"

#include <QMessageBox>
#include "connection.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    connection c;
    bool test=c.createconnect();
    QApplication a(argc, argv);
    MainWindow w;


    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to continue."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
