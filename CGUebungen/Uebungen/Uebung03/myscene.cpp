#include "opengl.h"
#include "screenrenderer.h"
#include "transformation.h"
#include "keyboardtransformation.h"
#include "color.h"
#include "bodypart.h"
#include "kopf.h"
#include "arm.h"
#include "controllablecamera.h"
#include "scenemanager.h"
#include "window.h"
#include "uitransformation.h"

#include "ui_robot.h"

#include "mousecontrollablecamera.h"
#include "trianglemesh.h"
#include "texture.h"
#include "shader.h"
#include "listener.h"
//#include "audioengine.h"
//#include "soundsource.h"
//#include "shadermanager.h"
//#include "efx-presets.h"

#include "inputregistry.h"
#include "gameloop.h"


#include "body.h"
#include "tower.h"
#include "pipe.h"

#include "world.h"
#include "trianglemesh.h"

#include "bodypart.h"
#include "listener.h"

#include "idleobserver.h"
#include "qdebug.h"


Node* initScene1();
UITransformation* rot;

void SceneManager::initScenes()
{
    Ui_RobotDock* lDock;
    QDockWidget* lDockWidget = new QDockWidget(QString("Robot"), SceneManager::getMainWindow());

    Camera* cam = new Camera();
    RenderingContext* myContext = new RenderingContext(cam);
    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
    unsigned int myScene = SceneManager::instance()->addScene(initScene1());
    ScreenRenderer* myRenderer = new ScreenRenderer(myContextNr, myScene);
    Q_UNUSED(myRenderer);

    // Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(myScene);
    SceneManager::instance()->setActiveContext(myContextNr);
    SceneManager::instance()->setFullScreen();

    cam->setEyePosition(QVector3D(.0,0.0,10.));

    lDock = new Ui_RobotDock();

    lDock->setupUi(lDockWidget);
    lDockWidget->resize(150, 100);
    SceneManager::getMainWindow()->addDockWidget(Qt::RightDockWidgetArea, lDockWidget);
    lDockWidget->show();

    QObject::connect(Window::getInstance(), SIGNAL(sigFPS(int)), lDock->lcdNumber, SLOT(display(int)));
    // Hier können die Signals des UI mit eigenen QObject Slots verbunden werden und umgekehrt
    // Loesung fuer Orientierung ueber GUI mit Qt Signal/Slot
//    QObject::connect(lDock->verticalSlider, SIGNAL(valueChanged(int)), rot, SLOT(setXrot(int)));
//    QObject::connect(lDock->verticalSlider_2, SIGNAL(valueChanged(int)), rot, SLOT(setYrot(int)));
//    QObject::connect(lDock->verticalSlider_3, SIGNAL(valueChanged(int)), rot, SLOT(setZrot(int)));
}

Node* initScene1()
{
    //Objekte anlegen
    QString path(SRCDIR); //aus .pro-File!



    rot = new UITransformation();
    KeyboardTransformation* schieb = new KeyboardTransformation;
    Node* schiebNode = new Node(schieb);
    Node* rotNode = new Node(rot);

/*
    //    Objekte anlegen
    KeyboardTransformation* schieb = new KeyboardTransformation;
    BodyPart* torso = new BodyPart(4.0f, 8.0f, 4.0f);
    Kopf* belmes = new Kopf(2.0f, 1.0f, 2.0f);
    Arm* lArm = new Arm(1.0f, 6.0f, 1.0f, false);
    Arm* rArm = new Arm(1.0f, 6.0f, 1.0f, true);
    BodyPart* lFinger = new BodyPart(0.2f, 1.0f, 0.2f);
    BodyPart* rFinger = new BodyPart(0.2f, 1.0f, 0.2f);
    BodyPart* bein = new BodyPart(1.5f, 2.0f, 1.5f);
    BodyPart* fuss = new BodyPart(3.0f, 0.2f, 3.0f);
    Color* c;
*/



    // Panzerteile erzeugen

    Geometry* gTower = new TriangleMesh(path + QString("/../Models/turret.obj"));
    Geometry* gBody = new TriangleMesh(path + QString("/../Models/chassis.obj"));
    Geometry* gPipe = new TriangleMesh(path + QString("/../Models/barrel.obj"));

    Drawable* dTower = new Drawable(gTower);
    Drawable* dBody = new Drawable(gBody);
    Drawable* dPipe = new Drawable(gPipe);

    Texture *t;

    Transformation *posTower = new Transformation();
    Transformation *posBody = new Transformation();
    Transformation *posPipe = new Transformation();

    // Texturen laden

    t = dTower->getProperty<Texture>();
    t->loadPicture(path + QString("/../Textures/Unbekannt.png"));

    t = dBody->getProperty<Texture>();
    t->loadPicture(path + QString("/../Textures/Unbekannt2.png"));

    t = dPipe->getProperty<Texture>();
    t->loadPicture(path + QString("/../Textures/Unbekannt3.png/"));

    // Shader laden
    /* ... */

    // Nodes anlegen

    Node *dTowerNode = new Node(dTower);
   // Node *posTowerNode = new Node(posTower);

    Node *dBodyNode = new Node(dBody);
  //  Node *posBodyNode = new Node(posBody);

    Node *dPipeNode = new Node(dPipe);
   // Node *posPipeNode = new Node(posPipe);

    Node *root = new Node(); // Ausgangsnode


    // Transformationen - in Zukunft mit sinnvollen Keys belegen!
    KeyboardTransformation* bodyRotation = new KeyboardTransformation();
    KeyboardTransformation* towerRotation = new KeyboardTransformation();
    KeyboardTransformation* pipeRotation = new KeyboardTransformation();
//    bodyRotation->setRotKeys(KeyboardTransformation::NoKey,
//                             KeyboardTransformation::NoKey,
//                             'q', 'Q',
//                             KeyboardTransformation::NoKey,
//                             KeyboardTransformation::NoKey);
//    towerRotation->setRotKeys(KeyboardTransformation::NoKey,
//                              KeyboardTransformation::NoKey,
//                              'v', 'V',
//                              KeyboardTransformation::NoKey,
//                              KeyboardTransformation::NoKey);
//    pipeRotation->setRotKeys('h', 'H',
//                             KeyboardTransformation::NoKey,
//                             KeyboardTransformation::NoKey,

//                             KeyboardTransformation::NoKey,
//                             KeyboardTransformation::NoKey
//                          );


    GameLoop* loop = new GameLoop(bodyRotation, towerRotation, pipeRotation);
    loop->doIt();


    // Transformationsnodes

    Node* bodyRotationNode = new Node(bodyRotation);
    Node* towerRotationNode = new Node(towerRotation);
    Node* pipeRotationNode = new Node(pipeRotation);



    // aktuell unnötig, gibt Orientierungn bei Initialisierung an

    //bodyRotation->rotate(0.0,0.0,0.0,0.0);
    //towerRotation->rotate(0.0,0.0,0.0,0.0);
    //pipeRotation->rotate(0.0,0.0,0.0,0.0);



    // Baum aufbauen

    root->addChild(bodyRotationNode);
    bodyRotationNode->addChild(dBodyNode);

    bodyRotationNode->addChild(towerRotationNode);
    towerRotationNode->addChild(dTowerNode);

    towerRotationNode->addChild(pipeRotationNode);
    pipeRotationNode->addChild(dPipeNode);



    // Sinn?
    //schieb->setTransKeysUpper('e', 'r', 't');
    //schiebNode->addChild(rotNode);

/*
    // Keys
    // Loesung fuer Verschieben über KeyboardTransformation
    schieb->setTransKeysUpper('e', 'r', 't');

    // Farben
    c = belmes->getProperty<Color>();
    c->setValue(1.0f, 1.0f, 0.0f, 1.0f);
    c = lArm->getProperty<Color>();
    c->setValue(0.5f, 0.5f, 1.0f, 1.0f);
    c = rArm->getProperty<Color>();
    c->setValue(0.5f, 0.5f, 1.0f, 1.0f);
    c = lFinger->getProperty<Color>();
    c->setValue(1.0f, 0.5f, 0.5f, 1.0f);
    c = rFinger->getProperty<Color>();
    c->setValue(1.0f, 0.5f, 0.5f, 1.0f);
    c = fuss->getProperty<Color>();
    c->setValue(0.0f, 0.8f, 0.0f, 1.0f);
    c = bein->getProperty<Color>();
    c->setValue(0.0f, 0.0f, 0.8f, 1.0f);
    c = torso->getProperty<Color>();
    c->setValue(1.0f, 0.0f, 0.0f, 1.0f);

    // Positionieren
    // Ursprung des Roboters ist das Zentrum seines Torsos
    // Danach müssen sich die Teile positionieren
    belmes->setPosition(0.0, torso->getY() / 2 + belmes->getY() / 2, 0.0);
    bein->setPosition(0.0, -torso->getY() / 2 - bein->getY() / 2, 0.0);
    fuss->setPosition(0.0, -bein->getY() / 2 - fuss->getY() / 2, 0.0);
    lArm->setPosition(torso->getX() / 2 + lArm->getX() / 2, 0.0, 0.0);
    lFinger->setPosition(0.0, -lArm->getY() / 2 - lFinger->getY() / 2, 0.0);
    rArm->setPosition(-torso->getX() / 2 - rArm->getX() / 2, 0.0, 0.0);
    rFinger->setPosition(0.0, -rArm->getY() / 2 - rFinger->getY() / 2, 0.0);

    // Baum aufbauen
    lArmNode->addChild(lFingerNode);
    rArmNode->addChild(rFingerNode);
    torsoNode->addChild(rArmNode);
    torsoNode->addChild(lArmNode);
    torsoNode->addChild(belmesNode);
    torsoNode->addChild(beinNode);
    beinNode->addChild(fussNode);
    rotNode->addChild(torsoNode);
    schiebNode->addChild(rotNode);
*/

    return (root);
}
