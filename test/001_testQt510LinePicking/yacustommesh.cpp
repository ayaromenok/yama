#include "yacustommesh.h"
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPerVertexColorMaterial>

YaCustomMesh::YaCustomMesh(Qt3DCore::QEntity *rootEntity,
                           bool isLines, bool isPoints)
{
    setParent(rootEntity);
    _isLines = isLines;
    _isPoints = isPoints;
    addMaterial();
    addTransform();

    _meshRnd = new Qt3DRender::QGeometryRenderer;
    _geom = new Qt3DRender::QGeometry(_meshRnd);

    _vxBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer,_geom);
    _idBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer, _geom);
    fillVertexBuffer();
    fillIndexBuffer();
    fillAttributes();

    addRenderer();
    addComponents();
}

void
YaCustomMesh::fillVertexBuffer()
{ // vec3 for position
    // vec3 for colors
    // vec3 for normals

    /*          2
               /|\
              / | \
             / /3\ \
             0/___\ 1
    */

    // 4 distinct vertices
    QByteArray vertexBufferData;
    vertexBufferData.resize(4 * (3 + 3 + 3) * sizeof(float));

    // Vertices
    QVector3D v0(-1.0f, 0.0f, -1.0f);
    QVector3D v1(1.0f, 0.0f, -1.0f);
    QVector3D v2(0.0f, 1.0f, 0.0f);
    QVector3D v3(0.0f, 0.0f, 1.0f);

    // Faces Normals
    QVector3D n023 = QVector3D::normal(v0, v2, v3);
    QVector3D n012 = QVector3D::normal(v0, v1, v2);
    QVector3D n310 = QVector3D::normal(v3, v1, v0);
    QVector3D n132 = QVector3D::normal(v1, v3, v2);

    // Vector Normals
    QVector3D n0 = QVector3D(n023 + n012 + n310).normalized();
    QVector3D n1 = QVector3D(n132 + n012 + n310).normalized();
    QVector3D n2 = QVector3D(n132 + n012 + n023).normalized();
    QVector3D n3 = QVector3D(n132 + n310 + n023).normalized();

    // Colors
    QVector3D red(1.0f, 0.0f, 0.0f);
    QVector3D green(0.0f, 1.0f, 0.0f);
    QVector3D blue(0.0f, 0.0f, 1.0f);
    QVector3D white(1.0f, 1.0f, 1.0f);
    QVector3D lightGrey(.75f, 0.75f, 0.75f);
    QVector3D grey(0.5f, 0.5f, 0.5f);
    QVector3D darkGrey(0.25f, 0.25f, 0.25f);

    QVector<QVector3D> vertices;
    if (_isLines){
        vertices = QVector<QVector3D>()
                << v0 << n0 << white
                << v1 << n1 << white
                << v2 << n2 << white
                << v3 << n3 << white;
    } else if (_isPoints) {
        vertices = QVector<QVector3D>()
                << v0 << n0 << red
                << v1 << n1 << red
                << v2 << n2 << red
                << v3 << n3 << red;
    } else
    vertices = QVector<QVector3D>()
            << v0 << n0 << darkGrey
            << v1 << n1 << grey
            << v2 << n2 << darkGrey
            << v3 << n3 << grey;

    float *rawVertexArray = reinterpret_cast<float *>(vertexBufferData.data());
    int idx = 0;

    Q_FOREACH (const QVector3D &v, vertices) {
        rawVertexArray[idx++] = v.x();
        rawVertexArray[idx++] = v.y();
        rawVertexArray[idx++] = v.z();
    }
    _vxBuffer->setData(vertexBufferData);
}

void
YaCustomMesh::fillIndexBuffer()
{
    QByteArray indexBufferData;
    indexBufferData.resize(4 * 3 * sizeof(ushort));
    ushort *rawIndexArray = reinterpret_cast<ushort *>(indexBufferData.data());

    // Front
    rawIndexArray[0] = 0;
    rawIndexArray[1] = 1;
    rawIndexArray[2] = 2;
    // Bottom
    rawIndexArray[3] = 3;
    rawIndexArray[4] = 1;
    rawIndexArray[5] = 0;
    // Left
    rawIndexArray[6] = 0;
    rawIndexArray[7] = 2;
    rawIndexArray[8] = 3;
    // Right
    rawIndexArray[9] = 1;
    rawIndexArray[10] = 3;
    rawIndexArray[11] = 2;
    _idBuffer->setData(indexBufferData);
}

void
YaCustomMesh::fillAttributes()
{
    // Attributes
    Qt3DRender::QAttribute *positionAttribute = new Qt3DRender::QAttribute();
    positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(_vxBuffer);
    positionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setByteOffset(0);
    positionAttribute->setByteStride(9 * sizeof(float));
    positionAttribute->setCount(4);
    positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());

    Qt3DRender::QAttribute *normalAttribute = new Qt3DRender::QAttribute();
    normalAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    normalAttribute->setBuffer(_vxBuffer);
    normalAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    normalAttribute->setVertexSize(3);
    normalAttribute->setByteOffset(3 * sizeof(float));
    normalAttribute->setByteStride(9 * sizeof(float));
    normalAttribute->setCount(4);
    normalAttribute->setName(Qt3DRender::QAttribute::defaultNormalAttributeName());

    Qt3DRender::QAttribute *colorAttribute = new Qt3DRender::QAttribute();
    colorAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    colorAttribute->setBuffer(_vxBuffer);
    colorAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    colorAttribute->setVertexSize(3);
    colorAttribute->setByteOffset(6 * sizeof(float));
    colorAttribute->setByteStride(9 * sizeof(float));
    colorAttribute->setCount(4);
    colorAttribute->setName(Qt3DRender::QAttribute::defaultColorAttributeName());

    Qt3DRender::QAttribute *indexAttribute = new Qt3DRender::QAttribute();
    indexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
    indexAttribute->setBuffer(_idBuffer);
    indexAttribute->setVertexBaseType(Qt3DRender::QAttribute::UnsignedShort);
    indexAttribute->setVertexSize(1);
    indexAttribute->setByteOffset(0);
    indexAttribute->setByteStride(0);
    indexAttribute->setCount(12);

    _geom->addAttribute(positionAttribute);
    _geom->addAttribute(normalAttribute);
    _geom->addAttribute(colorAttribute);
    _geom->addAttribute(indexAttribute);
}

void
YaCustomMesh::addMaterial()
{
    _mtl = new Qt3DExtras::QPerVertexColorMaterial(this);
}

void
YaCustomMesh::addTransform()
{
    _trsfm = new Qt3DCore::QTransform;
    _trsfm->setScale(8.0f);
}

void
YaCustomMesh::addRenderer()
{
    _meshRnd->setInstanceCount(1);
    _meshRnd->setIndexOffset(0);
    _meshRnd->setFirstInstance(0);
    if (_isLines)
        _meshRnd->setPrimitiveType(Qt3DRender::QGeometryRenderer::LineLoop);
    else if (_isPoints)
        _meshRnd->setPrimitiveType(Qt3DRender::QGeometryRenderer::Points);
    else
        _meshRnd->setPrimitiveType(Qt3DRender::QGeometryRenderer::Triangles);
    _meshRnd->setGeometry(_geom);
    // 4 faces of 3 points
    _meshRnd->setVertexCount(12);
}

void
YaCustomMesh::addComponents()
{
    this->addComponent(_meshRnd);
    this->addComponent(_trsfm);
    this->addComponent(_mtl);
}


