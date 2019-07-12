#include "Room.h"

Room::Room() {};

Room::~Room() {};

Room::Room(int i,vector<string> v)
{
    this->id_=i;
    this->room_member_=v;
}
bool Room::IsFull()
{
    if (room_member_.size() >= MAX_CONNECTION)
        return true;
    else return false;
}
bool Room::IsEmpty()
{
    return (room_member_.empty());
}
bool Room::AddUserIntoRoom(string X)
{
    if(this->IsFull()==true)
    {
        cout << "Romm is full, cannot join this room!";
        exit(false);
    }
    if(CheckExist(X) >=0)
    {
        cout << "User existed in room, cannot join this room!";
        exit(false);
    }
    room_member_.push_back(X);
    cout << "Add user successfully!";
    exit(true);
}
int Room::CheckExist(string X) // return -1: doesn't exist, else return position
{
    int pos=room_member_.size();
    for(int i=0; i<room_member_.size(); i++)
    {
        if(room_member_[i] == X)
            {
                pos = i;
                break;
            }
    }
    if(pos==room_member_.size())
    {
        return -1;
    }
    else
    {
        return pos;
    }
}
bool Room::RemoveUserOutOfRoom(string X)
{
    if(IsEmpty())
    {
        cout << "Room is empty, nothing to remove!";
        return false;
    }
    int pos = CheckExist(X);
    if(pos==-1)
    {
        cout << "User doesnt exist, cannot remove!";
        return false;
    }
    room_member_.erase(room_member_.begin()+pos);
    cout << "Remove user successfully";
    return true;
}
bool Room::IsUserExist(string X)
{
    if(CheckExist(X)==-1)
    {
        cout << "User doesn't exist!";
        return false;
    }
    else
    {
        cout << "User existed in room id " << id_;
        return true;
    }
    
}
void Room::ListAllUser()
{
    for(auto i : this->room_member_)
        cout << (string*)&i << endl;
}
int main()
{
    ReadRoomFile("Room.txt",&room_list);
    if(room_list.empty()==true)
        cout << "Nothing to show?";
    for(auto i : room_list)
    {
        cout << i.get_room_id();
        i.ListAllUser();
    }
    return 0;
}