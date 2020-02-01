/* MCOM: Driver
  
   Main file for MCOM. Created by Ryan Babij (github.com/RyanBabij/MCOM)
  
  License:
  All code and binaries in MCOM repo are copyrighted.
  Wildcat code is public domain.
*/

#include <string>

#define WILDCAT_USE_OPENGL
//#define WILDCAT_USE_DIRECT3D

   // What OS we are compiling for. Currently only Windows and Linux are supported cos I don't got a Mac.
#include <System/Windows.hpp> //#define WILDCAT_WINDOWS
//#define WILDCAT_LINUX

#define WILDCAT_AUDIO

/* Audio stuffs. */
#include <Audio/Sound.hpp> // Generic sound data handler
#include <Audio/Wav.hpp>
#include <Audio/AudioPlayer.hpp> // Generic audio player
#include <Audio/AudioPlayer_OpenAL.hpp>
/* Global OpenAL audio player. */
AudioPlayer_OpenAL globalAudioPlayer;

Sound * missileLaunch;
Sound * missileExplode;
Sound * missileRIP;
Sound * cityRIP;
Sound * missileGround;

   // DYNAMICALLY GENERATED HEADER FILE WITH STRING WHICH COUNTS COMPILATIONS.
#include "CompileCount.hpp"

#include <iostream>

#include "Driver_Settings.cpp"

#include <Container/Vector/Vector.hpp>

#include <cstdlib>
#include <string>
#include <sstream>

/* Tidies up the game and shuts down. */
void shutDown()
{
   std::cout<<"Driver::shutDown().\n";
   exit(0);
}

//Stolen from https://codereview.stackexchange.com/questions/226/formatter-class
// This allows you to pass multiple datatypes as an std::string.
// Use like this: function( Stream() << "Error Recieved" << 42 << " " << some_code << " '" << some_msg << "'");
class Stream
{
  public:
    std::stringstream ss_;
    // Build a string by chaining << operators.
    template<class Field> Stream& operator<<(Field f)
    {
      ss_ << f;
      return *this;
    }
    // This is a custom typecast to std::string. (C++11)
    operator std::string() const { return ss_.str(); }
};

#define GLEW_STATIC
// Need to figure out which of this is better. I think GLEW is more supported.
#include <Graphics/OpenGL/glew.h> // THIS CURRENTLY FIXES LINKER CRAP. Also allows RGBA_COMPRESSED, it would seem.
#define FREEGLUT_STATIC 
#include <Graphics/OpenGL/freeglut.h> //


#include <Graphics/Render/Renderer.cpp>

#include <Graphics/Texture/Texture.hpp>
#include <Graphics/Texture/TextureLoader.hpp>


#include "Driver_LoadTextures.hpp"

#include <Graphics/Png/Png.hpp>
#include <File/FileManager.hpp>

#include <string>

void printHelp()
{
   std::cout<<"\n\n------------------------------------------\n";
   std::cout<<"\nMCOM"<<VERSION<<".\n";
   std::cout<<"   Warning: This is not a stable release.\n";
   std::cout<<"   This program uses LodePNG.\n";

   std::cout<<"Options:\n";
   std::cout<<"   None.\n";

   std::cout<<"\n------------------------------------------\n";
   std::cout<<"Version "<<VERSION<<".\n";
   std::cout<<"Compiled: "<<__DATE__<<". "<<__TIME__<<".\n";
   std::cout<<"Compile count: "<<COMPILE_COUNT<<".\n";
   std::cout<<"------------------------------------------\n\n";
}

void pauseGame()
{
   std::cout<<"pauseGame() called.\n";
   PAUSE_LOGIC=true;
}

#include <System/Time/Timer.hpp>

/* This object exploits the c++ guarantee that the destructor is always called, in order to deal with unanticipated shutdowns, such as the player clicking the X. However, it seems the destructor guarantee does not apply in some cases, such as ending the process using the task manager, or using ctrl+c from the console. */
class QuitChecker
{
   private:
   Timer gameTime;
   
   public:
   QuitChecker()
   {
      gameTime.init();
      gameTime.start();
    
    // For now we will clear the savedata on startup because it can cause some instability.
    std::cout<<"Deleting temporary data folder ("<<SAVE_FOLDER_PATH<<")\n";
    if (SAVE_FOLDER_PATH.length() > 0 )
    {
      FileManager::deleteDirectory(SAVE_FOLDER_PATH,true);
    }
   }
   ~QuitChecker()
   {
    gameTime.update();
    if (gameTime.seconds > 10 )
    {
      std::cout<<"Time played: "<<gameTime.seconds/60<<" minutes.\n";
    }
    
    if (CLEAN_SAVES_ON_EXIT)
    {
      std::cout<<"Deleting temporary data folder ("<<SAVE_FOLDER_PATH<<")\n";
      if (SAVE_FOLDER_PATH.length() > 0 )
      {
        FileManager::deleteDirectory(SAVE_FOLDER_PATH,true);
      }
    }
      globalAudioPlayer.close();

   }
};
QuitChecker quitChecker;

#include <stdio.h>
#include <Math/Random/GlobalRandom.hpp>
/* No need for a globalRandom object. Just use Random:: */

#include <Graphics/Font/Font.hpp>

// This is the global font for now.
Wildcat::Font font8x8;

#include <Device/Mouse/Mouse.hpp>
Mouse globalMouse;
#include <Device/Keyboard/Keyboard.hpp>
Keyboard globalKeyboard;


#include <System/Time/Timer.hpp>
Timer frameRateTimer;
Timer frameRateTimer2; // Using this till I fix fps output
Timer pollRateTimer;
Timer logicRateTimer;
Timer physicsRateTimer;
Timer animationTimer;
Timer playerKeypressTimer;
Timer gameTimer; /* Runs for duration of game without resetting */
/* Use this for checking algo speeds. */
Timer debugTimer;

#include <Math/Geometry/Geometry.hpp>

#include <Device/Display/DisplayInterface.hpp>
#include <Device/Display/DisplayInterfaceManager.hpp>
/* Global display interface manager, to handle all rendering called by driver. */
DisplayInterfaceManager displayInterfaceManager;

#include <Device/Mouse/MouseInterface.hpp>
#include <Device/Mouse/MouseInterfaceManager.hpp>
/* Global mouse interface manager. To handle all objects that recieve mouse events. */
MouseInterfaceManager mouseInterfaceManager;


#include <Device/Keyboard/KeyboardInterface.hpp>
#include <Device/Keyboard/KeyboardInterfaceManager.hpp>
/* Global keyboard interface manager. To handle all objects that recieve keyboard events. */
KeyboardInterfaceManager keyboardInterfaceManager;

#include <Graphics/GUI/GUI_Manager.hpp>
#include <Graphics/GUI/GUI.hpp>
/* GUI manager. Manages all GUI controls. */
GUI_Manager globalGuiManager;


#include <Interface/LogicTick/LogicTickInterface.hpp>
#include <Interface/LogicTick/LogicTickManager.hpp>
LogicTickManager logicTickManager;

#include <Interface/IdleTick/IdleTickInterface.hpp>
#include <Interface/IdleTick/IdleTickManager.hpp>
IdleTickManager idleManager;


// /* Title Menu / Main Menu */
//Also includes Terminal
#include "Menu_Title.hpp"
Menu_Title menuTitle;

#include "GameScript.cpp"
GameScript gameScript;


/* Initialization goes here. */
#include "Driver_Init.hpp"

/* OpenGL function hooks go here. */
#include "Driver_GLHooks.hpp"

#include <Data/ArgReader.hpp>

int main(int nArgs, char ** arg)
{
   ArgReader argReader;
   argReader.feed(nArgs,arg);
  
   if (argReader.hasTag("-help") || argReader.hasTag("--help") || argReader.hasTag("-h"))
   {
      printHelp();
      return 0;
   }
  
   printHelp();

   GL_init(nArgs, arg);
   
   /* Initialise game. Load textures, fonts etc. */
   init();
  
   /* Reshape is called here. */
   glutMainLoop();
   
   return 0;
}