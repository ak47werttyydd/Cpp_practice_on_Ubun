//
// Created by ruochen on 02/09/23.
//
/*Bidirectional Circular Linked List*/

#ifndef CPP_LINKEDLISTTEST_H
#define CPP_LINKEDLISTTEST_H

#include <iterator>  //iterator_tag, advance
#include <cstddef> //ptrdiff_t, size_t
#include <memory> //allocator
#include <iostream>
#include <unordered_map>
#include <functional> //std::function
#include <algorithm>

using namespace std;

/*Compare Start*/
/**Functor ComAscend Start**/
template<typename T>
struct ComAscend{
    bool operator()(const T& x,const T& y){
        return true;
    }
};

template<>
struct ComAscend<int>{
    bool operator()(const int& x,const int& y){
        return x<=y;
    }
};

template<>
struct ComAscend<double>{
    bool operator()(const double& x,const double& y){
        return x<=y;
    }
};

template<>
struct ComAscend<float>{
    bool operator()(const float& x,const float& y){
        return x<=y;
    }
};

template<>
struct ComAscend<char>{
    bool operator()(const char& x,const char& y){
        return x<=y;
    }
};
/**Functor ComAscend End**/

/**Function ComDescend Start**/
bool ComDescend(const int& x, const int& y){
    return x>=y;
}

bool ComDescend(const double& x, const double& y){
    return x>=y;
}

bool ComDescend(const float& x, const float& y){
    return x>=y;
}

bool ComDescend(const char& x, const char& y){
    return x>=y;
}

//Any else types of data, don't compare, just return true
template<class T>
bool ComDescend(const T& x, const T& y){
    return true;
}
/**Function ComDescend End**/

/*Compare End*/

/*Node Start*/
template<typename T>
class __ListNode {
public:
    typedef __ListNode<T>*  link_type;
    template <typename> friend class __ListIterator;
    template <typename,typename> friend class List;
private:
    T data;
    link_type prev;
    link_type next;
public:
    __ListNode(T d, link_type p= nullptr, link_type n= nullptr):data(d),prev(p),next(n){}
};
/*Node End*/

/*ListIterator Start*/
template<class T>
class __ListIterator{
public:
    //must
    typedef bidirectional_iterator_tag iterator_category;
    typedef T& reference;
    typedef T value_type;
    typedef T* pointer;
    typedef ptrdiff_t difference_type;

    //option
    typedef __ListIterator<T> self;
    typedef __ListNode<T>* link_type;
    typedef __ListNode<T> list_node;

private:
    link_type node;  //a pointer to the node

public:
    //ctor default
    __ListIterator():node(nullptr){}

    //ctor with node arg
    explicit __ListIterator(const link_type& node):node(node){}  //no confusion between function parameter and class member with the same name "node"

    //copy ctor (shallow copy)
    __ListIterator(const self& iterator):node(iterator.node){}

    //dtor (no need, because __ListIterator doesn't own any dynamically allocated memory directly)
    ~__ListIterator()= default; //The __list_iterator represents a position within the list, rather than owning any dynamically allocated memory directly. This means that, typically, it doesn't require a destructor to release any memory. Instead, the memory management (like allocating or deallocating nodes) is handled by the container (list in this case).

    //assignment (shallow copy)
    self& operator=(const self&);

    //prefix--
    self& operator--();

    //postfix --
    self operator--(int);

    //prefix++
    self& operator++();

    //postfix++
    self operator++(int);

    //==
    bool operator==(const self&) const;

    //！=
    bool operator!=(const self&) const;

    //->
    pointer operator->() const;

    //*
    reference operator*() const {
        return node->data;
    }

    //+int
    self operator+(int) const;

    //-int
    self operator-(int) const;

};

//assignment (shallow copy)
template<class T>
inline typename __ListIterator<T>::self& __ListIterator<T>::operator= (const self& iterator){
    //Inside the class template's body, you can use self directly.
    //When defining a member function outside the class template's body, you need to qualify the return type with typename __list_iterator<T>::self& to be explicit.
    //Within the function parameter list or within the function body itself, you can use self directly since the context makes it clear which self you're referring to.
    node=iterator.node;
    return *this;
}

//prefix--
template<class T>
inline typename __ListIterator<T>::self& __ListIterator<T>::operator-- (){
    node=node->prev;
    return *this;
}

//postfix--
template<class T>
inline typename __ListIterator<T>::self __ListIterator<T>::operator--(int){
    self tmp=*this;
    --(*this);
    return tmp;
}

//prefix++
template<class T>
inline typename __ListIterator<T>::self& __ListIterator<T>::operator++ (){
    node=node->next;
    return *this;
}

//postfix++
template<class T>
inline typename __ListIterator<T>::self __ListIterator<T>::operator++(int){
    self tmp=*this;
    ++(*this);
    return tmp;
}

//==
template<class T>
inline bool __ListIterator<T>::operator==(const self& iterator) const {
    return node==iterator.node;
}

//!=
template<class T>
inline bool __ListIterator<T>::operator!=(const self& iterator) const {
    return node!=iterator.node;
}

//->
template<class T>
inline typename __ListIterator<T>::pointer __ListIterator<T>::operator->() const {
    return &(operator*());
}

//+int： getting to the *this+x iterator, rather than modifying *this
template<class T>
inline typename __ListIterator<T>::self __ListIterator<T>::operator+(int x) const {
    self tmp=*this;
    if(x>=0){
        while(x--){
            ++tmp;
        }
    }else{
        while(x++){
            --tmp;
        }
    }
    return tmp;
}

//-int
template<class T>
inline typename __ListIterator<T>::self __ListIterator<T>::operator-(int x) const {
    return (*this)+(-x);
}


/*ListIterator End*/

/*List Start*/
template<class T,class Alloc=allocator<__ListNode<T>>>
class List{
public:
    typedef List<T> self;
    typedef __ListNode<T> list_node;
    typedef list_node* link_type;
    typedef __ListIterator<T> iterator;
    typedef T value_type;
private:
    link_type sentinelNode;
    Alloc nodeAlloc;
public:
    //ctor default
    List():sentinelNode(__get_node()){
        sentinelNode->next=sentinelNode;
        sentinelNode->prev=sentinelNode;
    }
    //copy ctor
    explicit List(const self& list){
         sentinelNode=__get_node();
         link_type curNode=sentinelNode;
         //deep copy and chain nodes from list
         for(iterator i=list.begin();i!=list.end();++i){
             curNode->next = __get_node(*i);
             curNode->next->prev = curNode;
             curNode=curNode->next;
         }
         //circular
         curNode->next=sentinelNode;
         sentinelNode->prev=curNode;
    }
    //dtor
    ~List(){
        clear();
        __deallocate_node(sentinelNode);
    }
    //clear： clear(destruct+deallocate) all nodes without sentinelNode;
    void clear(){
        link_type curNode=sentinelNode->next;
        while(curNode!=sentinelNode){
            link_type tmpNode=curNode;
            curNode=curNode->next;
            __destroy_deallocate_node(tmpNode);
        }
        sentinelNode->prev = sentinelNode;
        sentinelNode->next = sentinelNode;
    }

    //begin: return iterator pointing to the first node after sentinel node
    iterator begin() const {
        return iterator(sentinelNode->next);
    }

    //end: return iterator pointing to the sentinelNode
    iterator end() const {
        return iterator(sentinelNode);
    }

    //size
    size_t size() const {
        size_t count=0;
        for(iterator i=begin();i!=end();++i){
            count++;
        }
        return count;
    }

    //print
    void print() const {
        if(!empty()){
            int count=1;
            for(iterator i=begin();i!=end();++i){
                cout<<"The "<<count<<"th element is "<<*i<<", ";
                count++;
            }
            cout<<endl;
        }
        else cout<<"The list is empty"<<endl;
    }

    //empty
    bool empty() const {
        return sentinelNode->next==sentinelNode;
    }

    //push_back
    void push_back(const value_type& data){
        link_type newNode=__get_node(data);
        link_type lastNode=sentinelNode->prev;
        lastNode->next=newNode;
        newNode->prev=lastNode;
        newNode->next=sentinelNode;
        sentinelNode->prev=newNode;
    }

    //push_front
    void push_front(const value_type& data){
        link_type newNode=__get_node(data);
        newNode->next=sentinelNode->next;
        newNode->prev=sentinelNode;
        sentinelNode->next->prev=newNode;
        sentinelNode->next=newNode;
    }

    //insert:
        // 0<=idx<=size
        // the first element's idx is 0. insert(data,0) gets a new node and substitute the first element. The previous first element is pushed forward as the second element
        // insert(data,size) is push_back
    int insert(const value_type& data, size_t idx){
        if(size()<idx) {
            cout<<"Wrong index! The interval is 0<=idx<=size"<<endl;
            return 0;
        }
        else if(idx==0){
            push_front(data);
        }
        else if(idx==size()){
            push_back(data);
        }
        else{
            link_type position=sentinelNode->next;  //where the newNode should be
            while(idx){
                position=position->next;
                --idx;
            }
            link_type newNode=__get_node(data);
            newNode->prev=position->prev;
            newNode->next=position;
            position->prev->next=newNode;
            position->prev=newNode;
        }
        return 1;
    }

    //pop_back
    int pop_back(){
        if(!empty()){
            link_type lastNode=sentinelNode->prev;
            lastNode->prev->next=sentinelNode;
            sentinelNode->prev=lastNode->prev;
            __destroy_deallocate_node(lastNode);
            return 1;
        }
        else cout<<"empty list"<<endl;
        return 0;
    }

    //pop_front
    int pop_front(){
        if(!empty()){
            link_type firstNode=sentinelNode->next;
            sentinelNode->next=firstNode->next;
            firstNode->next->prev=sentinelNode;
            __destroy_deallocate_node(firstNode);
            return 1;
        }
        else cout<<"empty list"<<endl;
        return 0;
    }

    //remove
    int remove(size_t idx){
        if(idx>=size()){
            cout<<"Wrong index! The interval is 0<=idx<size"<<endl;
            return 0;
        }
        else if(idx==0){
            pop_front();
        }
        else if(idx==size()-1) {
            pop_back();
        }
        else{
            link_type position=sentinelNode->next;
            while(idx){
                position=position->next;
                --idx;
            }
            position->prev->next=position->next;
            position->next->prev=position->prev;
            __destroy_deallocate_node(position);
        }
        return 1;
    }


//sort(mode): mode=0 ascend, mode=1 descend
    void sort(int mode){
        if(mode){
            ComAscend<value_type> comAscend;
            __sort(begin(),end()-1,comAscend);
            cout<<"Sorting Finish"<<endl;
        }
        else{
            __sort(begin(),end()-1,static_cast<bool(*)(const value_type&, const value_type&)>(ComDescend));
            cout<<"Sorting Finish"<<endl;
        }
    }


protected:
    //__get_node: allocate the memory to a node
    link_type __get_node(){
        link_type node=nodeAlloc.allocate(1);
        return node;
    }
    //__get_node: allocate memory and ctor a node with data
    link_type __get_node(const value_type& data){
        link_type node=__get_node();
        nodeAlloc.construct(node,list_node{data,nullptr,nullptr});  //must defining a public ctor for __ListNode
        return node;
    }
    //__deallocate_node: deallocate the memory of a node
    void __deallocate_node(link_type node){
        nodeAlloc.deallocate(node,1);
    }
    //__destroy_deallocate_node: destruct a node and then deallocate it
    void __destroy_deallocate_node(link_type node){
        nodeAlloc.destroy(node); //destruct a node
        //or node->~list_node();
        __deallocate_node(node); //deallocate the memory
    }


//__sort: partition+recurse
// using function template to get function and functor
    template<class Comparator>
    void __sort(iterator start, iterator finish, Comparator comp){
        //termination
//        if(start!=finish && start!=end() && finish!=end()) {   //termination 1. the interval is a point; 2. either side of iterator gets to sentinel
        if(__comesBefore(start,finish)){
            //partition
            iterator pivot = finish;
            iterator i = start;  //scanning
            iterator j = start;  //the right place to put pivot
            for (; i != finish; ++i) {
                if (comp(*i, *pivot)) {
                    swap(*i, *j);
                    ++j;
                }
            }

            //put pivot at the right place
            iter_swap(j, pivot);

            //recursive
            __sort(start, j - 1, comp);
            __sort(j + 1, finish, comp);
            /*Why segmentation fault while ascending order?
             * original 3,2,1,5,4
             * while when 1,2,3,4,5
             * start: 2; finish: 3; after partition j: 3; j+1:4, which surpasses finish. But "__sort(j + 1, finish, comp);" doesn't terminate under condition "if(start!=finish && start!=end() && finish!=end())"
             * Revision:
             * the termination condition should be start>=finish || start==end() || finish==end()
            */
        }
    }

    //compare iterator A and B, return whether A is before B
    bool __comesBefore(const iterator& iterator_a, const iterator& iterator_b){
        if( iterator_a!=end()){   //iterator_b!=end() can be left out, because if iterator_b points to sentinel, always return false
            iterator it=iterator_a+1;  //it starts from iterator_a+1
            while(it!=end()){  //find whether iterator_b is after iterator_a
                if(it==iterator_b) return true;
                it++;
            }
        }
        return false;  //1. iterator_a or iterator_b point to sentinel, return false;  2. iterator_b is not after iterator_a, return false
    }

    //reverse
    //merge
    //unique elements
    //deep copy
    //equal
};
/*List End*/



#endif //CPP_LINKEDLISTTEST_H
