#ifndef ARROW_H
#define ARROW_H
#include <Qpainter>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>

//class Sommet;
class Arrow : public QGraphicsLineItem
{
public:
    Arrow(qreal startX, qreal startY,qreal endX,qreal endY);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    double setWeight();


    qreal start_point_x;
    qreal start_point_y;
    qreal end_point_x;
    qreal end_point_y;
    qreal weight;
private:
    QPolygonF arrowHead;

};

#endif // ARROW_H
