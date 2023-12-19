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

    cout << "������ISBN��: ";
    cin >> ISBN;
    cout << "�������鼮����: ";
    cin >> name;
    cout << "����������: ";
    cin >> author;
    cout << "�����������: ";
    cin >> publisher;
    cout << "������������: ";
    cin >> year;
    cout << "����������: ";
    cin >> count;

    cout << "��ȷ���鼮��Ϣ (����y/yesȷ��) : " << endl
         << "ISBN: " << ISBN << "  �鼮����: " << name << "  ����: " << author
         << "  ������: " << publisher << "  �������: " << year
         << "  ����: " << count << "\n> ";
    string confirm;
    cin.get();
    getline(cin, confirm);

    if (confirm == "y" || confirm == "yes") {
        while (count--) {
            bookManager.insertUnique(bookManager.end(),
                                     Book(bookManager.size() + 1, ISBN, name,
                                          author, publisher, year, false, ""));
        }
        cout << "�ѳɹ����" << endl;
    } else {
        cout << "��ȡ�����" << endl;
    }

    cout << "�Ƿ������� (����y/yes����)\n> ";
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
        cout << "����ҳ������, ���������� (�˳��鿴����0)\n> ";
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

    cout << "��ǰ�� " << currPage << " ҳ, �� " << totalPages
         << " ҳ, ��������תҳ (�˳��鿴����0)\n> ";
    if (cin >> currPage && currPage) {
        FindByPage(currPage, pageSize);
    }
}

void BookManager::FindByID() {
    int id;
    cout << "������Ҫ��ѯ���鼮���: ";
    cin >> id;

    auto it = bookManager.find(id);
    if (it != bookManager.end()) {
        cout << *it << endl;
    } else {
        cout << "���鼮��Ų�����" << endl;
    }

    cout << "�Ƿ������ѯ (����y/yes����)\n> ";
    string confirm;
    cin.get();
    getline(cin, confirm);
    if (confirm == "y" || confirm == "yes") {
        FindByID();
    }
}

void BookManager::FindByISBN() {
    string ISBN;
    cout << "������Ҫ��ѯ���鼮ISBN��: ";
    cin >> ISBN;

    bool find = false;
    int inCount = 0, outCount = 0;
    auto it = bookManager.begin();
    while (it != bookManager.end()) {
        if (it->GetISBN() == ISBN) {
            if (!find) {
                cout << "ISBN: " << it->GetISBN()
                     << "  �鼮����: " << it->GetName()
                     << "  ����: " << it->GetAuthor()
                     << "  ������: " << it->GetPublisher()
                     << "  �������: " << it->GetYear() << endl;
                find = true;
            }
            if (it->GetBorrowStatus()) {
                cout << "�鼮���: " << it->GetId()
                     << "  ������: " << it->GetBorrower() << endl;
                ++outCount;
            } else {
                ++inCount;
            }
        }
        ++it;
    }
    if (find) {
        cout << "�� " << inCount + outCount << " ��  ";
        if (outCount) {
            cout << "������: " << outCount << "��  ";
        }
        cout << "�ڿ���: " << inCount << "��" << endl;
    } else {
        cout << "��ISBN�Ų�����" << endl;
    }

    cout << "�Ƿ������ѯ (����y/yes����)\n> ";
    string confirm;
    cin.get();
    getline(cin, confirm);
    if (confirm == "y" || confirm == "yes") {
        FindByISBN();
    }
}

void BookManager::UpdateByID() {
    int id;
    cout << "������Ҫ���µ��鼮���: ";
    cin >> id;

    auto it = bookManager.find(id);
    if (it != bookManager.end()) {
        cout << "ԭ�鼮��Ϣ: " << endl
             << "ISBN: " << it->GetISBN() << "  �鼮����: " << it->GetName()
             << "  ����: " << it->GetAuthor()
             << "  ������: " << it->GetPublisher()
             << "  �������: " << it->GetYear() << endl
             << "�Ƿ���� (����y/yes����)\n> ";
        string confirm;
        cin.get();
        getline(cin, confirm);
        if (confirm == "y" || confirm == "yes") {
            string updateISBN, updateName, updateAuthor, updatePublisher;
            int updateYear;

            cout << "��������º��ISBN�� (����������0): ";
            cin >> updateISBN;
            if (updateISBN == "0") {
                updateISBN = it->GetISBN();
            }
            cout << "��������º���鼮���� (����������0): ";
            cin >> updateName;
            if (updateName == "0") {
                updateName = it->GetName();
            }
            cout << "��������º������ (����������0): ";
            cin >> updateAuthor;
            if (updateAuthor == "0") {
                updateAuthor = it->GetAuthor();
            }
            cout << "��������º�ĳ����� (����������0): ";
            cin >> updatePublisher;
            if (updatePublisher == "0") {
                updatePublisher = it->GetPublisher();
            }
            cout << "��������º�ĳ������ (����������0): ";
            cin >> updateYear;
            if (updateYear == 0) {
                updateYear = it->GetYear();
            }

            cout << "��ȷ�ϸ��º���鼮��Ϣ (����y/yesȷ��) : " << endl
                 << "ISBN: " << updateISBN << "  �鼮����: " << updateName
                 << "  ����: " << updateAuthor
                 << "  ������: " << updatePublisher
                 << "  �������: " << updateYear << "\n> ";
            cin.get();
            getline(cin, confirm);
            if (confirm == "y" || confirm == "yes") {
                it->SetISBN(updateISBN);
                it->SetName(updateName);
                it->SetAuthor(updateAuthor);
                it->SetPublisher(updatePublisher);
                it->SetYear(updateYear);
                cout << "�ѳɹ�����" << endl;
            } else {
                cout << "��ȡ������" << endl;
            }
        } else {
            cout << "��ȡ������" << endl;
        }
    } else {
        cout << "���鼮��Ų�����" << endl;
        cin.get();
    }

    cout << "�Ƿ�������� (����y/yes����)\n> ";
    string confirm;
    getline(cin, confirm);
    if (confirm == "y" || confirm == "yes") {
        UpdateByID();
    }
}

void BookManager::UpdateByISBN() {
    string ISBN;
    cout << "������Ҫ���µ��鼮ISBN��: ";
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
        cout << "ԭ�鼮��Ϣ: " << endl
             << "ISBN: " << it->GetISBN() << "  �鼮����: " << it->GetName()
             << "  ����: " << it->GetAuthor()
             << "  ������: " << it->GetPublisher()
             << "  �������: " << it->GetYear() << endl
             << "�Ƿ���� (����y/yes����)\n> ";
        string confirm;
        cin.get();
        getline(cin, confirm);
        if (confirm == "y" || confirm == "yes") {
            string updateISBN, updateName, updateAuthor, updatePublisher;
            int updateYear;

            cout << "��������º��ISBN�� (����������0): ";
            cin >> updateISBN;
            if (updateISBN == "0") {
                updateISBN = it->GetISBN();
            }
            cout << "��������º���鼮���� (����������0): ";
            cin >> updateName;
            if (updateName == "0") {
                updateName = it->GetName();
            }
            cout << "��������º������ (����������0): ";
            cin >> updateAuthor;
            if (updateAuthor == "0") {
                updateAuthor = it->GetAuthor();
            }
            cout << "��������º�ĳ����� (����������0): ";
            cin >> updatePublisher;
            if (updatePublisher == "0") {
                updatePublisher = it->GetPublisher();
            }
            cout << "��������º�ĳ������ (����������0): ";
            cin >> updateYear;
            if (updateYear == 0) {
                updateYear = it->GetYear();
            }

            cout << "��ȷ�ϸ��º���鼮��Ϣ (����y/yesȷ��) : " << endl
                 << "ISBN: " << updateISBN << "  �鼮����: " << updateName
                 << "  ����: " << updateAuthor
                 << "  ������: " << updatePublisher
                 << "  �������: " << updateYear << "\n> ";
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
                cout << "�ѳɹ�����" << endl;
            } else {
                cout << "��ȡ������" << endl;
            }
        } else {
            cout << "��ȡ������" << endl;
        }
    } else {
        cout << "��ISBN�Ų�����" << endl;
        cin.get();
    }

    cout << "�Ƿ�������� (����y/yes����)\n> ";
    string confirm;
    getline(cin, confirm);
    if (confirm == "y" || confirm == "yes") {
        UpdateByISBN();
    }
}

void BookManager::RemoveByID() {
    int id;
    cout << "������Ҫɾ�����鼮���: ";
    cin >> id;

    auto it = bookManager.find(id);
    if (it != bookManager.end()) {
        cout << "�鼮��Ϣ: " << endl
             << *it << endl
             << "�Ƿ�ɾ�� (����y/yesɾ��)\n> ";
        string confirm;
        cin.get();
        getline(cin, confirm);
        if (confirm == "y" || confirm == "yes") {
            if (it->GetBorrowStatus()) {
                cout << "���鼮�ѳ���, ������: " << it->GetBorrower()
                     << " , �Ƿ�ȷ��ɾ�� (����y/yesȷ��)\n> ";
                getline(cin, confirm);
                if (confirm == "y" || confirm == "yes") {
                    bookManager.erase(it);
                    cout << "�ѳɹ�ɾ��" << endl;
                } else {
                    cout << "��ȡ��ɾ��" << endl;
                }
            } else {
                bookManager.erase(it);
                cout << "�ѳɹ�ɾ��" << endl;
            }
        } else {
            cout << "��ȡ��ɾ��" << endl;
        }
    } else {
        cout << "���鼮��Ų�����" << endl;
        cin.get();
    }

    cout << "�Ƿ����ɾ�� (����y/yes����)\n> ";
    string confirm;
    getline(cin, confirm);
    if (confirm == "y" || confirm == "yes") {
        RemoveByID();
    }
}

void BookManager::RemoveByISBN() {
    string ISBN;
    cout << "������Ҫɾ�����鼮ISBN��: ";
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
        cout << "�鼮��Ϣ: " << endl
             << "ISBN: " << it->GetISBN() << "  �鼮����: " << it->GetName()
             << "  ����: " << it->GetAuthor()
             << "  ������: " << it->GetPublisher()
             << "  �������: " << it->GetYear() << endl
             << "�Ƿ�ɾ�� (����y/yesɾ��)\n> ";
        string confirm;
        cin.get();
        getline(cin, confirm);
        if (confirm == "y" || confirm == "yes") {
            while (it != bookManager.end()) {
                auto itAfter = ++it;
                --it;
                if (it->GetISBN() == ISBN) {
                    if (it->GetBorrowStatus()) {
                        cout << "�鼮���: " << it->GetId()
                             << " �ѳ���, ������: " << it->GetBorrower()
                             << " , �Ƿ�ɾ�� (����y/yesɾ��)\n> ";
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
            cout << "�����ɾ��" << endl;
        } else {
            cout << "��ȡ��ɾ��" << endl;
        }
    } else {
        cout << "��ISBN�Ų�����" << endl;
        cin.get();
    }

    cout << "�Ƿ����ɾ�� (����y/yes����)\n> ";
    string confirm;
    getline(cin, confirm);
    if (confirm == "y" || confirm == "yes") {
        RemoveByISBN();
    }
}

void BookManager::Lend() {
    int id;
    string borrower;

    cout << "������Ҫ������鼮���: ";
    cin >> id;
    auto it = bookManager.find(id);
    if (it != bookManager.end()) {
        if (it->GetBorrowStatus()) {
            cout << "���鼮�ѽ��" << endl;
            cin.get();
        } else {
            cout << "�����������: ";
            cin >> borrower;
            cout << "��ȷ�Ͻ�����Ϣ (����y/yesȷ��): " << endl
                 << "�鼮���: " << id << "  ISBN: " << it->GetISBN()
                 << "  �鼮����: " << it->GetName()
                 << "  ����: " << it->GetAuthor()
                 << "  ������: " << it->GetPublisher()
                 << "  �������: " << it->GetYear() << "  ������: " << borrower
                 << "\n> ";
            string confirm;
            cin.get();
            getline(cin, confirm);
            if (confirm == "y" || confirm == "yes") {
                it->SetBorrowStatus(true);
                it->SetBorrower(borrower);
                cout << "�ѳɹ����" << endl;
            } else {
                cout << "��ȡ�����" << endl;
            }
        }
    } else {
        cout << "���鼮��Ų�����" << endl;
        cin.get();
    }

    cout << "�Ƿ������� (����y/yes����)\n> ";
    string confirm;
    getline(cin, confirm);
    if (confirm == "y" || confirm == "yes") {
        Lend();
    }
}

void BookManager::Return() {
    int id;
    cout << "������Ҫ�黹���鼮���: ";
    cin >> id;
    auto it = bookManager.find(id);
    if (it != bookManager.end()) {
        if (!it->GetBorrowStatus()) {
            cout << "���鼮δ���" << endl;
            cin.get();
        } else {
            cout << "��ȷ�Ϲ黹��Ϣ (����y/yesȷ��): " << endl
                 << "�鼮���: " << id << "  ISBN: " << it->GetISBN()
                 << "  �鼮����: " << it->GetName()
                 << "  ����: " << it->GetAuthor()
                 << "  ������: " << it->GetPublisher()
                 << "  �������: " << it->GetYear()
                 << "  ������: " << it->GetBorrower() << "\n> ";
            string confirm;
            cin.get();
            getline(cin, confirm);
            if (confirm == "y" || confirm == "yes") {
                it->SetBorrowStatus(false);
                it->SetBorrower("");
                cout << "�ѳɹ��黹" << endl;
            } else {
                cout << "��ȡ���黹" << endl;
            }
        }
    } else {
        cout << "���鼮��Ų�����" << endl;
        cin.get();
    }

    cout << "�Ƿ�����黹 (����y/yes����)\n> ";
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
        cout << "��ǰû���ѽ�����鼮" << endl;
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
        cout << "�ļ���ʧ��" << endl;
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
