
#include <iostream>
#include <iomanip>

using namespace std;

#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player {
  public:
    Player();
    Player(string name);

    //Accessors
    string getName();
    bool   isSick();
    bool   isDead();   

    //Mutators
    void setName(string nm);
    void setSick(bool sck);
    void setDead(bool dead);    
  
  private:    
    string  name;
    bool    sick;
    bool    dead;    
};
#endif