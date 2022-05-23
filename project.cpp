#include <iostream>
#include <fstream>
#include <iomanip>
#include "Trail.h"
#include "TrailHelper.h"

using namespace std;
const string INTRODUCTION = "THIS PROGRAM SIMULATES A TRIP OVER THE OREGON TRAIL FROM INDEPENDENCE, MISSOURI TO OREGON CITY, OREGON IN 1847. \nYOUR FAMILY OF FIVE WILL COVER THE 2040 MILE OREGON TRAIL IN 5-6 MONTHS, IF YOU MAKE IT ALIVE\n";
const string LEADER_PROMPT = "What is the first name of the wagon leader? ";
const string MEMBER_PROMPT = "What are the names of four other members in your party? ";
const string START_LOC_TEXT = "It is 1847. Your jumping off place for Oregon is Independence, Missouri.\n We suggest that you start on 03/28/1847.  Is that ok with you?  Enter Y(Yes)/N(No)? ";
const string START_MONTH = "That's fine!! You can choose a departure date between 03/01/1847 and 05/01/1847\nYou must decide which month to leave Independence.";
const string MONTH_MENU = "\n===== Start Month Menu ======\n 1. March\n 2. April \n 3. May\nWhat is your choice? ";
const string START_DAY_TEXT = "Great!! Which day would you like to leave on? Enter your choice: ";
const string MAIN_MENU = "========== THE OREGON TRAIL ==========\n 1. Continue on trail\n 2. Stop to rest\n 3. Hunt\n 4. Quit\nWhat is your choice(1-4) ? ";
const string RIVER_MENU = "========= RIVER MENU =========\nYou may: \n 1. Cross the River\n 2. Stop to rest \nWhat is your choice (1-2)? ";
const string FORT_MENU = "========= FORT MENU =========\nYou may: \n 1. Continue on trail \n 2. Stop to rest \n 3. Visit the store\nWhat is your choice (1-3)? ";

const string FIRST_STORE_TEXT = "Sorry!!No help text available!!\n";
const string END_DATE_TEXT = "You must reach reach Oregon City on or before November 30th, 1847. \n";

/*Start date logic goes here:
    Suggest default start date. 
    If chosen, set start date to 03/28/1847
    If not, provide choice of March,April,May. 
      a.If they select May, set start date as 05/01/1847.
      b.Ask them to select the day. Set start date to user
        picked month and day values
*/
void setStartDate(Trail& trail) {  
  cout << START_LOC_TEXT;
  string yesNo;
  cin >> yesNo;
  yesNo = lowercase(yesNo);
  if("y" == yesNo || "yes" == yesNo) {
    trail.setDate(3, 28);
  }
  else {    
    cout << START_MONTH;
    int option = showMenu(MONTH_MENU, 1, 3);
    int month = option + 2;
    
    if(month != 5) {//Not May
      int day = 0;
      int maxDays = (month == 3) ? 31 : 30;
      while(day < 1 || day > maxDays) {
        cout << START_DAY_TEXT;
        cin >> day;
      }
      trail.setDate(month,day);
    }
    else {
      trail.setDate(month, 1);
    }    
  }   
  cout << "Your start date is " << trail.getCurrentDate()<< endl << END_DATE_TEXT;
  return;
}

/* Handle visit to the first store at the start*/
void visitStoreAtStart(Trail& trail) {
  //display visit store text from file
  ifstream storeFile;
  storeFile.open("store.txt");

  if(!storeFile) {
    cout << FIRST_STORE_TEXT;
  }
  else{
    string line;
    while(getline(storeFile,line)) {
        cout << line << endl;
    }
    storeFile.close();
  }
  trail.shopAtStore();
}

/* Add players to Trail object
*/
void addPlayers(Trail& trail) {
  string name;
  const int PARTY_SIZE = 5;

  cout << INTRODUCTION;  
  cout << LEADER_PROMPT;
  for(int index = 1;index <= PARTY_SIZE; index++) {
    cin >> name;
    trail.addPlayer(name, index - 1);  
    name = "";
    if(index == 1) {
      cout << MEMBER_PROMPT;
    }
  }
}

int main() {
  // Initialize random number generator 
  srand(time(0)); 
  Trail trail;  
  addPlayers(trail);  
  setStartDate(trail);
  visitStoreAtStart(trail);  
  trail.readRiverFile("rivers.txt");
  trail.readFortFile("forts.txt");
  bool endGame = false; 

  //repeat while game is not over
  while(false == trail.gameOver() && false == endGame){
    trail.showStatusUpdate(); 
    
    int choice = showMenu(MAIN_MENU,1,4);
    switch(choice){
      case 1:{ //1. Continue on trail
        
        if(true == trail.nextTurn()){ //gameover
          endGame = true;
          break;
        }
        if(true == trail.atDestination()){//at dest
          cout << CONGRATS << endl;
          endGame = true;
          break;
        }
        else if(true == trail.atRiver()){ //at river
          cout << "You have reached " << trail.getMilestoneName() << endl;
          trail.showStatusUpdate(); 
          int option;
          do{
            option = showMenu(RIVER_MENU,1,2);
            if(option == 2){//rest
              if(true == trail.advanceDays(1)){
                endGame = true;
                break;
              }
            }
            else if(true == trail.crossRiver()){ //cross
              endGame = true;
              break;
            }
          }while(option == 2 && endGame == false);
        }
        else if(true == trail.atFort()){//fort
          cout << "You have reached " << trail.getMilestoneName() << endl;
          trail.showStatusUpdate(); 
          int option;
          do{
            option = showMenu(FORT_MENU,1,3);
            if(option == 2){//rest
              if(true == trail.advanceDays(1)){
                endGame = true;
                break;
              }
            }
            else if(option == 1){ //Continue
              break;
            }
            else{ //visit store
              trail.shopAtStore();
            }
          }while(option != 1 && endGame == false);
        }       
        if(true == trail.raiderAttack()){ //gameover
          endGame = true;
          break;
        }
        break;
      }
      case 2:{ // 2. Stop to rest
        string restMenu = "You can rest between 1 and 3 days.\n How many days would you like to rest? Enter 1-3 \n";
        int daysToRest = showMenu(restMenu,1,3);
        if(true == trail.advanceDays(daysToRest)){ //gameover
          endGame = true;
          break;
        }
        break;
      }
      case 3:{//3. Hunt
        if(true == trail.hunt()){ //gameover
          endGame = true;
          break;
        }
        break;
      }
      default:{//4. Quit
        cout << "We are sorry to see you and your team cut your trip short!! Please come back again!!!" << endl;
        endGame = true; 
        break;
      }
    }//switch end    
    if(false == endGame){ //run misfortune 
      if (true == trail.misfortune()){
        endGame = true;           
      }
    } 
    else{//game end?
      trail.showStatusUpdate();
      trail.showGameEndMessage();
      break;
    }      
  }//end of while 
} // end of main
