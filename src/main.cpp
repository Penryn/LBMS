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
                                cout << "当前书籍为空" << endl;
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
                                        cout << "输入有误, 请重新输入" << endl;
                                        break;
                                    }
                                }
                                Menu::Find();
                            }
                            break;
                        }
                        case 3: {
                            if (book.Empty()) {
                                cout << "当前书籍为空" << endl;
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
                                        cout << "输入有误, 请重新输入" << endl;
                                        break;
                                    }
                                }
                                Menu::Update();
                            }
                            break;
                        }
                        case 4: {
                            if (book.Empty()) {
                                cout << "当前书籍为空" << endl;
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
                                        cout << "输入有误, 请重新输入" << endl;
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
                                        cout << "输入有误, 请重新输入" << endl;
                                        break;
                                    }
                                }
                                Menu::LendOrReturn();
                            }
                            break;
                        }
                        default: {
                            cout << "输入有误, 请重新输入" << endl;
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
                cout << "输入有误, 请重新输入" << endl;
                break;
            }
        }
        Menu::Start();
    }

    user.Save();
    book.Save();
    cout << "欢迎下次使用" << endl;

    return 0;
}