// Project Identifier: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD

#include <getopt.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include "functions.h"

using namespace std;


int main(int argc, char ** argv){
    ios_base::sync_with_stdio(false);

    TreasureHunt myHunt;

    myHunt.get_options(argc, argv);

}//main



void TreasureHunt::get_options(int argc, char** argv){
    //bool modeSpecified = false;
    int option = 0;
    opterr = false;
    int option_index = 0;

    struct option long_options[]{
        {"help", no_argument, nullptr, 'h'},
        {"captain", required_argument, nullptr, 'c'},
        {"first-mate", required_argument, nullptr, 'f'},
        {"hunt-order", required_argument, nullptr, 'o'},
        {"verbose", no_argument, nullptr, 'v'},
        {"stats", no_argument, nullptr, 's'},
        {"show-path", required_argument, nullptr, 'p'},
        {nullptr, 0, nullptr, '\0'}
    };

    while((option = getopt_long(argc, argv, "hc:f:o:vsp:", long_options, &option_index)) != -1){
        switch(option){
        case 'h':
            //TODO
            break;
        case 'c':
            captain = optarg;
            break;
        
        case 'f':
            firstMate = optarg;
            break;
        
        case 'o':
            huntOrder = std::string(optarg);
            break;

        case 'v':
            vbose = true;
            break;

        case 's':
            stats = true;
            break;

        case 'p':
            showP = optarg;
            break;

        default:
            huntOrder = "NESW";
            captain = "STACK";
            firstMate = "QUEUE";
        
        }//switch
    }//while

    /*if(!something){
        set hunt order and all that to default
    }*/

}//getMode


void TreasureHunt::run(){
    // put the functions that do command line stuff
}

