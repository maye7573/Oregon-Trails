#include <iostream>
#include <iomanip>
#include "Inventory.h"
using namespace std;

#ifndef _Store_H_
#define _Store_H_

class Store {
  public:    
    Store(int index);
        
    //Mutators
    void displayStore(Inventory& supplies);
    
  private:   
    void setSupplies(Inventory& supplis, Inventory& cart);
    int storeIndex; 
    double oxPrice;
    double foodPrice;
    double bulletPrice;
    double medicalKitPrice;
    double wheelPrice;
    double axelPrice;
    double tonguePrice;
};

#endif