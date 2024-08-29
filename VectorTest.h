//
// Created by ruochen on 09/08/23.
//
#include <vector>
#include <iostream>
#include <string>
#include <limits> //numeric_limits
#include <algorithm>
#include <iterator> //advance
using namespace std;


#ifndef CPP_BINARY_SEARCH_H
#define CPP_BINARY_SEARCH_H


class VectorTest{
public:
    enum class TypingMode:int {
        bySize,
        byTermination,
        Max //Special enumerator indicating the end
    };
    //VectorTest(vector,target)
    VectorTest(const vector<int>& in, int t): input(in), target(t){ idx=-1;}
    VectorTest();

    void set(const vector<int>&, int);

    friend istream& operator>>(istream&, VectorTest::TypingMode&);  //declare the cin>>VectorTest::TypingMode obj

    void setTyping(){
        cout<<"Please choose the typing mode, 0:bySize, 1:byTermination"<<endl;
        while(true){  //repeat until valid typingMode
            TypingMode typingMode;
            if(cin >> typingMode){  //valid typingMode
                switch(typingMode){
                    case static_cast<VectorTest::TypingMode>( 0 ):
                        _setTypingBySize();
                        break;
                    case static_cast<VectorTest::TypingMode>( 1 ):
                        _setTypingByTermination();
                        break;
                    default:
                        cout<<"Not valid typingMode. Implementing bySize"<<endl;
                        _setTypingBySize();
                }
                break;
            }else{ //invalid typingMode
                cout<<"Invalid typingMode! Please choose the typing mode, 0:bySize, 1:byTermination"<<endl;
                cin.clear();  //clear fail state
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); //clear cin buffer. may be redundant?
            }
        }

        cout<<"Please enter the target (integer): "<<endl;
        while(true){
            cin>>target;
            if(cin.fail()){  //invalid target
                cout<<"Invalid target! Please enter the target in integer: "<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); //may be redundant?
            }else{  //valid target
                break;
            }
        }
    }

    void _setTypingBySize(){
        cout<<"Typing vector<int>:"<<endl;
        cout<<"Please enter the size"<<endl;
        int n; //size of vector
        while(true){
            cin>>n;
            if(!(cin.fail())) break;
            else{
                cout<<"Invalid size. Please enter the size in int"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
        cout<<"the Size is: "<<n<<endl;
        for(int i=0;i<n;i++){
            cout<<"Please enter the "<<i+1<<"th element:"<<endl;
            int element;
            while(!(cin>>element)){
                //invalid
                cout<<"Invalid element. Please enter the "<<i+1<<"th element:"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
            input.push_back(element);
            cout<<"the "<<i+1<<"th element is "<<element<<endl;
        }
    }

    void _setTypingByTermination(){
        string termination="exit";
        int i=1; //count of elements
        int element;
        cout<<"Please enter an integer or terminate by typing \"exit\""<<endl;
        while(true){
            if(!(cin>>element)){ //non-integer or overflow
                cin.clear(); //clear the error state
                string str_temp;
                cin>>str_temp;//redirect cin
                if(str_temp==termination) break;  //encountering a termination symbol, exit the loop
                //a non-termination string
                cin.clear(); //typing ENTER immediately without any characters raises failbit
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); //clear buffer in cin until encounter '\n'
                cout<<"Invalid input. Please enter an integer or terminate by typing \"exit\""<<endl;
                continue;
            }
            //an integer
            input.push_back(element);
            cout<<"the "<<i++<<"th element is: "<<element<<endl;
        }
    }

    //Please initialize and sort first, then bsearch
    //the binarysearch adopts lowerbound method, i.e. find the lowerbound where the target can put
    void bsearch();

    void qsort(){
        _qsort(input.begin(),input.end()-1);
        cout<<"Sorted vector is: ";
        for(int element : input){
            cout<<element<<" ";
        }
        cout<<endl;
    }

    /*auxiliary function for qsort*/
    void _qsort(vector<int>::iterator start, vector<int>::iterator end);

private:
    vector<int> input;
    int target{};
    int idx;

};

/*Start: Definition of Binary Search*/
inline VectorTest::VectorTest() {
    idx=-1;
    cout<<"Please Use set(const vector<int>& input, int target) or setTyping() to set input and target"<<endl;
}

inline void VectorTest::set(const vector<int>& in, int t){
    input=in;
    target=t;
}


inline void VectorTest::bsearch()  {
    int size=static_cast<int>(input.size());  //the initial size of searching range is the entire vector
    int step; //move to the middle element
    int first=0; //initial starting element of searching domain is the first element in the vector;
    //At last, "first" is the lowerbound, e.g. target is 2, input is [1,2,2,3] lowerbound is index=1
    int i; //iterator
    if(input[0]>target){
        cout<<"target is smaller than any elements."<<endl;
        idx=-1;
        return;
    }
    else if(input[0]==target){
        idx=0;
        cout<<"target's idx is: "<<idx<<endl;
        return;
    }
    if(input.back()<target){
        cout<<"target is larger than any elements."<<endl;
        idx=-1;
        return;
    }
    else if(input.back()==target){
        idx=size-1;
        cout<<"target's idx is: "<<idx<<endl;
        return;
    }
    while(size>0) {  //find the lowerbound of the target
        step=size/2;
        i=first+step;
        if(input[i]<target){ //should search the right domain
            first=i+1;
            size-=step+1;
        }
        else{ //should search the left domain when input[i]<=target;
            //first remains
            size=step;
        }
    }
    if(input[first]==target) {
        idx=first;
        cout<<"target's idx is: "<<idx<<endl;
    }
    else{
        idx=-1;
        cout<<"Can't find the target. The lowerbound is: "<<first<<endl;
    }
}

//partition+recursion(starting index, ending index)
inline void VectorTest::_qsort(vector<int>::iterator start, vector<int>::iterator end){
    /*Partition*/
    if(start<end){  //termination condition: if start==end, terminate
        vector<int>::iterator pivot=end;  //selecting the end element as pivot
        vector<int>::iterator i=start; //the new and final position of pivot after partition (i.e. the first element > pivot)
        for(vector<int>::iterator j=start; j<end; j++){
            if(*j<=*pivot){  //<= and < are OK
                iter_swap(i++,j); //swap element smaller than pivot with the first element larger than pivot, and then move i one step forward which points to the new first element larger than pivot
            }
        }
        iter_swap(i,pivot);

        /*Recursion*/
        _qsort(start,i-1);
        _qsort(i+1,end);
    }
}


/*template function, getting the size of enum*/
template <typename E>
constexpr typename std::underlying_type<E>::type enumSize() {
//constexpr specifies to calculate as a const in compiler-time
//underlying_type is a type traits, it responds the underlying type of enumeration class E
    return static_cast<typename std::underlying_type<E>::type>(E::Max);  //Max is a special enumerator defined in enumeration class to indicate the size
}

/*cin>>VectorTest::TypingMode*/
//if the input is valid number or string, success. Otherwise asserting errors
istream& operator>>(istream& is, VectorTest::TypingMode& mode )
{
    int intTmp ;
    string strTmp;
    if ( is >> intTmp ){ //int
        if( 0 <= intTmp && intTmp < enumSize<VectorTest::TypingMode>()) {  //intTmp is valid
            mode = static_cast<VectorTest::TypingMode>( intTmp );  //forced cast int into VectorTest::TypingMode
        }else{  //intTmp is invalid
            is.clear();  //clear any error flags
            is.setstate(std::ios::failbit); //set the "failbit" flag on the input stream
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //clear buffer
        }
    }
    else{  //string
        is.clear();
        is>>strTmp;
        if(strTmp=="bySize") mode=VectorTest::TypingMode::bySize;
        else if (strTmp=="byTermination") mode=VectorTest::TypingMode::byTermination;
        else{
            is.clear();  //clear any error flags
            is.setstate(std::ios::failbit); //set the "failbit" flag on the input stream
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //clear buffer
        }
    }
    return is ;
}

#endif //CPP_BINARY_SEARCH_H