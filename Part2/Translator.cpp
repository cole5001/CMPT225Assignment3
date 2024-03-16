/*
*Translator.cpp
 *
 * Description: Instantiation and use of Dictionary class.
 *              BST-based implementation
 *              Language: Dutch
 *              
 * Author: Cole Ackerman
 * Date of last modification: March. 2024
*/

#include "Dictionary.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "BST.h"
#include "WordPair.h"
#include "ElementAlreadyExistsException.h"
#include "ElementDoesNotExistException.h"
#include "EmptyDataCollectionException.h"
#include "UnableToInsertException.h"

using std::cin;
using std::cout;
using std::ifstream;
using std::nothrow;

void display(WordPair anElement){
  cout << anElement;
}

int main(int argc, char *argv[]) {
  Dictionary* testing = new Dictionary();

  if (testing != nullptr) {
    string aLine = "";
    string aWord = "";
    string englishW = "";
    string translationW = "";
    string filename = "";
    string delimiter = ":";
    size_t pos = 0;
    WordPair translated;

    // Expecting at least a filename on the command line.
    if (argc > 1) {
      filename = argv[1];

      ifstream myFile(filename);
      if (myFile.is_open()) {
        const char* cmd = argv[2];
        const char* dsp = "display ";
        
        // Case where the "display" command is used: print everything and end
        if (argc > 2 && strcmp(cmd, dsp))
          while (getline(myFile,aLine)) {
            pos = aLine.find(delimiter);    
            englishW = aLine.substr(0, pos);
            aLine.erase(0, pos + delimiter.length());
            translationW = aLine;
            WordPair aWordPair(englishW, translationW);
            display(aWordPair);
          }
        // Generate the BST from the data file
        else {
          while (getline(myFile,aLine)) {
            pos = aLine.find(delimiter);    
            englishW = aLine.substr(0, pos);
            aLine.erase(0, pos + delimiter.length());
            translationW = aLine;
            WordPair aWordPair(englishW, translationW);
            testing->put(aWordPair);
          }          
          
          int i = 0;
          while (i != 1) {
            WordPair result = WordPair();
            bool exceptionFlag = false;
            
            // using a try/catch block to catch exception
            try {
              string target;
              cin >> target;
              WordPair targetPair = WordPair(target);
              result = testing->get(targetPair);
            }
            catch (const ElementDoesNotExistException& exc) {
              cout << "***Not Found!***\n";
              exceptionFlag = true;
            }
            
            // Display the WordPair if found 
            if (exceptionFlag==false){
              display(result);
            }
          }
        }
        myFile.close();
      }
      else 
        cout << "Unable to open file" << endl;
    }
    else
      cout << "Missing the data filename!" << endl;
  }
  else  
    cout << "new failed!" << endl;	
  
  return 0;
}