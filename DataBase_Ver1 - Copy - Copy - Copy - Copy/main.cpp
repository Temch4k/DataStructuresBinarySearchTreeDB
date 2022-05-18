//Artsiom Skarakhod & Zach Triplett
#include <iostream>
#include <fstream>
#include "functions.h"
#include "BSTree.h"
#include "Node.h"

using namespace std;
int main()
{
    BSTree<actors, string> *actors_Trees = new BSTree<actors, string>;
    BSTree<movies, string> *movies_Trees = new BSTree<movies, string>;

    Menu(actors_Trees,movies_Trees);
    return 0;
}