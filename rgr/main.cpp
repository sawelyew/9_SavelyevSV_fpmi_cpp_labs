#include <iostream>
#include <fstream>
#include <exception>
#include "figures.h"
#include "logger.h"

int main(){
    MoveLogger logger;
    Queen que(1,1,Colors::Black);
    que.Move(1,5, logger);
    Bishop bish(1,1, Colors::Black);
    bish.Move(2,2, logger);
    

    return 0;
}