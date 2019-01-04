#include "opengl.h"
#include "screenrenderer.h"
#include "transformation.h"
#include "color.h"

#include "scenemanager.h"
#include "window.h"
#include "uitransformation.h"

#include "ui_robot.h"
#include "trianglemesh.h"
#include "texture.h"

#include "listener.h"
//#include "audioengine.h"
//#include "soundsource.h"
//#include "shadermanager.h"
//#include "efx-presets.h"

#include "inputregistry.h"
#include "gameloop.h"

#include "projectile.h"

#include "idleobserver.h"

#include "screenrenderer.h"
#include "controllablecamera.h"
#include "simpleplane.h"
#include "shadertimed.h"
#include "transformation.h"
#include "shadermanager.h"
#include "modeltransformation.h"

#include "shader.h"
#include "sunlight.h"

#include "enemytank.h"

Node* initScene1();
//UITransformation* rot;

ScreenRenderer* playWindow;
Camera * cam;
PhysicEngine* v_PhysicEngine;

void addShaderHit(Drawable* d)
{
    // Setze Shader wenn Objekt zerstört
    ShaderTimed* redWaveformShader = ShaderManager::getShader<ShaderTimed>("/shaders/wavemotion.vert", "/shaders/hello_glsl.frag");
    redWaveformShader->setMsecsPerIteration(600);
    d->setShader(redWaveformShader);

    // Warte n Sekunden
    //

    // Lösche Objekt nachdem Animation abgelaufen
    //delete d;
}

class KeyListener: public Listener
{
    void keyboard(int key, int modifier)
    {
        if (key == Qt::Key_Escape)
        {
            if (SceneManager::instance()->isInFullScreenMode())
                SceneManager::instance()->setFullScreen(false);
            else
                 SceneManager::instance()->setFullScreen();
        }
    }
};

void SceneManager::initScenes()
{
    KeyListener* keyListener = new KeyListener();
    Ui_RobotDock* lDock;
    QDockWidget* lDockWidget = new QDockWidget(QString("Robot"), SceneManager::getMainWindow());

    // Physic Engine Erzeugen und einen Pointer auf Instanz holen
    int v_Slot = PhysicEngineManager::createNewPhysicEngineSlot(PhysicEngineName::BulletPhysicsLibrary);
    v_PhysicEngine = PhysicEngineManager::getPhysicEngineBySlot(v_Slot);

    cam = new Camera();   
    RenderingContext* myContext = new RenderingContext(cam);
    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
    unsigned int myScene = SceneManager::instance()->addScene(initScene1());
    playWindow = new ScreenRenderer(myContextNr, myScene);
   // Q_UNUSED(playWindow);

    // Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(myScene);
    SceneManager::instance()->setActiveContext(myContextNr);
    SceneManager::instance()->setFullScreen();

    cam->setEyePosition(QVector3D(0.0,10.0,30.));

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

    // Welt
    Geometry* gWorld = new TriangleMesh(path + QString("/../Models/world.obj"));
    Drawable* dWorld = new Drawable(gWorld);
    Node *dWorldNode = new Node(dWorld);
    Transformation *posWorld = new Transformation();
    posWorld->translate(0.0,-1.0,0.0);
    posWorld->scale(2,2,2);
    Node *worldTranslationNode = new Node(posWorld);

    // Panzerteile
    Geometry* gTower = new TriangleMesh(path + QString("/../Models/turret.obj"));
    Geometry* gBody = new TriangleMesh(path + QString("/../Models/chassis.obj"));
    Geometry* gPipe = new TriangleMesh(path + QString("/../Models/barrel.obj"));

    Drawable* dTower = new Drawable(gTower);
    Drawable* dBody = new Drawable(gBody);
    Drawable* dPipe = new Drawable(gPipe);

    Texture *t;

    // Material
    Material* m;
    m = dWorld->getProperty<Material>();
    m->setDiffuse(0.4f, .5f, .2f, 1.f);
    m->setAmbient(0.2f, .3f, .1f, 1.f);
    m->setSpecular(0.8f, .8f, .8f, 1.f);
    m->setShininess(8.f);
    dWorld->setShader(ShaderManager::getShader(QString("/shaders/PhongFragment.vert"), QString("/shaders/PhongFragment.frag")));

    // Lichtquelle
    SunLight* theLight = new SunLight;
    Node* theLightNode = new Node(theLight);
    theLight->setDiffuse(0.7f, 0.7f, 0.7f);
    theLight->setSpecular(0.6f, 0.6f, 0.6f);
    theLight->setAmbient(0.6f, 0.6f, 0.6f);
    theLight->turnOn();


    // Shader laden
    Shader* s = ShaderManager::getShader("/shaders/texture.vert","/shaders/texture.frag");


    // Texturen laden
    t = dTower->getProperty<Texture>();
    t->loadPicture(path + QString("/../Textures/Unbekannt.png"));

    t = dBody->getProperty<Texture>();
    t->loadPicture(path + QString("/../Textures/Unbekannt2.png"));

    t = dPipe->getProperty<Texture>();
    t->loadPicture(path + QString("/../Textures/Unbekannt3.png/"));

    t = dWorld->getProperty<Texture>();
    t->loadPicture(path + QString("/../Textures/World_Diffuse.png"));

    //Shader fuer Textur setzen
    dWorld->setShader(s);

    // Shader
    dWorld->setShader(s);
    dBody->setShader(s);
    dPipe->setShader(s);
    dTower->setShader(s);

    // Transformationen
    Transformation* bodyRotation = new Transformation();
    Transformation* towerRotation = new Transformation();
    Transformation* pipeRotation = new Transformation();

    // Nodes anlegen
    Node *root = new Node(); // Ausgangsnode
    Node *dTowerNode = new Node(dTower);
    Node *dBodyNode = new Node(dBody);
    Node *dPipeNode = new Node(dPipe);    

    Node* bodyRotationNode = new Node(bodyRotation);
    Node* towerRotationNode = new Node(towerRotation);
    Node* pipeRotationNode = new Node(pipeRotation);    

    GameLoop* loop = new GameLoop(bodyRotation, towerRotation, pipeRotation, cam, root, v_PhysicEngine);

    //Boden
    Drawable* v_Plane = new Drawable(new SimplePlane(100));
    v_Plane->setStaticGeometry(true);
    Transformation* v_TransformationPlane = new Transformation();
    Node* transformationPlaneNode = new Node(v_TransformationPlane);
    v_TransformationPlane->translate(0,-1.2,0);
    v_TransformationPlane->rotate(-90.f, 1.f, 0.f, 0.f);
    PhysicObject* v_PlanePhys = v_PhysicEngine->createNewPhysicObject(v_Plane);
    PhysicObjectConstructionInfo* v_Constrinf = new PhysicObjectConstructionInfo();
    v_Constrinf->setCollisionHull(CollisionHull::BoxAABB); // Automatische generierung einer Box aus den Vertexpunkten
    v_PlanePhys->setConstructionInfo(v_Constrinf);
    v_PlanePhys->registerPhysicObject();
    transformationPlaneNode->addChild(new Node(v_Plane));

    root->addChild(transformationPlaneNode);

    // Baum aufbauen
    root->addChild(theLightNode);
    theLightNode->addChild(bodyRotationNode);
    bodyRotationNode->addChild(dBodyNode);

    bodyRotationNode->addChild(towerRotationNode);
    towerRotationNode->addChild(dTowerNode);

    towerRotationNode->addChild(pipeRotationNode);
    pipeRotationNode->addChild(dPipeNode);

    theLightNode->addChild(worldTranslationNode);
    worldTranslationNode->addChild(dWorldNode);

    return (root);
}
