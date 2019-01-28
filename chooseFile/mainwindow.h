#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonInput_clicked();

    void on_pushButtonOutput_clicked();
private:
    QFileInfoList getFileList(QString path);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
