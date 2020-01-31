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
      if ( isDestroyed )
      {
         return &TEX_MCOM_CITY_RIP;
      }
      return &TEX_MCOM_CITY;
   }
   
   void getHit(const int missileX)
   {
      if (isCollisionX(missileX))
      {
         isDestroyed=true;
      }
   }
};

class Missile: public Sprite
{
   public:
   
   short int sourceX,targetX;
   
   double currentX;
   
   double currentY;
   
   double speedX,speedY;
   // maybe speedy is always 1, and speedx is variable from 0-1 (up to 45 degrees)
   Vector <double> vTrailX;
   Vector <double> vTrailY;
   // each missile leaves a trail which disappears after being destroyed
   
   unsigned short int blastSize; // counts up for x frames after impact.
   
   virtual ~Missile()
   {
   }
   Missile(unsigned short int _sourceX, unsigned short int _targetX, double speed)
   {
      sourceX=_sourceX;
      targetX=_targetX;
      
      currentX=sourceX;
      currentY=199;
      
      speedY=speed;
      speedX = targetX-sourceX;
      //speedX = speedX/(200*speedY);
      speedX = speedX/(200/speedY);
      
      //missile will always move down by 1 y pixel per cycle, however
      // x movement is variable. y height is fixed at 200px, so we can
      // easily calculate the x movement per tick.
      
      x1=sourceX;
      x2=sourceX+1;
      y1=199;
      y2=198;
      
      blastSize=0;
      
      vTrailX.push(currentX);
      vTrailY.push(currentY);
   }
   virtual Texture* currentTexture() override
   {
      return &texMissile;
   }
   
   void cycle()
   {
      if (currentY==0)
      {
         if ( blastSize != 0 )
         {
            ++blastSize;
            if (blastSize==10)
            {
               blastSize=0;
            }
         }
         return;
      }
      currentY-=speedY;
      if (currentY<=0)
      {
         currentY=0;
         
         // impact
         ++blastSize;
      }
      
      y1=currentY;
      y2=currentY+1;
      
      currentX+=speedX;
      x1=currentX;
      x2=x1+1;
      
      vTrailX.push(currentX);
      vTrailY.push(currentY);
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
      if ( isDestroyed )
      {
         return &TEX_MCOM_MISSILE_RIP;
      }
      return &TEX_MCOM_MISSILE;
   }
   
   void getHit(const int missileX)
   {
      if (isCollisionX(missileX))
      {
         isDestroyed=true;
      }
   }
};


#include <Game/Terminal/Terminal_Program.cpp>

#include <Math/Random/RandomLehmer.hpp>

class Terminal_Program_MissileCommand: public Terminal_Program
{
   RandomLehmer rngLehmer;
   
   unsigned long int missileIntensity;
   double minMissileSpeed;
   double missileSpeed; // maximum ySpeed.
   unsigned long int nCycle;
   
   const unsigned char BKG_R=64;
   const unsigned char BKG_G=0;
   const unsigned char BKG_B=128;

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
   
   Vector <Missile*> vMissile;


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