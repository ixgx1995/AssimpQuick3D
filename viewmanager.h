#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <QQmlEngine>
#include <QObject>
#include <QList>
#include "mesh.h"
#include "mygeometry.h"

class aiNode;
class aiScene;
class aiMesh;

class ViewManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<Mesh> meshes READ meshes CONSTANT)
    Q_PROPERTY(QList<MyGeometry*> geometrys READ geometrys CONSTANT)
    QML_NAMED_ELEMENT(ViewManager)

public:
    explicit ViewManager(QObject *parent = nullptr);

    Q_INVOKABLE void loadFile();

    QList<Mesh> meshes() const { return _meshs; }
    QList<MyGeometry*> geometrys() const { return _geometrys; }

private:
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh);

private:
    QList<Mesh> _meshs;
    QList<MyGeometry*> _geometrys;

};

#endif // VIEWMANAGER_H

