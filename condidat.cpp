#include "condidat.h"

#include <QSqlError>
#include <QSqlQueryModel>
QVector<condidat> condidat::History;
int condidat::lastGeneratedID = 0;

condidat::condidat()
{
    id_c="";
    nom_c="";
    num="";
    email="";
    statut_c="";
}
condidat::condidat(QString a, QString b, QString c, QString d, QString e)
{
    id_c=a;
    nom_c=b;
    num=c;
    email=d;
    statut_c=e;
}

QString condidat::getID_C()
{
    return id_c;
}

QString condidat::getNom_C()
{
    return nom_c;
}

QString condidat::getNum()
{
    return num;
}
QString condidat::getemail()
{
    return email;
}
QString condidat::getstatut_c()
{
    return statut_c;
}
int condidat::getID() const  {

    return ID;
}
QString condidat::getAction() const  {

    return action;
}
QDateTime condidat::getDateTime() const  {

    return date;
}
QString condidat::getDetails() const  {

    return details;
}


void condidat::setID_C(QString n)
{
    id_c=n;
}
void condidat::setNom_C(QString n)
{
    nom_c=n;
}
void condidat::setemail(QString n)
{
   email=n;
}
void condidat::setNum(QString n)
{
    num=n;
}
void condidat::setstatut_C(QString n)
{
    statut_c=n;
}

bool condidat::ajoutercondidat()
{
    QSqlQuery query;
    query.prepare("INSERT INTO CONDIDAT VALUES (:id,:nom,:num,:emaill,:statut)");
    query.bindValue(":id", id_c);
    query.bindValue(":nom",nom_c);
    query.bindValue(":num",num);
    query.bindValue(":emaill",email);
    query.bindValue(":statut",statut_c);

    if (query.exec()) {
            {qDebug() << "Employé ajouté avec succès !";
            ID = generateUniqueID();
                action = "Ajout";
                date = QDateTime::currentDateTime();
                details = QString("ID: %1, Nom: %2, Poste: %3, Salaire: %4,Email: %5")
                           .arg(id_c)
                           .arg(nom_c)
                           .arg(num)
                           .arg(email)
                           .arg(statut_c);

                History.append(*this);
                saveHistoryToFile("C:/Users/dell/Desktop/fileqt/history.json");
        }
            return true;
        } else {
            qDebug() << "Erreur lors de l'ajout de condidat : " << query.lastError().text();
            return false;
        }

}

QSqlQueryModel* condidat::afficher()
{
    QSqlQueryModel* empl=new QSqlQueryModel();

    empl->setQuery("SELECT * FROM CONDIDAT");
    empl->setHeaderData(0, Qt::Horizontal, QObject ::tr("id_c"));
    empl->setHeaderData(1, Qt::Horizontal,QObject :: tr("nom_c"));
    empl->setHeaderData(2, Qt::Horizontal, QObject ::tr("num"));
    empl->setHeaderData(3, Qt::Horizontal,QObject :: tr("email"));
    empl->setHeaderData(4, Qt::Horizontal, QObject ::tr("statut"));
    qDebug()<<"ok";
    return  empl;
}



bool condidat::supprimer(QString id)
{


QSqlQuery query;
query.prepare("SELECT nom_c, num, email, statut_c FROM CONDIDAT WHERE ID_C = :id");
query.bindValue(":id", id);

if (query.exec() && query.next()) {
    QString nom_e = query.value("nom_c").toString();
    QString poste = query.value("num").toString();
    QString salaire = query.value("email").toString();
    QString email = query.value("statut_c").toString();

    // Supprimer
    query.prepare("DELETE FROM CONDIDAT WHERE ID_C = :id");
    query.bindValue(":id", id);
    query.exec();

    // Enregistrer l'historique
    ID = generateUniqueID();
    action = "Suppression";
    date = QDateTime::currentDateTime();
    details = QString("ID: %1, Nom: %2, num: %3, email: %4, statut: %5")
               .arg(id_c)
               .arg(nom_c)
               .arg(num)
               .arg(email)
               .arg(statut_c);

    History.append(*this);
    saveHistoryToFile("C:/Users/dell/Desktop/fileqt/history.json");

    // Retourner true pour indiquer que la suppression a réussi
    return true;
}

return false;}

bool condidat::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE condidat "" SET nom_c=:nom, num=:num, email=:email, statut_c=:stat"" WHERE ID_C= :id");
    query.bindValue(":id",id_c);
    query.bindValue(":nom",nom_c);
    query.bindValue(":num",num);
    query.bindValue(":email",email);
    query.bindValue(":stat",statut_c);
    ID = generateUniqueID();
        action = "Modification";
        date = QDateTime::currentDateTime();
        details = QString("ID: %1, Nom: %2, Poste: %3, Salaire: %4,Email: %5")
                   .arg(id_c)
                   .arg(nom_c)
                   .arg(num)
                   .arg(email)
                   .arg(statut_c);

        History.append(*this);
        saveHistoryToFile("C:/Users/dell/Desktop/fileqt/history.json");
    return query.exec();
}

QSqlQueryModel* condidat::recherche(QString id)
{

    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT * FROM CONDIDAT WHERE id_c = :ID");
    query.bindValue(":ID", id);
    query.exec();

    model->setQuery(query);
    return model;
}

QSqlQueryModel* condidat::tri()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CONDIDAT ORDER BY id_c ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_c"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_c"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("num"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("statut_c"));

    return model;
}

QList<int> condidat::stat()
{
    QList<int> stat;
    QSqlQuery query;

    query.exec("SELECT COUNT(*) FROM EMPLOYE WHERE statut_c = 'En cours'");
    if (query.next()) {
        stat.append(query.value(0).toInt());
    }

    query.exec("SELECT COUNT(*) FROM EMPLOYE WHERE statut_c = 'Rejeté'");
    if (query.next()) {
        stat.append(query.value(0).toInt());
    }

    query.exec("SELECT COUNT(*) FROM employe WHERE statut_c = 'Embauché'");
    if (query.next()) {
        stat.append(query.value(0).toInt());
    }

    return stat;
}

bool condidat::saveHistoryToFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Error opening file for writing: " << file.errorString();
        return false;
    }

    QJsonArray jsonArray;
    for (const condidat &empl : History)
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
QJsonObject condidat::toJsonObject() const
{
    QJsonObject jsonObj;

    jsonObj["Id"] = id_c;
    jsonObj["Nom"] = nom_c;
    jsonObj["num"] = num;
    jsonObj["email"] = email;
    jsonObj["statut"] = statut_c;


    return jsonObj;
}

int condidat::generateUniqueID()
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
