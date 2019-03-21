#include "scene.h"
#include <QThread>

QVector<Sommet*> Scene::vect_sommet;

Scene::Scene(QObject *parent): QGraphicsScene(parent)
{
    nodes_nb = 0;
}

void Scene::clearColoredVertics()
{
    for(int i=0;i<solution_vertices.size();i++){
        solution_vertices.at(i)->colored = false;
    }
}

void Scene::colorVertices(QVector<Sommet*> vertices)
{
    clearColoredVertics();

    for(int i=0;i<vertices.size();i++){
        vertices.at(i)->colored = true;
    }
    this->update();

    solution_vertices = vertices;
}


void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
        Sommet::selectedNb = 0;
        Sommet::startNode = NULL;
    //    qInfo() << event->scenePos();
        QPointF point = event->scenePos();
    //   qInfo() << point.x();
        Sommet* sommet = new Sommet(point.x(),point.y(),++nodes_nb);
        Scene::vect_sommet.append(sommet);
        //sommet->setZValue(3);
        this->addItem(sommet);
        this->update();
}
