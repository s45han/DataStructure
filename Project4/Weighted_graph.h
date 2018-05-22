#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <iostream>
#include <limits>
#include "Exception.h"

/****************************************
 * UW User ID:  s45han
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

class Weighted_graph {
	private:
		static const double INF;
		// your choice
        double **matrix;
        int *degreeM;
        int *flag;
        int *crossout;
        bool *visited;
        int vertices;
        int edge;
	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int  ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double minimum_spanning_tree( int ) const;
		bool is_connected() const;

		void insert( int, int, double );

	// Friends

	friend std::ostream &operator << ( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Create a matrix for store weight and and degree counter for each vertex. also initilize the counter for edge # and vertices.
Weighted_graph::Weighted_graph(int m){
    
    if(m <0){
        throw illegal_argument();
    }
    
    edge = 0;
    vertices = m;
    
    matrix = new double *[m];
    degreeM = new int [m];
    visited = new bool[m];
    for (int i = 0; i <m ; i++){
        matrix[i] = new double [m];
    }
    
    for (int i = 0; i <m ; i++) {
        for (int j = 0; j <m ; j++){
            matrix[i][j] = INF;
        }
        matrix[i][i] = 0;
        degreeM[i] = 0;
    }
    
    //initialize these two for mst methods.
    flag = new int[vertices];
    crossout = new int [vertices];
}
//clear all the array created for matrix and degree, and also the flags
Weighted_graph::~Weighted_graph(){
    
    for (int i = 0; i <vertices; i ++){
        delete [] matrix[i];
    }
    delete []matrix;
    delete []degreeM;
    delete []flag;
    delete []crossout;
    delete []visited;

    
}

//return the degree of vertex from the degree matrix.
int Weighted_graph::degree(int n) const{
    if( (n >= vertices)||(n<0)){
        throw illegal_argument();}
    return degreeM[n];
}

//just return the counter for edge
int Weighted_graph::edge_count() const{
    return edge;
}

//if its the same index then it should return 0 else, return the weight stored in the matrix.
double Weighted_graph::adjacent(int m, int n) const{
    if( (m >= vertices)|| (n >= vertices)||(m<0)||(n<0)){
        throw illegal_argument();
    }else if (m == n ){
        return 0;
    }else{
        return matrix[m][n];
    }
}
//throw exception for the vertices not in range. and it the degree of the node is 0 it means there is no edge(thus 0)
//else we loop through each node, and each time it will find the minimum edge under the flagged nodes and also set a temp value for the flag node. when comparing the value, the row thats visited will be crossout by set a flag to 0.  after the iteration we increment the min edge. and return the result after number of vertices iteration
double Weighted_graph::minimum_spanning_tree(int m) const{
    if( (m<0)|| (m == INF)||(m>=vertices)){
        throw illegal_argument();
    }
    if(degreeM[m]==0){
        return 0;
    }
    
    
    double result = 0;
    double min = INF;
    int node = 0;
    for ( int i =0 ; i < vertices; i++){
        flag[i] = 0;
        crossout[i] =0;
    }
    flag[m] = 1;
    crossout[m]=1;
    
    
    for (int i = 0; i <vertices; i++){
        node = 0;
        min = INF;
        for(int k = 0; k <vertices; k++){
            if(flag[k]==1){
                for (int j = 0; j <vertices; j++) {
                    if ((matrix[j][k]<min) && (matrix[j][k]!= 0) && (crossout[j]==0)){
                        min= matrix[j][k];
                        node = j;
                    }
                }
            }
            
        }
        flag[node]= 1;
        crossout[node]=1;
    
        if (min != INF){
            result = result+min;
        }
    }
    return result;
}


//call the mst function, if all the nodes are flagged after the function, then it mean all the node are visited the graph is connected. if there is any flag that is 0 then it means its not connected
bool Weighted_graph::is_connected() const{
    
    if(edge ==0){
        return false;
    }
    int x = 0;
    for (int i =0 ; i <vertices; i++){
        if (degreeM[i]!= 0)
        {
            int x = i;
            break;
        }
    }

    minimum_spanning_tree(x);
    for (int i = 0; i < vertices; i++){
            if(flag[i]==0){
                return false;
            }
    }
    return true;
}

//throw exception, if the vetices does not exist, of it give the same point, or the weight is inf
//if weigh is 0, then delete the graph by setting the weight to INF, and also decremnet the edge and the degree of two nodes.
//else we put in the weight value into the adjancency matrix.
void Weighted_graph::insert( int m, int n, double w ){
    if ((w < 0) ||(w== INF) ||(vertices == 0) || ( m == n) ||(m >= vertices) ||(n >=vertices)||(m<0)||(n<0)){
        throw illegal_argument();
    }
    if(w == 0 ){
        if(matrix[m][n]==INF){
            return;
        }
        matrix[m][n] = INF;
        matrix[n][m] = INF;
        --edge;
        --degreeM[m];
        --degreeM[n];
        return;
    }else if(matrix[m][n] ==INF){
        ++edge;
        ++degreeM[m];
        ++degreeM[n];
    }
    matrix[m][n] = w;
    matrix[n][m] = w;
        
       
    return;
}

std::ostream &operator << ( std::ostream &out, Weighted_graph const &graph ) {
	// Your implementation

	return out;
}

#endif
