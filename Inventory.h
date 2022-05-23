#include <iostream>
#include <iomanip>

using namespace std;

#ifndef _INVENTORY_H_
#define _INVENTORY_H_

class Inventory {
  public:
    Inventory();
    
    //Accessors
    int getNumOxen();
    int getFoodInLbs();
    int getNumBullets();
    int getNumMedicalKits();
    int getNumWheels();
    int getNumAxels();
    int getNumTongues();
    double getCashAvailable();
    void showStatus();
    //Mutators
    bool setOxen(int count);
    bool setFoodInLbs(int lbs);
    void setBullets(int count);
    void setMedicalKits(int count);
    bool setWheels(int count);
    bool setAxels(int count);
    bool setTongues(int count);
    void setCash(double cash);
    bool payCash(double amount);

  private:    
    int oxen;
    int food;
    int bullets;
    int medicalKits;
    int wheels;
    int axels;
    int tongues;
    double cash;
}; 
    
#endif