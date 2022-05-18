//Artsiom Skarakhod & Zach Triplett
#include "BSTree.h"

// Constructor
template <typename DATATYPE, typename KEYTYPE>
BSTree<DATATYPE, KEYTYPE>::BSTree()
{
	root = nullptr;
}

// Destructor
template <typename DATATYPE, typename KEYTYPE>
BSTree<DATATYPE, KEYTYPE>::~BSTree()
{
    if (root !=nullptr)
        freeNode(root);
}

// Free the node
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::freeNode(Node<DATATYPE, KEYTYPE> * leaf)
{

    //if the root is the leaf, delete that leaf
    if(Root()==leaf)
    {
        delete(leaf);
    }
    // otherwise if the leaf is not null
    else if(leaf != nullptr)
    {
        //recursive call of the leaf's left
        freeNode(leaf->Left());
        //recursive call of the leaf's right
        freeNode(leaf->Right());
        //now delete the leaf
        delete(leaf);
    }
}

// Add a node
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::addNode(KEYTYPE key, DATATYPE &data)
{
	if (Root() == nullptr)
	{
		Node<DATATYPE, KEYTYPE> * newNodePtr = new Node<DATATYPE, KEYTYPE>;
		newNodePtr->setKey(key);
		newNodePtr->setData(data);
		root = newNodePtr;
		root->setParent(root);
	}
	else
		addNode(key, root, data);
}

// Add a node (private)
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::addNode(KEYTYPE key, Node<DATATYPE, KEYTYPE> * leaf, DATATYPE& data)
{
    if(leaf!=NULL) {
		// if the key is less than whatever in the node then move to the lec of the tree
		if (leaf->Key()< key) {
			// call the func7on again if there s7ll childern for this node
			if (leaf->Left() != nullptr) {
				addNode(key, leaf->Left(), data);
			}
				// if there is no children for this node we will place to the lec of this node
			else {
				Node<DATATYPE, KEYTYPE> *newNodePtr = new Node<DATATYPE, KEYTYPE>;
				newNodePtr->setKey(key);
				newNodePtr->setData(data);
				leaf->setLeft(newNodePtr);
			}
		// if the key is grater than whatever in the node then move to the lec of the tree
	}else{
		if(leaf->Right() != nullptr) {
			addNode(key, leaf->Right(), data);
		}
		// if there is no children for this node we will place to the right of this node
		else
			{
                Node<DATATYPE, KEYTYPE> * newNodePtr = new Node<DATATYPE, KEYTYPE>;
                newNodePtr->setKey(key);
                newNodePtr->setData(data);
                leaf->setRight(newNodePtr);
			}
		}
	}
}

template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> * BSTree<DATATYPE, KEYTYPE>::findNode(KEYTYPE key)
{
    Node<DATATYPE, KEYTYPE> * ttttttt=findNode(key, root);
    return ttttttt;
     //return findNode(key, root);
}
// Find a node(Private)
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> * BSTree<DATATYPE, KEYTYPE>::findNode(KEYTYPE key, Node<DATATYPE, KEYTYPE> *node)
{
	//Student must fill in
    //trap nullptr first in case we've hit the end unsuccessfully.

    if(node == nullptr)
    {
        return node;
    }
    //success base case
    //Greater than (Right), Less than (Left)
    if(key>node->Key())
    {
	    node = findNode(key,node->Left());
    }
	else if(key<node->Key())
    {
        node = findNode(key,node->Right());
    }
	else
    {
        return node;
    }
    return node;
}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::printInorder()
{
	printInorder(root);
}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::printInorder(Node<DATATYPE, KEYTYPE> * node)
{
    //makes sure that the node really exists
	if(node == nullptr)
	{
        return;
	}
	//prints out the nodes on the right first
	printInorder(node->Right());

	//prints out the node on the left nodes second
	printInorder(node->Left());
}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::print(ostream & out, const DATATYPE & data)
{
	out << data.number << "\t" << data.name << endl;
}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::deleteNode(KEYTYPE key)
{
	setRoot(deleteNode(Root(), key));
}

//deleteNode (Private)
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> * BSTree<DATATYPE, KEYTYPE>::deleteNode(Node<DATATYPE, KEYTYPE> * aRoot,KEYTYPE value)
{
	/* Given a binary search tree and a key, this function deletes the key
	and returns the new root */

	// base case
	if (aRoot == nullptr)
	{
		return aRoot;
	}

	// If the key to be deleted is smaller than the aRoot's key,
	// then it lies in left subtree
	if (value > aRoot->Key())
		aRoot->setLeft(deleteNode(aRoot->Left(), value));

	// If the key to be deleted is greater than the root's key,
	// then it lies in right subtree
	else if (value < aRoot->Key())
		root->setRight(deleteNode(aRoot->Right(), value));

	// if key is same as root's key, then This is the node
	// to be deleted
	else
	{
		// node with only one child or no child
		if (aRoot->Left() == nullptr)
		{
			Node<DATATYPE, KEYTYPE> *temp = aRoot->Right();
			delete aRoot;	
			return temp;
		}
		else if (aRoot->Right() == nullptr)
		{
			Node<DATATYPE, KEYTYPE> *temp = aRoot->Left();
			delete aRoot;
			return temp;
		}

		// node with two children: Get the inorder successor (smallest
		// in the left subtree)
		Node<DATATYPE, KEYTYPE> * temp = min(aRoot->Left());

		// Copy the inorder successor's content to this node
		aRoot->setKey(temp->Key());
		aRoot->setData(temp->Data());

		// Delete the inorder successor
		aRoot->setRight(deleteNode(aRoot->Right(), temp->Key()));
	}
	return aRoot;
}

// Find the node with min key
// Traverse the left sub-BSTree recursively
// till left sub-BSTree is empty to get min
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> * BSTree<DATATYPE, KEYTYPE>::min(Node<DATATYPE, KEYTYPE> * node)
{
	Node<DATATYPE, KEYTYPE> * current = node;

	/* loop down to find the leftmost leaf */
	while (current->Right() != nullptr)
		current = current->Right();

	return current;
}

// Find the node with max key
// Traverse the right sub-BSTree recursively
// till right sub-BSTree is empty to get max
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> * BSTree<DATATYPE, KEYTYPE>::max(Node<DATATYPE, KEYTYPE> * node)
{
	Node<DATATYPE, KEYTYPE> * tempNode = node;
	if (node == nullptr)
		tempNode = nullptr;
	else if (node->Left())
		tempNode = max(node->Left());
	else
		tempNode = node;

	return tempNode;
}
/*
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE> :: goThroughFullTree(Node<DATATYPE,KEYTYPE> * node, bool (f)(Node<DATATYPE,KEYTYPE> * node))
{
	//if something is found then put it into the vector
	if(f(node))
	{
		search.push_back(node);
	}
	//if there is still a node on the left go to the left
	if(node->Left()!= nullptr)
	{
		goThroughFullTree(node->Left(),f);
	}
	//if there is a node on the right go to the right
	if(node->Right()!= nullptr)
	{
		goThroughFullTree(node->Right(),f);
	}
}*/