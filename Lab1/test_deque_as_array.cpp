//
//  main.cpp
//  project1
//
//  Created by Cher Han on 16/1/24.
//  Copyright © 2016年 Cher Han. All rights reserved.
//

#include <iostream>
#include "Deque_as_array.h"
#include "Exception.h"

using namespace std;
int main(){
    std::cout<<"There are 10 test cases in total testing each functions in the .h file"<<std::endl;
    Deque_as_array Test1(5);
    //----------------------------------------
    std::cout<<"Test 0 : Clear an empty array";
    Test1.clear();
    try{
        
        Test1.head();
    }catch(underflow){
        std::cout<<" --- PASS"<<std::endl;}
    
    Test1.enqueue_head(1);
    Test1.enqueue_head(2);
    Test1.enqueue_tail(4);
    Test1.enqueue_tail(5);
    
    //----------------------------------------
    std::cout<<"Test 1 : head (2) and tail(4)";//<<std::endl;
    if(Test1.head() ==2 && Test1.tail() == 5){
        std::cout<<" --- PASS "<<std::endl;}
    
    //----------------------------------------
    std::cout<<"Test 2 : Enqueue a full array from head";
    try{
        Test1.enqueue_head(1);
    }catch(overflow){
        std::cout<<" --- PASS"<<std::endl;}
    //----------------------------------------
    std::cout<<"Test 3 : Enqueue a full array from tail";
    try{
        Test1.enqueue_tail(1);
    }catch(overflow){
        std::cout<<" --- PASS"<<std::endl;}
    //----------------------------------------
    std::cout<<"Test 4 : Clear an array";
    Test1.clear();
    if(Test1.size()==0){
        std::cout<<" --- PASS"<<std::endl;}
    //----------------------------------------
    std::cout<<"Test 5 : Dequeue an size 1 array";
    Test1.enqueue_tail(55);

    if(Test1.dequeue_tail()==55 && Test1.size()==0){
       std::cout<<" --- PASS"<<std::endl;}
    //----------------------------------------
    std::cout<<"Test 6 : Dequeue an array";
    Test1.enqueue_head(11);
    Test1.enqueue_head(22);
    Test1.enqueue_tail(44);
    Test1.enqueue_tail(54);
    if( Test1.dequeue_head()==22 && Test1.size() == 3){
        std::cout<<" --- PASS"<<std::endl;}
    //----------------------------------------
    std::cout<<"Test 7 : Capacity of the array";
    if(Test1.capacity()==5){
        std::cout<<" --- PASS"<<std::endl;}
    //----------------------------------------
    std::cout<<"Test 8 : size of the array";
    if(Test1.size()==3){
        std::cout<<" --- PASS"<<std::endl;}
    //----------------------------------------
    std::cout<<"Test 9 : Is array empty";
    if(!Test1.empty()){
        std::cout<<" --- PASS"<<std::endl;}
    
    return 0;
}
