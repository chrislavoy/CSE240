/**
Course: CSE240
Instructor: Dr. Chen
Assignment Name: Homework 8
Solved by: Chris LaVoy (3/28/14)
*/

#include <iostream>
#include <stdlib.h>
#include <string>
#pragma warning(disable: 4996)
using namespace std;

/****************** Forward Declarations ******************/
class container;
class person;

void branching(char c, container** pointerToHead);	// given
char* get_name();						// given
void printFirst(container* root); 				// given
int insertion(container** pointerToHead); 		// Question 2
person* search(container* root, char* sname); 		// Question 3
void deleteAll(container** pointerToHead); 		// Question 4
void printAll(container* root);				// Question 5



// A class for nodes of the linked list. 
class container {
public:
	person *plink;	// points to a person object
	container *next;
	container(){
		plink = NULL;
		next = NULL;
	};

	virtual ~container()
	{
		delete plink;
		delete next;
		plink = NULL;
		next = NULL;
	}
};

// A class to hold attributes of a person
class person {
public:
	char *name;
	char *email;
	int phone;
	// constructor that uses the parameters to initialize the class properties
	person(char *cName, char *cEmail, int iPhone) {
		name = new (char[32]);	// acquiring memory for storing name
		email = new (char[32]); 	// acquiring memory for storing email
		strcpy(name, cName);		// initialize name
		strcpy(email, cEmail); 	// initialize email
		phone = iPhone; 		// initialize phone
	}
	virtual ~person() {
		// write your destructor code here for Question 1
		delete[] name;
		delete[] email;
		name = NULL;
		email = NULL;
	}
};

int main()
{
	container* head = NULL; // Declare head as a local variable of main function
	// Print a menu for selection
	char ch = 'i';
	do {
		cout << "Enter your selection" << endl;
		cout << "\ti: insert a new entry" << endl;
		cout << "\tr: delete all entries" << endl;
		cout << "\ts: search an entry" << endl;
		cout << "\tp: print all entries" << endl;
		cout << "\tq: quit" << endl;
		cin >> ch;
		ch = tolower(ch);	// Convert any uppercase char to lowercase.
		branching(ch, &head);
		cout << endl;
	} while (ch != 'q');
	return 0;
};
// Branch to different tasks: insert a person, search for a person, delete a person
// print all added persons.
void branching(char c, container** pointerToHead)
{
	char *p;
	switch (c) {
	case 'i':
		insertion(pointerToHead);
		break;
	case 's':
		p = get_name();
		search(*pointerToHead, p);
		break;
	case 'r':
		deleteAll(pointerToHead);
		break;
	case 'p':
		printAll(*pointerToHead);
		break;
	case 'q':
		deleteAll(pointerToHead); // free all memory
		break;
	default:
		printf("Invalid input\n");
	}
};
// Read the input from the user.
char * get_name()
{
	char *p = new(char[32]); // Use dynamic memory which does not go out of scope
	cout << "Please enter a name for the search: " << endl;
	cin >> p;
	return p;
};
void printFirst(container* root)
{
	if (root != NULL)
	{
		cout << "\n\nname = " << root->plink->name << endl;
		cout << "email = " << root->plink->email << endl;
		cout << "phone = " << root->plink->phone << endl;
	}
};

int insertion(container** pointerToHead)
{

	container* newNode = new container();
	container* iterator = NULL;
	container* follower = NULL;
	person* newPerson = NULL;

	// Case 1: The program is out of memory
	if (newNode == NULL)
	{
		cout << "Fatal Error: Out of Memory. Exiting now." << endl;
		return 0;
	}
	else
	{
		char* name = new (char[32]);
		char* email = new (char[32]);
		int phone;

		cout << "Enter the name:" << endl;
		cin >> name;
		cout << "Enter the email:" << endl;
		cin >> email;
		cout << "Enter the phone number:" << endl;
		cin >> phone;
		newPerson = new person(name, email, phone);
		newNode->plink = newPerson;

		// If the list is empty
		if (*pointerToHead == NULL)
		{
			*pointerToHead = newNode;
			(*pointerToHead)->next = NULL;
			return 0;
		}
		else
		{
			if (strcmp(newPerson->name, (*pointerToHead)->plink->name) < 0)
			{
				newNode->next = *pointerToHead;
				*pointerToHead = newNode;
				return 0;
			}
			iterator = *pointerToHead;
			follower = iterator;
			while (iterator != NULL)
			{
				if (strcmp(newPerson->name, iterator->plink->name) < 0)
				{
					newNode->next = iterator;
					follower->next = newNode;
					return 0;
				}
				follower = iterator;
				iterator = iterator->next;
			}
			follower->next = newNode;
			newNode->next = NULL;
			return 0;
		}
	}
	return 0;
}

person* search(container* root, char* sname)
{
	container* iterator = root;

	while (iterator != NULL)
	{
		if (strcmp(sname, iterator->plink->name) == 0)
		{
			printf("\n\nname = %s\n", iterator->plink->name);
			printf("email = %s\n", iterator->plink->email);
			printf("phone = %d\n", iterator->plink->phone);
			
			free(sname); // garbage collection
			return iterator->plink;
		}
		iterator = iterator->next;
	}
	printf("The name does not exist.\n");
	free(sname); // garbage collection
	return iterator->plink;
}

void deleteNode(container** node)
{	
	free((*node)->plink);
	free(*node);
	*node = NULL;	
}

void deleteAll(container** pointerToHead)
{
	if (*pointerToHead == NULL)
	{
		return;
	}
	else
	{
		deleteAll(&(*pointerToHead)->next);
		deleteNode(&(*pointerToHead));
	}
}

void printAll(container *root)
{
	container* iterator = root;

	if (root != NULL)
	{
		if (iterator->next == NULL)
		{
			printFirst(iterator);
			return;
		}
		else
		{
			printFirst(iterator);
			printAll(iterator->next);
		}
	}
}