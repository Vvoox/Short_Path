#include "sommet.h"
Sommet* Sommet::startNode = NULL;
Sommet* Sommet::endNode = NULL;

qint32 Sommet::selectedNb = 0;

Sommet::Sommet(qreal x, qreal y, qreal node_id)
{
    this->ItemX = x;
    this->ItemY = y;
    Id = node_id;
    Pressed = false;
    isMoving = false;
    Selected = false;
    colored = false;
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    this->setZValue(4);
}

QRectF Sommet::boundingRect() const
{
    return QRectF(ItemX - 25,ItemY - 25,50,50);

}

void Sommet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QPen Pen;
    QFont font;
    Pen.setWidth(3);
    Pen.setColor(QColor(72, 171, 96,255));
    painter->setPen(Pen);
    painter->setBrush(QColor(121, 230, 148, 255));

    /*
     * Manage Event
    */

    if(Pressed == true){
        painter->setBrush(Qt::blue);
    }
    if(isSelected()){
        Pen.setColor(QColor(171, 146, 38));
        painter->setPen(Pen);
        painter->setBrush(QColor(253, 216, 53));
    }
    if(colored == true && MainWindow::modify==false){
        Pen.setColor(QColor(255, 255, 255));
        painter->setPen(Pen);
        painter->setBrush(QColor(230, 63, 63));
    }
    painter->drawEllipse(rect);

    /*

      Reset startNode en desélectionnement

    */

    if(!isSelected() && Sommet::startNode == this && MainWindow::modify==true){
            Sommet::selectedNb = 0;
            Sommet::startNode = NULL;
    }

    /*
     * Control font size and color
    */

    font.setPointSize(font.pointSize() * 1.3 );
    font.setWeight(font.weight()*1.4);
    painter->setFont(font);
    Pen.setColor(QColor(21, 121, 45,255));

    if(colored == true && MainWindow::modify==false){
        Pen.setColor(QColor(255, 255,255));
    }
    painter->setPen(Pen);
    painter->drawText(rect, Qt::AlignCenter,QString::number(Id));

}

void Sommet::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   // Pressed = true;
    //update();
    //QGraphicsItem::mousePressEvent(event);
//    qInfo() << event->pos().x();
}

void Sommet::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;
    isMoving = false;
    update();

    MainWindow::test->update();
    QGraphicsItem::mouseReleaseEvent(event);

}

void Sommet::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    isMoving = true;
    update();
    QGraphicsItem::mouseMoveEvent(event);

}

QVariant Sommet::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{

    if (change == QGraphicsItem::ItemSelectedChange)
        {
            if (value == true)
            {
                // Création du graphe (modify==true)
                if(Sommet::selectedNb == 1 && Sommet::startNode != NULL && MainWindow::modify==true){
                        Arrow* arrow = new Arrow(startNode->ItemX,startNode->ItemY,this->ItemX,this->ItemY);
                        MainWindow::Sommet_arrow[startNode].push_back(arrow);
                        MainWindow::Sommet_arrow[this].push_back(arrow);
                        arrow->setZValue(3);
                        Sommet* hehe= startNode;

                        double weight = arrow->setWeight();

                        MainWindow::matrix.insert(QPair<Sommet*,Sommet*>(hehe,this),weight);


                        if(weight != M_PI){
                            MainWindow::test->addItem(arrow);
                            MainWindow::test->update();
                        }else{
                            delete arrow;
                            MainWindow::Sommet_arrow[startNode].pop_back();
                            MainWindow::Sommet_arrow[this].pop_back();
                        }

                        // After choosing a value select this node
                        this->setSelected(true);
                        Sommet::startNode = this;
                }else if(MainWindow::modify==true){
                   Sommet::selectedNb = 1;
                   Sommet::startNode = this;
                }

                if(Sommet::selectedNb == 1 && Sommet::startNode != NULL && MainWindow::modify==false){
                       Sommet::endNode = this;
                }else if(MainWindow::modify==false){
                    Sommet::selectedNb = 1;
                    Sommet::startNode = this;
                }


                update();
                MainWindow::test->update();


            }
            else
            {
                update();
                MainWindow::test->update();
            }
        }

        return QGraphicsItem::itemChange(change, value);
}

