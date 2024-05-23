#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rabin.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonEncode_clicked();

    void on_openFileButton_clicked();

    void on_pushButtonDecode_clicked();

private:
    Ui::MainWindow *ui;
    rb::Rabin rabi;
    QString FileName;
};

#endif // MAINWINDOW_H
