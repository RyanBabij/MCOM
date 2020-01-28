#pragma once
#ifndef MCOM_PROGRAM_MISSILECOMMAND_CPP
#define MCOM_PROGRAM_MISSILECOMMAND_CPP

/* MCOM: Terminal_Program_MissileCommand
   #include "Terminal_Program_MissileCommand.cpp"
   
   Implementation of Terminal_Program_MissileCommand.hpp.
   
*/

#include "Terminal_Program_MissileCommand.hpp"

Terminal_Program_MissileCommand::Terminal_Program_MissileCommand(Terminal * term): Terminal_Program(term)
{
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
   // if (!active) { return; }
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
std::string Terminal_Program_MissileCommand::render()
{
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