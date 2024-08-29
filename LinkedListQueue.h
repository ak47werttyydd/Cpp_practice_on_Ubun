//
// Created by ruochen on 29/01/24.
//
#ifndef CPP_LINKEDLISTQUEUE_H
#define CPP_LINKEDLISTQUEUE_H
#include<cstdlib>
#include<stdexcept>
using namespace std;

struct Node{
public:
    typedef int value_type;
    typedef int& reference;
    typedef Node self_type;
    typedef Node* node_pointer;
public:
    friend class LinkedListQueue;
private:
    value_type data;
    node_pointer next;
public:
    Node(const value_type& inputData=0, node_pointer inputNext= nullptr): data(inputData), next(inputNext){};
    ~Node() = default;

};

class LinkedListQueue{
public:
    typedef int value_type;
    typedef int& reference;
    typedef size_t size_type;
    typedef Node node;
    typedef Node* node_pointer;
public:
    LinkedListQueue():size(0),head(nullptr),tail(nullptr){};
    ~LinkedListQueue(){
        while(size!=0){
            node_pointer tempNode=head; //store the head
            if(head->next){
                head=head->next;
            }
            else{
                head= nullptr;
            }
            delete tempNode;
            size--;
        }
    }

    node_pointer _constructNode(value_type inputData){
        node_pointer newNodePtr=new node(inputData);
        return newNodePtr;
    }

    bool enqueue(value_type inputData){
        node_pointer newNodePtr=_constructNode(inputData);
        try{
            if(size==0){
                head=newNodePtr;
                tail=newNodePtr;
                tail->next= nullptr;
                size++;
            }
            else{
                tail->next=newNodePtr;
                tail=newNodePtr;
                tail->next= nullptr;
                size++;
            }
            return true;
        }
        catch(...){
            delete newNodePtr;
            return false;
        }
    }
    //if fail, return -1
    //if success, return the data,delete the node
    value_type dequeue(){
        try{
            if(size==0){
                throw out_of_range("dequeue() on empty queue");
            }
            else{
                node_pointer tempNode=head;
                value_type headData=tempNode->data;
                if(head->next){
                    head=head->next;
                }
                else{
                    head= nullptr;
                }
                size--;
                //destruct the node
                delete tempNode;
                return headData;
            }
        }
        catch(...){
            return -1;
        }
    }

private:
    node_pointer head;
    node_pointer tail;
    size_type size;
};

#endif //CPP_LINKEDLISTQUEUE_H
