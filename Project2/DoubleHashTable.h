#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  s45han
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
private:
    int count;
    int power;
    int array_size;
    T *array;
    state *array_state;
    
    int h1( T const & ) const; // first hash function
    int h2( T const & ) const; // second hash function
    
public:
    DoubleHashTable( int = 5 );
    ~DoubleHashTable();
    int size() const;
    int capacity() const;
    bool empty() const;
    bool member( T const & ) const;
    T bin( int ) const;
    
    void print() const;
    
    void insert( T const & );
    bool remove( T const & );
    void clear();
};

template<typename T >
DoubleHashTable<T>::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {
    
    for ( int i = 0; i < array_size; ++i ) {
        array_state[i] = EMPTY;
    }
}
//------------------IMPLEMENTATIONS----------------------------
//This method should deallocate the memory stored, because we delared two arrays, so we need to used [] to
//delete the created two arrays.
template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
    delete []array;
    delete []array_state;
}

//This method should return the number of elements that is stored inside the hash table.
//Count is used as a tracker when element is inserted or deleted.
template<typename T >
int DoubleHashTable<T >::size() const {
       return count;
}

//THis methos should return the size of the hash table, and the array_size is declared when
//the array in created, so we can just return array_size.
template<typename T >
int DoubleHashTable<T >::capacity() const {
    return array_size;
}
//This method is used to check if there is any element in the hash table. I used the compare fucntion,
//to see if size == 0, if so, it will return true, else, it returns false.
template<typename T >
bool DoubleHashTable<T >::empty() const {
    return size()==0;
}

//This is the h1 function to find the index. Because the % may give a negative value, we will need to
//add the capacity inorder to make it posistive.
template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
        int i = static_cast<int>(obj);
    
        int result = i%capacity();
        if(result < 0){
            result = result+ capacity();
        }
        return result;
    }
    
    

//This is a method of h2 function, and apply the module of M to the result of this integer division((i / M) % M)
//if the result is even, I need to add 1 to make is odd.
template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
    // enter your implemetation here
    int result = (static_cast<int>(obj)/capacity())%capacity();
    if (result <0){
        result = result +capacity();
    }
    if(result %2 == 0){
        ++result;
    }
    
    return result;
}
//This method is used to see if the object is alreay in the hash table, we need to consider two cases where
//the element is occupided or deleted. if so, we check with index with object, if matches, return true; else, we update the index value by the h(k)function.after looping, if there is a space that's empty,
//then the object is not in the list. If the table is empty, there is no need to check anymore.
template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
    if(empty()){
        return false;
    }else{
        int index = h1(obj);
        while(array_state[index]==OCCUPIED || array_state[index]==DELETED){
            if (array[index]==obj && array_state[index]!=DELETED){
                return true;
            }
            index = (index + h2(obj))%capacity();
            if (index<0){index = index +capacity();}
        }
        return false;
    }
}
//This function should return of value stored in the specified index. because the function is not delared
//if the element is not occupied, we can just return the array[n].
template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
        return array[n];
}

//This method is used to insert value into the array, it should throw overflow, if the table is already full
//also, I used the member function to check if the obj is store in the table already. If so, it should
//return false to prevent another insertion.Then we try to find the correct index to insert, by calling the
//h1 and h2 functions, the it will keep on updating the index if the corresponding index is occupied. After
//we find the index, we put the obj in array and update the status to occupied, and also increase count.
template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {

    int index;
    if(count == capacity()){
        throw overflow();}
    else if(!(member(obj))){
 
        index = h1(obj);

        
        while(array_state[index]==OCCUPIED){
            index = (index + h2(obj))%capacity();
            if(index<0){
                index = index+capacity();
            }
        }
        array[index]= obj;
        array_state[index]= OCCUPIED;
        ++count;
        return;
    }
}

//This method is used to remove element in the table. If the size is 0, then is should return false, and
//next is to check if the element is in the array by memeber function. if so, return false as well.
//Then use the similiar methodology of the member function, we try to find the index to remove. After we
//find the corresponding index, the state of the index should not be deleted. then , set the status to
//DELETED and decreate the count size.
template<typename T >
bool DoubleHashTable<T>::remove( T const &obj ) {
    // enter your implemetation here
    if(size()==0){
        return false;
        
    }
    else if(!member(obj)){
        return false;
    }else{
        int index = h1(obj);
        while( array_state[index]==OCCUPIED || array_state[index]== DELETED){
            if (array[index]==obj && array_state[index]!= DELETED){
                --count;
                array_state[index]=DELETED;
                return true;
            
            }
            index = (index + h2(obj))%capacity();
            if (index<0){index = index +capacity();}
        }
        return false;
        
    }
}
//This method clear the hash table, we need to set the value to the initail values. count should be 0;
//and the status of all index should be DELETED as well.
template<typename T >
void DoubleHashTable<T >::clear() {
    count = 0;
    for (int i = 0; i <capacity(); ++i){
        array_state[i]= DELETED;
    }
    return ;
}
//This method is used to display the related information about the hash table, it will displays the size,
//capacity, contents and status. I used a loop to display the content and status.
template<typename T >
void DoubleHashTable<T >::print() const {
    // enter your implemetation here
    std::cout << "size: " << size() << std::endl;
    
    std::cout << "capacity: " << capacity() << std::endl;
    std::cout<<"Display\n" << std::endl;
    for(int i = 0 ; i <capacity(); ++i){
        std::cout<<array[i]<< "  state: "<< array_state[i]<<std::endl;
    }
    return;
}

#endif