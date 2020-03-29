//
//  main.cpp
//  HashTable
//
//  Created by Artun on 3.08.2019.
//  Copyright © 2019 Artun. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "hashtable.h"
#include "hashtable.cpp"
#include "BST.h"
#include "BST.cpp"


using namespace std;




struct DocumentItem
{
    string documentName;
    int count;
};

struct WordItem
{
    string word;
    vector<DocumentItem> list;
};

//HashTable<int, WordItem,1> myTable; // Hash Table
HashTable<int,WordItem> myTable();
int turnASCII(const string & word);
void updateNode(const int & key,const string & filename);




 
    


string toLower(string & word)
{
    for (int i = 0; i < word.length(); i++) {
        if (word[i] >= 65 && word[i] <= 90)
        {
            word[i]+= 32; // it is basically tolower function
        }
    }
    return word;
}



/*
 This function checks whether the word contains non digit characters, and uses them as seperators ending up with getting multiple words on the occasion
 */
string check(string & word)
{
    toLower(word);
    
    for (int i = 0; i < word.length(); i++)
    {
        if (word.at(i) < 97 || word.at(i) > 122) // means its not a letter
            word.at(i) =  ' ';
        
        
    }
    return word;
}




int turnASCII(const string & word)
{
    int toReturn = 0;
    
    for (int i = 0 ; i < word.length(); i++)
        toReturn += word.at(i);
    
    
    return toReturn;
}



int findHT(const string & word)
{
    bool flag = false ;
    
    int index = myTable().hash(turnASCII(word));
    
    if (myTable().array[index].element.word == word)
    {
        flag = true;
    }
    
    while (myTable().array[index].element.word!=word)
    {
        index++;
        if (myTable().array[index].element.word == word)
        {
            flag = true;
        }
        if(index > myTable().array.size())
            index = index - myTable().array.size();
    }
    
    if (flag) {
        return index;
    }
    else
        return -1;
}


void updateNode(const int & key,const string & filename)
{
    bool flag =false;
    for (int i = 0; i < myTable().array[key].element.list.size(); i++)
    {
        // check whether file exists
        if (myTable().array[key].element.list[i].documentName == filename) {
            myTable().array[key].element.list[i].count++;
            flag =true;
        }
    }
    
    if(flag==false)
    {
        DocumentItem temp;
        temp.documentName = filename;
        temp.count = 1;
        myTable().array[key].element.list.push_back(temp);
    }
}

// Preprocessing function(i.e filling the hash table up)
void preProcess(const string & filename)
{
    ifstream file;
    file.open(filename.c_str()); // File is opened
    
    
    string line;
    while(getline(file, line)) // read each line , then process it
    {
        istringstream iss(line);
        string word;
        
        toLower(word);
        while (iss>>word)
        {
    
            // seperator
               string templine =  check(word);
            
            istringstream iss2(templine);
            string tempword;
            while(iss2 >> tempword)
            {
                // if the word exists , update the corresponding hashnode
                //else , insert it to the hashtable
                int tempint = findHT(tempword);
                if (tempint  > -1) // means the word exists
                {
                    updateNode(tempint, filename);
                }
                else // means the word exist
                {
                    WordItem tempitem;
                    tempitem.word = tempword;
                    DocumentItem docitem;
                    docitem.count = 1;
                    docitem.documentName = filename;
                    tempitem.list.push_back(docitem);
                    myTable().insert(turnASCII(tempword), tempitem);
                }
                
            }
        }
        
    }
}


// BST FUNCTIONS
WordItem notFound;
string str = "";
BinarySearchTree<string,WordItem> mytree(str,notFound); // global variable


bool existsBST(string & element)
{
    return (mytree.find(element) == "") ? false : true;
}

void updateNodeBST(BinarySearchTree<string, WordItem> mytree, string & word,string doc )
{
    BinaryNode<string, WordItem> * mynode = mytree.updateNode(word);
    // we need to update mynodes word item
    // first we need to make sure about the file
    bool flag = false ;
    
    for (int i = 0; i < mynode->val.list.size() ; i++)
    {
        // we need check the list filename
        if (mynode->val.list[i].documentName == doc )
        {
            flag = true; // means that this document has occured before , we just need to update the count
            mynode->val.list[i].count++;
            break;
        }
    }
    
    if (flag == false) // means we are on a different document
    {
        DocumentItem newdoc;
        newdoc.count = 1;
        newdoc.documentName = doc;
        mynode->val.list.push_back(newdoc);
    }
    
}

string checkBST(string & word)
{
    
    for (int i = 0; i < word.length(); i++)
    {
        if (word.at(i) < 97 || word.at(i) > 122) // means its not a letter
            word.at(i) =  ' ';
        
        
    }
    return word;
}


void preProcessBST(string & filename)
{
    ifstream file;
    file.open(filename.c_str());
    
    // we are inside the file now
    
    
    // Better complexity ?
    string line;
    while (getline(file,line))
    {
        istringstream iss2(line);
        string word;
        
        while(iss2>>word)
        {
                toLower(word);
                checkBST(word);
            
            istringstream iss3(word);
            while(iss3>>word)
            {
            
                if (existsBST(word)) // if the word has occured before
                    updateNodeBST(mytree, word, filename);
                else // the word has never occured before
                {
                    WordItem toAdd;
                    toAdd.word = toLower(word);
                    
                    DocumentItem doc;
                    doc.count = 1;
                    doc.documentName = filename;
                    vector<DocumentItem> wordvec;
                    wordvec.push_back(doc);
                    toAdd.list = wordvec;
                    mytree.insert(word,toAdd);
                }
            }
        }
    }
}

vector<DocumentItem> commonfiles(vector<string> myVec)
{
    vector<DocumentItem> files;
    
    vector<WordItem> toPrint;
    for (int i = 0; i < myVec.size(); i++)
    {
        toPrint.push_back(mytree.getNode(myVec[i]));// all the information about the node
    }
    
    for (int i = 0; i < toPrint.size(); i++)
        for (int j = 0; j < toPrint[i].list.size(); j++)
            files.push_back(toPrint[i].list[j]);
    
    
    
    
    return files;
}

void  findBST(vector<string> queries)
{
    int count = 0;
    for (int i = 0; i<queries.size(); i++)
    {
        if(existsBST(queries[i])==false)
        {
            ; // do nothing
        }
        else
            count++;
    }
    

}

void findHTable(vector<string> queries)
{
    int count = 0;
    for (int i = 0; i<queries.size(); i++)
    {
        if(findHT(queries[i]) == -1)
        {
            ; // do nothing
        }
        else
            count++;
    }
}



    


int main()
{
  
    vector<string> filenames;
    int manyinputs;
    
    cout << "Enter the number of input files:   ";
    cin >> manyinputs;
    
    // Getting the filenames
    for (int i = 0; i < manyinputs; i++)
    {
        string filename;
        cout << "Please enter the   " << i << ". file name:    ";
        cin >> filename;
        filenames.push_back(filename);
    }
    
    
    // preprocessing for every file
    // Time is calculated here...
    
    for (int i = 0; i < filenames.size() ; i++)
        preProcess(filenames[i]);
    
    for (int i = 0; i < filenames.size() ; i++)
        preProcessBST(filenames[i]);
    
  
    
   
    
    // from very this line , preprocessing is done , hashtable is filled wiht a load factor <= 0.5
    // we need the queried words now
    
    string line;
    cout << "Enter queried words in one line:  ";
    cin.ignore();
    getline(cin,line);

    cout << endl;
    
    istringstream ss(line);
    string querystrings;
    vector<string> queries;
    while (ss>>querystrings)
    {
        queries.push_back(querystrings);
    }
    
    

    int HTcount = 0;
    int BSTcount=0;
    int k = 3000;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        findBST(queries);
    }
    auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
    (std::chrono::high_resolution_clock::now() - start);
    cout << "\nTime: " << BSTTime.count() / k << "\n";
    
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        findHTable(queries);
    }
    auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
    (std::chrono::high_resolution_clock::now() - start);
    cout << "\nTime: " << HTTime.count() / k << "\n";
    

    

    return 0;
}
