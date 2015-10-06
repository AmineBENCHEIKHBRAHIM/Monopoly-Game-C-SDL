#ifndef MONOPOLY_H_INCLUDED
#define MONOPOLY_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>




void rempboard(struct propriete** tab);

void takeTurn(player *currentPlayer, boardValues *currentGame);

int firstDie(player *currentPlayer);
int secondDie(player *currentPlayer);
int getRoll(player *currentPlayer);

void setPosition(player *currentPlayer, int newLocation);
void setPositionRoll(player *currentPlayer, int currentLocation, int dieRoll);
//void showPosition(player *currentPlayer, boardValues *currentGame);
int determineSquare(player *currentPlayer, int currentPosition, int dieRoll);

void buyHouse(int property);
void buyHotel(int property);
void buyProperty(int property, int propertyValue, player *currentPlayer);
//void buyProperty(int property, int propertyValue, player *currentPlayer);

void setMoney(int valueToAdd, int operatorToUse, player *currentPlayer);

int continuePlaying(boardValues *currentGame);
int getMoney(player *currentPlayer);
int getNumHouses(int property);
int getNumHotels(int property);
int initializePlayers(boardValues *currentGame);
int getCurrentPlayer(boardValues *currentGame);
void removePlayerFromGame();

int verifCanBuild(boardValues *passBoard, propriete[] passTab);
int verifCanSell(boardValues *passBoard, propriete[] passTab);





#endif // MONOPOLY_H_INCLUDED
