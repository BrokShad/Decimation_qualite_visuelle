#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <linux/errno.h>

using namespace std;


void MainWindow::initData(MyMesh *_mesh)
{
    //Génération de l'espace de clusters
    cout << "Attribution..." << endl;
    TAB_SIZE = pow(log10(mesh.n_vertices()),2)*2;
    cout << "Cluster size is " << TAB_SIZE << "³" << endl;

    N = new vector<MyMesh::Point>[8];

    cluster = new vector<MyMesh::Point>**[TAB_SIZE];
    for(int i=0; i<TAB_SIZE; i++)
    {
//        cout << i << "/" << TAB_SIZE << endl;
        cluster[i] = new vector<MyMesh::Point>*[TAB_SIZE];
        for(int j=0; j<TAB_SIZE; j++)
        {
            cluster[i][j] = new vector<MyMesh::Point>[TAB_SIZE];
        }
    }

    for (MyMesh::VertexIter vit = _mesh->vertices_begin(); vit != _mesh->vertices_end(); ++vit)
    {
        if(vit == _mesh->vertices_begin())
        {
            Xmax = _mesh->point(*vit)[0];
            Ymax = _mesh->point(*vit)[1];
            Zmax = _mesh->point(*vit)[2];
            Xmin = _mesh->point(*vit)[0];
            Ymin = _mesh->point(*vit)[1];
            Zmin = _mesh->point(*vit)[2];
        }
        else
        {
            if(_mesh->point(*vit)[0] > Xmax) Xmax = _mesh->point(*vit)[0];
            else if(_mesh->point(*vit)[0] < Xmin) Xmin = _mesh->point(*vit)[0];

            if(_mesh->point(*vit)[1] > Ymax) Ymax = _mesh->point(*vit)[1];
            else if(_mesh->point(*vit)[1] < Ymin) Ymin = _mesh->point(*vit)[1];

            if(_mesh->point(*vit)[2] > Zmax) Zmax = _mesh->point(*vit)[2];
            else if(_mesh->point(*vit)[2] < Zmin) Zmin = _mesh->point(*vit)[2];
        }
    }

    cellSizex = ((Xmax - Xmin)/TAB_SIZE)+0.00001;
    cellSizey = ((Ymax - Ymin)/TAB_SIZE)+0.00001;
    cellSizez = ((Zmax - Zmin)/TAB_SIZE)+0.00001;

    cout << "Bound box is (" << Xmin << "," << Ymin << "," << Zmin << ") to (" << Xmax << "," << Ymax << "," << Zmax << ")" << endl;
    cout << "Cell sizes are (" << cellSizex << "," << cellSizey << "," << cellSizez << ")" << endl;
    diagBoundBox = sqrt((Xmax-Xmin)*(Xmax-Xmin) + (Ymax-Ymin)*(Ymax-Ymin) + (Zmax-Zmin)*(Zmax-Zmin));

    //Distribution des points dans les clusters correspondants
    cout << "Putting points in clusters..." << endl;
    int cellX, cellY, cellZ;
    for (MyMesh::VertexIter vit = _mesh->vertices_begin(); vit != _mesh->vertices_end(); ++vit)
    {
        cellX = (_mesh->point(*vit)[0]-Xmin)/cellSizex;
        cellY = (_mesh->point(*vit)[1]-Ymin)/cellSizey;
        cellZ = (_mesh->point(*vit)[2]-Zmin)/cellSizez;
//        cout << "Point " << vit->idx() << " ("<< _mesh->point(*vit)[0] << "," << _mesh->point(*vit)[1] << "," << _mesh->point(*vit)[2] << ") at cell " << cellX << ", " << cellY << ", " << cellZ << endl;
//        getchar();
        cluster[cellX][cellY][cellZ].push_back(_mesh->point(*vit));
    }


    H_Curv(_mesh);
//    cout << "TESSSSSSSSST" << endl;
}

void MainWindow::rangeSearch(MyMesh *_mesh, int pid, float range)
{
        MyMesh::Point p = _mesh->point(_mesh->vertex_handle(pid));
        int pidCellX = (p[0]-Xmin)/cellSizex;
        int pidCellY = (p[1]-Ymin)/cellSizey;
        int pidCellZ = (p[2]-Zmin)/cellSizez;

        int cellPosXRange = 0;
        int cellPosYRange = 0;
        int cellPosZRange = 0;
        int cellNegXRange = 0;
        int cellNegYRange = 0;
        int cellNegZRange = 0;

        float Xrange = p[0]-Xmin-(cellSizex*pidCellX)+range;
        while(Xrange>cellSizex) {Xrange-=cellSizex; cellPosXRange++;}
        float Yrange = p[1]-Ymin-(cellSizey*pidCellY)+range;
        while(Yrange>cellSizey) {Yrange-=cellSizey; cellPosYRange++;}
        float Zrange = p[2]-Zmin-(cellSizez*pidCellZ)+range;
        while(Zrange>cellSizez) {Zrange-=cellSizez; cellPosZRange++;}

        Xrange = p[0]-Xmin-(cellSizex*pidCellX)-range;
        while(Xrange<0) {Xrange+=cellSizex; cellNegXRange++;}
        Yrange = p[1]-Ymin-(cellSizey*pidCellY)-range;
        while(Yrange<0) {Yrange+=cellSizey; cellNegYRange++;}
        Zrange = p[2]-Zmin-(cellSizez*pidCellZ)-range;
        while(Zrange<0) {Zrange+=cellSizez; cellNegZRange++;}

//        cout << "Cell range is " << cellPosXRange << " on Positive X, " << cellPosYRange << " on Positive Y, " << cellPosZRange << " on Positive Z" << endl;
//        cout << "Cell range is " << cellNegXRange << " on Negative X, " << cellNegYRange << " on Negative Y, " << cellNegZRange << " on Negative Z" << endl;
        int beginX = pidCellX-cellNegXRange;
        if(beginX<0) beginX = 0;
        int beginY = pidCellY-cellNegYRange;
        if(beginY<0) beginY = 0;
        int beginZ = pidCellZ-cellNegZRange;
        if(beginZ<0) beginZ = 0;

        int x,y,z,i,j;
        vector<MyMesh::Point>::iterator it;
        for(x = beginX; x<=pidCellX+cellPosXRange && x<TAB_SIZE; x++)
            for(y = beginY; y<=pidCellY+cellPosYRange && y<TAB_SIZE; y++)
                for(z = beginZ; z<=pidCellZ+cellPosZRange && z<TAB_SIZE; z++)
                {
//                    cout << "Looking into [" << x << "][" << y << "][" << z << "]" << endl;
                    for(it = cluster[x][y][z].begin(); it != cluster[x][y][z].end(); ++it)
                    {
                        float distance = sqrt(pow(p[0]-(*it)[0],2)+pow(p[1]-(*it)[1],2)+pow(p[2]-(*it)[2],2));
                        i=8;
                        if(distance<=diagBoundBox*0.003) i = 0;
                        else if(distance<=diagBoundBox*0.006) i = 1;
                        else if(distance<=diagBoundBox*0.009) i = 2;
                        else if(distance<=diagBoundBox*0.012) i = 3;
                        else if(distance<=diagBoundBox*0.015) i = 4;
                        else if(distance<=diagBoundBox*0.018) i = 5;
                        else if(distance<=diagBoundBox*0.024) i = 6;
                        else if(distance<=diagBoundBox*0.030) i = 7;
                        if(i<8) N[i].push_back(*it);
                    }
                }
}


void MainWindow::H_Curv(MyMesh* _mesh)
{
    Curvature = new float[_mesh->n_vertices()];

    // courbure moyenne
    for (MyMesh::VertexIter curVert = _mesh->vertices_begin(); curVert != _mesh->vertices_end(); curVert++) {
        float aire_barycentrique = barycentricArea(_mesh, (*curVert).idx());
        float H = calculateCurveOnVertex(_mesh, (*curVert).idx()) / (4 * aire_barycentrique);
        _mesh->data(*curVert).value = H;
//        cout << H << "H curv" << endl;
        Curvature[(*curVert).idx()] = H;
    }
}

float MainWindow::GWAMC(MyMesh* _mesh, float delta, int Nid, VertexHandle X){
//    float GWA[_mesh->n_vertices()];
    int id = X.idx();
    MyMesh::Point Xp = _mesh->point(_mesh->vertex_handle(id));
    float top = 0;
    float bot = 0;
//    cout << Curvature[id] << endl;
    for (int j = Nid; j >= 0; --j)
    {
        for (int i = 0; i < N[j].size(); ++i)
        {
            top += Curvature[id] * exp (-(norm(Xp-N[j].at(i))*norm(Xp-N[j].at(i)))/(2*delta*delta));
    //        cout << "Curvature[id] * exp ((norm(Xp-N.at(i))*norm(Xp-N.at(i)))/2*delta*delta)" << endl;
            bot += exp (-(norm(Xp-N[j].at(i))*norm(Xp-N[j].at(i)))/(2*delta*delta));
        }
    }
//    cout << Curvature[id] << " curvature " << endl;
//    cout << " valeur bot et top sommet " << id << " : " << top << "/" << bot << endl;
    if (bot == 0)
        return 0;
    return top/bot;
}

void MainWindow::vertexThreading(MyMesh* _mesh, VertexHandle v)
{
    rangeSearch(&mesh, v.idx(), diagBoundBox*0.030);
//    cout << N[0].size() << ", " << N[1].size() << ", " << N[2].size() << ", " << N[3].size() << ", " << N[4].size() << ", " << N[5].size() << ", " << N[6].size() << ", " << N[7].size() << ", " << endl;
//    exit(0);
    float delta1 = GWAMC(_mesh,diagBoundBox*0.003,0,v);
    float delta2 = GWAMC(_mesh,diagBoundBox*0.006,1,v);
    float delta3 = GWAMC(_mesh,diagBoundBox*0.009,2,v);
    float delta4 = GWAMC(_mesh,diagBoundBox*0.012,3,v);
    float delta5 = GWAMC(_mesh,diagBoundBox*0.015,4,v);
    float delta6 = GWAMC(_mesh,diagBoundBox*0.018,5,v);
    float delta7 = GWAMC(_mesh,diagBoundBox*0.024,6,v);
    float delta8 = GWAMC(_mesh,diagBoundBox*0.030,7,v);
//    cout << delta1 << ',' << delta2 << ',' << delta3 << ',' << delta4 << ',' << delta5 << ',' << delta6 << ',' << delta7 << ',' << delta8 << endl;
//        if (delta1 != delta2)
//            cout << delta1 << " " << delta2 << " saliency "<< endl;
    float saliencyValue = (abs(delta1-delta2)+abs(delta2-delta4)+abs(delta3-delta6)+abs(delta4-delta7)+abs(delta5-delta8))/5;
    if(saliencyValue < 0) saliencyValue = 0;
    _mesh->data(v).value = saliencyValue;
    if(saliencyValue > maxSaliency) maxSaliency = saliencyValue;
    else if(saliencyValue < minSaliency) minSaliency = saliencyValue;

    for(int i=0; i<8; i++) N[i].clear();

}

void MainWindow::saliency(MyMesh* _mesh){
    initData(&mesh);
    clock_t t1, t2;
    int i = 0;
    int progress;
//    ThreadPool tp(std::thread::hardware_concurrency());
//    cout << "Threads: " << std::thread::hardware_concurrency() << endl;
    for (MyMesh::VertexIter vit = _mesh->vertices_begin(); vit != _mesh->vertices_end(); ++vit)
    {
        progress = (int)((float)i/mesh.n_vertices()*100);
        if(progress > ui->saliencyProgressBar->value())
        {
            ui->saliencyProgressBar->setValue(progress);
        }
        if(i%1000 == 0) t1 = clock();
        vertexThreading(&mesh, *vit);
//        tp.enqueue([&](MyMesh* m, VertexHandle v){vertexThreading(m, v);}, &mesh, *vit);
//        async(launch::async, [&](MyMesh *m, VertexHandle v){return vertexThreading(m, v);}, &mesh, *vit);
        if(i%1000 == 999)
        {
            t2 = clock();

            cout << i << "/" << mesh.n_vertices() << " (" << static_cast<double>(t2-t1)/static_cast<double>(CLOCKS_PER_SEC) << "s since last update)" << endl;
        }
        i++;
    }

    ui->saliencyProgressBar->setValue(100);

}

float MainWindow::calculateCurveOnVertex(MyMesh* _mesh, int vertexID)
{
    VertexHandle vertex = VertexHandle(vertexID);
    float sum = 0.0;

    // on stocke toutes les faces adjacentes au sommet
    std::vector<int> faces;
    for(MyMesh::VertexFaceCWIter vfit = _mesh->vf_cwiter(vertex); vfit.is_valid(); vfit++){
        faces.push_back((*vfit).idx());
    }

    for(unsigned int i = 0; i < faces.size(); i++) {
        // on compare toutes les paires de face
        int face0 = faces[i];
        int face1 = faces[(i+1) % faces.size()];

        // on cherche l'arête commune entre les deux faces
        int edgeCommune;
        for(MyMesh::FaceEdgeIter feit0 = _mesh->fe_iter(FaceHandle(face0)); feit0.is_valid(); feit0++) {
            for(MyMesh::FaceEdgeIter feit1 = _mesh->fe_iter(FaceHandle(face1)); feit1.is_valid(); feit1++) {
                if((*feit0).idx() == (*feit1).idx()) {
                    edgeCommune = (*feit0).idx();
                    break;
                }
            }
        }

        // on cherche le sommet opposé sur la même arête
        int vertexOppose;
        for(MyMesh::VertexVertexIter vvit = _mesh->vv_iter(vertex); vvit.is_valid(); vvit++) {
            for(MyMesh::VertexEdgeIter veit = _mesh->ve_iter(vvit); veit.is_valid(); veit++) {
                if((*veit).idx() == edgeCommune) {
                    vertexOppose = (*vvit).idx();
                    break;
                }
            }
        }

        // on a tout trouvé, on ajoute l'angle entre les deux faces que multiplie
        // la longueur de l'arête commune
        sum += (angleFF(_mesh, face0, face1, vertexID, vertexOppose) * _mesh->calc_edge_length(EdgeHandle(edgeCommune)));
    }

    return sum;
}

float MainWindow::angleFF(MyMesh* _mesh, int faceID0,  int faceID1, int vertID0, int vertID1)
{
    // calcul des normales des faces que l'on normalise
    FaceHandle fh1 = _mesh->face_handle(faceID0);
    FaceHandle fh2 = _mesh->face_handle(faceID1);
    MyMesh::Normal normal1 = _mesh->calc_face_normal(fh1);
    MyMesh::Normal normal2 = _mesh->calc_face_normal(fh2);
    normal1.normalize();
    normal2.normalize();

    MyMesh::Point point1, point2;
    point1 = _mesh->point(_mesh->vertex_handle(vertID0));
    point2 = _mesh->point(_mesh->vertex_handle(vertID1));

    // calcul du vecteur entre point 1 et 2
    MyMesh::Normal vector_v1_v2 = point2 - point1;

    // calcul de l'angle entre les deux normales des faces 1 et 2
    float angle = acos(dot(normal1, normal2));

    //qDebug() << "(" << faceID0 << ", " << faceID1 << ", " << vertID0 << ", " << vertID1 << ") : " << angle * 180 / PI << endl;
    //qDebug() << dot(cross_product, vector_v1_v2) << endl;

    // determiner le signe de l'angle
    MyMesh::Normal cross_product = cross(normal1, normal2);
    return dot(cross_product, vector_v1_v2) < 0 ? - angle : angle;
}

float MainWindow::angleEE(MyMesh* _mesh, int vertexID, int faceID)
{
    FaceHandle face_h = _mesh->face_handle(faceID);
    QVector<MyMesh::Point> points;
    MyMesh::Point point_origine;

    // on cherche le point d'origine
    for(MyMesh::FaceVertexIter curVer = _mesh->fv_begin(face_h); curVer.is_valid(); curVer++) {
        VertexHandle vertex_h = *curVer;

        if(vertex_h.idx() == vertexID) {
            point_origine = _mesh->point(vertex_h);
        }
        else {
            points.push_back(_mesh->point(vertex_h));
        }
    }

    MyMesh::Point vecteur1 = points[1] - point_origine;
    MyMesh::Point vecteur2 = points[0] - point_origine;
    vecteur1.normalize();
    vecteur2.normalize();

    return acos(dot(vecteur1, vecteur2));
}

float MainWindow::barycentricArea(MyMesh* _mesh, int vertexID) {
    VertexHandle vh = _mesh->vertex_handle(vertexID);

    float area = 0;
    for(MyMesh::VertexFaceIter vfit = _mesh->vf_iter(vh); vfit.is_valid(); vfit++){
        area += faceArea(_mesh,(*vfit).idx());
    }

    return area / 3;
}

float MainWindow::faceArea(MyMesh* _mesh, int faceID)
{
    FaceHandle face_h = FaceHandle(faceID);

    // on enregistre les points de la face dans un QVector
    QVector<MyMesh::Point> points;
    for(MyMesh::FaceVertexIter curVer = _mesh->fv_iter(face_h); curVer.is_valid(); curVer++) {
        VertexHandle vertex_h = *curVer;
        points.push_back(_mesh->point(vertex_h));
    }
    float area = norm((points[1] - points[0]) % (points[2] - points[0])) / 2;
    points.clear();
    return area;
}


/************/
/*  OLD TP  */
/************/


void MainWindow::showEdgeSelection(MyMesh* _mesh)
{
    // on réinitialise les couleurs de tout le maillage
    resetAllColorsAndThickness(_mesh);

    /* **** à compléter ! (Partie 1) ****
     * cette fonction utilise la variables de sélection edgeSelection qui est l'ID de
     * l'arête sélectionnée et qui est égale à -1 si la sélection est vide
     */

    if(edgeSelection >= 0){
        _mesh->set_color(_mesh->edge_handle(edgeSelection), MyMesh::Color(0, 255, 0));
        _mesh->data(_mesh->edge_handle(edgeSelection)).thickness = 12;
    }


    // on affiche le nouveau maillage
    displayMesh(_mesh);
}

int MainWindow::getSmallestEdge(MyMesh* _mesh){

    float smallest = INT_MAX;
    int id_smallest;
    // parcours de toutes les arêtes
    for (MyMesh::EdgeIter curEdge = _mesh->edges_begin(); curEdge != _mesh->edges_end(); curEdge++)
    {
        EdgeHandle eh = EdgeHandle((*curEdge).idx());
        HalfedgeHandle heh = _mesh->halfedge_handle(eh,0);
        //si la taille de l'edge courrante est plus petite que la taille min, on actualise la taille du minimum ainsi que son id
        if(_mesh->calc_edge_length(eh) < smallest && _mesh->is_collapse_ok(heh)){
            smallest = _mesh->calc_edge_length(eh);
            id_smallest = eh.idx();
        }
    }
    return id_smallest;
}

int MainWindow::getSmallestSaliency(MyMesh* _mesh)
{
    float smallest = INT_MAX;
    int id_smallest;
    float current_value;
    // parcours de toutes les arêtes
    for (MyMesh::EdgeIter curEdge = _mesh->edges_begin(); curEdge != _mesh->edges_end(); curEdge++)
    {
        EdgeHandle eh = EdgeHandle((*curEdge).idx());
        HalfedgeHandle heh = _mesh->halfedge_handle(eh,0);
        //si la taille de l'edge courrante est plus petite que la taille min, on actualise la taille du minimum ainsi que son id
        current_value = (_mesh->data(_mesh->from_vertex_handle(heh)).value+_mesh->data(_mesh->to_vertex_handle(heh)).value)/2;
        if(current_value < smallest)
        {
            smallest = current_value;
            id_smallest = eh.idx();
        }
    }
    return id_smallest;
}

int MainWindow::getSmallestEdgeFace(MyMesh* _mesh){

    //cette fonction retour le plus petit rapport entre la taille de l'edge et l'aire des faces adjacentes
    float smallest = INT_MAX;
    int id_smallest;
    // parcours des arêtes
    for (MyMesh::EdgeIter curEdge = _mesh->edges_begin(); curEdge != _mesh->edges_end(); curEdge++)
    {
        EdgeHandle eh = EdgeHandle((*curEdge).idx());
        HalfedgeHandle heh = _mesh->halfedge_handle(eh,0);
        HalfedgeHandle oppoheh = _mesh->opposite_halfedge_handle(heh);
        FaceHandle fh1 = _mesh->face_handle(heh);
        FaceHandle fh2 = _mesh->face_handle(oppoheh);

        //calcul de la moyenne de l'aire des deux faces adjacentes
        float f1area = faceArea(_mesh, fh1.idx());
        float f2area = faceArea(_mesh, fh2.idx());
        float moyArea = f1area + f2area;
        moyArea = moyArea/2;
        if(_mesh->calc_edge_length(eh)*moyArea < smallest && _mesh->is_collapse_ok(heh)){
            smallest = _mesh->calc_edge_length(eh)*moyArea;
            id_smallest = eh.idx();
        }
    }
    return id_smallest;
}

int MainWindow::collapseEdge(MyMesh* _mesh, int edgeID)
{
    int r;
    EdgeHandle eh = EdgeHandle(edgeID);
    HalfedgeHandle heh = _mesh->halfedge_handle(eh, 0);
    //avant de supprimer une edge on vérifie qu'elle peut effectivement etre supprimée
    if (_mesh->is_collapse_ok(heh)){
        //calcul de la position du point au milieu de l'arrete que l'on souhaite supprimer
        MyMesh::Point midpoint =  _mesh->calc_edge_midpoint(heh);
        VertexHandle Destination = _mesh->to_vertex_handle(heh);

        _mesh->set_point(Destination, midpoint);
        _mesh->collapse(heh);
        r = 1;
    }
    else r = 0;

    _mesh->garbage_collection();
    return r;
}

// fonction pratique pour faire des tirages aléatoires
int randInt(int low, int high){return qrand() % ((high + 1) - low) + low;}

int MainWindow::getSmallestAngle(MyMesh* _mesh){
    //cette fonction permet de recupérer le plus petit angle entre les normales des deux faces adjacentes a une edge
    float smallest = INT_MAX;
    int id_smallest;
    for (MyMesh::EdgeIter curEdge = _mesh->edges_begin(); curEdge != _mesh->edges_end(); curEdge++){
        if (! _mesh->is_boundary(*curEdge) ){
            HalfedgeHandle heh = _mesh->halfedge_handle(*curEdge, 0);
            HalfedgeHandle oppoheh = _mesh->opposite_halfedge_handle(heh);
            FaceHandle fh0 = _mesh->face_handle(heh);
            FaceHandle fh1 = _mesh->face_handle(oppoheh);

            float ffangle = getAngleFF(_mesh, fh0.idx(), fh1.idx());
            //calcul de l'angle entre les deux normales
            if(ffangle < smallest && _mesh->is_collapse_ok(heh)){
                smallest = ffangle;

                id_smallest = (*curEdge).idx();
            }
        }
    }
    return id_smallest;

}

int MainWindow::getSmallestPlan(MyMesh *_mesh)
{
    //cette fonction calcul les normale du 1-ring de chaque vertex de chaque edges
    //il fait ensuite une moyenne de ces normal et retourne la plus petite des moyennes optenue
    float smallest = INT_MAX;
    int id_smallest;
    for (MyMesh::EdgeIter curEdge = _mesh->edges_begin(); curEdge != _mesh->edges_end(); curEdge++){
        if (! _mesh->is_boundary(*curEdge) ){
            HalfedgeHandle heh = _mesh->halfedge_handle(*curEdge, 0);

            //il n'y as pas besoin de faire les calcules si l'edge courante ne peut pas etre supprimée
            if(_mesh->is_collapse_ok(heh)){
                VertexHandle vertex0 = _mesh->to_vertex_handle(heh);
                VertexHandle vertex1 = _mesh->from_vertex_handle(heh);
                float moyF0 = 0;
                float moyF1 = 0;
                QVector<int> faceV0;
                QVector<int> faceV1;

                //parcours de toutes les faces du vertex courrant
                for(MyMesh::VertexFaceIter vfit = _mesh->vf_iter(vertex0); vfit.is_valid(); vfit ++){
                    faceV0.push_back((*vfit).idx());
                }
                //parcours de toutes les faces du vertex opposé au vertex courrant
                for(MyMesh::VertexFaceIter vfit = _mesh->vf_iter(vertex1); vfit.is_valid(); vfit ++){
                    faceV1.push_back((*vfit).idx());
                }

                for (int i=0; i<faceV0.size(); i++){
                    moyF0 += getAngleFF(_mesh, faceV0[i], faceV0[(i+1) % faceV0.size()]);
                }

                for (int i=0; i<faceV1.size(); i++){
                    moyF1 += getAngleFF(_mesh, faceV1[i], faceV1[(i+1) % faceV1.size()]);
                }

                moyF0 = moyF0 / faceV0.size();
                moyF1 = moyF1 / faceV1.size();

                float moy = (moyF0 + moyF1)/2;
                if(moy < smallest){
                    smallest = moy;
                    id_smallest = (*curEdge).idx();
                }
            }


        }

    }
    return id_smallest;
}

int MainWindow::getSmallestRatio(MyMesh *_mesh)
{
    float smallest = INT_MAX;
    int id_smallest;
    for (MyMesh::EdgeIter curEdge = _mesh->edges_begin(); curEdge != _mesh->edges_end(); curEdge++){
        if (! _mesh->is_boundary(*curEdge) ){
            HalfedgeHandle heh = _mesh->halfedge_handle(*curEdge, 0);

            if(_mesh->is_collapse_ok(heh)){
                VertexHandle vertex0 = _mesh->to_vertex_handle(heh);
                VertexHandle vertex1 = _mesh->from_vertex_handle(heh);
                float moyF0 = 0;
                float moyF1 = 0;
                QVector<int> faceV0;
                QVector<int> faceV1;

                for(MyMesh::VertexFaceIter vfit = _mesh->vf_iter(vertex0); vfit.is_valid(); vfit ++){
                    faceV0.push_back((*vfit).idx());
                }
                for(MyMesh::VertexFaceIter vfit = _mesh->vf_iter(vertex1); vfit.is_valid(); vfit ++){
                    faceV1.push_back((*vfit).idx());
                }

                for (int i=0; i<faceV0.size(); i++){
                    moyF0 += getAngleFF(_mesh, faceV0[i], faceV0[(i+1) % faceV0.size()]);
                }

                for (int i=0; i<faceV1.size(); i++){
                    moyF1 += getAngleFF(_mesh, faceV1[i], faceV1[(i+1) % faceV1.size()]);
                }

                moyF0 = moyF0 / faceV0.size();
                moyF1 = moyF1 / faceV1.size();
                float moy = (moyF0 + moyF1)/2;
                float size = _mesh->calc_edge_length(*curEdge);
                if(moy * size< smallest){
                    smallest = moy * size;
                    id_smallest = (*curEdge).idx();
                }
            }


        }

    }
    return id_smallest;
}


float MainWindow::getAngleFF(MyMesh* _mesh, int faceID0, int faceID1)
{
    FaceHandle fh0 = FaceHandle(faceID0);
    FaceHandle fh1 = FaceHandle(faceID1);
    MyMesh::Normal Nfaceh0 = _mesh->calc_face_normal(fh0);
    MyMesh::Normal Nfaceh1 = _mesh->calc_face_normal(fh1);

    float angle = acos(Nfaceh0 | Nfaceh1);


    return angle;
}

void MainWindow::decimation(MyMesh* _mesh, int percent)
{
    cout << "Decimating..." << endl;
    unsigned int finalEgdeCount = (_mesh->n_edges() * percent)/100;
    clock_t t1, t2;
    int i = 0;
    Dual current_dual;
    list<Dual> edgeList;
    for (MyMesh::EdgeIter curEdge = _mesh->edges_begin(); curEdge != _mesh->edges_end(); curEdge++)
    {
        EdgeHandle eh = EdgeHandle((*curEdge).idx());
        current_dual.id = eh.idx();
        HalfedgeHandle heh = _mesh->halfedge_handle(eh,0);
        current_dual.val = (_mesh->data(_mesh->from_vertex_handle(heh)).value+_mesh->data(_mesh->to_vertex_handle(heh)).value)/2;
        edgeList.push_back(current_dual);
    }
    edgeList.sort();
    list<Dual>::iterator it;
    while(_mesh->n_edges() > finalEgdeCount)
    {
        if(i%1000 == 0) t1 = clock();
        it = edgeList.begin();
        while(collapseEdge(&mesh, it->id)==0)
        {
            it++;
        }
        edgeList.erase(it,it);
        i++;
        if(i%1000 == 999)
        {
            t2 = clock();
            cout << _mesh->n_edges() << "/" << finalEgdeCount << " (" << static_cast<double>(t2-t1)/static_cast<double>(CLOCKS_PER_SEC) << "s since last update)" << endl;
        }
    }
}

//* **** début de la partie boutons et IHM **** *//

void MainWindow::on_pushButton_chargement_clicked()
{
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->saliencyProgressBar->setValue(0);

    // fenêtre de sélection des fichiers
    fileName = QFileDialog::getOpenFileName(this, tr("Open Mesh"), "", tr("Mesh Files (*.obj)"));

    // chargement du fichier .obj dans la variable globale "mesh"
    OpenMesh::IO::read_mesh(mesh, fileName.toUtf8().constData());
    fileName.chop(4);
    mesh.update_normals();

    // initialisation des couleurs et épaisseurs (sommets et arêtes) du mesh
    resetAllColorsAndThickness(&mesh);

    // on affiche le maillage
    displayMesh(&mesh);

    ui->pushButton_2->setEnabled(true);
}



/* **** fonctions supplémentaires **** */
// permet d'initialiser les couleurs et les épaisseurs des élements du maillage
void MainWindow::resetAllColorsAndThickness(MyMesh* _mesh)
{
    for (MyMesh::VertexIter curVert = _mesh->vertices_begin(); curVert != _mesh->vertices_end(); curVert++)
    {
        _mesh->data(*curVert).thickness = 1;
        _mesh->set_color(*curVert, MyMesh::Color(0, 0, 0));
    }

    for (MyMesh::FaceIter curFace = _mesh->faces_begin(); curFace != _mesh->faces_end(); curFace++)
    {
        _mesh->set_color(*curFace, MyMesh::Color(150, 150, 150));
    }

    for (MyMesh::EdgeIter curEdge = _mesh->edges_begin(); curEdge != _mesh->edges_end(); curEdge++)
    {
        _mesh->data(*curEdge).thickness = 1;
        _mesh->set_color(*curEdge, MyMesh::Color(0, 0, 0));
    }
}

// charge un objet MyMesh dans l'environnement OpenGL
void MainWindow::displayMesh(MyMesh* _mesh, bool isTemperatureMap, float mapRange)
{
    GLuint* triIndiceArray = new GLuint[_mesh->n_faces() * 3];
    GLfloat* triCols = new GLfloat[_mesh->n_faces() * 3 * 3];
    GLfloat* triVerts = new GLfloat[_mesh->n_faces() * 3 * 3];

    int i = 0;

    if(isTemperatureMap)
    {
        QVector<float> values;

        if(mapRange == -1)
        {
            for (MyMesh::VertexIter curVert = _mesh->vertices_begin(); curVert != _mesh->vertices_end(); curVert++)
                values.append(fabs(_mesh->data(*curVert).value));
            qSort(values);
            mapRange = values.at(values.size()*0.8);
            qDebug() << "mapRange" << mapRange;
        }

        float range = mapRange;
        MyMesh::ConstFaceIter fIt(_mesh->faces_begin()), fEnd(_mesh->faces_end());
        MyMesh::ConstFaceVertexIter fvIt;

        for (; fIt!=fEnd; ++fIt)
        {
            fvIt = _mesh->cfv_iter(*fIt);
            if(_mesh->data(*fvIt).value > 0){triCols[3*i+0] = 255; triCols[3*i+1] = 255 - std::min((_mesh->data(*fvIt).value/range) * 255.0, 255.0); triCols[3*i+2] = 255 - std::min((_mesh->data(*fvIt).value/range) * 255.0, 255.0);}
            else{triCols[3*i+2] = 255; triCols[3*i+1] = 255 - std::min((-_mesh->data(*fvIt).value/range) * 255.0, 255.0); triCols[3*i+0] = 255 - std::min((-_mesh->data(*fvIt).value/range) * 255.0, 255.0);}
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++; ++fvIt;
            if(_mesh->data(*fvIt).value > 0){triCols[3*i+0] = 255; triCols[3*i+1] = 255 - std::min((_mesh->data(*fvIt).value/range) * 255.0, 255.0); triCols[3*i+2] = 255 - std::min((_mesh->data(*fvIt).value/range) * 255.0, 255.0);}
            else{triCols[3*i+2] = 255; triCols[3*i+1] = 255 - std::min((-_mesh->data(*fvIt).value/range) * 255.0, 255.0); triCols[3*i+0] = 255 - std::min((-_mesh->data(*fvIt).value/range) * 255.0, 255.0);}
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++; ++fvIt;
            if(_mesh->data(*fvIt).value > 0){triCols[3*i+0] = 255; triCols[3*i+1] = 255 - std::min((_mesh->data(*fvIt).value/range) * 255.0, 255.0); triCols[3*i+2] = 255 - std::min((_mesh->data(*fvIt).value/range) * 255.0, 255.0);}
            else{triCols[3*i+2] = 255; triCols[3*i+1] = 255 - std::min((-_mesh->data(*fvIt).value/range) * 255.0, 255.0); triCols[3*i+0] = 255 - std::min((-_mesh->data(*fvIt).value/range) * 255.0, 255.0);}
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++;
        }
    }
    else
    {
        MyMesh::ConstFaceIter fIt(_mesh->faces_begin()), fEnd(_mesh->faces_end());
        MyMesh::ConstFaceVertexIter fvIt;
        for (; fIt!=fEnd; ++fIt)
        {
            fvIt = _mesh->cfv_iter(*fIt);
            triCols[3*i+0] = _mesh->color(*fIt)[0]; triCols[3*i+1] = _mesh->color(*fIt)[1]; triCols[3*i+2] = _mesh->color(*fIt)[2];
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++; ++fvIt;
            triCols[3*i+0] = _mesh->color(*fIt)[0]; triCols[3*i+1] = _mesh->color(*fIt)[1]; triCols[3*i+2] = _mesh->color(*fIt)[2];
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++; ++fvIt;
            triCols[3*i+0] = _mesh->color(*fIt)[0]; triCols[3*i+1] = _mesh->color(*fIt)[1]; triCols[3*i+2] = _mesh->color(*fIt)[2];
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++;
        }
    }


    ui->displayWidget->loadMesh(triVerts, triCols, _mesh->n_faces() * 3 * 3, triIndiceArray, _mesh->n_faces() * 3);

    delete[] triIndiceArray;
    delete[] triCols;
    delete[] triVerts;

    GLuint* linesIndiceArray = new GLuint[_mesh->n_edges() * 2];
    GLfloat* linesCols = new GLfloat[_mesh->n_edges() * 2 * 3];
    GLfloat* linesVerts = new GLfloat[_mesh->n_edges() * 2 * 3];

    i = 0;
    QHash<float, QList<int> > edgesIDbyThickness;
    for (MyMesh::EdgeIter eit = _mesh->edges_begin(); eit != _mesh->edges_end(); ++eit)
    {
        float t = _mesh->data(*eit).thickness;
        if(t > 0)
        {
            if(!edgesIDbyThickness.contains(t))
                edgesIDbyThickness[t] = QList<int>();
            edgesIDbyThickness[t].append((*eit).idx());
        }
    }
    QHashIterator<float, QList<int> > it(edgesIDbyThickness);
    QList<QPair<float, int> > edgeSizes;
    while (it.hasNext())
    {
        it.next();

        for(int e = 0; e < it.value().size(); e++)
        {
            int eidx = it.value().at(e);

            MyMesh::VertexHandle vh1 = _mesh->to_vertex_handle(_mesh->halfedge_handle(_mesh->edge_handle(eidx), 0));
            linesVerts[3*i+0] = _mesh->point(vh1)[0];
            linesVerts[3*i+1] = _mesh->point(vh1)[1];
            linesVerts[3*i+2] = _mesh->point(vh1)[2];
            linesCols[3*i+0] = _mesh->color(_mesh->edge_handle(eidx))[0];
            linesCols[3*i+1] = _mesh->color(_mesh->edge_handle(eidx))[1];
            linesCols[3*i+2] = _mesh->color(_mesh->edge_handle(eidx))[2];
            linesIndiceArray[i] = i;
            i++;

            MyMesh::VertexHandle vh2 = _mesh->from_vertex_handle(_mesh->halfedge_handle(_mesh->edge_handle(eidx), 0));
            linesVerts[3*i+0] = _mesh->point(vh2)[0];
            linesVerts[3*i+1] = _mesh->point(vh2)[1];
            linesVerts[3*i+2] = _mesh->point(vh2)[2];
            linesCols[3*i+0] = _mesh->color(_mesh->edge_handle(eidx))[0];
            linesCols[3*i+1] = _mesh->color(_mesh->edge_handle(eidx))[1];
            linesCols[3*i+2] = _mesh->color(_mesh->edge_handle(eidx))[2];
            linesIndiceArray[i] = i;
            i++;
        }
        edgeSizes.append(qMakePair(it.key(), it.value().size()));
    }

    ui->displayWidget->loadLines(linesVerts, linesCols, i * 3, linesIndiceArray, i, edgeSizes);

    delete[] linesIndiceArray;
    delete[] linesCols;
    delete[] linesVerts;

    GLuint* pointsIndiceArray = new GLuint[_mesh->n_vertices()];
    GLfloat* pointsCols = new GLfloat[_mesh->n_vertices() * 3];
    GLfloat* pointsVerts = new GLfloat[_mesh->n_vertices() * 3];

    i = 0;
    QHash<float, QList<int> > vertsIDbyThickness;
    for (MyMesh::VertexIter vit = _mesh->vertices_begin(); vit != _mesh->vertices_end(); ++vit)
    {
        float t = _mesh->data(*vit).thickness;
        if(t > 0)
        {
            if(!vertsIDbyThickness.contains(t))
                vertsIDbyThickness[t] = QList<int>();
            vertsIDbyThickness[t].append((*vit).idx());
        }
    }
    QHashIterator<float, QList<int> > vitt(vertsIDbyThickness);
    QList<QPair<float, int> > vertsSizes;

    while (vitt.hasNext())
    {
        vitt.next();

        for(int v = 0; v < vitt.value().size(); v++)
        {
            int vidx = vitt.value().at(v);

            pointsVerts[3*i+0] = _mesh->point(_mesh->vertex_handle(vidx))[0];
            pointsVerts[3*i+1] = _mesh->point(_mesh->vertex_handle(vidx))[1];
            pointsVerts[3*i+2] = _mesh->point(_mesh->vertex_handle(vidx))[2];
            pointsCols[3*i+0] = _mesh->color(_mesh->vertex_handle(vidx))[0];
            pointsCols[3*i+1] = _mesh->color(_mesh->vertex_handle(vidx))[1];
            pointsCols[3*i+2] = _mesh->color(_mesh->vertex_handle(vidx))[2];
            pointsIndiceArray[i] = i;
            i++;
        }
        vertsSizes.append(qMakePair(vitt.key(), vitt.value().size()));
    }

    ui->displayWidget->loadPoints(pointsVerts, pointsCols, i * 3, pointsIndiceArray, i, vertsSizes);

    delete[] pointsIndiceArray;
    delete[] pointsCols;
    delete[] pointsVerts;
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    vertexSelection = -1;
    edgeSelection = -1;
    faceSelection = -1;
    liveDisplay = false;
    decimationHeatmap = false;

    modevoisinage = false;

    ui->setupUi(this);

    ui->saliencyProgressBar->setRange(0, 100);
    ui->decimationRatioSpinbox->setRange(0, 100);

    ui->checkBox->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->decimationRatioSpinbox->setEnabled(false);

    const QStringList optionList = {"Quadric Saliency","Quadric"};
    ui->decimationComboBox->addItems(optionList);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->checkBox->setEnabled(false);
    ui->saliencyProgressBar->setValue(0);
    QFile heatfile(fileName + QString::fromStdString(".heat"));
    QStringList heatlist;
    if(heatfile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Heatfile found, using it instead of recalculating" << endl;
        QTextStream in(&heatfile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QRegExp rx("[,]");
            heatlist = line.split(rx, QString::SkipEmptyParts);
        }
        MyMesh::VertexIter vit = mesh.vertices_begin();
        for(int i = 0; i < heatlist.size(); i++)
        {
            mesh.data(*vit).value = heatlist.at(i).toFloat();
            ++vit;
        }
        ui->saliencyProgressBar->setValue(100);
    }
    else QtConcurrent::run([&](MyMesh* _mesh){saliency(&mesh);}, &mesh);
}

void MainWindow::on_saliencyProgressBar_valueChanged(int value)
{
    if(value%2 == 0 && liveDisplay)
    {
        displayMesh(&mesh,true);
    }
    if(value == 100)
    {
        if(!liveDisplay) displayMesh(&mesh,true);
        ui->checkBox->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton->setEnabled(true);
        ui->decimationRatioSpinbox->setEnabled(true);
    }
}

void MainWindow::on_decimationComboBox_currentIndexChanged(int index)
{
    decimationOptionIndex = index;
}

void MainWindow::on_pushButton_3_clicked()
{
    mesh2 = mesh;
    mesh2.update_normals();
    resetAllColorsAndThickness(&mesh2);
    Decimater::DecimaterT<MyMesh> decimator(mesh2);

    Decimater::ModQuadricT<MyMesh>::Handle MQhandler;
    Decimater::ModQuadricSaliencyT<MyMesh>::Handle MQShandler;

    if(decimationOptionIndex == 0) { decimator.add(MQShandler); decimator.module(MQShandler).unset_max_err(); }
    else if(decimationOptionIndex == 1) { decimator.add(MQhandler); decimator.module(MQhandler).unset_max_err(); }

    decimator.initialize();
    decimator.decimate_to(mesh2.n_vertices()*ui->decimationRatioSpinbox->value()/100);
    mesh2.garbage_collection();
    ui->pushButton_4->setEnabled(true);
    displayMesh(&mesh2,decimationHeatmap);
}

void MainWindow::on_pushButton_4_clicked()
{
    // fenêtre de sélection des fichiers
    //QString fileName = QFileDialog::getOpenFileName(this, tr("Open Mesh"), "", tr("Mesh Files (*.obj)"));
    QString savefile = QString::fromStdString(fileName.toStdString()+"_QS_"+to_string(ui->decimationRatioSpinbox->value())+".obj");

    // chargement du fichier .obj dans la variable globale "mesh"
    OpenMesh::IO::write_mesh(mesh2, savefile.toUtf8().constData());
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    liveDisplay = arg1;
    cout << "Live display = " << arg1 << endl;
}

void MainWindow::on_decimationRatioSpinbox_valueChanged(double arg1)
{

}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    decimationHeatmap = arg1;
    cout << "DHM = " << arg1 << endl;
}

void MainWindow::on_pushButton_clicked()
{
    //Export the heatmap
    QFile file(fileName + QString::fromStdString(".heat"));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (MyMesh::VertexIter vit = mesh.vertices_begin(); vit != mesh.vertices_end(); vit++)
        out << mesh.data(*vit).value << ",";
    cout << "Successfully exported the heatmap to: " << fileName.toStdString()+".heat" << endl;
}
