#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtSql>
#include<QDebug>
#include<QFileInfo>
#include<QSqlQuery>
#include<QMessageBox>
#include<QSqlError>
#include<QDate>
#include<QDebug>
#include <QTableView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include<QMouseEvent>

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
   void on_comboBox_Lokacije_currentIndexChanged(int index);
   void on_tableView_Printeri_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QTableView *tableView_Printeri;
    QComboBox *comboBox_Lokacije;
    QGraphicsScene *scene;
    QGraphicsPixmapItem* printerItem;
    bool isDragging;
    QGraphicsView *graphicsView_Printeri;

};

#endif // MAINWINDOW_H
