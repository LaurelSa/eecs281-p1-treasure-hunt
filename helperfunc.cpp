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


Location north(int currentx, int currenty, vector<vector<Location>> &map){
    //int tempR;
    Location newLoc;
    newLoc.type = '#';
    if(currentx - 1 >= 0){
        int tempR = currentx - 1;
        Location validLoc = map[tempR][currenty];
        validLoc.dirT = 'N';
        if(!validLoc.dis){return validLoc;}
    }//if
    return newLoc;
}//north

Location south(int currentx, int currenty, vector<vector<Location>> &map){
    //row +1
    Location tempLoc;
    tempLoc.type = '#';
    size_t locX = currentx;
    if(locX != map.size() - 1){
        int tempR = currentx +1;
        Location validLoc = map[tempR][currenty];
        validLoc.dirT = 'S';
        if(!validLoc.dis){return validLoc;}//if
    }//if
    return tempLoc;
}//south

Location east(int currentx, int currenty, vector<vector<Location>> &map){
    //col +1
    Location tempLoc;
    tempLoc.type = '#'; // initialize it as invalid
    size_t locY = currenty;
    if(locY != map.size() - 1){
        int tempC = currenty +1;
        Location validLoc = map[currentx][tempC];
        validLoc.dirT = 'E';
        //returns the location if the column is valid and it hasn't already been discovered
        if(!validLoc.dis){return validLoc;} 
    }//if
    return tempLoc;
}//east

Location west(int currentx, int currenty, vector<vector<Location>> &map){
    Location tempLoc;
    tempLoc.type ='#';
    if(currenty - 1 >= 0 ){
        int tempC = currenty - 1;
        Location validLoc = map[currentx][tempC];
        validLoc.dirT = 'W';
        if(!validLoc.dis){return validLoc;}
    }
    return tempLoc;
}