#include <iostream>
#include <fstream>
#include <exception>
#include "figures.h"
#include "logger.h"

class MoveLogger;
std::string GetLetterByNumChess(int x){
    if (x==1) return "a";
    else if (x==2) return "b";
    else if (x==3) return "c";
    else if (x==4) return "d";
    else if (x==5) return "e";
    else if (x==6) return "f";
    else if (x==7) return "g";
    else if (x==8) return "h";
    else throw std::runtime_error("Error with convertation letter into num.");
}

std::string ChessPiece::getColor(){
    if (color_ == Colors::Black) return "black";
    else return "white";
}
ChessPiece::ChessPiece(int x, int y, Colors color): x_curr_(x), y_curr_(y), color_(color){}
ChessPiece::ChessPiece(ChessPiece&& rhs): color_(rhs.color_), x_curr_(rhs.x_curr_), y_curr_(rhs.y_curr_){
    rhs.x_curr_ = 0; rhs.y_curr_ = 0;
}
ChessPiece& ChessPiece::operator=(ChessPiece&& rhs){
    if (this != &rhs){
        color_ = rhs.color_;
        x_curr_ = rhs.x_curr_;
        y_curr_ = rhs.y_curr_;
        rhs.x_curr_ = 0;
        rhs.y_curr_ = 0;
        }
    return *this;
}
ChessPiece::~ChessPiece(){}

Bishop::Bishop(int x, int y, Colors color): ChessPiece(x,y, color){}
Bishop::Bishop(Bishop&& rhs): ChessPiece(std::move(rhs)) {}
Bishop& Bishop::operator=(Bishop&& rhs){
    ChessPiece::operator=(std::move(rhs));
    return *this;
}
std::string Bishop::GetInfo(){
    return "B"+GetLetterByNumChess(x_curr_)+std::to_string(y_curr_);
}
bool Bishop::CanMove(uint16_t x, uint16_t y){
    return (x-x_curr_ == y-y_curr_);
}
void Bishop::Move(uint16_t x, uint16_t y, MoveLogger& logger){
    if (CanMove(x,y)){  
        logger.AddMove(this, x, y);
        setX(x);
        setY(y);
    }
    else{
        throw std::invalid_argument("Невозможно переместить слона на данную позицию.");
    }
}


Rook::Rook(int x, int y, Colors color): ChessPiece(x,y, color){}
Rook::Rook(Rook&& rhs): ChessPiece(std::move(rhs)) {}
Rook& Rook::operator=(Rook&& rhs){
    ChessPiece::operator=(std::move(rhs));
    return *this;
}
std::string Rook::GetInfo(){
    return "R"+GetLetterByNumChess(x_curr_)+std::to_string(y_curr_);
}
bool Rook::CanMove(uint16_t x, uint16_t y){
    return ((x-x_curr_) == 0 || (y-y_curr_)==0);
}
void Rook::Move(uint16_t x, uint16_t y, MoveLogger& logger){
    if (this->CanMove(x,y)){
        logger.AddMove(this, x, y);
        setX(x);
        setY(y);
    }
    else{
        throw std::invalid_argument("Невозможно переместить ладью на данную позицию.");                
    }
}


Queen::Queen(int x, int y, Colors color): ChessPiece(x,y,color), Rook(x,y,color), Bishop(x,y,color){}
Queen::Queen(Queen&& rhs): ChessPiece(std::move(rhs)), Rook(std::move(rhs)), Bishop(std::move(rhs)){}
Queen& Queen::operator=(Queen&& rhs){
    Rook::operator=(std::move(rhs));
    Bishop::operator=(std::move(rhs));
    return *this;
}
std::string Queen::GetInfo(){
    return "Q"+GetLetterByNumChess(x_curr_)+std::to_string(y_curr_);
}
bool Queen::CanMove(uint16_t x, uint16_t y){
    return (Rook::CanMove(x,y) || Bishop::CanMove(x,y));
}
void Queen::Move(uint16_t x, uint16_t y, MoveLogger& logger){
    if (CanMove(x,y)){
        logger.AddMove(this, x, y);
        setX(x);
        setY(y);
    }
    else{
        throw std::invalid_argument("Невозможно переместить ферзя на данную позицию.");
    }
}
