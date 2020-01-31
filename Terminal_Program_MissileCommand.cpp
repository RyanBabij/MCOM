#pragma once
#ifndef MCOM_PROGRAM_MISSILECOMMAND_CPP
#define MCOM_PROGRAM_MISSILECOMMAND_CPP

/* MCOM: Terminal_Program_MissileCommand
   #include "Terminal_Program_MissileCommand.cpp"
   
   Implementation of Terminal_Program_MissileCommand.hpp.
   
   Note we don't need to worry about sprite bounding boxes right now because
   incoming missiles only evaluate when they hit the ground.
*/

#include "Terminal_Program_MissileCommand.hpp"

Terminal_Program_MissileCommand::Terminal_Program_MissileCommand(Terminal * term): Terminal_Program(term)
{
   const int CITY_HEIGHT = 16;
   const int MISSILE_HEIGHT = 32;
   
   missile1.setCoord(0,0,32,MISSILE_HEIGHT);
   
   city1.setCoord(32,0,64,CITY_HEIGHT);
   city2.setCoord(64,0,96,CITY_HEIGHT);
   city3.setCoord(96,0,128,CITY_HEIGHT);
   
   missile2.setCoord(128,0,160,MISSILE_HEIGHT);

   city4.setCoord(160,0,192,CITY_HEIGHT);
   city5.setCoord(192,0,224,CITY_HEIGHT);
   city6.setCoord(224,0,256,CITY_HEIGHT);
   
   missile3.setCoord(256,0,288,MISSILE_HEIGHT);
   
   terminal->addSprite(&missile1);
   terminal->addSprite(&city1);
   terminal->addSprite(&city2);
   terminal->addSprite(&city3);
   terminal->addSprite(&missile2);
   terminal->addSprite(&city4);
   terminal->addSprite(&city5);
   terminal->addSprite(&city6);
   terminal->addSprite(&missile3);
   
   missileIntensity=1;
   missileSpeed=1;
   minMissileSpeed=0.5;
   
   // set bkg colour
   //terminal->fill(127,0,255,255);
   terminal->fill(64,0,128,255);

}

std::string Terminal_Program_MissileCommand::init (Vector <std::string>* vArg)
{
   return "AYY LMAO\n";
}

void Terminal_Program_MissileCommand::cycle() // for now this is being called directly before render()
{
   ++nCycle;
   
   for (int i=0;i<vMissile.size();++i)
   {
      // I'm not sure why there's a y-offset but it doesn't surprise me at all.
      terminal->setPixel(vMissile(i)->currentX,vMissile(i)->currentY+1,255,255,255);
      vMissile(i)->cycle();
      //if missile is impacted, draw blast.
   }
   
   if (nCycle %500 == 0)
   {
      ++missileIntensity;
      missileSpeed+=0.1;
   }
   
   for (unsigned long int i=0;i<missileIntensity;++i)
   {
      if (rngLehmer.rand8()<10)
      {
         unsigned int sourceX = rngLehmer.rand32()%320; // 0-319
         unsigned int targetX = rngLehmer.rand32()%320;
         
         
         double speed = minMissileSpeed + ((rngLehmer.rand8()%(int)(missileSpeed*10))/(double)15);
         if ( speed>missileSpeed ) { speed = missileSpeed; }
         
         Missile * m = new Missile(sourceX,targetX,speed);
         vMissile.push(m);
         terminal->addSprite(m);
      }
   }
   
   // long int missileCounter = missileIntensity;
   // while (missileCounter>0)
   // {
      // if ( rngLehmer.rand8() < missileIntensity )
      // {
         // //std::cout<<"ay\n";
         
         // // spawn missile at random x, travelling random trajectory. However trajectory should impact ground somewhere. We can pick a random source x and random target x.
         
         // unsigned int sourceX = rngLehmer.rand32()%320; // 0-319
         // unsigned int targetX = rngLehmer.rand32()%320;
         
         // Missile * m = new Missile(sourceX,targetX);
         // vMissile.push(m);
         // terminal->addSprite(m);
      // }
      // missileCounter-=255;
   // }
   

   
   return;
}

void Terminal_Program_MissileCommand::keyboardEvent (Keyboard* _keyboard)
{
   if (!active) { return; }
   // //std::string allowedInputs = " !@#$%^&*()\"\'\\=+-/";
   // if (easi.isWaitingInput > 0 && _keyboard->keyWasPressed)
   // {
      // if (_keyboard->lastKey == Keyboard::ENTER)
      // {
         // easi.isWaitingInput--;
         // std::cout<<"INPUT is: "<<input<<"\n";
         // easi.vInput.push(input);
         // input="";
         // output+="\n";
         // _keyboard->clearAll();
      // }
      // else if (_keyboard->lastKey == Keyboard::BACKSPACE)
      // {
         // if ( input.size() > 0 ) { input.pop_back(); output+='\b'; }
         // _keyboard->clearAll();
      // }
      // // ANSI lets us pass backspaces, so we can just return whatever keys we recieve.
      // else if (DataTools::isAlphaNumeric(_keyboard->lastKey))
      // {
         // output+=_keyboard->lastKey;
         // input+=_keyboard->lastKey;
         // _keyboard->clearAll();
         // return;
      // }
   // }
}

// Program can return update in text mode, or entire screen in graphics mode.
// Output string should be wiped 
// Might as well just write directly to Terminal screen because that's how they
// used to do it anyways.
std::string Terminal_Program_MissileCommand::render()
{
//   terminal->fill(127,0,255,255);
   // if ( nCycle > 100 )
   // {   terminal->fill(rngLehmer.rand8(),rngLehmer.rand8(),rngLehmer.rand8(),255);
   // }


   //Renderer::placeTexture4(0,0,64,32,&TEX_MCOM_CITY,true);

   return "AYY LMAO\n";
   
   
   // //Protip: We can't necessarily return if inactive, because there may be a final render call
   // // or batch cycles.
   // // Intead just check if we have output to return.
   // if ( output.size()==0 )
   // { return ""; }
   
   // // return a copy of output and wipe the output string.
   // std::string retRender = output;
   // output="";
   // return retRender;
}

bool Terminal_Program_MissileCommand::mouseEvent (Mouse* _mouse)
{
   if (_mouse->isLeftClick)
   {
      if ( terminal->mouseX != -1 && terminal->mouseY != -1 )
      {
         std::cout<<"Missile to "<<terminal->mouseX<<", "<<terminal->mouseY<<"\n";
         _mouse->isLeftClick=false;
         return true;
      }
   }
   return false;
}

#endif