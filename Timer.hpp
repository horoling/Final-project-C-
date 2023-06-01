/**
 * @file Timer.hpp
 * @author Chen Zhaoyv
 * @brief   This is a template class for the Timer,it can record the time and show it.
 *          During this code I use template in order to dicide the precision of the return time, 
 *          and use template operator overloading to print it.
 * @version 0.1
 * @date 2023-05-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
//commentator: 

#pragma once
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;
 

template<class T1, class T2 = void>
class Timer
{
public:
	Timer();
	T2 restart();	    //start again
	T1 elapsed() const; //the episode
	T2 sleep(T1 ms);  //waiting
protected:
private:
	clock_t start_time;
};

template<class T1,class T2>
T2 operator<<(ostream &cout,Timer<T1,T2> &A);

template<class T1, class T2>
Timer<T1,T2>::Timer(){
    start_time = clock();
}

template<class T1,class T2>
T2 Timer<T1,T2>::restart(){
    start_time = clock();
}

template<class T1,class T2>
T1 Timer<T1,T2>::elapsed() const{
    return T1(clock() - start_time)/CLOCKS_PER_SEC;
}


template<class T1,class T2>
T2 Timer<T1,T2>::sleep(T1 ms){
    while (1)
    {
        if (elapsed() == ms/1000)
        {
            break;
        }
    }  
}

template<class T1,class T2>
T2 operator<<(ostream &cout, Timer<T1,T2> &A){
    T1 s1 = A.elapsed();
    int s2 = s1;
    int h = 0;
    int m = 0;
    while(s2>60)
    {
        s2 = s2 - 60;
        m += 1;
    }
    while (m>60)
    {
        m -= 60;
        h += 1;
    }
    cout<<'0'<<h<<" : "<< m<<" : "<<s2;
}
