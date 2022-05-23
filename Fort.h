#include <iostream>
#include <iomanip>

using namespace std;

#ifndef _FORT_H_
#define _FORT_H_

class Fort {
  public:
    Fort();
    Fort(string name,int distance);

    //Accessors
    string getName();
    int getDistance();

    //Mutators
    void setName(string nm);
    void setDistance(int lngth);

  private:    
    string  name;
    int     distance;    
};
#endif