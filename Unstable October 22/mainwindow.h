#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <cstdlib>
#include <ctime>
#include <QTextStream>
#include <QDesktopServices>
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


    void on_saveRandBth_clicked();

    void on_saveBth_clicked();

    void on_myIdeasBth_clicked();

    void on_createBth_clicked();

    void on_newCatBth_clicked();

    void on_saveCatBth_clicked();

    void clearLabel();


private:
    Ui::MainWindow *ui;


    QString readFile();


};
#endif // MAINWINDOW_H
