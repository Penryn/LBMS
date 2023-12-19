#include "user.h"

User::User() = default;
User::User(const string &name, const string &password)
    : name(name), password(password) {}

User::~User() = default;

const string &User::GetName() const { return name; }
void User::SetName(const string &name) { User::name = name; }

const string &User::GetPassword() const { return password; }
void User::SetPassword(const string &password) { User::password = password; }

istream &operator>>(istream &in, User &user) {
    in >> user.name >> user.password;
    return in;
}
ostream &operator<<(ostream &out, const User &user) {
    out << user.name << " " << user.password;
    return out;
}
