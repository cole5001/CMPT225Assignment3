/*
* Dictionary.cpp
 * 
 * Description: Dictonary data collection ADT class.
 *              BST-based implementation.
 *              Duplicated elements not allowed.
 *              
 * Author: Cole Ackerman
 * Date of last modification: March. 2024
*/

#include "Dictionary.h"
#include <iostream>
using std::cout;
using std::endl;

 // Constructor and destructor:
   Dictionary::Dictionary(){                           // Default constructor
        BST();
   }

   Dictionary::Dictionary::~Dictionary(){                            // Destructor 
        keyValuePairs->~BST();
   }
   // Dictionary operations

   // Description: Returns the number of elements currently stored in the Dictionary.
   // Postcondition: This method does not change the Dictionary.
    unsigned int Dictionary::getElementCount() const{
        return keyValuePairs->getElementCount();
    }
    
   // Description: Puts "newElement" (association of key-value) into the Dictionary.
   // Precondition: "newElement" does not already exist in the Dictionary.
   //               This is to say: no duplication allowed.
   // Exception: Throws the exception "UnableToInsertException" 
   //            when newElement cannot be inserted in the Dictionary.  
   // Exception: Throws the exception "ElementAlreadyExistsException" 
   //            if "newElement" already exists in the Dictionary.  
    void Dictionary::put(WordPair & newElement){
        keyValuePairs->insert(newElement);
    }

   // Description: Gets "newElement" (i.e., the associated value of a given key) 
   //              from the Dictionary.
   // Precondition: Dictionary is not empty.
   // Exception: Throws the exception ElementDoesNotExistException
   //            if the key is not found in the Dictionary.
   // Exception: Throws the exception EmptyDataCollectionException if the Dictionary is empty.
   // Postcondition: This method does not change the Dictionary.
    WordPair & Dictionary::get(WordPair & targetElement) const{
        return keyValuePairs->retrieve(targetElement);
    }

   // Description: Prints the content of the Dictionary.
   // Precondition: Dictionary is not empty.
   // Exception: Throws the exception EmptyDataCollectionException if the Dictionary is empty.
   // Postcondition: This method does not change the Dictionary.
    void Dictionary::displayContent(void visit(WordPair &)) const{
        if (keyValuePairs->getElementCount() == 0){
            throw EmptyDataCollectionException("Binary search tree is empty.");
        }
        keyValuePairs->traverseInOrder(visit);
        cout << visit << endl;
    }