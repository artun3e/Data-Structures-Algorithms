//
//  BST.cpp
//  artunsarioglu_cs300_hw2
//
//  Created by Artun on 20.07.2019.
//  Copyright © 2019 Artun. All rights reserved.
//

#include "BST.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
    Constructor of the tree
*/
template <class Comparable,class value>
BinarySearchTree<Comparable,value>::BinarySearchTree(const Comparable & notFound,const value & Val ) :
ITEM_NOT_FOUND( notFound ), root( NULL )
{}


/**
 * Internal method to get element field in node t.
 * Return the element field or ITEM_NOT_FOUND if t is NULL.
 */
template <class Comparable,class value>
const Comparable & BinarySearchTree<Comparable,value>::elementAt( BinaryNode<Comparable,value> *t ) const
{
    return t == NULL ? ITEM_NOT_FOUND  : t->element;
}

/**
 * Find item x in the tree.
 * Return the matching item or ITEM_NOT_FOUND if not found.
 */
template <class Comparable,class value>
const Comparable & BinarySearchTree<Comparable,value>::find( const Comparable & x ) const
{
    return elementAt(find( x, root ));
}


/*
 This function checks whether the tree is empty.
 */
template<class Comparable,class value>
bool BinarySearchTree<Comparable,value>::isEmpty()const
{
    return root == NULL;
}


/**
 * Internal method to find an item in a subtree.
 * x is item to search for.
 * t is the node that roots the tree.
 * Return node containing the matched item.
 */

template <class Comparable,class value>
BinaryNode<Comparable,value> *
BinarySearchTree<Comparable,value>::find( const Comparable & x, BinaryNode<Comparable,value> * t ) const
{
    if ( t == NULL )
        return NULL;
    else if( x < t->element )
        return find( x, t->left );
    else if( t->element < x)
        return find( x, t->right );
    else
        return t; // Match
}


/**
 * Find the smallest item in the tree.
 * Return smallest item or ITEM_NOT_FOUND if empty.
 */
template <class Comparable,class value>
const Comparable & BinarySearchTree<Comparable,value>::findMin( ) const
{
    return elementAt(findMin( root ));
}

/**
 
 * Internal method to find the smallest item in a subtree t.
 
 * Return node containing the smallest item.
 
 */

template <class Comparable,class value>
BinaryNode<Comparable,value> *
BinarySearchTree<Comparable,value>::findMin( BinaryNode<Comparable,value> *t ) const
{
    if( t == NULL )
        return NULL;
    if( t->left == NULL )
        return t;
    return findMin( t->left );
}


/**
 * Find the smallest item in the tree.
 * Return smallest item or ITEM_NOT_FOUND if empty.
 */
template <class Comparable,class value>
const Comparable & BinarySearchTree<Comparable,value>::findMax( ) const
{
    return elementAt( findMax( root ) );
}

/**
 
 * Internal method to find the largest item in a subtree t.
 
 * Return node containing the largest item.
 
 */

template <class Comparable,class value>
BinaryNode<Comparable,value> *
BinarySearchTree<Comparable,value>::findMax( BinaryNode<Comparable,value> *t )const
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
    return t;
}

/**
 * Insert x into the tree; duplicates are ignored.
 */
template <class Comparable,class value>
void BinarySearchTree<Comparable,value>::insert( const Comparable & x, value theValue  )
{
    insert(x,theValue,root);
}

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the tree.
 * Set the new root.
 */
template <class Comparable,class value>
void BinarySearchTree<Comparable,value>::insert( const Comparable & x,value theValue ,BinaryNode<Comparable,value> * & t ) const
{
    if( t == NULL ) // create a new node at the right place
        t = new BinaryNode<Comparable,value>( x, theValue, NULL,NULL );
    else if( x < t->element )
        insert( x,theValue ,t->left ); // insert at the left or
    else if( t->element < x )
        insert( x,theValue ,t->right ); // right subtree
    else
        ; // Duplicate; do nothing
    
    // delete t ?
}

/**
 **Remove x from the tree. Nothing is done if x is not found.
 */
template <class Comparable,class value>
void BinarySearchTree<Comparable,value>::remove( const Comparable & x )
{
    remove( x, root );
}

/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the tree.
 * Set the new root.
 */
template <class Comparable,class value>
void BinarySearchTree<Comparable,value>::remove( const Comparable & x, BinaryNode<Comparable,value> * & t )const
{
    if( t == NULL )
        return; // Item not found; do nothing
    if( x < t->element )
        remove( x, t->left );
    else if( t->element < x )
        remove( x, t->right );
    else if( t->left != NULL && t->right != NULL ) // Two children
    {
        t->element = findMin( t->right)->element ;
        remove( t->element, t->right )->element;
    }
    else // one or no children
    {
        BinaryNode<Comparable,value> *oldNode = t;
        t = ( t->left != NULL ) ? t->left : t->right;
        delete oldNode;
    }
}

/*
 This funcction updates the node for occurences in files
 */


template<class Comparable,class value>
BinaryNode<Comparable, value> * BinarySearchTree<Comparable,value>::updateNode(Comparable & element)
{
    return find(element,root);
}


/*
 This function calls the private makeEmpty function to basically empty the tree
 P.s -> we do not need this in our homework
 */

/**
 * Destructor for the tree.
 */


/**
 * Internal method to make subtree empty.
 */




template<class Comparable,class value>
value BinarySearchTree<Comparable,value>::getNode(Comparable & element)
{
    return find(element,root)->val;
}

 


/**
 * Copy constructor.
 */

