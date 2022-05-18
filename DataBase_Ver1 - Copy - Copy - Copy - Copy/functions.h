#ifndef DATABASE_VER1_FUNCTIONS_H
#define DATABASE_VER1_FUNCTIONS_H

#include <fstream>
#include "BSTree.h"
#include <vector>
#include <string>
#include "functions.h"
#include "BSTree.hpp"

using namespace std;

ostream& operator <<(ostream& out, Node<actors,string> *a);
ostream& operator <<(ostream& out, Node<actors,string> *m);

//Takes in user choice and calls different functions depending on user choice
//uses switch statement, and intakes char for choice and then calls all of those functions
void Menu(BSTree<actors, string> *actors_Tree,BSTree<movies, string> *movies_Tree);

//takes in user input and makes sure that its a double or an int
int takeInint();
double takeIndouble();

//ACTORS
//reads in all of the information from files into a separate vectors of tructs of actors
bool readFromFileActors(string fileName, vector<actors> &actorVector);

//takes in the vector that eerything was read into and writes everything into the tree
template <typename DATATYPE, typename KEYTYPE>
bool fromVectoTree(vector<DATATYPE> &Vector, BSTree<DATATYPE,KEYTYPE> *tree);

//takes in user input, stores it into the actor struct and put it into the binary tree
bool addActor(BSTree<actors,string> *act);

//uses the binary tree funcrion and searches for the actor, then lets that actor to be modified
bool searchForActorAndModify(BSTree<actors,string> *act);

//uses the binary tree function and searches for the actor and then delets the actor
template <typename DATATYPE, typename KEYTYPE>
bool searchAndDelete(BSTree<DATATYPE,KEYTYPE> *del);

//takes in user input and searches the nodes data depending on what the user chose to search by
                    //checks if it contains the substring provided by user
bool searchForActorPartial(BSTree<actors,string> *act);
bool searchForActorAnswerP(BSTree<actors,string> *act);

//takes in user input and searches the tree data depending on what the user chose to search by
                    //completely compares the input and info inside of the tree
bool searchForActorFull(BSTree<actors,string> *act);
bool searchForActorAnswerF(BSTree<actors,string> *act);

//Sorts and prints actor binary tree the way the user wants it to be
void sortActor(vector<actors> actorVector);

//Takes the vector that was used to look trough the complete and partial actor searches and makes it into a binary tree
void AddResultsToTree(BSTree<actors,string> *answers);

//takes in the trees and prints out all of the data from it into a chosen file
void printToFileActor(BSTree<actors,string> *act);

//turns trees to vectors
template <typename DATATYPE, typename KEYTYPE>
void treeToVec(BSTree<DATATYPE,KEYTYPE> *act, Node<DATATYPE,KEYTYPE> *node,vector<DATATYPE> &treeActors);
//MOVIES
//reads in the movie inputs from a file as well as stores all of them into a vector of movies
bool readFromFileMovies(string fileName, vector<movies> &movieVector);

//takes in the user input and puts a new movie into the tree
bool addMovie(BSTree<movies,string> *mov);

//takes in user input, searches for it and modifies if finds the movie in the tree
bool searchForMovieAndModify(BSTree<movies,string> *mov);

//takes in user input and searches the nodes data between the movies depending on what the user chose to search by
        //checks if it contains the substring provided by user
bool searchForMoviePartial(BSTree<movies,string> *mov);
bool searchForMovieAnswersP(BSTree<movies,string> *mov);

//takes in user input and searches the nodes data between the movies depending on what the user chose to search by with
        //complete search this time
        //checks if it contains the substring provided by user
bool searchForMovieFull(BSTree<movies,string> *mov);
bool searchForMovieAnswersF(BSTree<movies,string> *mov);

//sort movie takes in user input and sorts and prints the movie binary tree the way the user wants it to be
bool sortMovie(vector<movies> moviesVector);

//takes the vector of found elements from searches and adds them to a separate binary tree that can be also looked thru
void AddResultsToTree2(BSTree<movies,string> *answers);

void printToFileMovie(BSTree<movies,string> *mov);



//SEARCHES

//Partial Actors
//all of these functions recursevily go through the full binary tree full of actors and try to find the user chosen
                    //input such as name, year, award, etc..
void searchActorNamePartial(Node<actors,string> *node, string name);

void searchActorYearPartial(Node<actors,string> *node, string year);

void searchActorAwardPartial(Node<actors,string> *node, string award);

void searchActorWonPartial(Node<actors,string> *node, string won);

void searchActorFilmPartial(Node<actors,string> *node, string film);

//Complete Actors
//all of these functions take in user input recursively and search through the binary tree, looking for exactly the same
                    //data as the user input
void searchActorNameFull(Node<actors,string> *node, string name);

void searchActorYearFull(Node<actors,string> *node, string year);

void searchActorAwardFull(Node<actors,string> *node, string award);

void searchActorWonFull(Node<actors,string> *node, string won);

void searchActorFilmFull(Node<actors,string> *node, string film);



//Partial movies
//all of these functions simply recursively run through the binary tree and look for the strings in the database
                    //that contain user substring and input
void searchMoviesNamePartial(Node<movies,string> *node, string name);

void searchMoviesYearPartial(Node<movies,string> *node, string year);

void searchMoviesNomPartial(Node<movies,string> *node, string nom);

void searchMoviesRatingPartial(Node<movies,string> *node, string rating);

void searchMoviesDurationPartial(Node<movies,string> *node, string duration);

void searchMoviesGenre1Partial(Node<movies,string> *node, string genre);

void searchMoviesGenre2Partial(Node<movies,string> *node, string genre);

void searchMoviesReleasePartial(Node<movies,string> *node, string release);

void searchMoviesMetaPartial(Node<movies,string> *node, string score);

void searchMoviesSynPartial(Node<movies,string> *node, string syn);

//Full movies
//all of these functions take in user input and recursively run through the binary movie tree, looking for the exact
            //same data that was inputed by the user
void searchMoviesNameFull(Node<movies,string> *node, string name);

void searchMoviesYearFull(Node<movies,string> *node, string year);

void searchMoviesNomFull(Node<movies,string> *node, string nom);

void searchMoviesRatingFull(Node<movies,string> *node, string rating);

void searchMoviesDurationFull(Node<movies,string> *node, string duration);

void searchMoviesGenre1Full(Node<movies,string> *node, string genre);

void searchMoviesGenre2Full(Node<movies,string> *node, string genre);

void searchMoviesReleaseFull(Node<movies,string> *node, string release);

void searchMoviesMetaFull(Node<movies,string> *node, string score);

void searchMoviesSynFull(Node<movies,string> *node, string syn);

//prints out the vector of searches that matched with user input for the movie binary tree
void printOI();

//prints out the vector of searches that matchhed with user input for the actor binary tree
void printOOF();

//menu that does all of the functions to the extra credit
void NominationsMenu();

#endif //DATABASE_VER1_FUNCTIONS_H
