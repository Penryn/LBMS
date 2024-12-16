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

    // 初始化用户数据
    void Init();

    // 注册
    bool Register();

    // 登录
    bool Login();

    // 保存数据
    void Save();
};

#endif  // _INCLUDE_USERMANAGER_H_