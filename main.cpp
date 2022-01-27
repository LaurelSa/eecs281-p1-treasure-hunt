// Project Identifier: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD

#include <getopt.h>
#include <iostream>
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

    myHunt.create_map();

    myHunt.cap_search();

    myHunt.report();



}//main

void print_help(){
    cout << "This program searches for treasure from a file\n"
         << "Usage: \'./hunt\n\t [--captain | -c] <STACK | QUEUE>\n"
         <<                 "\t[--first-mate | -f] <STACK | QUEUE>\n"
         <<                 "\t[--hunt-order | -o] <string inlcuding N, E, S, W>\n"
         <<                 "\t[--verbose | -v]\n" 
         <<                 "\t[--stats | -s]\n" 
         <<                 "\t[--show-path| -p] <M | L>\n" 
         <<                 "\t[--help | -h]\n" 
         <<endl;
}


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
            print_help();
            exit(0);
            break;
        case 'c':
            captain = optarg;
            if(optarg == nullptr){
                captain = "STACK";
            }
            else if(captain != "STACK" && captain != "QUEUE"){
                cerr << "Invalid argument to --captain" << endl;  // personal debug
                exit(1);
            }
            break;
        
        case 'f':
            firstMate = optarg;
            if(optarg == nullptr){
                firstMate = "QUEUE";
            }
            else if(firstMate != "STACK" && firstMate != "QUEUE"){
                cerr << "Invalid argument to --first-mate" << endl;  // personal debug
                exit(1);
            }
            break;
        
        case 'o':
            huntOrder = optarg;
            if(optarg == nullptr){
                huntOrder = "NESW";
            }
            else if(huntOrder.length() != 4){
                cerr << "Invalid argument to --hunt-order" << endl;  // personal debug
                exit(1);
            }
            else{
                long int numN = count(huntOrder.begin(), huntOrder.end(), 'N');
                long int numS = count(huntOrder.begin(), huntOrder.end(), 'S');
                long int numE = count(huntOrder.begin(), huntOrder.end(), 'E');
                long int numW = count(huntOrder.begin(), huntOrder.end(), 'W');
                if(numN > 1 || numS > 1 || numE > 1 || numW >1){
                    cerr << "Invalid argument to --hunt-order" << endl;  // personal debug
                    exit(1);
                }
            }
            break;

        case 'v':
            vbose = true;
            break;

        case 's':
            stats = true;
            break;

        case 'p':
            if(showP == 'M' || showP == 'L'){
                cerr << "Specify --show-path only once" << endl;  // personal debug
                exit(1);
            }
            showP = *optarg;
            if(showP != 'M' && showP != 'L'){
                //cout << showP;
                cerr << "Invalid argument to --show-path" << endl;  // personal debug
                
                exit(1);
            }
            break;

        default:
            cerr << "Unknown option" << endl;  // personal debug
                exit(1);
        }//switch

    }//while

    /*if(!something){
        set hunt order and all that to default
    }*/

}//getMode


void TreasureHunt::run(){
    // put the functions that do command line stuff
}

