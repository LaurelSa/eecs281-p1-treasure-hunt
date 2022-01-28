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


Location north(const Location &current, vector<vector<Location>> &map){
    //int tempR;
    Location newLoc;
    newLoc.type = '#';
    if(current.x - 1 >= 0){
        int tempR = current.x - 1;
        Location validLoc = map[tempR][current.y];
        validLoc.dirT = 'N';
        if(!validLoc.dis){return validLoc;}
    }//if
    return newLoc;
}//north

Location south(const Location &current, vector<vector<Location>> &map){
    //row +1
    Location tempLoc;
    tempLoc.type = '#';
    size_t locX = current.x;
    if(locX != map.size() - 1){
        int tempR = current.x +1;
        Location validLoc = map[tempR][current.y];
        validLoc.dirT = 'S';
        if(!validLoc.dis){return validLoc;}//if
    }//if
    return tempLoc;
}//south

Location east(const Location &current, vector<vector<Location>> &map){
    //col +1
    Location tempLoc;
    tempLoc.type = '#'; // initialize it as invalid
    size_t locY = current.y;
    if(locY != map.size() - 1){
        int tempC = current.y +1;
        Location validLoc = map[current.x][tempC];
        validLoc.dirT = 'E';
        //returns the location if the column is valid and it hasn't already been discovered
        if(!validLoc.dis){return validLoc;} 
    }//if
    return tempLoc;
}//east

Location west(const Location &current, vector<vector<Location>> &map){
    Location tempLoc;
    tempLoc.type ='#';
    if(current.y - 1 >= 0 ){
        int tempC = current.y - 1;
        Location validLoc = map[current.x][tempC];
        validLoc.dirT = 'W';
        if(!validLoc.dis){return validLoc;}
    }
    return tempLoc;
}