//
//  hashtable.h
//  HashTable
//
//  Created by Artun on 3.08.2019.
//  Copyright © 2019 Artun. All rights reserved.
//

#ifndef hashtable_h
#define hashtable_h
#include <vector>

using namespace std;



template<class k,class HashedObj>
class HashTable
{
    
public:
    
    explicit HashTable(const k & key ,const HashedObj & notFound, int size = 101 );
    
    k & find( const k & x );
    void makeEmpty( );
    void insert(const k & key ,const HashedObj & x );
    void remove( const HashedObj & x );
   // const HashTable & operator=( const HashTable & rhs );
    enum EntryType { ACTIVE, EMPTY, DELETED };
    bool findElement();
    bool isActive( int currentPos ) const;
    int findPos( const k & x ) ;
    void rehash( );
    int hash( k  key)  ;
    
    struct HashEntry
    {
        k key;
        HashedObj element;
        EntryType info;
        HashEntry( const HashedObj & e,k mykey,EntryType i = EMPTY )
        : element( e ),key(mykey) ,info( i ) { }
    };
    vector<HashEntry> array;
    int currentSize;
    const HashedObj ITEM_NOT_FOUND;
    k notAkey;
    
};


#endif /* hashtable_h */
