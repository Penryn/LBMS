#include "bookManager.h"
#include "menu.h"
#include "userManager.h"

int main() {
    UserManager user;
    BookManager book;
    user.Init();
    book.Init();

    Menu::Start();
    int choice;
    while (cin >> choice && choice) {
        switch (choice) {
            case 1:
                if (!user.Login()) {
                    break;
                }

                Menu::Main();
                while (cin >> choice && choice) {
                    switch (choice) {
                        case 1: {
                            book.Insert();
                            break;
                        }
                        case 2: {
                            if (book.Empty()) {
                                cout << "��ǰ�鼮Ϊ��" << endl;
                                break;
                            }
                            Menu::Find();
                            while (cin >> choice && choice) {
                                switch (choice) {
                                    case 1: {
                                        book.FindByID();
                                        break;
                                    }
                                    case 2: {
                                        book.FindByISBN();
                                        break;
                                    }
                                    case 3: {
                                        book.FindByPage(1, 20);
                                        break;
                                    }
                                    default: {
                                        cout << "��������, ����������" << endl;
                                        break;
                                    }
                                }
                                Menu::Find();
                            }
                            break;
                        }
                        case 3: {
                            if (book.Empty()) {
                                cout << "��ǰ�鼮Ϊ��" << endl;
                                break;
                            }
                            Menu::Update();
                            while (cin >> choice && choice) {
                                switch (choice) {
                                    case 1: {
                                        book.UpdateByID();
                                        break;
                                    }
                                    case 2: {
                                        book.UpdateByISBN();
                                        break;
                                    }
                                    default: {
                                        cout << "��������, ����������" << endl;
                                        break;
                                    }
                                }
                                Menu::Update();
                            }
                            break;
                        }
                        case 4: {
                            if (book.Empty()) {
                                cout << "��ǰ�鼮Ϊ��" << endl;
                                break;
                            }
                            Menu::Remove();
                            while (cin >> choice && choice) {
                                switch (choice) {
                                    case 1: {
                                        book.RemoveByID();
                                        break;
                                    }
                                    case 2: {
                                        book.RemoveByISBN();
                                        break;
                                    }
                                    default: {
                                        cout << "��������, ����������" << endl;
                                        break;
                                    }
                                }
                                Menu::Remove();
                            }
                            break;
                        }
                        case 5: {
                            Menu::LendOrReturn();
                            while (cin >> choice && choice) {
                                switch (choice) {
                                    case 1: {
                                        book.Lend();
                                        break;
                                    }
                                    case 2: {
                                        book.Return();
                                        break;
                                    }
                                    case 3: {
                                        book.FindAllLend();
                                        break;
                                    }
                                    default: {
                                        cout << "��������, ����������" << endl;
                                        break;
                                    }
                                }
                                Menu::LendOrReturn();
                            }
                            break;
                        }
                        default: {
                            cout << "��������, ����������" << endl;
                            break;
                        }
                    }
                    Menu::Main();
                }
                break;
            case 2: {
                user.Register();
                break;
            }
            default: {
                cout << "��������, ����������" << endl;
                break;
            }
        }
        Menu::Start();
    }

    user.Save();
    book.Save();
    cout << "��ӭ�´�ʹ��" << endl;

    return 0;
}