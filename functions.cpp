#include "functions.h"
#include <getopt.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <stdio.h>
#include <stdbool.h>

using namespace std;


void TreasureHunt::create_map(){
    int mapSize;
    char mapT; 
    char next;
    string line;
    while(cin.peek()== '#'){
        getline(cin, line);
    }
    cin >> mapT >> mapSize;

    Location loc;

    //vector< vector<Location> > map(mapSize, vector<Location>(mapSize, loc));
    map.resize(mapSize, vector<Location>(mapSize));
    

    if(mapT == 'M'){
        char let;
        int row = 0;
        int col = 0;
        while(cin >> let){
            Location loc;
            loc.type = let;
            loc.x = row;
            loc.y = col;
            if(let == '@'){startLoc = loc;}
            map[row][col] = loc;


            if(col < mapSize){++col;}
            else if(col >= mapSize){col = 0; ++row;}
        } //while
    } // if M


    if(mapT == 'L'){
        char let;
        int row = 0;
        int col = 0;
        while(cin >> row >> col >> let){
            Location loc;
            loc.type = let;
            loc.x = row;
            loc.y = col;

            if(let == '@'){startLoc = loc;}

            map[row][col] = loc;
        }//while
    }//if L
   
}//create_map



// Runs through the search order and adds any valid lcoations to the container
// valid with both captain and first mate, only ever need to push in this function
// locType: 'o' for captain | '.' for fm
// container: search container for cap or mate
// cur: sailLocation (if captain) | searchLocation (if fm)
void TreasureHunt::hunt(char locType, deque<Location> &container, Location cur){
    for(int i = 0; i < 4; ++i){
        char curD = huntOrder[i];
        Location newLoc;
        
        if(curD == 'N'){
            newLoc = north(cur, map);
            if(newLoc.type == locType){ // if the location type looking for and newLoc type match, add to container
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'N'; // add the direction travelled to find the location
                container.push_back(newLoc);
            }//if
            // if types don't match and we are in captain hunt but discovered land, launch a fm search
            else if(newLoc.type != locType && locType == 'o' && newLoc.type == '.'){
                fm_search();
            }//else if
        }//if N

        if(curD =='S'){
            newLoc = south(cur, map);
            if(newLoc.type == locType){
                map[newLoc.x][newLoc.y].dis = true;
                map[newLoc.x][newLoc.y].dirT = 'S';
                container.push_back(newLoc);
            }//if
            else if(newLoc.type != locType && locType == 'o' && newLoc.type == '.'){
                fm_search();
            }//else if
        }//if S

        if(curD == 'E'){
            newLoc = east(cur, map);
            if(newLoc.type == locType){
                map[newLoc.x][newLoc.y].dis = true;
                map[newLoc.x][newLoc.y].dirT = 'E';
                container.push_back(newLoc);
            }//if
            else if(newLoc.type != locType && locType == 'o' && newLoc.type == '.'){
                fm_search();
            }//else if
        }//if E

        if(curD == 'W'){
            newLoc = west(cur, map);
            if(newLoc.type == locType){
                map[newLoc.x][newLoc.y].dis = true; 
                map[newLoc.x][newLoc.y].dirT = 'W';
                container.push_back(newLoc);
            }//if
            else if(newLoc.type != locType && locType == 'o' && newLoc.type == '.'){
                fm_search();
            }//else if
        }//if W
    }//for
}


void TreasureHunt::cap_search(){
    // add start locaiton to deque
    cap.search.push_back(startLoc);

    // while container not empty
    while(!cap.search.empty()){
        // set sailLocation to next location
        // if captain is a queue use front and pop front
        if(captain== "QUEUE"){
            cap.sailLocation = cap.search.front();
            cap.search.pop_front();
        }
        //if captain is a stack use back and pop back
        else if(captain == "STACK"){
            cap.sailLocation = cap.search.back();
            cap.search.pop_back();
        }
        // follow hunt order to add new locations
        hunt('o', cap.search, cap.sailLocation);
    }
    // hunt ended, report outcome



}

void TreasureHunt::fm_search(){
    //cap.search.

    // queue funcitonality for FM
    if(firstMate == "QUEUE"){

    }  

    // stack functionality for FM
    else{

    }



}

