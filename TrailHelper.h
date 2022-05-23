/*This header file has helper members and functions that could be used across classes*/
#include <iostream>
#include <iomanip>

using namespace std;

#ifndef _TrailHelper_H_
#define _TrailHelper_H_

struct PlayerStats{
      string name;
      int miles;
      int food;
      double cash;
};
const string CONGRATS = "Congrats!! You and your family have reached Oregon City before the deadline!!!\nCome and play again!!";

int splitLine(string aString,char separator, string tempArr[], int size);
int showMenu(string menu, int lowOption, int highOption);
string lowercase(string text);
int getRand(int divisor, int add);  
void bubbleSort(PlayerStats arr[], int n) ;
bool swap(PlayerStats p1, PlayerStats p2);
void savePlayerStats(PlayerStats stats);

#endif