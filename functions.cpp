#include "header.h"

using namespace std;

// HASH MAP FUNCTIONS
//=======================================================
HashMap::HashMap(int capacity)
{
	buckets = new list<HashNode>[capacity];
	this->capacity = capacity;
	this->size = 0;
}
//================================================
unsigned long long int HashMap::hashCode(const string key)
{
	unsigned long long int sum=0;
	for(int i=0; i<key.length(); i++)
	{
		//Add ascci code of each letter times i power 10
		sum += key[i]*pow(10,i);
	}
	return sum;
}
//================================================
void HashMap::insert(const string key, const hotelDetails& newRecord, bool tf)
	{
	int index = hashCode(key)%this->capacity; //Find the bucket index where the new node will fall, make sure that the index is within the bounds of array
	if(!tf){
	for(auto it:buckets[index])
		if(it.getKey()==key)				//if key already present in the hash table
		{
			it.setValue(newRecord);				//then update the value and return
			return;
		}
		buckets[index].push_back(HashNode(key,newRecord));	//otherwise add the new element into the bucket/list
		this->size++;	
	}
	else
	{
		buckets[index].push_back(HashNode(key,newRecord));	//otherwise add the new element into the bucket/list
		this->size++;	
	}
}
//===================================================
string HashMap::search(const string key)
{
	int index = hashCode(key)%this->capacity;			//Get the index of the bucket
	int counter = 0;

	//range based loop same as for(auto it=buckets[index].begin(); i!=buckets[index].endl; it++)
	for(auto it:buckets[index]) 
	{
		if(it.getKey()==key)
		{
			cout << "(comparisions = "+to_string(++counter)+")";
			return it.getValue();
		}	
		counter++;
	}
	return "Record Not Found...!";			//conclude that data not found in the array
}
//=====================================================
string HashMap::remove(const string key)
{
	int index = hashCode(key)%this->capacity;	//Get the index of the bucket
	for(list<HashNode>::iterator it = buckets[index].begin(); it!=buckets[index].end(); ++it) 
	{
		if(it->getKey()==key)
		{
			cout<<"Deleted :"<<it->getKey()<<", "<<it->getValue()<<endl;
			string deleted = it->details.hotelName;
			buckets[index].erase(it);
			return deleted;
		}
	}
	cout<<"Cant delete....Record Not Found...!"<<endl;			//conclude that data not found in the array
}
//================================================
void HashMap::removeSecMap(const string key, string str)
{
	int index = hashCode(key)%this->capacity;

	for(list<HashNode>::iterator it = buckets[index].begin(); it!=buckets[index].end(); ++it)
	{
		if(it->details.hotelName==str)
		{
			buckets[index].erase(it);
			cout << "Deleted from hash map with cities" << endl;
			return;
		}
	}
}
//===================================================
int HashMap::getSize()
{
	return this->size;
}
//================================================
int HashMap::getCapacity()
{
	return this->capacity;
}
//================================================
void HashMap::printLinkedList(string key)
{
	int counter = 0;	
	int index = hashCode(key)%this->capacity;
	for(auto it: buckets[index])
	{
		if(it.getKey()==key)
		{
			counter++;
			cout << it.getValue() << endl;
		}
	}
	cout << "Count " << counter << endl;
	
	if(counter==0)
	{
		cout << "No hotels in this city were listed." << endl;
	}
}
//================================================
HashMap::~HashMap()
{
	delete[] this->buckets;
}
//=======================================================

//================================================
// HEAP FUNCTIONS
// Constructor
Heap::Heap(int capacity)
{
	this->array = new string[capacity];
	this->size=0;
}
// Insert an element in Heap keeping the Heap property intact 
void Heap::insert(string key)
{
	array[size++]=key;
	siftup(size-1);
}
// Remove the minimum value from Heap keeping the Heap property intact
int Heap::removeMin()
{
	array[0] = array[size-1];
	size--;
	siftdown(0);
}
// Return (but don't remove) the minimum value from the Heap
string Heap::getMin()
{
	return(array[0]);
}
int Heap::getSize()
{
	return size;
}
// Returns the index of the parent of the node i
int Heap::parent(int i)
{
	return (i-1)/2;
}
// Returns the index of the left child of the node i
int Heap::left(int i)
{
	return 2*i + 1;
}
// Returns the index of the right child of the node i
int Heap::right(int i)
{
	return 2*i + 2;
}
// Sift-up an element at index k
void Heap::siftup(int k)
{
	if(array[parent(k)] > array[k])
	{
		swap(array[parent(k)],array[k]);
		siftup(parent(k));
	}
	else return;	
}
// Sift-down an element at index k
void Heap::siftdown(int k)
{
	// 1. if element has no children do nothing
	if(left(k) > size && right(k) > size)
	{
		return;
	}
	// 2. if element has only a left child which i s smaller than element then swap the element with its left child
	if(right(k)> size && left(k) < size && left(left(k)) > size)
	{
		if(array[left(k)] < array[k])
		{
			swap(array[left(k)], array[k]);
			siftdown(left(k));
		}
	}
	// 3. if element has both children and smaller child is also smaller than the node then swap it with that node
	if(right(k)< size && left(k) < size )
	{
		if(array[left(k)] < array[right(k)])
		{
			if (array[k] > array[left(k)])
			{
				swap(array[left(k)], array[k]);
				siftdown(left(k));
			}
		}
		else if(array[left(k)] >= array[right(k)])
		{
			if (array[k] > array[right(k)])
			{
				swap(array[right(k)], array[k]);
				siftdown(right(k));	
			}
		}	
	}
}

void Heap::swap(string&a, string &b)
{
	string tmp = a;
	a=b;
	b=tmp;
}
//==================================================================

// OTHER INDIVIDUAL FUNCTIONS
// The function below was adapted from the following link: 
// https://stackoverflow.com/questions/16329358/remove-spaces-from-a-string-in-c
string Normalise(string str){
	
	str.erase(remove(str.begin(), str.end(), ' '),str.end());
	for (int i = 0; i < str.size(); i++)
	{
		str[i] = tolower(str[i]);
	}
	return(str);
}

bool isprime(int cap)
{
	for(int i=2; i< cap/2 ; i++)
	{
		if(cap%i == 0)
		{
			return false;
		}
	}
 	return true;
}

 void invocationError(){
	cout << "Error invoking the application." << endl;
    cout << "Please follow the following format to call the function: " << endl;
    cout << "mymachine >> ./hotelFinder -f <filename>" << endl; 
}

string getcityName(string str)
{
	return str.substr(str.find(',')+1);
}