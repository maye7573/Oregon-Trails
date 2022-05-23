#include <iostream>
#include "River.h"

River::River(string name,int depth, int length) :name(name), depth(depth),length(length){}

River::River() {}

string River::getName() {
    return name;
}
int River::getDepth(){
  return depth;
}

int River::getLength(){
  return length;
}

void River::setName(string nm) {
    name = nm;
}

void River::setDepth(int dpth) {
    depth = dpth;
}

void River::setLength(int lngth) {
    length = lngth;
}