#include "DLL.h"
#include <iostream>
#include <string>
using namespace std;

// default constructor is already implemented
// do not modify the default constructor
DLL::DLL(){
    headPtr = nullptr;
    itemCount=0;
}

// return the head pointer of the list
// it is already implemented, do not modify it
Node* DLL::getHeadPtr(){
    return headPtr;
}

// copy construct, which copies an existing list n
// the new list is a different object from n
// the new list and object n have the same contents
// Please implement it
DLL::DLL(DLL& n){
    if (n.headPtr == nullptr){
        headPtr = nullptr;
    }
    else {
        //initialize the first node of the new list, giving it the same values as the first node of n
        headPtr = new Node();
        headPtr->ssn = n.headPtr->ssn;
        headPtr->name = n.headPtr->name;
        headPtr->succ = n.headPtr->succ;
        headPtr->pred = n.headPtr->pred;

        //create a temp for the second value in n
        Node* tempN = n.headPtr->succ;

        //create a temp for the first value in the new list
        Node* temp = headPtr;

        //while the end of the list n hasn't been reached
        while (tempN != nullptr){
            //create the next node in the new list and initialize it's values to the corresponding ones of the node in list n
            temp->succ = new Node();
            (temp->succ)->ssn = tempN->ssn;
            (temp->succ)->name = tempN->name;
            (temp->succ)->succ = tempN->succ;
            (temp->succ)->pred = tempN->pred;
            
            //move on to the next node in each list
            temp = temp->succ;
            tempN = tempN->succ;
        }
    }
}

// destructor
// release every node of the list
// Please implement it
DLL::~DLL(){
    //set a temp value to head then make head null to remove that connection
    Node* curr = headPtr;
    headPtr = nullptr;

    //for each of the rest of the list values, store their next value and delete them
    while (curr != nullptr){
        Node* next = curr->succ;
        delete curr;
        curr = next;
    }
}

// if some node has SSN matcthes string ss
// return the index value of the node
// the index value of the first node is 0, the second node is 1, etc.
// if there is node matching ss, return -1
int DLL::search(string ss)const{
    //case if list is empty
    if (headPtr == nullptr){
        return -1;
    }

    //if not, search the list to find a matching ssn
    else {
        Node* temp = headPtr;
        int nodeCount = 0;
        while (temp->ssn.compare(ss) < 0 && temp->succ != nullptr){
            temp = temp->succ;
            nodeCount++;
        }

        //if the last node checked before ssn was too big has the ssn, say where
        if (temp->ssn.compare(ss) == 0){
            return nodeCount;
        }
    }
    //if no match found, return invalid location
    return -1;
}

// insert (ss, name) to the existing list
// the SSN values are each node are organized in INCREASING order
// if there is a node matching ss value, return false; otherwise true
// else create a node with (ss, name), insert the node to the proper position
// parameter count is the counter of number of valid insertion
// when you implement this method, consider the following situations:
// 1. list is empty
// 2. node should be inserted to the beginning of the list
// 3. node should be inserted to the middle of the list
// 4. node should be inserted to the end of the list
bool DLL::insert(string ss, string name, int & count){
    //case if list is empty
    if (headPtr == nullptr){
        headPtr = new Node();
        headPtr->ssn = ss;
        headPtr->name = name;
        count++;
        itemCount++;
        return true;
    }
    
    //search for appropriate location in ordered list to put new node
    Node* temp = headPtr;
    while (temp->succ != nullptr && (temp->succ)->ssn.compare(ss) <= 0){
        temp = temp->succ;
    }
    
    //if the value stopped at has the same ssn, not valid insert
    if (temp->ssn.compare(ss) == 0){
        return false;
    }

    //initialize new node's data since insert is valid
    Node* newPerson = new Node();
    newPerson->ssn = ss;
    newPerson->name = name;

    //case if inserted to beginning of list
    if (headPtr->ssn.compare(ss) > 0){
        newPerson->succ = headPtr;
        (newPerson->succ)->pred = newPerson;
        headPtr = newPerson;
        count++;
        itemCount++;
        return true;
    }

    //case if inserted to end of list
    if (temp->succ == nullptr){
        newPerson->pred = temp;
        temp->succ = newPerson;
        count++;
        itemCount++;
        return true;
    }

    //case if inserted to middle of list
    else {
        newPerson->succ = temp->succ;
        (newPerson->succ)->pred = newPerson;
        temp->succ = newPerson;
        newPerson->pred = temp;
        count++;
        itemCount++;
        return true;
    }
}

// remove node containing ss value
// if there is no node containing ss, return false; otherwise true
// consider the following situations:
// 1. list is empty
// 2. node containing ss value is the first node
// 3. node containing ss value is in the middle of the list
// 4. node containing ss value is the last node of the list
bool DLL::remove(string ss, int &count){
    //case if list is empty
    if (headPtr == nullptr){
        return false;
    }
    //initialize temp to search list
    Node* nodeDel = headPtr;

    //case if it's the first node
    if (headPtr->ssn.compare(ss) == 0){
        headPtr = nodeDel->succ;
        (nodeDel->succ)->pred = nullptr;
        nodeDel->succ = nullptr;
        delete nodeDel;
        count++;
        itemCount--;
        return true;
    }

    //search for the ssn if not first node
    while (nodeDel->succ != nullptr && (nodeDel->succ)->ssn.compare(ss) <= 0) {
        nodeDel = nodeDel->succ;
    }

    //case if it's the last node
    if (nodeDel->succ == nullptr && nodeDel->ssn.compare(ss) == 0){
        (nodeDel->pred)->succ = nullptr;
        nodeDel->pred = nullptr;
        delete nodeDel;
        count++;
        itemCount--;
        return true;
    }

    //case if it's a middle node
    if (nodeDel->ssn.compare(ss) == 0){
        (nodeDel->succ)->pred = nodeDel->pred;
        (nodeDel->pred)->succ = nodeDel->succ;
        delete nodeDel;
        count++;
        itemCount--;
        return true;
    }

    //if there is no ssn matching, return delete not valid
    return false;
}

// return the number of the nodes
// it is already implemented, do not modify it
int DLL::size(){
    return itemCount;
}

// iterate through each node
// print out SSN and memory address of each node
// do not modify this method
void DLL::display(){
    Node* temp;
    temp = headPtr;
    while (temp != nullptr) {
        cout << temp->ssn << "\t" << temp << endl;
        temp = temp->succ;
    }
}