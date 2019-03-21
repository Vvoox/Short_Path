#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMessageBox>
#include "scene.h"
#include "sommet.h"
#include "arrow.h"
#include "algorithmes.h"
#include <QMap>
#include <QVector>
#include "generator.h"

class Scene;
class Arrow;
class Sommet;
class Generator;
class Algorithmes;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    static Scene* test;
    static MainWindow* pointer;
    static QMap<Sommet*, QVector<Arrow*> > Sommet_arrow;
    static QMap<QPair<Sommet*,Sommet*>, qint64> matrix;
    static double setWeight();
    static bool modify;
    Algorithmes* Algos;
    Generator* generator;

    ~MainWindow();

private slots:
    void on_toolButton_clicked();
    void on_toolButton_2_clicked();
    void on_dijkstra_clicked();

    void on_save_clicked();

    void on_bellman_kalaba_clicked();

    void on_aStar_clicked();

    void on_random_clicked();

    void on_reset_clicked();

private:
    Ui::MainWindow *ui;
    Scene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsTextItem *text;
    Sommet *sommet;
    Arrow* arrow;
};

#endif // MAINWINDOW_H
