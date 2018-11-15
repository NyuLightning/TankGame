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

#include "World.h"
#include "tank.h"

Node* initScene1();
UITransformation* rot;

void SceneManager::initScenes()
{
    Ui_RobotDock* lDock;
    QDockWidget* lDockWidget = new QDockWidget(QString("Robot"), SceneManager::getMainWindow());

    ControllableCamera* cam = new ControllableCamera();
    RenderingContext* myContext = new RenderingContext(cam);
    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
    unsigned int myScene = SceneManager::instance()->addScene(initScene1());
    ScreenRenderer* myRenderer = new ScreenRenderer(myContextNr, myScene);
    Q_UNUSED(myRenderer);

    // Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(myScene);
    SceneManager::instance()->setActiveContext(myContextNr);
    //    SceneManager::instance()->setFullScreen();

    cam->setEyePosition(QVector3D(.0,0.0,10.));

    lDock = new Ui_RobotDock();

    lDock->setupUi(lDockWidget);
    lDockWidget->resize(150, 100);
    SceneManager::getMainWindow()->addDockWidget(Qt::RightDockWidgetArea, lDockWidget);
    lDockWidget->show();

    QObject::connect(Window::getInstance(), SIGNAL(sigFPS(int)), lDock->lcdNumber, SLOT(display(int)));
    // Hier können die Signals des UI mit eigenen QObject Slots verbunden werden und umgekehrt
    // Loesung fuer Orientierung ueber GUI mit Qt Signal/Slot
    QObject::connect(lDock->verticalSlider, SIGNAL(valueChanged(int)), rot, SLOT(setXrot(int)));
    QObject::connect(lDock->verticalSlider_2, SIGNAL(valueChanged(int)), rot, SLOT(setYrot(int)));
    QObject::connect(lDock->verticalSlider_3, SIGNAL(valueChanged(int)), rot, SLOT(setZrot(int)));
}

Node* initScene1()
{
    rot = new UITransformation();
    //    Objekte anlegen
    KeyboardTransformation* schieb = new KeyboardTransformation;



    //Welt initialisiereb
    World* world = new World(50.0f,10.0f,50.0f);
    Color* c;

    // Nodes anlegen

    Node* rotNode = new Node(rot);
    Node* schiebNode = new Node(schieb);
    Node* worldNode = new Node(world);

    // Keys
    // Loesung fuer Verschieben über KeyboardTransformation
    schieb->setTransKeysUpper('e', 'r', 't');

    // Farben

    c = world->getProperty<Color>();
    c->setValue(1.0f, 1.0f, 0.0f, 1.0f);

    // Positionieren
    // Ursprung des Roboters ist das Zentrum seines Torsos
    // Danach müssen sich die Teile positionieren
    /*
    belmes->setPosition(0.0, torso->getY() / 2 + belmes->getY() / 2, 0.0);
    bein->setPosition(0.0, -torso->getY() / 2 - bein->getY() / 2, 0.0);
    fuss->setPosition(0.0, -bein->getY() / 2 - fuss->getY() / 2, 0.0);
    lArm->setPosition(torso->getX() / 2 + lArm->getX() / 2, 0.0, 0.0);
    lFinger->setPosition(0.0, -lArm->getY() / 2 - lFinger->getY() / 2, 0.0);
    rArm->setPosition(-torso->getX() / 2 - rArm->getX() / 2, 0.0, 0.0);
    rFinger->setPosition(0.0, -rArm->getY() / 2 - rFinger->getY() / 2, 0.0);
    */
    // Baum aufbauen
    worldNode->addChild(rotNode);
    rotNode->addChild(schiebNode);
    /*
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
    return (schiebNode);
}
