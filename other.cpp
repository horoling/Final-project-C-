/**
 * @file other.cpp
 * @author Chen Zhaoyv
 * @brief   This code is about some insignificant functions like print the interface.
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
#include<cstdlib>
#include<windows.h>
using namespace std;
#include"head.h"


void W_interface(){
    cout<<"1:log in as visitor"<<endl;
    cout<<"2:creat an player account"<<endl;
    cout<<"3:log in an manager account"<<endl;
    cout<<"4:log in an player account."<<endl;
    cout<<"5:exit"<<endl;
}

void U_interface(){
    cout<<"1:play mineweeper."<<endl;
    cout<<"2:return last interface."<<endl;
    cout<<"3:sign up as a player."<<endl;
}

void M_interface(){
    cout<<"1:change user data."<<endl;
    cout<<"2:log out"<<endl;
    cout<<"3:modify the difficulty."<<endl;
    cout<<"4:change manager password."<<endl;
}

bool isNum(string str){
    stringstream sin(str);
    double d;
    char c;
    if (!(sin>>d))
    {
        return false;
    }
    return true;
}

void W_choose(int n){
    Player A;
    Manager B;
    switch (n)
    {
    case 1:
        Creat_user_account();
        break;
    case 2:
        A.Creat_player_accout();
        break;
    case 3:
        B.log_in();
        break;
    case 4:
        log_in();
        system("pause");
        break;
    case 5:
        exit(1);
        break;
    default:
        break;
    }
}

