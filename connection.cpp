#include "connection.h"

connection::connection()
{

}
bool connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("nour");
db.setUserName("aziz");//inserer nom de l'utilisateur
db.setPassword("aziz");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





return  test;
}
