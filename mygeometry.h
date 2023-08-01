#ifndef MYGEOMETRY_H
#define MYGEOMETRY_H

#include "mesh.h"
#include <QQuick3DGeometry>

class MyGeometry : public QQuick3DGeometry
{
    Q_OBJECT
    Q_PROPERTY(Mesh mesh READ mesh WRITE setMesh NOTIFY meshChanged)
    QML_NAMED_ELEMENT(MyGeometry)

public:
    explicit MyGeometry();

    inline const Mesh &mesh() const { return _mesh; }
    void setMesh(const Mesh &mesh);

signals:
    void meshChanged();

private:
    void updateData();
    void updatePro();

private:
    Mesh _mesh;
};


#endif // MYGEOMETRY_H

