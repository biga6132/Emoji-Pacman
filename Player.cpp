
#include "Player.h"
#include <iostream>
#include <string>

Player::Player(const std::string name, const bool is_human){
    name_ = name;
    is_human_ = is_human;
    points_ = 0;
    has_Treasure_ = false;
    isDead_ = false;
    moves_ = 0;
}

void Player::ChangePoints(const int x){
    points_ += x;
}

void Player::SetPosition(Position pos){
    pos_ = pos;
}

void Player::setHasTreasure(){
    has_Treasure_ = (!has_Treasure_);
}

void Player::setIsDead(bool isdead){
    isDead_ = isdead;
}

void Player::setLives(){
    lives_--;
}

std::string Player::ToRelativePosition(Position other){
    if(pos_.row-1 == other.row && pos_.col == other.col){
        return "U";
    }
    if(pos_.row+1 == other.row && pos_.col == other.col){
        return "D";
    }
    if(pos_.row == other.row && pos_.col-1 == other.col){
        return "L";
    }
    if(pos_.row == other.row && pos_.col+1 == other.col){
        return "R";
    }
    else{
        return "E";
    }
}


std::string Player::Stringify(){
    return name_ + " has " + std::to_string(getLives()) + " lives remaining";
}

int Player::getMoves(){
    return moves_;
}

void Player::incrementMoves(){
    moves_++;
}
