#include "arrow.h"

Arrow::Arrow(qreal startX, qreal startY,qreal endX,qreal endY)
{
    start_point_x = startX;
    start_point_y = startY;
    end_point_x = endX;
    end_point_y = endY;
    weight = M_PI;
    //setFlag(ItemIsMovable);
}

QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + 30) / 2.0;

       return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                         line().p2().y() - line().p1().y()))
           .normalized()
           .adjusted(-extra, -extra, extra, extra);
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QLineF line,line2;
    QPen Pen;
    Pen.setWidth(2);
    Pen.setBrush(Qt::white);
    line.setLine(start_point_x,start_point_y,end_point_x,end_point_y);
    double angle = std::atan2(-line.dy(), line.dx());
    double center = sqrt(pow(end_point_x-start_point_x,2)+pow(end_point_y-start_point_y,2))/2;
    line2.setLine(start_point_x + 27*cos(angle),start_point_y-27*sin(angle),end_point_x - 38*cos(angle),end_point_y+38*sin(angle));
    painter->setPen(Pen);
    painter->drawLine(line2);

    qreal arrowSize = 38;
    qreal addAngel = M_PI/13;


    if(weight != M_PI){
        painter->drawText(start_point_x + center*cos(angle+0.08),start_point_y-center*sin(angle+0.08),QString::number(weight));
    }

    QPointF arrowP0 = line.p2() - QPointF(27*cos(angle),-27*sin(angle));
    QPointF arrowP1 = line.p2() - QPointF(cos(angle + addAngel) * arrowSize,
                                    -sin(angle + addAngel) * arrowSize);
    QPointF arrowP2 = line.p2() - QPointF(cos(angle - addAngel) * arrowSize,
                                    -sin(angle - addAngel) * arrowSize);

    arrowHead << arrowP0 << arrowP1 << arrowP2;

    painter->setPen(Qt::white);
    painter->drawPolygon(arrowHead);
}

double Arrow::setWeight()
{
    QInputDialog* getweight= new QInputDialog();
    getweight->setFixedSize(300,400);
    getweight->setContentsMargins(5,5,5,5);
    getweight->setInputMode(QInputDialog::IntInput);
    getweight->setIntMinimum(INT_MIN);
    if(getweight->exec()){
        weight = getweight->intValue();
        return getweight->intValue();
    }else{
        return M_PI;
    }
}

