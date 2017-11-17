#ifndef YACUSTOMMESH_H
#define YACUSTOMMESH_H

#include <QObject>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QMaterial>

class YaCustomMesh : public Qt3DCore::QEntity
{
public:
    YaCustomMesh(Qt3DCore::QEntity *rootEntity,
                 bool isLines = false,
                 bool isPoints = false);

private:
    void fillVertexBuffer();
    void fillIndexBuffer();
    void fillAttributes();

    void addMaterial();
    void addTransform();
    void addRenderer();
    void addComponents();
    Qt3DRender::QMaterial*              _mtl;
    Qt3DCore::QTransform*               _trsfm;

    Qt3DRender::QGeometryRenderer*      _meshRnd;
    Qt3DRender::QGeometry*              _geom;

    Qt3DRender::QBuffer*                _vxBuffer;
    Qt3DRender::QBuffer*                _idBuffer;
    bool                                _isLines;
    bool                                _isPoints;
};

#endif // YACUSTOMMESH_H
