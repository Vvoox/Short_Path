#include "generator.h"
#include "ui_generator.h"

Generator::Generator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Generator)
{
    ui->setupUi(this);
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    scene = MainWindow::test;
}

void Generator::generateGraph(qint32 maxX,qint32 maxY)
{
    qint32 verticesNb = ui->verticesNb->value();
    qint32 density = ui->density->value();
    qint32 arrowsNb = density*verticesNb*(verticesNb-1)/200;
    qint32 vertexX,vertexY,randVertexA,randVertexB;
    QVector<Sommet *>& vect_sommet = Scene::vect_sommet;
    QMap<QPair<Sommet*,Sommet*>, qint64>& matrix = MainWindow::matrix;


    /*
    *
    * Clear Matrix and Vect_sommet for new generation
    *
    */

    vect_sommet.clear(); matrix.clear();
    Sommet::endNode = NULL;Sommet::startNode = NULL;


    for(qint32 i=0;i<verticesNb;i++){
        vertexX = qrand() % (maxX-120) + 30 ;
        vertexY = -(qrand() % (maxY-100)) + 100;
        sommet = new Sommet(vertexX,vertexY,i+1);
        scene->addItem(sommet);
        vect_sommet.push_back(sommet);
    }

    for(qint32 i=0;i<arrowsNb;i++){
        randVertexA = qrand()%verticesNb;
        randVertexB = qrand()%verticesNb;
        if(randVertexA == randVertexB || matrix.find(QPair<Sommet*,Sommet*>(vect_sommet.at(randVertexA),vect_sommet.at(randVertexB))) != matrix.end()){
                i--;
                continue;
        }

        if(matrix.find(QPair<Sommet*,Sommet*>(vect_sommet.at(randVertexB),vect_sommet.at(randVertexA))) != matrix.end()){
            i--;
            continue;
        }

        Arrow* arrow = new Arrow(vect_sommet.at(randVertexA)->ItemX,vect_sommet.at(randVertexA)->ItemY,vect_sommet.at(randVertexB)->ItemX,vect_sommet.at(randVertexB)->ItemY);
        scene->addItem(arrow);

        arrow->weight = qrand()%100 + 1;

        matrix.insert(QPair<Sommet*,Sommet*>(vect_sommet.at(randVertexA),vect_sommet.at(randVertexB)),arrow->weight);

    }



}

qint32 Generator::getVerticesNb()
{
    return ui->verticesNb->value();
}

qint32 Generator::getDensity()
{
    return ui->density->value();
}

Generator::~Generator()
{
    delete ui;
}
