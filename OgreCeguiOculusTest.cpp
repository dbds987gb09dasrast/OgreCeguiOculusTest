#include "windows.h"
#include "ogre.h"
#include "OIS.h"
#include "MiniOgreClass02.h"
#include "OgreEuler.h"

#undef new

using namespace Ogre;

const float g_eyeHeight = 1.7f;
const float g_walkSpeed = 5.0f;
const float g_turnSpeed = 0.003f;

Ogre::Euler        g_bodyOrientation;
Vector3            g_bodyPosition(0,0,0);
Quaternion         g_headOrientation(1,0,0,0);
bool               g_flying=false;
Ogre::Euler        g_sinbadLook;
Ogre::Bone        *g_sinbadHead;

//CEGUI::OgreRenderer* mRenderer;

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT ){
	try{
		// Create Root
		Root *root = new Ogre::Root("plugins_d.cfg","config.cfg","ogre_d.log");
		RenderWindow *window;

		// Display the configuration dialog
		if(!root->showConfigDialog()){
			// The user selected cancel, so clean up and exit
			delete root;
			return 1;
		}

		// Initialise the ogre root. This creates a window (or fullscreen)
		window = root->initialise(true, "Oculus");

		// Create a scene manager (the octree manager in this case)
		SceneManager *sceneManager = root->createSceneManager("OctreeSceneManager");

		// manual configuration
		//ogre
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("media/Sinbad.zip","Zip");
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("media/sibenik.zip","Zip");
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("media","FileSystem");

		//cegui
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("datafiles/imagesets", "FileSystem", "Imagesets");
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("datafiles/fonts", "FileSystem", "Fonts");
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("datafiles/schemes", "FileSystem", "Schemes");
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("datafiles/looknfeel", "FileSystem", "LookNFeel");
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("datafiles/layouts", "FileSystem", "Layouts");
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
		
		// this position is ok
		MiniOgreClass moc;
		moc.setupOculusRift();
		moc.setupOgre(sceneManager, window);
		moc.getCameraNode()->setPosition(0.0f,1.7f,10.0f);

		/* put down some rendering procedures here */

		// init. cegui
		moc.setupCegui(window);

		//prepare input methods
		moc.setupInputMethod(window);

		// Add a light.
		Light *light = sceneManager->createLight("light");
		light->setType(Light::LT_DIRECTIONAL);
		light->setDirection(-0.577,-0.577,-0.577);
		light->setDiffuseColour(ColourValue::White);
		sceneManager->setAmbientLight(ColourValue(0.4f,0.4f,0.4f));
		
		// Add the level mesh.
		SceneNode *node;
		Entity *ent;
		ent = sceneManager->createEntity("sibenik.mesh");
		node = sceneManager->getRootSceneNode()->createChildSceneNode();
		node->attachObject(ent);
		
		ent = sceneManager->createEntity("sinbad.mesh");
		ent->getAnimationState("Dance")->setEnabled(true);
		node = sceneManager->getRootSceneNode()->createChildSceneNode();
		node->setScale(0.25f,0.25f,0.25f);
		node->setPosition(10.7, 1.25, 0);
		node->yaw(Ogre::Degree(90));
		node->attachObject(ent);
		
		g_bodyPosition = Vector3(15.8f, g_eyeHeight, 0.0f);
		g_bodyOrientation.yaw(Ogre::Degree(90));

		// Get the current time.(this is for the animation)
		unsigned long last = root->getTimer()->getMilliseconds();
		unsigned long now=last;
		
		// Loop while the ogre window is open
		while(!window->isClosed()){
			MSG msg;
			// Check for windows messages
			while( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) ){
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			
			last = now;
			now = root->getTimer()->getMilliseconds();
			float deltaT = (now-last)/1000.0f;

			moc.getKeyboard()->capture();
			//moc.getMouse()->capture();
			Vector3 translate(0,0,0);

			if(moc.exitCalled()){
				break;
			}

			if(moc.getKeyboard()->isKeyDown(OIS::KC_ESCAPE)){
				break;
			}

			/*
			g_bodyOrientation.yaw(Radian(-g_mouse->getMouseState().X.rel*g_turnSpeed));
			if(!moc.isOculusReady()){
				g_bodyOrientation.pitch(Radian(-g_mouse->getMouseState().Y.rel*g_turnSpeed));
				g_bodyOrientation.limitPitch(Ogre::Degree(90));
			}
			g_bodyPosition+= g_bodyOrientation*(translate*deltaT);
			*/

			// Add deltaT to the ninja's animation (animations don't update automatically)
			ent->getAnimationState("Dance")->addTime(deltaT);

			if(!g_flying){
				g_bodyPosition.y = g_eyeHeight;
			}
			moc.getCameraNode()->setPosition(g_bodyPosition);
			moc.getCameraNode()->setOrientation(g_bodyOrientation.toQuaternion() * moc.getOrientation());

			// Render the scene
			root->renderOneFrame();
			// Perform a 1ms sleep. This stops the app from hogging the cpu, and also
			// stops some gfx cards (like my previous one) from overheating
			Sleep(1);
		}
		
		//CEGUI::OgreRenderer::destroySystem();  //********************************************

		// Clean up and exit
		moc.shutDownInputMethod();
		moc.shutDownCegui();
		moc.shutDownOgre();
		moc.shutDownOculus();

		delete root;
	}
	catch( Ogre::Exception& e )
	{
		MessageBox( NULL, e.getFullDescription().c_str(), "An Ogre exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}
	catch(...)
	{
		MessageBox( NULL, "An exception has occured!", "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}
	return 0;
}
