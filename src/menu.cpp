#include "menu.h"

#include <iostream>
using namespace std;

void Menu::Start() {
    cout << "----------------------------------------------------------------"
         << endl
         << "欢迎使用图书馆书籍管理系统" << endl
         << "1: 登录" << endl
         << "2: 注册" << endl
         << "0: 退出" << endl
         << "> ";
}

void Menu::Main() {
    cout << "----------------------------------------------------------------"
         << endl
         << "请输入对应功能前的编号进行操作" << endl
         << "1: 添加书籍" << endl
         << "2: 查询书籍" << endl
         << "3: 修改书籍" << endl
         << "4: 删除书籍" << endl
         << "5: 借阅管理" << endl
         << "0: 退出登录" << endl
         << "> ";
}

void Menu::Find() {
    cout << "----------------------------------------------------------------"
         << endl
         << "请输入对应功能前的编号进行操作" << endl
         << "1: 根据书籍编号进行查询" << endl
         << "2: 根据ISBN号进行查询" << endl
         << "3: 查看所有书籍" << endl
         << "0: 返回上级菜单" << endl
         << "> ";
}

void Menu::Update() {
    cout << "----------------------------------------------------------------"
         << endl
         << "请输入对应功能前的编号进行操作" << endl
         << "1: 根据书籍编号进行修改" << endl
         << "2: 根据ISBN号进行修改" << endl
         << "0: 返回上级菜单" << endl
         << "> ";
}

void Menu::Remove() {
    cout << "----------------------------------------------------------------"
         << endl
         << "请输入对应功能前的编号进行操作" << endl
         << "1: 根据书籍编号进行删除" << endl
         << "2: 根据ISBN号进行删除" << endl
         << "0: 返回上级菜单" << endl
         << "> ";
}

void Menu::LendOrReturn() {
    cout << "----------------------------------------------------------------"
         << endl
         << "请输入对应功能前的编号进行操作" << endl
         << "1: 借出" << endl
         << "2: 归还" << endl
         << "3: 查看所有已借出书籍" << endl
         << "0: 返回上级菜单" << endl
         << "> ";
}