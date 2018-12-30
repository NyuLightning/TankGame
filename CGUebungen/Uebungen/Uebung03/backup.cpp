//#include "opengl.h"
//#include "scenemanager.h"
//#include "transformation.h"
//#include "keyboardtransformation.h"
//#include "color.h"
//#include "simplecube.h"
//#include "simpleplane.h"
//#include "mainwindow.h"
//#include "controllablecamera.h"
//#include "screenrenderer.h"

//Node* initScene1();

//void SceneManager::initScenes()
//{
//    ControllableCamera* cam = new ControllableCamera();
//    RenderingContext* myContext = new RenderingContext(cam);
//    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
//    unsigned int myScene = SceneManager::instance()->addScene(initScene1());
//    ScreenRenderer* myRenderer = new ScreenRenderer(myContextNr, myScene);
//    Q_UNUSED(myRenderer);

//    // Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
//    SceneManager::instance()->setActiveScene(myScene);
//    SceneManager::instance()->setActiveContext(myContextNr);
//    //    SceneManager::instance()->setFullScreen();
//}

//Node* initScene1()
//{
//    //    QString path(SRCDIR); // aus .pro-File!
//    // Physic Engine Erzeugen und einen Pointer auf Instanz holen
//    int v_Slot = PhysicEngineManager::createNewPhysicEngineSlot(PhysicEngineName::BulletPhysicsLibrary);
//    PhysicEngine* v_PhysicEngine = PhysicEngineManager::getPhysicEngineBySlot(v_Slot);
//    Node* root = new Node(new Transformation);

// Array für Cubes und dazugehörigen PhysicObjects
//#define V_NUMBER_CUBES 10
//    Transformation* v_Transformations[V_NUMBER_CUBES];
//    Drawable* v_Cubes[V_NUMBER_CUBES];
//    PhysicObject* v_PhysicObjects[V_NUMBER_CUBES];
//    for (int i = 0; i < V_NUMBER_CUBES; i++)
//    {
//        // Transformation erzeugen für Position
//        v_Transformations[i] = new Transformation();
//        v_Transformations[i]->translate(0.f, ((float)i + 0.25f) * 2.f, 0.f);

//        // Trafo in Baum hängen
//        Node* transformationNode = new Node(v_Transformations[i]);
//        root->addChild(transformationNode);

//        // Geometrie und Szenenobjekt erzeugen
//        v_Cubes[i] = new Drawable(new SimpleCube(1.f));
//        transformationNode->addChild(new Node(v_Cubes[i]));
//        v_Cubes[i]->getProperty<Color>()->setValue(1.f / ((float)i + 1.f), 1.f / ((float)i + 1.f), 1.f / ((float)i + 1.f), 1.f);

//        // Ein PhysicObject von der Engine für ein Drawable erzeugen lassen
//        v_PhysicObjects[i] = v_PhysicEngine->createNewPhysicObject(v_Cubes[i]);

//        // Ein PhysicObjectConstructionInfo Objekt erzeugen, welches die Eigenschaften eines PhysicObjects festlegt,
//        // für jede Eigenschaft gibt es einen Standardwert, das Objekt wird später automatisch gelöscht
//        PhysicObjectConstructionInfo* v_PhysicObjectConstructionInfo = new PhysicObjectConstructionInfo();
//        // Optionale veränderung der Informationen
//        v_PhysicObjectConstructionInfo->setBoxHalfExtends(QVector3D(0.5f, 0.5f, 0.5f)); // Ausdehnung des Würfels in
//                                                                                        // halber länge angeben
//        v_PhysicObjectConstructionInfo->setCcdActivation(true); // durchdringen durch andere Objekte Abfangen, benötigt
//                                                                // mehr Rechenzeit
//        v_PhysicObjectConstructionInfo->setCollisionHull(CollisionHull::BoxHalfExtends); // Form des Hüllkörpers
//                                                                                         // festlegen
//        v_PhysicObjectConstructionInfo->setFriction(0.5f); // Reibung zwischen 0 und 1 angeben, 0 keine reibung 1
//                                                           // maximal
//        v_PhysicObjectConstructionInfo->setLocalInertiaPoint(QVector3D(0.f, 0.f, 0.f)); // Schwerpunkt des Objektes
//                                                                                        // angeben, Standardwert (0,0,0)
//        v_PhysicObjectConstructionInfo->setMass(2.f); // Gewicht des Körpers bestimmen, sollte nicht zu groß gewählt
//                                                      // werden
//        v_PhysicObjectConstructionInfo->setMidpointTransformation(QMatrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)); // Mittelpunkttransformation angeben falls
//        // Geometrie in seinem Koordinatensystem
//        // verschoben liegt
//        v_PhysicObjectConstructionInfo->setRestitution(0.1f);     // Elastizität des Körpers bestimmen, von 0 bis 1
//                                                                  // definiert
//        v_PhysicObjectConstructionInfo->setRollingFriction(0.1f); // Rollwiderstand vorallem bei Kugeln angeben

//        // Dem PhysicObject die Konstruktionsinforaionen geben
//        v_PhysicObjects[i]->setConstructionInfo(v_PhysicObjectConstructionInfo);

//        // Das PhysicObject in seiner Engine Registrieren, damit die Simulation starten kann
//        v_PhysicObjects[i]->registerPhysicObject();
//    }

//    // Platte erstellen auf welche die Würfel fallen
//    Drawable* v_Plane = new Drawable(new SimplePlane(10.f));
//    v_Plane->setStaticGeometry(true);
//    Transformation* v_TransformationPlane = new Transformation();
//    Node* transformationPlaneNode = new Node(v_TransformationPlane);
//    v_TransformationPlane->rotate(-90.f, 1.f, 0.f, 0.f);
//    PhysicObject* v_PlanePhys = v_PhysicEngine->createNewPhysicObject(v_Plane);
//    PhysicObjectConstructionInfo* v_Constrinf = new PhysicObjectConstructionInfo();
//    v_Constrinf->setCollisionHull(CollisionHull::BoxAABB); // Automatische generierung einer Box aus den Vertexpunkten
//    v_PlanePhys->setConstructionInfo(v_Constrinf);
//    v_PlanePhys->registerPhysicObject();
//    transformationPlaneNode->addChild(new Node(v_Plane));

//    root->addChild(transformationPlaneNode);
//    return (root);
//}
