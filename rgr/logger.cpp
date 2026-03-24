#include <iostream>
#include <string>
#include <fstream>
#include "logger.h"
#include "figures.h"


MoveLogger::MoveLogger(): id_(next_id_++){}
MoveLogger::~MoveLogger(){
    std::string filename = "game_" + std::to_string(id_) + "_log.txt";
    std::ofstream out(filename);
    for (const std::string& move: history){
        out << move << "\n";

    }
}
void MoveLogger::AddMove(ChessPiece* figure, int x, int y){
    std::string from = figure->GetInfo();
    std::string to = GetLetterByNumChess(x) + std::to_string(y);
    std::string color = figure->getColor();

    std::string record = std::to_string(history.size() + 1) + ". " + color + ": " + from + " - " + to;
    history.push_back(record);
}
int MoveLogger::next_id_ = 1;