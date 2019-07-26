//
//  artunsarioglu_cs300_hw2.cpp
//  artunsarioglu_cs300_hw2
//
//  Created by Artun on 20.07.2019.
//  Copyright © 2019 Artun. All rights reserved.
//


// insert , remove ,find hepsini worditeme gore yapman gerek onu duzelt zaten rahat rahat calisacak.
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "BST.h"
#include "BST.cpp"

using namespace std;

struct  DocumentItem
{
    string documentName;
    int count;
};

struct WordItem
{
    string word;
    // List of document items
    vector<DocumentItem> list ;
};


WordItem notFound;
string str = "";
BinarySearchTree<string,WordItem> mytree(str,notFound); // global variable


string toUpper(string & word){
    
    for (int i = 0; i < word.length(); i++) {
        if (word[i] >= 65 && word[i] <= 90)
        {
            word[i]+= 32; // it is basically tolower function
        }
    }
    return word;
}


bool hasDigits(string c) // this function checks whether a string c has any digits inside of it
{
    if (c.find('0') != string::npos ||
        c.find('1') != string::npos ||
        c.find('2') != string::npos ||
        c.find('3') != string::npos ||
        c.find('4') != string::npos ||
        c.find('5') != string::npos ||
        c.find('6') != string::npos ||
        c.find('7') != string::npos ||
        c.find('8') != string::npos ||
        c.find('9') != string::npos)
        return true;
    return false;
}


bool exists(string & element)
{
    return (mytree.find(element) == "") ? false : true;
}


void updateNode(BinarySearchTree<string, WordItem> mytree, string & word,string doc )
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
void preProcess(string & filename)
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
          if(hasDigits(word) == false)
          {
                toUpper(word);
                if (exists(word)) // if the word has occured before
                    updateNode(mytree, word, filename);
                else // the word has never occured before
                {
                    WordItem toAdd;
                    toAdd.word = toUpper(word);
                    
                    DocumentItem doc;
                    doc.count = 1;
                    doc.documentName = filename;
                    vector<DocumentItem> wordvec;
                    wordvec.push_back(doc);
                    toAdd.list = wordvec;
                    mytree.insert(word,toAdd);
                    
                }
          }
            else
                ; // simply do nothing

        }
    }
}

int main()
{
    vector<string> files;
    vector<WordItem> toPrint;
    
    
    // Getting the number of documents to preprocess
    int nuDocuments;
    cout << "Enter number of input files:  ";
    cin >>nuDocuments;
    
    //Getting all the names of files to preprocess and adding it to files vector
    
    for (int i = 0; i < nuDocuments; i++)
    {
        string filename;
        cout << "Enter " << i+1 << ". file name:  ";
        cin >> filename;
        files.push_back(filename);
    }
    
    //Now,it's preprocessing time
    for (int i = 0; i<files.size(); i++)
    {
        string filename = files[i];
        preProcess(filename);
    }
    string querywords;
    cout << "Enter queried words in one line:   ";
    cin.ignore();
    getline(cin,querywords);
 
    
    istringstream iss2(querywords);
    string w;
    while(iss2 >> w) // need to find the words
    {
       toUpper(w);
        
        if (exists(w) == false) //
        {
            ; // do nothing
        }
        
        else // means the word exists in the tree we just need to access to its node
        {
            WordItem temp = mytree.getNode(w);// we have the all information we need right now
            toPrint.push_back(temp);
        }
    
    }
    
    for (int i = 0; i < toPrint.size(); i++)
    {
        cout << toPrint[i].word << "has occured ";
        for (int j = 0; j<toPrint[i].list.size(); j++)
        {
            cout << toPrint[i].list[j].count << " times" << endl;
        }
    }
    
    
    
  
    
    return 0;
}
