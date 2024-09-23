/**------------------------------------------
    Project 2: Search Engine
    Course: CS 251, Fall 2023
    System: Visual Studio Code and Windows 10
    Student Author: Dana Fakhreddine
 ---------------------------------------------**/

// This is a .cpp file you will edit and turn in.

// Remove starter comments and add your own
// comments on each function and on complex code sections.

#include <string>
#include <iostream>
#include "search.h"
#include <map>
using namespace std;


//testing whether cleanToken() works for different series of strings
//outputs solution and student solution to compare
//prerequires function checkPunctuation() to work
void testingCleanToken(){
  //getting a series of different inputs and creating answers for each
  cout<<"testing clean token"<<endl;
  string firstTest = "././././././././dog???????????";
  string answer1 = "dog";
  string secondTest = ",,,,,,banana.bread!!!!";
  string secondAnswer = "banana.bread";
  string thirdTest = "+++++?????CS___251--------";
  string thirdAnswer = "cs___251";
  string fourthTest = "+++";
  string fourthAnswer = "";

  //outputting the string, the answer, and student's solution
  cout<<"string"<<firstTest<<" answer: "<<answer1<<" students solution: "<<cleanToken(firstTest)<<endl;
  cout<<"string"<<secondTest<<" answer: "<<secondAnswer<<" students solution: "<<cleanToken(secondTest)<<endl;
  cout<<"string"<<thirdTest<<" answer: "<<thirdAnswer<<" students solution: "<<cleanToken(thirdTest)<<endl;
  cout<<"string"<<fourthTest<<" answer: "<<fourthAnswer<<" students solution: "<<cleanToken(fourthTest)<<endl;
}

//printing out sets to see solutions 
//function being used in multiple test case functions
void printSolutionsAndAnswer(set<string> print){
  for(auto e: print){
    cout<<e<<endl;
  }
}

//testing whether gatherTokens() accurately parses a string by spaces
//and returns the cleaned version of each string in a set
//prerequires cleanToken() function to work
void testingGatherTokens(){
  cout<<"testing gatherTokens"<<endl;

  //different strings to be tested on 
  string str1 = "Hello! world... CS!! is--- fun^^";
  string str2 = "PLL.. TVD$$$ ST!!! Shadow and bone:)";
  string str3 = "Pop!! ..jazz.band??? rock,music rap>>>";
  string str4 = ".";
  
  //answers for the strings above
  set<string> answer1 = {"cs", "fun", "hello", "is", "world"};
  set<string> answer2 = {"and", "bone", "pll", "shadow", "st", "tvd"};
  set<string> answer3 = {"jazz.band", "pop", "rap", "rock,music"};
  set<string> answer4 = {""};
  
  //testing first string
  cout<<"string: "<<str1<<endl<<" answer should be: ";
  printSolutionsAndAnswer(answer1);
  cout<<" students solution: ";
  printSolutionsAndAnswer(gatherTokens(str1));

  //testing second string
  cout<<"string: "<<str2<<endl<<" answer should be: ";
  printSolutionsAndAnswer(answer2);
  cout<<" students solution: ";
  printSolutionsAndAnswer(gatherTokens(str2));

  //testing third string
  cout<<"string: "<<str3<<endl<<" answer should be: ";
  printSolutionsAndAnswer(answer3);
  cout<<" students solution: ";
  printSolutionsAndAnswer(gatherTokens(str3));

  //testing third string
  cout<<"string: "<<str4<<endl<<" answer should be: ";
  printSolutionsAndAnswer(answer4);
  cout<<" students solution: ";
  printSolutionsAndAnswer(gatherTokens(str4));
}

//printing out map keys and values
//used for testingBuildIndex() function to print out a map
void printMap(map<string, set<string>> index){
  for(auto e: index){
    cout<<e.first<<"-->";
    for(auto &j: e.second){
      cout<<j<<" ";
    }
    cout<<endl;
    }
}

//testing whether buildIndex() correctly makes a map for the words and urls
//prints out the map for different file names and making sure the num 
//of web pages is correct
//pre requires gatherTokens() function to work
void testingBuildIndex(){
  cout<<"testing buildIndex() function:"<<endl;
  map<string, set<string>> index1;
  map<string, set<string>> index2;

  //testing on different file inputs
  string filename1 = "tiny.txt";
  string filename2 = "cplusplus.txt";
  string filename3 = "";

  int count1;
  int count2;

  //outputting maps for each file
  cout<<"for tiny.txt"<<endl;
  count1 = buildIndex(filename1, index1);
  printMap(index1);
  cout<<"count: "<<count1<<endl;

  cout<<"for cplusplus.txt"<<endl;
  count2 = buildIndex(filename2, index2);
  printMap(index2);
  cout<<"count: "<<count2<<endl;
  
  cout<<"for empty string"<<endl;
  buildIndex(filename3, index2);
}

//testing whether queryMatches() function works for returning
//correct set of urls based off of search
//pre requires finalSet() function to work and buildIndex() to work
void testingQueryMatches(){
  cout<<"testing for queryMatches() funtion"<<endl;
  map<string, set<string>> index;

  //different search queries to test
  string sentence1 = "milk +red";
  string sentence2 = "red -fish";
  string sentence3 = "eggs not";

  set<string> one;
  set<string> two;
  set<string> three;

  buildIndex("tiny.txt", index);

  //outputting answers and student solutions
  cout<<"first sentence"<<endl;
  printSolutionsAndAnswer(findQueryMatches(index, sentence1));
  cout<<"second sentence"<<endl;
  printSolutionsAndAnswer(findQueryMatches(index, sentence2));
  cout<<"third sentence"<<endl;
  printSolutionsAndAnswer(findQueryMatches(index, sentence3));
}

//testing searcEngine function
void testSearchEngine(){
  searchEngine("tiny.txt");
  searchEngine("cplusplus.txt");
}

//running all of the tests
void runTests(){
  int userInput;
  cout<<"Choose a num to test certain functions"<<endl;
  cout<<"1.cleanTokens()"<<endl<<"2.gatherTokens()"<<endl<<"3.buildIndex()"<<endl;
  cout<<"4.queryMatches()"<<"Any num for search engine"<<endl;
  cin>>userInput;

  if(userInput == 1){
    testingCleanToken();
  }else if(userInput == 2){
    testingGatherTokens();
  }else if(userInput == 3){
    testingBuildIndex();
  }else if(userInput == 4){
    testingQueryMatches();
  }else{
    testSearchEngine();
  }
}

int main() {
    
    // Use this function to call and test the functions you write inside of
    // search.h.  If you do not call the functions here, nothing will run.

    //run all test cases
    //runTests();

    string filename;
    getline(cin, filename);
    searchEngine(filename);
    
    return 0;
}

