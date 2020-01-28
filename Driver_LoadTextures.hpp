#pragma once
#ifndef MCOM_LOAD_TEXTURES_HPP
#define MCOM_LOAD_TEXTURES_HPP

#include <string>

#define THREADED_TEXTURE_LOADING
#if defined THREAD_ALL || defined THREADED_TEXTURE_LOADING
  #include <thread>
#endif

#include <Graphics/Texture/TextureLoader.hpp>
#include <Graphics/Texture/Texture.hpp>

/* MCOM: Driver_LoadTextures.hpp
  #include "Driver_LoadTextures.hpp"

   Called from Driver::init().
   These vars are global.
   All texture refs start with TEX_, and then use the path and filename from the textures folder.
   Requires OpenGL headers.
   Note that the font data is loaded elsewhere.
*/

void SetColor(int value){
#ifdef WILDCAT_WINDOWS
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);
#endif
}


static Texture TEX_TERMINAL;
static Texture TEX_TERMINAL_GRID;
static Texture TEX_TERMINAL_BKG;

static Texture TEX_MCOM_CITY;
static Texture TEX_MCOM_MISSILE;

Texture texRuntime; /* Test of runtime graphics creation. */


void loadTextureVerbose(const std::string _path, Texture* _texture)
{
   std::cout<<"Loading: "<<_path<<".\n";
   
   if(loadTextureNearestNeighbour(_path,_texture)==false)
   { std::cout<<"Error loading "<<_path<<".\n"; }
}

void preloadTextureVerbose(const std::string _path, Texture* _texture)
{

   
   if(loadTextureNearestNeighbour(_path,_texture)==false)
   {
      SetColor(4);
      std::cout<<"Loading: "<<_path<<": FAIL.\n";
      SetColor(7);
  }
  else
  {
    std::cout<<"Loading: "<<_path<<": SUCCESS.\n";
  }

}


void loadTextures() // Testing some multithreading here. Probably shouldn't because a texture atlas would be better
{
  
//#undef THREADED_TEXTURE_LOADING
#if defined THREAD_ALL || defined THREADED_TEXTURE_LOADING
  std::thread t1( []
  {
#endif
      // LOAD MENU TEXTURES
    //preloadTextureVerbose("Textures/HaruhiTerminal2.png",&TEX_TERMINAL);
    //preloadTextureVerbose("Textures/43Grid.png",&TEX_TERMINAL_GRID);
    //preloadTextureVerbose("Textures/Background5.png",&TEX_TERMINAL_BKG);
    preloadTextureVerbose("Textures/Game/cityt.png",&TEX_MCOM_CITY);
    preloadTextureVerbose("Textures/Game/missilet.png",&TEX_MCOM_MISSILE);

#if defined THREAD_ALL || defined THREADED_TEXTURE_LOADING
  });
  
  std::thread t2( []
  {
#endif

#if defined THREAD_ALL || defined THREADED_TEXTURE_LOADING
  });
#endif
    
    
#if defined THREAD_ALL || defined THREADED_TEXTURE_LOADING
  t1.join();
  t2.join();
#endif

  bindNearestNeighbour(&TEX_MCOM_CITY,COMPRESS_TEXTURES);
  bindNearestNeighbour(&TEX_MCOM_MISSILE,COMPRESS_TEXTURES);
  
  //bindNearestNeighbour(&TEX_TERMINAL_GRID,COMPRESS_TEXTURES);
  //bindNearestNeighbour(&TEX_TERMINAL_BKG,COMPRESS_TEXTURES);
  
  texRuntime.create(320,200,0,true);

    
}

#endif
