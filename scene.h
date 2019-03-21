#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <sommet.h>
#include <arrow.h>
#include <QVector>
#include <QWidget>

class Sommet;
class Scene  : public QGraphicsScene
{
public:
    Scene(QObject *parent = Q_NULLPTR);
    qint32 nodes_nb;
    static QVector<Sommet*> vect_sommet;
    QVector<Sommet*> solution_vertices;
    void clearColoredVertics();
    void colorVertices(QVector<Sommet*> vertices);
    //void add_arrow(Sommet* start, Sommet* end);
protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H
