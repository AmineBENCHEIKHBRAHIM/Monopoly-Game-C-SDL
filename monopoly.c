#include "monopoly.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>


void rempboard(struct propriete** tab)
{

   (*tab)[0].type=10;
   (*tab)[0].xl=614;
   (*tab)[0].xr=705;
   (*tab)[0].yt=614;
   (*tab)[0].yd=707;
   (*tab)[1].type=1;
   (*tab)[1].nb_maisons=0;
   (*tab)[1].nb_hotel=0;
   (*tab)[1].couleur=1;
   (*tab)[1].etat=1;
   (*tab)[1].val_achat=60;
   (*tab)[1].val_maison=50;
   (*tab)[1].rent0=2;
   (*tab)[1].rent1=10;
   (*tab)[1].rent2=30;
   (*tab)[1].rent3=90;
   (*tab)[1].rent4=160;
   (*tab)[1].rent5=250;
   (*tab)[1].xl=557;
   (*tab)[1].xr=614;
   (*tab)[1].yt=614;
   (*tab)[1].yd=707;
   (*tab)[2].type=4;
   (*tab)[2].xl=502;
   (*tab)[2].xr=557;
   (*tab)[2].yt=614;
   (*tab)[2].yd=707;
   (*tab)[3].type=1;
   (*tab)[3].nb_maisons=0;
   (*tab)[3].nb_hotel=0;
   (*tab)[3].couleur=1;
   (*tab)[3].etat=1;
   (*tab)[3].val_achat=60;
   (*tab)[3].val_maison=50;
   (*tab)[3].rent0=4;
   (*tab)[3].rent1=20;
   (*tab)[3].rent2=60;
   (*tab)[3].rent3=180;
   (*tab)[3].rent4=320;
   (*tab)[3].rent5=450;
   (*tab)[3].xl=446;
   (*tab)[3].xr=502;
   (*tab)[3].yt=614;
   (*tab)[3].yd=707;
   (*tab)[4].type=9;
   (*tab)[4].val_achat=200;
   (*tab)[4].xl=390;
   (*tab)[4].xr=446;
   (*tab)[4].yt=614;
   (*tab)[4].yd=707;
   (*tab)[5].type=2;
   (*tab)[5].val_achat=200;
   (*tab)[5].rent1=50;
   (*tab)[5].rent2=100;
   (*tab)[5].rent3=150;
   (*tab)[5].rent4=200;
   (*tab)[5].xl=333;
   (*tab)[5].xr=390;
   (*tab)[5].yt=614;
   (*tab)[5].yd=707;
   (*tab)[6].type=1;
   (*tab)[6].nb_maisons=0;
   (*tab)[6].nb_hotel=0;
   (*tab)[6].couleur=2;
   (*tab)[6].etat=1;
   (*tab)[6].val_achat=100;
   (*tab)[6].val_maison=50;
   (*tab)[6].rent0=6;
   (*tab)[6].rent1=30;
   (*tab)[6].rent2=90;
   (*tab)[6].rent3=270;
   (*tab)[6].rent4=400;
   (*tab)[6].rent5=550;
   (*tab)[6].xl=277;
   (*tab)[6].xr=333;
   (*tab)[6].yt=614;
   (*tab)[6].yd=707;
   (*tab)[7].type=3;
   (*tab)[7].xl=221;
   (*tab)[7].xr=277;
   (*tab)[7].yt=614;
   (*tab)[7].yd=707;
   (*tab)[8].type=1;
   (*tab)[8].nb_maisons=0;
   (*tab)[8].nb_hotel=0;
   (*tab)[8].couleur=2;
   (*tab)[8].etat=1;
   (*tab)[8].val_achat=100;
   (*tab)[8].val_maison=50;
   (*tab)[8].rent0=6;
   (*tab)[8].rent1=30;
   (*tab)[8].rent2=90;
   (*tab)[8].rent3=270;
   (*tab)[8].rent4=400;
   (*tab)[8].rent5=550;
   (*tab)[8].xl=165;
   (*tab)[8].xr=221;
   (*tab)[8].yt=614;
   (*tab)[8].yd=707;
   (*tab)[9].type=1;
   (*tab)[9].nb_maisons=0;
   (*tab)[9].nb_hotel=0;
   (*tab)[9].couleur=2;
   (*tab)[9].etat=1;
   (*tab)[9].val_achat=120;
   (*tab)[9].val_maison=50;
   (*tab)[9].rent0=8;
   (*tab)[9].rent1=40;
   (*tab)[9].rent2=100;
   (*tab)[9].rent3=300;
   (*tab)[9].rent4=450;
   (*tab)[9].rent5=600;
   (*tab)[9].xl=109;
   (*tab)[9].xr=165;
   (*tab)[9].yt=614;
   (*tab)[9].yd=707;
   (*tab)[10].type=5;
   (*tab)[10].memo_prison=0;
   (*tab)[10].xl=18;
   (*tab)[10].xr=109;
   (*tab)[10].yt=614;
   (*tab)[10].yd=707;
   (*tab)[11].type=1;
   (*tab)[11].nb_maisons=0;
   (*tab)[11].nb_hotel=0;
   (*tab)[11].couleur=3;
   (*tab)[11].etat=1;
   (*tab)[11].val_achat=140;
   (*tab)[11].val_maison=100;
   (*tab)[11].rent0=10;
   (*tab)[11].rent1=50;
   (*tab)[11].rent2=150;
   (*tab)[11].rent3=450;
   (*tab)[11].rent4=625;
   (*tab)[11].rent5=750;
   (*tab)[11].xl=18;
   (*tab)[11].xr=109;
   (*tab)[11].yt=557;
   (*tab)[11].yd=614;
   (*tab)[12].type=7;
   (*tab)[12].val_achat=150;
   (*tab)[12].xl=18;
   (*tab)[12].xr=109;
   (*tab)[12].yt=501;
   (*tab)[12].yd=557;
   (*tab)[13].type=1;
   (*tab)[13].nb_maisons=0;
   (*tab)[13].nb_hotel=0;
   (*tab)[13].couleur=3;
   (*tab)[13].etat=1;
   (*tab)[13].val_achat=140;
   (*tab)[13].val_maison=100;
   (*tab)[13].rent0=10;
   (*tab)[13].rent1=50;
   (*tab)[13].rent2=150;
   (*tab)[13].rent3=450;
   (*tab)[13].rent4=625;
   (*tab)[13].rent5=750;
   (*tab)[13].xl=18;
   (*tab)[13].xr=109;
   (*tab)[13].yt=445;
   (*tab)[13].yd=501;
   (*tab)[14].type=1;
   (*tab)[14].nb_maisons=0;
   (*tab)[14].nb_hotel=0;
   (*tab)[14].couleur=3;
   (*tab)[14].etat=1;
   (*tab)[14].val_achat=160;
   (*tab)[14].val_maison=100;
   (*tab)[14].rent0=12;
   (*tab)[14].rent1=60;
   (*tab)[14].rent2=180;
   (*tab)[14].rent3=500;
   (*tab)[14].rent4=700;
   (*tab)[14].rent5=900;
   (*tab)[14].xl=18;
   (*tab)[14].xr=109;
   (*tab)[14].yt=389;
   (*tab)[14].yd=445;
   (*tab)[15].type=2;
   (*tab)[15].val_achat=200;
   (*tab)[15].rent1=50;
   (*tab)[15].rent2=100;
   (*tab)[15].rent3=150;
   (*tab)[15].rent4=200;
   (*tab)[15].xl=18;
   (*tab)[15].xr=109;
   (*tab)[15].yt=333;
   (*tab)[15].yd=389;
   (*tab)[16].type=1;
   (*tab)[16].nb_maisons=0;
   (*tab)[16].nb_hotel=0;
   (*tab)[16].couleur=4;
   (*tab)[16].etat=1;
   (*tab)[16].val_achat=180;
   (*tab)[16].val_maison=100;
   (*tab)[16].rent0=14;
   (*tab)[16].rent1=70;
   (*tab)[16].rent2=200;
   (*tab)[16].rent3=550;
   (*tab)[16].rent4=750;
   (*tab)[16].rent5=950;
   (*tab)[16].xl=18;
   (*tab)[16].xr=109;
   (*tab)[16].yt=278;
   (*tab)[16].yd=333;
   (*tab)[17].type=4;
   (*tab)[17].xl=18;
   (*tab)[17].xr=109;
   (*tab)[17].yt=221;
   (*tab)[17].yd=278;
   (*tab)[18].type=1;
   (*tab)[18].nb_maisons=0;
   (*tab)[18].nb_hotel=0;
   (*tab)[18].couleur=4;
   (*tab)[18].etat=1;
   (*tab)[18].val_achat=180;
   (*tab)[18].val_maison=100;
   (*tab)[18].rent0=14;
   (*tab)[18].rent1=70;
   (*tab)[18].rent2=200;
   (*tab)[18].rent3=550;
   (*tab)[18].rent4=750;
   (*tab)[18].rent5=950;
   (*tab)[18].xl=18;
   (*tab)[18].xr=109;
   (*tab)[18].yt=165;
   (*tab)[18].yd=221;
   (*tab)[19].type=1;
   (*tab)[19].nb_maisons=0;
   (*tab)[19].nb_hotel=0;
   (*tab)[19].couleur=4;
   (*tab)[19].etat=1;
   (*tab)[19].val_achat=200;
   (*tab)[19].val_maison=100;
   (*tab)[19].rent0=16;
   (*tab)[19].rent1=80;
   (*tab)[19].rent2=220;
   (*tab)[19].rent3=600;
   (*tab)[19].rent4=800;
   (*tab)[19].rent5=1000;
   (*tab)[19].xl=18;
   (*tab)[19].xr=109;
   (*tab)[19].yt=109;
   (*tab)[19].yd=165;
   (*tab)[20].type=8;
   (*tab)[20].xl=18;
   (*tab)[20].xr=109;
   (*tab)[20].yt=17;
   (*tab)[20].yd=109;
   (*tab)[21].type=1;
   (*tab)[21].nb_maisons=0;
   (*tab)[21].nb_hotel=0;
   (*tab)[21].couleur=5;
   (*tab)[21].etat=1;
   (*tab)[21].val_achat=220;
   (*tab)[21].val_maison=150;
   (*tab)[21].rent0=18;
   (*tab)[21].rent1=90;
   (*tab)[21].rent2=250;
   (*tab)[21].rent3=700;
   (*tab)[21].rent4=875;
   (*tab)[21].rent5=1050;
   (*tab)[21].xl=109;
   (*tab)[21].xr=165;
   (*tab)[21].yt=17;
   (*tab)[21].yd=109;
   (*tab)[22].type=3;
   (*tab)[22].xl=165;
   (*tab)[22].xr=221;
   (*tab)[22].yt=17;
   (*tab)[22].yd=109;
   (*tab)[23].type=1;
   (*tab)[23].nb_maisons=0;
   (*tab)[23].nb_hotel=0;
   (*tab)[23].couleur=5;
   (*tab)[23].etat=1;
   (*tab)[23].val_achat=220;
   (*tab)[23].val_maison=150;
   (*tab)[23].rent0=18;
   (*tab)[23].rent1=90;
   (*tab)[23].rent2=250;
   (*tab)[23].rent3=700;
   (*tab)[23].rent4=875;
   (*tab)[23].rent5=1050;
   (*tab)[23].xl=221;
   (*tab)[23].xr=277;
   (*tab)[23].yt=17;
   (*tab)[23].yd=109;
   (*tab)[24].type=1;
   (*tab)[24].nb_maisons=0;
   (*tab)[24].nb_hotel=0;
   (*tab)[24].couleur=5;
   (*tab)[24].etat=1;
   (*tab)[24].val_achat=240;
   (*tab)[24].val_maison=150;
   (*tab)[24].rent0=20;
   (*tab)[24].rent1=100;
   (*tab)[24].rent2=300;
   (*tab)[24].rent3=750;
   (*tab)[24].rent4=925;
   (*tab)[24].rent5=1100;
   (*tab)[24].xl=277;
   (*tab)[24].xr=333;
   (*tab)[24].yt=17;
   (*tab)[24].yd=109;
   (*tab)[25].type=2;
   (*tab)[25].val_achat=200;
   (*tab)[25].rent1=50;
   (*tab)[25].rent2=100;
   (*tab)[25].rent3=150;
   (*tab)[25].rent4=200;
   (*tab)[25].xl=333;
   (*tab)[25].xr=389;
   (*tab)[25].yt=17;
   (*tab)[25].yd=109;
   (*tab)[26].type=1;
   (*tab)[26].nb_maisons=0;
   (*tab)[26].nb_hotel=0;
   (*tab)[26].couleur=6;
   (*tab)[26].etat=1;
   (*tab)[26].val_achat=260;
   (*tab)[26].val_maison=150;
   (*tab)[26].rent0=22;
   (*tab)[26].rent1=110;
   (*tab)[26].rent2=330;
   (*tab)[26].rent3=800;
   (*tab)[26].rent4=975;
   (*tab)[26].rent5=1150;
   (*tab)[26].xl=389;
   (*tab)[26].xr=445;
   (*tab)[26].yt=17;
   (*tab)[26].yd=109;
   (*tab)[27].type=1;
   (*tab)[27].nb_maisons=0;
   (*tab)[27].nb_hotel=0;
   (*tab)[27].couleur=6;
   (*tab)[27].etat=1;
   (*tab)[27].val_achat=260;
   (*tab)[27].val_maison=150;
   (*tab)[27].rent0=22;
   (*tab)[27].rent1=110;
   (*tab)[27].rent2=330;
   (*tab)[27].rent3=800;
   (*tab)[27].rent4=975;
   (*tab)[27].rent5=1150;
   (*tab)[27].xl=445;
   (*tab)[27].xr=501;
   (*tab)[27].yt=17;
   (*tab)[27].yd=109;
   (*tab)[28].type=7;
   (*tab)[28].val_achat=150;
   (*tab)[28].xl=501;
   (*tab)[28].xr=557;
   (*tab)[28].yt=17;
   (*tab)[28].yd=109;
   (*tab)[29].type=1;
   (*tab)[29].nb_maisons=0;
   (*tab)[29].nb_hotel=0;
   (*tab)[29].couleur=6;
   (*tab)[29].etat=1;
   (*tab)[29].val_achat=280;
   (*tab)[29].val_maison=150;
   (*tab)[29].rent0=24;
   (*tab)[29].rent1=120;
   (*tab)[29].rent2=360;
   (*tab)[29].rent3=850;
   (*tab)[29].rent4=1025;
   (*tab)[29].rent5=1200;
   (*tab)[29].xl=557;
   (*tab)[29].xr=614;
   (*tab)[29].yt=17;
   (*tab)[29].yd=109;
   (*tab)[30].type=6;
   (*tab)[30].xl=614;
   (*tab)[30].xr=705;
   (*tab)[30].yt=17;
   (*tab)[30].yd=109;
   (*tab)[31].type=1;
   (*tab)[31].nb_maisons=0;
   (*tab)[31].nb_hotel=0;
   (*tab)[31].couleur=7;
   (*tab)[31].etat=1;
   (*tab)[31].val_achat=300;
   (*tab)[31].val_maison=200;
   (*tab)[31].rent0=26;
   (*tab)[31].rent1=130;
   (*tab)[31].rent2=390;
   (*tab)[31].rent3=900;
   (*tab)[31].rent4=1100;
   (*tab)[31].rent5=1275;
   (*tab)[31].xl=614;
   (*tab)[31].xr=705;
   (*tab)[31].yt=109;
   (*tab)[31].yd=165;
   (*tab)[32].type=1;
   (*tab)[32].nb_maisons=0;
   (*tab)[32].nb_hotel=0;
   (*tab)[32].couleur=7;
   (*tab)[32].etat=1;
   (*tab)[32].val_achat=300;
   (*tab)[32].val_maison=200;
   (*tab)[32].rent0=26;
   (*tab)[32].rent1=130;
   (*tab)[32].rent2=390;
   (*tab)[32].rent3=900;
   (*tab)[32].rent4=1100;
   (*tab)[32].rent5=1275;
   (*tab)[32].xl=614;
   (*tab)[32].xr=705;
   (*tab)[32].yt=165;
   (*tab)[32].yd=221;
   (*tab)[33].type=4;
   (*tab)[33].xl=614;
   (*tab)[33].xr=705;
   (*tab)[33].yt=221;
   (*tab)[33].yd=277;
   (*tab)[34].type=1;
   (*tab)[34].nb_maisons=0;
   (*tab)[34].nb_hotel=0;
   (*tab)[34].couleur=7;
   (*tab)[34].etat=1;
   (*tab)[34].val_achat=320;
   (*tab)[34].val_maison=200;
   (*tab)[34].rent0=28;
   (*tab)[34].rent1=150;
   (*tab)[34].rent2=450;
   (*tab)[34].rent3=1000;
   (*tab)[34].rent4=1200;
   (*tab)[34].rent5=1400;
   (*tab)[34].xl=614;
   (*tab)[34].xr=705;
   (*tab)[34].yt=277;
   (*tab)[34].yd=333;
   (*tab)[35].val_achat=200;
   (*tab)[35].rent1=50;
   (*tab)[35].rent2=100;
   (*tab)[35].rent3=150;
   (*tab)[35].rent4=200;
   (*tab)[35].xl=614;
   (*tab)[35].xr=705;
   (*tab)[35].yt=333;
   (*tab)[35].yd=389;
   (*tab)[36].type=3;
   (*tab)[36].xl=614;
   (*tab)[36].xr=705;
   (*tab)[36].yt=389;
   (*tab)[36].yd=445;
   (*tab)[37].type=1;
   (*tab)[37].nb_maisons=0;
   (*tab)[37].nb_hotel=0;
   (*tab)[37].couleur=8;
   (*tab)[37].etat=1;
   (*tab)[37].val_achat=350;
   (*tab)[37].val_maison=200;
   (*tab)[37].rent0=35;
   (*tab)[37].rent1=175;
   (*tab)[37].rent2=500;
   (*tab)[37].rent3=1100;
   (*tab)[37].rent4=1300;
   (*tab)[37].rent5=1500;
   (*tab)[37].xl=614;
   (*tab)[37].xr=705;
   (*tab)[37].yt=445;
   (*tab)[37].yd=501;
   (*tab)[38].type=9;
   (*tab)[38].val_achat=75;
   (*tab)[38].xl=614;
   (*tab)[38].xr=705;
   (*tab)[38].yt=501;
   (*tab)[38].yd=557;
   (*tab)[39].type=1;
   (*tab)[39].nb_maisons=0;
   (*tab)[39].nb_hotel=0;
   (*tab)[39].couleur=8;
   (*tab)[39].etat=1;
   (*tab)[39].val_achat=400;
   (*tab)[39].val_maison=200;
   (*tab)[39].rent0=50;
   (*tab)[39].rent1=200;
   (*tab)[39].rent2=600;
   (*tab)[39].rent3=1400;
   (*tab)[39].rent4=1700;
   (*tab)[39].rent5=2000;
   (*tab)[39].xl=614;
   (*tab)[39].xr=705;
   (*tab)[39].yt=557;
   (*tab)[39].yd=614;

}



void buyProperty(int property,int propertyValue, player *currentPlayer)
{
   if(currentPlayer->money > propertyValue)
   {
   currentPlayer->money -= propertyValue;

   }
   else
   {
      printf("Insufficient funds to buy property.");
   }

}
//0 stands for +, 1 stands for -, 2 frees player (quit/remove);
void setMoney(int valueToAdd, int operatorToUse, player *currentPlayer)
{
   switch(operatorToUse)
   {
      case 0:
      currentPlayer->money += valueToAdd;
      break;

      case 1:
     currentPlayer-> money -= valueToAdd;
      break;

      default:
      printf("Entered an incorrect value, try again");
      break;
   }
}


int continuePlaying(boardValues *currentGame)
{

int moneyCheck = 0;
int i = 0;
for (i = 0; i < currentGame->numPlayers; i++)
{
   moneyCheck += currentGame->thePlayers[i].money;
}

if (moneyCheck < 0)
{
   return 0;
}
else
{
   return 1;
}

}
int firstDie(player *currentPlayer)
{
   srand(time(0));
   int thisDie = rand() % 6;
   currentPlayer->dieOne = thisDie + 1;
   return (thisDie + 1);
}

int secondDie(player *currentPlayer)
{
   srand(rand() % 6);
   int thisDie = rand() % 6;
   currentPlayer->dieTwo = thisDie + 1;
   return (thisDie + 1);
}

int getRoll(player *currentPlayer)
{
   int totalRoll = (currentPlayer->dieOne) + (currentPlayer->dieTwo);
   return totalRoll;
}

int getMoney(struct player *currentPlayer)
{
   return currentPlayer->money;
}

/*
*This method is for go to jail, advance to, etc.
*
*/void setPosition(player *currentPlayer, int newLocation)
{
   currentPlayer->currentLocation = newLocation;
}

/*
* Specifically for when a player rolls the die.
*/
void setPositionRoll(player *currentPlayer, int currentLocation, int dieRoll)
{
   if ((currentLocation + dieRoll) >= 40)
   {
        setPosition(currentPlayer, (currentLocation + dieRoll) - 40);
        printf("You passed Go, collect $200!\n");
        currentPlayer->money += 200;

   }
   else
   {
      setPosition(currentPlayer, currentLocation + dieRoll);
   }

}
//Player






int initializePlayers(boardValues *currentGame)
{
   int i=0;
   for (i = 0; i < (currentGame->numPlayers); i++)
   {
     currentGame->thePlayers[i].currentLocation = 0;
     currentGame->thePlayers[i].money = 1500;
     currentGame->thePlayers[i].doublesCounter = 0;
     currentGame->thePlayers[i].dieOne = 0;
     currentGame->thePlayers[i].dieTwo = 0;
     currentGame->thePlayers[i].dieRoll = 0;
     currentGame->thePlayers[i].nb_propriete = 0;
     currentGame->thePlayers[i].wealth = 0;
     currentGame->thePlayers[i].living = 1;
     currentGame->thePlayers[i].railroadCounter = 0;
     currentGame->thePlayers[i].utilityCounter =0;
     currentGame->thePlayers[i].memo_prison = 0;
     currentGame->thePlayers[i].nb_propriete_mortaged = 0;

   }
  return 0;
}

int getCurrentPlayer(struct boardValues *currentGame)
{
   return currentGame->currentPlayer;
}

int verifCanBuild(boardValues *passBoard, propriete[] passTab)
{
    int var=0;
    if(passBoard->currentPlayer==passTab[1].appartenance && passBoard->currentPlayer==passTab[3].appartenance)
    {
        var=1;
    }
    if(passBoard->currentPlayer==passTab[6].appartenance && passBoard->currentPlayer==passTab[8].appartenance && passBoard->currentPlayer==passTab[9].appartenance)
    {
        var=1;
    }
    if(passBoard->currentPlayer==passTab[11].appartenance && passBoard->currentPlayer==passTab[13].appartenance && passBoard->currentPlayer==passTab[14].appartenance)
    {
        var=1;
    }
    if(passBoard->currentPlayer==passTab[16].appartenance && passBoard->currentPlayer==passTab[18].appartenance && passBoard->currentPlayer==passTab[19].appartenance)
    {
        var=1;
    }
    if(passBoard->currentPlayer==passTab[21].appartenance && passBoard->currentPlayer==passTab[23].appartenance && passBoard->currentPlayer==passTab[24].appartenance)
    {
        var=1;
    }
    if(passBoard->currentPlayer==passTab[26].appartenance && passBoard->currentPlayer==passTab[27].appartenance && passBoard->currentPlayer==passTab[29].appartenance)
    {
        var=1;
    }
    if(passBoard->currentPlayer==passTab[31].appartenance && passBoard->currentPlayer==passTab[32].appartenance && passBoard->currentPlayer==passTab[34].appartenance)
    {
        var=1;
    }
    if(passBoard->currentPlayer==passTab[37].appartenance && passBoard->currentPlayer==passTab[39].appartenance)
    {
        var=1;
    }
    return var;
}

int verifCanSell(boardValues *passBoard, propriete[] passTab)
{
    int var=0;
    if(passBoard->currentPlayer==passTab[1].appartenance && passBoard->currentPlayer==passTab[3].appartenance && (passTab[1].nb_maisons>0 | passTab[3].nb_maisons>0))
    {
        var=1;
    }
    if(passBoard->currentPlayer==passTab[6].appartenance && passBoard->currentPlayer==passTab[8].appartenance && passBoard->currentPlayer==passTab[9].appartenance && (passTab[6].nb_maisons>0 | passTab[8].nb_maisons>0 | passTab[9].nb_maisons>0))
    {
        var=1;
    }
    if(passBoard->currentPlayer==passTab[11].appartenance && passBoard->currentPlayer==passTab[13].appartenance && passBoard->currentPlayer==passTab[14].appartenance && (passTab[11].nb_maisons>0 | passTab[13].nb_maisons>0 | passTab[14].nb_maisons>0))
    {
        var=1;
    }
    if(passBoard->currentPlayer==passTab[16].appartenance && passBoard->currentPlayer==passTab[18].appartenance && passBoard->currentPlayer==passTab[19].appartenance && (passTab[16].nb_maisons>0 | passTab[18].nb_maisons>0 | passTab[19].nb_maisons>0))
    {
        var=1;
    }
    if(passBoard->currentPlayer==passTab[21].appartenance && passBoard->currentPlayer==passTab[23].appartenance && passBoard->currentPlayer==passTab[24].appartenance && (passTab[21].nb_maisons>0 | passTab[23].nb_maisons>0 | passTab[24].nb_maisons>0))
    {
        var=1;
    }
    if(passBoard->currentPlayer==passTab[26].appartenance && passBoard->currentPlayer==passTab[27].appartenance && passBoard->currentPlayer==passTab[29].appartenance && (passTab[26].nb_maisons>0 | passTab[27].nb_maisons>0 | passTab[29].nb_maisons>0))
    {
        var=1;
    }
    if(passBoard->currentPlayer==passTab[31].appartenance && passBoard->currentPlayer==passTab[32].appartenance && passBoard->currentPlayer==passTab[34].appartenance && (passTab[31].nb_maisons>0 | passTab[32].nb_maisons>0 | passTab[34].nb_maisons>0))
    {
        var=1;
    }
    if(passBoard->currentPlayer==passTab[37].appartenance && passBoard->currentPlayer==passTab[39].appartenance && (passTab[37].nb_maisons>0 | passTab[39].nb_maisons>0))
    {
        var=1;
    }
    return var;
}
//Start of print location
