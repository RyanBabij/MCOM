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

#include <Math/Random/RandomLehmer.hpp>


class GameScript: public IdleTickInterface, public LogicTickInterface
{
   RandomLehmer rngLehmer;
   public:
   
   Terminal * terminal;
   
   int mainSequence;
   
   std::string strPlayerName;
   
   Timer timerScriptUpdate;
   Timer timerGameTime;
   
   Terminal_Program_MissileCommand mcom;
   
   GameScript(): mcom(&menuTitle.terminal)
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
      
      mcom.active=true;
     terminal->addProgram(&mcom);
   }
   
   void idleTick() override
   {
      if (terminal==0) { return; }
      

      //terminal->amountStatic=255;
   //   terminal->fill(rngLehmer.rand8(),rngLehmer.rand8(),rngLehmer.rand8(),255);
      
      //std::cout<<(int)rngLehmer.rand8()<<"\n";
      return;
     
   }
   
   void logicTick() override
   {
      mcom.cycle();
   }
   
};

#endif