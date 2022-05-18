//Artsiom Skarakhod
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include "functions.h"
#include "BSTree.h"

#include "Node.h"

using namespace std;


vector<Node<actors,string>*> oof;
vector<Node<movies,string>*> oi;

void Menu(BSTree<actors, string> *actors_Tree,BSTree<movies,string> *movies_Tree)
{
    cout << "Welcome to the movie Data Base!" << endl;
    bool manu = true;
    char user_menu_choice = 0;
    string choice;

    //vector containing actor structs
    vector<actors> readActors;
    vector<movies> readMovies;

    cout <<"What files would you like to read the info from?"<<endl;

    //should ask what file the user would like to read from
    string file ="actor-actress.csv";

    //ACTOR
    //reads al of the info from file to actor vector
    cout<<"Enter the Actor's file name! ";
    readFromFileActors(file, readActors);
    fromVectoTree(readActors,actors_Tree);

    //MOVIE
    file = "pictures.csv";
    readFromFileMovies(file, readMovies);
    fromVectoTree(readMovies, movies_Tree);

    while (manu)
    {
        //prints out the menu options
        cout << "A. Add record to Actor-Actress Data base" << endl
             << "B. Add record to Movie Data base" << endl
             << "C. Search for a record in Actor-Actress data base and modify" << endl
             << "D. Search for a record in Movie database and MODIFY the fields." << endl
             << "E. Search for a record in Actor-Actress database and DELETE the fields." << endl
             << "F. Search for a record in Movie database and DELETE the fields." << endl
             << "G. SORT the Actor-Actress database by any field." << endl
             << "H. SORT the Movie database by any field. " << endl
             << "I. COMPLETE SEARCH the Actor-Actress database." << endl
             << "J. COMPLETE SEARCH the Movie database." << endl
             << "K. PARTIAL SEARCH the Actor-Actress database." << endl
             << "L. PARTIAL SEARCH the Movie database. " << endl
             << "M. Print Actor-Actress to file"<<endl
             << "N. Print Pictures to file"<<endl
             << "W.(E.C.) Nominations Menu"<<endl
             << "Q. To Quit"<<endl;
        getline(cin, choice);
        user_menu_choice=choice[0];
        //Menu
        //Insert choice
        switch (user_menu_choice)
        {
            case 'A':
            case 'a':
                addActor(actors_Tree);
                //add actors
                break;
            case 'B':
            case 'b':
                addMovie(movies_Tree);
                //add movies
                break;
            case 'C':
            case 'c':
                searchForActorAndModify(actors_Tree);
                //Search and Modify actors
                break;
            case 'D':
            case 'd':
                searchForMovieAndModify(movies_Tree);
                //Search then modify movies
                break;
            case 'E':
            case 'e':
                searchAndDelete(actors_Tree);
                //Search then delete actor
                break;
            case 'F':
            case 'f':
                searchAndDelete(movies_Tree);
                //Search then delete movie
                break;
            case 'G':
            case 'g':
                sortActor(readActors);
                //sort actor and print into file
                break;
            case 'H':
            case 'h':
                sortMovie(readMovies);
                //sort movie and print to file
                break;
            case 'I':
            case 'i':
                searchForActorFull(actors_Tree);
                //use complete search and look for actor
                break;
            case 'J':
            case 'j':
                searchForMovieFull(movies_Tree);
                //user complete search and look for movie
                break;
            case 'K':
            case 'k':
                searchForActorPartial(actors_Tree);
                //partial search for the actor
                break;
            case 'L':
            case 'l':
                searchForMoviePartial(movies_Tree);
                //partial search for movies
                break;
            case 'M':
            case 'm':
                printToFileActor(actors_Tree);
                //prints out actor trees into file
                break;
            case 'N':
            case 'n':
                printToFileMovie(movies_Tree);
                //prints out movie trees into file
                break;
            case 'W':
            case 'w':
                NominationsMenu();
                //takes you to the extra credit part
                break;
            case 'Q':
            case 'q':
                cout <<"You chose to quit the data base :("<<endl;
                manu = false;
                //lets the user exit the menu
            default:
                break;
        }
    }
}

int takeInint()
{
    //takes in user input and makes sure that its an int
    string input;
    int x;
    while (true) {
        cin >> input;

        // This code converts from string to number safely.
        stringstream myStream(input);
        if (myStream >> x)
            break;
        cout << "That is not an integer, please try again" << endl;
    }
    return x;
}

double takeIndouble()
{
    //takes in user input and makes sure its a double
    string input;
    double rating;
    while (true) {
        cin >> input;

        // This code converts from string to number safely.
        stringstream myStream(input);
        if (myStream >> rating)
            break;
        cout << "That is not an int, please try again" << endl;
    }
    return rating;
}

void printOOF()
{
    //prints out the vector of complete or partial searches for actor
    for(int i =0; i<oof.size();i++)
    {
        cout<<"Result: "<<i+1<<endl;
        cout<<"Name: \t"<<oof[i]->Data().Name<<endl;
        cout<<"Year: \t"<<oof[i]->Data().Year<<endl;
        cout<<"Winner: \t"<<oof[i]->Data().Winner<<endl;
        cout<<"Film: \t"<<oof[i]->Data().Film<<endl;
        cout<<"Awards: \t"<<oof[i]->Data().Award<<endl<<endl;
    }
}

void printOI()
{
    //prints out the vector of complete or partial searches for movies
    for(int i =0; i<oi.size();i++)
    {
        cout<<"Result: "<<i+1<<endl;
        cout<<"Name: \t"<<oi[i]->Data().Name<<endl;
        cout<<"Year: \t"<<oi[i]->Data().Year<<endl;
        cout<<"Nominations: "<<oi[i]->Data().nominations<<endl;
        cout<<"Rating: \t"<<oi[i]->Data().ratings<<endl;
        cout<<"Duration: \t"<<oi[i]->Data().duration<<endl;
        cout<<"Genre1: \t"<<oi[i]->Data().genre<<endl;
        cout<<"Genre2: \t"<<oi[i]->Data().genre2<<endl;
        cout<<"Release: \t"<<oi[i]->Data().release<<endl;
        cout<<"Metacrytic: \t"<<oi[i]->Data().metacrytic<<endl;
        cout<<"Synopsis: \t"<<oi[i]->Data().synopsis<<endl<<endl;
    }
}

//ACTORS
bool readFromFileActors(string fileName, vector<actors> &actorVector)
{
    //makes the infile stream
    bool read= true;

    while(read)
    {
        getline(cin,fileName);

        ifstream infile(fileName);
        string junior = "Jr.";
        string junior1= "Jr.,";

        //makes temp strings that the info will be read into
        string header, year, award, winner, name, film;
        //takes in the header of the file
        //and checks if we can actually use and access the file
        if (getline(infile, header))
        {
            //makes sure that its the right file with the right header
            int sizeDeleted = header.size()-27;
            header.erase(27,sizeDeleted);

            if((header=="Year,Award,Winner,Name,Film") || (header=="Year,Award,Winner,Name,Film,"))
            {
                read=false;

            }
            else
            {
                //if the header doesn't match then the file is in a wrong format and we need another file
                cout<<"Header does not seem to match the actor database, please try another file: ";
            }
            if(!read) {
                //takes in all of the useful info from the file
                // that is separated by commans and new lines
                while (getline(infile, year, ','))
                {
                    getline(infile, award, ',');
                    getline(infile, winner, ',');
                    getline(infile, name, ',');

                    //removes quotation marks
                    name.erase(remove(name.begin(), name.end(), '\"'), name.end());

                    getline(infile, film, '\n');

                    //FOR EXTRA CREDIT CHECKING THE COMMA
                    if(film[film.size()-1]==',')
                    {
                        film.erase(film.size()-1,1);
                    }

                    film.erase(remove(film.begin(), film.end(), '\"'), film.end());

                    //make sure that the film name goes in the right way
                    std::string::size_type position = film.find(junior);
                    if (position != std::string::npos) {
                        film.erase(position, junior.length() + 1);
                        name.append(" Jr.");
                    }

                    //make a struct where you'll be reading all of the info into
                    actors actors_Struct;

                    //put the info into the structs
                    actors_Struct.Year = year;
                    actors_Struct.Award = award;


                    //keep on putting info into structs
                    actors_Struct.Winner = winner;
                    actors_Struct.Name = name;
                    actors_Struct.Film = film;

                    //make a vector full of structs
                    actorVector.push_back(actors_Struct);
                }
            }
        }
            //if you cannot read in the header then there is no file
        else {
            cout << "Cannot open your actors file! try again" << endl;
        }
    }
    return false;
}

bool addActor(BSTree<actors,string> *act)
{
    string name;
    bool yesno=true;
    string film,winner;
    string award;
    string input;
    char winChar;
    int year;
    actors actor_Add;

    //enters character NAME
    cout<<"Enter name: ";
    getline(cin,name);
    actor_Add.Name=name;

    //enters the movie YEAR
    //make sure that they input int
    cout<<"Enter year: ";
    year=takeInint();

    //make an int into a string
    string y = to_string(year);
    actor_Add.Year = y;

    //get actors MOVIE NAME
    cout<<"Enter film: ";
    cin.ignore();
    getline(cin,film);
    actor_Add.Film=film;

    //gets the WINNER
    //takes in the user input and sets it equal to true or false
    while(yesno)
    {
        cout << "Enter if the actor won th medal or not y/n";
        cin >> winChar;
        //makes sure that the user put in thr right coordinates
        if((winChar=='y')||(winChar=='n'))
        {
            //if the user did then set it equal to it
            if(winChar=='y')
            {
                winner="1";
            } else
            {
                winner= "0";
            }
            actor_Add.Winner=winner;
            yesno = false;
        }
    }

    //takes in users actor award
    cout<<"Input actors award";
    cin.ignore();
    getline(cin,award);
    actor_Add.Award=award;

    //adds it to the tree
    act->addNode(actor_Add.Name,actor_Add);
}

bool searchForActorAndModify(BSTree<actors,string> *act)
{
    string actor_LookedFor;
    Node<actors,string> *newAct;
    bool yesno=true;
    //takes in actor name
    cout << "Who would you like to search for?(Search by the field that the tree was sorted by) ";
    getline(cin, actor_LookedFor);

    //launches the find node function in the binarytree.hpp
    newAct = act->findNode(actor_LookedFor);
    //if actor is not found return actor is not found
    if (newAct == nullptr)
    {
        cout<<"Actor not found"<<endl<<endl;
        return false;
    }

    //if actor was found then take in the data and edit it
    actors data=newAct->Data();

    //makes all of the variables for the actor
    bool change = true;
    string choice;
    string filmName;
    string awards;
    int year;
    string input;
    char winChar;
    string winner;

    //asks the user what would they like to change and takes in a char variable
    cout<<"What would you like to change?"<<endl;
    //makes a loop that only the user can exit
    while(change) {
        //prints out all of the data that can be edited
        cout<<"Name: "<<data.Name<<endl;
        cout<<"Year: "<<data.Year<<endl;
        cout<<"Film: "<<data.Film<<endl;
        cout<<"Awards: "<<data.Award<<endl;
        cout<<"Winner? "<<data.Winner<<endl<<endl;

        cout << "A.Year" << endl;
        cout << "B.film" << endl;
        cout << "C.awards" << endl;
        cout << "D.winnrer?" << endl;
        cout << "Q.exit the edit" << endl;

        //gets user choice and makes sure its a char
        getline(cin,choice);
        char c = choice[0];

        //user choices
        switch (c) {
            //pick a to change year
            case 'a':
            case 'A': {
                cout << "Enter year: ";
                year = takeInint();
                //make an int into a string
                string y = to_string(year);
                data.Year = y;
                cin.ignore();
            }
                break;
                //pick b to change film
            case 'b':
            case 'B':
                cout << "film: ";
                getline(cin, filmName);
                data.Film = filmName;
                break;
                //pick c to change awards
            case 'c':
            case 'C':
                cout << "awards: ";
                getline(cin, awards);
                data.Award = awards;
                break;
                //pick d to change winner
            case 'd':
            case 'D':
                while(yesno)
                {
                    cout << "Enter if the actor won th medal or not y/n";
                    cin >> winChar;
                    //makes sure that the user put in thr right coordinates
                    if((winChar=='y')||(winChar=='n'))
                    {
                        //if the user did then set it equal to it
                        if(winChar=='y')
                        {
                            winner="1";
                        } else
                        {
                            winner= "0";
                        }
                        data.Winner=winner;
                        yesno = false;
                    }
                }
                data.Winner = winner;
                break;
                //exits
            case 'Q':
            case 'q':
            {
                //asks user if they want to change their edits or not
                bool loop = true;
                while (loop) {
                    char choice2;
                    cout << "Save changes? y/n ";
                    cin >> choice2;
                    switch (choice2) {
                        //if yes then save all of the settings
                        case 'y':
                        case 'Y':
                            newAct->setData(data);
                            change = false;
                            loop = false;
                            break;
                            // if no then return 0 and everything goes back to normal
                        case 'N':
                        case 'n':
                            return false;
                            //if the user inputs the wrong choice as again
                        default:
                            cout << "I dont understand you" << endl;
                            break;
                    }
                }
                cin.ignore();
            }
                break;
                //if the user picks the wrong option ask again
            default:
                cout << "Wrong choice!" << endl;
                break;
        }
    }
}

bool searchForActorPartial(BSTree<actors,string> *act)
{
    //sets a node equal to the root of the tree
    string choice,temp;
    string year;
    string dududu;
    bool menu = true;
    bool menu2 = true;
    //prints out the options

    while(menu)
    {
        //prints out the menu and makes a new answerTree
        BSTree <actors,string> *answersTree = new BSTree<actors, string>;
        Node<actors,string> *node = act->Root();
        cout <<"This is partial search!"<<endl;
        //menu options
        cout <<"What would you like to search by?(Case sensitive)"<<endl
             <<"A. search by name"<<endl
             <<"B. search by year"<<endl
             <<"C. search by award"<<endl
             <<"D. search by winner"<<endl
             <<"E. search by film"<<endl
             <<"Q. Exit"<<endl;

        //takes in user choice
        getline(cin, choice);
        char c = choice[0];
        //lets the user pick options
        switch (c)
        {
            case 'A':
            case 'a':
                //cleans out the vector of answers
                oof.clear();
                //takes in user input and what they'd like to search by
                cout << "Enter name: ";
                getline(cin, temp);
                //does the partial search with users input
                searchActorNamePartial(node, temp);
                //prints out the vector of answers
                cout<<"Your results: "<<endl;
                printOOF();
                //if there are more than 1 answer then search through the answers again
                if(oof.size()>1)
                {
                    //turns the answer vector into a binary tree
                    AddResultsToTree(answersTree);
                    while (menu2) {
                        //takes in user input and checks if they want to searc again
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        //if yes, then search the answers
                        switch (a) {
                            case 'y':
                            case 'Y':
                                searchForActorAnswerP(answersTree);
                                break;
                                //if no then go back to partial searching menu
                            case 'n':
                            case 'N':
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'B':
            case 'b':
                //clears out the vector tree
                oof.clear();
                //takes in user input by what they want to search
                cout << "Enter year: ";
                getline(cin,year);
                //does a partial search with the user input
                searchActorYearPartial(node,year);
                //prints out the user results and adds them into the tree of answers
                cout<<"Your results: "<<endl;
                printOOF();
                AddResultsToTree(answersTree);
                //sees if the user wants to search the answers
                while(menu2)
                {
                    cout<<"Search again? y/n"<<endl;
                    getline(cin, choice);

                    char a = choice[0];
                    switch (a)
                    {
                        case 'y':
                        case 'Y':
                            //if yes then call the search answers function
                            searchForActorAnswerP(answersTree);
                            break;
                        case 'n':
                        case 'N':
                            //if no then go back to the partial search menu
                            menu2=false;
                            break;
                        default:
                            cout<<"Wrong choice"<<endl;
                            break;
                    }
                }
                break;
            case 'C':
            case 'c':
                //cleans out the user vector of answers
                oof.clear();
                //takes in user input for the search
                cout << "Enter award: ";
                getline(cin, temp);
                //searches for the input
                searchActorAwardPartial(node,temp);
                //prints out the answers
                cout<<"Your results: "<<endl;
                printOOF();
                //adds answers to the tree
                AddResultsToTree(answersTree);
                //see what the user wants to do with those answers
                while(menu2)
                {
                    cout<<"Search again? y/n"<<endl;
                    getline(cin, choice);

                    char a = choice[0];
                    switch (a)
                    {
                        case 'y':
                        case 'Y':
                            //if the user wants to search them again then call function to search them again
                            searchForActorAnswerP(answersTree);
                            break;
                        case 'n':
                        case 'N':
                            //if not then go back to the menu
                            menu2=false;
                            break;
                        default:
                            cout<<"Wrong choice"<<endl;
                            break;
                    }
                }
                break;
            case 'd':
            case 'D':
                //cleans out the user vector of answers
                oof.clear();
                //takes in user input for the search
                cout << "Enter the amount of times won: ";
                getline(cin, temp);
                //searches for the input
                searchActorWonPartial(node,temp);
                //prints out the answers
                cout<<"Your results: "<<endl;
                printOOF();
                //adds answers to the tree
                AddResultsToTree(answersTree);
                //see what the user wants to do with those answers
                while(menu2)
                {
                    cout<<"Search again? y/n"<<endl;
                    getline(cin, choice);

                    char a = choice[0];
                    switch (a)
                    {
                        case 'y':
                        case 'Y':
                            //if the user wants to search them again then call function to search them again
                            searchForActorAnswerP(answersTree);
                            break;
                        case 'n':
                        case 'N':
                            //if not then go back to the menu
                            menu2=false;
                            break;
                        default:
                            cout<<"Wrong choice"<<endl;
                            break;
                    }
                }
                break;
            case 'E':
            case 'e':
                //cleans out the user vector of answers
                oof.clear();
                //takes in user input for the search
                cout << "Enter film: ";
                getline(cin, temp);
                //searches for the input
                searchActorFilmPartial(node,temp);
                //prints out the answers
                cout<<"Your results: "<<endl;
                printOOF();
                //adds answers to the tree
                AddResultsToTree(answersTree);
                //see what the user wants to do with those answers
                while(menu2)
                {
                    cout<<"Search again? y/n"<<endl;
                    getline(cin, choice);

                    char a = choice[0];
                    switch (a)
                    {
                        case 'y':
                        case 'Y':
                            //if the user wants to search them again then call function to search them again
                            searchForActorAnswerP(answersTree);
                            break;
                        case 'n':
                        case 'N':
                            //if not then go back to the menu
                            menu2=false;
                            break;
                        default:
                            cout<<"Wrong choice"<<endl;
                            break;
                    }
                }
                break;
            case 'Q':
            case 'q':
                menu = false;
                break;
            default:
                break;
        }
    }
}

bool searchForActorAnswerP(BSTree<actors,string> *act)
{
    //sets a node equal to the root of the tree
    string choice,temp;
    string year;
    string dududu;
    bool menu = true;
    //prints out the options


    while(menu)
    {
        //prints out the menu and makes a new answerTree
        Node<actors,string> *node = act->Root();
        cout <<"This is partial searches answer search!"<<endl;
        //menu options
        cout <<"What would you like to search the ANSWERS by?(Case sensitive)"<<endl
             <<"A. search by name"<<endl
             <<"B. search by year"<<endl
             <<"C. search by award"<<endl
             <<"D. search by winner"<<endl
             <<"E. search by film"<<endl
             <<"Q. Exit"<<endl;

        //takes in user choice
        getline(cin, choice);
        char c = choice[0];
        //lets the user pick options
        switch (c)
        {
            case 'A':
            case 'a':
                //cleans out user's answer vector
                oof.clear();
                cout << "Enter name: ";
                getline(cin, temp);
                //takes in user input
                searchActorNamePartial(node, temp);
                //looks for that input and prints it out
                cout<<"Your results: "<<endl;
                printOOF();
                break;
            case 'B':
            case 'b':
                //cleans out userns answer vector
                oof.clear();
                cout << "Enter year: ";
                getline(cin,year);
                //takes in user input and searches the tree of answers with it
                searchActorYearPartial(node,year);
                //prints out the results
                cout<<"Your results: "<<endl;
                printOOF();
                break;
            case 'C':
            case 'c':
                //cleans out users answers vector
                oof.clear();
                //takes in user input to search thru answers
                cout << "Enter award: ";
                getline(cin, temp);
                //looks for those answers
                searchActorAwardPartial(node,temp);
                //prints out those answers
                cout<<"Your results: "<<endl;
                printOOF();
                break;
            case 'd':
            case 'D':
                //cleans out users answers vector
                oof.clear();
                //rakes in user input for search w/ it
                cout << "Enter won: ";
                getline(cin,dududu);
                //looks for that input
                searchActorWonPartial(node,dududu);
                //prints out the results
                cout<<"Your results: "<<endl;
                printOOF();
                break;
            case 'E':
            case 'e':
                //cleans out users answers vector
                oof.clear();
                //rakes in user input for search w/ it
                cout << "Enter film: ";
                getline(cin, temp);
                //looks for that input
                searchActorFilmPartial(node,temp);
                //prints out the results
                cout<<"Your results: "<<endl;
                printOOF();
                break;
            case 'Q':
            case 'q':
                menu = false;
                break;
            default:
                break;
        }
    }
}

//exactly the same as search for actor partial but instead of looking for a substing inside of the data strings,
//simply compares the input and data looks for identical material
bool searchForActorFull(BSTree<actors,string> *act)
{
    bool menu = true;
    string choice;
    string temp;
    string year;
    string dududu;
    bool menu2= true;

    BSTree <actors,string> *answersTree = new BSTree<actors, string>;
    while(menu)
    {
        Node<actors,string> *node = act->Root();
        cout<<"This is complete search!"<<endl;
        cout <<"What would you like to search by?"<<endl
             <<"A. search by name"<<endl
             <<"B. search by year"<<endl
             <<"C. search by award"<<endl
             <<"D. search by winner"<<endl
             <<"E. search by film"<<endl
             <<"Q. Exit"<<endl;

        //takes in user choice
        getline(cin, choice);
        char c = choice[0];
        string re;
        switch (c)
        {
            case 'A':
            case 'a':
                oof.clear();
                cout << "Enter name: ";
                getline(cin, temp);
                searchActorNameFull(node, temp);
                cout<<"Your results: "<<endl;
                printOOF();
                if(oof.size()>1)
                {
                    AddResultsToTree(answersTree);
                    while (menu2) {
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                searchForActorAnswerF(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'B':
            case 'b':
                oof.clear();
                cout << "Enter year: ";
                getline(cin,year);
                searchActorYearFull(node,year);
                cout<<"Your results: "<<endl;
                printOOF();
                if(oof.size()>1)
                {
                    AddResultsToTree(answersTree);
                    while (menu2) {
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                searchForActorAnswerF(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'C':
            case 'c':
                oof.clear();
                cout << "Enter award: ";
                getline(cin, temp);
                temp.append(" ");
                searchActorAwardFull(node,temp);
                cout<<"Your results: "<<endl;
                printOOF();
                if(oof.size()>1)
                {
                    AddResultsToTree(answersTree);
                    while (menu2) {
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                searchForActorAnswerF(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'd':
            case 'D':
                oof.clear();
                cout << "Enter won: ";
                getline(cin,dududu);
                searchActorWonFull(node,dududu);
                cout<<"Your results: "<<endl;
                printOOF();
                if(oof.size()>1)
                {
                    AddResultsToTree(answersTree);
                    while (menu2) {
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                searchForActorAnswerF(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'E':
            case 'e':
                oof.clear();
                cout << "Enter film: ";
                getline(cin, temp);
                temp.append(" ");
                searchActorFilmFull(node,temp);
                cout<<"Your results: "<<endl;
                printOOF();
                if(oof.size()>1)
                {
                    AddResultsToTree(answersTree);
                    while (menu2) {
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                searchForActorAnswerF(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'Q':
            case 'q':
                menu = false;
                break;
            default:
                break;
        }
    }
}
bool searchForActorAnswerF(BSTree<actors,string> *act)
{
    bool menu = true;
    string choice;
    string temp;
    string year;
    string dududu;
    while(menu)
    {
        Node<actors,string> *node = act->Root();
        cout<<"You are complete searching the answers now!"<<endl;
        cout <<"What would you like to search your answers by?"<<endl
             <<"A. search by name"<<endl
             <<"B. search by year"<<endl
             <<"C. search by award"<<endl
             <<"D. search by winner"<<endl
             <<"E. search by film"<<endl
             <<"Q. Exit"<<endl;

        //takes in user choice
        getline(cin, choice);
        char c = choice[0];
        string re;
        switch (c)
        {
            case 'A':
            case 'a':
                oof.clear();
                cout << "Enter name: ";
                getline(cin, temp);
                searchActorNameFull(node, temp);
                cout<<"Your results: "<<endl;
                printOOF();
                break;
            case 'B':
            case 'b':
                oof.clear();
                cout << "Enter year: ";
                getline(cin,year);
                searchActorYearFull(node,year);
                cout<<"Your results: "<<endl;
                printOOF();
                break;
            case 'C':
            case 'c':
                oof.clear();
                cout << "Enter award: ";
                getline(cin, temp);
                temp.append(" ");
                searchActorAwardFull(node,temp);
                cout<<"Your results: "<<endl;
                printOOF();
                break;
            case 'd':
            case 'D':
                oof.clear();
                cout << "Enter won: ";
                getline(cin,dududu);
                searchActorWonFull(node,dududu);
                cout<<"Your results: "<<endl;
                printOOF();
                break;
            case 'E':
            case 'e':
                oof.clear();
                cout << "Enter film: ";
                getline(cin, temp);
                temp.append(" ");
                searchActorFilmFull(node,temp);
                cout<<"Your results: "<<endl;
                printOOF();
                break;
            case 'Q':
            case 'q':
                menu = false;
                break;
            default:
                break;
        }
    }
}

void sortActor(vector<actors> actorVector)
{
    //prints out the menu options
    cout<<"What would you like to sort by?"<<endl;
    bool menu = true, menu2=true;
    char choice;
    string c;
    string a;
    //creates the menu that keeps on printing out users available sort options
    while(menu)
    {
        cout<<"A. Sort by Year"<<endl
            <<"B. Sort by Award"<<endl
            <<"C. Sort by Winner"<<endl
            <<"D. Sort by Film"<<endl
            <<"Q. Exit"<<endl;
        //takes in user input for the menu
        getline(cin, c);
        choice=c[0];
        switch(choice)
        {
            case 'A':
            case 'a':
            {
                //makes a new binary tree
                BSTree<actors, string> *year = new BSTree<actors, string>;
                //adds all of the actors from to the tree from the beginning
                for(int i=0;i<actorVector.size()-1;i++)
                {
                    year->addNode(actorVector[i].Year,actorVector[i]);
                }
                //asks if they want to print the answers into the file
                cout<<"Print sorted results to files?y/n";
                getline (cin,c);
                choice = c[0];
                while(menu2)
                {
                    switch(choice)
                    {
                        //if yes then simply print everything out
                        case 'y':
                        case 'Y':
                            printToFileActor(year);
                            menu2 = false;
                            break;
                            //if no then leave the menu
                        case 'N':
                        case 'n':
                            menu2 = false;
                            break;
                        default:
                            break;
                    }
                }
                //delete that tree
                year->~BSTree();
            }
                break;
            case 'B':
            case 'b':
            {
                //makes a new binary tree
                BSTree<actors, string> *award = new BSTree<actors, string>;
                //adds all of the actors from to the tree from the beginning
                for (int i = 0; i < actorVector.size() - 1; i++)
                {
                    award->addNode(actorVector[i].Award, actorVector[i]);
                }
                //asks if they want to print the answers into the file
                cout<<"Print sorted results to files?y/n";
                getline (cin,c);
                choice = c[0];
                while(menu2)
                {
                    switch(choice)
                    {
                        //if yes then simply print everything out
                        case 'y':
                        case 'Y':
                            printToFileActor(award);
                            break;
                            //if no then leave the menu
                        case 'N':
                        case 'n':
                            menu2 = false;
                            break;
                        default:
                            break;
                    }
                }
                //deletes the tree
                award->~BSTree();
            }
                break;
            case 'C':
            case 'c':
            {
                //makes a new binary tree
                BSTree<actors, string> *winner = new BSTree<actors, string>;
                //adds all of the actors from to the tree from the beginning
                for (int i = 0; i < actorVector.size() - 1; i++)
                {
                    winner->addNode(actorVector[i].Winner, actorVector[i]);
                }
                //asks if they want to print the answers into the file
                cout<<"Print sorted results to files?y/n";
                getline (cin,c);
                choice = c[0];
                while(menu2)
                {
                    switch(choice)
                    {
                        //if yes then simply print everything out
                        case 'y':
                        case 'Y':
                            printToFileActor(winner);
                            break;
                            //if no then leave the menu
                        case 'N':
                        case 'n':
                            menu2 = false;
                            break;
                        default:
                            break;
                    }
                }
                //deletes the tree
                winner->~BSTree();
            }
                break;
            case 'D':
            case 'd':
            {
                //makes a new binary tree
                BSTree<actors, string> *film = new BSTree<actors, string>;
                //adds all of the actors from to the tree from the beginning
                for (int i = 0; i < actorVector.size() - 1; i++)
                {
                    film->addNode(actorVector[i].Film, actorVector[i]);
                }
                //asks if they want to print the answers into the file
                cout<<"Print sorted results to files?y/n";
                getline (cin,c);
                choice = c[0];
                while(menu2)
                {
                    switch(choice)
                    {
                        //if yes then simply print everything out
                        case 'y':
                        case 'Y':
                            printToFileActor(film);
                            break;
                            //if no then leave the menu
                        case 'N':
                        case 'n':
                            menu2 = false;
                            break;
                        default:
                            break;
                    }
                }
                //deletes the tree
                film->~BSTree();
            }
                break;
            case 'Q':
            case 'q':
                menu = false;
                break;
            default:
                cout<<"Wrong choice"<<endl;
                break;
        }
    }
}

void AddResultsToTree(BSTree<actors,string> *answers)
{
    //takes the results from binary complete and partial search and stores thme into another tree so they can be
    //searched again
    actors ans;
    for(int i=0;i<oof.size();i++)
    {
        ans = oof[i]->Data();
        answers->addNode(ans.Name,ans);
    }
}

void printToFileActor(BSTree<actors,string> *act)
{
    //makes variables for printing
    string fileName;
    //makes a node equal to the root of the actor tree to start from the beginning
    Node<actors,string> *node = act->Root();
    vector<actors> vec;
    //make a vector out of the tree
    treeToVec(act,node,vec);
    ofstream out;

    //takes in user input and sees where they'd like to print the tree to
    cout <<"What file would you like to print to";
    getline(cin,fileName);

    //if the file cannot be open then say cannot be open
    out.open(fileName);
    if(!out.is_open())
    {
        cout<<"Sorry file couldn't be opened"<<endl;
        return;
    }
    //print out the vector of the tree into the file
    out<<"Name,Year,Award,Winner,Film\n";
    for(int i =0; i<vec.size();i++)
    {
        out<<vec[i].Name<<",";
        out<<vec[i].Year<<",";
        out<<vec[i].Award<<",";
        out<<vec[i].Winner<<",";
        out<<vec[i].Film<<"\n";
    }
    out.close();
}

template <typename DATATYPE, typename KEYTYPE>
void treeToVec(BSTree<DATATYPE,KEYTYPE> *act, Node<DATATYPE,KEYTYPE> *node,vector<DATATYPE> &treeActors)
{
    //if there is still a node on the left go to the left
    if(node == nullptr)
    {
        return;
    }

    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        treeToVec(act, node->Right(),treeActors);
    }
    //add the current node to the vector
    treeActors.push_back(node->Data());

    //if there is a space on the right go to the right
    if(node->Left()!= nullptr)
    {
        treeToVec(act, node->Left(),treeActors);
    }

}

template <typename DATATYPE, typename KEYTYPE>
bool searchAndDelete(BSTree<DATATYPE,KEYTYPE> *del)
{
    //simply asks for user input and looks for that actor
    string actor_LookedFor;

    cout << "Who would you like to delete? (Case sensitive, type in exact name)";
    getline(cin, actor_LookedFor);

    //calls function delete node and delets that actor
    del->deleteNode(actor_LookedFor);
}

//MOVIES
bool readFromFileMovies(string fileName, vector<movies> &movieVector)
{

    bool read= true;

    while(read) {
        cout << "Enter the Movies's file name!";
        getline(cin, fileName);

        ifstream infile(fileName);
        string header, name, year, nominations, rating, duration, genre1, genre2, release, metacritic, synopsis;

        //if you can read in the header then the file was open
        if (getline(infile, header)) {
            read = false;
            while (getline(infile, name, ',')) {
                //reading in all of the info from a file
                getline(infile, year, ',');
                getline(infile, nominations, ',');
                getline(infile, rating, ',');
                getline(infile, duration, ',');
                getline(infile, genre1, ',');
                getline(infile, genre2, ',');
                getline(infile, release, ',');
                getline(infile, metacritic, ',');
                getline(infile, synopsis, '\n');

                //making a string year into an int
                movies movie_Struct;

                //putting YEAR and NAME into the struct

                //checks if there are no spaces in the beginning
                if (name[0] == ' ') {
                    name.erase(0, 1);
                }

                movie_Struct.Name = name;
                movie_Struct.Year = year;

                //putting NOMINATIONS into the struct
                movie_Struct.nominations = nominations;

                //putting RATING into the struct
                movie_Struct.ratings = rating;


                //putting DURATION into the struct
                movie_Struct.duration = duration;

                //putting GENRE1, GENRE2 and RELEASE into the struct
                movie_Struct.genre = genre1;
                movie_Struct.genre2 = genre2;
                movie_Struct.release = release;

                //making an int from a string for metacrytic

                //putting METACRYTIC into the struct
                movie_Struct.metacrytic = metacritic;

                //deletes the arrows from the synopsis

                movie_Struct.synopsis = synopsis;

                movieVector.push_back(movie_Struct);
            }
        } else {
            cout << "File not found!" << endl;
        }
    }

}

template <typename DATATYPE, typename KEYTYPE>
bool fromVectoTree(vector<DATATYPE> &Vector, BSTree<DATATYPE,KEYTYPE> *tree)
{
    //mid term f the vector
    int moviesCount=0;
    //adds all of the movie from to the tree from the beginning
    for (auto &i : Vector) {
        tree->addNode(i.Name, i);
        moviesCount++;
    }
    cout<<"There are: "<<moviesCount<<" infos in our database"<<endl;
}

bool addMovie(BSTree<movies,string> *mov)
{
    string name, genre1, genre2, release, synopsis, y;
    int temp;
    double tem;

    movies newMovie;

    //takes in new movies name
    //enters character NAME
    cout<<"Enter name: ";
    getline(cin,name);

    //makes sure that there is no space at the beginning
    if(name[0]==' ')
    {
        name.erase(name[0]);
    }

    newMovie.Name=name;

    //takes in users year
    cout<<"Enter year: ";
    temp=takeInint();

    //make an int into a string
    y = to_string(temp);
    newMovie.Year = y;


    //takes in users nominations
    cout << "Enter the amount of nominations: ";
    temp=takeInint();

    //make an int into a string
    y = to_string(temp);
    newMovie.nominations = y;


    //takes in user rating
    cout << "Enter rating: ";
    tem = takeIndouble();

    y = to_string(tem);
    newMovie.ratings=y;


    //takes in movie duration
    cout << "Enter movie duration: ";
    temp=takeInint();

    //make an int into a string
    y = to_string(temp);
    newMovie.duration = y;


    //takes in both of the movie genres
    cin.ignore();
    cout<<"Enter genre1 of the movie: ";
    getline(cin,genre1);
    newMovie.genre=genre1;

    cout<<"Enter the second genre of the movie, if there isnt one input \"-\" :";
    getline(cin,genre2);
    newMovie.genre2=genre2;

    //takes in movie release month
    cout<<"Enter movie release: ";
    getline(cin,release);
    newMovie.release=release;

    //takes in the meracritic score
    cout<<"Enter Metacritic: ";
    temp=takeInint();

    //make an int into a string
    y = to_string(temp);
    newMovie.metacrytic = y;

    cin.ignore();
    //takes in synopsis from the user
    cout<<"Enter synopsis: ";
    getline(cin,synopsis);
    newMovie.synopsis=synopsis;

    //adds the actor to the tree
    mov->addNode(newMovie.Name,newMovie);
}

bool searchForMovieAndModify(BSTree<movies,string> *mov)
{

    string movie_LookedFor;
    Node<movies,string> *newMov;
    //takes the name of the movie
    cout << "What movie are you looking for?(Case sensitive, type in exact name) ";
    getline(cin, movie_LookedFor);

    if(movie_LookedFor[0]==' ')
    {
        movie_LookedFor.erase(0,1);
    }

    //launches the find node function in the binarytree.hpp
    newMov = mov->findNode(movie_LookedFor);
    //if movie is not found return movie is not found
    if (newMov == nullptr)
    {
        cout<<"Sorry movie not found"<<endl<<endl;
        return false;
    }

    //if movie was found then take in the data and edit it
    movies data=newMov->Data();

    //prints out all of the data that can be edited of the movie


    //makes all of the variables for the actor
    bool change = true;
    string choice;
    string genre1, genre2;
    string release;
    string synopsis;
    string meta;
    int z;

    //asks the user what would they like to change and takes in a char variable
    cout<<"What would you like to change?"<<endl;
    //makes a loop that only the user can exit
    while(change) {

        cout<<"Name: \t"<<data.Name<<endl;
        cout<<"Year: \t"<<data.Year<<endl;
        cout<<"Num of Nominations: \t"<<data.nominations<<endl;
        cout<<"Ratings: \t"<<data.ratings<<endl;
        cout<<"Duration: \t"<<data.duration<<" minutes"<<endl;
        cout<<"Genre 1: \t"<<data.genre <<endl;
        cout<<"Genre 2: \t"<<data.genre2<<endl;
        cout<<"Release: \t"<<data.release<<endl;
        cout<<"Metacrytics: \t"<<data.metacrytic<<endl;
        cout<<"Synopsis: \t"<<data.synopsis<<endl<<endl;

        cout << "A.Year" << endl;
        cout << "B.num. of nominations" << endl;
        cout << "C.ratings?" << endl;
        cout << "D.duration" << endl;
        cout << "E.genre1 "<<endl;
        cout << "F.genre2 "<<endl;
        cout << "G.release"<<endl;
        cout << "H.metacrytics"<<endl;
        cout << "I.synopsis"<<endl;
        cout << "Q.exit the editor"<<endl<<endl;

        //gets user choice and makes sure its a char
        getline(cin,choice);
        char c = choice[0];

        //user choices
        switch (c) {
            //pick a to change year of the movie
            case 'a':
            case 'A':
                cout <<"Enter year ";
                data.Year=takeInint();
                break;
                //pick b to change the amout of nominations
            case 'b':
            case 'B':
                cout << "number of nominations: ";
                data.nominations=takeInint();
                break;
                //pick c to change ratings
            case 'c':
            case 'C':
                cout << "ratings: ";
                data.ratings=takeIndouble();
                break;
                //pick d to change duration of the movie
            case 'd':
            case 'D':
                cout << "duration";
                data.duration=takeInint();
                break;
            case 'e':
            case 'E':
                //takes in user input and changes movies genre 1
                cout <<"Genre 1: ";
                getline(cin,genre1);
                data.genre=genre1;
                break;
            case 'F':
            case 'f':
                //takes in user input and changes movies genre 2
                cout<<"Genre 2: ";
                getline(cin, genre2);
                data.genre2=genre2;
                break;
            case 'G':
            case 'g':
                //takes in user input and changes movies release month
                cout<<"Release month: ";
                getline(cin,release);
                data.release=release;
                break;
            case 'H':
            case 'h':
                //takes in user score and changes movies metacrytics score
                cout<<"Metacrytics score: ";
                z=takeInint();
                meta=to_string(z);
                break;
            case 'I':
            case 'i':
                //takes in user input and changes movies synopsis
                cout<<"Movie's synopsis: ";
                getline(cin,synopsis);
                data.synopsis=synopsis;
                break;
            case 'Q':
            case 'q': {
                //exits
                //asks user if they want to change their edits or not
                bool loop = true;
                while (loop) {
                    char choice2;
                    cout << "Save changes? y/n ";
                    cin >> choice2;
                    switch (choice2)
                    {
                        //if yes then save all of the changes that were done to the movie
                        case 'y':
                        case 'Y':
                            newMov->setData(data);
                            change = false;
                            loop = false;
                            break;
                            // if no then return 0 and everything goes back to normal
                        case 'N':
                        case 'n':
                            return false;
                            //if the user inputs the wrong choice as again
                        default:
                            cout << "I dont understand you" << endl;
                            break;
                    }
                    cin.ignore();
                }
                break;
            }
                //if the user picks the wrong option ask again
            default:
                break;
        }
    }
}

//exactly the same as full search for movies but instead of calling the option to compare the string directly
//it calls to look for a substring inside of a string
bool searchForMovieAnswersP(BSTree<movies,string> *mov)
{
    string choice,temp;
    string year;
    bool menu = true;
    //prints out the options

    while(menu)
    {
        //sets a node equal to the root of the tree
        Node<movies,string> *node = mov->Root();
        cout<<"This is partial ANSWER search!"<<endl;
        cout <<"What would you like to search by?(Case sensitive)"<<endl
             <<"A. search by name"<<endl
             <<"B. search by year"<<endl
             <<"C. search by nominations"<<endl
             <<"D. search by rating"<<endl
             <<"E. search by duration"<<endl
             <<"F. search by genre1"<<endl
             <<"G. search by genre2"<<endl
             <<"H. search by release"<<endl
             <<"I. search by metacrytic"<<endl
             <<"J. search by synopsis"<<endl
             <<"Q. Exit"<<endl;

        //takes in user choice
        getline(cin, choice);
        char c = choice[0];
        string re;
        switch (c)
        {
            case 'A':
            case 'a':
                oi.clear();
                cout << "Enter movie name: ";
                getline(cin, temp);
                searchMoviesNamePartial(node, temp);
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'B':
            case 'b':
                oi.clear();
                cout << "Enter year: ";
                getline(cin,year);
                searchMoviesYearPartial(node,year);
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'C':
            case 'c':
                oi.clear();
                cout << "Enter the amount of nominations: ";
                getline(cin, temp);
                searchMoviesNomPartial(node,temp);
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'd':
            case 'D':
                oi.clear();
                cout << "Enter rating: ";
                getline(cin, temp);
                searchMoviesRatingPartial(node, temp);
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'E':
            case 'e':
                oi.clear();
                cout << "Enter duration: ";
                getline(cin, temp);
                searchMoviesDurationPartial(node,temp);
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'F':
            case 'f':
                oi.clear();
                cout << "Enter genre 1: ";
                getline(cin, temp);
                searchMoviesGenre1Partial(node, temp);
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'G':
            case 'g':
                oi.clear();
                cout << "Enter genre 2: ";
                getline(cin, temp);
                searchMoviesGenre2Partial(node, temp);
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'H':
            case 'h':
                oi.clear();
                cout << "Enter movie's release month: ";
                getline(cin, temp);
                searchMoviesReleasePartial(node, temp);
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'I':
            case 'i':
                oi.clear();
                cout << "Enter Metacrytic: ";
                getline(cin,temp);
                searchMoviesMetaPartial(node,temp);
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'J':
            case 'j':
                cout << "Enter Synopsis: ";
                getline(cin,temp);
                searchMoviesSynPartial(node,temp);
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'Q':
            case 'q':
                menu = false;
                break;
            default:
                break;
        }
    }
}
bool searchForMoviePartial(BSTree<movies,string> *mov)
{
    string choice,temp;
    string year,rating;
    bool menu = true;
    bool menu2= true;
    //prints out the options

    while(menu)
    {
        BSTree <movies,string> *answersTree = new BSTree<movies, string>;
        //sets a node equal to the root of the tree
        Node<movies,string> *node = mov->Root();
        cout<<"This is partial search!"<<endl;
        cout <<"What would you like to search by?"<<endl
             <<"A. search by name"<<endl
             <<"B. search by year"<<endl
             <<"C. search by nominations"<<endl
             <<"D. search by rating"<<endl
             <<"E. search by duration"<<endl
             <<"F. search by genre1"<<endl
             <<"G. search by genre2"<<endl
             <<"H. search by release"<<endl
             <<"I. search by metacrytic"<<endl
             <<"Q. Exit"<<endl;

        //takes in user choice
        getline(cin, choice);
        char c = choice[0];
        string re;
        switch (c)
        {
            case 'A':
            case 'a':
                oi.clear();
                cout << "Enter movie name: ";
                getline(cin, temp);
                searchMoviesNamePartial(node, temp);
                cout<<"Your results: "<<endl;
                printOI();
                if(oi.size()>1)
                {
                    AddResultsToTree2(answersTree);
                    while (menu2) {
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                searchForMovieAnswersP(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'B':
            case 'b':
                oi.clear();
                cout << "Enter year: ";
                getline(cin,year);
                searchMoviesYearPartial(node,year);
                cout<<"Your results: "<<endl;
                printOI();
                if(oi.size()>1)
                {
                    AddResultsToTree2(answersTree);
                    while (menu2) {
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                searchForMovieAnswersP(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'C':
            case 'c':
                oi.clear();
                cout << "Enter the amount of nominations: ";
                getline(cin,year);
                searchMoviesNomPartial(node,year);
                cout<<"Your results: "<<endl;
                printOI();
                if(oi.size()>1)
                {
                    AddResultsToTree2(answersTree);
                    while (menu2) {
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                searchForMovieAnswersP(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'd':
            case 'D':
                oi.clear();
                cout << "Enter rating: ";
                getline(cin,rating);
                searchMoviesRatingPartial(node, rating);
                cout<<"Your results: "<<endl;
                printOI();
                if(oi.size()>1)
                {
                    AddResultsToTree2(answersTree);
                    while (menu2) {
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                searchForMovieAnswersP(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'E':
            case 'e':
                oi.clear();
                cout << "Enter duration: ";
                getline(cin,year);
                searchMoviesDurationPartial(node,year);
                cout<<"Your results: "<<endl;
                printOI();
                if(oi.size()>1)
                {
                    AddResultsToTree2(answersTree);
                    while (menu2) {
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                searchForMovieAnswersP(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'F':
            case 'f':
                oi.clear();
                cout << "Enter genre 1: ";
                getline(cin, temp);
                searchMoviesGenre1Partial(node, temp);
                cout<<"Your results: "<<endl;
                printOI();
                if(oi.size()>1)
                {
                    AddResultsToTree2(answersTree);
                    while (menu2) {
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                searchForMovieAnswersP(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'G':
            case 'g':
                oi.clear();
                cout << "Enter genre 2: ";
                getline(cin, temp);
                searchMoviesGenre2Partial(node, temp);
                cout<<"Your results: "<<endl;
                printOI();
                if(oi.size()>1)
                {
                    AddResultsToTree2(answersTree);
                    while (menu2) {
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                searchForMovieAnswersP(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'H':
            case 'h':
                oi.clear();
                cout << "Enter movie's release month: ";
                getline(cin, temp);
                searchMoviesReleasePartial(node, temp);
                cout<<"Your results: "<<endl;
                printOI();
                if(oi.size()>1)
                {
                    AddResultsToTree2(answersTree);
                    while (menu2) {
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                searchForMovieAnswersP(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'I':
            case 'i':
                oi.clear();
                cout << "Enter Metacrytic: ";
                getline(cin,year);
                searchMoviesMetaPartial(node,year);
                cout<<"Your results: "<<endl;
                printOI();
                if(oi.size()>1)
                {
                    AddResultsToTree2(answersTree);
                    while (menu2) {
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                searchForMovieAnswersP(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'J':
            case 'j':
                oi.clear();
                cout << "Enter Synopsis: ";
                getline(cin,year);
                searchMoviesSynPartial(node,year);
                cout<<"Your results: "<<endl;
                printOI();
                if(oi.size()>1)
                {
                    AddResultsToTree2(answersTree);
                    while (menu2) {
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                searchForMovieAnswersP(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }

                break;
            case 'Q':
            case 'q':
                menu = false;
                break;
            default:
                break;
        }
    }
}

bool searchForMovieAnswersF(BSTree<movies,string> *mov)
{
    string choice,temp;
    string year;
    bool menu = true;
    //prints out the options
    while(menu)
    {
        //sets a node equal to the root of the tree
        Node<movies,string> *node = mov->Root();
        cout<<"This is complete of the answers for the movies search!"<<endl;
        cout <<"What would you like to search by?(Case sensitive)"<<endl
             <<"A. search by name"<<endl
             <<"B. search by year"<<endl
             <<"C. search by nominations"<<endl
             <<"D. search by rating"<<endl
             <<"E. search by duration"<<endl
             <<"F. search by genre1"<<endl
             <<"G. search by genre2"<<endl
             <<"H. search by release"<<endl
             <<"I. search by metacrytic"<<endl
             <<"J. search by synopsis"<<endl
             <<"Q. Exit"<<endl;

        //takes in user choice
        getline(cin, choice);
        char c = choice[0];
        string re;
        switch (c)
        {
            case 'A':
            case 'a':
                //clears out the answers vector
                oi.clear();
                //takes in user input and searches for exact matching answet
                cout << "Enter movie name: ";
                getline(cin, temp);
                searchMoviesNameFull(node, temp);
                //prints out all of the results of the answer searches
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'B':
            case 'b':
                //clears out the answers vector
                oi.clear();
                //takes in user input and searches for exact matching answet
                cout << "Enter year: ";
                getline(cin,year);
                searchMoviesYearFull(node,year);
                //prints out all of the results of the answer searches
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'C':
            case 'c':
                //clears out the answers vector to make sure that its clear
                oi.clear();
                //takes in user input and searches for exact matching answer
                cout << "Enter the amount of nominations: ";
                getline(cin, temp);
                searchMoviesNomFull(node,temp);
                //prints out all of the results of the answer searches
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'd':
            case 'D':
                //clears out the answers vector
                oi.clear();
                //takes in user input and searches for exact matching answer
                cout << "Enter rating: ";
                getline(cin, temp);
                searchMoviesRatingFull(node, temp);
                //prints out all of the results of the answer searches
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'E':
            case 'e':
                //clears out the answers vector
                oi.clear();
                //takes in user input and searches for exact matching answer
                cout << "Enter duration: ";
                getline(cin, temp);
                searchMoviesDurationFull(node,temp);
                //prints out all of the results of the answer searches
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'F':
            case 'f':
                //clears out the answers vector
                oi.clear();
                //takes in user input and searches for exact matching answer
                cout << "Enter genre 1: ";
                getline(cin, temp);
                searchMoviesGenre1Full(node, temp);
                //prints out all of the results of the answer searches
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'G':
            case 'g':
                //clears out the answers vector
                oi.clear();
                //takes in user input and searches for exact matching answer
                cout << "Enter genre 2: ";
                getline(cin, temp);
                searchMoviesGenre2Full(node, temp);
                //prints out all of the results of the answer searches
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'H':
            case 'h':
                //clears out the answers vector
                oi.clear();
                //takes in user input and searches for exact matching answer
                cout << "Enter movie's release month: ";
                getline(cin, temp);
                searchMoviesReleasePartial(node, temp);
                //prints out all of the results of the answer searches
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'I':
            case 'i':
                //clears out the answers vector
                oi.clear();
                //takes in user input and searches for exact matching answer
                cout << "Enter Metacrytic: ";
                getline(cin,temp);
                searchMoviesMetaFull(node,temp);
                //prints out all of the results of the answer searches
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'J':
            case 'j':
                //clears out the answers vector
                oi.clear();
                //takes in user input and searches for exact matching answet
                cout << "Enter Synopsis: ";
                getline(cin,temp);
                searchMoviesSynFull(node,temp);
                //prints out all of the results of the answer searches
                cout<<"Your results: "<<endl;
                printOI();
                break;
            case 'Q':
            case 'q':
                menu = false;
                break;
            default:
                break;
        }
    }
}
bool searchForMovieFull(BSTree<movies,string> *mov)
{
    string choice,temp;
    string year;
    string rating;
    bool menu = true;
    bool menu2=true;
    //prints out the options

    while(menu)
    {
        BSTree <movies,string> *answersTree = new BSTree<movies, string>;
        //sets a node equal to the root of the tree
        Node<movies,string> *node = mov->Root();
        cout<<"This is complete search!"<<endl;
        cout <<"What would you like to search by?"<<endl
             <<"A. search by name"<<endl
             <<"B. search by year"<<endl
             <<"C. search by nominations"<<endl
             <<"D. search by rating"<<endl
             <<"E. search by duration"<<endl
             <<"F. search by genre1"<<endl
             <<"G. search by genre2"<<endl
             <<"H. search by release"<<endl
             <<"I. search by metacrytic"<<endl
             <<"Q. Exit"<<endl;

        //takes in user choice
        getline(cin, choice);
        char c = choice[0];
        string re;
        switch (c)
        {
            case 'A':
            case 'a':
                //clears out the answer vector for the movies
                oi.clear();
                //takes in user input to search for the movies
                cout << "Enter movie name: ";
                getline(cin, temp);
                //does complete search and looks for the exactly matching strings
                searchMoviesNameFull(node, temp);
                //prints out all of the results from a searxh
                cout<<"Your results: "<<endl;
                printOI();
                //if there are more than one answer asks if the user wants to search through the answers
                if(oi.size()>1)
                {
                    while (menu2)
                    {
                        //sees if the user wants to go through the search more times
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                //if yes then search through the vector and make a tree
                                AddResultsToTree2(answersTree);
                                searchForMovieAnswersF(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                //if no then no
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'B':
            case 'b':
                //clears out the answer vector for the movies
                oi.clear();
                //takes in user input to search for the movies
                cout << "Enter a year: ";
                getline(cin, temp);
                //does complete search and looks for the exactly matching strings
                searchMoviesYearFull(node, temp);
                //prints out all of the results from a searxh
                cout<<"Your results: "<<endl;
                printOI();
                //if there are more than one answer asks if the user wants to search through the answers
                if(oi.size()>1)
                {
                    while (menu2)
                    {
                        //sees if the user wants to go through the search more times
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                //if yes then search through the vector and make a tree
                                AddResultsToTree2(answersTree);
                                searchForMovieAnswersF(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                //if no then no
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'C':
            case 'c':
                //clears out the answer vector for the movies
                oi.clear();
                //takes in user input to search for the movies
                cout << "Enter a Nominations: ";
                getline(cin, temp);
                //does complete search and looks for the exactly matching strings
                searchMoviesNomFull(node, temp);
                //prints out all of the results from a searxh
                cout<<"Your results: "<<endl;
                printOI();
                //if there are more than one answer asks if the user wants to search through the answers
                if(oi.size()>1)
                {
                    while (menu2)
                    {
                        //sees if the user wants to go through the search more times
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                //if yes then search through the vector and make a tree
                                AddResultsToTree2(answersTree);
                                searchForMovieAnswersF(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                //if no then no
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'd':
            case 'D':
                //clears out the answer vector for the movies
                oi.clear();
                //takes in user input to search for the movies
                cout << "Enter a rating: ";
                getline(cin, rating);
                //does complete search and looks for the exactly matching strings
                searchMoviesRatingFull(node, rating);
                //prints out all of the results from a searxh
                cout<<"Your results: "<<endl;
                printOI();
                //if there are more than one answer asks if the user wants to search through the answers
                if(oi.size()>1)
                {
                    while (menu2)
                    {
                        //sees if the user wants to go through the search more times
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                //if yes then search through the vector and make a tree
                                AddResultsToTree2(answersTree);
                                searchForMovieAnswersF(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                //if no then no
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'E':
            case 'e':
                //clears out the answer vector for the movies
                oi.clear();
                //takes in user input to search for the movies
                cout << "Enter duration: ";
                getline(cin, temp);
                //does complete search and looks for the exactly matching strings
                searchMoviesDurationFull(node, temp);
                //prints out all of the results from a searxh
                cout<<"Your results: "<<endl;
                printOI();
                //if there are more than one answer asks if the user wants to search through the answers
                if(oi.size()>1)
                {
                    while (menu2)
                    {
                        //sees if the user wants to go through the search more times
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                //if yes then search through the vector and make a tree
                                AddResultsToTree2(answersTree);
                                searchForMovieAnswersF(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                //if no then no
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'F':
            case 'f':
                //clears out the answer vector for the movies
                oi.clear();
                //takes in user input to search for the movies
                cout << "Enter first genre: ";
                getline(cin, temp);
                //does complete search and looks for the exactly matching strings
                searchMoviesGenre1Full(node, temp);
                //prints out all of the results from a searxh
                cout<<"Your results: "<<endl;
                printOI();
                //if there are more than one answer asks if the user wants to search through the answers
                if(oi.size()>1)
                {
                    while (menu2)
                    {
                        //sees if the user wants to go through the search more times
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                //if yes then search through the vector and make a tree
                                AddResultsToTree2(answersTree);
                                searchForMovieAnswersF(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                //if no then no
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'G':
            case 'g':
                //clears out the answer vector for the movies
                oi.clear();
                //takes in user input to search for the movies
                cout << "Enter genre 2: ";
                getline(cin, temp);
                //does complete search and looks for the exactly matching strings
                searchMoviesGenre2Full(node, temp);
                //prints out all of the results from a search
                cout<<"Your results: "<<endl;
                printOI();
                //if there are more than one answer asks if the user wants to search through the answers
                if(oi.size()>1)
                {
                    while (menu2)
                    {
                        //sees if the user wants to go through the search more times
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                //if yes then search through the vector and make a tree
                                AddResultsToTree2(answersTree);
                                searchForMovieAnswersF(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                //if no then no
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'H':
            case 'h':
                //clears out the answer vector for the movies
                oi.clear();
                //takes in user input to search for the movies
                cout << "Enter a release: ";
                getline(cin, temp);
                //does complete search and looks for the exactly matching strings
                searchMoviesReleaseFull(node, temp);
                //prints out all of the results from a searxh
                cout<<"Your results: "<<endl;
                printOI();
                //if there are more than one answer asks if the user wants to search through the answers
                if(oi.size()>1)
                {
                    while (menu2)
                    {
                        //sees if the user wants to go through the search more times
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                //if yes then search through the vector and make a tree
                                AddResultsToTree2(answersTree);
                                searchForMovieAnswersF(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                //if no then no
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'I':
            case 'i':
                //clears out the answer vector for the movies
                oi.clear();
                //takes in user input to search for the movies
                cout << "Enter a Metacritic: ";
                getline(cin, temp);
                //does complete search and looks for the exactly matching strings
                searchMoviesMetaFull(node, temp);
                //prints out all of the results from a searxh
                cout<<"Your results: "<<endl;
                printOI();
                //if there are more than one answer asks if the user wants to search through the answers
                if(oi.size()>1)
                {
                    while (menu2)
                    {
                        //sees if the user wants to go through the search more times
                        cout << "Search the answers? y/n" << endl;
                        getline(cin, choice);
                        char a = choice[0];
                        switch (a) {
                            case 'y':
                            case 'Y':
                                //if yes then search through the vector and make a tree
                                AddResultsToTree2(answersTree);
                                searchForMovieAnswersF(answersTree);
                                break;
                            case 'n':
                            case 'N':
                                //if no then no
                                menu2 = false;
                                break;
                            default:
                                cout << "Wrong choice" << endl;
                                break;
                        }
                    }
                }
                break;
            case 'Q':
            case 'q':
                menu = false;
                break;
            default:
                break;
        }
    }
}

bool sortMovie(vector<movies> moviesVector)
{
    //prints out the menu options
    cout<<"What would you like to sort by?";
    bool menu = true, menu2= true;
    char choice;
    string c;
    //creates the menu that keeps on printing out users available sort options
    while(menu)
    {
        cout<<"A. Sort by Year"<<endl
            <<"B. Sort by Nominations"<<endl
            <<"C. Sort by Rating"<<endl
            <<"D. Sort by Duration"<<endl
            <<"E. Sort by Genre1"<<endl
            <<"F. Sort by Genre2"<<endl
            <<"G. Sort by Release"<<endl
            <<"H. Sort By Metacritics"<<endl
            <<"I. Sort by Synopsis"<<endl
            <<"Q. Exit"<<endl;
        getline(cin, c);
        choice=c[0];
        switch(choice)
        {
            case 'A':
            case 'a':
            {
                BSTree<movies, string> *year = new BSTree<movies, string>;
                //adds all of the actors from to the tree from the beginning
                for(int i=0;i<moviesVector.size()-1;i++)
                {
                    year->addNode(moviesVector[i].Year,moviesVector[i]);
                }
                //takes in user input if they want to print out new tree to a file
                cout<<"Print sorted results to files?y/n";
                getline (cin,c);
                choice = c[0];
                while(menu2)
                {
                    switch(choice)
                    {
                        case 'y':
                        case 'Y':
                            //if yes then calls a function to print out the binary tree
                            printToFileMovie(year);
                            menu2 = false;
                            break;
                        case 'N':
                        case 'n':
                            //if not the leave the submenu
                            menu2 = false;
                            break;
                        default:
                            break;
                    }
                }
                //deletes the new tree from the memory
                year->~BSTree();
            }
                break;
            case 'B':
            case 'b':
            {
                BSTree<movies, string> *nominations = new BSTree<movies, string>;
                //adds all of the actors from to the tree from the beginning
                for(int i=0;i<moviesVector.size()-1;i++)
                {
                    nominations->addNode(moviesVector[i].Year,moviesVector[i]);
                }
                //takes in user input if they want to print out new tree to a file
                cout<<"Print sorted results to files?y/n";
                getline (cin,c);
                choice = c[0];
                while(menu2)
                {
                    switch(choice)
                    {
                        case 'y':
                        case 'Y':
                            //if yes then calls a function to print out the binary tree
                            printToFileMovie(nominations);
                            menu2 = false;
                            break;
                        case 'N':
                        case 'n':
                            //if not the leave the submenu
                            menu2 = false;
                            break;
                        default:
                            break;
                    }
                }
                //deletes the new tree from the memory
                nominations->~BSTree();
            }
                break;
            case 'C':
            case 'c':
            {
                BSTree<movies, string> *rating = new BSTree<movies, string>;
                //adds all of the actors from to the tree from the beginning
                for(int i=0;i<moviesVector.size()-1;i++)
                {
                    rating->addNode(moviesVector[i].Year,moviesVector[i]);
                }
                //takes in user input if they want to print out new tree to a file
                cout<<"Print sorted results to files?y/n";
                getline (cin,c);
                choice = c[0];
                while(menu2)
                {
                    switch(choice)
                    {
                        case 'y':
                        case 'Y':
                            //if yes then calls a function to print out the binary tree
                            printToFileMovie(rating);
                            menu2 = false;
                            break;
                        case 'N':
                        case 'n':
                            //if not the leave the submenu
                            menu2 = false;
                            break;
                        default:
                            break;
                    }
                }
                //deletes the new tree from the memory
                rating->~BSTree();
            }
                break;
            case 'D':
            case 'd':
            {
                BSTree<movies, string> *duration = new BSTree<movies, string>;
                //adds all of the actors from to the tree from the beginning
                for(int i=0;i<moviesVector.size()-1;i++)
                {
                    duration->addNode(moviesVector[i].Year,moviesVector[i]);
                }
                //takes in user input if they want to print out new tree to a file
                cout<<"Print sorted results to files?y/n";
                getline (cin,c);
                choice = c[0];
                while(menu2)
                {
                    switch(choice)
                    {
                        case 'y':
                        case 'Y':
                            //if yes then calls a function to print out the binary tree
                            printToFileMovie(duration);
                            menu2 = false;
                            break;
                        case 'N':
                        case 'n':
                            //if not the leave the submenu
                            menu2 = false;
                            break;
                        default:
                            break;
                    }
                }
                //deletes the new tree from the memory
                duration->~BSTree();
            }
                break;
            case 'E':
            case 'e':
            {
                BSTree<movies, string> *g = new BSTree<movies, string>;
                //adds all of the actors from to the tree from the beginning
                for(int i=0;i<moviesVector.size()-1;i++)
                {
                    g->addNode(moviesVector[i].Year,moviesVector[i]);
                }
                //takes in user input if they want to print out new tree to a file
                cout<<"Print sorted results to files?y/n";
                getline (cin,c);
                choice = c[0];
                while(menu2)
                {
                    switch(choice)
                    {
                        case 'y':
                        case 'Y':
                            //if yes then calls a function to print out the binary tree
                            printToFileMovie(g);
                            menu2 = false;
                            break;
                        case 'N':
                        case 'n':
                            //if not the leave the submenu
                            menu2 = false;
                            break;
                        default:
                            break;
                    }
                }
                //deletes the new tree from the memory
                g->~BSTree();
            }
                break;
            case 'F':
            case 'f':
            {
                BSTree<movies, string> *g2 = new BSTree<movies, string>;
                //adds all of the actors from to the tree from the beginning
                for(int i=0;i<moviesVector.size()-1;i++)
                {
                    g2->addNode(moviesVector[i].Year,moviesVector[i]);
                }
                //takes in user input if they want to print out new tree to a file
                cout<<"Print sorted results to files?y/n";
                getline (cin,c);
                choice = c[0];
                while(menu2)
                {
                    switch(choice)
                    {
                        case 'y':
                        case 'Y':
                            //if yes then calls a function to print out the binary tree
                            printToFileMovie(g2);
                            menu2 = false;
                            break;
                        case 'N':
                        case 'n':
                            //if not the leave the submenu
                            menu2 = false;
                            break;
                        default:
                            break;
                    }
                }
                //deletes the new tree from the memory
                g2->~BSTree();
            }
                break;
            case 'G':
            case 'g':
            {
                BSTree<movies, string> *rel = new BSTree<movies, string>;
                //adds all of the actors from to the tree from the beginning
                for(int i=0;i<moviesVector.size()-1;i++)
                {
                    rel->addNode(moviesVector[i].Year,moviesVector[i]);
                }
                //takes in user input if they want to print out new tree to a file
                cout<<"Print sorted results to files?y/n";
                getline (cin,c);
                choice = c[0];
                while(menu2)
                {
                    switch(choice)
                    {
                        case 'y':
                        case 'Y':
                            //if yes then calls a function to print out the binary tree
                            printToFileMovie(rel);
                            menu2 = false;
                            break;
                        case 'N':
                        case 'n':
                            //if not the leave the submenu
                            menu2 = false;
                            break;
                        default:
                            break;
                    }
                }
                //deletes the new tree from the memory
                rel->~BSTree();
            }
                break;
            case 'H':
            case 'h':
            {
                BSTree<movies, string> *meta = new BSTree<movies, string>;
                //adds all of the actors from to the tree from the beginning
                for(int i=0;i<moviesVector.size()-1;i++)
                {
                    meta->addNode(moviesVector[i].Year,moviesVector[i]);
                }
                //takes in user input if they want to print out new tree to a file
                cout<<"Print sorted results to files?y/n";
                getline (cin,c);
                choice = c[0];
                while(menu2)
                {
                    switch(choice)
                    {
                        case 'y':
                        case 'Y':
                            //if yes then calls a function to print out the binary tree
                            printToFileMovie(meta);
                            menu2 = false;
                            break;
                        case 'N':
                        case 'n':
                            //if not the leave the submenu
                            menu2 = false;
                            break;
                        default:
                            break;
                    }
                }
                //deletes the new tree from the memory
                meta->~BSTree();
            }
                break;
            case 'I':
            case 'i':
            {
                BSTree<movies, string> *s = new BSTree<movies, string>;
                //adds all of the actors from to the tree from the beginning
                for(int i=0;i<moviesVector.size()-1;i++)
                {
                    s->addNode(moviesVector[i].Year,moviesVector[i]);
                }
                //takes in user input if they want to print out new tree to a file
                cout<<"Print sorted results to files?y/n";
                getline (cin,c);
                choice = c[0];
                while(menu2)
                {
                    switch(choice)
                    {
                        case 'y':
                        case 'Y':
                            //if yes then calls a function to print out the binary tree
                            printToFileMovie(s);
                            menu2 = false;
                            break;
                        case 'N':
                        case 'n':
                            //if not the leave the submenu
                            menu2 = false;
                            break;
                        default:
                            break;
                    }
                }
                //deletes the new tree from the memory
                s->~BSTree();
            }
                break;
            case 'Q':
            case 'q':
                menu = false;
                break;
            default:
                cout<<"Wrong choice"<<endl;
                break;
        }

    }
}

void AddResultsToTree2(BSTree<movies,string> *answers)
{
    //takes a vector and adds the results into a small tree
    movies ans;
    for(int i=0;i<oi.size();i++)
    {
        ans = oi[i]->Data();
        answers->addNode(ans.Name,ans);
    }
}
void printToFileMovie(BSTree<movies,string> *mov)
{
    //creates the info for the write out
    string fileName;
    Node<movies,string> *node = mov->Root();;
    vector<movies> vec;
    //turns the tree into a vector
    treeToVec(mov,node,vec);
    ofstream out;

    //takes in user input to create a file
    cout <<"What file would you like to print to";
    getline(cin,fileName);

    //create that file
    out.open(fileName);
    if(!out.is_open())
    {
        cout<<"Sorry file couldn't be opened"<<endl;
        return;
    }

    //insert the header into the file and print the file out
    out<<"name,year,nominations,rating,duration,genre1,genre2,release,metacritic,synopsis\n";
    for(int i =0; i<vec.size();i++)
    {
        out<<vec[i].Name<<",";
        out<<vec[i].Year<<",";
        out<<vec[i].nominations<<",";
        out<<vec[i].ratings<<",";
        out<<vec[i].duration<<",";
        out<<vec[i].genre<<",";
        out<<vec[i].genre2<<",";
        out<<vec[i].release<<",";
        out<<vec[i].metacrytic<<",";
        out<<vec[i].synopsis<<"\n";
    }
    out.close();
}


//SEARCHES
//Partial SEARCH ACTOR
void searchActorNamePartial(Node<actors,string> *node, string name)
{
    //if something is found then put it into the vector
    if(node->Data().Name.find(name)!=std::string::npos)
    {
        oof.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchActorNamePartial(node->Left(),name);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchActorNamePartial(node->Right(),name );
    }
}
void searchActorYearPartial(Node<actors,string> *node, string year)
{
    //if something is found then put it into the vector
    if(node->Data().Year.find(year)!=std::string::npos)
    {
        oof.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchActorYearPartial(node->Left(),year);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchActorYearPartial(node->Right(),year );
    }
}
void searchActorAwardPartial(Node<actors,string> *node, string award)
{
    //if something is found then put it into the vector
    if(node->Data().Award.find(award)!=std::string::npos)
    {
        oof.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchActorAwardPartial(node->Left(),award);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchActorAwardPartial(node->Right(),award);
    }
}
void searchActorWonPartial(Node<actors,string> *node, string won)
{
    //if something is found then put it into the vector
    if(node->Data().Winner==won)
    {
        oof.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchActorWonPartial(node->Left(),won);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchActorWonPartial(node->Right(),won);
    }
}
void searchActorFilmPartial(Node<actors,string> *node, string film)
{
    //if something is found then put it into the vector
    if(node->Data().Film.find(film)!=std::string::npos)
    {
        oof.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchActorFilmPartial(node->Left(),film);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchActorFilmPartial(node->Right(),film);
    }
}

//Full SEARCH ACTOR
void searchActorNameFull(Node<actors,string> *node, string name)
{
    //checks if there is no space at the begining of the string
    if(name[name.size()-1]==' ')
    {
        name.erase(name.size()-1,1);
    }

    bool wrong=false;

    //checks if two strings have exact same size
    if(node->Data().Name.size()== name.size())
    {
        //checks if two strings are exactly the same
        for(int i =0; i<node->Data().Name.size()-1;i++)
        {
            //if not the same then screw it
            if(node->Data().Name[i]!=name[i])
            {
                wrong=true;
                break;
            }
        }
        //if they are the same then add them to the vector
        if(!wrong)
        {
            oof.push_back(node);
        }
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchActorNameFull(node->Left(),name);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchActorNameFull(node->Right(),name );
    }
}
void searchActorYearFull(Node<actors,string> *node, string year)
{
    //if something is found then put it into the vector
    if(node->Data().Year== year)
    {
        oof.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchActorYearFull(node->Left(),year);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchActorYearFull(node->Right(),year );
    }
}
void searchActorAwardFull(Node<actors,string> *node, string award)
{
    if(award[award.size()-1]==' ')
    {
        award.erase(award.size()-1,1);
    }

    bool wrong=false;

    //checks if two strings have exact same size
    if(node->Data().Award.size()== award.size())
    {
        //checks if two strings are exactly the same
        for(int i =0; i<node->Data().Award.size()-1;i++)
        {
            //if not the same then screw it
            if(node->Data().Award[i]!=award[i])
            {
                wrong=true;
                break;
            }
        }
        //if they are the same then add them to the vector
        if(!wrong)
        {
            oof.push_back(node);
        }
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchActorAwardFull(node->Left(),award);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchActorAwardFull(node->Right(),award);
    }
}
void searchActorWonFull(Node<actors,string> *node, string won)
{
    //if something is found then put it into the vector
    if(node->Data().Winner==won)
    {
        oof.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchActorWonFull(node->Left(),won);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchActorWonFull(node->Right(),won);
    }
}
void searchActorFilmFull(Node<actors,string> *node, string film)
{
    //makes sure that there is no space at the end of te film name
    if(film[film.size()-1]==' ')
    {
        film.erase(film.size()-1,1);
    }
    bool wrong=false;

    //checks if two strings have exact same size
    if(node->Data().Film.size()== film.size())
    {
        //checks if two strings are exactly the same
        for(int i =0; i<node->Data().Film.size()-1;i++)
        {
            //if not the same then screw it
            if(node->Data().Film[i]!=film[i])
            {
                wrong=true;
                break;
            }
        }
        //if they are the same then add them to the vector
        if(!wrong)
        {
            oof.push_back(node);
        }
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchActorFilmFull(node->Left(),film);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchActorFilmFull(node->Right(),film);
    }
}

//Partial SEARCH Movies
void searchMoviesNamePartial(Node<movies,string> *node, string name)
{
    //if something is found then put it into the vector
    if(node->Data().Name.find(name)!=std::string::npos)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesNamePartial(node->Left(),name);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesNamePartial(node->Right(),name );
    }
}
void searchMoviesYearPartial(Node<movies,string> *node, string year)
{
    //if something is found then put it into the vector
    if(node->Data().Year.find(year)!=std::string::npos)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesYearPartial(node->Left(),year);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesYearPartial(node->Right(),year );
    }
}
void searchMoviesNomPartial(Node<movies,string> *node, string nom)
{
    //if something is found then put it into the vector
    if(node->Data().nominations.find(nom)!=std::string::npos)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesNomPartial(node->Left(),nom);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesNomPartial(node->Right(),nom);
    }
}
void searchMoviesRatingPartial(Node<movies,string> *node, string rating)
{
    //if something is found then put it into the vector
    if(node->Data().ratings.find(rating)!=std::string::npos)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesRatingPartial(node->Left(),rating);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesRatingPartial(node->Right(),rating);
    }
}
void searchMoviesDurationPartial(Node<movies,string> *node, string duration)
{
    //if something is found then put it into the vector
    if(node->Data().duration.find(duration)!=std::string::npos)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesDurationPartial(node->Left(),duration);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesDurationPartial(node->Right(),duration);
    }
}
void searchMoviesGenre1Partial(Node<movies,string> *node, string genre)
{
    //if something is found then put it into the vector
    if(node->Data().genre.find(genre)!=std::string::npos)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesGenre1Partial(node->Left(),genre);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesGenre1Partial(node->Right(),genre );
    }
}
void searchMoviesGenre2Partial(Node<movies,string> *node, string genre)
{
    //if something is found then put it into the vector
    if(node->Data().genre2.find(genre)!=std::string::npos)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesGenre2Partial(node->Left(),genre);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesGenre2Partial(node->Right(),genre );
    }
}
void searchMoviesReleasePartial(Node<movies,string> *node, string release)
{
    //if something is found then put it into the vector
    if(node->Data().release.find(release)!=std::string::npos)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesReleasePartial(node->Left(),release);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesReleasePartial(node->Right(),release );
    }
}
void searchMoviesMetaPartial(Node<movies,string> *node, string score)
{
    //if something is found then put it into the vector
    if(node->Data().metacrytic.find(score)!=std::string::npos)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesMetaPartial(node->Left(),score);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesMetaPartial(node->Right(),score );
    }
}
void searchMoviesSynPartial(Node<movies,string> *node, string syn)
{
    //if something is found then put it into the vector
    if(node->Data().synopsis.find(syn)!=std::string::npos)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesReleasePartial(node->Left(),syn);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesReleasePartial(node->Right(),syn);
    }
}


//Full Search movies
void searchMoviesNameFull(Node<movies,string> *node, string name)
{
    //if something is found then put it into the vector
    if(name[name.size()-1]==' ')
    {
        name.erase(name.size()-1,1);
    }

    bool wrong=false;

    //checks if two strings have exact same size
    if(node->Data().Name.size()== name.size())
    {
        //checks if two strings are exactly the same
        for(int i =0; i<node->Data().Name.size()-1;i++)
        {
            //if not the same then screw it
            if(node->Data().Name[i]!=name[i])
            {
                wrong=true;
                break;
            }
        }
        //if they are the same then add them to the vector
        if(!wrong)
        {
            oi.push_back(node);
        }
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesNameFull(node->Left(),name);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesNameFull(node->Right(),name );
    }
}
void searchMoviesYearFull(Node<movies,string> *node, string year)
{
    //if something is found then put it into the vector
    if(node->Data().Year==year)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesYearFull(node->Left(),year);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesYearFull(node->Right(),year );
    }
}
void searchMoviesNomFull(Node<movies,string> *node, string nom)
{
    //if something is found then put it into the vector
    if(node->Data().nominations==nom)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesNomFull(node->Left(),nom);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesNomFull(node->Right(),nom);
    }
}
void searchMoviesRatingFull(Node<movies,string> *node, string rating)
{
    //if something is found then put it into the vector
    if(node->Data().ratings==rating)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesRatingFull(node->Left(),rating);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesRatingFull(node->Right(),rating);
    }
}
void searchMoviesDurationFull(Node<movies,string> *node, string duration)
{
    //if something is found then put it into the vector
    if(node->Data().duration==duration)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesDurationFull(node->Left(),duration);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesDurationFull(node->Right(),duration);
    }
}
void searchMoviesGenre1Full(Node<movies,string> *node, string genre)
{
    //if something is found then put it into the vector
    if(node->Data().genre==genre)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesGenre1Full(node->Left(),genre);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesGenre1Full(node->Right(),genre );
    }
}
void searchMoviesGenre2Full(Node<movies,string> *node, string genre)
{
    //if something is found then put it into the vector
    if(node->Data().genre2==genre)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesGenre2Full(node->Left(),genre);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesGenre2Full(node->Right(),genre );
    }
}
void searchMoviesReleaseFull(Node<movies,string> *node, string release)
{
    //if something is found then put it into the vector
    if(node->Data().release==release)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesReleaseFull(node->Left(),release);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesReleaseFull(node->Right(),release );
    }
}
void searchMoviesMetaFull(Node<movies,string> *node, string score)
{
    //if something is found then put it into the vector
    if(node->Data().metacrytic==score)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesMetaFull(node->Left(),score);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesMetaFull(node->Right(),score );
    }
}
void searchMoviesSynFull(Node<movies,string> *node, string syn)
{
    //if something is found then put it into the vector
    if(node->Data().synopsis.find(syn)!=std::string::npos)
    {
        oi.push_back(node);
    }
    //if there is still a node on the left go to the left
    if(node->Left()!= nullptr)
    {
        searchMoviesSynFull(node->Left(),syn);
    }
    //if there is a node on the right go to the right
    if(node->Right()!= nullptr)
    {
        searchMoviesSynFull(node->Right(),syn);
    }
}

void NominationsMenu()
{
    //prints out welcome to the ec part
    cout<<"Welcome to extra credit part!"<<endl;
    //making a new read in vector
    vector<actors> nominations;
    //takin in the filename
    string filename;

    //creating a new BSTree for the nominations
    BSTree<actors,string> *nominations_Tree = new BSTree<actors,string>;

    //reads in the info into a new BSTree
    cout<<"Enter Nomination's file name! ";
    readFromFileActors(filename,nominations);
    fromVectoTree(nominations,nominations_Tree);

    bool menu= true;
    string choice;
    char c;

    while(menu)
    {
        cout<<"A. Add a Nomination"<<endl
            <<"B. Modify Nomination"<<endl
            <<"C. Delete Nomination"<<endl
            <<"D. Sort Nomination"<<endl
            <<"E. Complete Search Nomination"<<endl
            <<"F. Partial Search Nomination"<<endl
            <<"G. Print to File Nomination"<<endl
            <<"Q. Exit nomination menu"<<endl;
        getline(cin, choice);
        c=choice[0];
        switch (c)
        {
            case 'A':
            case 'a':
                addActor(nominations_Tree);
                break;
            case 'B':
            case 'b':
                searchForActorAndModify(nominations_Tree);
                break;
            case 'C':
            case 'c':
                searchAndDelete(nominations_Tree);
                break;
            case 'd':
            case 'D':
                sortActor(nominations);
                break;
            case 'E':
            case 'e':
                searchForActorFull(nominations_Tree);
                break;
            case 'F':
            case 'f':
                searchForActorPartial(nominations_Tree);
                break;
            case 'G':
            case 'g':
                printToFileActor(nominations_Tree);
                break;
            case 'Q':
            case 'q':
                menu = false;
                break;
            default:
                cout<<"Wrong choice"<<endl;
                break;
        }
    }
}
