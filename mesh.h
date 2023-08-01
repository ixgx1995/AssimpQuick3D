#ifndef MESH_H
#define MESH_H

#include "QObject"
#include <QVector3D>
#include <QList>

struct Vertex
{
    inline float x() const { return position.x(); }
    inline float y() const { return position.y(); }
    inline float z() const { return position.z(); }

    QVector3D position;
    QVector3D normal;
};

Q_DECLARE_METATYPE(Vertex)

struct Mesh
{
public:
    inline Mesh() {}
    Mesh(const QList<Vertex> &vertices, const QList<quint32> &indices, QVector3D min, QVector3D max)
        : vertices(vertices), indices(indices), boundsMin(min), boundsMax(max)
    { }

    QList<Vertex> vertices;
    QList<quint32> indices;
    QVector3D boundsMin;
    QVector3D boundsMax;

};

Q_DECLARE_METATYPE(Mesh)

#endif // MESH_H

