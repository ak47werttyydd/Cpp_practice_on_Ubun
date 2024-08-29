#include "VectorTest.h"
#include "LinkedListTest.h"
#include "LinkedListQueue.h"
#include <iomanip>  //print format
#include <map>
using namespace std;

void vector_test(){
    /*Begin Test1: 1. args-ctor  2. repetitive target*/
    cout<<setw(10)<<setfill('-')<<"Begin Test1: 1. args-ctor  2. repetitive target"<<endl;
    vector<int> v1={1,5,4,9,2,2,7,6,0,1};
    int target1=2;
    VectorTest test1(v1,target1);
    test1.qsort();
    test1.bsearch();
    cout<<setw(10)<<setfill('-')<<"End Test1: 1. args-ctor  2. repetitive target"<<endl;
    /*End Test1*/

    /*Begin Test2, 1. default ctor 2. target is not in*/
    cout<<setw(10)<<setfill('-')<<"Begin Test2, 1. default ctor 2. target is not in"<<endl;
    vector<int> v2={3,4,5,8,7,6,9,0,1,1};
    int target2=2;
    VectorTest test2;
    test2.set(v2,target2);
    test2.qsort();
    test2.bsearch();
    cout<<setw(10)<<setfill('-')<<"End Test2, 1. default ctor 2. target is not in"<<endl;
    /*End Test2*/

    /*Begin Test3 1. default ctor 2. typing by */
    //please input a vector with all elements > 2
    int i=0;
    map<VectorTest::TypingMode,string> typingModeString={
            {VectorTest::TypingMode::bySize,        "bySize"},
            {VectorTest::TypingMode::byTermination, "byTermination"},
            {VectorTest::TypingMode::Max,           "Max"}
    };
    while(i<2){
        VectorTest::TypingMode typingMode=static_cast<VectorTest::TypingMode>(i);
        cout << setw(10) << setfill('-') << "Begin Test3, 1. default ctor 2. target is not in, 3. TypingMode is " << typingModeString[typingMode] << endl;
        VectorTest test3;
        test3.setTyping();
        test3.qsort();
        test3.bsearch();
        i++;
        cout << setw(10) << setfill('-') << "End Test3, 1. default ctor 2. target is not in, 3. TypingMode is " << typingModeString[typingMode] << endl;
    }
    /*End Test3*/

}

void linked_list_test(){
//    cout<<setw(50) << setfill('-')<<internal<<"Testing List<int> Begin"<<endl;
//    cout<<"get a list with two elements"<<endl;
//    List<int> list;
//    list.push_back(1);
//    list.push_back(2);
//    list.print();
//    cout<<"the size is: "<<list.size()<<endl;
//    cout<<"is it empty? 0 is no, 1 is yes: "<<list.empty()<<endl;
//
//    cout<<"copy ctor list2 from list"<<endl;
//    List<int> list2(list);
//    list2.print();
//    cout<<"the size is: "<<list2.size()<<endl;
//    cout<<"is it empty? 0 is no, 1 is yes: "<<list2.empty()<<endl;
//
//    cout<<"clear the list"<<endl;
//    list.clear();
//    list.print();
//    cout<<"the size is: "<<list.size()<<endl;
//    cout<<"is it empty? 0 is no, 1 is yes: "<<list.empty()<<endl;
//
//    cout<<"destruct the list"<<endl;
//    list.~List();
//    list.print();
//    cout<<"the size is: "<<list.size()<<endl;
//    cout<<"is it empty? 0 is no, 1 is yes: "<<list.empty()<<endl;
//    cout<<internal<<setw(50) << setfill('-')<<"Testing List<int> End"<<endl;
//
//    cout<<internal<<setw(50) << setfill('-')<<"Testing __ListIterator<int> Begin"<<endl;
//    __ListIterator<int> iterator;
//    iterator=list2.begin();
//    cout<<"the first element is: "<<*iterator<<endl;
//    iterator=--list2.end();
//    cout<<"the last element is: "<<*iterator<<endl;
//    cout<<"list2.begin()==list2.end() is: " << ( list2.begin()==list2.end() ) <<endl;
//    iterator=list2.begin();
//    cout<<"list2.begin()+5 points to: "<<*(iterator+5)<<endl;
//    cout<<setw(50) << setfill('-')<<internal<<"Testing __ListIterator<int> End"<<endl;
//
//    cout<<setw(50) << setfill('-')<<internal<<"Testing List<VectorTest> Begin"<<endl;
//    vector<int> v1={1,5,4,9,2,2,7,6,0,1};
//    int target1=2;
//    VectorTest test1(v1,target1);
//    vector<int> v2={1,2,3};
//    int target2=3;
//    VectorTest test2(v2,target2);
//    List<VectorTest> list3;
//    list3.push_back(test1);
//    list3.push_back(test2);
//    list3.begin()->qsort();
//    list3.begin()->bsearch();
//    list3.clear();
//    cout<<"the size is: "<<list3.size()<<endl;
//    cout<<"is it empty? 0 is no, 1 is yes: "<<list3.empty()<<endl;
//    cout<<setw(50) << setfill('-')<<internal<<"Testing List<VectorTest> End"<<endl;

//    cout<<setw(50) << setfill('-')<<internal<<"Testing push_front,insert,pop_front, pop_back, remove Begin"<<endl;
//    List<int> list4;
//    list4.push_front(1);
//    list4.push_front(2);
//    cout<<"list4 should be 2,1"<<endl;
//    list4.print();
//    list4.insert(3,0);
//    cout<<"list4 should be 3,2,1"<<endl;
//    list4.print();
//    list4.insert(4,3);
//    cout<<"list4 should be 3,2,1,4"<<endl;
//    list4.print();
//    list4.insert(5,3);
//    cout<<"list4 should be 3,2,1,5,4"<<endl;
//    list4.print();
//    list4.pop_back();
//    cout<<"list4 should be 3,2,1,5"<<endl;
//    list4.print();
//    list4.pop_front();
//    cout<<"list4 should be 2,1,5"<<endl;
//    list4.print();
//    list4.push_back(6);
//    list4.remove(0);
//    cout<<"list4 should be 1,5,6"<<endl;
//    list4.print();
//    list4.remove(1);
//    cout<<"list4 should be 1,6"<<endl;
//    list4.print();
//    list4.remove(1);
//    cout<<"list4 should be 1"<<endl;
//    list4.print();
//    cout<<setw(50) << setfill('-')<<internal<<"Testing push_front,insert,pop_front, pop_back, remove End"<<endl;

    cout<<setw(50) << setfill('-')<<internal<<"Testing sort"<<endl;
    List<int> list5;
    list5.push_front(1);
    list5.push_front(2);
    cout<<"list5 should be 2,1"<<endl;
    list5.print();
    list5.insert(3,0);
    cout<<"list5 should be 3,2,1"<<endl;
    list5.print();
    list5.insert(4,3);
    cout<<"list5 should be 3,2,1,4"<<endl;
    list5.print();
    list5.insert(5,3);
    cout<<"list5 should be 3,2,1,5,4"<<endl;
    list5.print();
    list5.sort(1);
    cout<<"list5 should be 1,2,3,4,5"<<endl;
    list5.print();
    list5.sort(0);
    cout<<"list5 should be 5,4,3,2,1"<<endl;
    list5.print();

}

void linked_list_queue_test(){
    LinkedListQueue queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    int a,b,c;
    a=queue.dequeue();
    b=queue.dequeue();
    c=queue.dequeue();
    cout<<"a,b,c is: "<<a<<" "<<b<<" "<<c<<endl;

}

int main() {
    linked_list_queue_test();
    return 0;
}
