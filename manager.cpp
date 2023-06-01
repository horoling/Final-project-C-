/**
 * @file manager.cpp
 * @author Chen Zhaoyv
 * @brief  This code is the definition of the functions about manager.
 *         The initial password is 0000
 * @version 0.1
 * @date 2023-05-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
//commentator: 

#include<iostream>
#include<fstream>
#include<cstring>
#include<sstream>
#include<string>
using namespace std;
#include"head.h"

Manager::Manager(){
    name = "";
    password = 000;
}

void Manager::m_interface(){
    cout<<"1:delete player"<<endl;
    cout<<"2:reset player's password."<<endl;
    cout<<"3:return."<<endl;
}

bool Manager::record(){
    ofstream Fout;
    Fout.open("E:\\manager.txt",ios::out|ios::app);
    Fout<<name<<endl;
    Fout<<password<<endl;
    Fout.close();
    return true;
}

bool Manager::log_in(){
    ofstream Fout;
    ifstream Fin;
    string s;
    string pa;
    int n;
    Fin.open("E:/manager.txt",ios::in|ios::app);

    if (!Fin.is_open()) {
        cout << "error" << endl;
        return 0;
    }

    if (!getline(Fin,s))
    {
        Fin.close();
        Fout.open("E:/manager.txt",ios::out);
        Fout<<"0000"<<endl;   
        Fout.close();  
    }
    cout<<"password:"<<endl;
    cin>>pa;
    if (pa == s)
    {
        cout<<"log in successfully."<<endl;
        M_interface();
        cin>>n;
        M_choose(n);
    }   
    else log_in();
    return true;
}


string Manager::change_password(){
    string str1,str2;
    int j; 
	cout<<"input new password"<<endl;
	cin>>str1; 
	cout<<"input new password again"<<endl;
	cin>>str2;
    if (str1 == str2)
    {
        ofstream Fout;
        Fout.open(Filename,ios::out);
        Fout.flush();
        Fout<<str2<<endl;
    }
    else change_password();
    return str2;
}

void Manager::manage(){
    m_interface();
    Player A;
    string s;
    int n;
    cin>>n;
    if (n == 2)
    {
        cin>>s;
        Player A(s,000);
    }
    
    switch (n)
    {
    case 1:
        del_p();
        break;
    case 2:
        A.change_password();
        
    default:
        break;
    }
}

bool Manager::del_p(){
    string s;
    fstream Fin;
    ofstream Fout;
    int i = 0;
    int p;
    int q;
    cin>>s;
    Fin.open(Filename,ios::in);
    if (!Fin.is_open())
    {
        cout<<"error"<<endl;
        return 0;
    }
    
    p = Find_player(s);
    q = Find_next(s);
    string temp;
    string line;
    while (getline(Fin,line))
    {
        i++;
        if (i<p || i>q)
        {
            temp += line;
            temp += '\n';
        }
    }
    Fin.close();
    Fout.open(Filename,ios::out);
    Fout.flush();
    Fout<<temp;
    Fout.close();
    return true;    

}

int Manager::modify_dif(){
    cout<<"1.Beginner\n2.Intermediate\n3.Expert\n4.Custom"<<endl;
    int d;
    cin>>d;
    Dif = d;
    return Dif;
}

int Manager::M_choose(int n){

    int i;
    switch (n)
    {
    case 1:
        manage();
        break;
    case 2:
        break;
    case 3:
        modify_dif();
        break;
    case 4:
        change_password();
        break;
    default:
        break;
    }
    return i;
}
