#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <QProgressDialog>
#include <cstdlib>
#include <QVector>
#include <math.h>

#include <stdlib.h>
#include <list>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <time.h>
#include <cmath>
#include <future>

#define TAB_SIZE 20

namespace Ui {
class MainWindow;
}

using namespace OpenMesh;
using namespace OpenMesh::Attributes;

using namespace std;

struct RPoint
{
    int x;
    int y;
    int z;
};

struct MyTraits : public OpenMesh::DefaultTraits
{
    // use vertex normals and vertex colors
    VertexAttributes( OpenMesh::Attributes::Normal | OpenMesh::Attributes::Color | OpenMesh::Attributes::Status);
    // store the previous halfedge
    HalfedgeAttributes( OpenMesh::Attributes::PrevHalfedge );
    // use face normals face colors
    FaceAttributes( OpenMesh::Attributes::Normal | OpenMesh::Attributes::Color | OpenMesh::Attributes::Status);
    EdgeAttributes( OpenMesh::Attributes::Color | OpenMesh::Attributes::Status );
    // vertex thickness
    VertexTraits{float thickness; float value;};
    // edge thickness
    EdgeTraits{float thickness;};
};
typedef OpenMesh::TriMesh_ArrayKernelT<MyTraits> MyMesh;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // les fonctions à compléter
    void showEdgeSelection(MyMesh* _mesh);
    void collapseEdge(MyMesh* _mesh, int edgeID);
    void decimation(MyMesh* _mesh, int percent, QString method);
    void updateEdgeSelectionIHM();
    int smallestEdge(MyMesh* _mesh);
    void displayMesh(MyMesh *_mesh, bool isTemperatureMap = false, float mapRange = -1);
    void resetAllColorsAndThickness(MyMesh* _mesh);

    float faceArea(MyMesh* _mesh, int faceID);
    int getSmallestAngle(MyMesh *_mesh);
    int getSmallestPlan(MyMesh *_mesh);
    int getSmallestRatio(MyMesh *_mesh);
    float getAngleFF(MyMesh *_mesh, int faceID0, int faceID1);
    int getSmallestEdge(MyMesh *_mesh);
    int getSmallestEdgeFace(MyMesh *_mesh);

    float barycentricArea(MyMesh *_mesh, int vertexID);
    float angleEE(MyMesh *_mesh, int vertexID, int faceID);
    float angleFF(MyMesh *_mesh, int faceID0, int faceID1, int vertID0, int vertID1);
    float calculateCurveOnVertex(MyMesh *_mesh, int vertexID);
    void H_Curv(MyMesh *_mesh);
    void vertexThreading(MyMesh* _mesh, VertexHandle v);
    float GWAMC(MyMesh *_mesh, float delta, QVector<MyMesh::Point> N, VertexHandle X);

    float *Curvature;
    QVector<MyMesh::Point> rangeSearch(MyMesh *_mesh, int pid, float range);
    void saliency(MyMesh *_mesh);
    void initData(MyMesh *_mesh);
    void Neighbourhood(MyMesh *_mesh);
private slots:

    void on_pushButton_chargement_clicked();
    void on_pushButton_edgeMoins_clicked();
    void on_pushButton_edgePlus_clicked();
    void on_pushButton_delSelEdge_clicked();

    void on_pushButton_decimate_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:

    struct Point
    {
        int id;
        float x;
        float y;
        float z;
    };

    float Xmax;
    float Xmin;
    float Ymax;
    float Ymin;
    float Zmax;
    float Zmin;
    float cellSizex;
    float cellSizey;
    float cellSizez;
    float diagBoundBox;

    QVector<MyMesh::Point> pList;
    array<array<array<vector<MyMesh::Point>, TAB_SIZE>, TAB_SIZE>, TAB_SIZE> cluster;

    bool modevoisinage;

    MyMesh mesh;
    int vertexSelection;
    int edgeSelection;
    int faceSelection;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
