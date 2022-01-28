// PROJECT IDENTIFIER: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD
#include "functions.h"
#include <getopt.h>
#include <iostream>
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
    while(cin.peek() == '#'){
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

            if(col < mapSize - 1){++col;} // incriment col until reaching end of a row
            else if(col >= mapSize - 1){col = 0; ++row;} // reset column and change to new row
        } //while
    } // if M

    //reading in map in coordinate form
    if(mapT == 'L'){
        char let;
        int row = 0;
        int col = 0;
        //int numElts = 0;
        // read in coordinates and symbols
        while(cin >> row >> col >> let){
            Location loc; //create new location
            loc.type = let;
            loc.x = row;
            loc.y = col;
            if(let == '@'){startLoc = loc;} // set start location

            map[row][col] = loc; // add location to map
            //++numElts;
        }//while
        /*if(numElts < mapSize*mapSize){
        for(int r = 0; r < mapSize; ++r){
            for(int c = 0; c < mapSize; ++c){
                if(map[r][c].type == 'I'){
                    map[r][c].type = '.';
                    map[r][c].x = r;
                    map[r][c].y = c;
                }//if
            }//for
        }//for
        }//if*/
    }//if L
}//create_map


bool TreasureHunt::cap_hunt(std::deque<Location> &search, std::deque<Location> &searchMate){
    bool foundT = false; // variable to track if treasure is found

    for(int i = 0; i < 4; ++i){
        char curD = huntOrder[i];
        Location newLoc;

        // check what direction to search
        if(curD == 'N'){
            newLoc = north(sailLocation, map); // call appropriate location grabber function
            // check that the newLoc is land
            if(newLoc.type == '.'){ 
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'N'; // add the direction travelled to find the location
                search.push_back(newLoc); // add the location to the captain deque
            }//if
            // check if the newLoc is land or treasure and hand the search off to the firstmate
            else if(newLoc.type == 'o' || newLoc.type == '$'){
                newLoc.dirT = 'N';
                newLoc.dis = true;
                map[newLoc.x][newLoc.y] = newLoc;
                foundT = fm_search(newLoc, searchMate);
                newLoc.dirT = foundT; // in the hitLand vector dirT says if treasure was found by fm
                if(vbose){print_verbose(newLoc, foundT);}
                ++numAshore;
            }//else if
        }//if N

        else if(curD == 'S'){
            newLoc = south(sailLocation, map);
            if(newLoc.type == '.'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'S'; // add the direction travelled to find the location
                search.push_back(newLoc);
            }//if
            else if(newLoc.type == 'o' || newLoc.type == '$'){
                newLoc.dirT = 'S';
                newLoc.dis = true;
                map[newLoc.x][newLoc.y] = newLoc;
                foundT = fm_search(newLoc, searchMate);
                newLoc.dirT = foundT; // in the hitLand vector dirT says if treasure was found by fm DELETE?
                if(vbose){print_verbose(newLoc, foundT);}
                ++numAshore;
            }//else if
        }//else if S

        else if(curD == 'E'){
            newLoc = east(sailLocation, map);
            if(newLoc.type == '.'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'E'; // add the direction travelled to find the location
                search.push_back(newLoc);
            }//if
            else if(newLoc.type == 'o' || newLoc.type == '$'){
                newLoc.dirT = 'E';
                newLoc.dis = true;
                map[newLoc.x][newLoc.y] = newLoc;
                foundT = fm_search(newLoc, searchMate);
                newLoc.dirT = foundT; // in the hitLand vector dirT says if treasure was found by fm
                if(vbose){print_verbose(newLoc, foundT);}
                ++numAshore;
            }//else if
        }//else if E

        else if(curD == 'W'){
            newLoc = west(sailLocation, map);
            if(newLoc.type == '.'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'W'; // add the direction travelled to find the location
                search.push_back(newLoc);
            }//if
            else if(newLoc.type == 'o' || newLoc.type == '$'){
                newLoc.dirT = 'W';
                newLoc.dis = true;
                map[newLoc.x][newLoc.y] = newLoc;
                foundT = fm_search(newLoc, searchMate);
                newLoc.dirT = foundT; // in the hitLand vector dirT says if treasure was found by fm
                if(vbose){print_verbose(newLoc, foundT);}
                ++numAshore;
            }//else if
        }//else if W
    }
    return foundT;
}


bool TreasureHunt::fm_hunt(std::deque<Location> &search){
    bool found = false;
    for(int i = 0; i < 4; ++i){
        char curD = huntOrder[i];
        Location newLoc;

        // check what direction to search
        if(curD == 'N'){
            newLoc = north(searchLocation, map); // call appropriate location grabber function
            // check that the newLoc is water or treasure
            if(newLoc.type == 'o' || newLoc.type == '$'){ 
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'N'; // add the direction travelled to find the location
                search.push_back(newLoc); // add the location to the first mate dequq
                if(newLoc.type == '$'){ return true;}
            }
        }

        else if(curD == 'S'){
            newLoc = south(searchLocation, map);
            if(newLoc.type == 'o' || newLoc.type == '$'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'S'; // add the direction travelled to find the location
                search.push_back(newLoc);
                if(newLoc.type == '$'){ return true;}
            }
        }

        else if(curD == 'E'){
            newLoc = east(searchLocation, map);
            if(newLoc.type == 'o' || newLoc.type == '$'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'E'; // add the direction travelled to find the location
                search.push_back(newLoc);
                if(newLoc.type == '$'){ return true;}
            }
        }

        else if(curD == 'W'){
            newLoc = west(searchLocation, map);
            if(newLoc.type == 'o' || newLoc.type == '$'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'W'; // add the direction travelled to find the location
                search.push_back(newLoc);
                if(newLoc.type == '$'){ return true;}
            }//if
        }//else if
    }
    return found;
}



void TreasureHunt::cap_search(){
    std::deque<Location> search;
    std::deque<Location> searchMate;
    if(vbose){cout << "Treasure hunt started at: " << startLoc.x << "," << startLoc.y << '\n';}
    bool foundT = false;
    // add start locaiton to deque
    startLoc.dis = true;
    search.push_back(startLoc);

    // while container not empty
    while(!search.empty() && !foundT){
        // set sailLocation to next location
        // if captain is a queue use front and pop front
        if(captain == "QUEUE"){
            sailLocation = search.front();
            search.pop_front();
            ++numWaterI;
        }
        //if captain is a stack use back and pop back
        else if(captain == "STACK"){
            sailLocation = search.back();
            search.pop_back();
            ++numWaterI;
        }
        // follow hunt order to add new locations
        foundT = cap_hunt(search, searchMate);
    }
    // hunt ended, report outcome
    if(vbose){
        if(treasureLoc.type != '$'){cout << "Treasure hunt failed" << '\n';}
    }
}

bool TreasureHunt::fm_search(const Location &landLoc, std::deque<Location> &search){
    //if(vbose){cout << "Searching island... ";}
    //std::deque<Location> search;
    bool foundT = false;
    bool tInHunt = false;
    search.push_back(landLoc);

    if(landLoc.type == '$'){
        ++numLandI;
        foundT = true;
        treasureLoc = search.back();
    }

    //check if container is empty
    while(!search.empty() && !foundT && !tInHunt){

        if(firstMate == "QUEUE"){
            /*if(tInHunt){
                ++numLandI;
                foundT = true;
                treasureLoc = mate.search.front();
                break;
            }//if*/
            searchLocation = search.front();
            search.pop_front();
            ++numLandI;
        }//if

        else if(firstMate == "STACK"){
            //check if back is treasure
            /*if(tInHunt){
                treasureLoc = mate.search.back();
                foundT = true;
                break;
            }//if*/
            searchLocation = search.back();
            search.pop_back();
            ++numLandI;
        }//else if

        tInHunt = fm_hunt(search);
        if(tInHunt){
            ++numLandI;
            foundT = true;
            treasureLoc = search.back();
        }
        
    }//while
    return foundT;
}

Back opposite_direction(char direction, Location loc){
    Back prevLoc;
    if(direction == 'N'){
        //backwards is south
        prevLoc.r = loc.x + 1;
        prevLoc.c = loc.y;
        //prevLoc.nextDir = 'S';
    }
    else if(direction == 'S'){
        //backwards is N
        prevLoc.r = loc.x - 1;
        prevLoc.c = loc.y;
        //prevLoc.nextDir = 'N';
    }
    else if(direction == 'E'){
        //backwards is  W
        prevLoc.r = loc.x;
        prevLoc.c = loc.y - 1;
        //prevLoc.nextDir = 'W';
    }
    else if(direction == 'W'){
        //backwards is E
        prevLoc.r = loc.x;
        prevLoc.c = loc.y + 1;
        //prevLoc.nextDir = 'E';
    }
    return prevLoc;
}

std::deque<Location> TreasureHunt::backtrace(){
    std::deque<Location> Path;
    if(treasureLoc.type == '$'){treasureLoc.type = 'X';}
    Location cur = treasureLoc;
    
    //map[treasureLoc.x][treasureLoc.y].type = 'X';
    Path.push_front(cur);
    

    while(!(cur.x == startLoc.x && cur.y == startLoc.y)){
        Back nextDirection = opposite_direction(cur.dirT, cur);
        Location next = map[nextDirection.r][nextDirection.c];
        Path.push_front(next);
        // we have our current Loc and next Loc
        if((cur.dirT == 'N' || cur.dirT == 'S') &&(next.dirT == 'N' || next.dirT == 'S')){
            map[next.x][next.y].type = '|';
        }
        else if((cur.dirT == 'N' || cur.dirT == 'S') &&(next.dirT == 'E' || next.dirT == 'W')){
            map[next.x][next.y].type = '+';
        }
        else if((cur.dirT == 'E' || cur.dirT == 'W') &&(next.dirT == 'E' || next.dirT == 'W')){
            map[next.x][next.y].type = '-';
        }
        else if((cur.dirT == 'E' || cur.dirT == 'W') &&(next.dirT == 'N' || next.dirT == 'S')){
            map[next.x][next.y].type = '+';
        }
        
        cur = next;
        ++pathLength;
    }
    //Path.push_front(startLoc);
    return Path;
}

void TreasureHunt::report(){
    //verbose called during search
    std::deque<Location> path = backtrace();
    if(stats){
        //call print_stats
        //backtrace();
        print_stats();
    }

    if(showP == "M" && treasureLoc.type == 'X'){
        //backtrace();
        print_show_pathM();
    }

    if(showP == "L" && treasureLoc.type == 'X'){
        //backtrace();
        print_show_pathL(path);
    }

    if(treasureLoc.type == '$' || treasureLoc.type == 'X'){
        cout << "Treasure found at " << treasureLoc.x << "," << treasureLoc.y;
        cout << " with path length " << pathLength << "." << '\n';
    }
    if(treasureLoc.type != '$' && treasureLoc.type != 'X'){
        cout << "No treasure found after investigating " << numLandI+numWaterI; //fixed
        cout << " locations." << '\n';
        
    }
}

void TreasureHunt::print_stats(){
    cout << "--- STATS ---" << '\n';

    cout << "Starting location: " << startLoc.x<< "," << startLoc.y<< '\n';
    cout << "Water locations investigated: " << numWaterI << '\n';
    cout << "Land locations investigated: " << numLandI << '\n';
    cout << "Went ashore: " << numAshore << '\n';

    if(treasureLoc.type == 'X'){
        cout << "Path length: " << pathLength << '\n';
        cout << "Treasure location: " << treasureLoc.x << "," << treasureLoc.y << '\n';
    }
    
    cout << "--- STATS ---" << '\n';
} 

void TreasureHunt::print_verbose(const Location &hitLand, bool found){

    cout << "Went ashore at: " << hitLand.x << "," << hitLand.y << '\n';
    cout << "Searching island... ";

    if(found){
        cout << "party found treasure at " << treasureLoc.x << "," << treasureLoc.y << "." << '\n';
    }
    else{
        cout << "party returned with no treasure." << '\n';
    }
    
}

void TreasureHunt::print_show_pathM(){
    map[treasureLoc.x][treasureLoc.y].type = 'X';
    for(size_t r = 0; r < map.size(); ++r){
        for(size_t c = 0; c < map.size(); ++c){
            cout << map[r][c].type;
        }
        cout << '\n';
    }
    
}

void TreasureHunt::print_show_pathL(std::deque<Location> &Path){
    cout << "Sail:"<< '\n';
    while(Path.front().type == '.' || Path.front().type == '@'){
       cout << Path.front().x << "," << Path.front().y << '\n';
       Path.pop_front();
    }
    cout << "Search:" << '\n';
    while(Path.front().type == 'o' || Path.front().type == 'X'){
       cout << Path.front().x << "," << Path.front().y << '\n';
       Path.pop_front();
    }
}