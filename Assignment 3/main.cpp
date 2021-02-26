/************************************************
** Connor Greenwald 
** Greenwac 
** 933 287 362
** 
** Thomas Tonini
** Toninit
** 932 257 516
** 
** CS 440 Assingment #3
**
*************************************************/

#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

template <typename KeyType, typename ValueType>

//Hashnode class
class HashNode
{
public:
	ValueType value;
	KeyType key;

	HashNode(KeyType key, ValueType value)
	{
		this->value = value;
		this->key = key;
	}
};

template <typename KeyType, typename ValueType>

//Hashmap class
class HashMap
{
	//Array of hashnodes
	HashNode<KeyType, ValueType> **hashArray;
	int buckets;

public:
	HashMap()
	{
		//Initial size
		buckets = 80;
		hashArray = new HashNode<KeyType, ValueType> *[buckets];

		//Create the array
		for (int i = 0; i < buckets; i++)
			hashArray[i] = NULL;
	}

	/************************************************
	** FUNCTION NAME: insertNode
	** PARAMENTERS: key and value
	** PRECONDITIONS: hashmap has been created
	** POSTCONDITIONS: node has been added to hashmap
	*************************************************/
	void insertNode(KeyType key, ValueType value)
	{
		HashNode<KeyType, ValueType> *temp = new HashNode<KeyType, ValueType>(key, value);

		// Create hash key
		int tempKey = atoi(key);
		int hashBucketIndex = tempKey % buckets;

		//navigate until theres freespace
		while (hashArray[hashBucketIndex] != NULL && hashArray[hashBucketIndex]->key != key && hashArray[hashBucketIndex]->key != NULL)
		{
			hashBucketIndex++;
			hashBucketIndex = hashBucketIndex % buckets;
		}

		hashArray[hashBucketIndex] = temp;
	}

	/************************************************
	** FUNCTION NAME: findNode
	** PARAMENTERS: key as a pointer
	** PRECONDITIONS: hash map has been made
	** POSTCONDITIONS: returns found value if key exists
	*************************************************/
	ValueType findNode(char *key)
	{
		// Apply hash function to find index for given key
		int tempKey = atoi(key);
		int hashBucketIndex = tempKey % buckets;
		int counter = 0;

		int tempIndex = atoi(hashArray[hashBucketIndex]->key);

		//finding the node with given key
		while (hashArray[hashBucketIndex] != NULL)
		{
			int counter = 0;
			if (counter++ > buckets) //to avoid infinite loop
				return NULL;
			//if node found return its value
			if (tempIndex == tempKey)
			{
				return hashArray[hashBucketIndex]->value;
			}
			hashBucketIndex++;
			hashBucketIndex = hashBucketIndex % buckets;
		}
		//if key value pair doesnt exist
		return NULL;
	}
};

int main()
{
	ifstream file;
	ofstream out;

	string currentLine;

	file.open("Employees.csv");
	out.open("EmployeeIndex.txt");

	//set the file pointer back to the begining of the file
	file.clear();
	file.seekg(0);

	HashMap<char *, char *> *emp = new HashMap<char *, char *>;

	const char *delimiter = ",";
	char *value, *key, *token, *input, *info1, *info2;

	//Add to the hash table
	int i = 0;
	while (getline(file, currentLine))
	{

		token = new char[currentLine.length() + 1];
		strcpy(token, currentLine.c_str());

		input = strtok(token, ",");
		key = input;
		input = strtok(NULL, ",");
		info1 = input;
		input = strtok(NULL, ",");
		info2 = input;
		input = strtok(NULL, ",");
		value = input;

		emp->insertNode(key, value);
		out << key << ", " << info1 << ", " << info2 << ",  " << value << endl;
		cin.clear();
	}

	file.close();
	out.close();

	char userInput, *inputKey = new char[1024];
	cout << "Creation or Lookup? (C/L): ";
	cin >> userInput;
	if (userInput == 'L')
	{
		cout << "Enter a key: ";
		cin >> inputKey;
		if (emp->findNode(inputKey) == NULL)
		{
			cout << "There is no value associated with that key." << endl;
		}
		else
		{
			cout << "The key value pair is: " << inputKey << " " << emp->findNode(inputKey) << endl;
		}
	}

	return 0;
}
