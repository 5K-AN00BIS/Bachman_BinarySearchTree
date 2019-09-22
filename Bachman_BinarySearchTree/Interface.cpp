// Preprocessor Directives
#include "Interface.h"
#include <chrono> // High res clock path

// Build out the testing suite. Not quite sure how to do this, but wanted it in the code so I could at least start on it.
bool AVLTreeTestingSuite()
{
	// Starts off the test_success as true so it's guaranteed to run at least once and resets whenever called.
	bool test_success = true;

	// Create a new LinkedList for testing
	AVLTree<int>* testingTree = new AVLTree<int>();

	// Check to see if the list is created empty as intended.
	if (testingTree->isEmpty())
	{
		std::cout << "The tree was created and is empty as needed." << std::endl;
	}
	else
	{
		std::cout << "Something was on the ship the whole time. This tree didn't create empty." << std::endl;
		test_success = false; // Set test_success to false so we can let the user know something failed.
	}

	return test_success;
}

// Interface with the user to let them know if tests were good or not.
bool TestingSuite()
{
	std::system("cls"); // Clear the screen for the user.
	bool list_test_status = AVLTreeTestingSuite();

	if (list_test_status) // If the status is successful and the bool is still true
	{
		std::cout << "All tests were run successfully. Everything is working as intended!\n" << std::endl;
		return true;
	}
	else // Something failed in the testing so test_success is set to false.
	{
		std::cout << "At least one test has failed! Uh oh!\n" << std::endl;
		return false;
	}
}

// Creates the Interface class, which will be the main driver for the entirety of this program.
void Interface()
{
	// Create a new AVLTree for integers in this scenario.
	AVLTree<int>* numberTree = new AVLTree<int>();

	// Create a new variable to store user menu integer.
	int menuSelection = -1;
	// Input value
	char input[6];
	int hold; // Holds the value of input in some scenarios.

	// While loop to resurface the menu as long as the user does not want to exit the program.
	while (menuSelection != 0)
	{
		// Displays the menu to the user and asks for input to traverse the settings.
		std::cout << "Welcome to Ryan Bachman's AVL Tree project for CSC382!" << std::endl;
		std::cout << "Please select what you'd like to do in the menu below using the designated numbers in parentheses." << std::endl;
		std::cout << "(1) Insert nodes into the tree" << std::endl;
		std::cout << "(2) Delete a node." << std::endl;
		std::cout << "(3) Find the maximum value in the tree." << std::endl;
		std::cout << "(4) Print the tree." << std::endl;
		std::cout << "(5) Automated Testing Suite" << std::endl;
		std::cout << "(0) Exit the program." << std::endl;
		std::cout << "\nPlease enter the number corresponding to the action you want to take: ";
		std::cin >> menuSelection;

		// Switch for menu selection and interaction.
		switch (menuSelection)
		{
		case 1: // If menuSelection is equal to 1.
		{
			system("cls"); // Clear the screen for a clean interface.
			std::cout << "You've elected to insert a node.\n" << std::endl;
			// Ask user for input
			std::cout << "Please enter the amount of nodes you want in the tree: ";
			std::cin >> input;
			hold = atoi(input); // Convert string input to integer for this assignment.

			// Start clock for runtime analysis.
			auto start = std::chrono::high_resolution_clock::now();

			// For loop to insert numbers into the tree using the insert function.
			for (int i = 1; i <= hold; ++i)
			{
				numberTree->insert(i); // Should add a number every time i counts so that it's easy to test.
			}

			// Stop clock for runtime analysis.
			auto finish = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = finish - start;

			std::cout << std::endl << "You have added " << hold << " nodes to the tree. Rebalancing the tree..." << std::endl;
			std::cout << "This process took " << elapsed.count() << " seconds" << std::endl << std::endl;
			break; // End the case.
		}
		case 2: // If menuSelection is equal to 2.
		{
			system("cls"); // Clear the screen for a clean interface.
			std::cout << "You've elected to delete a node.\n" << std::endl;

			// Error prevention - Cannot add if the tree is empty already.
			if (numberTree->isEmpty())
			{
				std::cout << "The tree is empty. Try adding to it first with 1 in the menu." << std::endl << std::endl;
			}
			else
			{
				// Ask user for input
				std::cout << "Enter the number you want to delete from the tree: ";
				std::cin >> input;
				hold = atoi(input); // Convert string input to integer for this assignment.

				// Start clock for runtime analysis.
				auto start = std::chrono::high_resolution_clock::now();

				numberTree->delKey(hold);

				// Stop clock for runtime analysis.
				auto finish = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double> elapsed = finish - start;

				std::cout << std::endl << hold << " has been deleted from the tree. Rebalancing the tree..." << std::endl;
				std::cout << "This process took " << elapsed.count() << " seconds" << std::endl << std::endl;
			}
			
			break; // End the case.
		}
		case 3: // If menuSelection is equal to 3.
		{
			system("cls"); // Clear the screen for a clean interface.
			std::cout << "You've elected to find the maximum value.\n" << std::endl;
			numberTree->maximum();

			break; // End the case.
		}
		case 4: // If menuSelection is equal to 4.
		{
			system("cls"); // Clear the screen for a clean interface.
			std::cout << "Printing the tree... This will traverse the tree in order.\n" << std::endl << std::endl;
			numberTree->print();

			std::cout << std::endl << std::endl;

			break; // End the case.
		}
		case 5: // If menuSelection is equal to 5.
		{
			system("cls"); // Clear the screen for a clean interface.
			std::cout << "You've started the Automated Testing Suite.\n" << std::endl;
			TestingSuite();
			break;
		}
		case 0: // If menuSelection is equal to 0.
		{
			system("cls"); // Clear the screen for a clean interface.
			std::cout << "Closing the program.\n" << std::endl;
			break;
		}
		default: // If menuSelection is equal to anything else.
		{
			system("cls"); // Clear the screen for a clean interface.
			std::cout << "Incorrect selection. Please use the numbers in parentheses to interact with the menu.\n" << std::endl;
			break;
		}
		}

	}
}