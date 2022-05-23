#include <iostream>
#include <iomanip>
#include "Player.h"
#include "Fort.h"
#include "River.h"
#include "Inventory.h"

using namespace std;
#ifndef _TRAIL_H_
#define _TRAIL_H_

struct PlayerStats;

const int MAX_STOPS = 30;
class Trail {
  public:
    Trail();    
    //Accessors
    string getMilestoneName();
    bool isNextMilestoneRiver();
    bool isNextMilestoneFort();
    int getDistanceToNextMilestone();
    string getCurrentDate();
    void showStatusUpdate();
    void showGameEndMessage();
    int getTeamSize();
    River getRiver();
    Fort getFort();

    bool isAfterDeadline();
    bool brokenWagonOrNoParts();
    bool isLeaderDead();
    bool atDestination();
    //Mutators
    void setDate(int month, int day);
    bool advanceDays(int n);
    void advanceMiles(int n);

    bool addPlayer(string name, int index);

    int readRiverFile(string fileName);
    int readFortFile(string fileName);
    void shopAtStore();
    bool nextTurn();
    bool atRiver();
    bool atFort();
    bool rest(int days);
    bool crossRiver();    
    bool hunt();
    bool playPuzzle();
    bool raiderAttack();
    bool misfortune();
    bool gameOver();   
  private:    

    bool playerDeadWithDisease(int prob, int index, string playerName, string disease);
    string getDisease(int option);
    //data members    
    int    currentMonth;
    int    currentDay; 
    Player  players[5];//players team
    Fort    forts[MAX_STOPS];//all forts on the way
    River   rivers[MAX_STOPS];//All rivers to cross
    Inventory supplies; //current supplies
    int     nextFortIndex; //next fort to cross
    int     nextRiverIndex;//next river to cross
    int     numForts; //read from file
    int     numRivers; //read from file
    int     milesTravelled;   //from beginning of trip
};
#endif