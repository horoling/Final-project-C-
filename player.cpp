/**
 * @file player.cpp
 * @author Chen Zhaoyv
 * @brief This code is the definition of the functions about player
 * @version 0.1
 * @date 2023-05-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include<iostream>
#include<fstream>
#include<cstring>
#include<sstream>
#include<string>
using namespace std;
#include"head.h"

Player::Player(){
    name = "";
    password = 000;
}

bool Player::record(){
    ofstream Fout;
    Fout.open("E:\\player.txt",ios::out|ios::app);
    Fout<<name<<endl;
    Fout<<password<<endl;
    Fout.close();
    return true;
}

void Player::P_interface(){
    cout<<"1:play minesweeper!"<<endl;
    cout<<"2:log out"<<endl;
    cout<<"3:View score learderboard."<<endl;
    cout<<"4:change password."<<endl;
}

bool Player::Creat_player_accout(){
    
    cin.sync();

    string n;
    int id;

    cout<<"name"<<endl;
    getline(cin,n);
    if (Find_player(n))
    {
        cout<<"This name had been occupied."<<endl;
        return false;
    }
    
    cout<<"password"<<endl;
    cin>>id;
    
    Player A(n,id);
    return A.record();
}


bool check_password(string name){
    int i;
    string password;
    string in;
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
            cout<<"password:";
            cin>>in;
            getline(Fin,password);
            if (password.compare(in) == 0)
            {
            Fin.close();
            return i;
            }
        }
    }
    Fin.close();
    return 0;
}

string Player::change_password(){
	string str1,str2;
    int j; 
    int i = Find_player(name);
	cout<<"input new password"<<endl;
	cin>>str1; 
	cout<<"input new password again"<<endl;
	cin>>str2;
	char str[7] = " ";
	for(j=0;j<str2.length();++j){
		str[j]=str2[j];
	}
	str[j]='\0';
	if(str1==str2) {
			Modify_password(i+1,str);
			cout<<"had changed"<<endl;	
		}
	else{
		cout<<"incorrect"<<endl;
	}
    return str2;
}

void Modify_password(int lineNum,char* content)//修改文件 
{	ifstream Fin;	
	char line[1024]={'\0'};	
	Fin.open(Filename,ios::in);	
	int i=0;	
	string temp;	
	while(Fin.getline(line,sizeof(line)))	
	{		
	i++;		
	if(lineNum!=i)		
	{			
	temp+=charToStr(line);		
	}		
	else		
	{	       
	temp+=content;		
	}		
	temp+='\n';	
	}	
	Fin.close();	
	ofstream out;	
	out.open(Filename,ios::out);	
	out.flush();	
	out<<temp;	
	out.close();  
}

string charToStr(char *contentChar)
{
	
	string tempStr;
    tempStr = contentChar;
	return tempStr;
}

bool Player::grade(int g){
    ifstream Fin;
    int i;
    int lineNum = 0;
    if (g)
    {
            Fin.open(Filename,ios::in);
    i = Find_player(name);
	char line[1024]={'\0'};	

	string temp;	
	while(Fin.getline(line,sizeof(line)))	
	{	
	temp+=charToStr(line);			
	lineNum++;		
	if(lineNum==(i + 2))		
	{
	temp+="\n*";			
	temp+= to_string(g);			
	}
	temp+='\n';	
	}	
	Fin.close();	
	ofstream out;	
	out.open(Filename,ios::out);	
	out.flush();	
	out<<temp;	
	out.close();  
    }
    
    return true;
}

bool log_in(){
    string n;
    int s;
    int g;
    cout<<"name"<<endl;
    cin>>n;
    Player A(n,000);
    if (A.Find_player(n))
    {
        check_password(n);
        A.P_interface();
        cin>>s;
        switch (s)
        {
        case 1:
            A.grade(mine());
            break;
        case 2:
            break;
        case 3:
            A.check_highest_grade();
            break;
        case 4:
            A.change_password();
            break;
        default:
            break;
        }
    }
    else{
        cout<<"You hadn't sign up!"<<endl;
    } 
    return false;
}