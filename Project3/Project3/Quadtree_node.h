#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

/****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "ece250.h"

template <typename T>
class Quadtree;

template <typename T>
class Quadtree_node {
	private:
		T       x_value;
		T       y_value;

		Quadtree_node *north_west;
		Quadtree_node *north_east;
		Quadtree_node *south_west;
		Quadtree_node *south_east;

	public:
		Quadtree_node( T const & = T(), T const & = T() );
        ~Quadtree_node() ;
		T retrieve_x() const;
		T retrieve_y() const;

		Quadtree_node *nw() const;
		Quadtree_node *ne() const;
		Quadtree_node *sw() const;
		Quadtree_node *se() const;

		T min_x() const;
		T min_y() const;

		T max_x() const;
		T max_y() const;

		T sum_x() const;
		T sum_y() const;

		bool member( T const &, T const & ) const;

		bool insert( T const &, T const & );
		void clear();

        friend class Quadtree<T>;
};

template <typename T>
Quadtree_node<T>::Quadtree_node( T const &x, T const &y ):
x_value( x ), 
y_value( y ), 
north_west( 0 ),
north_east( 0 ),
south_west( 0 ),
south_east( 0 ) {
	// empty constructor
}


//This call the function to deallocate the the memoery.
template <typename T>
Quadtree_node<T>::~Quadtree_node() {
    north_east->clear();
    north_west->clear();
    south_east->clear();
    south_west->clear();
}

//get x value of the node.
template <typename T>
T Quadtree_node<T>::retrieve_x() const {
	return x_value;
}

//get y value of the node.
template <typename T>
T Quadtree_node<T>::retrieve_y() const {
	return y_value;
}

//point to the north west node of the current node.
template <typename T>
Quadtree_node<T> *Quadtree_node<T>::nw() const {
	return north_west;
}

//point to the north east node of the current node.
template <typename T>
Quadtree_node<T> *Quadtree_node<T>::ne() const {
	return north_east;
}

//point to the south west node of the current node.
template <typename T>
Quadtree_node<T> *Quadtree_node<T>::sw() const {
	return south_west;
}

//point to the south east node of the current node.
template <typename T>
Quadtree_node<T> *Quadtree_node<T>::se() const {
	return south_east;
}

//find the min x value of the tree. when nw sw= 0 means that we have reached the end of the node. thus it will be the smallest value.
//else, it will find the nw sw of the current node until it reaches the end. we compare the sw nw found.
template <typename T>
T Quadtree_node<T>::min_x() const {
	// you may use std::min
    if(nw()==0 && sw()==0){
        return x_value;
    }else if(nw() == 0 && sw()!=0){
        return sw()->min_x();
    }else if(nw() != 0 && sw()==0){
        return nw()->min_x();
    }else{
        return std::min(nw()->min_x(),sw()->min_x());
    }
    
}

//find the min y value of the tree, recursively find the next sw se until it reaches the end of the tree.
template <typename T>
T Quadtree_node<T>::min_y() const {
	// you may use std::min
    if(sw()==0 && se()==0){
        return y_value;
    }else if(sw()==0 && se()!=0){
        return se()->min_y();
    }else if(sw()!= 0 && se()==0){
        return sw()->min_y();
    }else{
        return std::min(sw()->min_y(), se()->min_y());
    }
	
}

//similar with the x min and x max, stop until you find the leaves and compare.
template <typename T>
T Quadtree_node<T>::max_x() const {
	// you may use std::max
    if (se() == 0 && ne()==0){
        return x_value;
    }else if(se() == 0 && ne() != 0){
        return ne()->max_x();
    }else if(se() != 0 && ne() ==0){
        return se()->max_x();
    }else{
        return std::max(nw()->max_x(),ne()->max_x());
    }
}

//similar with the x min and x max, stop until you find the leaves and compare.
template <typename T>
T Quadtree_node<T>::max_y() const {
	// you may use std::max
    if (nw() == 0 && ne()==0){
        return y_value;
    }else if(nw() == 0 && ne() != 0){
        return ne()->max_y();
    }else if(nw() != 0 && ne() ==0){
        return nw()->max_y();
    }else{
        return std::max(nw()->max_y(),ne()->max_y());
    }
}

//add the current value to to variable store the previous sum, and go up the tree and add again.
template <typename T>
T Quadtree_node<T>::sum_x() const {
    T sum = 0;
	if ( this == 0 ) {
		// hint...
		return 0;
	} else {
        if(nw() == 0 &&sw()==0 && ne()==0 &&se()== 0){
            return x_value;
        }else {
            if(nw()!= 0){
                sum += nw()->sum_x();
            }
            if(ne()!= 0){
                sum += ne()->sum_x();
            }
            if(sw()!= 0){
                sum += sw()->sum_x();
            }
            if(se()!= 0){
                sum += se()->sum_x();
            }
        }
        	}
    return x_value + sum ;

}

//similar with sum_x, add from the leave and traverse up the tree.
template <typename T>
T Quadtree_node<T>::sum_y() const {
    T sum = 0;
    
    if ( this == 0 ) {
        // hint...
        return 0;
    } else {
        if(nw() == 0 && sw()==0 && ne()==0 && se()== 0){
            return y_value;
        }else {
            if(nw()!= 0){
                sum += nw()->sum_y();
            }
            if(ne()!= 0){
                sum += ne()->sum_y();
            }
            if(sw()!= 0){
                sum += sw()->sum_y();
            }
            if(se()!= 0){
                sum += se()->sum_y();
            }
        }
    }
    return y_value + sum ;
}

//check if the value exists, if not check the four nodes after this. if it reaches the end of the tree, it mean the values does not exist then return false.
template <typename T>
bool Quadtree_node<T>::member( T const &x, T const &y ) const {
	if ( this == 0 ) {
		return false;
	}else if(x_value == x && y_value == y ){
             return true;
    }else if(x_value==0 && y_value==0){
        return false;
    
    }else if(x < x_value){
        
            if(y < y_value){
                return sw()->member(x,y);
            }else{
                return nw()->member(x,y);
            }
        
    }else {//if(x >= x_value){
        if(y < y_value){
            return se()->member(x,y);
        }else{
            return ne()->member(x,y);
        }
    }
	//return false;


}
//check if the value exists, then return false. if it finds the right place, then we create a node and return true.
template <typename T>
bool Quadtree_node<T>::insert( T const &x, T const &y ) {
    if(x_value == x && y_value == y){
        return false;
    }else if(x_value == 0 && y_value == 0){
        new Quadtree_node(x,y);
        return true;
    }else if(x < x_value ){
        if(y < y_value){
            if(sw()==0){
                south_west = new Quadtree_node(x,y);
                return true;
            }else{
                return sw()->insert(x,y);
            }
        }else{
            if(nw()==0){
                north_west = new Quadtree_node(x,y);
                return true;
            }else{
                return nw()->insert(x,y);
            }
        }
    }else if (x>=x_value){
        if(y < y_value){
            if(se()==0){
                south_east = new Quadtree_node(x,y);
                return true;
            }else{
                return se()->insert(x,y);
                
            }
        }else{
            if(ne()==0){
                north_east = new Quadtree_node(x,y);
                return true;
            }else{
                return ne()->insert(x,y);
            }
        }
    }
    return false;
}

//clear the the tree until it reaches the leaves. 
template <typename T>
void Quadtree_node<T>::clear() {
    if(this!=0){
        nw()->clear();
        north_west = 0;
        ne()->clear();
        north_east = 0;
        sw()->clear();
        south_west = 0;
        se()->clear();
        south_east = 0;
        //x_value = 0;
        //y_value = 0;
        
        delete this;

    }
    
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
