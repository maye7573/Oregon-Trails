/* This file has helper member and function definitions that could be used across classes*/

#include <iostream>
#include <string>
#include <fstream>
#include "TrailHelper.h"

using namespace std;
const string INVALID_OPTION = "Invalid option. Try Again!!\n";

int splitLine(string aString,char separator,string tempArr[], int size){
  int n = aString.length();
  int count = 0;
  int startIndex = 0;

  for(int index=0;index < n; index++) {
    //number of pieces > size, return -1
    if( count == size) {
      return size;
    }

    char currChar = aString[index];
    if(separator == currChar) {
      string piece = aString.substr(startIndex, index - startIndex);
      startIndex = index + 1;
      if(piece.length() > 0) {
        tempArr[count] = piece;         
        count++;
      }
    }
  }

  if(count < size) {
    string piece = aString.substr(startIndex);
    if(piece.length() > 0) {
      tempArr[count] = piece;
      count++;
    }      
  }
  return count;
}

int showMenu(string menu, int lowOption, int highOption){ 
  int option;
  do{
    cout << menu;   
    cin >> option;

    if(option < lowOption || option > highOption) {
        cout << INVALID_OPTION;
    }
  } while(option < lowOption || option > highOption);
  return option;    
}

string lowercase(string s) {
  string r = s;
  
  for (int i = 0; i < r.length(); i++)  {
    r[i] = tolower(r[i]);   
  }
  return r; 
}

/* Random number generator that takes a divisor
   and minimum value to return */
int getRand(int divisor, int add) {
  int n = rand() % 1000 % divisor + add;
}

/*helper function used for sorting player metrics*/
bool swap(PlayerStats p1, PlayerStats p2){
  if(p1.miles > p2.miles){
    return false;
  }
  else if(p1.miles == p2.miles){
    if(p1.cash > p2.cash){
      return false;
    }
    else if(p1.cash == p2.cash){
      if(p1.food > p2.food){
        return false;
      }
      else if(p1.food == p2.food){
        return false;
      }
      else{
        return true;
      }
    }
    else{
      return true;
    }
  }
  else{
    return true; 
  }
}

/*
  Bubble sort function
  Input: PlayerStats Array and its size
  Return: None
  It sorts the array in place using bubble sort

  1. In each round, compares two adjacent players swapping them if the latter places higher than former.
  2. At the end of first round, lowest ranker player would be at the end
  3. As rounds continue, number of elements to sort goes down by 1
  4. We repeat these compare, swapping rounds until no more swaps were made in a round.

*/
void bubbleSort(PlayerStats arr[], int n){ 
  for (int i = 0; i < n-1; i++){
    int swaps = 0;     
    for (int j = 0; j < n-1-i; j++){
    //i=0
    //3 2 5 1 4
    //2 3 5 1 4 - swap j=0
    //2 3 5 1 4 no swap, j=1
    //2 3 1 5 4 - swap j =2
    //2 3 1 4 5 no swap, j=3
    //i=1
    //2 3 1 4 5 j=0 no swap
    //2 1 3 4 5 j=1 swap
    //2 1 3 4 5 j=2
    //i=2
    //1 2 3 4 5 j=0 swap
    //1 2 3 4 5 j=1 no swap
    //i=3 j=0 to 0
    //1 2 3 4 5
    
      //cout << "highScore for " << j << " " << j+1 << " //gave: " << higherScore(arr[j] , arr[j+1]) << endl;
      if(true == swap(arr[j] , arr[j+1])){  
          PlayerStats temp = arr[j];
          arr[j] = arr[j+1];
          arr[j+1] = temp;
          swaps = swaps + 1; 
      }
    }
    if(swaps==0){
      break;
    } 
  }
  //cout << "Number of swaps: " << swaps << endl;
  return;
}

void savePlayerStats(PlayerStats stats){
  ifstream file; 
  file.open("./results.txt");
  //Array of playerstats struct
  PlayerStats playerArr[100];
  string line;
  int numLines = 0;
  if(!file){
    cout << "Could not open results.txt\n";
  }
  else {
    while(getline(file, line)){
      if(numLines == 100){//hit max array size, stop!
        break;
      }    
      string tempArr[4];
      //split line into 4 fields:name,miles,food,cash
      int fields = splitLine(line,',',tempArr,4);
      string name = tempArr[0];
      int miles = stoi(tempArr[1]);
      int food = stoi(tempArr[2]);
      double cash = stod(tempArr[3]);
      //write those fields into next playerArr 
      playerArr[numLines].name = name;
      playerArr[numLines].miles = miles;
      playerArr[numLines].food = food;
      playerArr[numLines].cash = cash; 
      numLines++; 
    }
    file.close();
  }
  ofstream outFile;
  outFile.open("./results.txt");
  if(outFile){    
    playerArr[numLines++] = stats;//add current player stats to array
    bubbleSort(playerArr, numLines);
    
    for(int i = 0;i < numLines;i++){       
      //cout << "writing line: " << playerArr[i].name << "\n";
      outFile << fixed << setprecision(2) << playerArr[i].name << "," << playerArr[i].miles << "," << playerArr[i].food << "," << playerArr[i].cash << endl;
    } 
    outFile.flush();
    outFile.close(); 
  }
  return;
}


