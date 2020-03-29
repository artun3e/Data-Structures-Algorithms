#include <iostream>
#include "hashtable.h"
#include <vector>

using namespace std;


/**
 * Internal method to return a prime number
 * at least as large as n. Assumes n > 0.
 */
bool isPrime( int n )
{
    
    if ( n == 2 || n == 3 )
        return true;
    
    if ( n == 1 || n % 2 == 0 )
        return false;
    
    for ( int i = 3; i * i <= n; i += 2 )
        if ( n % i == 0 )
            return false;
    
    return true;
    
}

int nextPrime( int n )
{
    if ( n % 2 == 0 )
        n++;
    
    for ( ; ! isPrime( n ); n += 2 )
        ;
    
    return n;
    
}

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */



/**
 * Construct the hash table.
 */
template <class k,class HashedObj>
HashTable<k,HashedObj>::HashTable( const k & key,const HashedObj & notFound,int size )
: ITEM_NOT_FOUND( notFound ), array( nextPrime( size ) )
{
    makeEmpty( );
}


template<class k,class HashedObj>
int HashTable<k,HashedObj>::hash(k  key) 
{
    return key % array.size();
}


template<class k,class HashedObj>
/**
 * Method that performs quadratic probing resolution.
 * Return the position where the search for x terminates.
 */
int HashTable<k,HashedObj>::findPos(const k & x )
{
    int collisionNum = 0;
    //int currentPos = hash(x);
    int currentPos = hash(x);
    while ( array[ currentPos ].info != EMPTY && array[ currentPos ].key != x )
    {
        currentPos += 2 * ++collisionNum - 1; // add the difference
        if ( currentPos >= array.size( ) ) // perform the mod
            currentPos = currentPos - array.size( ); // if necessary
    }
    
    return currentPos;
}


/**
 
 * Return true if currentPos exists and is active.
 
 */

template <class k,class HashedObj>
bool HashTable<k,HashedObj>::isActive( int currentPos ) const
{
    return array[ currentPos ].info == ACTIVE;
}


/**
 * Find item x in the hash table.
 * Return the matching item, or ITEM_NOT_FOUND, if not found.
 */

template <class k,class HashedObj>
 k & HashTable<k,HashedObj>::find( const k & x )
{
   
    int currentPos = findPos( x );
    if (isActive( currentPos ))
        return array[ currentPos].key;
    return notAkey ; // might have deal with it later
}



/**
 * Insert item x into the hash table. If the item is
 * already present, then do nothing.
 */

template <class k,class HashedObj>
void HashTable<k,HashedObj>::insert( const k & key,const HashedObj & x )
{
    // Insert x as active
    int currentPos = findPos( key);
    if ( isActive( currentPos ) )
        return;
    
    array[ currentPos ] = HashEntry( x, ACTIVE );
    // enlarge the hash table if necessary
    
    if ( ++currentSize >= array.size()*1.0 / 2 )
        rehash( );
}


/**
 * Expand the hash table.
 */

template <class k,class HashedObj>
void HashTable<k,HashedObj>::rehash( )
{
    vector<HashEntry> oldArray = array;
    // Create new double-sized, empty table
    array.resize( nextPrime( 2 * oldArray.size( ) ) );

    for ( int j = 0; j < array.size( ); j++ )
        array[ j ].info = EMPTY;
    
    // Copy table over
    currentSize = 0;
    
    for ( int i = 0; i < oldArray.size( ); i++ )
        if ( oldArray[ i ].info == ACTIVE )
            insert( oldArray[i].key,oldArray[ i ].element );
    
}




