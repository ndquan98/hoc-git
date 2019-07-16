//#ifndef _ROOM_H_
//#define _ROOM_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//#include "User.h"

#define MAX_CONNECTION 4
/* - Trong Room chi chua user_name cua cac account, ko chua toan bo thong tin account. 
   - Viec set status mot user se do server quyet dinh, sau khi thuc hien func AddUserIntoRoom() hoac
     RemoveUserOutOfRoom() thi ngay lap tuc server phai set status cua user do
   - Thong tin Room dung cho ca server va client
   - Viec quan ly user_name, password, status nam trong class Account, hoac <listAcount> cuc ki quan trong*/
class Room{ 
    private:
        int id_;
        vector<string> room_member_;
        int CheckExist(string); //return -1 not exist, else return position in room_member_
    public:
        Room();
        Room(int,vector<string>);
        ~Room();
        bool IsFull();
        bool IsEmpty();
        int get_room_id() {return this->id_;}
        vector<string> get_room_member() {return this->room_member_;}
        bool AddUserIntoRoom(string);
        bool RemoveUserOutOfRoom(string);
        bool IsUserExist(string);
        void ListAllUser();
};

void ReadRoomFile(string file_name, vector<Room> &rl)
{
    ifstream file(file_name,ios::in);
    rl.clear();
    int number;
    int id, num;
    string tmp;
    file>>number;
    for(int i=0;i<number;i++)
    {
        file >> id >> num;
        vector<string> tmp_l;
        for(int j=0; j<num; j++)
        {
            file  >> tmp;
            tmp_l.push_back(tmp);
        }
        Room R(id,tmp_l);
        rl.push_back(R);
    }
    file.close();
}
void WriteRoomFile(string file_name, vector<Room> &rl)
{
    ofstream file(file_name, ios::out);
    file << rl.size() << endl;
    for(int i=0; i<rl.size(); i++)
    {
        file << rl[i].get_room_id() << " " << rl[i].get_room_member().size() << endl;
        for(int  j=0; j < rl[i].get_room_member().size(); j++)
        {
            file << rl[i].get_room_member().at(j);
            file << endl;
        }
    }
    rl.clear();
    file.close();
}