#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <sstream>
#include <map>
#include <set>

class Lesson{
    static int next_id_;

    protected:
        int id_;
        int auditory_number_;
        std::string subject_name_;
        std::string teacher_name_;
        std::string day_;
        int duration_;
    public:
        Lesson(): id_(next_id_++){};
        Lesson(int aud_n, std::string subj, std::string teacher, std::string day, int duration): 
            id_(next_id_++), auditory_number_(aud_n), subject_name_(subj), teacher_name_(teacher), day_(day), duration_(duration){}
        virtual ~Lesson(){};
        Lesson(Lesson&& rhs): id_(std::move(rhs.id_)), auditory_number_(std::move(rhs.auditory_number_)), subject_name_(std::move(rhs.subject_name_)), 
            teacher_name_(std::move(rhs.teacher_name_)), day_(std::move(rhs.day_)), duration_(std::move(rhs.duration_)) {}
        Lesson& operator=(const Lesson& rhs){
            id_ = rhs.id_;
            auditory_number_ = rhs.auditory_number_;
            subject_name_ = rhs.subject_name_;
            teacher_name_ = rhs.teacher_name_;
            day_ = rhs.day_;
            duration_ = rhs.duration_;
            return *this;
        }
        Lesson& operator=(Lesson&& rhs) noexcept{
            if (this != &rhs){
                id_ = rhs.id_;
                auditory_number_ = rhs.auditory_number_;
                subject_name_ = std::move(rhs.subject_name_);
                teacher_name_ = std::move(rhs.teacher_name_);
                day_ = rhs.day_;
                duration_ = std::move(rhs.duration_);
            }
            return *this;
        }
        int GetID() const{return id_;}
        int SetID(int id){id_ = id;}
        int GetAuditoryNumber() const{return auditory_number_;}
        std::string GetSubjectName() const {return subject_name_;}
        std::string GetTeacherName()const {return teacher_name_;}
        std::string GetDay()const {return day_;}
        int GetDuration()const {return duration_;}

        // Example: "ID: x | Type: x | Auditory: x | Subject: x | Teacher: x | Day: x | Duration: x"
        virtual void DisplayInfo() const = 0;
        virtual std::string GetType() const = 0;
};
int Lesson::next_id_ = 1;

class Lecture: public Lesson{
    public:
        Lecture(int aud_n, std::string subj, std::string teacher, std::string day, int duration): Lesson(aud_n, subj, teacher, day, duration){}
        Lecture(): Lesson(){}

        
        std::string GetType() const override{
            return "Lecture";
        }

        void DisplayInfo() const override{
            std::cout << "ID: " << id_ << " | " << "Type: " << GetType() << " | Auditory: " << auditory_number_ << " | Subject: " 
                << subject_name_ << " | Teacher: " << teacher_name_ << " | Day: " << day_ << " | Duration: " << duration_ << "\n";
        }
};

class Seminar: public Lesson{
    public:
        Seminar(): Lesson(){}
        Seminar(int aud_n, std::string subj, std::string teacher, std::string day, int duration): Lesson(aud_n, subj, teacher, day, duration){}


        std::string GetType() const override{
            return "Seminar";
        }
        void DisplayInfo() const override{
            std::cout << "ID: " << id_ << " | " << "Type: " << GetType() << " | Auditory: " << auditory_number_ << " | Subject: " 
                << subject_name_ << " | Teacher: " << teacher_name_ << " | Day: " << day_ << " | Duration: " << duration_ << "\n";
        }
};

class Lab: public Lesson{
    public:
        Lab(): Lesson(){}
        Lab(int aud_n, std::string subj, std::string teacher, std::string day, int duration): Lesson(aud_n, subj, teacher, day, duration){}


        std::string GetType() const override{
            return "Lab";
        }

        void DisplayInfo() const override{
            std::cout << "ID: " << id_ << " | " << "Type: " << GetType() << " | Auditory: " << auditory_number_ << " | Subject: " 
                << subject_name_ << " | Teacher: " << teacher_name_ << " | Day: " << day_ << " | Duration: " << duration_ << "\n";
        }
    
};

std::vector<Lesson*> ReadLessonsFromFileToVector(const std::string& filename){
    std::ifstream in(filename);
    if (!in.is_open()) throw std::runtime_error("Can't open the input file.");
    if (in.peek() == EOF) throw std::runtime_error("Input file is empty.");

    // Type;Auditory number;Subject_name;Teacher_name;Day;Duration
    std::vector<Lesson*> lessons;
    std::string line;
    while(std::getline(in, line)){
        std::stringstream ss(line);
        std::string aud_num, subject, teacher, day, duration, type;
        std::getline(ss, type, ';');
        std::getline(ss, aud_num, ';');
        std::getline(ss, subject, ';');
        std::getline(ss, teacher, ';');
        std::getline(ss, day, ';');
        std::getline(ss, duration, ';');
        
        Lesson* les;
        if (type == "Lecture"){
            les = new Lecture(std::stoi(aud_num), subject, teacher, day, std::stoi(duration));
        }
        else if (type == "Seminar"){
            les = new Seminar(std::stoi(aud_num), subject, teacher, day, std::stoi(duration));
        }
        else if (type == "Lab"){
            les = new Lab(std::stoi(aud_num), subject, teacher, day, std::stoi(duration));
        }
        else continue;

        lessons.push_back(les);
    }
    return lessons;
}
void HandleQueries(const std::vector<Lesson*>& lessons){
    std::cout << "Menu:\n";
    std::cout << "1: Information about lessons\n";
    std::cout << "2: Lessons' amount of each type\n";
    std::cout << "3: All lessons carrying out by a particular teacher\n";
    std::cout << "4: Overall duration of each type of lessons\n";
    std::cout << "5: List of subjects carrying out at a particular day\n";
    // std::cout << "0: Close the menu (program will be stopped)\n";
    std::cout << "Write down option (number from 1 to 5): ";
    std::string user_option_string;
    std::cin >> user_option_string;
    int option;
    try{
        option = std::stoi(user_option_string);
    }
    catch(...){
        std::cerr << "Wrong option. Try one more time\n";
        return;
    }
    if (option == 1){
        for (auto* les: lessons){
            les->DisplayInfo();
        }
    }
    else if (option == 2){
        std::map<std::string, int> map{{"Lecture", 0}, {"Seminar", 0}, {"Lab", 0}};
        for (auto* les: lessons){
            map[les->GetType()]++;
        }

        for(auto [subject, count]: map){
            std::cout << "| " << subject << ": " << count << " |";
        }
        std::cout << "\n";
    }
    else if (option == 3){
        std::cout << "Write down teacher's name: ";
        std::string name;
        std::cin.ignore();
        std::getline(std::cin, name);
        bool found = false;
        for (auto* les: lessons){
            if ((les->GetTeacherName()) == name) {
                les->DisplayInfo();
                found = true;
            }
        }
        if (!found){
            std::cout << "No information was found\n";
        }
    }

    else if (option == 4){
        std::map<std::string, int> map{{"Lecture", 0}, {"Seminar", 0}, {"Lab", 0}};
        for (auto* les: lessons){
            map[les->GetType()] += les->GetDuration();
        }
        for(auto [subject, overall_duration]: map){
            std::cout << "| " << subject << ": " << overall_duration << " |";
        }
        std::cout << "\n";
    }

    else if (option == 5){
        std::cout << "Write down a day of week: ";
        std::string day;
        std::cin >> day;
        std::set<std::string> subjects;
        for (auto* les: lessons){
            if ((les->GetDay()) == day){
                subjects.insert(les->GetSubjectName());
            }
        }
        if (subjects.size() > 0){
            for (std::string subject: subjects){
                std::cout << "| " << subject << " |";
            }
        }
        else{
            std::cout << "No information was found.";
        }
        std::cout << "\n";
    }
    else{
        throw std::invalid_argument("This option doesn't exist.");
    }
}

int main(){
    std::vector<Lesson*> lessons;
    try{
        lessons = ReadLessonsFromFileToVector("input.txt");
        HandleQueries(lessons);
    }
    catch(const std::exception& e){
        std::cout << e.what() << std::endl;
    }
    for (auto* les: lessons){
            delete les;
        }
    return 0;
}