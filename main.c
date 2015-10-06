#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <fmodex/fmod.h>
#include <time.h>

typedef struct player
{
   int money;
   int wealth;
   int currentLocation;
   int dieRoll;
   int dieOne;
   int dieTwo;
   int doublesCounter;
   int railroadCounter;
   int utilityCounter;
   int memo_prison;
   int nb_propriete;
   int nb_propriete_mort;
   int nb_maisons;
}player;

typedef struct propriete
{
    int type;
    int nb_maisons;
    int couleur;
    int etat;
    int appartenance;
    float val_achat;
    float val_maison;
    float rent0;
    float rent1;
    float rent2;
    float rent3;
    float rent4;
    float rent5;
    int xl,xr;
    int yt,yd;
}propriete;

typedef struct boardValues
{
   int numPlayers;
   int currentPlayer;
   player thePlayers[2];
} boardValues;



void rempboard(struct propriete** tab);
void initializePlayers(boardValues *currentGame);
void remp_buyj1(SDL_Surface*** tab);
void remp_buyj2(SDL_Surface*** tab);
void remp_mortj1(SDL_Surface*** tab);
void remp_mortj2(SDL_Surface*** tab);
void remp_illum(SDL_Surface*** tab);
void remp_1m(SDL_Surface*** tab);
void remp_2m(SDL_Surface*** tab);
void remp_3m(SDL_Surface*** tab);
void remp_4m(SDL_Surface*** tab);
void remp_5m(SDL_Surface*** tab);
int firstDie(player *currentPlayer);
int secondDie(player *currentPlayer);
int getRoll(player *currentPlayer);
void setPositionRoll(player *currentPlayer, int currentLocation, int dieRoll);
void setPosition(player *currentPlayer, int newLocation);
void setMoney(int valueToAdd, int operatorToUse, player *currentPlayer);

int main ( int argc, char** argv )
{
   int comptchance=0;
   int comptcomchest=0;
   int incometaxoptions=0;

   int lastlocationj1=0;
   int lastlocationj2=0;
   boardValues theGame;
   boardValues *passBoard = &theGame;
   struct propriete* tab;
   tab = malloc(40*sizeof(struct propriete));
   rempboard(&tab);// Paramétrage des cases
   theGame.numPlayers=2;
   initializePlayers(passBoard);

theGame.currentPlayer = 1;
// ***** tout ce qui concerne le son
FMOD_SYSTEM *system;
FMOD_SOUND *musique;
FMOD_RESULT resultat;

FMOD_SOUND *player1start;
FMOD_SOUND *clicrolletdepl;
FMOD_SOUND *wouldubuy;
FMOD_SOUND *clicbuy;
FMOD_SOUND *clickfinish;
FMOD_SOUND *chanceouchest;
FMOD_SOUND *okchanceouchest;
FMOD_SOUND *mort;
FMOD_SOUND *clickpropbuildoumort;
FMOD_SOUND *simpleclick;

FMOD_System_Create(&system);
FMOD_System_Init(system, 12, FMOD_INIT_NORMAL, NULL);

/* On ouvre la musique */
resultat = FMOD_System_CreateSound(system, "song.wma",
FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &musique);

resultat = FMOD_System_CreateSound(system, "player1start.wav",
FMOD_CREATESAMPLE, 0, &player1start);
resultat = FMOD_System_CreateSound(system, "clicrolletdepl.wav",
FMOD_CREATESAMPLE, 0, &clicrolletdepl);
resultat = FMOD_System_CreateSound(system, "wouldubuy.wav",
FMOD_CREATESAMPLE, 0, &wouldubuy);
resultat = FMOD_System_CreateSound(system, "clickfinish.wav",
FMOD_CREATESAMPLE, 0, &clickfinish);
resultat = FMOD_System_CreateSound(system, "chanceouchest.wav",
FMOD_CREATESAMPLE, 0, &chanceouchest);
resultat = FMOD_System_CreateSound(system, "okchanceouchest.wav",
FMOD_CREATESAMPLE, 0, &okchanceouchest);
resultat = FMOD_System_CreateSound(system, "mort.wav",
FMOD_CREATESAMPLE, 0, &mort);
resultat = FMOD_System_CreateSound(system, "clickpropbuildoumort.wav",
FMOD_CREATESAMPLE, 0, &clickpropbuildoumort);
resultat = FMOD_System_CreateSound(system, "clicbuy.wav",
FMOD_CREATESAMPLE, 0, &clicbuy);
resultat = FMOD_System_CreateSound(system, "simpleclick.wav",
FMOD_CREATESAMPLE, 0, &simpleclick);

/* On active la répétition de la musique à l'infini */
FMOD_Sound_SetLoopCount(musique, -1);
/* On joue la musique */
FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0,
NULL);










    // ****** tableaux sdl_surface ************
SDL_Surface** tab_buyj1;
tab_buyj1 = malloc(40*sizeof(SDL_Surface*));
SDL_Surface** tab_mortagej1;
tab_mortagej1 = malloc(40*sizeof(SDL_Surface*));
SDL_Surface** tab_buyj2;
tab_buyj2 = malloc(40*sizeof(SDL_Surface*));
SDL_Surface** tab_mortagej2;
tab_mortagej2 = malloc(40*sizeof(SDL_Surface*));
SDL_Surface** tab_illum;
tab_illum = malloc(40*sizeof(SDL_Surface*));
SDL_Surface** tab_j1_b;
tab_j1_b = malloc(40*sizeof(SDL_Surface*));
SDL_Surface** tab_j2_b;
tab_j2_b = malloc(40*sizeof(SDL_Surface*));
SDL_Surface** tab_1m;
tab_1m = malloc(40*sizeof(SDL_Surface*));
SDL_Surface** tab_2m;
tab_2m = malloc(40*sizeof(SDL_Surface*));
SDL_Surface** tab_3m;
tab_3m = malloc(40*sizeof(SDL_Surface*));
SDL_Surface** tab_4m;
tab_4m = malloc(40*sizeof(SDL_Surface*));
SDL_Surface** tab_5m;
tab_5m = malloc(40*sizeof(SDL_Surface*));


remp_buyj1(&tab_buyj1);
remp_buyj2(&tab_buyj2);
remp_mortj1(&tab_mortagej1);
remp_mortj2(&tab_mortagej2);
remp_illum(&tab_illum);
remp_j1_b(&tab_j1_b);
remp_j2_b(&tab_j2_b);
remp_1m(&tab_1m);
remp_2m(&tab_2m);
remp_3m(&tab_3m);
remp_4m(&tab_4m);
remp_5m(&tab_5m);
    // ***** Initialisations des pointeurs de surfaces *****
SDL_Surface* ecran = NULL;
SDL_Surface* imageDeFond = NULL;
SDL_Surface* imaged1 = NULL;
SDL_Surface* imaged2 = NULL;
SDL_Surface* imagej1 = NULL;
SDL_Surface* imagej2 = NULL;
SDL_Surface* soldej1 = NULL;
SDL_Surface* soldej2 = NULL;
SDL_Surface* rent = NULL;
SDL_Surface* boutonmortage = NULL;
SDL_Surface* boutonunmortage = NULL;
SDL_Surface* boutonbuild = NULL;
SDL_Surface* boutonsell = NULL;
// ***** initialisation des fonts *******
TTF_Font* police = NULL;
SDL_Color vertactif = {39,107,24},vertpassif = {124,219,103},blanc = {254,254,254};
// ***** Declaration des évènements *****
SDL_Event event;
// ***** Declarations des positions des surfaces *****
SDL_Rect positionFond;
SDL_Rect positionnew;
SDL_Rect positionexit;
SDL_Rect positiond1;
SDL_Rect positiond2;
SDL_Rect positionj1;
SDL_Rect positionj2;
SDL_Rect positionsoldej1_tj2;
SDL_Rect positionsoldej2_tj2;
SDL_Rect positionsoldej1_tj1;
SDL_Rect positionsoldej2_tj1;
SDL_Rect positionrent;

int continuer = 1;
int continuerjeu=1;
int abandon=0;
char soldep1[10]="";
char soldep2[10]="";
char renttab[10]="";
// ***** Initialisation des positions des surfaces ******
positionFond.x = 0;
positionFond.y = 0;
positionnew.x=335;
positionnew.y=700;
positionexit.x=650;
positionexit.y=700;
positiond1.x = 148;
positiond1.y = 472;
positiond2.x = 216;
positiond2.y = 523;
positionj1.x = 620;
positionj1.y = 610;
positionj2.x = 655;
positionj2.y = 650;
positionsoldej1_tj2.x = 880;
positionsoldej1_tj2.y = 37;
positionsoldej2_tj2.x = 880;
positionsoldej2_tj2.y = 104;
positionsoldej1_tj1.x = 880;
positionsoldej1_tj1.y = 37;
positionsoldej2_tj1.x = 880;
positionsoldej2_tj1.y = 309;
positionrent.x = 348;
positionrent.y = 302;

// ****** Initialisation de la SDL ******
SDL_Init(SDL_INIT_VIDEO);
TTF_Init();
ecran = SDL_SetVideoMode(1024, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
SDL_WM_SetCaption("Monopoly", NULL);
police = TTF_OpenFont("baskvill.ttf",28);
imageDeFond = IMG_Load("welcome1.jpg");
sprintf(soldep1, "$ %i", theGame.thePlayers[0].money);
sprintf(soldep2, "$ %i", theGame.thePlayers[1].money);
soldej1 = TTF_RenderText_Blended(police,soldep1,vertactif);
soldej2 = TTF_RenderText_Blended(police,soldep2,vertpassif);
while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Veut arrêter le jeu
                        continuer = 0;
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT)
            {

                    if((positionnew.x<=event.button.x)&&(event.button.x<=positionnew.x+264) && (positionnew.y<=event.button.y) && (event.button.y<=positionnew.y+68))
                        // implémentation du jeu
                    {
                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, player1start, 0,NULL);
                        imageDeFond = IMG_Load("player1starts.png");
                        imaged1 = NULL;
                        imaged2 = NULL;
                        imagej1 = NULL;
                        imagej2 = NULL;
                        soldej1 = TTF_RenderText_Blended(police,soldep1,vertactif);
                        soldej2 = TTF_RenderText_Blended(police,soldep2,vertpassif);
                        continuerjeu=1;
                        int att_start=1;
                        int att_die=0;
                        int att_buy=0;
                        int att_finish=0;
                        while (continuerjeu)
                        {
                        SDL_WaitEvent(&event);
                                    switch(event.type)
                                    {

                                    case SDL_QUIT:
                                    continuerjeu=0;
                                    SDL_FreeSurface(imageDeFond);
                                    imageDeFond = IMG_Load("welcome1.jpg");
                                    break;
                                    case SDL_KEYDOWN:
                                            switch(event.key.keysym.sym)
                                            {
                                            case SDLK_ESCAPE:
                                            continuerjeu=0;
                                            SDL_FreeSurface(imageDeFond);
                                            imageDeFond = IMG_Load("welcome1.jpg");
                                            break;
                                            }
                                    break;
                                    case SDL_MOUSEBUTTONUP:
                                    if (event.button.button == SDL_BUTTON_LEFT)
                                    {
                                      if((377<=event.button.x)&&(event.button.x<=476) && (397<=event.button.y) && (event.button.y<=437) && (att_start))
                                      {
                                          FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, simpleclick, 0,NULL);
                                          SDL_FreeSurface(imageDeFond);
                                          imageDeFond = IMG_Load("rolldicej1.png");
                                          imagej1 = IMG_Load("j1.png");
                                          imagej2 = IMG_Load("j2.png");
                                          att_start=0;att_die=1;att_buy=0;att_finish=0;
                                      }
                                        abandon=0;
                                       boutonmortage=NULL;
                                      boutonunmortage=NULL;
                                      boutonbuild=NULL;
                                      boutonsell=NULL;
                                      // s'il abandonne l'achat ********************

                                      if(tab[theGame.thePlayers[1].currentLocation].etat==1)
                                      {
                                         if((att_buy)&&(387<=event.button.x)&&(event.button.x<=483) && (537<=event.button.y) && (event.button.y<=577))
                                      {
                                          FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, simpleclick, 0,NULL);
                                          imageDeFond=IMG_Load("finishturnj2.jpg");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          abandon=1;
                                      }
                                      }
                                      if(theGame.currentPlayer==1)
                                      {
                                           // s'il il abandonne l'achat ********************
                                      if(tab[theGame.thePlayers[0].currentLocation].etat==1)
                                      {
                                         if((att_buy)&&(387<=event.button.x)&&(event.button.x<=483) && (537<=event.button.y) && (event.button.y<=577))
                                      {
                                          FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, simpleclick, 0,NULL);
                                          imageDeFond=IMG_Load("finishturnj1.jpg");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          abandon=1;
                                      }
                                      }
                                      //s'il attend de cliquer roll dice et puis deplacement et pop up ********
                                      if((326<=event.button.x)&&(event.button.x<=480) && (511<=event.button.y) && (event.button.y<=573) && (att_die))
                                      {
                                          FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clicrolletdepl, 0,NULL);
                                          SDL_FreeSurface(imageDeFond);
                                          imageDeFond = IMG_Load("boardclean.png");
                                          int d1=firstDie(&theGame.thePlayers[0]);
                                          int d2=secondDie(&theGame.thePlayers[0]);
                                          theGame.thePlayers[0].dieRoll=getRoll(&theGame.thePlayers[0]);

                                          setPositionRoll(&theGame.thePlayers[0],theGame.thePlayers[0].currentLocation,theGame.thePlayers[0].dieRoll);
                                          switch(d1)
                                          {
                                              case 1:imaged1 = IMG_Load("de1.png");break;
                                              case 2:imaged1 = IMG_Load("de2.png");break;
                                              case 3:imaged1 = IMG_Load("de3.png");break;
                                              case 4:imaged1 = IMG_Load("de4.png");break;
                                              case 5:imaged1 = IMG_Load("de5.png");break;
                                              case 6:imaged1 = IMG_Load("de6.png");break;
                                          }
                                          switch(d2)
                                          {
                                              case 1:imaged2 = IMG_Load("de1.png");break;
                                              case 2:imaged2 = IMG_Load("de2.png");break;
                                              case 3:imaged2 = IMG_Load("de3.png");break;
                                              case 4:imaged2 = IMG_Load("de4.png");break;
                                              case 5:imaged2 = IMG_Load("de5.png");break;
                                              case 6:imaged2 = IMG_Load("de6.png");break;
                                          }
                                          imagej1 = IMG_Load("j1.png");
                                          imagej2 = IMG_Load("j2.png");
                                          SDL_PollEvent(&event);
                                          int endeplacement=1;
                                          while(endeplacement)
                                          {

                                          if((0<=lastlocationj1)&&(lastlocationj1<=9))
                                          {
                                                if((0<=theGame.thePlayers[0].currentLocation)&&(theGame.thePlayers[0].currentLocation<=9))
                                                {
                                                    if (positionj1.x>tab[theGame.thePlayers[0].currentLocation].xl)
                                                {
                                                    positionj1.x=positionj1.x-10;

                                                }
                                                if(positionj1.x<=tab[theGame.thePlayers[0].currentLocation].xl){endeplacement=0;}
                                                }
                                                else
                                                {
                                                  if (positionj1.x>tab[theGame.thePlayers[0].currentLocation].xl)
                                                {
                                                    positionj1.x=positionj1.x-10;

                                                }
                                                if (positionj1.x<=tab[theGame.thePlayers[0].currentLocation].xl)
                                                {
                                                    if (positionj1.y>tab[theGame.thePlayers[0].currentLocation].yt)
                                                        {
                                                        positionj1.y=positionj1.y-10;

                                                        }
                                                }
                                                if((positionj1.x<=tab[theGame.thePlayers[0].currentLocation].xl)&&(positionj1.y<=tab[theGame.thePlayers[0].currentLocation].yt)){endeplacement=0;}
                                                }

                                          }
                                          if((10<=lastlocationj1)&&(lastlocationj1<=19))
                                          {
                                              if((10<=theGame.thePlayers[0].currentLocation)&&(theGame.thePlayers[0].currentLocation<=19))
                                              {
                                                  if (positionj1.y>tab[theGame.thePlayers[0].currentLocation].yt)
                                                {
                                                    positionj1.y=positionj1.y-10;
                                                }
                                                if(positionj1.y<=tab[theGame.thePlayers[0].currentLocation].yt)
                                                {
                                                    endeplacement=0;
                                                }
                                              }
                                              else
                                              {
                                                 if (positionj1.y>tab[theGame.thePlayers[0].currentLocation].yt)
                                                {
                                                    positionj1.y=positionj1.y-10;
                                                }
                                                if (positionj1.y<=tab[theGame.thePlayers[0].currentLocation].yt)
                                                {
                                                    if (positionj1.x<tab[theGame.thePlayers[0].currentLocation].xl)
                                                        {
                                                        positionj1.x=positionj1.x+10;

                                                        }
                                                }
                                                if((positionj1.x>=tab[theGame.thePlayers[0].currentLocation].xl)&&(positionj1.y<=tab[theGame.thePlayers[0].currentLocation].yt))
                                                {
                                                    endeplacement=0;
                                                }
                                              }


                                          }
                                          if((20<=lastlocationj1)&&(lastlocationj1<=29))
                                          {
                                              if((20<=theGame.thePlayers[0].currentLocation)&&(theGame.thePlayers[0].currentLocation<=29))
                                              {
                                                  if (positionj1.x<tab[theGame.thePlayers[0].currentLocation].xl)
                                                {
                                                    positionj1.x=positionj1.x+10;

                                                }
                                                if(positionj1.x>=tab[theGame.thePlayers[0].currentLocation].xl)
                                                {
                                                    endeplacement=0;
                                                }
                                              }
                                              else
                                              {
                                                 if (positionj1.x<tab[theGame.thePlayers[0].currentLocation].xl)
                                                {
                                                    positionj1.x=positionj1.x+10;

                                                }
                                                if (positionj1.x>=tab[theGame.thePlayers[0].currentLocation].xl)
                                                {
                                                    if (positionj1.y<tab[theGame.thePlayers[0].currentLocation].yt)
                                                        {
                                                        positionj1.y=positionj1.y+10;

                                                        }
                                                }
                                                 if((positionj1.x>=tab[theGame.thePlayers[0].currentLocation].xl)&&(positionj1.y>=tab[theGame.thePlayers[0].currentLocation].yt))
                                                {
                                                    endeplacement=0;
                                                }
                                              }


                                          }
                                          if((30<=lastlocationj1)&&(lastlocationj1<=39))
                                          {
                                              if((30<=theGame.thePlayers[0].currentLocation)&&(theGame.thePlayers[0].currentLocation<=39))
                                              {
                                                 if (positionj1.y<tab[theGame.thePlayers[0].currentLocation].yt)
                                                {
                                                    positionj1.y=positionj1.y+10;

                                                }
                                                if(positionj1.y>=tab[theGame.thePlayers[0].currentLocation].yt)
                                                {
                                                    endeplacement=0;
                                                }
                                              }
                                              else
                                              {
                                                 if (positionj1.y<tab[theGame.thePlayers[0].currentLocation].yt)
                                                {
                                                    positionj1.y=positionj1.y+10;

                                                }
                                                if (positionj1.y>=tab[theGame.thePlayers[0].currentLocation].yt)
                                                {
                                                    if (positionj1.x>tab[theGame.thePlayers[0].currentLocation].xl)
                                                        {
                                                        positionj1.x=positionj1.x-10;

                                                        }
                                                }
                                                 if((positionj1.y>=tab[theGame.thePlayers[0].currentLocation].yt)&&(positionj1.x<=tab[theGame.thePlayers[0].currentLocation].xl))
                                                {
                                                    endeplacement=0;
                                                }
                                              }


                                          }

                                        if(!endeplacement)
                                        {
                                            int a=theGame.thePlayers[0].currentLocation;
                                            switch(a)
                                            {
                                                case 0:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, wouldubuy, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("goj1_b.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;
                                                case 10:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, wouldubuy, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                  imageDeFond=IMG_Load("jailj1_b.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;

                                                break;
                                                case 20:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, wouldubuy, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("freeparkingpotj1_b.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;
                                                case 2:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, chanceouchest, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("communitychest1j1.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;


                                                case 17:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, chanceouchest, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("communitychest1j1.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;
                                                case 33:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, chanceouchest, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("communitychest2j1.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;
                                                case 7:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, chanceouchest, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("chance1j1.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;
                                                case 22:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, chanceouchest, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("chance1j1.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;
                                                case 36:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, chanceouchest, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("chance2j1.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;
                                                case 30:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, wouldubuy, 0,NULL);
                                                theGame.thePlayers[0].currentLocation=10;
                                                positionj1.x=tab[10].xl;
                                                positionj1.y=tab[10].yt;
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("jailj1.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                theGame.thePlayers[0].memo_prison=1;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;
                                                case 38:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, wouldubuy, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("luxuryj1_b.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;
                                                default:
                                                if(tab[a].etat==1)
                                                {
                                                    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, wouldubuy, 0,NULL);
                                                    SDL_FreeSurface(imageDeFond);
                                                   imageDeFond = tab_j1_b[theGame.thePlayers[0].currentLocation];
                                                   imaged1=NULL;
                                                   imaged2=NULL;
                                                   att_start=0;att_die=0;att_buy=1;att_finish=0;
                                                }
                                                else
                                                {
                                                    if((tab[a].etat==2)&&(tab[a].appartenance==2))
                                                       {
                                                           FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, wouldubuy, 0,NULL);
                                                           SDL_FreeSurface(imageDeFond);
                                                           imageDeFond = IMG_Load("payrentj1toj2.png");
                                                          /* int nb=tab[a].nb_maisons;
                                                           switch(nb)
                                                           {
                                                               case 0:
                                                               sprintf(renttab, "$ %i", tab[a].rent0);break;
                                                               case 1:
                                                               sprintf(renttab, "$ %i", tab[a].rent1);break;
                                                               case 2:
                                                               sprintf(renttab, "$ %i", tab[a].rent2);break;
                                                               case 3:
                                                               sprintf(renttab, "$ %i", tab[a].rent3);break;
                                                               case 4:
                                                               sprintf(renttab, "$ %i", tab[a].rent4);break;
                                                               case 5:
                                                               sprintf(renttab, "$ %i", tab[a].rent5);break;
                                                           }
                                                           SDL_FreeSurface(rent);
                                                            rent = TTF_RenderText_Blended(police,renttab,blanc);*/
                                                           imaged1=NULL;
                                                           imaged2=NULL;
                                                           att_start=0;att_die=0;att_buy=1;att_finish=0;
                                                       }
                                                       else
                                                       {
                                                           if((tab[a].appartenance==1)&&((tab[a].etat==2)||(tab[a].etat==3)))
                                                           {
                                                               FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, wouldubuy, 0,NULL);
                                                               SDL_FreeSurface(imageDeFond);
                                                               imageDeFond = IMG_Load("ownpropertyj1.png");
                                                                imaged1=NULL;
                                                                imaged2=NULL;
                                                                att_start=0;att_die=0;att_buy=1;att_finish=0;abandon=0;
                                                           }
                                                           else
                                                           {
                                                               if((tab[a].appartenance==2)&&(tab[a].etat==3))
                                                               {
                                                                   FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, wouldubuy, 0,NULL);
                                                                   SDL_FreeSurface(imageDeFond);
                                                                   imageDeFond = IMG_Load("j1mortj2property.png");
                                                                imaged1=NULL;
                                                                imaged2=NULL;
                                                                att_start=0;att_die=0;att_buy=1;att_finish=0;abandon=0;
                                                               }
                                                           }
                                                       }
                                                }
                                                break;
                                            }

                                        }

                                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                        SDL_BlitSurface(imaged1, NULL, ecran, &positiond1);
                        SDL_BlitSurface(imaged2, NULL, ecran, &positiond2);
                        SDL_BlitSurface(imagej1, NULL, ecran, &positionj1);
                        SDL_BlitSurface(imagej2, NULL, ecran, &positionj2);
                       // SDL_BlitSurface(rent,NULL,ecran,&positionrent);
                        sprintf(soldep1,"$ %i",theGame.thePlayers[0].money);
                        sprintf(soldep2,"$ %i",theGame.thePlayers[1].money);
                        SDL_FreeSurface(soldej1);
                        SDL_FreeSurface(soldej2);
                        soldej1 = TTF_RenderText_Blended(police,soldep1,vertactif);
                        soldej2 = TTF_RenderText_Blended(police,soldep2,vertpassif);
                        SDL_BlitSurface(soldej1,NULL,ecran,&positionsoldej1_tj1);
                        SDL_BlitSurface(soldej2,NULL,ecran,&positionsoldej2_tj1);
                        int i=0;
                        for(i=0;i<40;i++)
                        {if((tab[i].etat==2)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_buyj1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_buyj2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_mortagej1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_mortagej2[i],NULL,ecran,&positionFond);
                        }
                         if(tab[i].nb_maisons==1)
                        {
                            SDL_BlitSurface(tab_1m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==2)
                        {
                            SDL_BlitSurface(tab_2m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==3)
                        {
                            SDL_BlitSurface(tab_3m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==4)
                        {
                            SDL_BlitSurface(tab_4m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==5)
                        {
                            SDL_BlitSurface(tab_5m[i],NULL,ecran,&positionFond);
                        }
                        }
                        SDL_Flip(ecran);
                                          }
                                      }
                                      //s'il veut acheter et a du solde suffisant donc il achète******************
                                      if(tab[theGame.thePlayers[0].currentLocation].etat==1)
                                      {
                                         if((att_buy)&&(246<=event.button.x)&&(event.button.x<=342) && (537<=event.button.y) && (event.button.y<=577)&&(theGame.thePlayers[0].money>tab[theGame.thePlayers[0].currentLocation].val_achat))
                                      {
                                          FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clicbuy, 0,NULL);
                                           int a=theGame.thePlayers[0].currentLocation;
                                          if((a==5)||(a==15)||(a==25)||(a==35))
                                          {theGame.thePlayers[0].railroadCounter+=1;

                                          }
                                          if((a==12)||(a==28)){theGame.thePlayers[0].utilityCounter+=1;
                                          }
                                          setMoney(tab[theGame.thePlayers[0].currentLocation].val_achat,1,&theGame.thePlayers[0]);
                                          tab[theGame.thePlayers[0].currentLocation].etat=2;tab[theGame.thePlayers[0].currentLocation].appartenance=1;
                                          theGame.thePlayers[0].nb_propriete+=1;
                                          SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj1.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;abandon=0;
                                      }
                                      }


                                      // s'il perd
                                      if((theGame.thePlayers[0].money<0)&&(theGame.thePlayers[0].nb_propriete==theGame.thePlayers[0].nb_propriete_mort))
                                      {
                                          SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("player2won.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;abandon=0;
                                      }
                                      /*
                                       //s'il a la possibilité de mortager allumer le bouton mortage
                                      if(theGame.thePlayers[0].nb_propriete>theGame.thePlayers[0].nb_propriete_mort)
                                      {
                                          boutonmortage=IMG_Load("mortagepermis.png");
                                      }
                                      else{boutonmortage=NULL;}

                                         //s'il a la possibilité de unmortager allumer le bouton unmortage
                                      if((theGame.thePlayers[0].nb_propriete_mort>0)&&(theGame.thePlayers[0].money>29))
                                      {
                                          boutonunmortage=IMG_Load("unmortagepermis.png");
                                      }
                                      else{boutonunmortage=NULL;}

                                       //s'il a la possibilité de build allumer le bouton build
                                      if((theGame.thePlayers[0].nb_propriete>0)&&(theGame.thePlayers[0].money>50))
                                      {
                                          boutonbuild=IMG_Load("buildpermis.png");
                                      }
                                      else{boutonbuild=NULL;}

                                      //s'il a la possibilité de sell allumer le bouton sell
                                      if(theGame.thePlayers[0].nb_maisons>0)
                                      {
                                          boutonsell=IMG_Load("sellpermis.png");
                                      }
                                      else{boutonsell=NULL;}
                                        */
                                       //s'il tombe dans la propriete de son opponent et n'est pas mort et solde suffisant
                                      if((tab[theGame.thePlayers[0].currentLocation].etat==2)&&(tab[theGame.thePlayers[0].currentLocation].appartenance==2))
                                      {
                                          int a=theGame.thePlayers[0].currentLocation;
                                          int nb=tab[a].nb_maisons;
                                          int x;
                                          if((a==5)||(a==15)||(a==25)||(a==35))
                                          {
                                              switch(theGame.thePlayers[1].railroadCounter)
                                              {
                                                  case 1:x=25;break;
                                                  case 2:x=50;break;
                                                  case 3:x=100;break;
                                                  case 4:x=200;break;
                                              }
                                          }
                                          else
                                          {
                                              if((a==12)||(a==28))
                                              {
                                                  switch(theGame.thePlayers[1].utilityCounter)
                                                  {
                                                      case 1:x=4*theGame.thePlayers[0].dieRoll;
                                                      case 2:x=10*theGame.thePlayers[0].dieRoll;
                                                  }
                                              }
                                              else
                                              {
                                                  switch(nb)
                                                           {
                                                               case 0:
                                                               x=tab[a].rent0;break;
                                                               case 1:
                                                               x=tab[a].rent1;break;
                                                               case 2:
                                                               x=tab[a].rent2;break;
                                                               case 3:
                                                                x=tab[a].rent3;break;
                                                               case 4:
                                                                x=tab[a].rent4;break;
                                                               case 5:
                                                                x=tab[a].rent5;break;
                                                           }
                                              }
                                          }

                                           if((att_buy)&&(316<=event.button.x)&&(event.button.x<=412) && (346<=event.button.y) && (event.button.y<=386)&&(theGame.thePlayers[0].money>x))
                                           {
                                            FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clicbuy, 0,NULL);

                                                               setMoney(x,1,&theGame.thePlayers[0]);
                                                               setMoney(x,0,&theGame.thePlayers[1]);
                                            SDL_FreeSurface(imageDeFond);
                                           imageDeFond = IMG_Load("finishturnj1.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;abandon=0;
                                           }
                                      }
                                      //s'il tombe ds sa propriete et elle est acheté ou mortagé
                                      if((tab[theGame.thePlayers[0].currentLocation].appartenance==1)&&((tab[theGame.thePlayers[0].currentLocation].etat==2)||(tab[theGame.thePlayers[0].currentLocation].etat==3)))
                                      {
                                           if((att_buy)&&(377<=event.button.x)&&(event.button.x<=473) && (397<=event.button.y) && (event.button.y<=437))
                                           {
                                               FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, simpleclick, 0,NULL);
                                               SDL_FreeSurface(imageDeFond);
                                               imageDeFond=IMG_Load("finishturnj1.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                           }
                                      }
                                      // s'il tombe ds son opponent property mais elle est mortagé

                                          if((tab[theGame.thePlayers[0].currentLocation].appartenance==2)&&(tab[theGame.thePlayers[0].currentLocation].etat==3))
                                          {
                                             if((att_buy)&&(377<=event.button.x)&&(event.button.x<=473) && (397<=event.button.y) && (event.button.y<=437))
                                           {
                                               FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, simpleclick, 0,NULL);
                                               SDL_FreeSurface(imageDeFond);
                                               imageDeFond=IMG_Load("finishturnj1.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                           }
                                          }

                                      //s'il s'agit d'un chance ou community chest et solde suffisant .......
                                      if((att_buy)&&(317<=event.button.x)&&(event.button.x<=413) && (448<=event.button.y) && (event.button.y<=488))
                                      {
                                          int a=theGame.thePlayers[0].currentLocation;
                                          if((a==7)||(a==22))
                                          {
                                              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, okchanceouchest, 0,NULL);
                                            setMoney(50,0,&theGame.thePlayers[0]);
                                            SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj1.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          }
                                          if((a==36)&&(theGame.thePlayers[0].money>=15))
                                          {
                                              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, okchanceouchest, 0,NULL);
                                            setMoney(15,1,&theGame.thePlayers[0]);
                                            SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj1.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          }
                                          if((a==2)||(a==17))
                                          {
                                              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, okchanceouchest, 0,NULL);
                                            setMoney(50,0,&theGame.thePlayers[0]);
                                            setMoney(50,1,&theGame.thePlayers[1]);
                                            SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj1.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          }
                                          if((a==33)&&(theGame.thePlayers[0].money>=100))
                                          {
                                              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, okchanceouchest, 0,NULL);
                                            setMoney(100,1,&theGame.thePlayers[0]);
                                            SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj1.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          }
                                      }
                                      // S'il s'agit d'une luxure et solde suffisant
                                      if((att_buy)&&(377<=event.button.x)&&(event.button.x<=473) && (397<=event.button.y) && (event.button.y<=437))
                                      {
                                          int a=theGame.thePlayers[0].currentLocation;
                                          if((a==38)&&(theGame.thePlayers[0].money>=75))
                                          {
                                            setMoney(75,1,&theGame.thePlayers[0]);
                                            FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clicbuy, 0,NULL);
                                            SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj1.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          }
                                      }
                                      // S'il s'agit de la case départ
                                      if((att_buy)&&(315<=event.button.x)&&(event.button.x<=411) && (440<=event.button.y) && (event.button.y<=480))
                                      {
                                          int a=theGame.thePlayers[0].currentLocation;
                                          if(a==0)
                                          {
                                              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, simpleclick, 0,NULL);
                                              SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj1.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          }
                                      }
                                      // S'il s'agit du prison
                                      if(theGame.thePlayers[0].memo_prison==0)
                                      {
                                          if((att_buy)&&(377<=event.button.x)&&(event.button.x<=473) && (397<=event.button.y) && (event.button.y<=437))
                                      {
                                          int a=theGame.thePlayers[0].currentLocation;
                                          if(a==10)
                                          {
                                              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, simpleclick, 0,NULL);
                                              SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj1.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          }
                                      }
                                      }
                                      else
                                      {
                                          if((att_buy)&&(354<=event.button.x)&&(event.button.x<=493) && (382<=event.button.y) && (event.button.y<=439))
                                      {
                                          int a=theGame.thePlayers[0].currentLocation;
                                          if(a==10)
                                          {
                                              SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj1.png");
                                          FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clicbuy, 0,NULL);
                                          setMoney(50,1,&theGame.thePlayers[0]);
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          theGame.thePlayers[0].memo_prison=0;
                                          }
                                      }
                                      }
                                      // S'il s'agit d'un free parking pot
                                      if((att_buy)&&(377<=event.button.x)&&(event.button.x<=473) && (397<=event.button.y) && (event.button.y<=437))
                                      {
                                          int a=theGame.thePlayers[0].currentLocation;
                                          if(a==20)
                                          {
                                              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clicbuy, 0,NULL);
                                              setMoney(250,0,&theGame.thePlayers[0]);
                                              SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj1.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          }
                                      }
                                      // S'il s'agit d'une income tax et solde suffisant
                                      if((att_buy)&&(377<=event.button.x)&&(event.button.x<=473) && (397<=event.button.y) && (event.button.y<=437))
                                      {
                                          int a=theGame.thePlayers[0].currentLocation;
                                          if((a==4)&&(theGame.thePlayers[0].money>=200))
                                          {
                                              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clicbuy, 0,NULL);
                                            setMoney(200,1,&theGame.thePlayers[0]);
                                            SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj1.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          }
                                      }
                                        /*
                                      // S'il veut acheter et n'a pas de solde donc mortage*****************
                                      if((att_buy)&&(320<=event.button.x)&&(event.button.x<=462) && (720<=event.button.y) && (event.button.y<=760)&&(theGame.thePlayers[0].money<tab[theGame.thePlayers[0].currentLocation].val_achat))
                                      {
                                          int continuermortage=1;
                                          imageDeFond=IMG_Load("boardcleanshadow.png");
                                          while(continuermortage)
                                          {
                                             SDL_WaitEvent(&event);
                                             switch(event.type)
                                             {
                                                    case SDL_QUIT:
                                                    continuermortage=0;continuerjeu=0;continuer=0;
                                                    imageDeFond = tab_j1_b[theGame.thePlayers[0].currentLocation];
                                                    break;
                                                    case SDL_KEYDOWN:
                                                    switch(event.key.keysym.sym)
                                                    {
                                                    case SDLK_ESCAPE:
                                                    continuermortage=0;
                                                    imageDeFond = tab_j1_b[theGame.thePlayers[0].currentLocation];
                                                    }
                                                    break;
                                                    case SDL_MOUSEBUTTONUP:
                                                    if (event.button.button == SDL_BUTTON_LEFT)
                                                    {
                                                        int i=0;
                                                        for(i=0;i<40;i++)
                                                        {
                                                            if((tab[i].xl<=event.button.x)&&(event.button.x<=tab[i].xr)&&(tab[i].yt<=event.button.y)&&(event.button.y<=tab[i].yd))
                                                            {
                                                                tab[i].etat=3;
                                                                setMoney(tab[i].val_achat/2,0,&theGame.thePlayers[0]);
                                                            }
                                                        }

                                                    }
                                                    break;
                                             }
                                             SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                        sprintf(soldep1,"$ %i",theGame.thePlayers[0].money);
                        sprintf(soldep2,"$ %i",theGame.thePlayers[1].money);
                        SDL_FreeSurface(soldej1);
                        SDL_FreeSurface(soldej2);
                        soldej1 = TTF_RenderText_Blended(police,soldep1,vertactif);
                        soldej2 = TTF_RenderText_Blended(police,soldep2,vertpassif);
                        SDL_BlitSurface(soldej1,NULL,ecran,&positionsoldej1_tj1);
                        SDL_BlitSurface(soldej2,NULL,ecran,&positionsoldej2_tj1);
                        int i=0;
                        for(i=0;i<40;i++)
                        {if((tab[i].etat==2)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_buyj1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_buyj2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_mortagej1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_mortagej2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==1))
                        {
                            SDL_BlitSurface(tab_illum[i],NULL,ecran,&positionFond);
                        }
                        }
                        SDL_BlitSurface(imagej1, NULL, ecran, &positionj1);
                        SDL_BlitSurface(imagej2, NULL, ecran, &positionj2);
                        SDL_Flip(ecran);
                                           }

                                         }*/
                                         // S'il clique mortage *********************
                                          if((theGame.thePlayers[0].nb_propriete>theGame.thePlayers[0].nb_propriete_mort)&&(320<=event.button.x)&&(event.button.x<=462) && (720<=event.button.y) && (event.button.y<=760)&&(!att_buy))
                                      {
                                          int continuermortage=1;
                                          SDL_FreeSurface(imageDeFond);
                                          FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, mort, 0,NULL);
                                          imageDeFond=IMG_Load("boardcleanshadow.png");
                                          while(continuermortage)
                                          {
                                             SDL_WaitEvent(&event);
                                             switch(event.type)
                                             {
                                                    case SDL_QUIT:
                                                    continuermortage=0;continuerjeu=0;continuer=0;
                                                    imageDeFond = tab_j1_b[theGame.thePlayers[0].currentLocation];
                                                    break;
                                                    case SDL_KEYDOWN:
                                                    switch(event.key.keysym.sym)
                                                    {
                                                    case SDLK_ESCAPE:
                                                    continuermortage=0;
                                                    if(att_finish==1)
                                                    {

                                                        imageDeFond = IMG_Load("finishturnj1.png");
                                                    }
                                                    else
                                                    {
                                                        if(att_buy==1) {
                                                            imageDeFond = tab_j1_b[theGame.thePlayers[0].currentLocation];}
                                                        else
                                                        {
                                                        if(att_die==1){
                                                            imageDeFond=IMG_Load("rolldicej1.png");}
                                                        }
                                                    }
                                                    break;
                                                    }
                                                    break;
                                                    case SDL_MOUSEBUTTONUP:
                                                    if (event.button.button == SDL_BUTTON_LEFT)
                                                    {
                                                        int i=0;
                                                        for(i=0;i<40;i++)
                                                        {
                                                            if((tab[i].xl<=event.button.x)&&(event.button.x<=tab[i].xr)&&(tab[i].yt<=event.button.y)&&(event.button.y<=tab[i].yd)&&(tab[i].etat==2)&&(tab[i].appartenance==1)&&(!att_buy))
                                                            {
                                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clickpropbuildoumort, 0,NULL);
                                                                tab[i].etat=3;
                                                                setMoney(tab[i].val_achat/2,0,&theGame.thePlayers[0]);
                                                                theGame.thePlayers[0].nb_propriete_mort+=1;
                                                            }
                                                        }

                                                    }
                                                    break;
                                             }
                                             SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                        sprintf(soldep1,"$ %i",theGame.thePlayers[0].money);
                        sprintf(soldep2,"$ %i",theGame.thePlayers[1].money);
                        SDL_FreeSurface(soldej1);
                        SDL_FreeSurface(soldej2);
                        soldej1 = TTF_RenderText_Blended(police,soldep1,vertactif);
                        soldej2 = TTF_RenderText_Blended(police,soldep2,vertpassif);
                        SDL_BlitSurface(soldej1,NULL,ecran,&positionsoldej1_tj1);
                        SDL_BlitSurface(soldej2,NULL,ecran,&positionsoldej2_tj1);
                        int i=0;
                        for(i=0;i<40;i++)
                        {if((tab[i].etat==2)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_buyj1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_buyj2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_mortagej1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_mortagej2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==1)&&(tab[i].nb_maisons==0))
                        {
                            SDL_BlitSurface(tab_illum[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==1)
                        {
                            SDL_BlitSurface(tab_1m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==2)
                        {
                            SDL_BlitSurface(tab_2m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==3)
                        {
                            SDL_BlitSurface(tab_3m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==4)
                        {
                            SDL_BlitSurface(tab_4m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==5)
                        {
                            SDL_BlitSurface(tab_5m[i],NULL,ecran,&positionFond);
                        }
                        }
                        SDL_BlitSurface(imagej1, NULL, ecran, &positionj1);
                        SDL_BlitSurface(imagej2, NULL, ecran, &positionj2);
                        SDL_Flip(ecran);
                                           }

                                         }

                                        // S'il clique unmortage *********************
                                      if((theGame.thePlayers[0].nb_propriete_mort>0)&&(theGame.thePlayers[0].money>29)&&(469<=event.button.x)&&(event.button.x<=611) && (720<=event.button.y) && (event.button.y<=760)&&(!att_buy))
                                      {
                                          int continuerunmortage=1;
                                          SDL_FreeSurface(imageDeFond);
                                          FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, mort, 0,NULL);
                                          imageDeFond=IMG_Load("boardcleanshadow.png");
                                          while(continuerunmortage)
                                          {
                                             SDL_WaitEvent(&event);
                                             switch(event.type)
                                             {
                                                    case SDL_QUIT:
                                                    continuerunmortage=0;continuerjeu=0;continuer=0;
                                                    SDL_FreeSurface(imageDeFond);
                                                    imageDeFond = tab_j1_b[theGame.thePlayers[0].currentLocation];
                                                    break;
                                                    case SDL_KEYDOWN:
                                                    switch(event.key.keysym.sym)
                                                    {
                                                    case SDLK_ESCAPE:
                                                    continuerunmortage=0;
                                                    if(att_finish==1)
                                                    {

                                                        imageDeFond = IMG_Load("finishturnj1.png");
                                                    }
                                                    else
                                                    {
                                                        if(att_buy==1) {
                                                            imageDeFond = tab_j1_b[theGame.thePlayers[0].currentLocation];}
                                                        else
                                                        {
                                                        if(att_die==1){
                                                            imageDeFond=IMG_Load("rolldicej1.png");}
                                                        }
                                                    }
                                                    break;
                                                    }
                                                    break;
                                                    case SDL_MOUSEBUTTONUP:
                                                    if (event.button.button == SDL_BUTTON_LEFT)
                                                    {
                                                        int i=0;
                                                        for(i=0;i<40;i++)
                                                        {
                                                            if((tab[i].xl<=event.button.x)&&(event.button.x<=tab[i].xr)&&(tab[i].yt<=event.button.y)&&(event.button.y<=tab[i].yd)&&(tab[i].etat==3)&&(tab[i].appartenance==1)&&((tab[i].val_achat<theGame.thePlayers[0].money)))
                                                            {
                                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clickpropbuildoumort, 0,NULL);
                                                                tab[i].etat=2;
                                                                setMoney(tab[i].val_achat,1,&theGame.thePlayers[0]);
                                                                theGame.thePlayers[0].nb_propriete_mort-=1;
                                                            }
                                                        }

                                                    }
                                                    break;
                                             }
                                             SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                        sprintf(soldep1,"$ %i",theGame.thePlayers[0].money);
                        sprintf(soldep2,"$ %i",theGame.thePlayers[1].money);
                        SDL_FreeSurface(soldej1);
                        SDL_FreeSurface(soldej2);
                        soldej1 = TTF_RenderText_Blended(police,soldep1,vertactif);
                        soldej2 = TTF_RenderText_Blended(police,soldep2,vertpassif);
                        SDL_BlitSurface(soldej1,NULL,ecran,&positionsoldej1_tj1);
                        SDL_BlitSurface(soldej2,NULL,ecran,&positionsoldej2_tj1);
                        int i=0;
                        for(i=0;i<40;i++)
                        {if((tab[i].etat==2)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_buyj1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_buyj2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_mortagej1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_mortagej2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==1)&&(tab[i].val_achat<=theGame.thePlayers[0].money))
                        {
                            SDL_BlitSurface(tab_illum[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==1)
                        {
                            SDL_BlitSurface(tab_1m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==2)
                        {
                            SDL_BlitSurface(tab_2m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==3)
                        {
                            SDL_BlitSurface(tab_3m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==4)
                        {
                            SDL_BlitSurface(tab_4m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==5)
                        {
                            SDL_BlitSurface(tab_5m[i],NULL,ecran,&positionFond);
                        }
                        }
                        SDL_BlitSurface(imagej1, NULL, ecran, &positionj1);
                        SDL_BlitSurface(imagej2, NULL, ecran, &positionj2);
                        SDL_Flip(ecran);
                                           }

                                         }


                                            // S'il clique build *********************
                                      if((theGame.thePlayers[0].nb_propriete>0)&&(theGame.thePlayers[0].money>50)&&(113<=event.button.x)&&(event.button.x<=209) && (720<=event.button.y) && (event.button.y<=760)&&(!att_buy))
                                      {
                                          int continuerbuild=1;
                                          SDL_FreeSurface(imageDeFond);
                                          FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, mort, 0,NULL);
                                          imageDeFond=IMG_Load("boardcleanshadow.png");
                                          while(continuerbuild)
                                          {
                                             SDL_WaitEvent(&event);
                                             switch(event.type)
                                             {
                                                    case SDL_QUIT:
                                                    continuerbuild=0;continuerjeu=0;continuer=0;
                                                    SDL_FreeSurface(imageDeFond);
                                                    imageDeFond = tab_j1_b[theGame.thePlayers[0].currentLocation];
                                                    break;
                                                    case SDL_KEYDOWN:
                                                    switch(event.key.keysym.sym)
                                                    {
                                                    case SDLK_ESCAPE:
                                                    continuerbuild=0;
                                                    if(att_finish==1)
                                                    {

                                                        imageDeFond = IMG_Load("finishturnj1.png");
                                                    }
                                                    else
                                                    {
                                                        if(att_buy==1) {
                                                            imageDeFond = tab_j1_b[theGame.thePlayers[0].currentLocation];}
                                                        else
                                                        {
                                                        if(att_die==1){
                                                            imageDeFond = IMG_Load("rolldicej1.png");}
                                                        }
                                                    }
                                                    break;
                                                    }
                                                    break;
                                                    case SDL_MOUSEBUTTONUP:
                                                    if (event.button.button == SDL_BUTTON_LEFT)
                                                    {
                                                        int i=0;
                                                        for(i=0;i<40;i++)
                                                        {
                                                            if((tab[i].xl<=event.button.x)&&(event.button.x<=tab[i].xr)&&(tab[i].yt<=event.button.y)&&(event.button.y<=tab[i].yd)&&(tab[i].etat==2)&&(tab[i].appartenance==1)&&(i!=12)&&(i!=28)&&(i!=5)&&(i!=15)&&(i!=25)&&(i!=35)&&((tab[i].val_maison<theGame.thePlayers[1].money)))
                                                            {
                                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clickpropbuildoumort, 0,NULL);
                                                                tab[i].nb_maisons+=1;
                                                                setMoney(tab[i].val_maison,1,&theGame.thePlayers[0]);
                                                                theGame.thePlayers[0].nb_maisons+=1;
                                                            }
                                                        }

                                                    }
                                                    break;
                                             }
                                             SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                        sprintf(soldep1,"$ %i",theGame.thePlayers[0].money);
                        sprintf(soldep2,"$ %i",theGame.thePlayers[1].money);
                        SDL_FreeSurface(soldej1);
                        SDL_FreeSurface(soldej2);
                        soldej1 = TTF_RenderText_Blended(police,soldep1,vertactif);
                        soldej2 = TTF_RenderText_Blended(police,soldep2,vertpassif);
                        SDL_BlitSurface(soldej1,NULL,ecran,&positionsoldej1_tj1);
                        SDL_BlitSurface(soldej2,NULL,ecran,&positionsoldej2_tj1);
                        int i=0;
                        for(i=0;i<40;i++)
                        {if((tab[i].etat==2)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_buyj1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_buyj2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_mortagej1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_mortagej2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==1)&&(tab[i].val_maison<=theGame.thePlayers[0].money)&&(tab[i].nb_maisons<5)&&(i!=5)&&(i!=15)&&(i!=25)&&(i!=35)&&(i!=12)&&(i!=28))
                        {
                            SDL_BlitSurface(tab_illum[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==1)
                        {
                            SDL_BlitSurface(tab_1m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==2)
                        {
                            SDL_BlitSurface(tab_2m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==3)
                        {
                            SDL_BlitSurface(tab_3m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==4)
                        {
                            SDL_BlitSurface(tab_4m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==5)
                        {
                            SDL_BlitSurface(tab_5m[i],NULL,ecran,&positionFond);
                        }
                        }
                        SDL_BlitSurface(imagej1, NULL, ecran, &positionj1);
                        SDL_BlitSurface(imagej2, NULL, ecran, &positionj2);
                        SDL_Flip(ecran);
                                           }

                                         }



                                            // S'il clique sell *********************
                                      if((theGame.thePlayers[0].nb_maisons)&&(217<=event.button.x)&&(event.button.x<=313) && (720<=event.button.y) && (event.button.y<=760)&&(!att_buy))
                                      {
                                          int continuersell=1;
                                          SDL_FreeSurface(imageDeFond);
                                          FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, mort, 0,NULL);
                                          imageDeFond=IMG_Load("boardcleanshadow.png");
                                          while(continuersell)
                                          {
                                             SDL_WaitEvent(&event);
                                             switch(event.type)
                                             {
                                                    case SDL_QUIT:
                                                    continuersell=0;continuerjeu=0;continuer=0;
                                                    SDL_FreeSurface(imageDeFond);
                                                    imageDeFond = tab_j1_b[theGame.thePlayers[0].currentLocation];
                                                    break;
                                                    case SDL_KEYDOWN:
                                                    switch(event.key.keysym.sym)
                                                    {
                                                    case SDLK_ESCAPE:
                                                    continuersell=0;
                                                    if(att_finish==1)
                                                    {

                                                        imageDeFond = IMG_Load("finishturnj1.png");
                                                    }
                                                    else
                                                    {
                                                        if(att_buy==1) {
                                                            imageDeFond = tab_j1_b[theGame.thePlayers[0].currentLocation];}
                                                        else
                                                        {
                                                        if(att_die==1){
                                                            imageDeFond=IMG_Load("rolldicej1.png");}
                                                        }
                                                    }
                                                     break;
                                                    }
                                                    break;
                                                    case SDL_MOUSEBUTTONUP:
                                                    if (event.button.button == SDL_BUTTON_LEFT)
                                                    {
                                                        int i=0;
                                                        for(i=0;i<40;i++)
                                                        {
                                                            if((tab[i].xl<=event.button.x)&&(event.button.x<=tab[i].xr)&&(tab[i].yt<=event.button.y)&&(event.button.y<=tab[i].yd)&&(tab[i].etat==2)&&(tab[i].nb_maisons>0)&&(tab[i].appartenance==1))
                                                            {
                                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clickpropbuildoumort, 0,NULL);
                                                                tab[i].nb_maisons-=1;
                                                                setMoney(tab[i].val_maison/2,0,&theGame.thePlayers[0]);
                                                                theGame.thePlayers[0].nb_maisons-=1;
                                                            }
                                                        }

                                                    }
                                                    break;
                                             }
                                             SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                        sprintf(soldep1,"$ %i",theGame.thePlayers[0].money);
                        sprintf(soldep2,"$ %i",theGame.thePlayers[1].money);
                        SDL_FreeSurface(soldej1);
                        SDL_FreeSurface(soldej2);
                        soldej1 = TTF_RenderText_Blended(police,soldep1,vertactif);
                        soldej2 = TTF_RenderText_Blended(police,soldep2,vertpassif);
                        SDL_BlitSurface(soldej1,NULL,ecran,&positionsoldej1_tj1);
                        SDL_BlitSurface(soldej2,NULL,ecran,&positionsoldej2_tj1);
                        int i=0;
                        for(i=0;i<40;i++)
                        {if((tab[i].etat==2)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_buyj1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_buyj2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_mortagej1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_mortagej2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==1)&&(tab[i].nb_maisons>0))
                        {
                            SDL_BlitSurface(tab_illum[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==1)
                        {
                            SDL_BlitSurface(tab_1m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==2)
                        {
                            SDL_BlitSurface(tab_2m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==3)
                        {
                            SDL_BlitSurface(tab_3m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==4)
                        {
                            SDL_BlitSurface(tab_4m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==5)
                        {
                            SDL_BlitSurface(tab_5m[i],NULL,ecran,&positionFond);
                        }
                        }
                        SDL_BlitSurface(imagej1, NULL, ecran, &positionj1);
                        SDL_BlitSurface(imagej2, NULL, ecran, &positionj2);
                        SDL_Flip(ecran);
                                           }

                                         }



                                         // S'il clique finish turn


                                      }
                                      if(theGame.currentPlayer==2)
                                      {
                                      //s'il attend de cliquer roll dice et puis deplacement et pop up ********
                                      if((326<=event.button.x)&&(event.button.x<=480) && (511<=event.button.y) && (event.button.y<=573) && (att_die))
                                      {
                                          FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clicrolletdepl, 0,NULL);
                                          SDL_FreeSurface(imageDeFond);
                                          imageDeFond = IMG_Load("boardcleanj2.png");
                                          soldej1 = TTF_RenderText_Blended(police,soldep1,vertpassif);
                                          soldej2 = TTF_RenderText_Blended(police,soldep2,vertactif);
                                          int d1=firstDie(&theGame.thePlayers[1]);
                                          int d2=secondDie(&theGame.thePlayers[1]);
                                          theGame.thePlayers[1].dieRoll=getRoll(&theGame.thePlayers[1]);

                                          setPositionRoll(&theGame.thePlayers[1],theGame.thePlayers[1].currentLocation,theGame.thePlayers[1].dieRoll);
                                          switch(d1)
                                          {
                                              case 1:imaged1 = IMG_Load("de1.png");break;
                                              case 2:imaged1 = IMG_Load("de2.png");break;
                                              case 3:imaged1 = IMG_Load("de3.png");break;
                                              case 4:imaged1 = IMG_Load("de4.png");break;
                                              case 5:imaged1 = IMG_Load("de5.png");break;
                                              case 6:imaged1 = IMG_Load("de6.png");break;
                                          }
                                          switch(d2)
                                          {
                                              case 1:imaged2 = IMG_Load("de1.png");break;
                                              case 2:imaged2 = IMG_Load("de2.png");break;
                                              case 3:imaged2 = IMG_Load("de3.png");break;
                                              case 4:imaged2 = IMG_Load("de4.png");break;
                                              case 5:imaged2 = IMG_Load("de5.png");break;
                                              case 6:imaged2 = IMG_Load("de6.png");break;
                                          }
                                          imagej1 = IMG_Load("j1.png");
                                          imagej2 = IMG_Load("j2.png");
                                          SDL_PollEvent(&event);
                                          int endeplacement=1;
                                          while(endeplacement)
                                          {

                                          if((0<=lastlocationj2)&&(lastlocationj2<=9))
                                          {
                                              if((0<=theGame.thePlayers[1].currentLocation)&&(theGame.thePlayers[1].currentLocation<=9))
                                              {
                                                 if (positionj2.x>tab[theGame.thePlayers[1].currentLocation].xl)
                                                {
                                                    positionj2.x=positionj2.x-10;

                                                }
                                                if(positionj2.x<=tab[theGame.thePlayers[1].currentLocation].xl)
                                                {
                                                    endeplacement=0;
                                                }
                                              }
                                              else
                                              {
                                                 if (positionj2.x>tab[theGame.thePlayers[1].currentLocation].xl)
                                                {
                                                    positionj2.x=positionj2.x-10;

                                                }
                                                if (positionj2.x<=tab[theGame.thePlayers[1].currentLocation].xl)
                                                {
                                                    if (positionj2.y>tab[theGame.thePlayers[1].currentLocation].yt)
                                                        {
                                                        positionj2.y=positionj2.y-10;

                                                        }
                                                }
                                                 if((positionj2.x<=tab[theGame.thePlayers[1].currentLocation].xl)&&(positionj2.y<=tab[theGame.thePlayers[1].currentLocation].yt))
                                                {
                                                    endeplacement=0;
                                                }
                                              }


                                          }
                                          if((10<=lastlocationj2)&&(lastlocationj2<=19))
                                          {
                                              if((10<=theGame.thePlayers[1].currentLocation)&&(theGame.thePlayers[1].currentLocation<=19))
                                              {
                                                if (positionj2.y>tab[theGame.thePlayers[1].currentLocation].yt)
                                                {
                                                    positionj2.y=positionj2.y-10;

                                                }
                                                if(positionj2.y<=tab[theGame.thePlayers[1].currentLocation].yt)
                                                {
                                                    endeplacement=0;
                                                }
                                              }
                                              else
                                              {
                                                if (positionj2.y>tab[theGame.thePlayers[1].currentLocation].yt)
                                                {
                                                    positionj2.y=positionj2.y-10;

                                                }
                                                if (positionj2.y<=tab[theGame.thePlayers[1].currentLocation].yt)
                                                {
                                                    if (positionj2.x<tab[theGame.thePlayers[1].currentLocation].xl)
                                                        {
                                                        positionj2.x=positionj2.x+10;

                                                        }
                                                }
                                                if((positionj2.x>=tab[theGame.thePlayers[1].currentLocation].xl)&&(positionj2.y<=tab[theGame.thePlayers[1].currentLocation].yt))
                                                {
                                                    endeplacement=0;
                                                }
                                              }

                                          }
                                          if((20<=lastlocationj2)&&(lastlocationj2<=29))
                                          {
                                              if((20<=theGame.thePlayers[1].currentLocation)&&(theGame.thePlayers[1].currentLocation<=29))
                                              {
                                                 if (positionj2.x<tab[theGame.thePlayers[1].currentLocation].xl)
                                                {
                                                    positionj2.x=positionj2.x+10;

                                                }
                                                 if(positionj2.x>=tab[theGame.thePlayers[1].currentLocation].xl)
                                                {
                                                    endeplacement=0;
                                                }
                                              }
                                              else
                                              {
                                                if (positionj2.x<tab[theGame.thePlayers[1].currentLocation].xl)
                                                {
                                                    positionj2.x=positionj2.x+10;

                                                }
                                                if (positionj2.x>=tab[theGame.thePlayers[1].currentLocation].xl)
                                                {
                                                    if (positionj2.y<tab[theGame.thePlayers[1].currentLocation].yt)
                                                        {
                                                        positionj2.y=positionj2.y+10;

                                                        }
                                                }
                                                if((positionj2.x>=tab[theGame.thePlayers[1].currentLocation].xl)&&(positionj2.y>=tab[theGame.thePlayers[1].currentLocation].yt))
                                                {
                                                    endeplacement=0;
                                                }
                                              }

                                          }
                                          if((30<=lastlocationj2)&&(lastlocationj2<=39))
                                          {
                                              if((30<=theGame.thePlayers[1].currentLocation)&&(theGame.thePlayers[1].currentLocation<=39))
                                              {
                                                 if (positionj2.y<tab[theGame.thePlayers[1].currentLocation].yt)
                                                {
                                                    positionj2.y=positionj2.y+10;

                                                }
                                                 if(positionj2.y>=tab[theGame.thePlayers[1].currentLocation].yt)
                                                {
                                                    endeplacement=0;
                                                }
                                              }
                                              else
                                              {
                                                if (positionj2.y<tab[theGame.thePlayers[1].currentLocation].yt)
                                                {
                                                    positionj2.y=positionj2.y+10;

                                                }
                                                if (positionj2.y>=tab[theGame.thePlayers[1].currentLocation].yt)
                                                {
                                                    if (positionj2.x>tab[theGame.thePlayers[1].currentLocation].xl)
                                                        {
                                                        positionj2.x=positionj2.x-10;

                                                        }
                                                }
                                                if((positionj2.y>=tab[theGame.thePlayers[1].currentLocation].yt)&&(positionj2.x<=tab[theGame.thePlayers[1].currentLocation].xl))
                                                {
                                                    endeplacement=0;
                                                }
                                              }

                                          }

                                        if(!endeplacement)
                                        {
                                            int a=theGame.thePlayers[1].currentLocation;

                                            switch(a)
                                            {

                                            case 0:
                                            FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, wouldubuy, 0,NULL);
                                            SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("goj2_b.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;
                                                case 10:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, wouldubuy, 0,NULL);
                                                    SDL_FreeSurface(imageDeFond);
                                                  imageDeFond=IMG_Load("jailj2_b.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;

                                                break;
                                                case 20:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, wouldubuy, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("freeparkingpotj2_b.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;
                                                case 2:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, chanceouchest, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("communitychest1j2.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;


                                                case 17:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, chanceouchest, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("communitychest1j2.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;
                                                case 33:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, chanceouchest, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("communitychest2j2.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;
                                                case 7:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, chanceouchest, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("chance1j2.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;
                                                case 22:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, chanceouchest, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("chance1j2.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;
                                                case 36:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, chanceouchest, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("chance2j2.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;
                                                case 30:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, wouldubuy, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                theGame.thePlayers[1].currentLocation=10;
                                                positionj2.x=tab[10].xl;
                                                positionj2.y=tab[10].yt;
                                                imageDeFond=IMG_Load("jailj2.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                theGame.thePlayers[1].memo_prison=1;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;
                                                case 38:
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, wouldubuy, 0,NULL);
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("luxuryj2_b.png");
                                                imaged1=NULL;
                                                imaged2=NULL;
                                                att_start=0;att_die=0;att_buy=1;att_finish=0;break;
                                                default:
                                                if(tab[a].etat==1)
                                                {
                                                    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, wouldubuy, 0,NULL);
                                                    SDL_FreeSurface(imageDeFond);
                                                   imageDeFond = tab_j2_b[theGame.thePlayers[1].currentLocation];
                                                   imaged1=NULL;
                                                   imaged2=NULL;
                                                   att_start=0;att_die=0;att_buy=1;att_finish=0;
                                                }
                                                else
                                                {
                                                    if((tab[a].etat==2)&&(tab[a].appartenance==1))
                                                       {
                                                           FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, wouldubuy, 0,NULL);
                                                           SDL_FreeSurface(imageDeFond);
                                                           imageDeFond = IMG_Load("payrentj2toj1.png");
                                                           /*int nb=tab[a].nb_maisons;
                                                           switch(nb)
                                                           {
                                                               case 0:
                                                               sprintf(renttab, "$ %i", tab[a].rent0);break;
                                                               case 1:
                                                               sprintf(renttab, "$ %i", tab[a].rent1);break;
                                                               case 2:
                                                               sprintf(renttab, "$ %i", tab[a].rent2);break;
                                                               case 3:
                                                               sprintf(renttab, "$ %i", tab[a].rent3);break;
                                                               case 4:
                                                               sprintf(renttab, "$ %i", tab[a].rent4);break;
                                                               case 5:
                                                               sprintf(renttab, "$ %i", tab[a].rent5);break;
                                                           }
                                                           SDL_FreeSurface(rent);
                                                            rent = TTF_RenderText_Blended(police,renttab,blanc);*/
                                                           imaged1=NULL;
                                                           imaged2=NULL;
                                                           att_start=0;att_die=0;att_buy=1;att_finish=0;
                                                       }
                                                       else
                                                       {
                                                           if((tab[a].appartenance==2)&&((tab[a].etat==2)||(tab[a].etat==3)))
                                                           {
                                                               FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, wouldubuy, 0,NULL);
                                                               SDL_FreeSurface(imageDeFond);
                                                               imageDeFond = IMG_Load("ownpropertyj2.png");
                                                                imaged1=NULL;
                                                                imaged2=NULL;
                                                                att_start=0;att_die=0;att_buy=1;att_finish=0;abandon=0;
                                                           }
                                                           else
                                                           {
                                                               if((tab[a].appartenance==1)&&(tab[a].etat==3))
                                                               {
                                                                   FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, wouldubuy, 0,NULL);
                                                                   SDL_FreeSurface(imageDeFond);
                                                                   imageDeFond = IMG_Load("j2mortj1property.png");
                                                                imaged1=NULL;
                                                                imaged2=NULL;
                                                                att_start=0;att_die=0;att_buy=1;att_finish=0;abandon=0;
                                                               }
                                                           }
                                                       }
                                                }
                                                /*
                                                imageDeFond = tab_j2_b[theGame.thePlayers[1].currentLocation];
                                            imaged1=NULL;
                                            imaged2=NULL;
                                            att_start=0;att_die=0;att_buy=1;att_finish=0;*/
                                            break;
                                            }
                                        }

                                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                        SDL_BlitSurface(imaged1, NULL, ecran, &positiond1);
                        SDL_BlitSurface(imaged2, NULL, ecran, &positiond2);
                        SDL_BlitSurface(imagej1, NULL, ecran, &positionj1);
                        SDL_BlitSurface(imagej2, NULL, ecran, &positionj2);
                        //SDL_BlitSurface(rent,NULL,ecran,&positionrent);
                        sprintf(soldep1,"$ %i",theGame.thePlayers[0].money);
                        sprintf(soldep2,"$ %i",theGame.thePlayers[1].money);
                        SDL_FreeSurface(soldej1);
                        SDL_FreeSurface(soldej2);
                        soldej1 = TTF_RenderText_Blended(police,soldep1,vertpassif);
                        soldej2 = TTF_RenderText_Blended(police,soldep2,vertactif);
                        SDL_BlitSurface(soldej1,NULL,ecran,&positionsoldej1_tj2);
                        SDL_BlitSurface(soldej2,NULL,ecran,&positionsoldej2_tj2);
                        int i=0;
                        for(i=0;i<40;i++)
                        {if((tab[i].etat==2)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_buyj1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_buyj2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_mortagej1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_mortagej2[i],NULL,ecran,&positionFond);
                        }
                         if(tab[i].nb_maisons==1)
                        {
                            SDL_BlitSurface(tab_1m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==2)
                        {
                            SDL_BlitSurface(tab_2m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==3)
                        {
                            SDL_BlitSurface(tab_3m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==4)
                        {
                            SDL_BlitSurface(tab_4m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==5)
                        {
                            SDL_BlitSurface(tab_5m[i],NULL,ecran,&positionFond);
                        }
                        }
                        SDL_Flip(ecran);
                                          }
                                      }
                                      //s'il veut acheter et a du solde suffisant donc il achète******************
                                      if((att_buy)&&(246<=event.button.x)&&(event.button.x<=342) && (537<=event.button.y) && (event.button.y<=577)&&(theGame.thePlayers[1].money>tab[theGame.thePlayers[1].currentLocation].val_achat))
                                      {
                                          int a=theGame.thePlayers[1].currentLocation;
                                          if((a==5)||(a==15)||(a==25)||(a==35)){theGame.thePlayers[1].railroadCounter+=1;
                                          }
                                          if((a==12)||(a==28)){theGame.thePlayers[1].utilityCounter+=1;
                                           }
                                           FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clicbuy, 0,NULL);
                                          setMoney(tab[theGame.thePlayers[1].currentLocation].val_achat,1,&theGame.thePlayers[1]);
                                          tab[theGame.thePlayers[1].currentLocation].etat=2;tab[theGame.thePlayers[1].currentLocation].appartenance=2;
                                          theGame.thePlayers[1].nb_propriete+=1;
                                          SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj2.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;abandon=0;
                                      }

                                       if((theGame.thePlayers[1].money<0)&&(theGame.thePlayers[1].nb_propriete==theGame.thePlayers[1].nb_propriete_mort))
                                      {
                                          SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("player1won.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;abandon=0;
                                      }
                                        /*
                                       //s'il a la possibilité de mortager allumer le bouton mortage
                                      if(theGame.thePlayers[1].nb_propriete>theGame.thePlayers[1].nb_propriete_mort)
                                      {
                                          boutonmortage=IMG_Load("mortagepermis.png");
                                      }
                                      else
                                      {
                                          boutonmortage=NULL;
                                      }
                                         //s'il a la possibilité de unmortager allumer le bouton unmortage
                                      if((theGame.thePlayers[1].nb_propriete_mort>0)&&(theGame.thePlayers[1].money>29))
                                      {
                                          boutonunmortage=IMG_Load("unmortagepermis.png");
                                      }
                                      else{boutonunmortage=NULL;}

                                       //s'il a la possibilité de build allumer le bouton build
                                      if((theGame.thePlayers[1].nb_propriete>0)&&(theGame.thePlayers[1].money>50))
                                      {
                                          boutonbuild=IMG_Load("buildpermis.png");
                                      }
                                      else{boutonbuild=NULL;}

                                      //s'il a la possibilité de sell allumer le bouton sell
                                      if(theGame.thePlayers[1].nb_maisons>0)
                                      {
                                          boutonsell=IMG_Load("sellpermis.png");
                                      }
                                      else{boutonsell=NULL;}
                                      */
                                      //s'il tombe dans la propriete de son opponent et n'est pas mort et solde suffisant
                                      if((tab[theGame.thePlayers[1].currentLocation].etat==2)&&(tab[theGame.thePlayers[1].currentLocation].appartenance==1))
                                      {
                                          int a=theGame.thePlayers[1].currentLocation;
                                          int nb=tab[a].nb_maisons;
                                          int x;
                                          if((a==5)||(a==15)||(a==25)||(a==35))
                                          {
                                              switch(theGame.thePlayers[0].railroadCounter)
                                              {
                                                  case 1:
                                                  x=25;break;
                                                  case 2:
                                                  x=50;break;
                                                  case 3:
                                                  x=100;break;
                                                  case 4:
                                                  x=200;break;
                                              }
                                          }
                                          else
                                          {
                                              if((a==12)||(a==28))
                                              {
                                                  switch(theGame.thePlayers[0].utilityCounter)
                                                  {
                                                      case 1:x=4*theGame.thePlayers[1].dieRoll;
                                                      case 2:x=10*theGame.thePlayers[1].dieRoll;
                                                  }
                                              }
                                              else
                                              {
                                                  switch(nb)
                                                           {
                                                               case 0:
                                                               x=tab[a].rent0;break;
                                                               case 1:
                                                               x=tab[a].rent1;break;
                                                               case 2:
                                                               x=tab[a].rent2;break;
                                                               case 3:
                                                                x=tab[a].rent3;break;
                                                               case 4:
                                                                x=tab[a].rent4;break;
                                                               case 5:
                                                                x=tab[a].rent5;break;
                                                           }
                                              }
                                          }

                                           if((att_buy)&&(316<=event.button.x)&&(event.button.x<=412) && (346<=event.button.y) && (event.button.y<=386)&&(theGame.thePlayers[1].money>x))
                                           {
                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clicbuy, 0,NULL);
                                                setMoney(x,0,&theGame.thePlayers[0]);
                                                setMoney(x,1,&theGame.thePlayers[1]);
                                                SDL_FreeSurface(imageDeFond);
                                                imageDeFond=IMG_Load("finishturnj2.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;abandon=0;
                                           }

                                           }
                                      //s'il tombe ds sa propriete et elle est acheté ou mortagé
                                      if((tab[theGame.thePlayers[1].currentLocation].appartenance==2)&&((tab[theGame.thePlayers[1].currentLocation].etat==2)||(tab[theGame.thePlayers[1].currentLocation].etat==3)))
                                      {
                                           if((att_buy)&&(377<=event.button.x)&&(event.button.x<=473) && (397<=event.button.y) && (event.button.y<=437))
                                           {
                                               FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, simpleclick, 0,NULL);
                                               SDL_FreeSurface(imageDeFond);
                                               imageDeFond=IMG_Load("finishturnj2.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                           }
                                      }
                                      // s'il tombe ds son opponent property mais elle est mortagé

                                          if((tab[theGame.thePlayers[1].currentLocation].appartenance==1)&&(tab[theGame.thePlayers[1].currentLocation].etat==3))
                                          {
                                             if((att_buy)&&(377<=event.button.x)&&(event.button.x<=473) && (397<=event.button.y) && (event.button.y<=437))
                                           {
                                               FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, simpleclick, 0,NULL);
                                               SDL_FreeSurface(imageDeFond);
                                               imageDeFond=IMG_Load("finishturnj2.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                           }
                                          }

                                      //s'il s'agit d'un chance ou community chest et solde suffisant .......
                                      if((att_buy)&&(317<=event.button.x)&&(event.button.x<=413) && (448<=event.button.y) && (event.button.y<=488))
                                      {
                                          int a=theGame.thePlayers[1].currentLocation;
                                          if(((a==7)||(a==22))&&(theGame.thePlayers[1].money>=15))
                                          {
                                              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, okchanceouchest, 0,NULL);
                                              setMoney(15,1,&theGame.thePlayers[1]);
                                              SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj2.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          }
                                          if((a==36)&&(theGame.thePlayers[1].money>=50))
                                          {
                                              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, okchanceouchest, 0,NULL);
                                            setMoney(50,1,&theGame.thePlayers[1]);
                                            setMoney(50,0,&theGame.thePlayers[0]);
                                            SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj2.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          }
                                          if((a==2)||(a==17))
                                          {
                                              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, okchanceouchest, 0,NULL);
                                            setMoney(25,0,&theGame.thePlayers[1]);
                                            SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj2.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          }
                                          if(a==33)
                                          {
                                              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, okchanceouchest, 0,NULL);
                                            setMoney(100,0,&theGame.thePlayers[1]);
                                            SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj2.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          }
                                      }
                                      // S'il s'agit d'une luxure et solde suffisant
                                      if((att_buy)&&(377<=event.button.x)&&(event.button.x<=473) && (397<=event.button.y) && (event.button.y<=437))
                                      {
                                          int a=theGame.thePlayers[1].currentLocation;
                                          if((a==38)&&(theGame.thePlayers[1].money>=75))
                                          {
                                              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clicbuy, 0,NULL);
                                            setMoney(75,1,&theGame.thePlayers[1]);
                                            SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj2.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          }
                                      }
                                      // S'il s'agit de la case départ
                                      if((att_buy)&&(315<=event.button.x)&&(event.button.x<=411) && (440<=event.button.y) && (event.button.y<=480))
                                      {
                                          int a=theGame.thePlayers[1].currentLocation;
                                          if(a==0)
                                          {
                                              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, simpleclick, 0,NULL);
                                              SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj2.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          }
                                      }
                                      // S'il s'agit du prison
                                      if(theGame.thePlayers[1].memo_prison==0)
                                      {
                                          if((att_buy)&&(377<=event.button.x)&&(event.button.x<=473) && (397<=event.button.y) && (event.button.y<=437))
                                      {
                                          int a=theGame.thePlayers[1].currentLocation;
                                          if(a==10)
                                          {
                                              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, simpleclick, 0,NULL);
                                              SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj2.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          }
                                      }
                                      }
                                      else
                                      {
                                          if((att_buy)&&(354<=event.button.x)&&(event.button.x<=493) && (382<=event.button.y) && (event.button.y<=439))
                                      {
                                          int a=theGame.thePlayers[1].currentLocation;
                                          if(a==10)
                                          {
                                              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clicbuy, 0,NULL);
                                              SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj2.png");
                                          setMoney(50,1,&theGame.thePlayers[1]);
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          theGame.thePlayers[1].memo_prison=0;
                                          }
                                      }
                                      }
                                      // S'il s'agit d'un free parking pot
                                      if((att_buy)&&(377<=event.button.x)&&(event.button.x<=473) && (397<=event.button.y) && (event.button.y<=437))
                                      {
                                          int a=theGame.thePlayers[1].currentLocation;
                                          if(a==20)
                                          {
                                              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clicbuy, 0,NULL);
                                              setMoney(250,0,&theGame.thePlayers[1]);
                                              SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj2.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          }
                                      }
                                      // S'il s'agit d'une income tax et solde suffisant et 200
                                      if((att_buy)&&(377<=event.button.x)&&(event.button.x<=473) && (397<=event.button.y) && (event.button.y<=437))
                                      {
                                          int a=theGame.thePlayers[1].currentLocation;
                                          if((a==4)&&(theGame.thePlayers[1].money>=200))
                                          {
                                              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clicbuy, 0,NULL);
                                            setMoney(200,1,&theGame.thePlayers[1]);
                                            SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("finishturnj2.png");
                                          att_buy=0;att_die=0;att_start=0;att_finish=1;
                                          }
                                      }
                                        /*
                                      // S'il veut acheter et n'a pas de solde donc mortage*****************
                                      if((att_buy)&&(320<=event.button.x)&&(event.button.x<=462) && (720<=event.button.y) && (event.button.y<=760)&&(theGame.thePlayers[1].money<tab[theGame.thePlayers[1].currentLocation].val_achat))
                                      {
                                          int continuermortage=1;
                                          imageDeFond=IMG_Load("boardcleanshadowj2.png");
                                          while(continuermortage)
                                          {
                                             SDL_WaitEvent(&event);
                                             switch(event.type)
                                             {
                                                    case SDL_QUIT:
                                                    continuermortage=0;continuerjeu=0;continuer=0;
                                                    imageDeFond = tab_j2_b[theGame.thePlayers[1].currentLocation];
                                                    break;
                                                    case SDL_KEYDOWN:
                                                    switch(event.key.keysym.sym)
                                                    {
                                                    case SDLK_ESCAPE:
                                                    continuermortage=0;
                                                    imageDeFond = tab_j2_b[theGame.thePlayers[1].currentLocation];
                                                    }
                                                    break;
                                                    case SDL_MOUSEBUTTONUP:
                                                    if (event.button.button == SDL_BUTTON_LEFT)
                                                    {
                                                        int i=0;
                                                        for(i=0;i<40;i++)
                                                        {
                                                            if((tab[i].xl<=event.button.x)&&(event.button.x<=tab[i].xr)&&(tab[i].yt<=event.button.y)&&(event.button.y<=tab[i].yd))
                                                            {
                                                                tab[i].etat=3;
                                                                setMoney(tab[i].val_achat/2,0,&theGame.thePlayers[1]);
                                                            }
                                                        }

                                                    }
                                                    break;
                                             }
                                             SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                        sprintf(soldep1,"$ %i",theGame.thePlayers[0].money);
                        sprintf(soldep2,"$ %i",theGame.thePlayers[1].money);
                        SDL_FreeSurface(soldej1);
                        SDL_FreeSurface(soldej2);
                        soldej1 = TTF_RenderText_Blended(police,soldep1,vertpassif);
                        soldej2 = TTF_RenderText_Blended(police,soldep2,vertactif);
                        SDL_BlitSurface(soldej1,NULL,ecran,&positionsoldej1_tj2);
                        SDL_BlitSurface(soldej2,NULL,ecran,&positionsoldej2_tj2);
                        int i=0;
                        for(i=0;i<40;i++)
                        {if((tab[i].etat==2)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_buyj1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_buyj2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_mortagej1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_mortagej2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==2))
                        {
                            SDL_BlitSurface(tab_illum[i],NULL,ecran,&positionFond);
                        }
                        }
                        SDL_BlitSurface(imagej1, NULL, ecran, &positionj1);
                        SDL_BlitSurface(imagej2, NULL, ecran, &positionj2);
                        SDL_Flip(ecran);
                                           }

                                         }*/

                                          // S'il clique mortage *********************
                                      if((theGame.thePlayers[1].nb_propriete>theGame.thePlayers[1].nb_propriete_mort)&&(320<=event.button.x)&&(event.button.x<=462) && (720<=event.button.y) && (event.button.y<=760)&&(!att_buy))
                                      {
                                          int continuermortage=1;
                                          SDL_FreeSurface(imageDeFond);
                                          FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, mort, 0,NULL);
                                          imageDeFond=IMG_Load("boardcleanshadowj2.png");
                                          while(continuermortage)
                                          {
                                             SDL_WaitEvent(&event);
                                             switch(event.type)
                                             {
                                                    case SDL_QUIT:
                                                    continuermortage=0;continuerjeu=0;continuer=0;
                                                    SDL_FreeSurface(imageDeFond);
                                                    imageDeFond = tab_j2_b[theGame.thePlayers[1].currentLocation];
                                                    break;
                                                    case SDL_KEYDOWN:
                                                    switch(event.key.keysym.sym)
                                                    {
                                                    case SDLK_ESCAPE:
                                                    continuermortage=0;
                                                    if(att_finish==1)
                                                    {

                                                        imageDeFond = IMG_Load("finishturnj2.png");
                                                    }
                                                    else
                                                    {
                                                        if(att_buy==1) {
                                                            imageDeFond = tab_j2_b[theGame.thePlayers[1].currentLocation];}
                                                        else
                                                        {
                                                        if(att_die==1){
                                                            imageDeFond=IMG_Load("rolldicej2.png");}
                                                        }
                                                    }
                                                    break;
                                                    }
                                                    break;
                                                    case SDL_MOUSEBUTTONUP:
                                                    if (event.button.button == SDL_BUTTON_LEFT)
                                                    {
                                                        int i=0;
                                                        for(i=0;i<40;i++)
                                                        {
                                                            if((tab[i].xl<=event.button.x)&&(event.button.x<=tab[i].xr)&&(tab[i].yt<=event.button.y)&&(event.button.y<=tab[i].yd)&&(tab[i].etat==2)&&(tab[i].appartenance==2))
                                                            {
                                                                 FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clickpropbuildoumort, 0,NULL);
                                                                tab[i].etat=3;
                                                                setMoney(tab[i].val_achat/2,0,&theGame.thePlayers[1]);
                                                                theGame.thePlayers[1].nb_propriete_mort+=1;
                                                            }
                                                        }

                                                    }
                                                    break;
                                             }
                                             SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                        sprintf(soldep1,"$ %i",theGame.thePlayers[0].money);
                        sprintf(soldep2,"$ %i",theGame.thePlayers[1].money);
                        SDL_FreeSurface(soldej1);
                        SDL_FreeSurface(soldej2);
                        soldej1 = TTF_RenderText_Blended(police,soldep1,vertpassif);
                        soldej2 = TTF_RenderText_Blended(police,soldep2,vertactif);
                        SDL_BlitSurface(soldej1,NULL,ecran,&positionsoldej1_tj2);
                        SDL_BlitSurface(soldej2,NULL,ecran,&positionsoldej2_tj2);
                        int i=0;
                        for(i=0;i<40;i++)
                        {if((tab[i].etat==2)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_buyj1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_buyj2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_mortagej1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_mortagej2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==2)&&(tab[i].nb_maisons==0))
                        {
                            SDL_BlitSurface(tab_illum[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==1)
                        {
                            SDL_BlitSurface(tab_1m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==2)
                        {
                            SDL_BlitSurface(tab_2m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==3)
                        {
                            SDL_BlitSurface(tab_3m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==4)
                        {
                            SDL_BlitSurface(tab_4m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==5)
                        {
                            SDL_BlitSurface(tab_5m[i],NULL,ecran,&positionFond);
                        }
                        }
                        SDL_BlitSurface(imagej1, NULL, ecran, &positionj1);
                        SDL_BlitSurface(imagej2, NULL, ecran, &positionj2);
                        SDL_Flip(ecran);
                                           }

                                         }

                                         // S'il clique unmortage *********************
                                      if((theGame.thePlayers[1].nb_propriete_mort>0)&&(469<=event.button.x)&&(event.button.x<=611) && (720<=event.button.y) && (event.button.y<=760)&&(!att_buy))
                                      {
                                          int continuerunmortage=1;
                                           FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, mort, 0,NULL);
                                          SDL_FreeSurface(imageDeFond);
                                          imageDeFond=IMG_Load("boardcleanshadowj2.png");
                                          while(continuerunmortage)
                                          {
                                             SDL_WaitEvent(&event);
                                             switch(event.type)
                                             {
                                                    case SDL_QUIT:
                                                    continuerunmortage=0;continuerjeu=0;continuer=0;
                                                    SDL_FreeSurface(imageDeFond);
                                                    imageDeFond = tab_j1_b[theGame.thePlayers[1].currentLocation];
                                                    break;
                                                    case SDL_KEYDOWN:
                                                    switch(event.key.keysym.sym)
                                                    {
                                                    case SDLK_ESCAPE:
                                                    continuerunmortage=0;
                                                    if(att_finish==1)
                                                    {

                                                        imageDeFond = IMG_Load("finishturnj2.png");
                                                    }
                                                    else
                                                    {
                                                        if(att_buy==1) {
                                                            imageDeFond = tab_j2_b[theGame.thePlayers[1].currentLocation];}
                                                        else
                                                        {
                                                        if(att_die==1){
                                                            imageDeFond=IMG_Load("rolldicej2.png");}
                                                        }
                                                    }
                                                    }
                                                    break;
                                                    case SDL_MOUSEBUTTONUP:
                                                    if (event.button.button == SDL_BUTTON_LEFT)
                                                    {
                                                        int i=0;
                                                        for(i=0;i<40;i++)
                                                        {
                                                            if((tab[i].xl<=event.button.x)&&(event.button.x<=tab[i].xr)&&(tab[i].yt<=event.button.y)&&(event.button.y<=tab[i].yd)&&(tab[i].etat==3)&&(tab[i].appartenance==2)&&(tab[i].val_achat<theGame.thePlayers[1].money))
                                                            {
                                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clickpropbuildoumort, 0,NULL);
                                                                tab[i].etat=2;
                                                                setMoney(tab[i].val_achat,1,&theGame.thePlayers[1]);
                                                                theGame.thePlayers[1].nb_propriete_mort-=1;
                                                            }
                                                        }

                                                    }
                                                    break;
                                             }
                                             SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                        sprintf(soldep1,"$ %i",theGame.thePlayers[0].money);
                        sprintf(soldep2,"$ %i",theGame.thePlayers[1].money);
                        SDL_FreeSurface(soldej1);
                        SDL_FreeSurface(soldej2);
                         soldej1 = TTF_RenderText_Blended(police,soldep1,vertpassif);
                        soldej2 = TTF_RenderText_Blended(police,soldep2,vertactif);
                        SDL_BlitSurface(soldej1,NULL,ecran,&positionsoldej1_tj2);
                        SDL_BlitSurface(soldej2,NULL,ecran,&positionsoldej2_tj2);
                        int i=0;
                        for(i=0;i<40;i++)
                        {if((tab[i].etat==2)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_buyj1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_buyj2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_mortagej1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_mortagej2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==2))
                        {
                            SDL_BlitSurface(tab_illum[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==1)
                        {
                            SDL_BlitSurface(tab_1m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==2)
                        {
                            SDL_BlitSurface(tab_2m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==3)
                        {
                            SDL_BlitSurface(tab_3m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==4)
                        {
                            SDL_BlitSurface(tab_4m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==5)
                        {
                            SDL_BlitSurface(tab_5m[i],NULL,ecran,&positionFond);
                        }
                        }
                        SDL_BlitSurface(imagej1, NULL, ecran, &positionj1);
                        SDL_BlitSurface(imagej2, NULL, ecran, &positionj2);
                        SDL_Flip(ecran);
                                           }

                                         }


                                         // S'il clique build *********************
                                      if((theGame.thePlayers[1].nb_propriete>0)&&(theGame.thePlayers[1].money>50)&&(113<=event.button.x)&&(event.button.x<=209) && (720<=event.button.y) && (event.button.y<=760)&&(!att_buy))
                                      {
                                          int continuerbuild=1;
                                          SDL_FreeSurface(imageDeFond);
                                           FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, mort, 0,NULL);
                                          imageDeFond=IMG_Load("boardcleanshadowj2.png");
                                          while(continuerbuild)
                                          {
                                             SDL_WaitEvent(&event);
                                             switch(event.type)
                                             {
                                                    case SDL_QUIT:
                                                    continuerbuild=0;continuerjeu=0;continuer=0;
                                                    SDL_FreeSurface(imageDeFond);
                                                    imageDeFond = tab_j2_b[theGame.thePlayers[1].currentLocation];
                                                    break;
                                                    case SDL_KEYDOWN:
                                                    switch(event.key.keysym.sym)
                                                    {
                                                    case SDLK_ESCAPE:
                                                    continuerbuild=0;
                                                    if(att_finish==1)
                                                    {

                                                        imageDeFond = IMG_Load("finishturnj2.png");
                                                    }
                                                    else
                                                    {
                                                        if(att_buy==1) {
                                                            imageDeFond = tab_j1_b[theGame.thePlayers[1].currentLocation];}
                                                        else
                                                        {
                                                        if(att_die==1){
                                                            imageDeFond=IMG_Load("rolldicej2.png");}
                                                        }
                                                    }
                                                    break;
                                                    }
                                                    break;
                                                    case SDL_MOUSEBUTTONUP:
                                                    if (event.button.button == SDL_BUTTON_LEFT)
                                                    {
                                                        int i=0;
                                                        for(i=0;i<40;i++)
                                                        {
                                                            if((tab[i].xl<=event.button.x)&&(event.button.x<=tab[i].xr)&&(tab[i].yt<=event.button.y)&&(event.button.y<=tab[i].yd)&&(tab[i].etat==2)&&(tab[i].appartenance==2)&&(i!=12)&&(i!=28)&&(i!=5)&&(i!=15)&&(i!=25)&&(i!=35)&&(tab[i].val_maison<theGame.thePlayers[1].money))
                                                            {
                                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clickpropbuildoumort, 0,NULL);
                                                                tab[i].nb_maisons+=1;
                                                                setMoney(tab[i].val_maison,1,&theGame.thePlayers[1]);
                                                                theGame.thePlayers[1].nb_maisons+=1;
                                                            }
                                                        }

                                                    }
                                                    break;
                                             }
                                             SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                        sprintf(soldep1,"$ %i",theGame.thePlayers[0].money);
                        sprintf(soldep2,"$ %i",theGame.thePlayers[1].money);
                        SDL_FreeSurface(soldej1);
                        SDL_FreeSurface(soldej2);
                         soldej1 = TTF_RenderText_Blended(police,soldep1,vertpassif);
                        soldej2 = TTF_RenderText_Blended(police,soldep2,vertactif);
                        SDL_BlitSurface(soldej1,NULL,ecran,&positionsoldej1_tj2);
                        SDL_BlitSurface(soldej2,NULL,ecran,&positionsoldej2_tj2);
                        int i=0;
                        for(i=0;i<40;i++)
                        {if((tab[i].etat==2)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_buyj1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_buyj2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_mortagej1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_mortagej2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==2)&&(tab[i].val_maison<=theGame.thePlayers[1].money)&&(tab[i].nb_maisons<5)&&(i!=5)&&(i!=15)&&(i!=25)&&(i!=35)&&(i!=12)&&(i!=28))
                        {
                            SDL_BlitSurface(tab_illum[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==1)
                        {
                            SDL_BlitSurface(tab_1m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==2)
                        {
                            SDL_BlitSurface(tab_2m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==3)
                        {
                            SDL_BlitSurface(tab_3m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==4)
                        {
                            SDL_BlitSurface(tab_4m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==5)
                        {
                            SDL_BlitSurface(tab_5m[i],NULL,ecran,&positionFond);
                        }
                        }
                        SDL_BlitSurface(imagej1, NULL, ecran, &positionj1);
                        SDL_BlitSurface(imagej2, NULL, ecran, &positionj2);
                        SDL_Flip(ecran);
                                           }

                                         }
                                          // S'il clique sell*********************
                                      if((theGame.thePlayers[1].nb_maisons>0)&&(217<=event.button.x)&&(event.button.x<=313) && (720<=event.button.y) && (event.button.y<=760)&&(!att_buy))
                                      {
                                          int continuersell=1;
                                          SDL_FreeSurface(imageDeFond);
                                           FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, mort, 0,NULL);
                                          imageDeFond=IMG_Load("boardcleanshadowj2.png");
                                          while(continuersell)
                                          {
                                             SDL_WaitEvent(&event);
                                             switch(event.type)
                                             {
                                                    case SDL_QUIT:
                                                    continuersell=0;continuerjeu=0;continuer=0;
                                                    SDL_FreeSurface(imageDeFond);
                                                    imageDeFond = tab_j2_b[theGame.thePlayers[1].currentLocation];
                                                    break;
                                                    case SDL_KEYDOWN:
                                                    switch(event.key.keysym.sym)
                                                    {
                                                    case SDLK_ESCAPE:
                                                    continuersell=0;
                                                    if(att_finish==1)
                                                    {

                                                        imageDeFond = IMG_Load("finishturnj2.png");
                                                    }
                                                    else
                                                    {
                                                        if(att_buy==1) {
                                                            imageDeFond = tab_j2_b[theGame.thePlayers[1].currentLocation];}
                                                        else
                                                        {
                                                        if(att_die==1){
                                                            imageDeFond=IMG_Load("rolldicej2.png");}
                                                        }
                                                    }
                                                    break;
                                                    }
                                                    break;
                                                    case SDL_MOUSEBUTTONUP:
                                                    if (event.button.button == SDL_BUTTON_LEFT)
                                                    {
                                                        int i=0;
                                                        for(i=0;i<40;i++)
                                                        {
                                                            if((tab[i].xl<=event.button.x)&&(event.button.x<=tab[i].xr)&&(tab[i].yt<=event.button.y)&&(event.button.y<=tab[i].yd)&&(tab[i].etat==2)&&(tab[i].nb_maisons>0)&&(tab[i].appartenance==2))
                                                            {
                                                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clickpropbuildoumort, 0,NULL);
                                                                tab[i].nb_maisons-=1;
                                                                setMoney(tab[i].val_maison/2,0,&theGame.thePlayers[1]);
                                                                theGame.thePlayers[1].nb_maisons-=1;
                                                            }
                                                        }

                                                    }
                                                    break;
                                             }
                                             SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                        sprintf(soldep1,"$ %i",theGame.thePlayers[0].money);
                        sprintf(soldep2,"$ %i",theGame.thePlayers[1].money);
                        SDL_FreeSurface(soldej1);
                        SDL_FreeSurface(soldej2);
                         soldej1 = TTF_RenderText_Blended(police,soldep1,vertpassif);
                        soldej2 = TTF_RenderText_Blended(police,soldep2,vertactif);
                        SDL_BlitSurface(soldej1,NULL,ecran,&positionsoldej1_tj2);
                        SDL_BlitSurface(soldej2,NULL,ecran,&positionsoldej2_tj2);
                        int i=0;
                        for(i=0;i<40;i++)
                        {if((tab[i].etat==2)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_buyj1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_buyj2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_mortagej1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_mortagej2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==2)&&(tab[i].nb_maisons>0))
                        {
                            SDL_BlitSurface(tab_illum[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==1)
                        {
                            SDL_BlitSurface(tab_1m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==2)
                        {
                            SDL_BlitSurface(tab_2m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==3)
                        {
                            SDL_BlitSurface(tab_3m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==4)
                        {
                            SDL_BlitSurface(tab_4m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==5)
                        {
                            SDL_BlitSurface(tab_5m[i],NULL,ecran,&positionFond);
                        }
                        }
                        SDL_BlitSurface(imagej1, NULL, ecran, &positionj1);
                        SDL_BlitSurface(imagej2, NULL, ecran, &positionj2);
                        SDL_Flip(ecran);
                                           }

                                         }


                                         // S'il clique finish turn
                                         if((att_finish)&&(326<=event.button.x)&&(event.button.x<=480) && (511<=event.button.y) && (event.button.y<=573)&&(!abandon))
                                         {
                                             theGame.currentPlayer=1;
                                             SDL_FreeSurface(imageDeFond);
                                             FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clickfinish, 0,NULL);
                                             imageDeFond = IMG_Load("rolldicej1.png");
                                             soldej1 = TTF_RenderText_Blended(police,soldep1,vertactif);
                                             soldej2 = TTF_RenderText_Blended(police,soldep2,vertpassif);
                                             att_die=1;att_buy=0;att_finish=0;abandon=0;
                                             lastlocationj1=theGame.thePlayers[0].currentLocation;
                                         }

                                      }
                                      if((att_finish)&&(326<=event.button.x)&&(event.button.x<=480) && (511<=event.button.y) && (event.button.y<=573)&&(theGame.currentPlayer==1)&&(!abandon))
                                         {
                                             theGame.currentPlayer=2;
                                             SDL_FreeSurface(imageDeFond);
                                             FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, clickfinish, 0,NULL);
                                             imageDeFond = IMG_Load("rolldicej2.png");
                                             soldej1 = TTF_RenderText_Blended(police,soldep1,vertpassif);
                                            soldej2 = TTF_RenderText_Blended(police,soldep2,vertactif);
                                             att_die=1;att_buy=0;att_finish=0;abandon=0;
                                             lastlocationj2=theGame.thePlayers[1].currentLocation;
                                         }
                                    }
                                    break;
                                    }
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                        SDL_BlitSurface(imaged1, NULL, ecran, &positiond1);
                        SDL_BlitSurface(imaged2, NULL, ecran, &positiond2);
                        SDL_BlitSurface(imagej1, NULL, ecran, &positionj1);
                        SDL_BlitSurface(imagej2, NULL, ecran, &positionj2);
                        SDL_BlitSurface(rent,NULL,ecran,&positionrent);
                         SDL_BlitSurface(boutonmortage,NULL,ecran,&positionFond);
                         SDL_BlitSurface(boutonunmortage,NULL,ecran,&positionFond);
                        SDL_BlitSurface(boutonbuild,NULL,ecran,&positionFond);
                        SDL_BlitSurface(boutonsell,NULL,ecran,&positionFond);
                        /*
                          if(theGame.currentPlayer==1)
                        {
                            if(theGame.thePlayers[0].nb_propriete<=theGame.thePlayers[0].nb_propriete_mort){boutonmortage=NULL;}
                             if(theGame.thePlayers[0].nb_propriete_mort<=0){boutonunmortage=NULL;}
                              if(theGame.thePlayers[0].nb_propriete>theGame.thePlayers[0].nb_propriete_mort){boutonmortage=IMG_Load("mortagepermis.png");}
                             if(theGame.thePlayers[0].nb_propriete_mort>0){boutonunmortage=IMG_Load("unmortagepermis.png");}
                             if((theGame.thePlayers[0].nb_propriete<=theGame.thePlayers[0].nb_propriete_mort)||(theGame.thePlayers[0].money<50)){boutonbuild=NULL;}
                             if(theGame.thePlayers[0].nb_maisons<=0){boutonsell=NULL;}
                              if((theGame.thePlayers[0].nb_propriete>theGame.thePlayers[0].nb_propriete_mort)&&(theGame.thePlayers[0].money>49)){boutonbuild=IMG_Load("buildpermis.png");}
                             if(theGame.thePlayers[0].nb_maisons>0){boutonsell=IMG_Load("sellpermis.png");}
                        }
                         if(theGame.currentPlayer==2)
                        {
                            if(theGame.thePlayers[1].nb_propriete<=theGame.thePlayers[1].nb_propriete_mort){boutonmortage=NULL;}
                            if(theGame.thePlayers[1].nb_propriete_mort<=0){boutonunmortage=NULL;}
                              if(theGame.thePlayers[1].nb_propriete>theGame.thePlayers[1].nb_propriete_mort){boutonmortage=IMG_Load("mortagepermis.png");}
                             if(theGame.thePlayers[1].nb_propriete_mort>0){boutonunmortage=IMG_Load("unmortagepermis.png");}
                             if((theGame.thePlayers[1].nb_propriete<=theGame.thePlayers[1].nb_propriete_mort)||(theGame.thePlayers[1].money<50)){boutonbuild=NULL;}
                             if(theGame.thePlayers[1].nb_maisons<=0){boutonsell=NULL;}
                              if((theGame.thePlayers[1].nb_propriete>theGame.thePlayers[1].nb_propriete_mort)&&(theGame.thePlayers[1].money>49)){boutonbuild=IMG_Load("buildpermis.png");}
                             if(theGame.thePlayers[1].nb_maisons>0){boutonsell=IMG_Load("sellpermis.png");}
                        }*/
                        sprintf(soldep1,"$ %i",theGame.thePlayers[0].money);
                        sprintf(soldep2,"$ %i",theGame.thePlayers[1].money);
                        SDL_FreeSurface(soldej1);
                        SDL_FreeSurface(soldej2);
                        if(theGame.currentPlayer==1)
                        {
                            soldej1 = TTF_RenderText_Blended(police,soldep1,vertactif);
                        soldej2 = TTF_RenderText_Blended(police,soldep2,vertpassif);
                        SDL_BlitSurface(soldej1,NULL,ecran,&positionsoldej1_tj1);
                        SDL_BlitSurface(soldej2,NULL,ecran,&positionsoldej2_tj1);
                        }
                        else
                        {
                           soldej1 = TTF_RenderText_Blended(police,soldep1,vertpassif);
                        soldej2 = TTF_RenderText_Blended(police,soldep2,vertactif);
                        SDL_BlitSurface(soldej1,NULL,ecran,&positionsoldej1_tj2);
                        SDL_BlitSurface(soldej2,NULL,ecran,&positionsoldej2_tj2);
                        }

                        int i=0;
                        for(i=0;i<40;i++)
                        {if((tab[i].etat==2)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_buyj1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==2)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_buyj2[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==1))
                        {
                          SDL_BlitSurface(tab_mortagej1[i],NULL,ecran,&positionFond);
                        }
                        if((tab[i].etat==3)&&(tab[i].appartenance==2))
                        {
                          SDL_BlitSurface(tab_mortagej2[i],NULL,ecran,&positionFond);
                        }
                         if(tab[i].nb_maisons==1)
                        {
                            SDL_BlitSurface(tab_1m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==2)
                        {
                            SDL_BlitSurface(tab_2m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==3)
                        {
                            SDL_BlitSurface(tab_3m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==4)
                        {
                            SDL_BlitSurface(tab_4m[i],NULL,ecran,&positionFond);
                        }
                        if(tab[i].nb_maisons==5)
                        {
                            SDL_BlitSurface(tab_5m[i],NULL,ecran,&positionFond);
                        }
                        }
                        SDL_Flip(ecran);
                        }
                    }

                    if((positionexit.x<=event.button.x)&&(event.button.x<=positionexit.x+155) && (positionexit.y<=event.button.y)&&(event.button.y<=positionexit.y+64))
                        {continuer = 0;}
                        break;
                }
            break;
        }
        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
        SDL_Flip(ecran);

    }


    // *** libération du son
    FMOD_Sound_Release(musique);
    FMOD_Sound_Release(player1start);
    FMOD_Sound_Release(clicrolletdepl);
    FMOD_Sound_Release(wouldubuy);
    FMOD_Sound_Release(clicbuy);
    FMOD_Sound_Release(clickfinish);
    FMOD_Sound_Release(chanceouchest);
    FMOD_Sound_Release(okchanceouchest);
    FMOD_Sound_Release(mort);
    FMOD_Sound_Release(clickpropbuildoumort);
    FMOD_Sound_Release(simpleclick);
FMOD_System_Close(system);
FMOD_System_Release(system);





SDL_FreeSurface(imageDeFond);
SDL_FreeSurface(soldej1);
SDL_FreeSurface(soldej2);
SDL_FreeSurface(rent);
SDL_FreeSurface(imaged1);
SDL_FreeSurface(imaged2);
SDL_FreeSurface(imagej1);
SDL_FreeSurface(imagej2);
SDL_FreeSurface(boutonmortage);
SDL_FreeSurface(boutonunmortage);
SDL_FreeSurface(boutonbuild);
SDL_FreeSurface(boutonsell);
TTF_Quit();
TTF_CloseFont(police);
SDL_Quit();

return EXIT_SUCCESS;
}



void rempboard(struct propriete** tab)
{

   (*tab)[0].type=10;
   (*tab)[0].xl=614;
   (*tab)[0].xr=705;
   (*tab)[0].yt=614;
   (*tab)[0].yd=707;
   (*tab)[1].type=1;
   (*tab)[1].nb_maisons=0;
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
   (*tab)[4].etat=1;
   (*tab)[4].val_achat=200;
   (*tab)[4].xl=390;
   (*tab)[4].xr=446;
   (*tab)[4].yt=614;
   (*tab)[4].yd=707;
   (*tab)[5].type=2;
   (*tab)[5].nb_maisons=0;
   (*tab)[5].etat=1;
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
   (*tab)[10].xl=18;
   (*tab)[10].xr=109;
   (*tab)[10].yt=614;
   (*tab)[10].yd=707;
   (*tab)[11].type=1;
   (*tab)[11].nb_maisons=0;
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
   (*tab)[12].etat=1;
   (*tab)[12].val_achat=150;
   (*tab)[12].nb_maisons=0;
   (*tab)[12].rent0=50;
   (*tab)[12].xl=18;
   (*tab)[12].xr=109;
   (*tab)[12].yt=501;
   (*tab)[12].yd=557;
   (*tab)[13].type=1;
   (*tab)[13].nb_maisons=0;
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
   (*tab)[15].etat=1;
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
   (*tab)[25].etat=1;
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
   (*tab)[28].etat=1;
   (*tab)[28].nb_maisons;
   (*tab)[28].rent0=50;
   (*tab)[28].val_achat=150;
   (*tab)[28].xl=501;
   (*tab)[28].xr=557;
   (*tab)[28].yt=17;
   (*tab)[28].yd=109;
   (*tab)[29].type=1;
   (*tab)[29].nb_maisons=0;
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
   (*tab)[35].etat=1;
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

void remp_buyj1(SDL_Surface*** tab)
{
   (*tab)[0]=NULL;
   (*tab)[1]=IMG_Load("mediterraneanavej1.png");
   (*tab)[2]=NULL;
   (*tab)[3]=IMG_Load("balticavej1.png");
   (*tab)[4]=NULL;
   (*tab)[5]=IMG_Load("readingrailroadj1.png");
   (*tab)[6]=IMG_Load("orientalavej1.png");
   (*tab)[7]=NULL;
   (*tab)[8]=IMG_Load("vermontavej1.png");
   (*tab)[9]=IMG_Load("connecticutavej1.png");
   (*tab)[10]=NULL;
   (*tab)[11]=IMG_Load("stcharlespalacej1.png");
   (*tab)[12]=IMG_Load("electriccompanyj1.png");
   (*tab)[13]=IMG_Load("statesavej1.png");
   (*tab)[14]=IMG_Load("virginiaavej1.png");
   (*tab)[15]=IMG_Load("pennsylvaniarailroadj1.png");
   (*tab)[16]=IMG_Load("stjamespalacej1.png");
   (*tab)[17]=NULL;
   (*tab)[18]=IMG_Load("tennesseeavej1.png");
   (*tab)[19]=IMG_Load("newyorkavej1.png");
   (*tab)[20]=NULL;
   (*tab)[21]=IMG_Load("kentuckyavej1.png");
   (*tab)[22]=NULL;
   (*tab)[23]=IMG_Load("indianaavej1.png");
   (*tab)[24]=IMG_Load("illinoisavej1.png");
   (*tab)[25]=IMG_Load("borailroadj1.png");
   (*tab)[26]=IMG_Load("atlanticavej1.png");
   (*tab)[27]=IMG_Load("ventnoravej1.png");
   (*tab)[28]=IMG_Load("waterworksj1.png");
   (*tab)[29]=IMG_Load("marvingardensj1.png");
   (*tab)[30]=NULL;
   (*tab)[31]=IMG_Load("pacificavej1.png");
   (*tab)[32]=IMG_Load("northcarolinaavej1.png");
   (*tab)[33]=NULL;
   (*tab)[34]=IMG_Load("pennsylvaniaavej1.png");
   (*tab)[35]=IMG_Load("shortlinerailroadj1.png");
   (*tab)[36]=NULL;
   (*tab)[37]=IMG_Load("parkplacej1.png");
   (*tab)[38]=NULL;
   (*tab)[39]=IMG_Load("boardwalkj1.png");
}

void remp_buyj2(SDL_Surface*** tab)
{
   (*tab)[0]=NULL;
   (*tab)[1]=IMG_Load("mediteranneanavej2.png");
   (*tab)[2]=NULL;
   (*tab)[3]=IMG_Load("balticavej2.png");
   (*tab)[4]=NULL;
   (*tab)[5]=IMG_Load("readingrailroadj2.png");
   (*tab)[6]=IMG_Load("orientalavenuej2.png");
   (*tab)[7]=NULL;
   (*tab)[8]=IMG_Load("vermontavej2.png");
   (*tab)[9]=IMG_Load("connecticutavej2.png");
   (*tab)[10]=NULL;
   (*tab)[11]=IMG_Load("stcharlespalacej2.png");
   (*tab)[12]=IMG_Load("electriccompanyj2.png");
   (*tab)[13]=IMG_Load("statesavej2.png");
   (*tab)[14]=IMG_Load("virginiavej2.png");
   (*tab)[15]=IMG_Load("pennsylvaniarailroadj2.png");
   (*tab)[16]=IMG_Load("stjamespalacej2.png");
   (*tab)[17]=NULL;
   (*tab)[18]=IMG_Load("tennesseavej2.png");
   (*tab)[19]=IMG_Load("newyorkavej2.png");
   (*tab)[20]=NULL;
   (*tab)[21]=IMG_Load("kentuckyavej2.png");
   (*tab)[22]=NULL;
   (*tab)[23]=IMG_Load("indianaavej2.png");
   (*tab)[24]=IMG_Load("illinoisavej2.png");
   (*tab)[25]=IMG_Load("borailroadj2.png");
   (*tab)[26]=IMG_Load("atlanticavej2.png");
   (*tab)[27]=IMG_Load("ventnoravej2.png");
   (*tab)[28]=IMG_Load("waterworksj2.png");
   (*tab)[29]=IMG_Load("marvingardensj2.png");
   (*tab)[30]=NULL;
   (*tab)[31]=IMG_Load("pacificavej2.png");
   (*tab)[32]=IMG_Load("nocarolinaavej2.png");
   (*tab)[33]=NULL;
   (*tab)[34]=IMG_Load("pennsylvaniaavej2.png");
   (*tab)[35]=IMG_Load("shortlinerailroadj2.png");
   (*tab)[36]=NULL;
   (*tab)[37]=IMG_Load("parkplacej2.png");
   (*tab)[38]=NULL;
   (*tab)[39]=IMG_Load("boardwalkj2.png");
}
void remp_mortj1(SDL_Surface*** tab)
{
   (*tab)[0]=NULL;
   (*tab)[1]=IMG_Load("mediterraneanavej1_m.png");
   (*tab)[2]=NULL;
   (*tab)[3]=IMG_Load("balticavej1_m.png");
   (*tab)[4]=NULL;
   (*tab)[5]=IMG_Load("readingrailroadj1_m.png");
   (*tab)[6]=IMG_Load("orientalavej1_m.png");
   (*tab)[7]=NULL;
   (*tab)[8]=IMG_Load("vermontavej1_m.png");
   (*tab)[9]=IMG_Load("connecticutavej1_m.png");
   (*tab)[10]=NULL;
   (*tab)[11]=IMG_Load("stcharlespalacej1_m.png");
   (*tab)[12]=IMG_Load("electriccompanyj1_m.png");
   (*tab)[13]=IMG_Load("statesavej1_m.png");
   (*tab)[14]=IMG_Load("virginiaavej1_m.png");
   (*tab)[15]=IMG_Load("pennsylvaniarailroadj1_m.png");
   (*tab)[16]=IMG_Load("stjamespalacej1_m.png");
   (*tab)[17]=NULL;
   (*tab)[18]=IMG_Load("tennesseeavej1_m.png");
   (*tab)[19]=IMG_Load("newyorkavej1_m.png");
   (*tab)[20]=NULL;
   (*tab)[21]=IMG_Load("kentuckyavej1_m.png");
   (*tab)[22]=NULL;
   (*tab)[23]=IMG_Load("indianaavej1_m.png");
   (*tab)[24]=IMG_Load("illinoisavej1_m.png");
   (*tab)[25]=IMG_Load("borailroadj1_m.png");
   (*tab)[26]=IMG_Load("atlanticavej1_m.png");
   (*tab)[27]=IMG_Load("ventnoravej1_m.png");
   (*tab)[28]=IMG_Load("waterworksj1_m.png");
   (*tab)[29]=IMG_Load("marvingardensj1_m.png");
   (*tab)[30]=NULL;
   (*tab)[31]=IMG_Load("pacificavej1_m.png");
   (*tab)[32]=IMG_Load("northcarolinaavej1_m.png");
   (*tab)[33]=NULL;
   (*tab)[34]=IMG_Load("pennsylvaniaavej1_m.png");
   (*tab)[35]=IMG_Load("shortlinerailroadj1_m.png");
   (*tab)[36]=NULL;
   (*tab)[37]=IMG_Load("parkplacej1_m.png");
   (*tab)[38]=NULL;
   (*tab)[39]=IMG_Load("boardwalkj1_m.png");
}
void remp_mortj2(SDL_Surface*** tab)
{
   (*tab)[0]=NULL;
   (*tab)[1]=IMG_Load("mediteranneanavej2_m.png");
   (*tab)[2]=NULL;
   (*tab)[3]=IMG_Load("balticavej2_m.png");
   (*tab)[4]=NULL;
   (*tab)[5]=IMG_Load("readingrailroadj2_m.png");
   (*tab)[6]=IMG_Load("orientalavenuej2_m.png");
   (*tab)[7]=NULL;
   (*tab)[8]=IMG_Load("vermontavej2_m.png");
   (*tab)[9]=IMG_Load("connecticutavej2_m.png");
   (*tab)[10]=NULL;
   (*tab)[11]=IMG_Load("stcharlespalacej2_m.png");
   (*tab)[12]=IMG_Load("electriccompanyj2_m.png");
   (*tab)[13]=IMG_Load("statesavej2_m.png");
   (*tab)[14]=IMG_Load("virginiavej2_m.png");
   (*tab)[15]=IMG_Load("pennsylvaniarailroadj2_m.png");
   (*tab)[16]=IMG_Load("stjamespalacej2_m.png");
   (*tab)[17]=NULL;
   (*tab)[18]=IMG_Load("tennesseavej2_m.png");
   (*tab)[19]=IMG_Load("newyorkavej2_m.png");
   (*tab)[20]=NULL;
   (*tab)[21]=IMG_Load("kentuckyavej2_m.png");
   (*tab)[22]=NULL;
   (*tab)[23]=IMG_Load("indianaavej2_m.png");
   (*tab)[24]=IMG_Load("illinoisavej2_m.png");
   (*tab)[25]=IMG_Load("borailroadj2_m.png");
   (*tab)[26]=IMG_Load("atlanticavej2_m.png");
   (*tab)[27]=IMG_Load("ventnoravej2_m.png");
   (*tab)[28]=IMG_Load("waterworksj2_m.png");
   (*tab)[29]=IMG_Load("marvingardensj2_m.png");
   (*tab)[30]=NULL;
   (*tab)[31]=IMG_Load("pacificavej2_m.png");
   (*tab)[32]=IMG_Load("nocarolinaavej2_m.png");
   (*tab)[33]=NULL;
   (*tab)[34]=IMG_Load("pennsylvaniaavej2_m.png");
   (*tab)[35]=IMG_Load("shortlinerailroadj2_m.png");
   (*tab)[36]=NULL;
   (*tab)[37]=IMG_Load("parkplacej2_m.png");
   (*tab)[38]=NULL;
   (*tab)[39]=IMG_Load("boardwalkj2_m.png");
}
void remp_illum(SDL_Surface*** tab)
{
   (*tab)[0]=NULL;
   (*tab)[1]=IMG_Load("mediteraneanave.png");
   (*tab)[2]=NULL;
   (*tab)[3]=IMG_Load("balticave.png");
   (*tab)[4]=NULL;
   (*tab)[5]=IMG_Load("readingrailroad.png");
   (*tab)[6]=IMG_Load("orientalave.png");
   (*tab)[7]=NULL;
   (*tab)[8]=IMG_Load("vermontave.png");
   (*tab)[9]=IMG_Load("connecticutave.png");
   (*tab)[10]=NULL;
   (*tab)[11]=IMG_Load("stcharlespalace.png");
   (*tab)[12]=IMG_Load("electriccompany.png");
   (*tab)[13]=IMG_Load("statesave.png");
   (*tab)[14]=IMG_Load("virginiaave.png");
   (*tab)[15]=IMG_Load("pennsylvaniarailroad.png");
   (*tab)[16]=IMG_Load("stjamesplace.png");
   (*tab)[17]=NULL;
   (*tab)[18]=IMG_Load("tennesseave.png");
   (*tab)[19]=IMG_Load("newyorkave.png");
   (*tab)[20]=NULL;
   (*tab)[21]=IMG_Load("kentuckyave.png");
   (*tab)[22]=NULL;
   (*tab)[23]=IMG_Load("indianaave.png");
   (*tab)[24]=IMG_Load("illinoisave.png");
   (*tab)[25]=IMG_Load("borailroad.png");
   (*tab)[26]=IMG_Load("atlanticave.png");
   (*tab)[27]=IMG_Load("ventnorave.png");
   (*tab)[28]=IMG_Load("waterworks.png");
   (*tab)[29]=IMG_Load("marvingardens.png");
   (*tab)[30]=NULL;
   (*tab)[31]=IMG_Load("pacificave.png");
   (*tab)[32]=IMG_Load("northcarolinaave.png");
   (*tab)[33]=NULL;
   (*tab)[34]=IMG_Load("pennsylvaniaave.png");
   (*tab)[35]=IMG_Load("shortline.png");
   (*tab)[36]=NULL;
   (*tab)[37]=IMG_Load("parkplace.png");
   (*tab)[38]=NULL;
   (*tab)[39]=IMG_Load("boardwalk.png");
}

void remp_j1_b(SDL_Surface*** tab)
{
   (*tab)[0]=NULL;
   (*tab)[1]=IMG_Load("mediterraneanavej1_b.png");
   (*tab)[2]=NULL;
   (*tab)[3]=IMG_Load("batlicavenuej1_b.png");
   (*tab)[4]=IMG_Load("incometaxj1_b.png");
   (*tab)[5]=IMG_Load("readingbuyj1_b.png");
   (*tab)[6]=IMG_Load("orientalavenuej1_b.png");
   (*tab)[7]=NULL;
   (*tab)[8]=IMG_Load("vermontavej1_b.png");
   (*tab)[9]=IMG_Load("connecticutavej1_b.png");
   (*tab)[10]=NULL;
   (*tab)[11]=IMG_Load("stcharlesplacej1_b.png");
   (*tab)[12]=IMG_Load("electriccompanyj1_b.png");
   (*tab)[13]=IMG_Load("statesavenuej1_b.png");
   (*tab)[14]=IMG_Load("virginiaavenuej1_b.png");
   (*tab)[15]=IMG_Load("pennsylvaniarailroadj1_b.png");
   (*tab)[16]=IMG_Load("stjamesplacej1_b.png");
   (*tab)[17]=NULL;
   (*tab)[18]=IMG_Load("tennesseeavej1_b.png");
   (*tab)[19]=IMG_Load("newyorkavej1_b.png");
   (*tab)[20]=NULL;
   (*tab)[21]=IMG_Load("kentuckyavej1_b.png");
   (*tab)[22]=NULL;
   (*tab)[23]=IMG_Load("indianaavenuej1_b.png");
   (*tab)[24]=IMG_Load("ollinoisavenuej1_b.png");
   (*tab)[25]=IMG_Load("railroadj1_b.png");
   (*tab)[26]=IMG_Load("atlanticavenuej1_b.png");
   (*tab)[27]=IMG_Load("ventoravej1_b.png");
   (*tab)[28]=IMG_Load("waterworksj1_b.png");
   (*tab)[29]=IMG_Load("marvingardensj1_b.png");
   (*tab)[30]=NULL;
   (*tab)[31]=IMG_Load("pacificavej1_b.png");
   (*tab)[32]=IMG_Load("nocarolinaavej1_b.png");
   (*tab)[33]=NULL;
   (*tab)[34]=IMG_Load("pennsylvaniarj1_b.png");
   (*tab)[35]=IMG_Load("shortlinej1_b.png");
   (*tab)[36]=NULL;
   (*tab)[37]=IMG_Load("parkplacej1_b.png");
   (*tab)[38]=NULL;
   (*tab)[39]=IMG_Load("boardwalkj1_b.png");
}
void remp_j2_b(SDL_Surface*** tab)
{
   (*tab)[0]=NULL;
   (*tab)[1]=IMG_Load("mediteranneanavej2_b.png");
   (*tab)[2]=NULL;
   (*tab)[3]=IMG_Load("balticavej2_b.png");
   (*tab)[4]=IMG_Load("incometaxj2_b.png");
   (*tab)[5]=IMG_Load("readingbuyj2_b.png");
   (*tab)[6]=IMG_Load("orientalavej2_b.png");
   (*tab)[7]=NULL;
   (*tab)[8]=IMG_Load("vermontavej2_b.png");
   (*tab)[9]=IMG_Load("connecticutavej2_b.png");
   (*tab)[10]=NULL;
   (*tab)[11]=IMG_Load("charlesplacej2_b.png");
   (*tab)[12]=IMG_Load("electriccmpanyj2_b.png");
   (*tab)[13]=IMG_Load("statesavenuej2_b.png");
   (*tab)[14]=IMG_Load("virginiaavej2_b.png");
   (*tab)[15]=IMG_Load("pennsylvaniabuyj2_b.png");
   (*tab)[16]=IMG_Load("stjamesplacej2_b.png");
   (*tab)[17]=NULL;
   (*tab)[18]=IMG_Load("tennesseavej2_b.png");
   (*tab)[19]=IMG_Load("newyorkavenuej2_b.png");
   (*tab)[20]=NULL;
   (*tab)[21]=IMG_Load("kentuckyavenuej2_b.png");
   (*tab)[22]=NULL;
   (*tab)[23]=IMG_Load("indianaavej2_b.png");
   (*tab)[24]=IMG_Load("illinoisavenuej2_b.png");
   (*tab)[25]=IMG_Load("borailroadbuyj2_b.png");
   (*tab)[26]=IMG_Load("atlanticavenuej2_b.png");
   (*tab)[27]=IMG_Load("ventnoravenuej2_b.png");
   (*tab)[28]=IMG_Load("waterworksj2_b.png");
   (*tab)[29]=IMG_Load("marvingardensj2_b.png");
   (*tab)[30]=NULL;
   (*tab)[31]=IMG_Load("pacificavej2_b.png");
   (*tab)[32]=IMG_Load("nocarolinaavej2_b.png");
   (*tab)[33]=NULL;
   (*tab)[34]=IMG_Load("pennsylvaniaavej2_b.png");
   (*tab)[35]=IMG_Load("shortlinebuyj2_b.png");
   (*tab)[36]=NULL;
   (*tab)[37]=IMG_Load("parkplacej2_b.png");
   (*tab)[38]=NULL;
   (*tab)[39]=IMG_Load("boardwalkj2_b.png");
}


void remp_1m(SDL_Surface*** tab)
{
   (*tab)[0]=NULL;
   (*tab)[1]=IMG_Load("mediteraneanave1m.png");
   (*tab)[2]=NULL;
   (*tab)[3]=IMG_Load("balticave1m.png");
   (*tab)[4]=NULL;
   (*tab)[5]=NULL;
   (*tab)[6]=IMG_Load("orientalave1m.png");
   (*tab)[7]=NULL;
   (*tab)[8]=IMG_Load("vermontave1m.png");
   (*tab)[9]=IMG_Load("connecticut1m.png");
   (*tab)[10]=NULL;
   (*tab)[11]=IMG_Load("stcharles1m.png");
   (*tab)[12]=NULL;
   (*tab)[13]=IMG_Load("statesave1m.png");
   (*tab)[14]=IMG_Load("virginiaave1m.png");
   (*tab)[15]=NULL;
   (*tab)[16]=IMG_Load("stjamesplace1m.png");
   (*tab)[17]=NULL;
   (*tab)[18]=IMG_Load("tenesseave1m.png");
   (*tab)[19]=IMG_Load("newyorkave1m.png");
   (*tab)[20]=NULL;
   (*tab)[21]=IMG_Load("kentuckyave1m.png");
   (*tab)[22]=NULL;
   (*tab)[23]=IMG_Load("indianaave1m.png");
   (*tab)[24]=IMG_Load("illinoisave1m.png");
   (*tab)[25]=NULL;
   (*tab)[26]=IMG_Load("atlanticave1m.png");
   (*tab)[27]=IMG_Load("ventnorave1m.png");
   (*tab)[28]=NULL;
   (*tab)[29]=IMG_Load("marvingardens1m.png");
   (*tab)[30]=NULL;
   (*tab)[31]=IMG_Load("pacificave1m.png");
   (*tab)[32]=IMG_Load("northcarolinaave1m.png");
   (*tab)[33]=NULL;
   (*tab)[34]=IMG_Load("pennsylvaniaave1m.png");
   (*tab)[35]=NULL;
   (*tab)[36]=NULL;
   (*tab)[37]=IMG_Load("parkplace1m.png");
   (*tab)[38]=NULL;
   (*tab)[39]=IMG_Load("boardwalk1m.png");
}

void remp_2m(SDL_Surface*** tab)
{
   (*tab)[0]=NULL;
   (*tab)[1]=IMG_Load("mediteraneanave2m.png");
   (*tab)[2]=NULL;
   (*tab)[3]=IMG_Load("balticave2m.png");
   (*tab)[4]=NULL;
   (*tab)[5]=NULL;
   (*tab)[6]=IMG_Load("orientalave2m.png");
   (*tab)[7]=NULL;
   (*tab)[8]=IMG_Load("vermontave2m.png");
   (*tab)[9]=IMG_Load("connecticutave2m.png");
   (*tab)[10]=NULL;
   (*tab)[11]=IMG_Load("stcharles2m.png");
   (*tab)[12]=NULL;
   (*tab)[13]=IMG_Load("statesave2m.png");
   (*tab)[14]=IMG_Load("virginiaave2m.png");
   (*tab)[15]=NULL;
   (*tab)[16]=IMG_Load("stjamesplace2m.png");
   (*tab)[17]=NULL;
   (*tab)[18]=IMG_Load("tenesseave2m.png");
   (*tab)[19]=IMG_Load("newyorkave2m.png");
   (*tab)[20]=NULL;
   (*tab)[21]=IMG_Load("kentuckyave2m.png");
   (*tab)[22]=NULL;
   (*tab)[23]=IMG_Load("indianaave2m.png");
   (*tab)[24]=IMG_Load("illinoisave2m.png");
   (*tab)[25]=NULL;
   (*tab)[26]=IMG_Load("atlanticave2m.png");
   (*tab)[27]=IMG_Load("ventnorave2m.png");
   (*tab)[28]=NULL;
   (*tab)[29]=IMG_Load("marvingardens2m.png");
   (*tab)[30]=NULL;
   (*tab)[31]=IMG_Load("pacificave2m.png");
   (*tab)[32]=IMG_Load("northcarolinaave2m.png");
   (*tab)[33]=NULL;
   (*tab)[34]=IMG_Load("pennsylvaniaave2m.png");
   (*tab)[35]=NULL;
   (*tab)[36]=NULL;
   (*tab)[37]=IMG_Load("parkplace2m.png");
   (*tab)[38]=NULL;
   (*tab)[39]=IMG_Load("boardwalk2m.png");
}

void remp_3m(SDL_Surface*** tab)
{
   (*tab)[0]=NULL;
   (*tab)[1]=IMG_Load("mediteraneanave3m.png");
   (*tab)[2]=NULL;
   (*tab)[3]=IMG_Load("balticave3m.png");
   (*tab)[4]=NULL;
   (*tab)[5]=NULL;
   (*tab)[6]=IMG_Load("orientalave3m.png");
   (*tab)[7]=NULL;
   (*tab)[8]=IMG_Load("vermontave3m.png");
   (*tab)[9]=IMG_Load("connecticutave3m.png");
   (*tab)[10]=NULL;
   (*tab)[11]=IMG_Load("stcharles3m.png");
   (*tab)[12]=NULL;
   (*tab)[13]=IMG_Load("statesave3m.png");
   (*tab)[14]=IMG_Load("virginiaave3m.png");
   (*tab)[15]=NULL;
   (*tab)[16]=IMG_Load("stjamesplace3m.png");
   (*tab)[17]=NULL;
   (*tab)[18]=IMG_Load("tenesseave3m.png");
   (*tab)[19]=IMG_Load("newyorkave3m.png");
   (*tab)[20]=NULL;
   (*tab)[21]=IMG_Load("kentuckyave3m.png");
   (*tab)[22]=NULL;
   (*tab)[23]=IMG_Load("indianaave3m.png");
   (*tab)[24]=IMG_Load("illinoisave3m.png");
   (*tab)[25]=NULL;
   (*tab)[26]=IMG_Load("atlanticave3m.png");
   (*tab)[27]=IMG_Load("ventnorave3m.png");
   (*tab)[28]=NULL;
   (*tab)[29]=IMG_Load("marvingardens3m.png");
   (*tab)[30]=NULL;
   (*tab)[31]=IMG_Load("pacificave3m.png");
   (*tab)[32]=IMG_Load("northcarolinaave3m.png");
   (*tab)[33]=NULL;
   (*tab)[34]=IMG_Load("pennsylvaniaave3m.png");
   (*tab)[35]=NULL;
   (*tab)[36]=NULL;
   (*tab)[37]=IMG_Load("parkplace3m.png");
   (*tab)[38]=NULL;
   (*tab)[39]=IMG_Load("boardwalk3m.png");
}

void remp_4m(SDL_Surface*** tab)
{
   (*tab)[0]=NULL;
   (*tab)[1]=IMG_Load("mediteraneanave4m.png");
   (*tab)[2]=NULL;
   (*tab)[3]=IMG_Load("balticave4m.png");
   (*tab)[4]=NULL;
   (*tab)[5]=NULL;
   (*tab)[6]=IMG_Load("orientalave4m.png");
   (*tab)[7]=NULL;
   (*tab)[8]=IMG_Load("vermontave4m.png");
   (*tab)[9]=IMG_Load("connecticutave4m.png");
   (*tab)[10]=NULL;
   (*tab)[11]=IMG_Load("stcharles4m.png");
   (*tab)[12]=NULL;
   (*tab)[13]=IMG_Load("statesave4m.png");
   (*tab)[14]=IMG_Load("virginiaave4m.png");
   (*tab)[15]=NULL;
   (*tab)[16]=IMG_Load("stjamesplace4m.png");
   (*tab)[17]=NULL;
   (*tab)[18]=IMG_Load("tenesseave4m.png");
   (*tab)[19]=IMG_Load("newyorkave4m.png");
   (*tab)[20]=NULL;
   (*tab)[21]=IMG_Load("kentuckyave4m.png");
   (*tab)[22]=NULL;
   (*tab)[23]=IMG_Load("indianaave4m.png");
   (*tab)[24]=IMG_Load("illinoisave4m.png");
   (*tab)[25]=NULL;
   (*tab)[26]=IMG_Load("atlanticave4m.png");
   (*tab)[27]=IMG_Load("ventnorave4m.png");
   (*tab)[28]=NULL;
   (*tab)[29]=IMG_Load("marvingardens4m.png");
   (*tab)[30]=NULL;
   (*tab)[31]=IMG_Load("pacificave4m.png");
   (*tab)[32]=IMG_Load("northcarolinaave4m.png");
   (*tab)[33]=NULL;
   (*tab)[34]=IMG_Load("pennsylvaniaave4m.png");
   (*tab)[35]=NULL;
   (*tab)[36]=NULL;
   (*tab)[37]=IMG_Load("parkplace4m.png");
   (*tab)[38]=NULL;
   (*tab)[39]=IMG_Load("boardwalk4m.png");
}

void remp_5m(SDL_Surface*** tab)
{
   (*tab)[0]=NULL;
   (*tab)[1]=IMG_Load("mediteranneanavehotel.png");
   (*tab)[2]=NULL;
   (*tab)[3]=IMG_Load("balticavehotel.png");
   (*tab)[4]=NULL;
   (*tab)[5]=NULL;
   (*tab)[6]=IMG_Load("orientalavehotel.png");
   (*tab)[7]=NULL;
   (*tab)[8]=IMG_Load("vermontavehotel.png");
   (*tab)[9]=IMG_Load("connecticutavehotel.png");
   (*tab)[10]=NULL;
   (*tab)[11]=IMG_Load("stcharleshotel.png");
   (*tab)[12]=NULL;
   (*tab)[13]=IMG_Load("statesavehotel.png");
   (*tab)[14]=IMG_Load("virginiaavehotel.png");
   (*tab)[15]=NULL;
   (*tab)[16]=IMG_Load("stjamesplacehotel.png");
   (*tab)[17]=NULL;
   (*tab)[18]=IMG_Load("tenesseavehotel.png");
   (*tab)[19]=IMG_Load("newyorkavehotel.png");
   (*tab)[20]=NULL;
   (*tab)[21]=IMG_Load("kentuckyavehotel.png");
   (*tab)[22]=NULL;
   (*tab)[23]=IMG_Load("indianaavehotel.png");
   (*tab)[24]=IMG_Load("illinoisavehotel.png");
   (*tab)[25]=NULL;
   (*tab)[26]=IMG_Load("atlanticavehotel.png");
   (*tab)[27]=IMG_Load("ventnoravehotel.png");
   (*tab)[28]=NULL;
   (*tab)[29]=IMG_Load("marvingardenshotel.png");
   (*tab)[30]=NULL;
   (*tab)[31]=IMG_Load("pacificavehotel.png");
   (*tab)[32]=IMG_Load("northcarolinaavehotel.png");
   (*tab)[33]=NULL;
   (*tab)[34]=IMG_Load("pennsylvaniaavehotel.png");
   (*tab)[35]=NULL;
   (*tab)[36]=NULL;
   (*tab)[37]=IMG_Load("parkplacehotel.png");
   (*tab)[38]=NULL;
   (*tab)[39]=IMG_Load("boardwalkhotel.png");
}

void initializePlayers(boardValues *currentGame)
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
     currentGame->thePlayers[i].railroadCounter = 0;
     currentGame->thePlayers[i].utilityCounter =0;
     currentGame->thePlayers[i].memo_prison = 0;
     currentGame->thePlayers[i].nb_propriete_mort = 0;
     currentGame->thePlayers[i].nb_maisons = 0;
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

void setPositionRoll(player *currentPlayer, int currentLocation, int dieRoll)
{
   if ((currentLocation + dieRoll) >= 40)
   {
        setPosition(currentPlayer, (currentLocation + dieRoll) - 40);
        currentPlayer->money += 200;

   }
   else
   {
      setPosition(currentPlayer, currentLocation + dieRoll);
   }

}

void setPosition(player *currentPlayer, int newLocation)
{
   currentPlayer->currentLocation = newLocation;
}

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
   }
}
