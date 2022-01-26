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
    //char next;
    string line;

    //check for comment on the first line
    while(cin.peek()== '#'){
        getline(cin, line); //read the comment into junk
    }//while

    //read in the mapType and mapSize
    cin >> mapT >> mapSize;

    //Location loc;

    // resize TreasureHunt::map based on size
    map.resize(mapSize, vector<Location>(mapSize));
    
    // reading in map in grid form
    if(mapT == 'M'){
        // initialize variable for location struct
        char let;
        int row = 0;
        int col = 0;
        // read in all the char in map grid
        while(cin >> let){
            Location loc; // create and modify a location
            loc.type = let;
            loc.x = row;
            loc.y = col;
        
            if(let == '@'){startLoc = loc;} // set start location
            map[row][col] = loc; // add location to map

            if(col < mapSize){++col;} // incriment col until reaching end of a row
            else if(col >= mapSize){col = 0; ++row;} // reset column and change to new row
        } //while
    } // if M

    //reading in map in coordinate form
    if(mapT == 'L'){
        char let;
        int row = 0;
        int col = 0;
        // read in coordinates and symbols
        while(cin >> row >> col >> let){
            Location loc; //create new location
            loc.type = let;
            loc.x = row;
            loc.y = col;
            if(let == '@'){startLoc = loc;} // set start location

            map[row][col] = loc; // add location to map
        }//while
    }//if L
}//create_map


bool TreasureHunt::cap_hunt(){
    bool foundT = false; // variable to track if treasure is found

    for(int i = 0; i < 4; ++i){
        char curD = huntOrder[i];
        Location newLoc;

        // check what direction to search
        if(curD == 'N'){
            newLoc = north(cap.sailLocation, map); // call appropriate location grabber function
            // check that the newLoc is land
            if(newLoc.type == 'o'){ 
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'N'; // add the direction travelled to find the location
                cap.search.push_back(newLoc); // add the location to the captain deque
            }//if
            // check if the newLoc is land or treasure and hand the search off to the firstmate
            else if(newLoc.type == '.' || newLoc.type == '$'){
                foundT = fm_search(newLoc);
                newLoc.dirT = foundT; // in the hitLand vector dirT says if treasure was found by fm
                hitLand.push_back(newLoc);
                ++numAshore;
            }//else if
        }//if N

        else if(curD == 'S'){
            newLoc = south(cap.sailLocation, map);
            if(newLoc.type == 'o'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'S'; // add the direction travelled to find the location
                cap.search.push_back(newLoc);
            }//if
            else if(newLoc.type == '.' || newLoc.type == '$'){
               foundT = fm_search(newLoc);
                newLoc.dirT = foundT; // in the hitLand vector dirT says if treasure was found by fm
                hitLand.push_back(newLoc);
                ++numAshore;
            }//else if
        }//else if S

        else if(curD == 'E'){
            newLoc = east(cap.sailLocation, map);
            if(newLoc.type == 'o'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'E'; // add the direction travelled to find the location
                cap.search.push_back(newLoc);
            }//if
            else if(newLoc.type == '.' || newLoc.type == '$'){
                foundT = fm_search(newLoc);
                newLoc.dirT = foundT; // in the hitLand vector dirT says if treasure was found by fm
                hitLand.push_back(newLoc);
                ++numAshore;
            }//else if
        }//else if E

        else if(curD == 'W'){
            newLoc = west(cap.sailLocation, map);
            if(newLoc.type == 'o'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'W'; // add the direction travelled to find the location
                cap.search.push_back(newLoc);
            }//if
            else if(newLoc.type == '.' || newLoc.type == '$'){
                foundT = fm_search(newLoc);
                newLoc.dirT = foundT; // in the hitLand vector dirT says if treasure was found by fm
                hitLand.push_back(newLoc);
                ++numAshore;
            }//else if
        }//else if W
    }
    return foundT;
}


void TreasureHunt::fm_hunt(){
    for(int i = 0; i < 4; ++i){
        char curD = huntOrder[i];
        Location newLoc;

        // check what direction to search
        if(curD == 'N'){
            newLoc = north(mate.searchLocation, map); // call appropriate location grabber function
            // check that the newLoc is water or treasure
            if(newLoc.type == '.' || newLoc.type == '$'){ 
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'N'; // add the direction travelled to find the location
                mate.search.push_back(newLoc); // add the location to the first mate dequq
            }
        }

        else if(curD == 'S'){
            newLoc = south(mate.searchLocation, map);
            if(newLoc.type == '.' || newLoc.type == '$'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'S'; // add the direction travelled to find the location
                mate.search.push_back(newLoc);
            }
        }

        else if(curD == 'E'){
            newLoc = east(mate.searchLocation, map);
            if(newLoc.type == '.' || newLoc.type == '$'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'E'; // add the direction travelled to find the location
                mate.search.push_back(newLoc);
            }
        }

        else if(curD == 'W'){
            newLoc = west(mate.searchLocation, map);
            if(newLoc.type == '.' || newLoc.type == '$'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'W'; // add the direction travelled to find the location
                mate.search.push_back(newLoc);
            }//if
        }//else if
    }
}



void TreasureHunt::cap_search(){
    bool foundT = false;
    // add start locaiton to deque
    startLoc.dis = true;
    cap.search.push_back(startLoc);

    // while container not empty
    while(!cap.search.empty() && !foundT){
        // set sailLocation to next location
        // if captain is a queue use front and pop front
        if(captain== "QUEUE"){
            cap.sailLocation = cap.search.front();
            cap.search.pop_front();
            ++numWaterI;
        }
        //if captain is a stack use back and pop back
        else if(captain == "STACK"){
            cap.sailLocation = cap.search.back();
            cap.search.pop_back();
            ++numWaterI;
        }
        // follow hunt order to add new locations
        foundT = cap_hunt();
    }
    // hunt ended, report outcome
}

bool TreasureHunt::fm_search(Location landLoc){
    bool foundT = false;
    mate.search.push_back(landLoc);

    //check if container is empty
    while(!mate.search.empty() && !foundT){

        if(firstMate == "QUEUE"){
            if(mate.search.front().type == '$'){
                foundT = true;
                treasureLoc = mate.search.front();
                break;
            }//if
            mate.searchLocation = mate.search.front();
            mate.search.pop_front();
            ++numLandI;
        }//if

        else if(firstMate == "STACK"){
            //check if back is treasure
            if(mate.search.back().type == '$'){
                treasureLoc = mate.search.back();
                foundT = true;
                break;
            }//if
            mate.searchLocation = mate.search.back();
            mate.search.pop_back();
            ++numLandI;
        }//else if

        fm_hunt();
        
    }//while
    return foundT;
}

Back opposite_direction(char direction, Location loc){
    Back prevLoc;
    if(direction == 'N'){
        //backwards is south
        prevLoc.r = loc.x - 1;
        prevLoc.c = loc.y;
        prevLoc.nextDir = 'S';
    }
    else if(direction == 'S'){
        //backwards is N
        prevLoc.r = loc.x + 1;
        prevLoc.c = loc.y;
        prevLoc.nextDir = 'N';
    }
    else if(direction == 'E'){
        //backwards is  W
        prevLoc.r = loc.x;
        prevLoc.c = loc.y - 1;
        prevLoc.nextDir = 'W';
    }
    else if(direction == 'W'){
        //backwards is E
        prevLoc.r = loc.x;
        prevLoc.c = loc.y + 1;
        prevLoc.nextDir = 'E';
    }
    return prevLoc;
}

void TreasureHunt::backtrace(){
    int row = treasureLoc.x;
    int col = treasureLoc.y;
    char disDirection = treasureLoc.dirT;
    

    Location cur = treasureLoc;

    while(cur.x != startLoc.x && cur.y != startLoc.y){
        Back nextDirection = opposite_direction(disDirection, cur);
        Location next = map[nextDirection.r][nextDirection.c];
        // we have our current Loc and next Loc
        if((cur.dirT == 'N' || cur.dirT == 'S') &&(next.dirT == 'N' || next.dirT == 'S')){
            
        }
    }


}

void report(){

}
