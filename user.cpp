/**
 * @file user.cpp
 * @author Chen Zhaoyv
 * @brief This code is the definition of the functions about user
 * @version 0.1
 * @date 2023-05-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
//commentator: 

#include<iostream>
#include<sstream>
#include<fstream>
#include<cstring>
#include<string>
using namespace std;
#include"head.h"

User::User(){
    name = "";
}

User::User(string n){
    name.assign(n);
}

int User::check_highest_grade(){
    ifstream Fin;
    string grade;
    int low = 0;
    int fial = 0;

    Fin.open("E:/player.txt",ios::in);

    if (!Fin.is_open()) {
        cout << "error" << endl;
        return 0;
    }

    while (getline(Fin,grade))
    {
        if (grade[0] == '*')
        {
            grade[0] = '0';
            low = stoi(grade);
            if (fial < low)
            {
                fial = low;
            }
        }
    }
    cout<<"The highest grade is "<<fial<<endl;
    return fial;
}


bool User::record(){
    int n;
    cout<<"password:"<<endl;
    cin>>n;
    Player A(name,n);
    A.record();
    return true;
}

int User::Find_player(string name){
    int i;
    ifstream Fin;
    string temp;
    Fin.open("E:\\player.txt",ios::in|ios::app);

    if (!Fin.is_open()) {
        cout << "error" << endl;
        return 0;
    }

    while (getline(Fin,temp))
    {
        i++;//计算用户名位置
        if (temp == name)
        {
                Fin.close();
            return i;
        }
    }
    Fin.close();
    return 0;
}


int User::Find_next(string name){
    int i;
    ifstream Fin;
    string temp;
    Fin.open("E:\\player.txt",ios::in|ios::app);

    if (!Fin.is_open()) {
        cout << "error" << endl;
        return 0;
    }

    while (getline(Fin,temp))
    {
        i++;//计算用户名位置
        if (temp == name)
        {
            getline(Fin,temp);
        while (isNum(temp) || temp[0] == '*')
        {
            getline(Fin,temp);
            i++;
        }
            Fin.close();
            return i;
        }
    }
    Fin.close();
    return 0;
}



bool Creat_user_account(){
    string n;
    int i,j;
    cout<<"name"<<endl;
    cin>>n;
    cout<<"Hello! "<<n<<endl;

    User A(n);

    U_interface();
    cin>>i;
    j = U_choose(i);
    if(j == 1){
        A.record();
    }
    else if (j == 2)
    {
        A.check_highest_grade();
    }
    
    return true;
}

int U_choose(int i){
    int n;
    switch (i)
    {
    case 1:
        mine();
        break;
    case 2:
        break;
    case 3:
        n = 2;
    case 4:
        n = 1;
        break;
    default:
        break;
    }
    return n;
}
