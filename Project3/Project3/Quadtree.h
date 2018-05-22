#ifndef QUADTREE_H
#define QUADTREE_H

/***************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ***************************************/

#include "ece250.h"
#include "Quadtree_node.h"
#include "Exception.h"
#include <iostream>

template <typename T>
class Quadtree {
	private:
		Quadtree_node<T> *tree_root;
		int count;

	public:
		Quadtree();
		~Quadtree();

		// Accessors

		int size() const;
		bool empty() const;

		T min_x() const;
		T min_y() const;

		T max_x() const;
		T max_y() const;

		T sum_x() const;
		T sum_y() const;

		Quadtree_node<T> *root() const;
		bool member( T const &, T const & ) const;

		// Mutators

		void insert( T const &, T const & );
		void clear();

	
};

template <typename T>
Quadtree<T>::Quadtree():
tree_root( 0 ), 
count( 0 ) {
	// empty constructor
}

template <typename T>
Quadtree<T>::~Quadtree() {
    delete tree_root;
}
//reuturn the size of the tree.
template <typename T>
int Quadtree<T>::size() const {
	return count;
}
//return true if count is 0
template <typename T>
bool Quadtree<T>::empty() const {
	return (count ==0);
}

//find the x min value by calling quadtree min x
template <typename T>
T Quadtree<T>::min_x() const {
    if(empty())
        throw underflow();
    else{
        return tree_root->min_x();
    }
    
}

//find the y min value by calling quadtree min y
template <typename T>
T Quadtree<T>::min_y() const {
    if(empty())
        throw underflow();
    else{
        return tree_root->min_y();
    }
}

//find the x max value by calling quadtree max x
template <typename T>
T Quadtree<T>::max_x() const {
    if(empty())
        throw underflow();
    else{
        return tree_root->max_x();
    }
}

//find the y min value by calling quadtree min y
template <typename T>
T Quadtree<T>::max_y() const {
    if(empty())
        throw underflow();
    else{
        return tree_root->max_y();
    }
}

////find the x sum value by calling quadtree sum x
template <typename T>
T Quadtree<T>::sum_x() const {
    if(empty()){
        return 0;
    }else{
        return tree_root->sum_x();
    }
}

//find the ysum value by calling quadtree sumy

template <typename T>
T Quadtree<T>::sum_y() const {
    if(empty()){
        return 0;
    }else{
        return tree_root->sum_y();
    }
}

//find the tree root if empty return 0
template <typename T>
Quadtree_node<T> *Quadtree<T>::root() const {
    if(empty()){
        return 0;
    }else{
        return tree_root;//* content of var, & address of var.
        }
    
}

//check if the input value exists. by calling node class
template <typename T>
bool Quadtree<T>::member( T const &x, T const &y ) const {
    if(tree_root->member(x,y)){
        return true;
    }else{
        return false;}
}

//insert node by calling node class
template <typename T>
void Quadtree<T>::insert( T const &x, T const &y ) {
    if(tree_root ==0){
        tree_root = new Quadtree_node<T>(x, y);
        count = 1;
    }else{
        bool inserted = tree_root->insert(x,y);
        if(inserted){
            count++;
        }
    }
    
}

//clear the tree by calling node class and set count to 0;
template <typename T>
void Quadtree<T>::clear() {
    tree_root->clear();
    tree_root = 0;
    count =0;
}



// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
