#include <iostream>
#include "Fort.h"

Fort::Fort(string name,int distance):name(name), distance(distance){}

Fort::Fort() {}

int Fort::getDistance(){
    return distance;
}
string Fort::getName() {
    return name;
}

void Fort::setName(string nm) {
    name = nm;
}

void Fort::setDistance(int lngth) {
    distance = lngth;
}


 
    

