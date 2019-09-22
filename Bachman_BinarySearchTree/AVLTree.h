#ifndef AVLTree_h
#define AVLTree_h

// Preprocessor Directives
#pragma once
#include <iostream>
#include <algorithm>

// Creates the AVLTree template class to be used throughout the program. Will include class definitions as well.
template <class T>
class AVLTree
{
public:
	// Constructor
	AVLTree(void) : root(NULL) {} // Do nothing

	// Destructor
	~AVLTree()
	{
		// Delete root to clear up space.
		delete root;
	}

	// Creates the insert function, used for inserting data/nodes into the tree.
	bool insert(T value)
	{
		// If root is null, create a new root with whatever value is set to.
		if (root == NULL)
		{
			root = new Node<T>(value, NULL);
		}
		else
		{
			Node<T>* n = root;
			Node<T>* parent;

			// While true, so it will run until it needs to be stopped.
			while (true)
			{
				// If the value is already in, return false to stop the loop.
				if (n->value == value)
				{
					return false;
				}

				parent = n;

				bool headLeft = n->value > value;
				n = headLeft ? n->left : n->right;

				if (n == NULL)
				{
					if (headLeft)
					{
						parent->left = new Node<T>(value, parent);
					}
					else
					{
						parent->right = new Node<T>(value, parent);
					}

					// Rebalance the tree after insert to simulate auto-rebalance.
					rebalance(parent);
					// End the loop.
					break;
				}
			}
		}

		return true;
	}

	// Creates the delete function, used for deleting data/nodes from the tree.
	void delKey(const T deleteKey)
	{
		// If empty, return so it does nothing.
		if (root == NULL)
		{ 
			return; // Return nothing
		}

		Node<T>* n = root;
		Node<T>* parent = root;
		Node<T>* deleteNode = NULL;
		Node<T>* child = root;

		while (child != NULL)
		{
			parent = n;
			n = child;
			child = deleteKey >= n->value ? n->right : n->left;

			if (deleteKey == n->value)
			{
				deleteNode = n;
			}
		}

		if (deleteNode != NULL)
		{
			deleteNode->value = n->value;

			child = n->left != NULL ? n->left : n->right;

			if (root->value == deleteKey)
			{
				root = child;
			}
			else
			{
				if (parent->left == n)
				{
					parent->left = child;
				}
				else
				{
					parent->right = child;
				}

				// Rebalance the tree after delete to simulate auto-rebalance.
				rebalance(parent);
			}
		}
	}

	// Print out the maximum key in a list using the private maximum function.
	void maximum()
	{
		std::cout << "The maximum value in the tree is " << maximum(root) << "." << std::endl << std::endl;
		std::cout << std::endl << std::endl;
	}

	// Creates the class that prints the tree from the private method using root as an argument. Also skips some lines afterwards.
	// Print traverses the tree inorder.
	void print()
	{
		print(root);
		std::cout << std::endl << std::endl;
	}

	// Check to see if the tree is empty.
	bool isEmpty()
	{
		// If the root is null, tree is empty.
		if (root == NULL)
			return true;

		return false; // Tree is not empty.
	}

private:
	// Used to keep track of the root node.
	Node<T>* root;

	// BEGIN REBALANCING SETUP... ROTATE CLASSES BELOW WILL BE USED IN REBALANCE TO MOVE THINGS SUCCESSFULLY SO IT'S AUTOMATED.
	// Creates the rotateRight class that will rotate the nodes left until balance has been achieved.
	Node<T>* rotateLeft(Node<T>* nodeOne)
	{
		Node<T>* nodeTwo = nodeOne->right; // Creates a second node and sets it equal to nodeOne right.
		nodeTwo->parent = nodeOne->parent; // Set nodeTwo parent equal to nodeOne parent.
		nodeOne->right = nodeTwo->left; // Shift the node left.

		// If right of node one is not null, set right parent equal to node 1.
		if (nodeOne->right != NULL)
		{
			nodeOne->right->parent = nodeOne;
		}

		nodeTwo->left = nodeOne;
		nodeOne->parent = nodeTwo;

		if (nodeTwo->parent != NULL)
		{
			if (nodeTwo->parent->right == nodeOne)
			{
				nodeTwo->parent->right = nodeTwo;
			}
			else
			{
				nodeTwo->parent->left = nodeTwo;
			}
		}

		// Set the balance again for both nodes and return the second node.
		setBalance(nodeOne);
		setBalance(nodeTwo);
		return nodeTwo;
	}

	// Creates the rotateRight class that will rotate the nodes right until balance has been achieved.
	Node<T>* rotateRight(Node<T>* nodeOne)
	{
		Node<T>* nodeTwo = nodeOne->left; // Creates a second node and sets it equal to nodeOne left.
		nodeTwo->parent = nodeOne->parent; // Set nodeTwo parent equal to nodeOne parent.
		nodeOne->left = nodeTwo->right; // Shift the node right.

		if (nodeOne->left != NULL)
		{
			nodeOne->left->parent = nodeOne;
		}

		nodeTwo->right = nodeOne;
		nodeOne->parent = nodeTwo;

		if (nodeTwo->parent != NULL)
		{
			if (nodeTwo->parent->right == nodeOne)
			{
				nodeTwo->parent->right = nodeTwo;
			}
			else
			{
				nodeTwo->parent->left = nodeTwo;
			}
		}

		// Set the balance again for both nodes and return the second node.
		setBalance(nodeOne);
		setBalance(nodeTwo);
		return nodeTwo;
	}

	// Creates the rotateLeftToRight class that (FILL)
	Node<T>* rotateLeftToRight(Node<T>* node)
	{
		node->left = rotateLeft(node->left);

		return rotateRight(node);
	}

	// Creates the rotateRightToLeft class that (FILL)
	Node<T>* rotateRightToLeft(Node<T>* node)
	{
		node->right = rotateRight(node->right);

		return rotateLeft(node);
	}

	// Creates the rebalance class that will rebalance the trees so that it will show correctly, especially after insertion and deletion.
	void rebalance(Node<T>* node)
	{
		// Get the setBalance of the specific node being rebalanced in the argument.
		setBalance(node);

		// If node balaance is negative 2, rotate right to get the balance needed, otherwise rotate left to right to set the rebalance.
		if (node->balance == -2)
		{
			if (height(node->left->left) >= height(node->left->right))
			{
				node = rotateRight(node);
			}
			else
			{
				node = rotateLeftToRight(node);
			}
		}
		else if (node->balance == 2) // If node balaance is positive 2, rotate right to get the balance needed, otherwise rotate right to left to set the rebalance.
		{
			if (height(node->right->right) >= height(node->right->left))
			{
				node = rotateLeft(node);
			}
			else
			{
				node = rotateRightToLeft(node);
			}
		}

		// If the parent is null, rebalance the parent node or set the root to the node being rebalanced, making it the new root with no parent.
		if (node->parent != NULL)
		{
			rebalance(node->parent);
		}
		else
		{
			root = node;
		}
	}

	// Creates the height class that should only report the height of the AVL tree.
	int height(Node<T>* node)
	{
		if (node == NULL)
		{
			return -1;
		}

		// Returns the height of the tree so that we can ensure proper balance.
		return 1 + std::max(height(node->left), height(node->right));
	}

	// Creates the setBalance class that holds node balance as the height of right - the height of left so the balancing can be done.
	void setBalance(Node<T>* node)
	{
		node->balance = height(node->right) - height(node->left);
	}

	// Creates the private print class that displays all the values in the existing nodes.
	void print(Node<T>* node)
	{
		// Will only display if the node is not null.
		if (node != NULL)
		{
			// Calls itself to print the node left and right at every interval.
			print(node->left);
			std::cout << node->value << " "; // COUT to print out the key of the node.
			print(node->right);
		}
	}

	// Private maximum so it can be called externally.
	int maximum(Node<T>* root)
	{
		// Base case, if root is empty...
		if (root == NULL)
		{
			return INT_MIN; // Return the minimum int.
		}

		// Returns 3 separate values.. The data of the root, the max in left subtree and the max in the right.
		int rootValue = root->value;
		int leftMax = maximum(root->left);
		int rightMax = maximum(root->right);

		// If left max is bigger than the valye of root, set new rootValue (can be confusing) to leftMax.
		if (leftMax > rootValue)
		{
			rootValue = leftMax;
		}
		// If right max is bigger than the value of root, set new rootValue (can be confusing) to rightMax.
		if (rightMax > rootValue)
		{
			rootValue = rightMax;
		}

		return rootValue;
	}
};

#endif