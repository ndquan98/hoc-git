#include "User.h"

User::User()
{
    UserName = "";
    Password = "";
    Status = 0;
}
User::User(string Name, string Password, int S)
{
    UserName=Name;
    Password=Password;
    Status = S;
}
User::~User(){}
string User::getUserName() {return this->UserName;}
string User::getPasswork() {return this->Password;}
bool User::Authenticate(const User &U)
{
    string N=U.UserName;
    string P=U.Password;
    if ((N==this->getUserName()) && (P==this->getPasswork()))
        return true;
    return false;
}
int User::getUserStatus() {return Status;}
/*--------------------------------- */
ListUser::ListUser() {};
ListUser::~ListUser() {};

bool ListUser::IsFull()
{
    if(List.size() >= MAX_USER)
        return true;
    return false;
}
bool ListUser::IsEmpty()
{
    if (List.empty() == true)
        return true;
    return false;
}
bool ListUser::AddUser(User U)
{
    if(IsFull()==true)
    {
        cout << "List User is full, cannot Add <" << U.getUserName() << ">!\n";
        return false;
    }
    string N=U.getUserName();
    for(int i=0; i<List.size(); i++)
        if (List[i].getUserName() == N)
        {
            cout << "Duplicate User Name, cannot Add!\n";
            return false;
        }
    List.push_back(U);
    cout << "Add User <" <<U.getUserName()<<"> succesfully!\n";
    return true;
}
bool ListUser::RemoveUser(User U)
{
    if(IsEmpty()==true)
    {
        cout << "List User is empty, nothing to remove!\n";
        return false;
    }
    string N=U.getUserName();
    int pos=List.size();
    for(int i=0; i<=List.size()-1; i++)
    {  
        if (List[i].getUserName() == N)
        {
            pos=i;
            break;
        }
            
    }
    if(pos==List.size())
        {
            cout << "User not found, cannnot remove!\n";
            return false;
        }
   // cout << "pos " << pos << endl;
    //cout << "size before: " << List.size() << endl;
    List.erase(List.begin()+pos);
    cout << "Remove User successfully!\n";
    //cout <<"size after: " << List.size() << endl;
    return true;
}
/*------------------------------------------ */
int main()
{
    User A("Quan","1233",0);
    User B("Quang","rtg",1);
    User C("Hoang","fff",1);
    User D("Quan","555",1);
    ListUser L;
    L.AddUser(A);
    L.AddUser(B);
    L.AddUser(C);
    L.AddUser(D);
    L.RemoveUser(A);
    L.RemoveUser(A);
    L.RemoveUser(B);
    //L.RemoveUser(C);
    L.RemoveUser(B);
    L.RemoveUser(C);
    L.RemoveUser(A);
    return 0;
}