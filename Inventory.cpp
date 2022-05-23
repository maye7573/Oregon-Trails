#include <iostream>
#include "Inventory.h"

const string SORRY_GAMEOVER = "\nGood game!In the end, the future refused to change!!!! We hope to see you again!\n";

Inventory::Inventory(): cash(1000), oxen(0), food(0), bullets(0), wheels(0), axels(0), tongues(0),medicalKits(0) {}

int Inventory::getNumOxen() {
    return oxen;
}

int Inventory::getFoodInLbs() {
    return food;
}

int Inventory::getNumBullets() {
    return bullets;
}

int Inventory::getNumMedicalKits() {
    return medicalKits;
}

int Inventory::getNumWheels() {
    return wheels;
}

int Inventory::getNumAxels() {
    return axels;
}

int Inventory::getNumTongues() {
    return tongues;
}

double Inventory::getCashAvailable() {
    return cash;
}

void Inventory::showStatus(){
  cout << "=======Your Supplies=======" << endl;
  cout << left << setw(16) << "Oxen: " << oxen <<endl;
  cout << left << setw(16) << "Food (lbs): " << food <<endl;
  cout << left << setw(16) << "Bullets: " << bullets <<endl;
  cout << left << setw(16) << "Wagon Wheels: " << wheels <<endl;
  cout << left << setw(16) << "Wagon Axles: " << axels <<endl;
  cout << left << setw(16) << "Wagon Tongues: " << tongues <<endl;
  cout << left << setw(16) << "Medical Kits: " << medicalKits <<endl;
  cout << left << setw(16) << "Cash available (in $): " << cash << endl;
  cout << "==========================" << endl;
}

bool Inventory::setOxen(int count) {
  //When no more oxen, game is over. Return False
  if(count <= 0){
    oxen = 0;
    return false;
  }
  else{
    oxen = count;
  }
  return true;    
}

bool Inventory::setFoodInLbs(int lbs) {
  //When Food is exhausted, game is over. Return False
  if(lbs <= 0){
    food = 0;
    cout << "Sorry! You cannot continue on the trail as you are out of food!!!\n" << SORRY_GAMEOVER;
    return false;
  }
  else {
    food = lbs;
  }
  return true;
}

void Inventory::setBullets(int count) {
  //bullets can't be negative
  if(count <= 0){
    bullets = 0;
  }
  else{
    bullets = count;
  }    
}

void Inventory::setMedicalKits(int count) {
    medicalKits = count;
}

void Inventory::setCash(double amount) {
    cash = amount;
}

bool Inventory::setWheels(int count) {
    if(count < 0){
      wheels = 0;
      return false;
    }
    wheels = count;
    return true;
}

bool Inventory::setAxels(int count) {
   if(count < 0){
      axels = 0;
      return false;
    }
    axels = count;
    return true;
}

bool Inventory::setTongues(int count) {
   if(count < 0){
      tongues = 0;
      return false;
    }
    tongues = count;
    return true;
}

bool Inventory::payCash(double amount) {
  //can't spend more than what you have, return false
  if(amount > cash){
    return false;
  }
  cash = cash - amount; 
  return true;
}

 
    

    


