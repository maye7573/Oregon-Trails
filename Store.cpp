#include <iostream>
#include <iomanip>
#include <fstream>
#include "Store.h"
#include "TrailHelper.h"

const string STORE_MENU = 
"======Store Menu=====\n1. Oxen\n2. Food\n3. Bullets\n4. Miscellaneous Supplies\n5. Quit\n=====================\nWhich item would you like to buy? ";
const string MISC_MENU = 
"======Miscellaneous Supplies =====\n1. Wagon Wheels\n2. Wagon Axles\n3. Wagon Tongues\n4. Medical Kit\n5. Quit\n===================================\nWhich item would you like to buy? ";
const string INVALID_QTY = "Invalid quantity. Quantity cannot be negative!!\n";
const string OXEN_ERROR = "You must spend between $100 and $200 dollars. Currently you only spent $";
const string THANK_YOU = "Thanks for shopping with us!!\n";
const string INSUFF_FUNDS = "You do not have sufficient funds for this purchase! Please remove one or more items from the cart!\n";


//Prices must increase by 25% by store index in the menu 
Store::Store(int index) {
  storeIndex = index;
  oxPrice = 40 * (1 + index * .25);
  foodPrice = 0.5 * (1 + index * .25);
  bulletPrice = 2 * (1 + index * .25);
  medicalKitPrice = 25 * (1 + index * .25);
  wheelPrice = 20 * (1 + index * .25);
  axelPrice = 20 * (1 + index * .25);
  tonguePrice = 20 * (1 + index * .25);
}

//Update user supplies by adding the supplies in the cart
void Store::setSupplies(Inventory& supplies , Inventory& cart){
  supplies.setOxen(supplies.getNumOxen() + cart.getNumOxen());
  supplies.setFoodInLbs(supplies.getFoodInLbs() + cart.getFoodInLbs());
  supplies.setBullets(supplies.getNumBullets() + cart.getNumBullets());
  supplies.setMedicalKits(supplies.getNumMedicalKits() + cart.getNumMedicalKits());
  supplies.setWheels(supplies.getNumWheels()+cart.getNumWheels());
  supplies.setAxels(supplies.getNumAxels() + cart.getNumAxels());
  supplies.setTongues(supplies.getNumTongues()+ cart.getNumTongues());
}

void Store::displayStore(Inventory& supplies) {
  int option = 0;
  double total = 0;
  Inventory cart;
  cart.setCash(supplies.getCashAvailable());
  do { 
    cout << "Enter -ve qty to return items from the cart" << endl;
    
    option = showMenu(STORE_MENU, 1, 5);  
    switch(option) {      
      case 1: { //oxen
        if(storeIndex == 0){
          cout << "You must spend $100 to $200 on oxen.\n";
        }
        cout << "There are 2 oxen in a yoke and the price of each yoke is $" << fixed << setprecision(2) << oxPrice << ".\nHow many yokes do you wish to purchase? ";
        int tempOxen;
        cin >> tempOxen;
        if(cart.getNumOxen() + (tempOxen * 2) < 0){
          cout << INVALID_QTY;
        }
        else{
          int oxTotal = (cart.getNumOxen() + (tempOxen * 2)) * (oxPrice/2);    
          if(storeIndex == 0 && (oxTotal < 100 || oxTotal > 200)) {
            cout << OXEN_ERROR << fixed << setprecision(2) << oxTotal << endl;
          }
          else {
          cart.setOxen(cart.getNumOxen() + (tempOxen * 2));
          total = total + (tempOxen * oxPrice);
          }    
        }      
        break;
      }
      case 2: { //food
        if(storeIndex == 0){
          cout << "You should purchase at least 200 lbs. of food per person.\n";
        }

        cout << "Each pound costs $" << fixed << setprecision(3) <<  (foodPrice) << "  cents.\nHow many pounds of food do you wish to purchase? ";          
        int tempFood;
        cin >> tempFood;
        if(cart.getFoodInLbs() + tempFood < 0){
          cout << INVALID_QTY;
        }
        else{
          cart.setFoodInLbs(cart.getFoodInLbs() + tempFood); 
          double foodTotal = tempFood * foodPrice;
          total = total + foodTotal;
        }
        break;
      }
      case 3: { //bullets
        cout << "A box of 20 bullets costs $" << fixed << setprecision(2) << bulletPrice << "\nHow many boxes of bullets do you wish to purchase? ";
        int tempBullets;
        cin >> tempBullets;
        if(cart.getNumBullets() + tempBullets < 0){
          cout << INVALID_QTY;
        }
        else{
          cart.setBullets(cart.getNumBullets() + (tempBullets * 20));
          double bulletTotal = tempBullets * bulletPrice;
          total = total + bulletTotal;
        }
        break;
      }
      case 4: { //Miscellaneous Supplies
        int miscOption; 
        do {   
          miscOption = showMenu(MISC_MENU, 1, 5);
          if(miscOption == 1){ 
            cout << "Wagon wheel costs $" << fixed << setprecision(2) << wheelPrice << "\nHow many wheels do you wish to purchase? ";
            int tempWheels;
            cin >> tempWheels;
            if(cart.getNumWheels() + tempWheels < 0){
              cout << INVALID_QTY;
            }
            else{
              cart.setWheels(cart.getNumWheels() + tempWheels);
              double wheelTotal = tempWheels * wheelPrice;
              total = total + wheelTotal;
            }
          }
          else if(miscOption == 2){ 
            cout << "Wagon axle costs $" << fixed << setprecision(2) << axelPrice << "\nHow many axles do you wish to purchase? ";
            int tempAxles;
            cin >> tempAxles;
            if(cart.getNumAxels() + tempAxles < 0){
              cout << INVALID_QTY;
            }
            else{
              cart.setAxels(cart.getNumAxels() + tempAxles);
              double axleTotal = tempAxles * axelPrice;
              total = total + axleTotal;
            }
          }
          else if(miscOption == 3){ 
            cout << "Wagon tongue costs $" << fixed << setprecision(2) << tonguePrice << "\nHow many wheel tongues do you wish to purchase? ";
            int tempTongues;
            cin >> tempTongues;
            if(cart.getNumTongues() + tempTongues < 0){
              cout << INVALID_QTY;
            }
            else{
              cart.setTongues(cart.getNumTongues() + tempTongues);
              double tongueTotal = tempTongues * tonguePrice;
              total = total + tongueTotal;
            }
          }
          else if(miscOption == 4){ 
            cout << "Medical kit costs $" << fixed << setprecision(2) << medicalKitPrice <<  "\nHow many medical kits do you wish to purchase? ";
            int tempMedicalKits;
            cin >> tempMedicalKits;
            if(cart.getNumMedicalKits() + tempMedicalKits < 0){
              cout << INVALID_QTY;
            }
            else{
              cart.setMedicalKits(cart.getNumMedicalKits() + tempMedicalKits);             
              double medicalKitsTotal = tempMedicalKits * medicalKitPrice;
              total = total + medicalKitsTotal;
            }
          }

          if(cart.getCashAvailable() < total){
            cout << INSUFF_FUNDS;
            supplies.showStatus();
          }
          else{
            cart.showStatus();
            cout << "Your current bill is: $" << fixed<< setprecision(2) << total <<  endl;
          }
        }while(miscOption != 5);
        break;
      }
      default: { 
        if(storeIndex == 0 && (cart.getNumOxen() * (oxPrice/2) < 100 ||cart.getNumOxen() *    (oxPrice/2) > 200)){
          cout << OXEN_ERROR << cart.getNumOxen() * (oxPrice/2) << endl;
          option = 1; // forcing user to go back
        }
        
        break;
      }
    } //switch
    if(cart.getCashAvailable() < total){
      cout << INSUFF_FUNDS;
      cart.showStatus();
    }
    else if(option != 5){
      cart.showStatus(); 
      cout << "Your current bill is: $" << fixed << setprecision(2) << total <<  endl;
    }
    else if(option == 5){
      supplies.payCash(total);
      cart.showStatus();
      cout << left << setw(20) << "Your final bill is: $" << fixed<< setprecision(2) << total <<  endl;
      cout << THANK_YOU;
      cout << "Here's the current supplies after shopping" << endl;
      setSupplies(supplies, cart);
      supplies.showStatus();
    }
  } while(option != 5);
}
