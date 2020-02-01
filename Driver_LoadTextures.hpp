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
static Texture TEX_MCOM_CITY_RIP;
static Texture TEX_MCOM_MISSILE;
static Texture TEX_MCOM_MISSILE_RIGHT;
static Texture TEX_MCOM_MISSILE_RIP;

Texture texRuntime; /* Test of runtime graphics creation. */
Texture texMissile;

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
    preloadTextureVerbose("Textures/Game/cityt.png",&TEX_MCOM_CITY);
    preloadTextureVerbose("Textures/Game/cityript.png",&TEX_MCOM_CITY_RIP);
    preloadTextureVerbose("Textures/Game/missilet.png",&TEX_MCOM_MISSILE);
    preloadTextureVerbose("Textures/Game/missilert.png",&TEX_MCOM_MISSILE_RIGHT);
    preloadTextureVerbose("Textures/Game/missileript.png",&TEX_MCOM_MISSILE_RIP);

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
   bindNearestNeighbour(&TEX_MCOM_CITY_RIP,COMPRESS_TEXTURES);
   bindNearestNeighbour(&TEX_MCOM_MISSILE,COMPRESS_TEXTURES);
   bindNearestNeighbour(&TEX_MCOM_MISSILE_RIGHT,COMPRESS_TEXTURES);
   bindNearestNeighbour(&TEX_MCOM_MISSILE_RIP,COMPRESS_TEXTURES);

   texRuntime.create(320,200,0,true);
   texMissile.create(1,1,0,true);
   texMissile.setPixel(0,0,0,0);
   texMissile.setPixel(0,0,1,0);
   texMissile.setPixel(0,0,2,0);
   texMissile.setPixel(0,0,3,255);

    
}

#endif
