OgreCeguiOculusTest
===================

Minimal application by using Ogre3D, CEGUI and OculusSDK.
This is currently for the Windows users.

 Requirement
=============
1. Get source code or SDK package of the following:

- Ogre3D (http://www.ogre3d.org/)
- CEGUI (http://cegui.org.uk/)
- OculusSDK (https://developer.oculusvr.com/ *registration reqruied)

2. Build or locate the above three packages on your local directory.
   (It is reccomended that the packages are examined by using the
    attached test programs.)

 How to build
==============
1. Make sure that the active solution configuration is set to 'Debug'.
2. Open the project's property pages -> C/C++ -> General and change
   the include path of the above packages to your own settings.
3. Open the project's property pages -> Linker -> General and change
   the library path of the above packages to your own settings.
4. Click Build -> Build Solution.

 How to use
============
1. Copy some DLL files from corresponding directories of Ogre3D and
   CEGUI packages to the debug directory of OgreCeguiOculusTest.
   The debug directory already contains the required files, but
   replacing them is recommended.
2. Change the config.cfg file to comfortable to your environment.
   The attached is just example.  If you executed the sample program
   in OculusSDK, useful form can be found in your ogre.cfg file in
   My document -> Ogre -> Byatis.
3. Execute OgreCeguiOculusTest.exe
