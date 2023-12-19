#include "bookManager.h"

#include <fstream>
#include <iostream>
using namespace std;

BookManager::BookManager() = default;

BookManager::~BookManager() = default;

void BookManager::Init() {
    string file = "../data/book.txt";

    ifstream in;
    in.open(file, ios::in);
    if (!in.is_open()) {
        ofstream out;
        out.open(file, ios::out | ios::app);
        out.close();
        in.open(file, ios::in);
    }

    Book book;
    while (in.peek() != EOF) {
        in >> book;
        bookManager.insertUnique(bookManager.end(), book);
    }

    in.close();
}

void BookManager::Insert() {
    string ISBN, name, author, publisher;
    int year, count;

    cout << "请输入ISBN号: ";
    cin >> ISBN;
    cout << "请输入书籍名称: ";
    cin >> name;
    cout << "请输入作者: ";
    cin >> author;
    cout << "请输入出版社: ";
    cin >> publisher;
    cout << "请输入出版年份: ";
    cin >> year;
    cout << "请输入数量: ";
    cin >> count;

    cout << "请确认书籍信息 (输入y/yes确认) : " << endl
         << "ISBN: " << ISBN << "  书籍名称: " << name << "  作者: " << author
         << "  出版社: " << publisher << "  出版年份: " << year
         << "  数量: " << count << "\n> ";
    string confirm;
    cin.get();
    getline(cin, confirm);

    if (confirm == "y" || confirm == "yes") {
        while (count--) {
            bookManager.insertUnique(bookManager.end(),
                                     Book(bookManager.size() + 1, ISBN, name,
                                          author, publisher, year, false, ""));
        }
        cout << "已成功添加" << endl;
    } else {
        cout << "已取消添加" << endl;
    }

    cout << "是否继续添加 (输入y/yes继续)\n> ";
    getline(cin, confirm);
    if (confirm == "y" || confirm == "yes") {
        Insert();
    }
}

bool BookManager::Empty() { return bookManager.empty(); }

void BookManager::FindByPage(int currPage, int pageSize) {
    size_t size = bookManager.size();
    size_t totalPages = (size - 1) / pageSize + 1;
    if (currPage < 0 || currPage > totalPages) {
        cout << "输入页数有误, 请重新输入 (退出查看输入0)\n> ";
        if (cin >> currPage && currPage) {
            FindByPage(currPage, pageSize);
        }
        return;
    }

    int firstIndex = (currPage - 1) * pageSize;
    auto it = bookManager.begin();
    while (firstIndex--) {
        ++it;
    }
    cout << "-----" << endl;
    int n = pageSize;
    while (n-- && it != bookManager.end()) {
        cout << *(it++) << endl;
    }
    cout << "-----" << endl;

    cout << "当前第 " << currPage << " 页, 共 " << totalPages
         << " 页, 请输入跳转页 (退出查看输入0)\n> ";
    if (cin >> currPage && currPage) {
        FindByPage(currPage, pageSize);
    }
}

void BookManager::FindByID() {
    int id;
    cout << "请输入要查询的书籍编号: ";
    cin >> id;

    auto it = bookManager.find(id);
    if (it != bookManager.end()) {
        cout << *it << endl;
    } else {
        cout << "该书籍编号不存在" << endl;
    }

    cout << "是否继续查询 (输入y/yes继续)\n> ";
    string confirm;
    cin.get();
    getline(cin, confirm);
    if (confirm == "y" || confirm == "yes") {
        FindByID();
    }
}

void BookManager::FindByISBN() {
    string ISBN;
    cout << "请输入要查询的书籍ISBN号: ";
    cin >> ISBN;

    bool find = false;
    int inCount = 0, outCount = 0;
    auto it = bookManager.begin();
    while (it != bookManager.end()) {
        if (it->GetISBN() == ISBN) {
            if (!find) {
                cout << "ISBN: " << it->GetISBN()
                     << "  书籍名称: " << it->GetName()
                     << "  作者: " << it->GetAuthor()
                     << "  出版社: " << it->GetPublisher()
                     << "  出版年份: " << it->GetYear() << endl;
                find = true;
            }
            if (it->GetBorrowStatus()) {
                cout << "书籍编号: " << it->GetId()
                     << "  借阅人: " << it->GetBorrower() << endl;
                ++outCount;
            } else {
                ++inCount;
            }
        }
        ++it;
    }
    if (find) {
        cout << "共 " << inCount + outCount << " 本  ";
        if (outCount) {
            cout << "借阅中: " << outCount << "本  ";
        }
        cout << "在库中: " << inCount << "本" << endl;
    } else {
        cout << "该ISBN号不存在" << endl;
    }

    cout << "是否继续查询 (输入y/yes继续)\n> ";
    string confirm;
    cin.get();
    getline(cin, confirm);
    if (confirm == "y" || confirm == "yes") {
        FindByISBN();
    }
}

void BookManager::UpdateByID() {
    int id;
    cout << "请输入要更新的书籍编号: ";
    cin >> id;

    auto it = bookManager.find(id);
    if (it != bookManager.end()) {
        cout << "原书籍信息: " << endl
             << "ISBN: " << it->GetISBN() << "  书籍名称: " << it->GetName()
             << "  作者: " << it->GetAuthor()
             << "  出版社: " << it->GetPublisher()
             << "  出版年份: " << it->GetYear() << endl
             << "是否更新 (输入y/yes更新)\n> ";
        string confirm;
        cin.get();
        getline(cin, confirm);
        if (confirm == "y" || confirm == "yes") {
            string updateISBN, updateName, updateAuthor, updatePublisher;
            int updateYear;

            cout << "请输入更新后的ISBN号 (不更新输入0): ";
            cin >> updateISBN;
            if (updateISBN == "0") {
                updateISBN = it->GetISBN();
            }
            cout << "请输入更新后的书籍名称 (不更新输入0): ";
            cin >> updateName;
            if (updateName == "0") {
                updateName = it->GetName();
            }
            cout << "请输入更新后的作者 (不更新输入0): ";
            cin >> updateAuthor;
            if (updateAuthor == "0") {
                updateAuthor = it->GetAuthor();
            }
            cout << "请输入更新后的出版社 (不更新输入0): ";
            cin >> updatePublisher;
            if (updatePublisher == "0") {
                updatePublisher = it->GetPublisher();
            }
            cout << "请输入更新后的出版年份 (不更新输入0): ";
            cin >> updateYear;
            if (updateYear == 0) {
                updateYear = it->GetYear();
            }

            cout << "请确认更新后的书籍信息 (输入y/yes确认) : " << endl
                 << "ISBN: " << updateISBN << "  书籍名称: " << updateName
                 << "  作者: " << updateAuthor
                 << "  出版社: " << updatePublisher
                 << "  出版年份: " << updateYear << "\n> ";
            cin.get();
            getline(cin, confirm);
            if (confirm == "y" || confirm == "yes") {
                it->SetISBN(updateISBN);
                it->SetName(updateName);
                it->SetAuthor(updateAuthor);
                it->SetPublisher(updatePublisher);
                it->SetYear(updateYear);
                cout << "已成功更新" << endl;
            } else {
                cout << "已取消更新" << endl;
            }
        } else {
            cout << "已取消更新" << endl;
        }
    } else {
        cout << "该书籍编号不存在" << endl;
        cin.get();
    }

    cout << "是否继续更新 (输入y/yes继续)\n> ";
    string confirm;
    getline(cin, confirm);
    if (confirm == "y" || confirm == "yes") {
        UpdateByID();
    }
}

void BookManager::UpdateByISBN() {
    string ISBN;
    cout << "请输入要更新的书籍ISBN号: ";
    cin >> ISBN;

    bool find = false;
    auto it = bookManager.begin();
    while (it != bookManager.end()) {
        if (it->GetISBN() == ISBN) {
            find = true;
            break;
        }
        ++it;
    }
    if (find) {
        cout << "原书籍信息: " << endl
             << "ISBN: " << it->GetISBN() << "  书籍名称: " << it->GetName()
             << "  作者: " << it->GetAuthor()
             << "  出版社: " << it->GetPublisher()
             << "  出版年份: " << it->GetYear() << endl
             << "是否更新 (输入y/yes更新)\n> ";
        string confirm;
        cin.get();
        getline(cin, confirm);
        if (confirm == "y" || confirm == "yes") {
            string updateISBN, updateName, updateAuthor, updatePublisher;
            int updateYear;

            cout << "请输入更新后的ISBN号 (不更新输入0): ";
            cin >> updateISBN;
            if (updateISBN == "0") {
                updateISBN = it->GetISBN();
            }
            cout << "请输入更新后的书籍名称 (不更新输入0): ";
            cin >> updateName;
            if (updateName == "0") {
                updateName = it->GetName();
            }
            cout << "请输入更新后的作者 (不更新输入0): ";
            cin >> updateAuthor;
            if (updateAuthor == "0") {
                updateAuthor = it->GetAuthor();
            }
            cout << "请输入更新后的出版社 (不更新输入0): ";
            cin >> updatePublisher;
            if (updatePublisher == "0") {
                updatePublisher = it->GetPublisher();
            }
            cout << "请输入更新后的出版年份 (不更新输入0): ";
            cin >> updateYear;
            if (updateYear == 0) {
                updateYear = it->GetYear();
            }

            cout << "请确认更新后的书籍信息 (输入y/yes确认) : " << endl
                 << "ISBN: " << updateISBN << "  书籍名称: " << updateName
                 << "  作者: " << updateAuthor
                 << "  出版社: " << updatePublisher
                 << "  出版年份: " << updateYear << "\n> ";
            cin.get();
            getline(cin, confirm);

            if (confirm == "y" || confirm == "yes") {
                while (it != bookManager.end()) {
                    if (it->GetISBN() == ISBN) {
                        it->SetISBN(updateISBN);
                        it->SetName(updateName);
                        it->SetAuthor(updateAuthor);
                        it->SetPublisher(updatePublisher);
                        it->SetYear(updateYear);
                    }
                    ++it;
                }
                cout << "已成功更新" << endl;
            } else {
                cout << "已取消更新" << endl;
            }
        } else {
            cout << "已取消更新" << endl;
        }
    } else {
        cout << "该ISBN号不存在" << endl;
        cin.get();
    }

    cout << "是否继续更新 (输入y/yes继续)\n> ";
    string confirm;
    getline(cin, confirm);
    if (confirm == "y" || confirm == "yes") {
        UpdateByISBN();
    }
}

void BookManager::RemoveByID() {
    int id;
    cout << "请输入要删除的书籍编号: ";
    cin >> id;

    auto it = bookManager.find(id);
    if (it != bookManager.end()) {
        cout << "书籍信息: " << endl
             << *it << endl
             << "是否删除 (输入y/yes删除)\n> ";
        string confirm;
        cin.get();
        getline(cin, confirm);
        if (confirm == "y" || confirm == "yes") {
            if (it->GetBorrowStatus()) {
                cout << "该书籍已出借, 借阅人: " << it->GetBorrower()
                     << " , 是否确认删除 (输入y/yes确认)\n> ";
                getline(cin, confirm);
                if (confirm == "y" || confirm == "yes") {
                    bookManager.erase(it);
                    cout << "已成功删除" << endl;
                } else {
                    cout << "已取消删除" << endl;
                }
            } else {
                bookManager.erase(it);
                cout << "已成功删除" << endl;
            }
        } else {
            cout << "已取消删除" << endl;
        }
    } else {
        cout << "该书籍编号不存在" << endl;
        cin.get();
    }

    cout << "是否继续删除 (输入y/yes继续)\n> ";
    string confirm;
    getline(cin, confirm);
    if (confirm == "y" || confirm == "yes") {
        RemoveByID();
    }
}

void BookManager::RemoveByISBN() {
    string ISBN;
    cout << "请输入要删除的书籍ISBN号: ";
    cin >> ISBN;

    bool find = false;
    auto it = bookManager.begin();
    while (it != bookManager.end()) {
        if (it->GetISBN() == ISBN) {
            find = true;
            break;
        }
        ++it;
    }
    if (find) {
        cout << "书籍信息: " << endl
             << "ISBN: " << it->GetISBN() << "  书籍名称: " << it->GetName()
             << "  作者: " << it->GetAuthor()
             << "  出版社: " << it->GetPublisher()
             << "  出版年份: " << it->GetYear() << endl
             << "是否删除 (输入y/yes删除)\n> ";
        string confirm;
        cin.get();
        getline(cin, confirm);
        if (confirm == "y" || confirm == "yes") {
            while (it != bookManager.end()) {
                auto itAfter = ++it;
                --it;
                if (it->GetISBN() == ISBN) {
                    if (it->GetBorrowStatus()) {
                        cout << "书籍编号: " << it->GetId()
                             << " 已出借, 借阅人: " << it->GetBorrower()
                             << " , 是否删除 (输入y/yes删除)\n> ";
                        getline(cin, confirm);
                        if (confirm == "y" || confirm == "yes") {
                            bookManager.erase(it);
                        }
                    } else {
                        bookManager.erase(it);
                    }
                }
                it = itAfter;
            }
            cout << "已完成删除" << endl;
        } else {
            cout << "已取消删除" << endl;
        }
    } else {
        cout << "该ISBN号不存在" << endl;
        cin.get();
    }

    cout << "是否继续删除 (输入y/yes继续)\n> ";
    string confirm;
    getline(cin, confirm);
    if (confirm == "y" || confirm == "yes") {
        RemoveByISBN();
    }
}

void BookManager::Lend() {
    int id;
    string borrower;

    cout << "请输入要借出的书籍编号: ";
    cin >> id;
    auto it = bookManager.find(id);
    if (it != bookManager.end()) {
        if (it->GetBorrowStatus()) {
            cout << "该书籍已借出" << endl;
            cin.get();
        } else {
            cout << "请输入借阅人: ";
            cin >> borrower;
            cout << "请确认借阅信息 (输入y/yes确认): " << endl
                 << "书籍编号: " << id << "  ISBN: " << it->GetISBN()
                 << "  书籍名称: " << it->GetName()
                 << "  作者: " << it->GetAuthor()
                 << "  出版社: " << it->GetPublisher()
                 << "  出版年份: " << it->GetYear() << "  借阅人: " << borrower
                 << "\n> ";
            string confirm;
            cin.get();
            getline(cin, confirm);
            if (confirm == "y" || confirm == "yes") {
                it->SetBorrowStatus(true);
                it->SetBorrower(borrower);
                cout << "已成功借出" << endl;
            } else {
                cout << "已取消借出" << endl;
            }
        }
    } else {
        cout << "该书籍编号不存在" << endl;
        cin.get();
    }

    cout << "是否继续借出 (输入y/yes继续)\n> ";
    string confirm;
    getline(cin, confirm);
    if (confirm == "y" || confirm == "yes") {
        Lend();
    }
}

void BookManager::Return() {
    int id;
    cout << "请输入要归还的书籍编号: ";
    cin >> id;
    auto it = bookManager.find(id);
    if (it != bookManager.end()) {
        if (!it->GetBorrowStatus()) {
            cout << "该书籍未借出" << endl;
            cin.get();
        } else {
            cout << "请确认归还信息 (输入y/yes确认): " << endl
                 << "书籍编号: " << id << "  ISBN: " << it->GetISBN()
                 << "  书籍名称: " << it->GetName()
                 << "  作者: " << it->GetAuthor()
                 << "  出版社: " << it->GetPublisher()
                 << "  出版年份: " << it->GetYear()
                 << "  借阅人: " << it->GetBorrower() << "\n> ";
            string confirm;
            cin.get();
            getline(cin, confirm);
            if (confirm == "y" || confirm == "yes") {
                it->SetBorrowStatus(false);
                it->SetBorrower("");
                cout << "已成功归还" << endl;
            } else {
                cout << "已取消归还" << endl;
            }
        }
    } else {
        cout << "该书籍编号不存在" << endl;
        cin.get();
    }

    cout << "是否继续归还 (输入y/yes继续)\n> ";
    string confirm;
    getline(cin, confirm);
    if (confirm == "y" || confirm == "yes") {
        Return();
    }
}

void BookManager::FindAllLend() {
    BookManager LendBook;
    auto it = bookManager.begin();
    while (it != bookManager.end()) {
        if (it->GetBorrowStatus()) {
            LendBook.bookManager.insertUnique(LendBook.bookManager.end(), *it);
        }
        ++it;
    }
    if (LendBook.Empty()) {
        cout << "当前没有已借出的书籍" << endl;
        return;
    }
    LendBook.FindByPage(1, 20);
}

void BookManager::Save() {
    string filePath = "../data/book";
    string fileType = ".txt";

    ofstream out;
    out.open(filePath + ".temp", ios::app);
    if (!out.is_open()) {
        cout << "文件打开失败" << endl;
        return;
    }

    auto it = bookManager.begin();
    while (it != bookManager.end()) {
        out << *(it++) << endl;
    }

    out.close();
    std::remove((filePath + fileType).c_str());
    rename((filePath + ".temp").c_str(), (filePath + fileType).c_str());
}
