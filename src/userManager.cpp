#include "userManager.h"

#include <fstream>

UserManager::UserManager() = default;

UserManager::~UserManager() = default;

void UserManager::Init() {
    string file = "../data/user.txt";

    ifstream in;
    in.open(file, ios::in);
    if (!in.is_open()) {
        ofstream out;
        out.open(file, ios::out | ios::app);
        out.close();
        in.open(file, ios::in);
    }

    User user;
    while (in.peek() != EOF) {
        in >> user;
        userManager.insertUnique(userManager.end(), user);
    }

    in.close();
}

bool UserManager::Register() {
    string secertKey, name, password, rePassword;

    cout << "请输入密钥: ";
    cin >> secertKey;
    if (secertKey != "vivo50") {
        cout << "密钥错误" << endl;
        return false;
    }

    cout << "请输入用户名: ";
    cin >> name;
    if (userManager.find(name) != userManager.end()) {
        cout << "该用户名已注册" << endl;
        return false;
    }

    cout << "请输入密码: ";
    cin >> password;
    cout << "请确认密码: ";
    cin >> rePassword;
    if (password != rePassword) {
        cout << "密码不一致" << endl;
        return false;
    }

    User user(name, password);
    userManager.insertUnique(userManager.end(), user);
    cout << "注册成功" << endl;
    return true;
}

bool UserManager::Login() {
    string name, password;
    cout << "请输入用户名: ";
    cin >> name;
    cout << "请输入密码: ";
    cin >> password;

    auto it = userManager.find(name);
    if (it == userManager.end()) {
        cout << "用户名或密码错误" << endl;
        return false;
    }

    if ((*it).GetPassword() != password) {
        cout << "用户名或密码错误" << endl;
        return false;
    }

    cout << "登陆成功" << endl;
    return true;
}

void UserManager::Save() {
    string filePath = "../data/user";
    string fileType = ".txt";

    ofstream out;
    out.open(filePath + ".temp", ios::app);
    if (!out.is_open()) {
        cout << "文件打开失败" << endl;
        return;
    }

    auto it = userManager.begin();
    while (it != userManager.end()) {
        out << *(it++) << endl;
    }

    out.close();
    remove((filePath + fileType).c_str());
    rename((filePath + ".temp").c_str(), (filePath + fileType).c_str());
}