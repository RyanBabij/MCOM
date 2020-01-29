#pragma once
#ifndef MCOM_PROGRAM_MISSILECOMMAND_HPP
#define MCOM_PROGRAM_MISSILECOMMAND_HPP

/* MCOM: Terminal_Program_MissileCommand
   #include "Terminal_Program_MissileCommand.hpp"
   
   Missile Command is a small game to demo my Terminal emulator.
   
   It's basically the same as the original game. Use the mouse
   cursor to aim, and shoot from one of three missile batteries
   using the A S D keys. Left-click will use the nearest free battery.
   
   Missiles will rain down, getting faster over time. The player's
   job is to shoot them down using their three counter-missile
   batteries.
   
   Unlike the original, there are no waves, the game continues
   until all the cities are destroyed.
   
   Sometimes a plane will fly overhead and drop bombs. Both the
   plane and bombs can be destroyed.
   
*/

class City: public Sprite
{
   // we may want to implement a sprite class for Terminal
   public:
   bool isDestroyed;
   // texture
   // state
   // audio files
   
   City()
   {
      isDestroyed=false;
      //texture = &TEX_MCOM_CITY;
   }
   
    virtual Texture* currentTexture() override
   {
      return &TEX_MCOM_CITY;;
   }
};

class Missile: public Sprite
{
   public:
   
   double speedX,speedY;
   Vector <HasXY*> vTrail;
   
   virtual ~Missile()
   {
   }
   Missile()
   {
   }
   virtual Texture* currentTexture() override
   {
      return &TEX_MCOM_MISSILE;;
   }
   
};

class MissileBase: public Sprite
{
   // we may want to implement a sprite class for Terminal
   public:
   bool isDestroyed;
   // texture
   // state
   // audio files
   
   MissileBase()
   {
      isDestroyed=false;
   }
   
    virtual Texture* currentTexture() override
   {
      return &TEX_MCOM_MISSILE;;
   }
};


#include <Game/Terminal/Terminal_Program.cpp>

#include <Math/Random/RandomLehmer.hpp>

class Terminal_Program_MissileCommand: public Terminal_Program
{
   RandomLehmer rngLehmer;
   public:
   
   City city1;
   City city2;
   City city3;
   City city4;
   City city5;
   City city6;
   
   MissileBase missile1;
   MissileBase missile2;
   MissileBase missile3;
   
   Vector <Missile> vMissile;


   Terminal_Program_MissileCommand(Terminal * ptrTerminal);

   std::string init (Vector <std::string>* vArg) override;

   std::string render() override;

   //run the code for 1 emulated cycle returns possible output
   void cycle() override;
   //void execute(int lineNumber);

   void keyboardEvent (Keyboard* _keyboard) override;
   bool mouseEvent (Mouse* _mouse) override;

};


#endif