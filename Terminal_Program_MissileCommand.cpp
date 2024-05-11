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
   intro=true;
   gameOver=false;
   
   const int CITY_HEIGHT = 16;
   const int MISSILE_HEIGHT = 32;
   
   missile1.setCoord(0,0,32,MISSILE_HEIGHT);
   missile1.isLeft=false;
   
   city1.setCoord(40,0,72,CITY_HEIGHT);
   city2.setCoord(72,0,104,CITY_HEIGHT);
   city3.setCoord(104,0,136,CITY_HEIGHT);
   
   missile2.setCoord(144,0,176,MISSILE_HEIGHT);

   city4.setCoord(184,0,216,CITY_HEIGHT);
   city5.setCoord(216,0,248,CITY_HEIGHT);
   city6.setCoord(248,0,280,CITY_HEIGHT);
   
   missile3.setCoord(288,0,320,MISSILE_HEIGHT);
   
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

   terminal->fill(BKG_R, BKG_G, BKG_B,255);

}

std::string Terminal_Program_MissileCommand::init (Vector <std::string>* vArg)
{
   return "AYY LMAO\n";
}

void Terminal_Program_MissileCommand::cycle() // for now this is being called directly before render()
{
	terminal->clearScreen(true);
   if (gameOver)
   {
      std::string strTime = DataTools::toString(gameTimer.fullSeconds);
      terminal->putString(0,1,"GAME OVER. FINAL TIME: "+strTime);
      return;
   }
   
   else if ( intro )
   {
      terminal->putString(0,0,"YOUR CITIES ARE BEING BOMBED");
      terminal->putString(0,2,"LEFT CLICK TO SHOOT INCOMING MISSILES");
      terminal->putString(0,4,"PRESS SPACE TO BEGIN");
      return;
   }
   else
   {
      gameTimer.update();
      std::string strTime = DataTools::toString(gameTimer.seconds);
      terminal->putString(0,0,strTime);
   }

   //terminal->setTextOverlay(strTime);
   
   ++nCycle;
   
   for (int i=0;i<vMissile.size();++i)
   {
      if (vMissile(i)==0) { continue; }
      
      // I'm not sure why there's a y-offset but it doesn't surprise me at all.
      terminal->setPixel(vMissile(i)->currentX,vMissile(i)->currentY+1,180,180,180);
      vMissile(i)->cycle();
      
      // if missile impacts, clear it's trail.
      if (vMissile(i)->blastSize==1)
      {
         for (int i2=0;i2<vMissile(i)->vTrailX.size();++i2)
         {
            terminal->setPixel(vMissile(i)->vTrailX(i2),vMissile(i)->vTrailY(i2)+1,BKG_R, BKG_G, BKG_B);
         }
         
         // check X collision
         city1.getHit(vMissile(i)->currentX,vMissile(i)->currentY);
         city2.getHit(vMissile(i)->currentX,vMissile(i)->currentY);
         city3.getHit(vMissile(i)->currentX,vMissile(i)->currentY);
         city4.getHit(vMissile(i)->currentX,vMissile(i)->currentY);
         city5.getHit(vMissile(i)->currentX,vMissile(i)->currentY);
         city6.getHit(vMissile(i)->currentX,vMissile(i)->currentY);
         
         missile1.getHit(vMissile(i)->currentX,vMissile(i)->currentY);
         missile2.getHit(vMissile(i)->currentX,vMissile(i)->currentY);
         missile3.getHit(vMissile(i)->currentX,vMissile(i)->currentY);
         
         // check gameover
         
         if (city1.isDestroyed && city2.isDestroyed && city3.isDestroyed && city3.isDestroyed
         &&  city4.isDestroyed && city5.isDestroyed && city6.isDestroyed)
         {
            gameOver=true;
         }

      }
      
      if ( vMissile(i)->blastSize>0)
      {
         int mX =vMissile(i)->currentX;
         int mY =vMissile(i)->currentY;
         int blastSize = vMissile(i)->blastSize;
         
         // draw blast circle
         // stolen from https://stackoverflow.com/questions/1201200/fast-algorithm-for-drawing-filled-circles
         for(int y=-blastSize; y<=blastSize; y++)
         {
             for(int x=-blastSize; x<=blastSize; x++)
             {
                 if(x*x+y*y <= blastSize*blastSize)
                 {
                     terminal->setPixel(mX+x, mY+y,255,0,0);
                     vMissile(i)->vTrailX.push(mX+x);
                     vMissile(i)->vTrailY.push(mY+y-1);
                     
                        for (int i2=0;i2<vMissile.size();++i2)
                        {
                           if ( i2==i || vMissile(i2) == 0 ) { continue;}
                           if ( (int)vMissile(i2)->currentX == mX+x &&
                           (int)vMissile(i2)->currentY == mY+y )
                           {
                              terminal->removeSprite(vMissile(i2));
                              // delete trail
                              for (int i3=0;i3<vMissile(i2)->vTrailX.size();++i3)
                              {
                                 terminal->setPixel(vMissile(i2)->vTrailX(i3),vMissile(i2)->vTrailY(i3)+1,BKG_R, BKG_G, BKG_B);
                              }
                              delete vMissile(i2);
                              vMissile(i2)=0;
                           }
                        }
                 }
             }
         }

      }

   }
   
   // remove exploded missiles
   for (int i=0;i<vMissile.size();++i)
   {
      if (vMissile(i) == 0 ) { continue; }
      if (vMissile(i)->blastSize == MAX_BLAST )
      {
            terminal->removeSprite(vMissile(i));
            for (int i2=0;i2<vMissile(i)->vTrailX.size();++i2)
            {
               terminal->setPixel(vMissile(i)->vTrailX(i2),vMissile(i)->vTrailY(i2)+1,BKG_R, BKG_G, BKG_B);
            }
            delete vMissile(i);
            vMissile(i)=0;
      }
      
    // //  std::cout<<".";
        // // // std::cout<<"Pixelcolour: "<<(int)terminal->getPixel(vMissile(i)->currentX,vMissile(i)->currentY,0)<<"\n";
      // else if (terminal->getPixel(vMissile(i)->currentX,vMissile(i)->currentY,0) == 255 )
      // {
                              // terminal->removeSprite(vMissile(i));
                              // // delete trail
                              // for (int i3=0;i3<vMissile(i)->vTrailX.size();++i3)
                              // {
                                 // terminal->setPixel(vMissile(i)->vTrailX(i3),vMissile(i)->vTrailY(i3)+1,BKG_R, BKG_G, BKG_B);
                              // }
                              // delete vMissile(i);
                              // vMissile(i)=0;
      // }
   }
   
   vMissile.removeNulls();
  // std::cout<<"Currentmissiles: "<<vMissile.size()<<"\n";
   
   if (nCycle %100 == 0)
   {      SET_ANIMATION_SPEED(ANIMATION_PER_SECOND+1);
   }
   
   if (nCycle %800 == 0)
   {
      ++missileIntensity;
      missileSpeed+=0.1;

   }
   
  // MAX_BLAST
   // garbage collect missiles
   for (int i=0;i<vMissile.size();++i)
   {
      //if ( vMissile.
   }

   for (unsigned long int i=0;i<missileIntensity;++i)
   {
      if (rngLehmer.rand8()<4)
      {
         unsigned int sourceX = rngLehmer.rand32()%320; // 0-319
         unsigned int targetX = rngLehmer.rand32()%320;
         
         
         double speed = minMissileSpeed + ((rngLehmer.rand8()%(int)(missileSpeed*10))/(double)15);
         if ( speed>missileSpeed ) { speed = missileSpeed; }
         
         Missile * m = new Missile(sourceX,199,targetX,0,speed);
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
   if (_keyboard->keyWasPressed)
   {
      if (_keyboard->lastKey == Keyboard::SPACE && intro)
      {
		 // std::cout<<"Cancelling intro\n";
         terminal->putString(0,0,"                                      ");
         terminal->putString(0,2,"                                      ");
         terminal->putString(0,4,"                                      ");
		 terminal->clearScreen(true);
		 
		 // This is necessary to wipe old text from the screen currently
		 //terminal->fill(BKG_R, BKG_G, BKG_B,255);
         intro=false;
         gameTimer.start();
         _keyboard->clearAll();
      }
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
   }
}

// Program can return update in text mode, or entire screen in graphics mode.
// Output string should be wiped 
// Might as well just write directly to Terminal screen because that's how they
// used to do it anyways.
std::string Terminal_Program_MissileCommand::render()
{
//   terminal->fill(127,0,255,255);
   // if ( nCycle > 100 )
    //{
       //terminal->fill(rngLehmer.rand8(),rngLehmer.rand8(),rngLehmer.rand8(),255);
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
   if (intro || gameOver ) { return false; }
   
   if ( terminal->mouseX != -1 && terminal->mouseY != -1 )
   {

      if (terminal->mouseX < 32)
      {
         //missile1.isLeft=true;
         missile2.isLeft=true;
         //missile3.isLeft=true;
      }
      else if (terminal->mouseX < 160 )
      {
        // missile1.isLeft=false;
         missile2.isLeft=true;
         //missile3.isLeft=true;
      }
      else if (terminal->mouseX < 288 )
      {
        // missile1.isLeft=false;
         missile2.isLeft=false;
        // missile3.isLeft=true;
      }
      else
      {
      //   missile1.isLeft=false;
         missile2.isLeft=false;
      //   missile3.isLeft=false;
      }
      
      if (_mouse->isLeftClick)
      {
         if ( terminal->mouseX < 106 )
         {
            // left
            Missile * m = new Missile(32,20,terminal->mouseX,terminal->mouseY,5);
            vMissile.push(m);
            terminal->addSprite(m);
			globalAudioPlayer.playSoundOnce(missileLaunch);
         }
         else if ( terminal->mouseX > 213 )
         {
            // right
            Missile * m = new Missile(288,20,terminal->mouseX,terminal->mouseY,5);
            vMissile.push(m);
            terminal->addSprite(m);
			globalAudioPlayer.playSoundOnce(missileLaunch);
         }
         else
         {
            // center
            Missile * m = new Missile(160,20,terminal->mouseX,terminal->mouseY,5);
            vMissile.push(m);
            terminal->addSprite(m);
			globalAudioPlayer.playSoundOnce(missileLaunch);
         }
         _mouse->isLeftClick=false;
         return true;
      }
      
   }
   return false;
}

#endif