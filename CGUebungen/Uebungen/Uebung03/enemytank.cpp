#include "enemytank.h"
#include "trianglemesh.h"

EnemyTank::EnemyTank(PhysicEngine* physicEngine, QMatrix4x4 StartPosMatrix, Node* rootNode)
{
QString path(SRCDIR);

_phyEngine = physicEngine;

//Chassis
chassis_geometry = new TriangleMesh(path + QString("/../Models/enemy_chassis.obj"));
chassis_drawable = new Drawable(chassis_geometry);
chassis_transformation = new Transformation();

chassis_transformation->setModelMatrix(StartPosMatrix);
chassis_transformation->translate(0,-0.1f,0);

chassis_phyObj = _phyEngine->createNewPhysicObject(chassis_drawable);

//Barrel
barrel_geometry = new TriangleMesh(path + QString("/../Models/enemy_barrel.obj"));
barrel_drawable = new Drawable(barrel_geometry);
barrel_transformation = new Transformation();

barrel_transformation->setModelMatrix(StartPosMatrix);
barrel_transformation->translate(0,-0.1f,0);

barrel_phyObj = _phyEngine->createNewPhysicObject(barrel_drawable);

//Turret
turret_geometry = new TriangleMesh(path + QString("/../Models/enemy_turret.obj"));
turret_drawable = new Drawable(turret_geometry);
turret_transformation = new Transformation();

turret_transformation->setModelMatrix(StartPosMatrix);
turret_transformation->translate(0,-0.1f,0);

turret_phyObj = _phyEngine->createNewPhysicObject(turret_drawable);

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
chassis_phyObj->setConstructionInfo(v_PhysicObjectConstructionInfo);
barrel_phyObj->setConstructionInfo(v_PhysicObjectConstructionInfo);
turret_phyObj->setConstructionInfo(v_PhysicObjectConstructionInfo);

// Das PhysicObject in seiner Engine Registrieren, damit die Simulation starten kann
chassis_phyObj->registerPhysicObject();
barrel_phyObj->registerPhysicObject();
turret_phyObj->registerPhysicObject();

//QVector3D direction = (QVector3D(0,0,-1) *StartPosMatrix).normalized();
//_phyObj->setLinearVelocity(direction*_projectileSpeed);

Node* chassis_transfNode = new Node(chassis_transformation);
Node* chassis_Node = new Node(chassis_drawable);
Node* barrel_transfNode = new Node(barrel_transformation);
Node* barrel_Node = new Node(barrel_drawable);
Node* turret_transfNode = new Node(turret_transformation);
Node* turret_Node = new Node(turret_drawable);

rootNode->addChild(chassis_transfNode);
chassis_transfNode->addChild(chassis_Node);
chassis_transfNode->addChild(turret_transfNode);
turret_transfNode->addChild(turret_Node);
turret_transfNode->addChild(barrel_transfNode);
barrel_transfNode->addChild(barrel_Node);
}
