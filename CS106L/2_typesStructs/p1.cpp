/*
Problem:
Given a text file called "words.txt", write a C++ program 
that reads in the file, counts the number of occurrences of each word, 
and prints the results to the console.

The output should be case-sensitive, words in uppercase and lowercase 
should be treated as distinct words.
The new streams we learned about in lecture namely std::ifstream, std::getline, 
and std::stringstream will be helpful here! 
*/
#include<iostream>
#include<fstream>
#include<sstream>
#include<map>

int main() {
    // TODO: Write your code here
    std::fstream file("./words.txt");
    std::string line;
    std::map<std::string, int> wordCount;
    while(getline(file, line)){
        // std::cout<<"!";
        std::stringstream ss(line);
        std::string word;
        while(ss >> word){
            wordCount[word]++;
        }
    }
    for(const auto& pair: wordCount)
        std::cout<<pair.first<<":"<<pair.second<<std::endl;
        
    return 0;
}