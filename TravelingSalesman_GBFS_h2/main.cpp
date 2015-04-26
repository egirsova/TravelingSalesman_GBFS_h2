//
//  main.cpp
//  TravelingSalesman_GBFS_h2
//
//  Created by Liza Girsova on 10/28/14.
//  Copyright (c) 2014 CMSC470. All rights reserved.
//


#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include "Domain.h"
#include "GBFS.h"

using namespace std;

int main(int argc, const char * argv[])
{
    cout<<"Algorithm: Greedy Best-First Search"<<endl;
    cout<<"Domain: Traveling Salesman Problem"<<endl<<endl;
    cout<<"Enter starting location: ";
    string start;
    getline(cin, start);
    
    Domain d;
    GBFS newGBFS;
    newGBFS.runGBFS(d, start, start);
    
    return 0;
}




