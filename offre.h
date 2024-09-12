#ifndef OFFRE_H
#define OFFRE_H


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

class offre
{
public:
    void setID_o(QString n);
    void settitre(QString n);
    void setdesc(QString n);
    void setstatut_o(QString n);

    QString getID_o();
    QString gettitre();
    QString getdesc();
    QString getstatut_o();
    offre();
    offre(QString, QString, QString, QString);

    bool ajouteroffre();
    QSqlQueryModel* afficher();
    bool supprimer(QString id);
    bool modifier();
    QSqlQueryModel* recherche(QString id);
    QSqlQueryModel* tri();
    QList<int> stat();
    static bool saveHistoryToFile(const QString &filePath);
    QJsonObject toJsonObject() const;
    int generateUniqueID();
        static QVector<offre> History;
        int getID() const;
        QString getAction() const;
        QDateTime getDateTime() const;
        QString getDetails() const;
     void exportToPdf(const QList<QString> &offreList);

private:
    QString id_o,titre,description,statut_o;
    QString action,details;
    QDateTime date;
    int ID;
    static int lastGeneratedID ;
};

#endif // OFFRE_H
