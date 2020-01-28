#pragma once
#ifndef MCOM_DRIVER_INIT_HPP
#define MCOM_DRIVER_INIT_HPP

/* MCOM: Driver_Init.hpp
  #include "Driver_Init.hpp"

Driver initialization goes here.

Initialize main menus, start timers, initialise any important data.

*/

void init()
{   
  Random::seed();

   //Makes cout faster but less reliable
   if ( FAST_COUT )
   {
      std::ios_base::sync_with_stdio(false);
      std::cin.tie(NULL);
   }
   
   globalKeyboard.init(); 

   /* Load textures (Tex pointers from Driver_TextureList.hpp). */
   loadTextures();
  
   /* Load font */
   Png fontPng;
   int fileSize;
   unsigned char* fileData = FileManager::getFile("Textures/Font/8x8/8x8 Transparent v4 plus junk white.png",&fileSize);   
   
   if ( fileData == 0 )
   {
      std::cout<<"ERROR: Font PNG did not load.\n";
   }
   else
   {   
      fontPng.load(fileData,fileSize);
      if(font8x8.loadData(&fontPng,8,8)==false)
      { std::cout<<"ERROR: Font did not load.\n"; }
      delete [] fileData;
   }

   /* Start timers. */
   frameRateTimer.init();
   frameRateTimer.start();
   frameRateTimer2.init();
   frameRateTimer2.start();
   pollRateTimer.init();
   pollRateTimer.start();
   logicRateTimer.init();
   logicRateTimer.start();
   physicsRateTimer.init();
   physicsRateTimer.start();
   animationTimer.init();
   animationTimer.start();
   debugTimer.init();
   debugTimer.start();
  
   playerKeypressTimer.init();
   playerKeypressTimer.start();
   
   gameTimer.init();
   gameTimer.start();

   /* Initialise the main menu */
   menuTitle.setPanel(0,0,RESOLUTIONX,RESOLUTIONY);
   menuTitle.setFont(&font8x8);
   menuTitle.init();
   menuTitle.backgroundTexture=&TEX_TERMINAL;
   menuTitle.active=true;

   mouseInterfaceManager.add(&menuTitle);
   globalGuiManager.add(&menuTitle);
   idleManager.add(&gameScript);
   idleManager.add(&menuTitle);
   
}

#endif
