#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/MAGARAC/Documents/untitled1/ClickChargeET.db");

    if(!mydb.open())
        ui->label_db->setText("Failed to open the database!");
    else
        ui->label_db->setText("Conected...");

    tableView_Printeri = findChild<QTableView*>("tableView_Printeri");
    comboBox_Lokacije = findChild<QComboBox*>("comboBox_Lokacije");

    QSqlQuery query("SELECT DISTINCT Lokacija FROM Printeri");
       while (query.next()) {
           QString location = query.value("Lokacija").toString();
           comboBox_Lokacije->addItem(location);
       }

    connect(comboBox_Lokacije, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_Lokacije_currentIndexChanged(int)));

    scene = new QGraphicsScene(this);
    ui->graphicsView_Printeri->setScene(scene);

    connect(ui->tableView_Printeri, SIGNAL(activated(const QModelIndex&)), this, SLOT(on_tableView_Printeri_activated(const QModelIndex&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_Lokacije_currentIndexChanged(int index)
{
    QString selectedLocation = comboBox_Lokacije->currentText();

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT * FROM Printeri WHERE Lokacija = '" + selectedLocation + "'");

    tableView_Printeri->setModel(model);
}

void MainWindow::on_tableView_Printeri_activated(const QModelIndex &index)
{
    // Fetch-a podatke iz tableviewa
    QString serijskiBroj = ui->tableView_Printeri->model()->index(index.row(), 0).data().toString();
    QString inventurniBroj = ui->tableView_Printeri->model()->index(index.row(), 1).data().toString();
    QString model = ui->tableView_Printeri->model()->index(index.row(), 2).data().toString();
    QString zaduzenaOsoba = ui->tableView_Printeri->model()->index(index.row(), 3).data().toString();

    // Brise stare podatke
    scene->clear();

    // Postavlja nove podatke
    QString imagePath = "C:\\Users\\MAGARAC\\Documents\\printeri_op\\printer.jpg";
    QImage printerImage(imagePath);
    int width = 200;
    int height = 150;
    QImage resizedImage = printerImage.scaled(width, height, Qt::KeepAspectRatio);

    QPixmap printerPixmap = QPixmap::fromImage(resizedImage);
    printerItem = new QGraphicsPixmapItem(printerPixmap);

    // Dodaje sliku
    scene->addItem(printerItem);

    float x = 1;
    float y = 1;
    float scale = 1;

    QPointF position(x * scale, y * scale);
    printerItem->setOffset(position);

    // Pravi text za pored printera
        QGraphicsTextItem *serijskiBrojText = new QGraphicsTextItem(serijskiBroj);
        QGraphicsTextItem *inventurniBrojText = new QGraphicsTextItem(inventurniBroj);
        QGraphicsTextItem *modelText = new QGraphicsTextItem(model);
        QGraphicsTextItem *zaduzenaOsobaText = new QGraphicsTextItem(zaduzenaOsoba);

        // Pozicioniranje texta pored slike
        int textSpacing = 10;
        serijskiBrojText->setPos(position.x() + printerPixmap.width() + textSpacing, position.y());
        inventurniBrojText->setPos(position.x() + printerPixmap.width() + textSpacing, position.y() + serijskiBrojText->boundingRect().height() + textSpacing);
        modelText->setPos(position.x() + printerPixmap.width() + textSpacing, position.y() + serijskiBrojText->boundingRect().height() + inventurniBrojText->boundingRect().height() + (2 * textSpacing));
        zaduzenaOsobaText->setPos(position.x() + printerPixmap.width() + textSpacing, position.y() + serijskiBrojText->boundingRect().height() + inventurniBrojText->boundingRect().height() + modelText->boundingRect().height() + (3 * textSpacing));

        scene->addItem(serijskiBrojText);
        scene->addItem(inventurniBrojText);
        scene->addItem(modelText);
        scene->addItem(zaduzenaOsobaText);
}


