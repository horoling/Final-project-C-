/**
 * @file head.h
 * @author Chen Zhaoyv
 * @brief   This is about all the declaration in the project.
 *          Including class User, Manager, Player and their functions, and some interface functions.
 * @version 0.1
 * @date 2023-05-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
//commentator: 

#ifndef _HEAD_H_
#define _HEAD_H_



#include<iostream>
using namespace std;
#define Filename "E:/player.txt"
extern int Dif;
 

class User
{
public:
    string name;
public:
    User();
    User(string name);
    virtual bool record();
    int Find_player(string name);
    int Find_next(string name);
    virtual int check_highest_grade();
};

class Player: public User
{
private:
    int password;
public:
    Player();
    Player(string n, int pa):User(n){
        password = pa;
    }
    void P_interface();
    virtual bool record();
    bool grade(int g);
    string change_password();
    bool Creat_player_accout();

};

class Manager: public User
{
private:
    int password;
public:
    Manager();
    Manager(string n, int pa):User(name){
        name = n;
        password = pa;
    }
    string change_password();
    virtual bool record();
    bool log_in();
    int M_choose(int n);
    void m_interface();
    void manage();
    bool del_p();
    int modify_dif();
};





void W_interface();
void U_interface();
void M_interface();
void W_choose(int n);
int U_choose(int n);

bool Creat_user_account();
bool log_in();
bool check_password(string name);
void Modify_password(int lineNum,char *content);
string charToStr(char *contentChar);
bool isNum(string str);

int mine();




#endif 