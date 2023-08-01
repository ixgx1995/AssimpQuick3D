#include "viewmanager.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <QFileDialog>
#include <iostream>


ViewManager::ViewManager(QObject *parent)
    : QObject{parent}
{

}

void ViewManager::loadFile()
{
    Assimp::Importer import;
    std::string szOut;
    import.GetExtensionList(szOut);

    QString t_assimp=tr("ASSIMP (") +QString::fromStdString(szOut) +tr(")");
    QString all_filter;
    all_filter+=t_assimp;
    QString filename = QFileDialog::getOpenFileName(nullptr,tr("open file"),"./",all_filter);
    if(filename.isEmpty()) {
        return;
    }

    _meshs.clear();
    const aiScene *scene = import.ReadFile(filename.toStdString(), aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString()<<std::endl;
        return;
    }
    processNode(scene->mRootNode, scene);///开始遍历scene
}

void ViewManager::processNode(aiNode *node, const aiScene *scene)
{
    // 处理节点所有的网格（如果有的话）
    for(unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];    ///一个节点有多个mesh
        auto nodeMesh = processMesh(mesh);
        _meshs.push_back(nodeMesh);

        MyGeometry *geometry = new MyGeometry;
        geometry->setMesh(nodeMesh);
        _geometrys.append(geometry);
    }
    // 接下来对它的子节点重复这一过程
    for(unsigned int i = 0; i < node->mNumChildren; i++) {    ///一个节点有多个子节点
        processNode(node->mChildren[i], scene);
    }
}

Mesh ViewManager::processMesh(aiMesh *mesh)
{
    QList<Vertex> vertices;
    QList<quint32> triangles;
    //遍历顶点,只存位置
    auto p = mesh->mVertices[0];
    QVector3D min, max;
    min = max = QVector3D(p.x, p.y, p.z);
    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex ver;
        ver.position = QVector3D(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        ver.normal = QVector3D(1, 1, 0);
        vertices.push_back(ver); ///把顶点存放的vector

        min.setX(std::min(min.x(), ver.position.x()));
        min.setY(std::min(min.y(), ver.position.y()));
        min.setZ(std::min(min.z(), ver.position.z()));
        max.setX(std::max(max.x(), ver.position.x()));
        max.setY(std::max(max.y(), ver.position.y()));
        max.setZ(std::max(max.z(), ver.position.z()));
    }
    // 处理索引
    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {  ///索引数量mNumFaces
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++) {
            triangles.push_back(face.mIndices[j]);
        }
    }

    //构建mesh并作为返回值
    return Mesh(vertices, triangles, min, max);
}

