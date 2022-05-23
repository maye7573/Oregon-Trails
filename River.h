#include <iostream>
#include <iomanip>

using namespace std;

#ifndef _RIVER_H_
#define _RIVER_H_

class River {
  public:
    River();
    River(string name,int depth, int length);

    //Accessors
    string getName();
    int getDepth();
    int getLength();

    //Mutators
    void setName(string nm);
    void setDepth(int dpth);
    void setLength(int lngth);

  private:    
    string  name;
    int     length;
    int     depth;
};

#endif