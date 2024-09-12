#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "condidat.h"
#include "offre.h"
#include <QMessageBox>
#include <QtCharts/QtCharts>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QHBoxLayout>
#include <QtCharts/QLegend>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->errornom_9->setVisible(false);
    ui->errornom_15->setVisible(false);
    ui->errornom_10->setVisible(false);
    ui->errornom_11->setVisible(false);
    ui->errornom_14->setVisible(false);
    ui->errornom_12->setVisible(false);
    ui->errornom_16->setVisible(false);
    ui->errornom_13->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool validateDigits(const QString &input) {
    QRegExp regExp("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}");
    return regExp.exactMatch(input);
}
bool validateDigits_contact(const QString &input) {
    QRegularExpression regex("^\\d{8,}$");
    return regex.match(input).hasMatch();
}
bool isIdValid(const QString& id) {
    if (id.length() != 2) {
        return false;
    }
    for (const QChar& digit : id) {
        if (!digit.isDigit()) {
            return false;
        }
    }
    return true;
}
void MainWindow::on_pushButton_20_clicked()
{
    qDebug()<<"Echec d'ajout";

    QString id=ui->a->text();
    QString nom=ui->b->text();
    QString statut=ui->comboBox_4->currentText();
    QString email=ui->le_mail_2->text();
    QString num=ui->le_salaire_2->text();


    QMessageBox Message;
    if(id.size()>0 && isIdValid(id) && nom.size()>0 && statut.size()>0  && email.size()>0 && num.size()>0 && validateDigits(email))
    {
    condidat p(id,nom,num,email,statut);
    if(p.ajoutercondidat())
    {
        ui->tab_4->setModel(p.afficher());
        Message.setText("Ajout avec succes");
    }
    else
        qDebug()<<"Echec d'ajout";
    }
    if(id.size()==0) {ui->errornom_10->setVisible(true);ui->errornom_15->setVisible(false);}
    else ui->errornom_10->setVisible(false);
    if(nom.size()==0) ui->errornom_9->setVisible(true);
    else ui->errornom_9->setVisible(false);
    if(statut.size()==0) ui->errornom_11->setVisible(true);
    else ui->errornom_11->setVisible(false);
    if(num.size()==0) {ui->errornom_13->setVisible(true);ui->errornom_16->setVisible(false);}
    else ui->errornom_13->setVisible(false);
    if(email.size()==0) {ui->errornom_12->setVisible(true); ui->errornom_14->setVisible(false);}
    else ui->errornom_12->setVisible(false);
    if(!validateDigits_contact(num)) {ui->errornom_16->setVisible(true);ui->errornom_13->setVisible(false);}
    else ui->errornom_16->setVisible(false);
    if(!isIdValid(id)) {ui->errornom_15->setVisible(true);ui->errornom_10->setVisible(false);}
    else ui->errornom_15->setVisible(false);
    if(!validateDigits(email)) {ui->errornom_14->setVisible(true);ui->errornom_12->setVisible(false);}
    else ui->errornom_14->setVisible(false);
    Message.exec();
}

void MainWindow::on_pushButton_41_clicked()
{
        condidat e1;
        e1.setID_C(ui->le_id_9->text());

       /* if (e1.estDejaSupprime(e1.getID_C())) {
            QMessageBox::information(this, "Suppression", "Ce condidat est déjà supprimé.");
            return;
        }*/

        bool test = e1.supprimer(e1.getID_C());
        QMessageBox msgBox;
        if (test) {
            msgBox.setText("Suppression avec succès");
        } else {
            msgBox.setText("Échec de la suppression.");
        }
        msgBox.exec();
}

void MainWindow::on_pushButton_34_clicked()
{
    QString id=ui->le_id_8->text();
    QString nom=ui->le_nom_6->text();
    QString statut=ui->comboBox_5->currentText();
    QString email=ui->le_email_5->text();
    QString num=ui->le_salaire_5->text();
    QMessageBox Qmsg;

    if(id.size()>0 && isIdValid(id) && nom.size()>0 && statut.size()>0  && email.size()>0 && num.size()>0 && validateDigits(email))
    {
        condidat E(id,nom,num,email,statut);
    bool test=E.modifier();
    if(test)
    {
        Qmsg.setText("Modification fait avec succes ");
        qDebug()<<"jawek behi";
        ui->tab_4->setModel((E.afficher()));
        if (E.saveHistoryToFile("C:/Users/dell/Desktop/fileqt/history.json")) {
                    qDebug() << "Historique enregistré avec succès dans un fichier JSON.";
                } else {
                    qDebug() << "Erreur lors de l'enregistrement de l'historique dans un fichier JSON.";
                }

                // Convertir l'employé en objet JSON et afficher les détails dans la console
                QJsonObject jsonObject = E.toJsonObject();
                qDebug() << "Objet JSON de l'employé après modification:" << jsonObject;
    }
    else
        Qmsg.setText("Erreur lors de la modification ");
    }
    Qmsg.exec();
}



void MainWindow::on_tab_4_clicked(const QModelIndex &index)
{
    int row=index.row();
    QModelIndex sibling=index.sibling(row,0);
    QString id_e=ui->tab_4->model()->data(sibling).toString();

    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE id_e= :id");
    query.bindValue(":id",id_e);

    if(query.exec())
    {
        while(query.next())
        {
            ui->le_id_8->setText(query.value(0).toString());
            ui->le_nom_6->setText(query.value(1).toString());
            ui->comboBox_5->setCurrentText(query.value(2).toString());
            ui->le_email_5->setText(query.value(4).toString());
            ui->le_salaire_5->setText(query.value(3).toString());
            ui->le_id_9->setText(query.value(0).toString());
        }
    }
    //generer code QR
    QString text ="partenaire details :"+ ui->tab_4->model()->data(ui->tab_4->model()->index(ui->tab_4->currentIndex().row(),1)).toString()
            +" "+ui->tab_4->model()->data(ui->tab_4->model()->index(ui->tab_4->currentIndex().row(),2)).toString()
            +" "+ui->tab_4->model()->data(ui->tab_4->model()->index(ui->tab_4->currentIndex().row(),3)).toString()
            +" "+ui->tab_4->model()->data(ui->tab_4->model()->index(ui->tab_4->currentIndex().row(),4)).toString();
               +" "+ui->tab_4->model()->data(ui->tab_4->model()->index(ui->tab_4->currentIndex().row(),5)).toString();
               +" "+ui->tab_4->model()->data(ui->tab_4->model()->index(ui->tab_4->currentIndex().row(),6)).toString();
 using namespace qrcodegen;
      // Create the QR Code object
      QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );
      qint32 sz = qr.getSize();
      QImage im(sz,sz, QImage::Format_RGB32);
        QRgb black = qRgb(  0,  0,  0);
        QRgb white = qRgb(255,255,255);
      for (int y = 0; y < sz; y++)
        for (int x = 0; x < sz; x++)
          im.setPixel(x,y,qr.getModule(x, y) ? black : white );
      ui->qrCodeLabel->setPixmap( QPixmap::fromImage(im.scaled(ui->qrCodeLabel->width(),ui->qrCodeLabel->height(),Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );

}

void MainWindow::on_pushButton_43_clicked()
{
    condidat P;
        QString id = ui->le_id_10->text();

          QSqlQueryModel* res = P.recherche(id);

          if (res->rowCount() > 0) {
              ui->tab_rech_3->setModel(res);

          } else {
              QMessageBox::information(nullptr, QObject::tr("Recherche"),
                                       QObject::tr("Aucun résultat trouvé pour cet ID."), QMessageBox::Ok);
          }
}

void MainWindow::on_pushButton_39_clicked()
{
    condidat p;
    ui->tab_4->setModel(p.tri());
}

/*void MainWindow::on_pushButton_40_clicked()
{
    QString strStream;
       QTextStream out(&strStream);
       QDate currentDate = QDate::currentDate();
       QString date = currentDate.toString("dd-MM-yyyy");


       const int rowCount = ui->tab_4->model()->rowCount();
       const int columnCount = ui->tab_4->model()->columnCount();

       out <<  "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           <<  QString("<title>%1</title>\n").arg("col1")
           <<  "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<h3 style='position: absolute; top: 0; right: 0; margin: 0; padding: 10px; text-align: right; font-size: 24px; color: #333;'> Tunis "+date+"</h3>"
           "<h1 style='text-align: center;'>Liste des partenaires</h1>\n"
           "<br>\n"
           "<br>\n"
           "<table border=1 cellspacing=0 cellpadding=2>\n";

       // headers
       out << "<thead><tr bgcolor=#f0f0f0>";
       for (int column = 0; column < columnCount; column++)
           if (!ui->tab_4->isColumnHidden(column))
               out << QString("<th>%3</th>").arg(ui->tab_4->model()->headerData(column, Qt::Horizontal).toString());
       out << "</tr></thead>\n";

       // data table
       for (int row = 0; row < rowCount; row++) {
           out << "<tr>";
           for (int column = 0; column < columnCount; column++) {
               if (!ui->tab_4->isColumnHidden(column)) {
                   QString data = ui->tab_4->model()->data(ui->tab_4->model()->index(row, column)).toString().simplified();
                   out << QString("<td bkcolor=0>%3</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
               }
           }
           out << "</tr>\n";
       }
       out <<  "</table>\n"
           "</body>\n"
           "</html>\n";

       QTextDocument *document = new QTextDocument();
       document->setHtml(strStream);

       QPrinter printer;

           document->print(&printer);


       delete document;
}*/
