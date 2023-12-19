#ifndef _INCLUDE_USER_H_
#define _INCLUDE_USER_H_

#include <iostream>
using namespace std;

class User {
private:
    string name;      // ÓÃ»§Ãû
    string password;  // ÃÜÂë

public:
    User();
    User(const string &name, const string &password);

    ~User();

    const string &GetName() const;
    void SetName(const string &name);

    const string &GetPassword() const;
    void SetPassword(const string &password);

    friend istream &operator>>(istream &in, User &user);
    friend ostream &operator<<(ostream &os, const User &user);
};

#endif  // _INCLUDE_USER_H_