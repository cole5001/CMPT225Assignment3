/*
* BST.cpp
* 
* Description: Binary Search Tree data collection ADT class.
*              Link-based implementation.
*              Duplicated elements are not allowed.
*
* Class invariant: It is always a BST.
* 
* Author: Inspired from our textbook
* Date of last modification: Feb. 2024
*/

#include "BST.h"
#include "WordPair.h"
#include <iostream>

using std::cout;
using std::endl;
using std::nothrow;


// You cannot change the prototype of the public methods of this class.
// Remember, if you add public methods to this class, our test driver 
// - the one with which we will mark this assignment - 
// will not know about them since, in order to create it, we will have 
// used only the public method prototypes below.

   //! Can't call constructor/destructor recursively -> use helper function

void BST::copy(BSTNode* currentRoot, BSTNode* newRoot) {
   if (currentRoot == nullptr) {
      newRoot = nullptr;
      return;
   }

   //* Else create new node, copy element from currentRoot and recursively copy from left and right subtree
   newRoot = new BSTNode(currentRoot->element);
   copy(currentRoot->left, newRoot->left);
   copy(currentRoot->right, newRoot->right);
}

void BST::clear(BSTNode* current) {
   // if (current == nullptr)
   //    return;
   if (current != nullptr) {
      clear(current->left);
      clear(current->right);
      delete current;
   }
}

/* Constructors and destructor */

// Default constructor
BST::BST() {}            

// Copy constructor
BST::BST(const BST & aBST) {
   elementCount = aBST.elementCount;
   copy(aBST.root, this->root);
}

// Destructor 
BST::~BST() {
   clear(root);
}                


/* Getters and setters */

// Description: Returns the number of elements currently stored in the binary search tree.   
// Postcondition: This method does not change the binary search tree.
// Time efficiency: O(1)
unsigned int BST::getElementCount() const {    
   return this->elementCount;
}


/* BST Operations */

// Description: Inserts an element into the binary search tree.
//              This is a wrapper method which calls the recursive insertR( ).
// Precondition: "newElement" does not already exist in the binary search tree.
// Exception: Throws the exception "UnableToInsertException" when newElement 
//            cannot be inserted because the "new" operator failed. 
// Exception: Throws the exception "ElementAlreadyExistsException" 
//            if "newElement" already exists in the binary search tree.
// Time efficiency: O(log2 n)   
void BST::insert(WordPair& newElement) {
   //* Check if new operator runs properly
   BSTNode* newNode = new BSTNode(newElement);
   if (newNode == nullptr)
      throw UnableToInsertException("new operator failed.");
   
   //* Call insertR if root exists
   if (root == nullptr) {
      root = newNode;
      elementCount++;
      return;
   }
   insertR(newNode, root);
} 

// Description: Recursive insertion into a binary search tree.
//              Returns true when "anElement" has been successfully inserted into the 
//              binary search tree. Otherwise, returns false.
bool BST::insertR(BSTNode* newBSTNode, BSTNode* current) {
   //* Check if element already exists
   if (current->element == newBSTNode->element) 
      throw ElementAlreadyExistsException("Element already exists.");

   //* Check left and right subtree recursively
   else if (newBSTNode->element < current->element) {
      if (!current->hasLeft()) {             //? same if use isLeaf?
         current->left = newBSTNode;
         elementCount++;
         return true;
      }
      return insertR(newBSTNode, current->left);
   }
   else {
      if (current->hasRight())
         return insertR(newBSTNode, current->right);
      else {
         current->right = newBSTNode;
         elementCount++;
         return true;
      }
   }
}

// Description: Retrieves "targetElement" from the binary search tree.
//              This is a wrapper method which calls the recursive retrieveR( ).
// Precondition: Binary search tree is not empty.
// Exception: Throws the exception "EmptyDataCollectionException" 
//            if the binary search tree is empty.
// Exception: Propagates the exception "ElementDoesNotExistException" 
//            thrown from the retrieveR(...)
//            if "targetElement" is not found in the binary search tree.
// Postcondition: This method does not change the binary search tree.
// Time efficiency: O(log2 n)
WordPair& BST::retrieve(WordPair& targetElement) const {
   if (elementCount == 0)  
      throw EmptyDataCollectionException("Binary search tree is empty.");
   WordPair& translated = retrieveR(targetElement, root);
   return translated;
}

// Description: Recursive retrieval from a binary search tree.
// Exception: Throws the exception "ElementDoesNotExistException" 
//            if "targetElement" is not found in the binary search tree.
// Postcondition: This method does not change the binary search tree.
WordPair& BST::retrieveR(WordPair& targetElement, BSTNode* current) const {
   //! Retrieve already handle case:empty
   if (current == nullptr)
      throw ElementDoesNotExistException("Element doesn't exist in the BST.");
   else if (current->element == targetElement)
      return current->element;
   
   //! No need to check hasLeft since case:nullptr covered
   else if (targetElement < current->element) 
      return retrieveR(targetElement, current->left);
   else 
      return retrieveR(targetElement, current->right);
} 


// Description: Traverses the binary search tree in order.
//              This is a wrapper method which calls the recursive traverseInOrderR( ).
//              The action to be done on each element during the traverse is the function "visit".
// Precondition: Binary search tree is not empty.
// Exception: Throws the exception "EmptyDataCollectionException" 
//            if the binary search tree is empty.
// Postcondition: This method does not change the binary search tree.
// Time efficiency: O(n)     
void BST::traverseInOrder(void visit(WordPair&)) const {
   if (elementCount == 0)  
      throw EmptyDataCollectionException("Binary search tree is empty.");
   traverseInOrderR(visit, root);
   return;
}

// Description: Recursive in order traversal of a binary search tree.   
// Postcondition: This method does not change the binary search tree. 
void BST::traverseInOrderR(void visit(WordPair&), BSTNode* current) const { 
   if (current != nullptr) {
      traverseInOrderR(visit, current->left);
      visit(current->element);
      traverseInOrderR(visit, current->right);
   }
}