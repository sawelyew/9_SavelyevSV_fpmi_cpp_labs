#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <exception>
#include <algorithm>


struct Author{
    std::string first_name_;
    std::string last_name_;
    std::string surname_;

    Author(std::string first_name, std::string last_name, std::string surname): 
        first_name_(first_name), last_name_(last_name), surname_(surname){}

    void PrintAuthor(){
        std::cout << first_name_ << " " << last_name_ << " " << surname_ << std::endl;
    }

    bool operator==(const Author& other) const {
        return first_name_ == other.first_name_ && 
               last_name_ == other.last_name_ && 
               surname_ == other.surname_;
    }

};

struct Book{
    int udk_;
    std::string name_;
    int year_;
    std::list<Author> authors_;

    Book(int udk, std::string name, int year, std::list<Author> authors):
        udk_(udk), name_(name), year_(year), authors_(authors){}

    void PrintBook(){
        std::cout << "Книга: " << name_ << std::endl;
        std::cout << "Год: " << year_ << std::endl;
        std::cout << "Авторы: " << std::endl;
        for(Author author: authors_){
            std::cout << author.first_name_ + " " + author.last_name_ + " " + author.surname_ << std::endl;
        }
        std::cout << "UDK: " << udk_ << std::endl;
    }
};

class Library{
    private:
        std::list<Book> books_;
    public:
        Library() = default;
        Library(std::list<Book> books): books_(books){
        books_.sort(
        [](const Book &book_a, const Book &book_b){ return book_a.name_ < book_b.name_; });
}

        Library(std::initializer_list<Book> list){
        for(Book book: list){
            books_.push_back(book);
        }
        books_.sort(
        [](const Book &book_a, const Book &book_b){ return book_a.name_ < book_b.name_; });
}

        
        std::list<Book> GetListOfBooks(){
            return books_;
        }

        void AddBookToLibrary(const Book &book){
            books_.push_back(book);
            books_.sort(
            [](const Book &book_a, const Book &book_b){ return book_a.name_ < book_b.name_; });
}


        void DeleteBookFromLibrary(const std::string &name){
            std::list<Book>::iterator it = std::find_if(books_.begin(), books_.end(),
            [&name](const Book& book) {return book.name_ == name;});

            if (it != books_.end()){
                books_.erase(it);
            }
            else{
                std::cout << "Книги с данным названием не было найдено." << std::endl;
            }
        }

        void FindBookByName(const std::string &name){
            std::cout << "Книги с названием " + name + ": " << std::endl;
            for(Book book: books_){
                if (book.name_ == name){
                    book.PrintBook();
                }
            }
        }

        void FindBooksByAuthor(const Author &author){
            std::cout << "Книги автора " + author.first_name_ + " " + author.last_name_ + " " + author.surname_ + ": " << std::endl;
            for (const Book &book : books_) {
                if (std::find(book.authors_.begin(), book.authors_.end(), author) != book.authors_.end()) {
                    std::cout << "Книга: " << book.name_ << std::endl;
                    std::cout << "Год: " << book.year_ << std::endl;
                    std::cout << "Авторы: " << std::endl;
                    for(Author author: book.authors_){
                        std::cout << author.first_name_ + " " + author.last_name_ + " " + author.surname_ << std::endl;
                    }
                    std::cout << "UDK: " << book.udk_ << std::endl;
                }
            }
        }

        void AddAuthorToBook(std::string book_name, Author &author){
            for(Book &book: books_){
                if (book.name_ == book_name){
                    book.authors_.push_back(author);
                }
            }
            books_.sort(
            [](const Book &book_a, const Book &book_b){ return book_a.name_ < book_b.name_; });
}


        void DeleteAuthorFromBook(std::string book_name, Author &author){
            for(Book &book: books_){
                if (book.name_ == book_name){
                    book.authors_.remove(author);
                }
            }
        }

        void PrintAllBooks() const {
        if (books_.empty()) {
            std::cout << "Library is empty\n;";
            return;
        }
        for (const Book& book : books_) {
            std::cout << "Книга: " << book.name_ << std::endl;
            std::cout << "Год: " << book.year_ << std::endl;
            std::cout << "Авторы: " << std::endl;
            for(Author author: book.authors_){
                std::cout << author.first_name_ + " " + author.last_name_ + " " + author.surname_ << std::endl;
            }
            std::cout << "UDK: " << book.udk_ << std::endl;
        }
    }

};



std::vector<std::string> SplitText(const std::string& text, const std::string& delimeters) {
    
    std::vector<std::string> words;

    std::string::size_type beg_index = 0;
    std::string::size_type end_index = text.find_first_of(delimeters, beg_index);
    
    while (beg_index != std::string::npos) {
    
        std::string word = text.substr(beg_index, end_index - beg_index);
        if (!word.empty()) {
            words.push_back(word);
        }

        beg_index = text.find_first_not_of(delimeters, end_index);
        end_index = text.find_first_of(delimeters, end_index + 1);
    }

    return words;
}

Author FromStringToAuthor(std::string line){
    std::vector<std::string> vect_author = SplitText(line, " ");
    Author author(vect_author[0], vect_author[1], vect_author[2]);
    return author;
}

void ReadFromFileToLibrary(std::ifstream &in, Library &library){
    std::string line, udk, name, authors, year;

    while (std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }
        
        udk = line;
        
        if (!std::getline(in, name) || 
            !std::getline(in, year) || 
            !std::getline(in, authors)) {
            break;
        }
        
        try {
            std::list<Author> list_authors;
            list_authors.push_back(FromStringToAuthor(authors));
            Book book(std::stoi(udk), name, std::stoi(year), list_authors);
            library.AddBookToLibrary(book);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

}


int main() {
    std::ifstream in("input.txt");
    
    if (!(in.is_open())){
        throw std::runtime_error("Ошибка! Невозможно открыть файл.");
    }

    if (in.peek() == EOF) { 
        throw std::runtime_error("Ошибка! Файл пуст.");
    }

    Library library;
    ReadFromFileToLibrary(in, library);
    std::cout << "Исходная библиотека после чтения: " << std::endl;
    library.PrintAllBooks();

    Book new_book{123, "Новая книга", 2025, {{"Сергеев", "Александр", "Михайлович"}}};
    std::cout << "Добавление новой книги:\n";
    new_book.PrintBook();

    library.AddBookToLibrary(new_book);
    std::cout << "Библиотека после добавления новой книги:\n";
    library.PrintAllBooks();

    std::string title = "New Book";
    library.FindBookByName(title);

    Author new_author{"Зубенко", "Михаил", "Петрович"};
    std::cout << "Добавление нового автора к книге:\n";
    library.AddAuthorToBook(title, new_author);
    library.FindBookByName(title);
    
    std::cout << "Новый автор был удален:\n";
    library.DeleteAuthorFromBook(title, new_author);
    library.FindBookByName(title);

    Author search_author{"Сергеев", "Александр", "Михайлович"};
    library.FindBooksByAuthor(search_author);

    std::cout << "Библиотека после удаления New book:\n";
    library.DeleteBookFromLibrary("New Book"); 
    library.PrintAllBooks();







    return 0;
}