#ifndef DEQUE_AS_ARRAY_H
#define DEQUE_AS_ARRAY_H

/******************************************
 * Name: Shiyun Han
 * UW User ID:  s45han
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 ******************************************/

#include "Exception.h"

//My idea for storing items into the array is that: ihead points to the begining of the array, and
//itail points to the next available space. Thus, when the array is not empty, there is always values
//in ihead and nothing should be stored in itail. This also means that the array should never be full
//If the capacity of the array is n, then the maximum number of entries is n-1. Otherwise, method
//should return overflow.
class Deque_as_array {
//delarations of needed variables
private:
    int array_size;
    int*array;
    int ihead;
    int itail;
    int count;
    
public:
    Deque_as_array( int = 10 );
    ~Deque_as_array();
    

    int head() const;
    int tail() const;
    int size() const;
    bool empty() const;
    int capacity() const;
    int operator[]( int n ) const;
    void enqueue_head( int const & );
    void enqueue_tail( int const & );
    int dequeue_head();
    int dequeue_tail();
    void clear();
    
    
};

//This method overload the operator[], and it is used for testing
//such that user can just use[] to access the value of array.
//the intake parameter n is called from main, and it represents index that user want to see
//This method returns the value of specified index
int Deque_as_array::operator[]( int n ) const {
    return array[n];
}

//This method is used to initiate an array, with the parameters meaing the size of the array
//if the size is not declared or smaller than 1, its default will be 1. otherwise, the array
//will be the size of the intake n. count is set to 0 representing stored number in the array
//Since the array is just created, there is nothing in the array, count should be 0
Deque_as_array::Deque_as_array( int n ):
array_size( std::max( 1, n ) ),
array( new int[array_size] ),
count( 0 ) {
    // empty
}

//this method is used to delete memory of the array
Deque_as_array::~Deque_as_array() {
    delete [] array;
}

//This method is used to return the size of the stored item in the array. We already defined that
//count represents the size, so this function should just return count.
int Deque_as_array::size() const {
    return count;
}

//This function return the size of array decided by user, the value is stored in array_size
int Deque_as_array::capacity() const {
    return array_size;
}

//This method check if the array is empty. It returns true if count = 0, false otherwise.
//because the size() method return count, and when there is '==', it means comparsion. size()==0
//return true operands are the same, false otherwise.
bool Deque_as_array::empty() const {
     return size()==0;
}

//This method should return the value at the head of the array.
//It shold throw underflow as there is nothing in the array, otherwise it should always return a value.
//Since ihead point to the begining of array, I just need array[ihead] to access the value
int Deque_as_array::head() const {
    if (empty()) {
        throw underflow();}
    else {
        return array[ihead];
    }
}

//This array returns the value at the end of the array
//It shold throw underflow as there is nothing in the array, otherwise it always return a value.
//since itail points to next available space,the value at the end should always be at
//one index before itail. There are two cases to consider:itail is at index 0 and other index.
//If itail is at 0 and it is a circular array, it means (itail-1) should be at the end of the array.
//Then, itail-1 should be at largest index which is capacity -1. When itail is not at 0,
//we can just simply use itail-1 to represent the previous index that stores the value.
int Deque_as_array::tail() const {
    
    if (empty()) {
        return 0;}//if there is nothing in the array, it should return 0;
    else {
        if(itail ==0){
            return array[capacity()-1];
        }else{
            return array[itail-1];
        }
    }
}
//This method stores values into the head of the array and values represented by the parameter obj
//Case 1: It should not store anything when the array is full or almost full(size = capacity-1)
//as I defined that array can only store n-1 elements in a n-element array. Thus, it should throw
//overflow if these case happen;
//case 2: if the size is 0, I set the default ihead to 0 and itail to 1
//case 3: size is not full or empty, I then need to set the new ihead becuase ihead has some value
//in the right now, and I want to enqueue from head, then the new ihead should be one index before.
//thus --ihead. However, one more to consider, if ihead is at 0 then new head should be the end of array
//which is capacity()-1. After the new ihead is set, I store value to it by used the parameter obj and
//the size should decrease by one.
void Deque_as_array::enqueue_head( int const &obj ) {
    //array cannot be full and can only be added when there are more than one space left
    if( size()==capacity() || (count+1)==capacity()){
        throw overflow();
        
    //if the array is empty, set the default head to 0 and tail to 1;
    }else if(count ==0){
        ihead=0;
        itail = 1;
    }else{
        if(ihead>0){
            --ihead;
        //if the ihead was at 0 and new head should move at the end
        }else if (ihead==0){
            ihead =capacity()-1;}
    }
    array[ihead]= obj;
    ++count;
}


//This method store value to the end of the array
//Case1: similar with enqueue_head, it should throw overflow if the full or almost full
//case2: similar wiwth enqueue_head, it set default ihead and itail if it's empty. and the value should
//be stored in 1, becase itail is 1 when it's empty. when value is store, new itail should be one index
//after (which is 2)
//case 3:not full or empty: the value can just be stored in itail becuase it one index after the end of
//array. After it's stored, new itail should be next index. if itail is at the end( capacity-1), new itail
//should be 0; otherwise, we just increase itail by 1. In the end, we increase the count by 1.
void Deque_as_array::enqueue_tail( int const &obj ) {
    if( size()==capacity()||(count+1)==capacity()){
        throw overflow();
    }else{
        //set default tail and head for an empty array
        if(count ==0){
//            ihead = 0;
//            array[1]=obj;
//            itail=2;
            ihead = 0;
            array[ihead]= obj;
            itail =1;
        //the array cannot be kept full, there must be one space empty.
        }else{
            array[itail]=obj;
            //if tail is at the end, next tail should be move to index 0
            if(itail==capacity()-1){
                itail = 0;
            }else{
                ++itail;
            }
        }
        ++count;

    }
}


//This method remove the element at begining of the array and return the value that is removed
//To return the value that needs to be removed, I put it in temp. Since ihead store the value,
//we just need to return array[ihead] and decrease size, but we also need to consider the new ihead.
//Case 1: if the array is empty, then there is nothing to delete, it should throw underflow
//Case 2: if the count is 1, the we need to decrease the size by 1 and return the value. We don't need
//to worry about the new ihead, as it will be reset to 0 when the array is empty.
//case 3: if the ihead is at the end(capacity-1), new head should be at the begining(0); otherwise
//ihead = ihead +1.
int Deque_as_array::dequeue_head() {
    int temp;
    //the array cannot be empty
    if( empty()){
        throw underflow();
    }else{
        
        temp = array[ihead];
        --count;
        if(count==1){
            count = 0;
            return temp;}

        if (ihead== capacity()-1){
            ihead =0;
        }else{
            ++ihead;}
    }
       return temp;
}

//This method remove the element at the end of the array and return the value that is removed
//To return the value that needs to be removed, I put it in temp. Since the end of array should be one
//index before itail, we need to find the real tail and set the new itail after it's dequeued.
//Case 1: if the array is empty, then there is nothing to delete, it should throw underflow
//Case 2: if the count is 1, the we need to decrease the size by 1 and return the value array[ihead]
//Since there is only one and current itail does not have value, the value is at ihead. We don't need
//to worry about the new ihead, as it will be reset to 0 when the array is empty.
//case 3: the real end is one index before itail, thus we use --itail. However, if tail is currently at
//index 0, and the new tail shoul be at the end (capacity-1); then we store array[itail] to temp and
//decrease the size

int Deque_as_array::dequeue_tail() {
    int temp;
    //array cannot be empty
    if( empty()){
        throw underflow();
    }else{
        if(count ==1 ){
            count=0;
            return temp = array[ihead];
        }else{
            if(itail == 0){
                itail =capacity()-1;
            }else{
                --itail;
            }
            temp = array[itail];
            --count;        
        }
    }
    return temp;
}

//This method remove all elements in the array and it is done by setting count to 0. Because in the accessor and mutators, those methods will
//throw underflow when the size is empty, there will not be any values in the array. I set ihead and itail to 0 and 1 repsectively, in case something
//went wrong, but I dont think it is needed.
void Deque_as_array::clear() {
    count = 0;
    ihead = 0;
    itail = 1;
    
}



// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif