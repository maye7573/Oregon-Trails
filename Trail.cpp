#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <math.h>
#include "Trail.h"
#include "Store.h"
#include "Player.h"
#include "TrailHelper.h"

using namespace std;

int daysInMonth[] = {00,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 
const int TOTAL_DISTANCE = 2040;
const string CURRENT_YEAR = "1847";

const string DISEASE_MENU = "1. Continue on trail\n2. Stop to rest\n  What is your choice (1-2)?";
const string RAIDER_MENU = "========= RAIDER MENU =========\nYou may: \n 1. Run\n 2. Attack\n 3. Surrender\nWhat is your choice (1-3)? ";
const string SORRY_GAMEOVER = "\nGood game!Life is hard, you'll never win, and you're going to die a horrible death if you do anything involving a Conestoga wagon!!\nCome back and play again!\n";


Trail::Trail()
:nextFortIndex(-1)
,nextRiverIndex(-1)
,numForts(0)
,numRivers(0)
,milesTravelled(0) {}

string Trail::getMilestoneName(){
  if(true == atFort()){
    return forts[nextFortIndex].getName();
  }
  else{
    return rivers[nextRiverIndex].getName();
  }
}

bool Trail::atRiver() {
  return (milesTravelled == rivers[nextRiverIndex].getLength());
}

bool Trail::atFort() {
  return (milesTravelled == forts[nextFortIndex].getDistance());
}

River Trail::getRiver(){
  if(nextRiverIndex != -1 && nextRiverIndex < numRivers){
    return rivers[nextRiverIndex];
  }
  return River();
}

Fort Trail::getFort(){
  if(nextFortIndex != -1 && nextFortIndex < numForts){
    return forts[nextFortIndex];
  }
  return Fort();
}

bool Trail::isNextMilestoneRiver() {
  if(nextFortIndex+1 < numForts && nextRiverIndex+1 < numRivers){
    if(forts[nextFortIndex+1].getDistance() <          rivers[nextRiverIndex+1].getLength()){
      return false;
    }
    else{
      return true;
    }
  }
  else if(nextFortIndex+1 < numForts) {
    return false;
  }
  else if(nextRiverIndex+1 < numRivers){
    return true;
  }
} 

bool Trail::isNextMilestoneFort() {
  if(nextFortIndex+1 < numForts && nextRiverIndex+1 < numRivers){
    if(forts[nextFortIndex+1].getDistance() <          rivers[nextRiverIndex+1].getLength()){
      return true;
    }
    else{
      return false;
    }
  }
  else if(nextFortIndex+1 < numForts) {
    return true;
  }
  else if(nextRiverIndex+1 < numRivers){
    return true;
  }
} 

int Trail::getDistanceToNextMilestone() {
    if(isNextMilestoneFort()){
      return forts[nextFortIndex+1].getDistance();
    }
    return rivers[nextRiverIndex+1].getLength();
}

string Trail::getCurrentDate(){
  ostringstream ss;
  ss << std::setw(2) << std::setfill('0') << currentDay;
  string day = ss.str();  
  ss.str("");
  ss.flush();
  ss << std::setw(2) << std::setfill('0') << currentMonth;
  string month = ss.str();
  return month + "-" + day + "-" + CURRENT_YEAR;
}

void Trail::showStatusUpdate(){
  cout << setw(30) << "Current Date: " << getCurrentDate() << endl;
  cout << setw(30) << "Miles Travelled: " << milesTravelled << endl;
  cout << setw(30) << "Miles till next milestone: " << getDistanceToNextMilestone() - milesTravelled << endl;
  supplies.showStatus(); 
}

bool Trail::isAfterDeadline() {
  const int NOVEMBER = 11;
  const int MARCH = 3;
  if(currentMonth < MARCH or currentMonth > NOVEMBER){
    return true;
  }
  else{
    return false;
  }
}

bool Trail::brokenWagonOrNoParts(){
  return ((supplies.getNumAxels() == 0) || (supplies.getNumWheels() == 0) || (supplies.getNumTongues() == 0));
}

bool Trail::isLeaderDead(){
  return players[0].isDead();
}

bool Trail::atDestination(){
  if(TOTAL_DISTANCE == milesTravelled){
    cout << CONGRATS << endl;
    return true;
  }
  return false;
}

void Trail::setDate(int month, int day){
  currentMonth = month;
  currentDay = day;
}

void Trail::shopAtStore(){
  Store store(nextFortIndex+1);
  store.displayStore(supplies); 
}

bool Trail::addPlayer(string name, int index){
  if(index >= 5){
    return false;
  }
  else{ 
    players[index] = Player(name);
    return true;
  }
}

/*If new day is past number of days in curr month
advance month and current day to appropriate values*/
bool Trail::advanceDays(int days) {
  for(int i = 0; i < days; i++){
    int food = supplies.getFoodInLbs();  
    //reduce 3lbs per person for the days
    int remaining = food - (3 * getTeamSize());
    if(false == supplies.setFoodInLbs(remaining)) 
    {
      return true;
    }
    int day = currentDay + 1; 
    int maxDays = daysInMonth[currentMonth];
    int month = (day > maxDays) ? currentMonth + 1 : currentMonth;
    day = (day > maxDays) ? day - maxDays : day; 
    setDate(month, day);

    if(true == isAfterDeadline()){//after deadline
      cout << "You were unable to reach Oregon City before Winter!!" << SORRY_GAMEOVER;
      return true;
    }
  } 
  return false;
}  

void Trail::advanceMiles(int miles) {
  milesTravelled += miles;
}  

int Trail::getTeamSize() {
  int size=0;
  for(int i = 0;i < 5;i++) {
    if(false == players[i].isDead()) {
      size +=1;
    }    
  }
  return size;
}

bool Trail::nextTurn() {
  int n = getRand(71, 70);
  if(n > 140){
    n = 140;
  }
  int distance = getDistanceToNextMilestone();
  //if we travelled past next milestone, change miles
  //travelled to next milestone
  if(false == atDestination()) {
    if (milesTravelled + n >= distance) {
      milesTravelled = distance;
      if(true == isNextMilestoneRiver()){
        nextRiverIndex++;
      }
      else {
        nextFortIndex++;
      }
    }
    else {
      advanceMiles(n);
    }     
  }
  else{
    cout << CONGRATS << endl;
    advanceDays(14);
    return true;
  }

  if(true == advanceDays(14)){
  return true;
  }
  return false;                   
} 

bool Trail::rest(int days) {
   if(true == advanceDays(days)){
    return true;
  } 
  return false;
}

int Trail::readRiverFile(string fileName) {
  ifstream inFile;
  inFile.open(fileName);
    
  if(!inFile){ //file open failed
    return -1;
  }
  string line; 
  string tempArr[MAX_STOPS];
  int riverLine = 0;
  numRivers = 0;
  while(getline(inFile,line)){//more lines to read
    if(numRivers == MAX_STOPS){//hit max array size, stop!
      break;
    }
    if(riverLine == 0 ){//first line for a river
      rivers[numRivers].setName(line);
      riverLine = 1;
    }
    else { //second line  
      string tempArr[2];
      int fields = splitLine(line,' ',tempArr,2);
      string distance = tempArr[0].substr(0, tempArr[0].length()-2);
      string depth = tempArr[1].substr(0, tempArr[1].length()-2);
      rivers[numRivers].setLength(stoi(distance));
      rivers[numRivers].setDepth(stoi(depth));

      riverLine = 0;
      numRivers++; 
    }
  }
  inFile.close(); 
  return numRivers;
}

int Trail::readFortFile(string fileName) {
    ifstream inFile;
    inFile.open(fileName);
    
    if(!inFile){ //file open failed
      return -1;
    }
    string line; 
    string tempArr[MAX_STOPS];
    int fortLine = 0;
    while (getline(inFile,line)) {//more lines to read

      if(numForts == MAX_STOPS){//hit max size, stop!
        break;
      }
      if(fortLine == 0 ){//first line for a fort
        forts[numForts].setName(line);        
        fortLine = 1;
      }
      else {//second line
        string distance = line.substr(0, line.length()-2);
        forts[numForts].setDistance(stoi(distance));
        fortLine = 0;
        numForts++; 
      }
    }
    inFile.close(); 
    return numForts;
}

bool Trail::crossRiver() {
  const double FERRYCOST = 10;
  double currentCash = supplies.getCashAvailable();
  if(getRiver().getDepth() > 3){//depth > 3
    cout << "You have use a ferry to cross the river. It costs $10 per person!" << endl;
    int howMany = currentCash / FERRYCOST; 
  
  if(supplies.getCashAvailable() < FERRYCOST){//not     enough $$
      cout << "Not enough money to pay for the ferry!!" << "You only have: $" << fixed << setprecision(2) << currentCash <<SORRY_GAMEOVER;
      return true; 
    }
    else if(howMany < getTeamSize()){
      for(int i = getTeamSize(); i <= howMany; i--){
        players[i].setDead(true); 
      }
      supplies.payCash(howMany * FERRYCOST);
      cout << howMany - 1 << " teammates and you crossed the river successfully, you had to leave the rest behind due to shortage of funds!" << endl;
    }
    else{
      supplies.payCash(getTeamSize() * FERRYCOST);
      cout << "You and your team crossed the river successfully!!\n";
    }
    return false;
  }
  cout << "You and your team crossed the river successfully!!\n";
  return false;
}

bool Trail::hunt() {
  if(true == advanceDays(1)){
    return true;
  } 
  int chance = getRand(100,1);
  string animal;
  int food;
  int bullets;
  if(chance <= 5){// moose
    animal = "Moose";
    food = getRand(300, 1) + 300;
    bullets = 12;
  }
  else if(chance <= 7){//bear
    animal = "Bear";
    food = getRand(250, 1) + 100;
    bullets = 10;
  }
  else if(chance <= 15){//deer
    animal = "Deer";
    food = getRand(25, 1) + 30;
    bullets = 5;
  }
  else if(chance <= 25){//fox
    animal = "Fox";      
    food = 5;
    bullets = 8;
  }
  else if(chance <= 50){//rabbit
    animal = "Rabbit";
    food = 2;
    bullets = 10;
  }
  else if(chance <= 80){//all five
    animal = "Moose, Bear, Deer, Fox, and Rabbit!";
    food = 1000;
    bullets = 45; 
  }
  else{// no game found(greater then 80)
    cout << "Sorry!! You were unable to find any game!" << endl;
  }
  bool puzzleSolved = false;
  if(animal.length()!= 0){//found game
    string huntMenu = "You got lucky!! You encountered " + animal + "!\n Do you want to hunt? \n 1. Yes 2. No\nEnter choice (1-2) ";
    int choice = showMenu(huntMenu, 1, 2);
    if(choice == 1){ // chose to hunt
      if(supplies.getNumBullets() < 10){ //no ammo
        cout << "Hunt was unsuccessful!!" << endl;
      }
      else{ //ammo present
        puzzleSolved = playPuzzle();
        if(false == puzzleSolved){ // puzzle faild
          cout << "Hunt was unsuccessful!!" << endl;
        }
        else{ // solved puzzle
          supplies.setBullets(supplies.getNumBullets() - bullets);
        }
      }
    }
  }
  //how much to eat per person
  string eatMenu = "How well do you want to eat tonight?\n 1. Poorly (2lbs per person)\n 2. Moderately (3lbs per person)\n 3. Well (5lbs per person)\nEnter your choice (1-3)";
  int choice = showMenu(eatMenu, 1, 3);
  int foodAvailable = supplies.getFoodInLbs();
  //we accounted for the 3lb each in advanceDays()
  if(choice == 1){//poorly eat
    int deplete = 1 * getTeamSize();
    supplies.setFoodInLbs(foodAvailable + deplete);
  }
  else if(choice == 3){//eat well
    int deplete = 2 * getTeamSize();
    if(false == supplies.setFoodInLbs(foodAvailable - deplete)){
      return true;
    }
  }
  if(true == puzzleSolved){//puzzle solved
    int foodAvailable = supplies.getFoodInLbs();
    if(foodAvailable + food > 1000){ // > 1000
      supplies.setFoodInLbs(1000); 
      cout << "From the animals you shot you got " << food << "lbs. However you can ONLY carry 1000 lbs!! Leaving rest of the food behind!!!" << endl;
    }
    else{ // <= 1000
      supplies.setFoodInLbs(foodAvailable +food);
      cout << "From the animals you shot you got " << food << "lbs. You now have " << foodAvailable + food << "lbs" << endl;
    }
  }
  return false;
}

bool Trail::playPuzzle(){
  int number = getRand(10,1); 
  cout << "the number is: " << number << endl;  
  cout << "You have three tries to guess the correct number (1-10) " << endl;
  
  int guess; 
  for(int tries = 1; tries <= 3; tries++){
    cin >> guess;
    if(guess == number){//guessed correctly
      cout << "You have correctly solved the puzzle!!" << endl;
      return true;
    }
    else if (tries < 3){//tried < 3 times so far
      cout << "Incorrect guess! Try again!!\n";
    }
    else{ //exhausted all tries
      cout << "Incorrect guess!! Sorry, You exhausted all three tries!!Correct Value was: " << number << endl;
    }
  }
  return false;
}


bool Trail::raiderAttack() {
  int M = milesTravelled;
  double raider = (pow((M/100) -4 ,2));
  double prob = (raider + 72) / (raider +12) - 1;
  prob = prob / 10; 

  if(prob > 0.1){//probability over 10%
    cout << "RIDERS AHEAD! THEY LOOK HOSTILE!" << endl;
    
    int option = showMenu(RAIDER_MENU, 1, 3);
    switch(option){
      case 1: { //run
        if(false == supplies.setOxen(supplies.getNumOxen()-1)){//all ox dead                  
          return true;
        }
        if(false == supplies.setFoodInLbs(supplies.getFoodInLbs()-10)){ //food 0, game over
          return true;
        }
        int rand = getRand(3,1);
        string part;
        bool partZero = false;
        if(rand == 1){ // wheel
          part = "wheel";
          if(false == supplies.setWheels(supplies.getNumWheels()-1)){
            partZero = true;
          }
        }
        else if(rand == 2){ //axle
           part = "axle";
          if(false == supplies.setAxels(supplies.getNumAxels()-1)){
            partZero = true; 
          }

        }
        else{ //tongue
           part = "tongue";
          if(false == supplies.setTongues(supplies.getNumTongues()-1)){
            partZero = true;
          }
        }     
        cout << "You left behind a ox, 10lbs of food";
        if(partZero == false){
          cout << ", and " << part << " when you ran away!\n";
        }

        else{ 
          cout << " when you ran away!\n";
        }
        break;
      }
      case 2: { //attack
        if(true == playPuzzle()){//won battle
          supplies.setFoodInLbs(supplies.getFoodInLbs()+ 50);
          supplies.setBullets(supplies.getNumBullets()+ 50);
          cout << "Congrats!! You won the battle, gained 50lbs of food and 50 bullets!!!" << endl;
        }
        else{//lost battle
          supplies.setBullets(supplies.getNumBullets() - 50);
          double cash = supplies.getCashAvailable();
          cash = cash * (.25);
          supplies.payCash(cash);
          cout << "Sorry, you lost the battle! You lost 50 bullets and a quarter of your cash reserves!!\n";
        }
        break;
      }
      default: { //surrender
        double cash = supplies.getCashAvailable();
        cash = cash * (.25);
        supplies.payCash(cash);
         cout << "Sorry, the riders took a quarter of your cash reserves" <<endl;
        break;
      }
    }//switch end

  }//prob > 10%'
  return false;
}

string Trail::getDisease(int option) {
  string diseaseName;
  switch(option){
    case 1: {
      diseaseName = "TYPHOID";
      break;
    }
    case 2: {
      diseaseName = "CHOLERA";
      break;
    }
    case 3:{
      diseaseName = "DIARRHEA";
      break;
    }
    case 4:{
      diseaseName = "DYSENTERY";
      break;
    }
    default:{
      diseaseName = "FEVER";
      break;
    }
  }
  return diseaseName;
}

bool Trail::misfortune() {
  int misf = 0;
  if (getRand(100, 1) <= 40) {//probability of 40% or less
    misf = getRand(3,1);
    switch(misf) {
      case 1: { //disease          
        int disease = getRand(6,1);//random disease
        int index = getRand(getTeamSize(),0);//rand player
        string playerName = players[index].getName();
        string diseaseName = getDisease(disease);
        players[index].setSick(true);
        cout << "Oh No!!" << playerName << " has " << diseaseName << endl;

        int kits = supplies.getNumMedicalKits();
        if(kits == 0){//NO MED KIT
          int option = showMenu(DISEASE_MENU, 1,2);
          if(option == 2){//REST
            cout<< "You and your team will rest for 3 days\n";
            if(true == advanceDays(3)){//game over
              return true;
            } 
            return playerDeadWithDisease(30, index, playerName, diseaseName);
          }
          else { //PRESS ON
            return playerDeadWithDisease(70, index,playerName, diseaseName);
          }
        }
        else {//Have a MED KIT
          supplies.setMedicalKits(kits-1);
          return playerDeadWithDisease(50, index, playerName, diseaseName);
        }
        break;
      }
      case 2: { //ox dies  
        int oxen = supplies.getNumOxen();
        if(true == supplies.setOxen(oxen - 1)){
          cout << "Oh No! One of the oxen has died!! You have " << oxen - 1 << " left!" << endl;
        }
        else {    
          cout << "OH NO!!YOUR LAST OX DIED!!\n" << SORRY_GAMEOVER;      
          return true;  
        }
        break; 
      }
      default: {//wagon parts break
        int index1 = getRand(3,1);//random part
        string partName;
        int quantity;
        switch(index1){
          case 1: {
            partName = "WHEELS";
            if(supplies.getNumWheels() > 0){
              supplies.setWheels(supplies.getNumWheels()-1);
            }
            else{//No spare, game over
              cout <<  "ONE OF YOUR WHEELS IS BROKEN, YOU DO NOT HAVE A SPARE!!" << SORRY_GAMEOVER;
              return true;
            }
            break;
          }
          case 2: {
            partName = "AXLES";
            if(supplies.getNumAxels() > 0){
              supplies.setAxels(supplies.getNumAxels()-1);
            }
            else{ //No spare, game over
              cout <<  "ONE OF YOUR AXLES IS BROKEN, YOU DO NOT HAVE A SPARE!!" << SORRY_GAMEOVER;   return true;
            }
            break;
          }
          default:{
            partName = "TONGUES";
            if(supplies.getNumTongues() > 0){
              supplies.setTongues(supplies.getNumTongues()-1);
            }
            else{//No spare, game over
              cout <<  "ONE OF YOUR TONGUES IS BROKEN, YOU DO NOT HAVE A SPARE!!" << SORRY_GAMEOVER;              
              return true;
            }
            break;
          }
        }//switch wagon parts
        cout << "One of your " << partName << " was broken! You fixed it with the spare part!!\n";
        break;
      }
    } //switch       
  }
  //cout << "\nTHANK GODDDD!!!!!!" << endl;
  return false;
}

bool Trail::playerDeadWithDisease(int prob, int i, string player, string disease){
  if (getRand(100, 1) <= prob){//dead
    players[i].setDead(true);
    if(i == 0){
      cout << "YOU DIED OF " << disease << SORRY_GAMEOVER << endl;      
      return true;
    }
    cout << player << " DIED OF " << disease << endl;
  }
  else {//cured
    cout << player << " has been cured of " << disease << endl;
    players[i].setSick(false); 
  }
  return false;
}

void Trail::showGameEndMessage(){  
  PlayerStats stats;
  stats.name = players[0].getName();
  stats.miles = milesTravelled;
  stats.food = supplies.getFoodInLbs();
  stats.cash = supplies.getCashAvailable();
  cout << "\nFinal Metrics: " << stats.name << " " << stats.miles << " " << stats.food << " " << stats.cash << endl;
  savePlayerStats(stats);
}

bool::Trail::gameOver() {
  if (atDestination()) {
    return true;
  }
  return false;
}

