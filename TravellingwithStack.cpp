//
//  main.cpp
//  artunsarioglu_cs300_hw1
//
//  Created by Artun on 10.07.2019.
//  Copyright © 2019 Artun. All rights reserved.
//

#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <string>
#include "stack.h"
#include "stack.cpp"

using namespace std;




// you are using 3 stacks instead just use 2 stacks
//xcor and ycor here is the coordinates that needs to be checked whether the salesman has ever been there
int main(){
    
    ifstream file;
    string filename;
    
    int current_x , current_y;
    
   // int temp = xCoords.top();
   // cout << temp;
    
    Stack<int> rode;
    coordinate<int> home;
    home.xCor = 0;
    home.yCor = 0;
    rode.push(home);
    
    cout << "Please enter filename: ";
    cin >> filename;
    
    
    file.open(filename.c_str()); // file is opened here
    string line;
    
    while (getline(file, line)) // get each line from the txt file
    {
        //cout << "top of the stack is now " << rode.top().xCor << rode.top().yCor << endl; # debugging purposes :)
        int xcor,ycor;
        
        istringstream iss(line);
        iss >> xcor >> ycor;
        
        bool flag = false;
        Stack<int> check_stack;
        check_stack.push(home);
        
        while(rode.top().xCor != 0 && rode.top().yCor != 0) // checking whether current coordinate has ever been visited before
        {
            coordinate<int> tmp;
            tmp.xCor = rode.top().xCor;
            tmp.yCor = rode.top().yCor;
            
            check_stack.push(tmp);
            rode.pop();
            
            if (rode.top().xCor == xcor && rode.top().yCor == ycor ) // if visited -> time travel back to that city (top is now that old city coordinates that we time travelled)
            {
                cout << "Time travel back to " << '(' << xcor << ',' << ycor << ')' << endl;
                flag = true;
                break;
            }
        }
        
        while(check_stack.top().xCor != 0 && check_stack.top().yCor != 0 && flag == false) // fill the main stack not the memo one
        {
            coordinate<int> tmp2;
            tmp2.xCor = check_stack.top().xCor;
            tmp2.yCor = check_stack.top().yCor;
            
            rode.push(tmp2);
            check_stack.pop();
        }
        
        while (flag == true) // empty the memo stack for reuse operations
        {
            if(check_stack.top().xCor == 0 && check_stack.top().yCor ==0)
                break;
            check_stack.pop();
        }
        
       
        if(!flag) // if traveller hasnt been that city before we simply go to that city(coordinate)
        {
        
            cout << "Moving to " << '(' << xcor << ',' << ycor  << ')' << endl;
            
              current_x = rode.top().xCor;
              current_y = rode.top().yCor;
            
            while(current_x < xcor) // directing to right x coordinate
            {
                
                coordinate<int> temp;
                temp.xCor = rode.top().xCor + 1;
                temp.yCor = rode.top().yCor;
                
                rode.push(temp);
                cout << '(' << rode.top().xCor << ',' << rode.top().yCor << ')' << endl;
                
                current_x++;
            }
            
            while(current_x > xcor) // directing to right x coordinate
            {
                 coordinate<int> temp;
                 temp.xCor = current_x - 1;
                 temp.yCor = current_y;
                
                rode.push(temp);
              
               
                cout << '(' << rode.top().xCor << ',' << rode.top().yCor << ')' << endl;
                
                current_x--;
            }
            
            while(current_y < ycor) // directing to right y coordinate
            {
                coordinate<int> temp2;
                temp2.xCor = current_x;
                temp2.yCor = current_y+1;
                
                rode.push(temp2);
                
                if(current_y+1 == ycor)
                    break;
                cout << '(' << rode.top().xCor << ',' << rode.top().yCor << ')' << endl;
                
                current_y++;
            }
            
            while(current_y > ycor)  // directing to right y coordinate
            {
                  coordinate<int> temp2;
                 temp2.xCor = current_x;
                 temp2.yCor = current_y-1;
                
                rode.push(temp2);
                
                if (current_y -1 == ycor) {
                    break;
                }
                cout << '(' << rode.top().xCor << ',' << rode.top().yCor << ')' << endl;
                
                current_y--;
            }
            cout << "Arrived to " << '(' << xcor << ',' << ycor  << ')' << endl;
        }
        
        else // time travel is happening here :)
        {
            while (rode.top().xCor != xcor && rode.top().yCor != ycor)
            {
                rode.pop();
            }
        }
    }
    
    cout << "Back to (0,0)" << endl;
    
    while(rode.top().xCor != 0) // back home coordinates
    {
         rode.pop();
         cout << '(' << rode.top().xCor << ',' << rode.top().yCor << ')' << endl;
    }
    
    cout << "Home sweet home" << endl;

    return 0;
}

