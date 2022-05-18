//Artsiom Skarakhod and Zach Triplett
#ifndef NODE_
#define NODE_
#include <iostream>
#include <string>

using namespace std;

// A tree node class for ints
// Placeholder for a composite data type

struct actors
{
    string Year;
    string Award;
    string Winner;
    string Name;
    string Film;
};

//this is going to be object movie inside of the movie binary tree
//every movie will have those variables
struct movies
{
    string Name;
    string Year;
    string nominations;
    string ratings;
    string duration;
    string genre;
    string genre2;
    string release;
    string metacrytic;
    string synopsis;
};

//Binary Tree Node
template <typename DATATYPE, typename KEYTYPE>
class Node {
private:
    KEYTYPE key; //This should be the datatype of your key...sorted field in tree
    DATATYPE data;
    Node<DATATYPE, KEYTYPE> * left;
    Node<DATATYPE, KEYTYPE> * right;
    Node<DATATYPE, KEYTYPE> * parent;
public:
    Node() {left=nullptr; right=nullptr; parent = nullptr;};
    void setKey(KEYTYPE aKey) { key = aKey; };
    void setData(DATATYPE aData) { data = aData; }
    void setLeft(Node<DATATYPE, KEYTYPE> * aLeft) { left = aLeft; };
    void setRight(Node<DATATYPE, KEYTYPE> * aRight) { right = aRight; };
    void setParent(Node<DATATYPE, KEYTYPE> * aParent) { parent = aParent; };
    KEYTYPE Key() { return key; };
    DATATYPE Data() { return data; }
    Node<DATATYPE, KEYTYPE> * Left() { return left; };
    Node<DATATYPE, KEYTYPE> * Right() { return right; };
    Node<DATATYPE, KEYTYPE> * Parent() { return parent; };
};

#endif
