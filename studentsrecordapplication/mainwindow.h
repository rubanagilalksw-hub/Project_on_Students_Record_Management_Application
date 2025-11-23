#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Student {
    QString roll;
    QString name;
    QString father;
    QString caste;
    QString district;
    QString gpa;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAdd_clicked();
    void on_btnNext_clicked();
    void on_btnUpdate_clicked();
    void on_btnDelete_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Student> records;
    int index = -1;

    void loadFile();
    void saveFile();
    void displayRecord(int i);
};

#endif // MAINWINDOW_H
