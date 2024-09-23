/**------------------------------------------
    Project 2: Search Engine
    Course: CS 251, Fall 2023
    System: Visual Studio Code and Windows 10
    Student Author: Dana Fakhreddine
 ---------------------------------------------**/

// This is a .h file you will edit and turn in.

// Remove starter comments and add your own
// comments on each function and on complex code sections.

#pragma once


#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <set>
#include <map>
using namespace std;



//removing punctuation from string
//parameters: string called str
//return: a cleaned version of the stirng passed in
string checkPunctuation(string str){
    char firstChar = str[0];
    char lastChar = str[str.size()-1];
    int checkIndex = 0;
    bool checkFirst;
    bool checkLast;
    int stringSize = str.size();

    //looping through string to check
    for(int i = 0; i<stringSize; i++){
            //checking if first char is punctuation
            if(ispunct(firstChar)){
                str.erase(str.begin()+0);
            }
            //checking if last char is punctuation
            if(ispunct(lastChar)){
                str.pop_back();
            }
            //reset first and last char to new characters
            firstChar = str[0];
            lastChar = str[str.size() - 1];
        }
    return str;
}

// checking string contains at least one letter, if yes then clenaing string and converting to lowercase
// parameter: string called s
//return: a cleaned and lowercase string
string cleanToken(string s) {
    string cleanedString;
    int countString = 0;
    string finalCleanedString;

    //counting the amount of alpha chars in a string
    for(int i = 0; i<s.size(); i++){
        if(isalpha(s[i])){
            countString++;
        }
    }

    //checking if string contains at least one letter
    if(countString < 1){
        cleanedString = "";
    }else{
        cleanedString =  checkPunctuation(s);
    }

    //converting to all lowercase
    for(int i = 0; i< cleanedString.size(); i++){
        finalCleanedString += tolower(cleanedString[i]);
    }
    return finalCleanedString;  
}

// getting a string and separating into different words based off spaces and cleaning each word
// parameter: string called text 
//return: set<string> called results
set<string> gatherTokens(string text) {
    set<string> tokens;
    string storeString;
    string cleanedWord;
    stringstream parseString(text);
    
    //dividing the body text into indivdiual tokens
    while(parseString >> storeString){
        //cleaning each token in tokens set
        cleanedWord = cleanToken(storeString);
        //if string is not empty, insert into set
        if(cleanedWord != ""){
            tokens.insert(cleanedWord);
        }
    }    
    return tokens; 
}

// reading in file and creating the inverted index, the map, setting the keys as each word and values as a set of urls
// parameters: string called filename, map of type string and set<string> called index
//return: int called count
int buildIndex(string filename, map<string, set<string>>& index) {
    ifstream readingFile(filename);
    string url;
    string bodyText;
    int pages = 0;
    
    //reading through file
    if(!readingFile.is_open()){
        cout<<"could not find database"<<endl;
        return 0;
    }else{
        //url is first line, and bodyText is the preceding line 
        while(getline(readingFile, url)){
            getline(readingFile, bodyText);
            set<string> temp = gatherTokens(bodyText);

            //setting key equal to word with associated urls as their values
            for(auto &keyWord: temp){
                index[keyWord].insert(url);
            }
            pages ++;
        }
        readingFile.close();
    }
    return pages;
}

//finding the query matches for the different words based off of the modifiers
//using set difference, set intersection, set union
//parameters: map of type string and set<string> called index, vector fo type string called words
//return: set of type string called results
set<string> finalSet(map<string, set<string>>& index, vector<string> words){
    set<string> results;
    
    //first setting the set equal to the urls of first word in vector for comparison later
    results = index.at(cleanToken(words[0]));

    for(int i = 1; i<words.size(); i++){
        string word = words.at(i);
        //making sure you pass through the cleaned version of the word to get urls set
        set<string> currWords = index.at(cleanToken(words.at(i)));
        set<string> tempResults;

        //set intersection if plus modifier
        if(word[0] == '+'){
            set_intersection(results.begin(),results.end(), currWords.begin(), currWords.end(), inserter(tempResults, tempResults.begin()));
        //set difference if minus modifier
        }else if(word[0] == '-'){
            set_difference(results.begin(),results.end(), currWords.begin(), currWords.end(), inserter(tempResults, tempResults.begin()));
        //else, perform set union
        }else{
            set_union(results.begin(),results.end(), currWords.begin(), currWords.end(), inserter(tempResults, tempResults.begin()));
        }
        //set results set to current 
        results = tempResults;
        //clear temp so it can redo process
        tempResults.clear();
    }
    return results;
}

// implementing the search functionality based off different modifiers  
// paramaters: map of type string and set<string> called index, string called sentence
//return: set of type string called result
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    set<string> result;
    stringstream parseWords(sentence);
    string searchWord;
    vector<string> words;
    
    //parsing sentence
    while(parseWords >> searchWord){
        words.push_back(searchWord);
    }

    //if only one word, look for all web pages containing that word
    if(words.size() == 1){
        return index.at(words[0]);
    //if more than one word, calculate the urls based off the modifiers in the sentence(if any)
    }else{
        result = finalSet(index, words);
    }
    return result;  
}

// putting all the functions together, getting input for file name and input for which words user is looking for
// parameters: string called filename
//return: void
void searchEngine(string filename) {
    int pages = 0;
    int uniqueTerms = 0;
    int matchingPages = 0;
    string querySentence;
    map<string, set<string>> index;
    set<string> urls;

    cout<<"Stand by while building index..."<<endl;
    pages = buildIndex(filename, index); 

    //calculating unique terms
    for(auto& e: index){
        uniqueTerms++;
    }
   
    cout<<"Indexed "<<pages<<" pages containing "<<uniqueTerms<<" unique terms"<<endl;

    cout<<endl<<"Enter query sentence (press enter to quit): ";
    getline(cin, querySentence);

    while(querySentence != ""){
        urls = findQueryMatches(index, querySentence);
        
        //counting the amount of matching pages
        for(auto &e: urls){
            matchingPages++;
        }

        cout<<"Found "<<matchingPages<<" matching pages"<<endl;
        //outputting urls
        for(auto &e: urls){
            cout<<e<<endl;
        }
        matchingPages = 0;

        cout<<endl<<"Enter query sentence (press enter to quit): ";
        getline(cin, querySentence);
    }
    cout<<"Thank you for searching!"<<endl;
}