//
//  Domain.cpp
//  TravelingSalesman_GBFS_h2
//
//  Created by Liza Girsova on 10/28/14.
//  Copyright (c) 2014 CMSC470. All rights reserved.
//

#include "Domain.h"
#include <string>
#include <map>
#include <vector>

// Templated constructor for the node
template<typename T, typename S> Node::Node(T state, S function, int cost, Node* parent, bool root){
    Node::state = state;
    Node::function = function;
    Node::cost = cost;
    Node::parent = parent;
    Node::root = root;
}

// Determines possible children of currentNode and returns a list of these nodes
list<Node> Domain::successorFn(Node* currentNode, Node* rootNode, list<Node> nodeStore){
    list<Node> tempList;
    itr_low = currentCity.lower_bound(currentNode->state);
    itr_high = currentCity.upper_bound(currentNode->state);
    
    for(itr = itr_low; itr != itr_high; ++itr){ // Iterates through pairs to determine possibilites
        pair<string, int> tempPair((itr->first, (itr->second)));  // Used to find route options
        string possibleCity = tempPair.first;
        int newDistance = tempPair.second+currentNode->cost;    // Adds distance each time
        int function = getFunction(currentNode, rootNode, newDistance);
        Node tempNode(possibleCity, function, newDistance, currentNode, false); // Used to compare for duplicate
        if(!(checkDuplicates(&tempNode, rootNode))&&!checkCycles(&tempNode, rootNode)){
            tempList.push_back(tempNode);
        }
    }
    return tempList;
}

// Method that checks for potential oscillation between two states
bool Domain::checkDuplicates(Node* tempNode, Node* rootNode){
    Node* compareNode = tempNode;
    if(compareNode->state == compareNode->parent->parent->state)
        return true;
    else
        return false;
}

// Checks to see if there are any cycles
bool Domain::checkCycles(Node* tempNode, Node* rootNode){
    Node* compareNode = tempNode;
    int count = 0; // Used to keep track of how many times previously visited
    while(compareNode != rootNode->parent){
        if(previouslyVisited(compareNode,rootNode))
            count++;
        compareNode = compareNode->parent;
    }
    // Sets the limit of the no. of times a city can be visited to 3
    if(count>3)
        return true;
    else
        return false;
}

// Checks to see if a city has been previously visited. Returns true if visited previously.
bool Domain::previouslyVisited(Node* tempNode, Node* rootNode){
    Node* compareNode = tempNode;  // compareNode used to go through path to compare to potential node
    while(!compareNode->root){
        compareNode = compareNode->parent;
        if(tempNode->state == compareNode->state){
            return true;
        }
    }
    return false;
}

// Counts how many of the required cities have been visited.
int Domain::citiesVisited(Node* currentNode, Node* rootNode){
    Node* compareNode = currentNode;
    list<string>::iterator itr;
    int count = 0;
    
    // Automatically sets count to 1 when we are checking the rootNode
    if(compareNode->root){
        return 1;
    }
    
    // Iterates through the path to check how many of the required cities have been visited
    count = 1; 
    while(!compareNode->root){
        itr = allCities.begin();
        // Loops through list of required cities
        while(itr!=allCities.end()){
            // Checks if a required city has been visited
            // Increments count only if never visited previously
            if(compareNode->state == *itr && !previouslyVisited(compareNode, rootNode)){
                count++;
                break;
            }
            itr++;
        }
        compareNode = compareNode->parent;
    }
    return count;
}

// Used to print the state in the way that it is represented
void Domain::print(string state){
    cout<<state<<endl;
}

// Determines the path cost
int Domain::getPathCost(Node* currentNode, Node* rootNode){
    return currentNode->cost;
}

// Determines depth
int Domain::getDepth(Node* currentNode, Node* rootNode){
    int pathCount = 0;
    while(currentNode != rootNode->parent){
        currentNode = currentNode->parent;
        pathCount++;
    }
    return pathCount;
}


