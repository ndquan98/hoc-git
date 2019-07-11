//#ifndef _USER_H_
//#define _USER_H_
#include <string>
#include <vector>
#include <iostream>
#define MAX_USER 20
using namespace std;

class User
{
    private:
        string UserName;
        string Password;
        int    Status;
    public:
        User();
        User(string,string,int);
        ~User();
        string getUserName();
        string getPasswork();
        int    getUserStatus();
        bool Authenticate(const User&U);
};

class ListUser
{
    private:
        vector<User> List;
    public:
        ListUser();
        ~ListUser();
        //User getUser();
        bool IsFull();
        bool IsEmpty();
        bool AddUser(User);
        bool RemoveUser(User);
};