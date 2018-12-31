#include "projectile.h"
#include "trianglemesh.h"

Projectile::Projectile(PhysicEngine* physicEngine, QMatrix4x4 turretMatrix, Node* rootNode)
{
    QString path(SRCDIR);

    _projectileSpeed = 30;


    _phyEngine = physicEngine;
    _geometry = new TriangleMesh(path + QString("/../Models/bullet.obj"));
    _drawable = new Drawable(_geometry);
    _transformation = new Transformation();

    _transformation->setModelMatrix(turretMatrix);
    _transformation->translate(0,-0.1f,0);

    _phyObj = _phyEngine->createNewPhysicObject(_drawable);

    // Ein PhysicObjectConstructionInfo Objekt erzeugen, welches die Eigenschaften eines PhysicObjects festlegt,
    // für jede Eigenschaft gibt es einen Standardwert, das Objekt wird später automatisch gelöscht
    PhysicObjectConstructionInfo* v_PhysicObjectConstructionInfo = new PhysicObjectConstructionInfo();
    // Optionale veränderung der Informationen
    v_PhysicObjectConstructionInfo->setCcdActivation(true); // durchdringen durch andere Objekte Abfangen, benötigt
                                                            // mehr Rechenzeit
    v_PhysicObjectConstructionInfo->setCollisionHull(CollisionHull::ConvexHull); // Form des Hüllkörpers
                                                                                     // festlegen
    v_PhysicObjectConstructionInfo->setFriction(0.5f); // Reibung zwischen 0 und 1 angeben, 0 keine reibung 1
                                                       // maximal
    v_PhysicObjectConstructionInfo->setLocalInertiaPoint(QVector3D(0.f, 0.f, 0.f)); // Schwerpunkt des Objektes
                                                                                    // angeben, Standardwert (0,0,0)
    v_PhysicObjectConstructionInfo->setMass(2.f); // Gewicht des Körpers bestimmen, sollte nicht zu groß gewählt
                                                  // werden
    //v_PhysicObjectConstructionInfo->setMidpointTransformation(QMatrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)); // Mittelpunkttransformation angeben falls
    // Geometrie in seinem Koordinatensystem
    // verschoben liegt
    v_PhysicObjectConstructionInfo->setRestitution(0.1f);     // Elastizität des Körpers bestimmen, von 0 bis 1
                                                              // definiert
    v_PhysicObjectConstructionInfo->setRollingFriction(0.1f); // Rollwiderstand vorallem bei Kugeln angeben


    // Dem PhysicObject die Konstruktionsinforaionen geben
    _phyObj->setConstructionInfo(v_PhysicObjectConstructionInfo);

    // Das PhysicObject in seiner Engine Registrieren, damit die Simulation starten kann
    _phyObj->registerPhysicObject();

    QVector3D direction = (QVector3D(0,0,-1) *turretMatrix).normalized();
    _phyObj->setLinearVelocity(direction*_projectileSpeed);

    Node* _transfNode = new Node(_transformation);
    Node* _Node = new Node(_drawable);
    rootNode->addChild(_transfNode);
    _transfNode->addChild(_Node);
}

