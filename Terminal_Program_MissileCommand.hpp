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

#include <Math/Geometry/Geometry.hpp> // for math vectors

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
   }
   
   virtual Texture* currentTexture() override
   {
      if ( isDestroyed )
      {
         return &TEX_MCOM_CITY_RIP;
      }
      return &TEX_MCOM_CITY;
   }
   
   void getHit(const int missileX, const int missileY)
   {
      if ( isDestroyed ) { return; }
      if (isCollisionX(missileX) && missileY <= 1)
      {
         isDestroyed=true;
         globalAudioPlayer.playSoundOnce(cityRIP);
      }
   }
};

const int MAX_BLAST =11;

class Missile: public Sprite
{
   double slope;
   
   MathVector2D <double> velocity;
         
   public:
   
   short int sourceX,sourceY,targetX,targetY;
   
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
   Missile(unsigned short int _sourceX, unsigned short int _sourceY, unsigned short int _targetX, unsigned short int _targetY, double speed)
   {
      sourceX=_sourceX;
      sourceY=_sourceY;
      targetX=_targetX;
      targetY=_targetY;

      // convert source,target into velocity vector.
      velocity.set(_sourceX,_sourceY,_targetX,_targetY);
      velocity.normalise();
      velocity.setMagnitude(speed);
      //std::cout<<"Vector from: "<<_sourceX<<", "<<_sourceY<<" to "<<_targetX<<", "<<_targetY<<"\n";
      //std::cout<<"Velocity: "<<vector.getXChange()<<", "<<vector.getYChange()<<"\n";


      int distanceY = _sourceY - _targetY;
      int distanceX = sourceX - _targetX;
      
      if ( distanceX == 0 && distanceY == 0 )
      {
         slope=0;
      }
      else if (distanceX == 0 )
      {
         slope=1;
      }
      else if (distanceY == 0 )
      {
         slope=0;
      }
      else
      {
         slope = (double)distanceX/distanceY;
      }

      currentX=sourceX;
      currentY=sourceY;
      
      speedY=speed;
      
      speedX = targetX-sourceX;
      //speedX = speedX/(200*speedY);
      speedX = speedX/(distanceY/speedY);
      
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
      // explosion stuff
      if (blastSize!=0) // if missile is exploding
      {
         if (blastSize<MAX_BLAST)
         {
            ++blastSize;
         }
         else
         {
            
         }
         
         // explosion calcs
         
         return;
      }
      
      // move along vector
      currentX+=velocity.getXChange();
      currentY+=velocity.getYChange();
      
      // impact and blast calculations go here
      
      // correct coordinates to prevent overshoot.
      if ( (velocity.xChange() >= 0 && currentX >= targetX)
      || (velocity.xChange() <= 0 && currentX <= targetX ))
      {
         currentX=targetX;
      }
      if ( (velocity.yChange() >= 0 && currentY >= targetY)
      || (velocity.yChange() <= 0 && currentY <= targetY ))
      {
         currentY=targetY;
      }
      
      if ( (int)currentX == targetX && (int)currentY == targetY )
      {
         blastSize=1;
         globalAudioPlayer.playSoundOnce(missileExplode);
      }
      
      y1=currentY;
      y2=currentY+1;

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
   bool isLeft; // facing left
   // texture
   // state
   // audio files
   
   unsigned char launchX,launchY; // pixel offset to launch from
   
   MissileBase()
   {
      isDestroyed=false;
      isLeft=true;
      launchX = 16;
      launchY = 5;
   }
   
   virtual Texture* currentTexture() override
   {
      if ( isDestroyed )
      {
         return &TEX_MCOM_MISSILE_RIP;
      }
      if ( isLeft )
      {
      return &TEX_MCOM_MISSILE;
      }
            return &TEX_MCOM_MISSILE_RIGHT;

   }
   
   void getHit(const int missileX, const int missileY)
   {
      if ( isDestroyed ) { return; }
      if (isCollisionX(missileX) && missileY <= 1)
      {
         isDestroyed=true;
         globalAudioPlayer.playSoundOnce(missileRIP);
      }
   }
};


#include <Game/Terminal/Terminal_Program.cpp>

#include <Math/Random/RandomLehmer.hpp>

class Terminal_Program_MissileCommand: public Terminal_Program
{
   RandomLehmer rngLehmer;
   
   bool intro; // true when player starts game
   bool gameOver; // true if game is finished
   
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
   
   bool launch(MissileBase* mb); // launch missile from designated launcher
   // returns false if unable

   void keyboardEvent (Keyboard* _keyboard) override;
   bool mouseEvent (Mouse* _mouse) override;

};


#endif