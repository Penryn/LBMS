#include "book.h"

Book::Book() = default;
Book::Book(int id, const string& ISBN, const string& name, const string& author,
           const string& publisher, int year, bool borrowStatus,
           const string& borrower)
    : id(id),
      ISBN(ISBN),
      name(name),
      author(author),
      publisher(publisher),
      year(year),
      borrowStatus(borrowStatus),
      borrower(borrower) {}

Book::~Book() = default;

const int& Book::GetId() const { return id; }
void Book::SetId(int id) { Book::id = id; }

const string& Book::GetISBN() const { return ISBN; }
void Book::SetISBN(const string& ISBN) { Book::ISBN = ISBN; }

const string& Book::GetName() const { return name; }
void Book::SetName(const string& name) { Book::name = name; }

const string& Book::GetAuthor() const { return author; }
void Book::SetAuthor(const string& author) { Book::author = author; }

const string& Book::GetPublisher() const { return publisher; }
void Book::SetPublisher(const string& publisher) {
    Book::publisher = publisher;
}

int Book::GetYear() const { return year; }
void Book::SetYear(int year) { Book::year = year; }

bool Book::GetBorrowStatus() const { return borrowStatus; }
void Book::SetBorrowStatus(bool status) { Book::borrowStatus = status; }

const string& Book::GetBorrower() const { return borrower; }
void Book::SetBorrower(const string& borrower) { Book::borrower = borrower; }

istream& operator>>(istream& in, Book& book) {
    in >> book.id >> book.ISBN >> book.name >> book.author >> book.publisher >>
        book.year >> book.borrowStatus;
    if (book.borrowStatus) {
        in >> book.borrower;
    } else {
        book.borrower = "";
    }
    return in;
}
ostream& operator<<(ostream& out, const Book& book) {
    if (typeid(out) == typeid(cout)) {
        out << "书籍编号: " << book.id << "  ISBN: " << book.ISBN
            << "  书籍名称: " << book.name << "  作者: " << book.author
            << "  出版社: " << book.publisher << "  出版年份: " << book.year;
        if (book.borrowStatus) {
            out << "  书籍状态: 借阅中  借阅人: " << book.borrower;
        } else {
            out << "  书籍状态: 在库中";
        }
    } else {
        out << book.id << " " << book.ISBN << " " << book.name << " "
            << book.author << " " << book.publisher << " " << book.year << " "
            << book.borrowStatus << " " << book.borrower;
    }

    return out;
}
