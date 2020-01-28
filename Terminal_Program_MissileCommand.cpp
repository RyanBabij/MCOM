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
   missile1.setCoord(0,0,32,32);
   
   city1.setCoord(32,0,64,16);
   city2.setCoord(64,0,96,16);
   city3.setCoord(96,0,128,16);
   
   missile2.setCoord(128,0,160,32);

   city4.setCoord(160,0,192,16);
   city5.setCoord(192,0,224,16);
   city6.setCoord(224,0,256,16);
   
   missile3.setCoord(256,0,288,32);
   
   terminal->addSprite(&missile1);
   terminal->addSprite(&city1);
   terminal->addSprite(&city2);
   terminal->addSprite(&city3);
   terminal->addSprite(&missile2);
   terminal->addSprite(&city4);
   terminal->addSprite(&city5);
   terminal->addSprite(&city6);
   terminal->addSprite(&missile3);

}

std::string Terminal_Program_MissileCommand::init (Vector <std::string>* vArg)
{
   return "AYY LMAO\n";
}

void Terminal_Program_MissileCommand::cycle() // for now this is being called directly before render()
{
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
   //terminal->fill(255,0,0,255);
   terminal->fill(rngLehmer.rand8(),rngLehmer.rand8(),rngLehmer.rand8(),255);

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

#endif