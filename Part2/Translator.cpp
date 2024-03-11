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

void display(WordPair* anElement){
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
    if ( ( argc > 1 ) ) {
      filename = argv[1];

      ifstream myfile(filename);
      if (myfile.is_open()) {
        cout << "Reading from a file:" << endl;  // For debugging purposes
        while ( getline (myfile,aLine) ) {
          pos = aLine.find(delimiter);    
          englishW = aLine.substr(0, pos);
          aLine.erase(0, pos + delimiter.length());
          translationW = aLine;
          WordPair aWordPair(englishW, translationW);
          cout << aWordPair << endl;

          testing->put(aWordPair);
		  // insert aWordPair into "testing" using a try/catch block
        }
        myfile.close();
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