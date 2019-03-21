#ifndef SOMMET_H
#define SOMMET_H
#include <mainwindow.h>
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "scene.h"
#include "arrow.h"

class Sommet : public QGraphicsItem
{
public:
    Sommet(qreal x,qreal y, qreal node_id);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    bool Pressed;
    bool isMoving;
    bool Selected;
    bool colored;
    qreal ItemX;
    qreal ItemY;
    qreal Id;


    static Sommet* startNode;
    static Sommet* endNode;
    static qint32 selectedNb;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

};

#endif // SOMMET_H
