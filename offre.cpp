#include "offre.h"

#include <QSqlError>
#include <QSqlQueryModel>
QVector<offre> offre::History;
int offre::lastGeneratedID = 0;

offre::offre()
{
    id_o="";
    titre="";
    description="";
    statut_o="";
}
offre::offre(QString a, QString b, QString c, QString d)
{
    id_o=a;
    titre=b;
    description=c;
    statut_o=d;
}

QString offre::getID_o()
{
    return id_o;
}

QString offre::gettitre()
{
    return titre;
}

QString offre::getdesc()
{
    return description;
}
QString offre::getstatut_o()
{
    return statut_o;
}
int offre::getID() const  {

    return ID;
}
QString offre::getAction() const  {

    return action;
}
QDateTime offre::getDateTime() const  {

    return date;
}
QString offre::getDetails() const  {

    return details;
}


void offre::setID_o(QString n)
{
    id_o=n;
}
void offre::settitre(QString n)
{
   titre=n;
}
void offre::setdesc(QString n)
{
    description=n;
}
void offre::setstatut_o(QString n)
{
    statut_o=n;
}

bool offre::ajouteroffre()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE VALUES (:id,:nom,:num,:statut)");
    query.bindValue(":id", id_o);
    query.bindValue(":nom",titre);
    query.bindValue(":num",description);
    query.bindValue(":statut",statut_o);

    if (query.exec()) {
            {qDebug() << " ajouté avec succès !";
            ID = generateUniqueID();
                action = "Ajout";
                date = QDateTime::currentDateTime();
                details = QString("ID: %1, titre: %2, description: %3, statut: %4")
                           .arg(id_o)
                           .arg(titre)
                           .arg(description)
                           .arg(statut_o);

                History.append(*this);
                saveHistoryToFile("C:/Users/dell/Desktop/fileqt/history.json");
        }
            return true;
        } else {
            qDebug() << "Erreur lors de l'ajout de condidat : " << query.lastError().text();
            return false;
        }

}

QSqlQueryModel* offre::afficher()
{
    QSqlQueryModel* empl=new QSqlQueryModel();

    empl->setQuery("SELECT * FROM OFFRE");
    empl->setHeaderData(0, Qt::Horizontal, QObject ::tr("id_o"));
    empl->setHeaderData(1, Qt::Horizontal,QObject :: tr("titre"));
    empl->setHeaderData(2, Qt::Horizontal, QObject ::tr("description"));
    empl->setHeaderData(4, Qt::Horizontal, QObject ::tr("statut_o"));
    qDebug()<<"ok";
    return  empl;
}



bool offre::supprimer(QString id)
{


QSqlQuery query;
query.prepare("SELECT titre, description, statut_o FROM OFFRE WHERE ID_O = :id");
query.bindValue(":id", id);

if (query.exec() && query.next()) {
    QString nom_e = query.value("titre").toString();
    QString poste = query.value("description").toString();
    QString email = query.value("statut_o").toString();

    // Supprimer
    query.prepare("DELETE FROM OFFRE WHERE ID_O = :id");
    query.bindValue(":id", id);
    query.exec();

    // Enregistrer l'historique
    ID = generateUniqueID();
    action = "Suppression";
    date = QDateTime::currentDateTime();
    details = QString("ID: %1, titre: %2, description: %3, statut: %4")
               .arg(id_o)
               .arg(titre)
               .arg(description)
               .arg(statut_o);

    History.append(*this);
    saveHistoryToFile("C:/Users/dell/Desktop/fileqt/history.json");

    // Retourner true pour indiquer que la suppression a réussi
    return true;
}

return false;}

bool offre::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE OFFRE "" SET titre=:titre, description=:description, statut_c=:stat"" WHERE ID_O= :id");
    query.bindValue(":id",id_o);
    query.bindValue(":nom",titre);
    query.bindValue(":desc",description);
    query.bindValue(":stat",statut_o);
    ID = generateUniqueID();
        action = "Modification";
        date = QDateTime::currentDateTime();
        details = QString("ID: %1, titre: %2, description: %3, statut: %4")
                   .arg(id_o)
                   .arg(titre)
                   .arg(description)
                   .arg(statut_o);

        History.append(*this);
        saveHistoryToFile("C:/Users/dell/Desktop/fileqt/history.json");
    return query.exec();
}

QSqlQueryModel* offre::recherche(QString id)
{

    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT * FROM OFFRE WHERE id_o = :ID");
    query.bindValue(":ID", id);
    query.exec();

    model->setQuery(query);
    return model;
}

QSqlQueryModel* offre::tri()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM OFFRE ORDER BY id_c ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_o"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("titre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("statut_o"));

    return model;
}

QList<int> offre::stat()
{
    QList<int> stat;
    QSqlQuery query;

    query.exec("SELECT COUNT(*) FROM offre WHERE statut_o = 'En cours'");
    if (query.next()) {
        stat.append(query.value(0).toInt());
    }

    query.exec("SELECT COUNT(*) FROM offre WHERE statut_o = 'Actif'");
    if (query.next()) {
        stat.append(query.value(0).toInt());
    }

    query.exec("SELECT COUNT(*) FROM offre WHERE statut_o = 'Clôturé'");
    if (query.next()) {
        stat.append(query.value(0).toInt());
    }

    return stat;
}

bool offre::saveHistoryToFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Error opening file for writing: " << file.errorString();
        return false;
    }

    QJsonArray jsonArray;
    for (const offre &empl : History)
     {
         QJsonObject Object;
         Object["ID"] = empl.getID();
         Object["Action"] = empl.getAction();
         Object["Date"] = empl.getDateTime().toString("yyyy-MM-dd HH:mm:ss");
         Object["Details"] = empl.getDetails();

         jsonArray.append(Object);
     }
    QJsonDocument jsonDoc(jsonArray);
    file.write(jsonDoc.toJson());
    file.close();

    return true;
}
QJsonObject offre::toJsonObject() const
{
    QJsonObject jsonObj;

    jsonObj["Id"] = id_o;
    jsonObj["titre"] = titre;
    jsonObj["description"] = description;
    jsonObj["statut"] = statut_o;


    return jsonObj;
}

int offre::generateUniqueID()
{

    QFile file("C:/Users/dell/Desktop/fileqt");
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        in >> lastGeneratedID;
        file.close();
    }


    int newID = ++lastGeneratedID;


    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << lastGeneratedID;
        file.close();
    }

    return newID;
}
