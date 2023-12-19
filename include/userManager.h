#ifndef _INCLUDE_USERMANAGER_H_
#define _INCLUDE_USERMANAGER_H_

#include "rbTree.h"
#include "user.h"

class UserManager {
private:
    struct NameOfUser {
        const string& operator()(const User& u) const { return u.GetName(); }
    };
    typedef RbTree<string, User, NameOfUser, std::less<>> RbTree;

    RbTree userManager;

public:
    UserManager();

    ~UserManager();

    // ��ʼ���û�����
    void Init();

    // ע��
    bool Register();

    // ��¼
    bool Login();

    // ��������
    void Save();
};

#endif  // _INCLUDE_USERMANAGER_H_