#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Decimater/DecimaterT.hh>
#include <OpenMesh/Tools/Decimater/ModAspectRatioT.hh>
#include <OpenMesh/Tools/Decimater/ModEdgeLengthT.hh>
#include <OpenMesh/Tools/Decimater/ModHausdorffT.hh>
#include <OpenMesh/Tools/Decimater/ModIndependentSetsT.hh>
#include <OpenMesh/Tools/Decimater/ModNormalDeviationT.hh>
#include <OpenMesh/Tools/Decimater/ModNormalFlippingT.hh>
#include <OpenMesh/Tools/Decimater/ModProgMeshT.hh>
#include <OpenMesh/Tools/Decimater/ModQuadricT.hh>
#include <OpenMesh/Tools/Decimater/ModRoundnessT.hh>
#include <QProgressDialog>
#include <cstdlib>
#include <QVector>
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QFuture>
#include <math.h>

#include <stdlib.h>
#include <list>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <time.h>
#include <cmath>

//#define TAB_SIZE 70
#include "threadpool.h"

namespace Ui {
class MainWindow;
}

using namespace OpenMesh;
using namespace OpenMesh::Attributes;

using namespace std;

struct Dual
{
    int id;
    int val;

    bool operator < (const Dual& b) const
    {
        return (val < b.val);
    }
};

struct DualOp
{
    inline bool operator() (const Dual& a, const Dual& b)
    {
        return (a.val < b.val);
    }
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
    virtual ~MainWindow();

    // les fonctions à compléter
    void showEdgeSelection(MyMesh* _mesh);
    int collapseEdge(MyMesh* _mesh, int edgeID);
    void decimation(MyMesh* _mesh, int percent);
    void updateEdgeSelectionIHM();
    int smallestEdge(MyMesh* _mesh);
    void displayMesh(MyMesh *_mesh, bool isTemperatureMap = false, float mapRange = -1);
    void resetAllColorsAndThickness(MyMesh* _mesh);

    float faceArea(MyMesh* _mesh, int faceID);
    int getSmallestAngle(MyMesh *_mesh);
    int getSmallestPlan(MyMesh *_mesh);
    int getSmallestRatio(MyMesh *_mesh);
    int getSmallestSaliency(MyMesh *_mesh);
    float getAngleFF(MyMesh *_mesh, int faceID0, int faceID1);
    int getSmallestEdge(MyMesh *_mesh);
    int getSmallestEdgeFace(MyMesh *_mesh);

    float barycentricArea(MyMesh *_mesh, int vertexID);
    float angleEE(MyMesh *_mesh, int vertexID, int faceID);
    float angleFF(MyMesh *_mesh, int faceID0, int faceID1, int vertID0, int vertID1);
    float calculateCurveOnVertex(MyMesh *_mesh, int vertexID);
    void H_Curv(MyMesh *_mesh);
    void vertexThreading(MyMesh* _mesh, VertexHandle v);
    float GWAMC(MyMesh *_mesh, float delta, int Nid, VertexHandle X);

    float *Curvature;
    void rangeSearch(MyMesh *_mesh, int pid, float range);
    void saliency(MyMesh *_mesh);
    void initData(MyMesh *_mesh);

private slots:

    void on_pushButton_chargement_clicked();

    void on_pushButton_2_clicked();

    void on_saliencyProgressBar_valueChanged(int value);

    void on_decimationComboBox_currentIndexChanged(int index);

    void on_pushButton_3_clicked();

    void on_decimationProgressBar_valueChanged(int value);

    void on_pushButton_4_clicked();

    void on_checkBox_stateChanged(int arg1);

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
    int TAB_SIZE;
    float maxSaliency;
    float minSaliency;

//    array<array<array<vector<MyMesh::Point>, TAB_SIZE>, TAB_SIZE>, TAB_SIZE> cluster;
    vector<MyMesh::Point> ***cluster;
    vector<MyMesh::Point> *N;
    vector<float> delta;
    vector<float> top;
    vector<float> bot;

    bool modevoisinage;

    bool liveDisplay;

    MyMesh mesh;
    int vertexSelection;
    int edgeSelection;
    int faceSelection;
    int decimationOptionIndex;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
