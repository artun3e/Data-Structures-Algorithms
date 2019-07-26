//
//  BST.h
//  artunsarioglu_cs300_hw2
//
//  Created by Artun on 20.07.2019.
//  Copyright © 2019 Artun. All rights reserved.
//

#ifndef BST_h
#define BST_h

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;


// Node for our Binary Search Tree
template<class Comparable,class value>
struct BinaryNode
{
    Comparable element;
    value val;
    BinaryNode *left;
    BinaryNode *right;
    
    BinaryNode(const Comparable & theElement,const value & theVal ,BinaryNode *lt, BinaryNode *rt)
    :   element(theElement) , val(theVal),left(lt) , right(rt) {}    
};

template <class Comparable,class value>
class BinarySearchTree
{
    
public:
    
    explicit BinarySearchTree( const Comparable & notFound,const value & Val );
    
    BinarySearchTree(); // Constructor --- comparable
  //  ~BinarySearchTree( ); // Destructor
    
    const Comparable & findMin( ) const;
    const Comparable & findMax( ) const;
    const Comparable & find( const Comparable & x ) const; //updated and okay now
    bool isEmpty( ) const;
    void makeEmpty( );
    void insert( const Comparable & x,value theValue ); //updated -- now checking -- and okey now --   COMPARABLE
    void remove( const Comparable & x );  //updated -- now checking -- and okey now -COMPARABLE
    BinaryNode<Comparable, value> * updateNode(Comparable & element); // updated
    value getNode(Comparable & element); 
    const BinarySearchTree & operator=(const BinarySearchTree & rhs );
    
private:
    
    BinaryNode<Comparable,value> *root;
    const Comparable ITEM_NOT_FOUND;
    const Comparable & elementAt( BinaryNode<Comparable,value> *t ) const; //check this
    void insert( const Comparable & x,value theValue ,BinaryNode<Comparable,value> * & t ) const; //updated -- and okey now
    void remove( const Comparable & x, BinaryNode<Comparable,value> * & t ) const; // updated -- and okey now
    BinaryNode<Comparable,value> * findMin( BinaryNode<Comparable,value> *t ) const;
    BinaryNode<Comparable,value> * findMax( BinaryNode<Comparable,value> *t ) const;
    BinaryNode<Comparable,value> * find( const Comparable & x,BinaryNode<Comparable,value> *t ) const;
    void makeEmpty( BinaryNode<Comparable,value> * & t ) const;
    BinaryNode<Comparable,value> * clone( BinaryNode<Comparable,value> *t ) const;
    
};

#endif /* BST_h */
