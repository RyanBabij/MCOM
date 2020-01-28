#pragma once
#ifndef MCOM_GAMESCRIPT_CPP
#define MCOM_GAMESCRIPT_CPP

/* MCOM: GameScript
   #include "GameScript.cpp"
   
   Regulates the state of the game, plot, etc.
   Uses IdleTickInterface to update.
*/

#include <Game/Terminal/Terminal.hpp>
#include "Terminal_Program_MissileCommand.cpp"

class GameScript: public IdleTickInterface
{
   public:
   
   Terminal * terminal;
   
   int mainSequence;
   
   std::string strPlayerName;
   
   Timer timerScriptUpdate;
   Timer timerGameTime;
   
   GameScript()
   {
      mainSequence=0;
      terminal = &menuTitle.terminal;
      strPlayerName="";
      
      timerScriptUpdate.init();
      timerScriptUpdate.start();
      
      timerGameTime.init();
      timerGameTime.start();
      
      terminal->cursorVisible=false;
      terminal->amountStatic=0;
   }
   
   void idleTick()
   {
      if (terminal==0) { return; }
      
      terminal->amountStatic=0;
      terminal->fill(0,0,0,0);
      return;
     
   }
};

#endif