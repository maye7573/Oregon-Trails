#include <iostream>
#include "Player.h"

Player::Player(string name):name(name) , dead(false) , sick(false){}

Player::Player(): name(""), dead(false), sick(false){}

bool Player::isSick(){
    return sick;
}

string Player::getName() {
    return name;
}

bool Player::isDead(){
    return dead;
}

void Player::setName(string nm) {
    name = nm;
}

void Player::setSick(bool sck) {
    sick = sck;
}

void Player::setDead(bool dead) {
    dead = dead;
}

 
    

    
