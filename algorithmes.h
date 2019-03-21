#ifndef ALGORITHMES_H
#define ALGORITHMES_H

#include "mainwindow.h"
#include <QVector>
#include <QDebug>
#include "scene.h"
class Sommet;

class Algorithmes
{
public:
    Algorithmes();
    QVector<Sommet *> dijkstra(Sommet* start, Sommet* end);
    QVector<Sommet *> bellman_kalaba(Sommet* start, Sommet* end);
    QVector<Sommet *> aStar(Sommet* start,Sommet* end);
};

#endif // ALGORITHMES_H
