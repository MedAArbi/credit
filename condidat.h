#ifndef CONDIDAT_H
#define CONDIDAT_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDate>
#include <QDataStream>
#include<QPainter>
#include <QPdfWriter>
#include <QFileDialog>
#include <QTextDocument>

class condidat
{
public:
    void setID_C(QString n);
    void setNom_C(QString n);
    void setNum(QString n);
    void setemail(QString n);
    void setstatut_C(QString n);

    QString getID_C();
    QString getNom_C();
    QString getNum();
    QString getemail();
    QString getstatut_c();
    condidat();
    condidat(QString, QString, QString, QString, QString);

    bool ajoutercondidat();
    QSqlQueryModel* afficher();
    bool estDejaSupprime(QString id);
    bool supprimer(QString id);
    bool modifier();
    QSqlQueryModel* recherche(QString id);
    QSqlQueryModel* tri();
    QList<int> stat();
    static bool saveHistoryToFile(const QString &filePath);
    QJsonObject toJsonObject() const;
    int generateUniqueID();
        static QVector<condidat> History;
        int getID() const;
        QString getAction() const;
        QDateTime getDateTime() const;
        QString getDetails() const;
     void exportToPdf(const QList<QString> &condidatList);

private:
    QString id_c,nom_c,num,statut_c,email;
    QString action,details;
    QDateTime date;
    int ID;
    static int lastGeneratedID ;
};

#endif // CONDIDAT_H
