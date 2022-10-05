#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowIcon(QIcon("aqua.ico"));

    QMessageBox::information(this, "Aqua Notebook", "Chose your category.");
    ui->setupUi(this);

    QStringList items;

    QFile *readcats = new QFile("combobox.ini");
    readcats->open(QFile::ReadOnly);

    QTextStream textStream(readcats);
    while (true)
    {
        QString line = textStream.readLine();
        if (line.isNull())
            break;
        else
            items.append(line);
    }
    readcats->close();

    ui->comboBox->addItems(items);//Записываем в комбобокс значения элементов из листа

    ui->newCatPoint->setVisible(false);
    ui->saveCatBth->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::readFile(){
    QString fileName = ui->comboBox->currentText();//Получаем название категории из комбобокса

    if(fileName == "Non-category"){
        QFile *nonCatFile = new QFile("ncideas.db");
        nonCatFile->open(QFile::ReadOnly | QIODevice::Text);
        ui->textEdit_2->setText(nonCatFile->readAll());
        nonCatFile->close();

    }
    else{

     QFile *readIdea = new QFile(fileName + ".db");
     readIdea->open(QFile::ReadOnly | QIODevice::Text);
     if(readIdea->isOpen()){
         QString data = readIdea->readAll();

         return data;
     }
     else{
         QMessageBox::warning(this, "Aqua Notebook", "Error 3. File not found.");
     }
     readIdea->close();
     delete readIdea;
    }
}
void MainWindow::on_saveRandBth_clicked()
{
    QFile *randIdeaFile = new QFile("ncideas.db");// нон-категория идея

    qint64 sizeOldFile, sizeAppenedFile;// Переменные для проверки записи в файл
    sizeOldFile = randIdeaFile->size();

    randIdeaFile->open(QFile::Append|QIODevice::Text);
    randIdeaFile->write(ui->textEdit->toPlainText().toUtf8());
    randIdeaFile->close();

    sizeAppenedFile = randIdeaFile->size();

    if(sizeAppenedFile > sizeOldFile){ // Если размер файла увеличился
        QMessageBox::information(this, "Aqua Notebook", "Saved!");
        ui->textEdit->clear();
    }
    else{
        QMessageBox::warning(this, "Aqua Notebook", "Error 1. Not saved.");
    }

    delete randIdeaFile;

}


void MainWindow::on_saveBth_clicked()
{
    QString fileName = ui->comboBox->currentText();//Получаем название категории из комбобокса

    if(fileName == "Non-category"){
        on_saveBth_clicked();
    }
    else {

        QFile *catIdeaFile = new QFile(fileName +".db"); // Берем название категории из списка

        qint64 sizeOldFile, sizeAppenedFile;// Переменные для проверки записи в файл
        sizeOldFile = catIdeaFile->size();

        catIdeaFile->open(QFile::Append | QIODevice::Text);
        catIdeaFile->write(ui->textEdit->toPlainText().toUtf8());
        catIdeaFile->close();

        sizeAppenedFile = catIdeaFile->size();

        if(sizeAppenedFile > sizeOldFile){ // Если размер файла увеличился
            QMessageBox::information(this, "Plans", "Saved!");
            ui->textEdit->clear();
        }
        else{
            QMessageBox::warning(this, "Aqua Notebook", "Error 2. Not saved category-file.");
        }

        delete catIdeaFile;
    }
}


void MainWindow::on_myIdeasBth_clicked()
{

    ui->textEdit_2->setText(readFile());
    connect(ui->myIdeasBth, &QPushButton::clicked, this, &MainWindow::clearLabel);

}

void MainWindow::clearLabel(){
    ui->textEdit_2->setText(" ");
    connect(ui->myIdeasBth, &QPushButton::clicked, this, &MainWindow::on_myIdeasBth_clicked);
}
void MainWindow::on_createBth_clicked()
{
    QDesktopServices::openUrl(QUrl("https://ru.pinterest.com/"));
}



void MainWindow::on_newCatBth_clicked()
{
    ui->newCatPoint->setVisible(true);//Включим видимость кнопок
    ui->saveCatBth->setVisible(true);
}


void MainWindow::on_saveCatBth_clicked()
{
    ui->comboBox->addItem(ui->newCatPoint->text());

    QFile *categFileCombo = new QFile("combobox.ini");
    categFileCombo->open(QFile::WriteOnly | QIODevice::Append);

    if(categFileCombo->isOpen()){

        categFileCombo->write(ui->newCatPoint->text().toUtf8() + "\n");
        categFileCombo->close();

        QMessageBox::information(this, "Aqua Notebook",ui->newCatPoint->text().toUtf8() + " saved!" );
    }
    else{
        QMessageBox::warning(this, "Aqua Notebook", "Error 1. Not saved category");
    }

    ui->newCatPoint->setVisible(false);//Выключим видимость кнопок
    ui->saveCatBth->setVisible(false);

    delete  categFileCombo;
}



