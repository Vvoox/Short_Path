#ifndef GENERATOR_H
#define GENERATOR_H

#include "mainwindow.h"
#include <QDialog>
#include <QDebug>
#include "sommet.h"
#include "arrow.h"
#include "scene.h"

class Sommet;
class Scene;
namespace Ui {
class Generator;
}

class Generator : public QDialog
{
    Q_OBJECT

public:
    explicit Generator(QWidget *parent = 0);
    void generateGraph(qint32 maxX,qint32 maxY);
    qint32 getVerticesNb();
    qint32 getDensity();
    Scene* scene;
    Sommet* sommet;
    ~Generator();

private:
    Ui::Generator *ui;
};

#endif // GENERATOR_H
