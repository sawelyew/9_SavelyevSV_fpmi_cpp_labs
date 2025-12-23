#pragma once

#include <string>
#include "time_utility.h"
#include <fstream>
#include <vector>
#include <iostream>

using TrainId = size_t;
using namespace time_utility;


enum class TrainType { 
    PASSENGER, FREIGHT, HIGH_SPEED, SUBWAY, SPECIALIZED
};


class Train {
private:
    TrainId id_;
    TrainType type_;
    std::string destination_;
    std::time_t dispatch_time_;
    std::time_t travelling_time_;

public:
    // your code goes here
    Train(std::string id, std::string type, std::string destination, std::string dispatch_time, std::string travelling_time){

        id_ = std::stoi(id);

        if (type == "PASSENGER") type_ = TrainType::PASSENGER;
        else if (type == "FREIGHT") type_ = TrainType::FREIGHT;
        else if (type == "HIGH_SPEED") type_ = TrainType::HIGH_SPEED;
        else if (type == "SUBWAY") type_ = TrainType::SUBWAY;
        else if (type == "SPECIALIZED") type_ = TrainType::SPECIALIZED;
        else {throw "Ошибка! Несуществующий тип поезда.";}

        destination_ = destination;


        std::string::size_type beg_index = dispatch_time.find_first_of("0123456789");
        std::string::size_type end_index = dispatch_time.find_first_of(" :", beg_index);
        std::string disp_hours = dispatch_time.substr(beg_index, end_index - beg_index);

        beg_index = dispatch_time.find_first_of("0123456789", end_index);
        end_index = dispatch_time.find_first_of(" :", beg_index);
        std::string disp_minutes = dispatch_time.substr(beg_index, end_index - beg_index);

        beg_index = travelling_time.find_first_of("0123456789");
        end_index = travelling_time.find_first_of(" :", beg_index);
        std::string trav_hours = travelling_time.substr(beg_index, end_index - beg_index);

        beg_index = travelling_time.find_first_of("0123456789", end_index);
        end_index = travelling_time.find_first_of(" :", beg_index);
        std::string trav_minutes = travelling_time.substr(beg_index, end_index - beg_index);

        // std::vector<std::string> vect_disp = SplitText(dispatch_time, ":");
        // std::vector<std::string> vect_trav = SplitText(travelling_time, ":");
        

        dispatch_time_ = SetTime(std::stoi(disp_hours), std::stoi(disp_minutes));
        travelling_time_ = SetTime(std::stoi(trav_hours), std::stoi(trav_minutes));
    }

    int GetID() const{
        return id_;
    }

    TrainType GetType() const{
        return type_;
    }

    std::string GetDestination() const{
        return destination_;
    }

    std::time_t GetDispatchTime() const{
        return dispatch_time_;
    }

    std::time_t GetTravellingTime() const{
        return travelling_time_;
    }

};
