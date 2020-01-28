#pragma once
#ifndef MCOM_PROGRAM_MISSILECOMMAND_HPP
#define MCOM_PROGRAM_MISSILECOMMAND_HPP

/* MCOM: Terminal_Program_MissileCommand
   #include "Terminal_Program_MissileCommand.hpp"
   
   Missile Command is a small game to demo my Terminal emulator.
   
   It's basically the same as the original game. Use the mouse
   cursor to aim, and shoot from one of three missile batteries
   using the A S D keys.
   
   Missiles will rain down, getting faster over time. The player's
   job is to shoot them down using their three counter-missile
   batteries.
   
   Unlike the original, there are no waves, the game continues
   until all the cities are destroyed.
   
   Sometimes a plane will fly overhead and drop bombs. Both the
   plane and bombs can be destroyed.
   
*/

class City
{
   // we may want to implement a sprite class for Terminal
   public:
   
   // texture
   // state
   // audio files
   
   City()
   {
   }
};

#include <Game/Terminal/Terminal_Program.cpp>

class Terminal_Program_MissileCommand: public Terminal_Program
{
   public:
   
   bool city1;
   bool city2;

   Terminal_Program_MissileCommand(Terminal * ptrTerminal);
   
   std::string init (Vector <std::string>* vArg) override;
   
   std::string render() override;
   
   //run the code for 1 emulated cycle returns possible output
   void cycle() override;
   //void execute(int lineNumber);
   
   void keyboardEvent (Keyboard* _keyboard) override;

};


#endif