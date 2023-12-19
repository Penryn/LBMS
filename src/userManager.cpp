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

    cout << "��������Կ: ";
    cin >> secertKey;
    if (secertKey != "vivo50") {
        cout << "��Կ����" << endl;
        return false;
    }

    cout << "�������û���: ";
    cin >> name;
    if (userManager.find(name) != userManager.end()) {
        cout << "���û�����ע��" << endl;
        return false;
    }

    cout << "����������: ";
    cin >> password;
    cout << "��ȷ������: ";
    cin >> rePassword;
    if (password != rePassword) {
        cout << "���벻һ��" << endl;
        return false;
    }

    User user(name, password);
    userManager.insertUnique(userManager.end(), user);
    cout << "ע��ɹ�" << endl;
    return true;
}

bool UserManager::Login() {
    string name, password;
    cout << "�������û���: ";
    cin >> name;
    cout << "����������: ";
    cin >> password;

    auto it = userManager.find(name);
    if (it == userManager.end()) {
        cout << "�û������������" << endl;
        return false;
    }

    if ((*it).GetPassword() != password) {
        cout << "�û������������" << endl;
        return false;
    }

    cout << "��½�ɹ�" << endl;
    return true;
}

void UserManager::Save() {
    string filePath = "../data/user";
    string fileType = ".txt";

    ofstream out;
    out.open(filePath + ".temp", ios::app);
    if (!out.is_open()) {
        cout << "�ļ���ʧ��" << endl;
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