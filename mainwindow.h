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
    void on_btnScan_clicked();

    void on_btnScanOpened_clicked();

    void on_btnScanClosed_clicked();

    int CalculateTimeout(int startPort, int endPort);

    void on_btnSave_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
