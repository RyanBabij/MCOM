#pragma once
#ifndef MCOM_MENU_TITLE_HPP
#define  MCOM_MENU_TITLE_HPP

/* MCOM: Menu_Title
   #include "Menu_Title.hpp"
   
   The title menu for the game, doesn't do a whole lot right now but
   in the future it'll regulate control between Terminal and other
   features. Also will regulate pause/load/save/quit.

*/

#include <Game/Terminal/Terminal.cpp>
// #include "Terminal_Program.cpp"

class Menu_Title: public GUI_Interface, public LogicTickInterface, public IdleTickInterface
{
   public:

   Terminal terminal;
   int terminalFlicker;
   
   /* Colours / theme. */
   Colour cNormal;
   Colour cSelected;
   Colour cDropPanel;
   Colour cHighlight;
   
   /* GUI manager. Manages all GUI controls for this menu. */
   GUI_Manager guiManager;
   
   /* Background image */
   Texture* backgroundTexture;

   Menu_Title()
   {
      active=false;
      panelX1=0; panelY1=0; panelX2=0; panelY2=0;
      font=0;
      
      terminalFlicker=255;
      
      guiManager.add(&terminal);
   }
   
   void setFont(Wildcat::Font* _font) override
   {
      font = _font;
      guiManager.setFont(_font);
   }

   void eventResize() override
   {
      const short int centerX = panelX1 + (panelNX / 2);
      const short int centerY = panelY1 + (panelNY / 2);
      //terminal.setPanel(centerX-320,centerY-200,centerX+320,centerY+200);
      
      terminal.setPanel(panelX1+10,panelY1+10,panelX2-10,panelY2-10);
   }
   
   void init() override
   {
      cNormal.set(200,200,200);
      cSelected.set(180,180,180);
      cDropPanel.set(170,170,170);
      cHighlight.set(170,170,170);

      setFont(font);
   }
   /* DisplayInterface:: */
   void render() override
   {
      int centerX = panelX1 + (panelNX / 2);
      int centerY = panelY1 + (panelNY / 2);
      
      glColor4ub(255,255,255,255);

      guiManager.render();
   }
  
   void logicTick() override
   {

   }
   
   bool keyboardEvent(Keyboard* _keyboard) override
   {
      terminal.keyboardEvent(_keyboard);
      return false;
   }
   bool mouseEvent(Mouse* _mouse) override
   {
      terminal.mouseEvent(_mouse);
      return false;
   }
   
   
   bool stealKeyboard() override
   {
      return guiManager.stealKeyboard();
   }
   
   
   //Flicker the terminal just for fun.
   void flicker()
   {
      if (Random::oneIn(3))
      {
         --terminalFlicker;
         --terminalFlicker;
         --terminalFlicker;
         if (terminalFlicker < 230 ) { terminalFlicker = 230; }
         //terminalFlicker = 255;
      }
      else if (Random::oneIn(3))
      {
         ++terminalFlicker;
         ++terminalFlicker;
         ++terminalFlicker;
         if (terminalFlicker > 255 ) { terminalFlicker = 255; }
      }
   }
   
   void idleTick() override
   {
      terminal.idleTick();
   }
   
};

#endif