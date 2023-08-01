#include "mygeometry.h"

MyGeometry::MyGeometry()
{
//    updatePro();
}

void MyGeometry::setMesh(const Mesh &mesh)
{
    _mesh = mesh;
    updateData();
    update();
    emit meshChanged();
}

void MyGeometry::updateData()
{
    clear();

    int stride = sizeof(Vertex);

    QByteArray vertexData(_mesh.vertices.count() * stride, Qt::Initialization::Uninitialized);
    memcpy(vertexData.data(), _mesh.vertices.constData(), vertexData.size());
    setVertexData(vertexData);

    QByteArray indexData(_mesh.indices.count()*sizeof(quint32), Qt::Initialization::Uninitialized);
    memcpy(indexData.data(), _mesh.indices.constData(), indexData.size());
    setIndexData(indexData);

    setStride(stride);
    setBounds(_mesh.boundsMin, _mesh.boundsMax);

    setPrimitiveType(QQuick3DGeometry::PrimitiveType::Triangles);
    addAttribute(Attribute::PositionSemantic, 0, Attribute::ComponentType::F32Type);
    addAttribute(Attribute::NormalSemantic, sizeof(QVector3D), Attribute::ComponentType::F32Type);
    addAttribute(Attribute::IndexSemantic, 0, Attribute::ComponentType::U32Type);
}

void MyGeometry::updatePro()
{
    clear();

    int stride = 3 * sizeof(float);
    QByteArray vertexData(3 * stride, Qt::Initialization::Uninitialized);
    float *p = reinterpret_cast<float *>(vertexData.data());
    *p++ = -1.0f; *p++ = -1.0f; *p++ = 0.0f;
    *p++ = 1.0f; *p++ = -1.0f; *p++ = 0.0f;

    *p++ = 0.0f; *p++ = 1.0f; *p++ = 0.0f;

    setVertexData(vertexData);
    setStride(stride);
    setBounds(QVector3D(-1.0f, -1.0f, 0.0f), QVector3D(+1.0f, +1.0f, 0.0f));

    setPrimitiveType(QQuick3DGeometry::PrimitiveType::Triangles);
    addAttribute(QQuick3DGeometry::Attribute::PositionSemantic, 0, QQuick3DGeometry::Attribute::F32Type);
}

