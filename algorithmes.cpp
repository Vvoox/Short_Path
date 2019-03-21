#include "algorithmes.h"

Algorithmes::Algorithmes()
{

}

QVector<Sommet *> Algorithmes::dijkstra(Sommet* start,Sommet* end)
{
    QVector<Sommet *> vect_sommet = Scene::vect_sommet;
    QMap<QPair<Sommet*,Sommet*>, qint64> matrix = MainWindow::matrix;

    // sPath is the shortest path found by dijkstra
    QVector<Sommet *> sPath;
    // dmin is the shortest distance from src to Sommet*
    QMap<Sommet*,qint64> dmin;
    // pred is the previous vertex
    QMap<Sommet*,Sommet*> pred;
    // check if Sommet* is in the spt
    QMap<Sommet*,bool> sVisite;

    for(int i=0;i<vect_sommet.size();i++){
        pred[vect_sommet.at(i)] = NULL;
        dmin[vect_sommet.at(i)] = INT32_MAX;
        sVisite[vect_sommet.at(i)] = false;
    }

    for(int i=0;i<vect_sommet.size();i++){
        if(matrix.find(QPair<Sommet*,Sommet*>(start,vect_sommet.at(i))) != matrix.end()){
            dmin[vect_sommet.at(i)] = matrix[QPair<Sommet*,Sommet*>(start,vect_sommet.at(i))];
            pred[vect_sommet.at(i)] = start;
        }
    }

    dmin[start] = 0;
    sVisite[start] = true;
    pred[start] = start;

    Sommet* current = start;
    for(int i=0;i<vect_sommet.size()-1;i++){
        int mind = INT32_MAX;


        for(int j=0;j<vect_sommet.size();j++){
            if(!sVisite[vect_sommet.at(j)] && dmin[vect_sommet.at(j)]<mind){
                current = vect_sommet.at(j);
                mind = dmin[vect_sommet.at(j)];
            }
        }

        sVisite[current] = true;

        for(int j=0;j<vect_sommet.size();j++){
            if(!sVisite[vect_sommet.at(j)]){
                if(matrix.find(QPair<Sommet*,Sommet*>(current,vect_sommet.at(j))) != matrix.end()){
                    if(matrix[QPair<Sommet*,Sommet*>(current,vect_sommet.at(j))] + mind<dmin[vect_sommet.at(j)]){
                        dmin[vect_sommet.at(j)] = matrix[QPair<Sommet*,Sommet*>(current,vect_sommet.at(j))] + mind;
                        pred[vect_sommet.at(j)] = current;
                    }
                }
            }
        }

    }


    sPath.push_front(end);


    while(pred[end] != start){
        sPath.prepend(pred[end]);
        end = pred[end];
    }

    sPath.push_front(start);

    for(int i=0;i<sPath.size();i++){
        qInfo()<< sPath.at(i)->Id;
    }




    return sPath;
}

QVector<Sommet *> Algorithmes::bellman_kalaba(Sommet *start, Sommet *end)
{
    QVector<Sommet *> vect_sommet = Scene::vect_sommet;
    QMap<QPair<Sommet*,Sommet*>, qint64> matrix = MainWindow::matrix;

    // sPath is the shortest path found by dijkstra
    QVector<Sommet *> sPath;
    // dmin is the shortest distance from src to Sommet*
    QMap<Sommet*,qint64> dmin;
    // pred is the previous vertex
    QMap<Sommet*,Sommet*> pred;


    for(int i=0;i<vect_sommet.size();i++){
        pred[vect_sommet.at(i)] = NULL;
        dmin[vect_sommet.at(i)] = INT32_MAX;
    }

    for(int i=0;i<vect_sommet.size();i++){
        if(matrix.find(QPair<Sommet*,Sommet*>(start,vect_sommet.at(i))) != matrix.end()){
            dmin[vect_sommet.at(i)] = matrix[QPair<Sommet*,Sommet*>(start,vect_sommet.at(i))];
            pred[vect_sommet.at(i)] = start;
        }
    }

    dmin[start] = 0;
    pred[start] = start;


    for(int i= 0;i<vect_sommet.size()-1;i++){


        for(int j=0;j<vect_sommet.size();j++){
            if(vect_sommet.at(j) == start) continue;

            qint64 mind = INT32_MAX;
            Sommet* tmp_pred = NULL;


            for(int k=0;k<vect_sommet.size();k++){
                if(matrix.find(QPair<Sommet*,Sommet*>(vect_sommet.at(k),vect_sommet.at(j))) != matrix.end()){
                    if(dmin[vect_sommet.at(k)]+matrix[QPair<Sommet*,Sommet*>(vect_sommet.at(k),vect_sommet.at(j))]<mind){
                        mind = dmin[vect_sommet.at(k)]+matrix[QPair<Sommet*,Sommet*>(vect_sommet.at(k),vect_sommet.at(j))];
                        tmp_pred = vect_sommet.at(k);
                    }

                }
            }
            dmin[vect_sommet.at(j)] = mind;
            pred[vect_sommet.at(j)] = tmp_pred;

        }

    }



    sPath.prepend(end);

    while(pred[end] != start){
        sPath.prepend(pred[end]);
        end = pred[end];
    }

    sPath.push_front(start);

    for(int i=0;i<sPath.size();i++){
        qInfo()<< sPath.at(i)->Id;
    }

    return sPath;

}

QVector<Sommet *> Algorithmes::aStar(Sommet *start, Sommet *end)
{
    QVector<Sommet *> vect_sommet = Scene::vect_sommet;
    QMap<QPair<Sommet*,Sommet*>, qint64> matrix = MainWindow::matrix;

    // sPath is the shortest path found by dijkstra
    QVector<Sommet *> sPath;
    // dmin is the shortest distance from src to Sommet*
    QMap<Sommet*,qint64> dmin;
    // pred is the previous vertex
    QMap<Sommet*,Sommet*> pred;

//    QMap<Sommet*,bool> sVisite;
//    double distance;

    Sommet* current = start;
    pred[start] = start;
    dmin[start] = 0;

    QVector<Sommet*> voisins;

    while(current != end){

        for(int i=0;i<vect_sommet.size();i++){
            if(matrix.find(QPair<Sommet*,Sommet*>(current,vect_sommet.at(i))) != matrix.end()){
                distance = sqrt(pow(vect_sommet.at(i)->ItemX-current->ItemX,2)+pow(vect_sommet.at(i)->ItemY-current->ItemY,2));
                dmin[vect_sommet.at(i)] = matrix[QPair<Sommet*,Sommet*>(current,vect_sommet.at(i))] + distance;
                pred[vect_sommet.at(i)] = current;
                voisins.push_back(vect_sommet.at(i));
            }
        }

        qint64 mind = INT_MAX;
        int current_index = 0;

        for(int i=0;i<voisins.size();i++){
            if(dmin[voisins.at(i)]<mind){
                mind = dmin[voisins.at(i)];
                current = voisins.at(i);
                current_index = i;
            }
        }

        voisins.remove(current_index);

    }

    sPath.prepend(end);

    while(pred[end] != start){
        sPath.prepend(pred[end]);
        end = pred[end];
    }

    sPath.push_front(start);

//    for(int i=0;i<sPath.size();i++){
//        qInfo()<< sPath.at(i)->Id;
//    }

    return sPath;



}
