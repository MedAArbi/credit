#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_20_clicked();

    void on_pushButton_41_clicked();

    void on_pushButton_34_clicked();

    void on_tab_4_clicked(const QModelIndex &index);

    void on_pushButton_43_clicked();

    void on_pushButton_39_clicked();

    void on_pushButton_40_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
