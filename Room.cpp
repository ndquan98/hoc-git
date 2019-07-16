#include "Room.h"
#include <iostream>

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
    if(CheckExist(X) >=0)
    {
        cout << "User existed in room, cannot join this room!";
        return false;
    }
    if(this->IsFull()==true)
    {
        cout << "Romm is full, cannot join this room!";
        return false;
    }
    this->room_member_.push_back(X);
    cout << "Add user successfully!";
    return true;
    
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
    int pos = CheckExist(X);
    if(this->IsEmpty())
    {
        cout << "Room is empty, nothing to remove!";
        return false;
    }
    
    if(pos==-1)
    {
        cout << "User doesnt exist, cannot remove!";
        return false;
    }
    this->room_member_.erase(room_member_.begin()+pos);
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
    for(auto i = 0; i<room_member_.size(); i++)
        cout << "\t " << room_member_.at(i) << endl;
}
int main()
{
    vector<Room> room_list;
    ReadRoomFile("room.txt",room_list);
    WriteRoomFile("room_out.txt",room_list);
    return 0;
}