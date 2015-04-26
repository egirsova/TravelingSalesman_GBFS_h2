//
//  Domain.h
//  TravelingSalesman_GBFS_h2
//
//  Created by Liza Girsova on 10/28/14.
//  Copyright (c) 2014 CMSC470. All rights reserved.
//

#ifndef __TravelingSalesman_GBFS_h2__Domain__
#define __TravelingSalesman_GBFS_h2__Domain__

#include <iostream>
#include <map>
#include <string>
#include <list>

using namespace std;

class Node
{
public:
    string state;
    int cost;
    int function;
    bool root;
    Node* parent;
    template<typename T, typename S> Node(T state, S function, int cost, Node *parent, bool root);
};

// Used to compare the nodes to enter into priority queue
class compareNode
{
public:
    // Overides the operator ()
    bool operator() (const Node* node1, const Node* node2) const
    {
        return node1->function > node2->function;
    }
};

class Domain
{
public:
    //Key: current city. T: pair that consists of the potential city name (to travel to) and distance
    typedef multimap<string, pair<string,int>> CityMap;
    CityMap currentCity;
    CityMap::iterator itr, itr_low, itr_high;
    list<string> allCities;
    
    // Creates the initial state. Adds all potential routes and distances. Returns the initial state.
    template<typename T>
    Node createInitialState(T startState){
        currentCity.insert(make_pair("Oradea", make_pair("Zerind", 71)));
        currentCity.insert(make_pair("Oradea", make_pair("Sibiu", 151)));
        currentCity.insert(make_pair("Zerind", make_pair("Oradea", 71)));
        currentCity.insert(make_pair("Zerind", make_pair("Arad", 75)));
        currentCity.insert(make_pair("Arad", make_pair("Zerind", 75)));
        currentCity.insert(make_pair("Arad", make_pair("Sibiu", 140)));
        currentCity.insert(make_pair("Arad", make_pair("Timisoara", 118)));
        currentCity.insert(make_pair("Timisoara", make_pair("Arad", 118)));
        currentCity.insert(make_pair("Timisoara", make_pair("Lugoj", 111)));
        currentCity.insert(make_pair("Lugoj", make_pair("Timisoara", 111)));
        currentCity.insert(make_pair("Lugoj", make_pair("Mehadia", 70)));
        currentCity.insert(make_pair("Mehadia", make_pair("Lugoj", 70)));
        currentCity.insert(make_pair("Mehadia", make_pair("Drobeta", 75)));
        currentCity.insert(make_pair("Drobeta", make_pair("Mehadia", 75)));
        currentCity.insert(make_pair("Drobeta", make_pair("Craiova", 120)));
        currentCity.insert(make_pair("Craiova", make_pair("Drobeta", 120)));
        currentCity.insert(make_pair("Craiova", make_pair("Rimnicu Vilcea", 146)));
        currentCity.insert(make_pair("Craiova", make_pair("Pitesti", 138)));
        currentCity.insert(make_pair("Rimnicu Vilcea", make_pair("Craiova", 146)));
        currentCity.insert(make_pair("Rimnicu Vilcea", make_pair("Pitesti", 97)));
        currentCity.insert(make_pair("Rimnicu Vilcea", make_pair("Sibiu", 80)));
        currentCity.insert(make_pair("Sibiu", make_pair("Rimnicu Vilcea", 80)));
        currentCity.insert(make_pair("Sibiu", make_pair("Arad", 140)));
        currentCity.insert(make_pair("Sibiu", make_pair("Oradea", 151)));
        currentCity.insert(make_pair("Sibiu", make_pair("Fagaras", 99)));
        currentCity.insert(make_pair("Fagaras", make_pair("Sibiu", 99)));
        currentCity.insert(make_pair("Fagaras", make_pair("Bucharest", 211)));
        currentCity.insert(make_pair("Pitesti", make_pair("Rimnicu Vilcea", 97)));
        currentCity.insert(make_pair("Pitesti", make_pair("Craiova", 138)));
        currentCity.insert(make_pair("Pitesti", make_pair("Bucharest", 101)));
        currentCity.insert(make_pair("Bucharest", make_pair("Pitesti", 101)));
        currentCity.insert(make_pair("Bucharest", make_pair("Fagaras", 211)));
        
        // Creates a list of all of the cities that need to be visited
        allCities.push_back("Oradea");
        allCities.push_back("Zerind");
        allCities.push_back("Arad");
        allCities.push_back("Timisoara");
        allCities.push_back("Lugoj");
        allCities.push_back("Mehadia");
        allCities.push_back("Drobeta");
        allCities.push_back("Craiova");
        allCities.push_back("Rimnicu Vilcea");
        allCities.push_back("Sibiu");
        allCities.push_back("Fagaras");
        allCities.push_back("Pitesti");
        allCities.push_back("Bucharest");
        
        // Creates rootNode
        Node tempRootNode(startState, 0, 0, nullptr, true);
        Node* rootPointer = &tempRootNode;
        Node rootNode = *new Node(startState, 0, 0, rootPointer, true);
        return rootNode;
    }
    
    // Calculates the heuristic
    template<typename T, typename S>
    int getHeuristic(T tempNode, S rootNode){
        int totalCities = allCities.size(); // No. of cities that need to be visited
        int citiesVisitedOnce = citiesVisited(tempNode, rootNode); // No. of required cities visited
        int totalCitiesVisited = getDepth(tempNode, rootNode);  // Total number of cities visited
        int citiesLeft = totalCities + totalCitiesVisited - citiesVisitedOnce;
        // Returns how many cities we still have to visit + number of cities "overvisited"
        return citiesLeft;
    }
    
    // Calculates the function f(n) = h(n)
    template<typename T, typename S>
    int getFunction(T tempNode, S rootNode, int cost){
        int function = getHeuristic(tempNode, rootNode);
        return function;
    }
    
    // Prints the final solution/goal in a user-friendly way
    template <typename T, typename S>
    void printFinal(T currentNode, S rootNode){
        cout<<"Path: "<<endl;
        list<string> path;
        list<string>::iterator itr;
        while(currentNode != rootNode->parent){
            path.push_front(currentNode->state);
            currentNode = currentNode->parent;
        }
        for(itr = path.begin(); itr != path.end(); ++itr){
            cout<<*itr<<endl;
        }
    }
    
    // Checks for goalState
    template<typename T, typename S, typename R>
    bool goalState(T currentNode, S goalState, R rootNode){
        list<string> path;
        list<string>::iterator itr;
        Node* compareNode = currentNode;
        while(compareNode != rootNode.parent){
            path.push_front(compareNode->state);
            compareNode = compareNode->parent;
        }
        if(citiesVisited(currentNode, &rootNode) == allCities.size() && path.front()==path.back() && path.size()>1)
            return true;
        else
            return false;
    }
    
    // Remaining methods that are not templated
    list<Node> successorFn(Node* currentNode, Node* rootNode, list<Node> nodeStore);
    bool checkDuplicates(Node* tempNode, Node* parent);
    bool checkCycles(Node* tempNode, Node* rootNode);
    bool previouslyVisited(Node* tempNode, Node* rootNode);
    void print(string state);
    int getDepth(Node* currentNode, Node* rootNode);
    int getPathCost(Node* currentNode, Node* rootNode);
    int count(Node* currentNode, Node* rootNode);
    int citiesVisited(Node* currentNode, Node* rootNode);
    
};


#endif /* defined(__TravelingSalesman_GBFS_h2__Domain__) */
