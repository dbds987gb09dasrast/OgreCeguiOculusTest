/// Copyright (C) 2013 Kojack
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
/// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
/// DEALINGS IN THE SOFTWARE.

#pragma once

#include "OgreQuaternion.h"
#include "OgreVector3.h"

namespace OVR
{
	class HMDDevice;
	class SensorFusion;
	class DeviceManager;
	class SensorDevice;

	namespace Util
	{
		namespace Render
		{
			class StereoConfig;
		}
	}
}

namespace Ogre
{
	class SceneManager;
	class RenderWindow;
	class Camera;
	class SceneNode;
	class Viewport;
	class CompositorInstance;
}

namespace CEGUI
{
	class OgreRenderer;
	class EventArgs;
}

namespace OIS
{
	class InputManager;
	class Keyboard;
//	class Mouse;
}

class MiniOgreClass
{
public:
	MiniOgreClass(void);
	~MiniOgreClass(void);
	bool setupOculusRift();
	bool setupOgre(Ogre::SceneManager *sm, Ogre::RenderWindow *win, Ogre::SceneNode *parent = 0);
	bool setupCegui(Ogre::RenderWindow *wnd);
	bool setupInputMethod(Ogre::RenderWindow *win);
	void shutDownOculus();
	void shutDownOgre();
	void shutDownCegui();
	void shutDownInputMethod();
	bool isOgreReady() const;
	bool isOculusReady() const;

	bool quit(const CEGUI::EventArgs &e);
	bool exitCalled();

	void update();
	Ogre::SceneNode *getCameraNode();
	Ogre::Quaternion getOrientation() const;
	Ogre::CompositorInstance *getCompositor(unsigned int i);
	float getCentreOffset() const;
	void resetOrientation();
	
	OIS::Keyboard* getKeyboard();
	//OIS::Mouse* getMouse();

protected:
	//oculus
	bool m_oculusReady;		/// Has the oculus rift been fully initialised?
	OVR::DeviceManager *m_deviceManager;
	OVR::HMDDevice *m_hmd;
	OVR::Util::Render::StereoConfig *m_stereoConfig;
	OVR::SensorDevice *m_sensor;
	OVR::SensorFusion *m_sensorFusion;

	//ogre
	bool m_ogreReady;		/// Has ogre been fully initialised?
	Ogre::SceneManager *m_sceneManager;
	Ogre::RenderWindow *m_window;
	Ogre::SceneNode *m_cameraNode;
	Ogre::Quaternion m_orientation;
	float m_centreOffset;	/// Projection centre offset.
	Ogre::Camera *m_cameras[2];
	Ogre::Viewport *m_viewports[2];
	Ogre::CompositorInstance *m_compositors[2];

	//cegui
	CEGUI::OgreRenderer* mRenderer;

	OIS::InputManager *m_inputManager;
	OIS::Keyboard     *m_keyboard;
	//OIS::Mouse        *m_mouse;

	bool m_exitCalled;
};
