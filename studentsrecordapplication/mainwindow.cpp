#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadFile();

    ui->btnUpdate->setEnabled(false);
    ui->btnDelete->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile()
{
    QFile file("students.txt");
    if(!file.open(QIODevice::ReadOnly))
        return;

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList p = line.split(",");

        if(p.size() == 6) {
            Student s;
            s.roll = p[0];
            s.name = p[1];
            s.father = p[2];
            s.caste = p[3];
            s.district = p[4];
            s.gpa = p[5];
            records.append(s);
        }
    }

    file.close();
}

void MainWindow::saveFile()
{
    QFile file("students.txt");
    file.open(QIODevice::WriteOnly);

    QTextStream out(&file);
    for(const Student &s : records) {
        out << s.roll << "," << s.name << "," << s.father << ","
            << s.caste << "," << s.district << "," << s.gpa << "\n";
    }

    file.close();
}

void MainWindow::displayRecord(int i)
{
    ui->txtRoll->setText(records[i].roll);
    ui->txtName->setText(records[i].name);
    ui->txtFather->setText(records[i].father);
    ui->txtCaste->setText(records[i].caste);
    ui->txtDistrict->setText(records[i].district);
    ui->txtGPA->setText(records[i].gpa);
}

// -------------------- ADD --------------------
void MainWindow::on_btnAdd_clicked()
{
    Student s;
    s.roll = ui->txtRoll->text();
    s.name = ui->txtName->text();
    s.father = ui->txtFather->text();
    s.caste = ui->txtCaste->text();
    s.district = ui->txtDistrict->text();
    s.gpa = ui->txtGPA->text();

    records.append(s);
    saveFile();

    QMessageBox::information(this, "Saved", "Record Added Successfully!");
}

// -------------------- NEXT --------------------
void MainWindow::on_btnNext_clicked()
{
    if(records.isEmpty()) return;

    if(index < records.size() - 1)
        index++;

    displayRecord(index);

    ui->btnAdd->setEnabled(false);
    ui->btnUpdate->setEnabled(true);
    ui->btnDelete->setEnabled(true);
}

// -------------------- UPDATE --------------------
void MainWindow::on_btnUpdate_clicked()
{
    if(index < 0) return;

    records[index].roll = ui->txtRoll->text();
    records[index].name = ui->txtName->text();
    records[index].father = ui->txtFather->text();
    records[index].caste = ui->txtCaste->text();
    records[index].district = ui->txtDistrict->text();
    records[index].gpa = ui->txtGPA->text();

    saveFile();

    QMessageBox::information(this, "Updated", "Record Updated Successfully!");
}

// -------------------- DELETE --------------------
void MainWindow::on_btnDelete_clicked()
{
    if(index < 0) return;

    records.removeAt(index);
    saveFile();

    QMessageBox::information(this, "Deleted", "Record Deleted Successfully!");

    index = -1;

    ui->btnAdd->setEnabled(true);
    ui->btnUpdate->setEnabled(false);
    ui->btnDelete->setEnabled(false);

    ui->txtName->clear();
    ui->txtRoll->clear();
    ui->txtFather->clear();
    ui->txtCaste->clear();
    ui->txtDistrict->clear();
    ui->txtGPA->clear();
}


