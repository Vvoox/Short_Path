#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>

MainWindow* MainWindow::pointer;
bool MainWindow::modify = true;
QMap<QPair<Sommet*,Sommet*>, qint64> MainWindow::matrix;

Scene* MainWindow::test = NULL;
QMap<Sommet*, QVector<Arrow*> > MainWindow::Sommet_arrow;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    MainWindow::pointer = this;
    // Display the window
        ui->setupUi(this);
        QMainWindow::showMaximized();
        setWindowIcon(QIcon(":/imgs/icon.png"));
    // Setup the scene
        scene = new Scene(this);
        MainWindow::test = scene;
        ui->graphicsView->setScene(scene);
        ui->graphicsView->setBackgroundBrush(QBrush(QColor(44, 62, 80,255), Qt::SolidPattern));
        ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // Create Item to init scene
        sommet = new Sommet(0,0,0);
        scene->addItem(sommet);
        sommet->hide();

    //
        Algos = new Algorithmes();
        generator = new Generator();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_clicked()
{
    QMessageBox msgBox;
    if(Sommet::startNode == NULL){
        msgBox.setText("Veuillez selectionner un sommet.");
        msgBox.exec();
    }else{

        for (int i = 0; i < MainWindow::Sommet_arrow[Sommet::startNode].size(); ++i) {
            scene->removeItem(MainWindow::Sommet_arrow[Sommet::startNode].at(i));
        //    delete MainWindow::Sommet_arrow[Sommet::startNode].at(i);
        }

        scene->removeItem(Sommet::startNode);
        Sommet::startNode = NULL;
        Sommet::selectedNb = 0;
        scene->update();
    }
}

void MainWindow::on_toolButton_2_clicked()
{

    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Nouveau fichier", "Êtes-vous sûr de vouloir continuer? \nTous vos modifications non enregistrés seront perdus",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
          scene->clear();
          scene->update();
      } else {
        qDebug() << "Yes was *not* clicked";
      }

    MainWindow::matrix.clear();
    Scene::vect_sommet.clear();
}

void MainWindow::on_save_clicked()
{
    MainWindow::modify = !MainWindow::modify;
    Sommet::startNode = NULL;
    Sommet::endNode = NULL;
    Sommet::selectedNb = 0;
}

void MainWindow::on_dijkstra_clicked()
{

    if(MainWindow::modify==true){
        QMessageBox::warning(this,QString("Generateur de graphes"),QString("Veuillez sauvegader votre graphe !"));
        return;
    }

    if(Sommet::startNode == NULL || Sommet::endNode == NULL){
        QMessageBox::warning(this,QString("Generateur de graphes"),QString("Veuillez sélectionner un point de départ et un point d'arrivée !"));
        return;
    }


    scene->colorVertices(Algos->dijkstra(Sommet::startNode,Sommet::endNode));

}

void MainWindow::on_bellman_kalaba_clicked()
{
    if(MainWindow::modify==true){
        QMessageBox::warning(this,QString("Generateur de graphes"),QString("Veuillez sauvegader votre graphe !"));
        return;
    }

    if(Sommet::startNode == NULL || Sommet::endNode == NULL){
        QMessageBox::warning(this,QString("Generateur de graphes"),QString("Veuillez sélectionner un point de départ et un point d'arrivée !"));
        return;
    }

    scene->colorVertices(Algos->bellman_kalaba(Sommet::startNode,Sommet::endNode));

}

void MainWindow::on_aStar_clicked()
{
    if(MainWindow::modify==true){
        QMessageBox::warning(this,QString("Generateur de graphes"),QString("Veuillez sauvegader votre graphe !"));
        return;
    }

    if(Sommet::startNode == NULL || Sommet::endNode == NULL){
        QMessageBox::warning(this,QString("Generateur de graphes"),QString("Veuillez sélectionner un point de départ et un point d'arrivée !"));
        return;
    }

    scene->colorVertices(Algos->aStar(Sommet::startNode,Sommet::endNode));


}

void MainWindow::on_random_clicked()
{
    if(generator->exec()){
        scene->clear();
        generator->generateGraph(ui->graphicsView->rect().right(),ui->graphicsView->rect().bottom());
    }
    return;
}

void MainWindow::on_reset_clicked()
{
    Sommet::startNode = NULL;
    Sommet::endNode = NULL;
    Sommet::selectedNb = 0;
    for(int i=0;i<Scene::vect_sommet.size();i++){
        Scene::vect_sommet.at(i)->colored = false;
    }
    scene->update();

}
