#include "time_utility.h"
#include "train.h"

#include <iostream>
#include <fstream>

void PrintVectorOfTrains(const std::vector<Train> &vector){
        std::string type;
        for (const Train &train: vector){
            if (train.GetType() == TrainType::PASSENGER) type = "PASSENGER";
            else if (train.GetType() == TrainType::FREIGHT) type = "FREIGHT";
            else if (train.GetType() == TrainType::HIGH_SPEED) type = "HIGH_SPEED";
            else if (train.GetType() == TrainType::SUBWAY) type = "SUBWAY";
            else if (train.GetType() == TrainType::SPECIALIZED) type = "SPECIALIZED";
            

            std::cout << "ID поезда: " << train.GetID() << std::endl;
            std::cout << "Тип поезда: " << type << std::endl;
            std::cout << "Поезд отправляется в " << train.GetDestination() << std::endl;
            std::cout << "Время отправления поезда: "; PrintTime(train.GetDispatchTime());
            std::cout << "Время в пути: "; PrintTime(train.GetTravellingTime());
            std::cout << "________________________" << std::endl;
        }

    }

void ReadInfoFromFileToVector(std::ifstream& in, std::vector<Train>& trains) {
    std::string line, train_id, train_type, destination, dispatch_time, travelling_time;
    
    while (std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }
        
        train_id = line;
        
        if (!std::getline(in, train_type) || 
            !std::getline(in, destination) || 
            !std::getline(in, dispatch_time) || 
            !std::getline(in, travelling_time)) {
            break;
        }
        
        try {
            Train obj(train_id, train_type, destination, dispatch_time, travelling_time);
            trains.push_back(obj);
        } catch (const std::exception& e) {
            std::cerr << "Error creating train " << train_id << ": " << e.what() << std::endl;
        }
    }
}

int main() {

    // using namespace time_utility;

    // std::random_device rd;
    // std::mt19937 generator(rd());

    // std::time_t t1 = SetTime(12, 23);
    // try {
    //     t1 = SetTime(12, 60);
    // } catch (const std::out_of_range& err) {
    //     std::cerr << err.what() << std::endl;
    // }

    // std::time_t t2 = GenerateRandomTime(generator);

    // std::cout << "t1: ";
    // PrintTime(t1);
    
    // std::cout << "t2: ";
    // PrintTime(t2);
    
    // std::cout << "t1 < t2: " << std::boolalpha << (t1 < t2) <<'\n';
    // std::cout << "t2 < t1: " << std::boolalpha << (t2 < t1) << '\n';
    try {
    std::ifstream in("trains.txt");
    std::vector<Train> trains;
    ReadInfoFromFileToVector(in, trains);
    PrintVectorOfTrains(trains);


    

    std::sort(trains.begin(), trains.end(), [](const Train &a, const Train &b){ 
        return a.GetDispatchTime() < b.GetDispatchTime();
    });

    std::cout << "\nПОСЛЕ СОРТИРОВКИ\n" << std::endl;
    PrintVectorOfTrains(trains);





    std::cout << "Введите начало диапазона времени для отслеживания поездов: ";
    std::string string_begin_interval;
    if (!(std::getline(std::cin, string_begin_interval))){
        throw std::runtime_error("Ошибка! Неправильно введен диапазон");
    }
    if(string_begin_interval.size() < 4){
        throw std::runtime_error("Ошибка! Начальный диапазон введен неверно.");
    }

    std::string string_end_interval;
    if (!(std::getline(std::cin, string_end_interval))){
        throw std::runtime_error("Ошибка! Неправильно введен диапазон");
    }

    if(string_end_interval.size() < 4){
        throw std::runtime_error("Ошибка! Начальный диапазон введен неверно.");
    }

    std::string::size_type beg_index = string_begin_interval.find_first_of("0123456789");
    std::string::size_type end_index = string_begin_interval.find_first_of(" :", beg_index);
    std::string begin_hours = string_begin_interval.substr(beg_index, end_index - beg_index);

    try {
        int hours = std::stoi(begin_hours);
        if (hours < 0 || hours > 23) {
            throw std::invalid_argument("Ошибка! Часы должны быть от 0 до 23");
        }
    }
    catch (const std::invalid_argument&) {
        throw std::invalid_argument("Ошибка! Неверно заданы часы начального диапазона");
    }


    beg_index = string_begin_interval.find_first_of("0123456789", end_index);
    end_index = string_begin_interval.find_first_of(" :", beg_index);
    std::string begin_minutes = string_begin_interval.substr(beg_index, end_index - beg_index);
    

    try {
    int minutes = std::stoi(begin_minutes);
    if (minutes < 0 || minutes > 59) {
        throw std::invalid_argument("Ошибка! Минуты должны быть от 0 до 59");
    }
} catch (const std::invalid_argument&) {
    throw std::invalid_argument("Ошибка! Неверно заданы минуты начального диапазона");
}


    beg_index = string_end_interval.find_first_of("0123456789");
    end_index = string_end_interval.find_first_of(" :", beg_index);
    std::string end_hours = string_end_interval.substr(beg_index, end_index - beg_index);


    try {
        int hours = std::stoi(end_hours);
        if (hours < 0 || hours > 23) {
            throw std::invalid_argument("Ошибка! Часы должны быть от 0 до 23");
        }
    } 
    catch (const std::invalid_argument&) {
        throw std::invalid_argument("Ошибка! Неверно заданы часы конечного диапазона");
    }

    beg_index = string_end_interval.find_first_of("0123456789", end_index);
    end_index = string_end_interval.find_first_of(" :", beg_index);
    std::string end_minutes = string_end_interval.substr(beg_index, end_index - beg_index);

    try {
        int minutes = std::stoi(end_minutes);
        if (minutes < 0 || minutes > 59) {
            throw std::invalid_argument("Ошибка! Минуты должны быть от 0 до 59");
        }
    } 
    catch (const std::invalid_argument&) {
        throw std::invalid_argument("Ошибка! Неверно заданы минуты конечного диапазона");
    }

    std::time_t begin_interval = SetTime(std::stoi(begin_hours), std::stoi(begin_minutes));
    std::time_t end_interval = SetTime(std::stoi(end_hours), std::stoi(end_minutes));


    if (begin_interval > end_interval){
        std::swap(begin_interval, end_interval);
    }


    std::vector<Train> interval_trains;
    for (const Train &train: trains){
        if (train.GetDispatchTime() >= begin_interval && train.GetDispatchTime() <= end_interval){
            interval_trains.push_back(train);
        }
    }
    if (interval_trains.size() == 0){
        std::cout << "Не найдено ни одного поезда из заданного диапазона." << std::endl;
    }
    else{
        std::cout << "\nПоезда из заданного диапазона: \n";
        PrintVectorOfTrains(interval_trains);
    }



    std::string city;
    std::cout << "Введите город для просмотра доступных рейсов(на английском языке заглавными буквами): ";
    if (!(std::cin >> city)){
        throw std::runtime_error("Неправильно введен город");
    }

    std::vector<Train> city_trains;
    for (const Train &train: trains){
        if (train.GetDestination() == city){
            city_trains.push_back(train);
        }
    }

    if (city_trains.size() == 0){
        std::cout << "Не удалось найти поезда с назначением в заданный город." << std::endl;
    }
    else{
        std::cout << "\nПоезда с заданным городом: \n" << std::endl;
        PrintVectorOfTrains(city_trains);
    }


    std::string type;
    std::cout << "Введите тип поезда(PASSENGER, FREIGHT, HIGH_SPEED, SUBWAY, SPECIALIZED): ";
    std::cin >> type;
    std::vector<Train> type_and_city_trains;
    for (const Train &train: city_trains){
        TrainType type_in_for;
        if (type == "PASSENGER") type_in_for = TrainType::PASSENGER;
        else if (type == "FREIGHT") type_in_for = TrainType::FREIGHT;
        else if (type == "HIGH_SPEED") type_in_for = TrainType::HIGH_SPEED;
        else if (type == "SUBWAY") type_in_for = TrainType::SUBWAY;
        else if (type == "SPECIALIZED") type_in_for = TrainType::SPECIALIZED;

        if(train.GetType() == type_in_for){
            type_and_city_trains.push_back(train);
        }
    }

    if(type_and_city_trains.size() == 0){
        std::cout << "Не удалось найти поезда с заданным типом и диапазоном времени." << std::endl;
    }
    else{
        std::cout << "\n Поезда с заданным типом и диапазоном времени:\n" << std::endl;
        PrintVectorOfTrains(type_and_city_trains);
    }
    if (city_trains.size() != 0){
        std::vector<Train> fastest_trains{city_trains[0]};
        Train fastest_train = fastest_trains[0];
        for(size_t i = 1; i < city_trains.size(); ++i){
            if (city_trains[i].GetTravellingTime() < fastest_train.GetTravellingTime()){
                fastest_trains.clear();
                fastest_trains.push_back(city_trains[i]);
                fastest_train = city_trains[i];
            }
            else if (city_trains[i].GetTravellingTime() == fastest_train.GetTravellingTime()){
                fastest_trains.push_back(city_trains[i]);
            }
        }
        std::cout << "\nСамые быстрые поезда в заданный город: \n" << std::endl;
        PrintVectorOfTrains(fastest_trains);
    }

    return EXIT_SUCCESS;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}