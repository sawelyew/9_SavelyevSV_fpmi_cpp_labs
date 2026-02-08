#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

struct Mark {
    std::string subject_; // предмет
    size_t mark_; // оценка
    
    void print_mark() const{
        std::cout << subject_ << ":" << mark_;
    }

};

struct StudentData {
    std::string name_; // фамилия, инициалы
    size_t number_; // номер зачётки
    std::vector<Mark> marks_; // результаты сессии
    //TODO

    void print_info() const{
        std::cout << "name: <" << name_ << "> studentdoc: <" << number_ << "> marks: <";
        for (size_t i=0; i<marks_.size(); ++i){
            marks_[i].print_mark();
            if (i != (marks_.size()-1)){
                std::cout << ",";
            }
        }
        std::cout << ">\n";
    }


    double avg_mark() const{
        double sum = 0;
        for(size_t i=0; i<marks_.size(); ++i){
            sum += marks_[i].mark_;
        }
        int amount = marks_.size();
        return sum/amount;
    }
};

struct SubjectStat{
    std::string name_;
    double avg;
};

bool isNum(std::string num){
    int start=0;
    if (num[0]=='-') start++;
    for (int i=start; i<num.size(); ++i){
        if (!isdigit(num[i])){
            return false;
        }
    }
    return true;
}

int main() {
    try{
        std::ifstream in("input.txt");
        if (!in.is_open()){
            throw std::runtime_error("Не удалось открыть входной файл.\n");
        }
        if (in.peek() == std::fstream::traits_type::eof()){
            throw std::runtime_error("Входной файл пуст.\n");
        }
        std::string line;
        std::map<size_t, StudentData> map;
        while(std::getline(in, line)){
            size_t start = line.find_first_not_of(" ");
            if (line.find_first_of("0123456789", start) == std::ifstream::traits_type::eof()){
                throw std::runtime_error("Ошибка входных данных.1\n");
            }
            size_t end = line.find_first_of("0123456789", start)-1;

            std::string name = line.substr(start, end - start);
            if (name.size() == line.size()){
                throw std::runtime_error("Ошибка входных данных.2\n");
            }
            start = line.find_first_of("0123456789", end);
            end = line.find_first_not_of("0123456789", start);
            
            if (!isNum(line.substr(start, end - start))){
                throw std::runtime_error("Ошибка входных данных.3\n");
            }
            size_t studentnum = std::stoi(line.substr(start, end - start));

            start = line.find_first_of("[");
            end = line.find_first_of("]");
            std::string str_marks = line.substr(start + 1, end - 1 - start);

            // std::cout << "name: <" << name << "> studentdoc: <" << studentnum << "> marks: <" << str_marks << ">\n";

            std::vector<Mark> vec_marks;
            std::stringstream ss(str_marks);
            std::string text;
            while(ss >> text){
                size_t sub_start = text.find_first_not_of(" ");
                size_t sub_end = text.find_first_of(":", sub_start);
                std::string subject = text.substr(sub_start, sub_end - sub_start);

                size_t mark_start = text.find_first_of("0123456789", sub_end);
                size_t mark_end = text.find_first_not_of("0123456789", mark_start);
                std::string str_mark = text.substr(mark_start, mark_end - mark_start);
                
                // std::cout << "sub: <" << subject << "> mark: <" << str_mark << ">\n";
                Mark mark;
                mark.subject_ = subject;
                mark.mark_ = std::stoi(str_mark);
                vec_marks.push_back(mark);
            }

            StudentData student{name, studentnum, vec_marks};
            map[studentnum] = student;
        }

        if (map.empty()){
            throw std::runtime_error("Список студентов пуст. Дальнейшую программу продолжить невозможно.\n");
        }

        std::vector<StudentData> vect;

        for (const auto& [num, stud]: map){
            stud.print_info();

            // Чтобы не делать отдельный цикл под перенос студентов из map в vect для 4 задачи
            vect.push_back(stud);
        }

        std::sort(vect.begin(), vect.end(), [](const StudentData& s1, const StudentData& s2){
                if (s1.name_ == s2.name_) return s1.avg_mark() > s2.avg_mark();
                else return s1.name_ < s2.name_;
            });

        std::cout << "-------------------------\n";
        for (size_t i=0; i<vect.size(); ++i){
            std::string full_name = vect[i].name_;
            size_t end = full_name.find_first_of(" ");
            std::string surname = full_name.substr(0, end);
            std::cout << i+1 << ", " << surname << ", " << vect[i].number_ << ", " << vect[i].avg_mark() << std::endl;
            // std::cout << "avg mark: <" << vect[i].avg_mark() << ">\n";
        }
        std::cout << "-------------------------\n";
        double begin, end;
        std::cout << "Введите начало диапазона для вывода студентов со средним баллом из диапазона: ";
        if (!(std::cin >> begin)) {
            throw std::runtime_error("Не удалось ввести начало диапазона.\n");
        }
        std::cout << "Введите конец диапазона: ";
        if (!(std::cin >> end)){
            throw std::runtime_error("Не удалось ввести конец диапазона.\n");
        }

        std::vector<StudentData> filt_vect;
        for (const StudentData& stud: vect){
            double avg = stud.avg_mark();
            if (avg >= begin && avg <= end) {
                filt_vect.push_back(stud);
            }
        }
        std::sort(filt_vect.begin(), filt_vect.end(), [](const StudentData& s1, const StudentData& s2){
            return s1.avg_mark() > s2.avg_mark();
        });
        if (!filt_vect.empty()){
            for (const StudentData& stud: filt_vect){
                stud.print_info();
                std::cout << "avg mark: <" << stud.avg_mark() << ">\n";
            }
        }
        else{
            std::cout << "Не удалось найти студентов со средним баллом из заданного диапазона.\n";
        }
        std::cout << "-------------------------\n";
        std::string subj;
        std::cout << "Введите предмет для вывода студентов, сдававших его(с заглавной буквы на английском): ";
        std::cin >> subj;

        bool found_one = false;
        for (const auto& [studentdoc, stud]: map){
            bool found = std::any_of(stud.marks_.begin(), stud.marks_.end(), [&subj](const Mark& m){return m.subject_ == subj;});
            if (found){
                found_one = true;
                stud.print_info();
            }
        }
        if (!found_one){
            std::cout << "Не удалось найти студентов, сдававших заданный предмет.\n";
        }
        
        std::map<std::string, size_t> subj_count;
        std::map<std::string, double> subj_sum;

        for (const auto& [studentdoc, stud]: map){
            for (const auto& mark: stud.marks_){
                subj_count[mark.subject_]++;
                subj_sum[mark.subject_]+=mark.mark_;
            }
        }

        std::cout << "-------------------------\n";
        std::cout << "Число студентов, сдающих каждый предмет:\n";
        for (const auto& [subj, count] : subj_count) {
            std::cout << subj << ": " << count << std::endl;
        }

        std::vector<SubjectStat> vect_subj_avg;
        for (const auto& [subj, count]: subj_count){
            double avg = subj_sum[subj]/count;
            vect_subj_avg.push_back({subj, avg});
        }
        std::sort(vect_subj_avg.begin(), vect_subj_avg.end(), [](const SubjectStat& subj1, const SubjectStat& subj2){return subj1.avg > subj2.avg;});
        std::cout << "-------------------------\n";
        std::cout << "Средние баллы по каждому предмету в порядке убывания:\n";
        for (const SubjectStat& subj: vect_subj_avg){
            std::cout << subj.name_ << ": " << subj.avg << std::endl;
        }


        std::cout << "-------------------------\n";
        std::cout << "Список студентов с максимальным баллом:\n";
        bool found_a_graders = false;
        for (const auto& [studentdoc, stud]: map){
            if (stud.avg_mark() == 10){
                stud.print_info();
                found_a_graders = true;
            }
        }
        if (!found_a_graders){
            std::cout << "Отличники отсутствуют.\n";
        }


        std::cout << "-------------------------\n";
        std::cout << "Студенты с неудовлетворительными оценками:\n";
        found_one = false;
        for(const auto& [studentdoc, stud]: map){
            bool found = std::any_of(stud.marks_.begin(), stud.marks_.end(), [](const Mark& mark){
                return mark.mark_ == 1 || mark.mark_ == 2 || mark.mark_ == 3;
            });
            if (found){
                found_one = true;
                stud.print_info();
            }
        }
        if (!found_one){
            std::cout << "Не удалось найти студентов с неудовлетворительными оценками.\n";
        }


        return 0;
    }
    catch(const std::exception& e){
        std::cerr << e.what();
    }
}
