//
//  GBFS.h
//  TravelingSalesman_GBFS_h2
//
//  Created by Liza Girsova on 10/28/14.
//  Copyright (c) 2014 CMSC470. All rights reserved.
//

#ifndef TravelingSalesman_GBFS_h2_GBFS_h
#define TravelingSalesman_GBFS_h2_GBFS_h

#include <iostream>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <list>
#include <string>
#include "Domain.h"

using namespace std;

class GBFS{
public:
    priority_queue<Node, vector<Node*>, compareNode> queue;
    
    template<typename T, typename S, typename R>
    void runGBFS(T domain, S initialState, R goalState){ // Runs the GBFS algorithm
        int nodeCount = 0;
        int nodeExpansions = 0;
        Node rootNode = domain.createInitialState(initialState);
        list<Node> nodeStore;
        nodeStore.push_back(rootNode);  // Used to store the nodes so pointers don't go out of scope
        queue.push(&rootNode);
        nodeCount++;
        
        while(!(domain.goalState(queue.top(), goalState, rootNode))){  // Loops to add nodes to queue
            
            cout<<endl<<"Current Node Expansion: ";
            domain.printFinal(queue.top(), &rootNode);
            nodeExpansions++;
            
            list<Node> tempList; // Creates a temporary list that stores the children of Node
            list<Node>::iterator itr;
            tempList = domain.successorFn(queue.top(), &rootNode, nodeStore); // Returned list of children
            queue.top()->function = -100; // Used to make sure expanded node stays at top
            
            while(!tempList.empty()){   // Loops through list to push onto queue
                nodeStore.push_back(tempList.front());  // First adds nodes to list to keep pointers
                queue.push(&nodeStore.back());  // Adds nodes to queue through the nodeStore pointer
                nodeCount++;
                tempList.pop_front();
            }
            queue.pop();
        }
        cout<<endl<<"GOAL REACHED: ";
        domain.print(queue.top()->state);
        cout<<endl;
        cout<<"Nodes generated: "<< nodeCount<<endl;
        cout<<"Nodes expanded: "<<nodeExpansions<<endl;
        cout<<"Depth: "<<domain.getDepth(queue.top(), &rootNode)<<endl;
        cout<<"Path Cost: "<<domain.getPathCost(queue.top(), &rootNode)<<endl<<endl;
        domain.printFinal(queue.top(), &rootNode);
    }
};





#endif
