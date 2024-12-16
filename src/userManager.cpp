#include "userManager.h"

#include <fstream>
#include <sstream>

UserManager::UserManager() = default;

UserManager::~UserManager() = default;

void UserManager::Init() {
    string file = "../data/user.csv";

    ifstream in(file);
    if (!in.is_open()) {
        ofstream out(file);
        out.close();
        in.open(file);
    }

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string name, password;

        getline(ss, name, ',');
        getline(ss, password, ',');

        User user(name, password);
        userManager.insertUnique(userManager.end(), user);
    }

    in.close();
}

bool UserManager::Register() {
    string secertKey,fileSecretKey, name, password, rePassword;

    // 从文件中读取密钥
    string filePath = "../data/key.txt";
    ifstream inFile(filePath);
    if (!inFile.is_open()) {
        cout << "无法打开密钥文件" << endl;
        return false;
    }
    getline(inFile, fileSecretKey);
    inFile.close();

    cout << "请输入密钥: ";
    cin >> secertKey;
    if (secertKey != fileSecretKey) {
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
    const string filePath = "../data/user.csv";

    ofstream out(filePath, ios::trunc);
    if (!out.is_open()) {
        cout << "文件打开失败" << endl;
        return;
    }

    for (const auto& user : userManager) {
        out << user.GetName() << "," << user.GetPassword() << endl;
    }

    out.close();
}