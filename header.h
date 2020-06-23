#include<iostream>
#include<fstream>
#include<sstream>
#include<cmath>
#include<list>
#include<algorithm>


using namespace std;

struct hotelDetails{
	string hotelName;
	string cityName;
	float stars;
	float price;
	string countryName;
	string address;
};

// Code adapted from Lab 12 as done in class and solutions
class HashNode
{
	public:
		string key;
		hotelDetails details;
	public:
		HashNode(string key, const hotelDetails& newRecord)
		{
			this->key = key;
			this->details.hotelName = newRecord.hotelName;
			this->details.cityName = newRecord.cityName;
			this->details.stars = newRecord.stars;
			this->details.price = newRecord.price;
			this->details.countryName = newRecord.countryName;
			this->details.address = newRecord.address;

		}
		string getKey()
		{
			return this->key;
		}
		void setValue(const hotelDetails& newRecord)
		{
			this->details.hotelName = newRecord.hotelName;
			this->details.cityName = newRecord.cityName;
			this->details.stars = newRecord.stars;
			this->details.price = newRecord.price;
			this->details.countryName = newRecord.countryName;
			this->details.address = newRecord.address;
		}
		string getValue()
		{
			return "\nName: "+this->details.hotelName+"\nCity: "+this->details.cityName+"\nStars: "+to_string(this->details.stars)+"\nPrice: "+to_string(this->details.price)+"\nCountry: "+this->details.countryName+"\nAddress: "+this->details.address;
		}
		void print()
		{
			cout << this->details.hotelName << ", ";
			cout << this->details.cityName << ", ";
			cout << this->details.stars << ", ";
			cout << this->details.price << ", ";
			cout << this->details.countryName << ", ";
			cout << this->details.address ;
		}

};

class HashMap
{
	private:
		list<HashNode> *buckets;		// Array of Pointers to Hash Nodes
		int size;					    // Current Size of HashMap
		int capacity;
		string inserted;
					    // Total Capacity of HashMap
	public:
		HashMap(int capacity);
		unsigned long long int hashCode(const string key);
		void insert(const string key, const hotelDetails& newRecord, bool tf);
		string search(const string key);
		string remove(const string key);
		void removeSecMap(const string key, string str);
		int getSize();
		int getCapacity();
		void printLinkedList(const string key);
		~HashMap();

};

//adapted from lab 11 
class Heap
{
	private:
		string *array;
		int size;
	
	public:
		Heap(int capacity);
		void insert(string key);
		int removeMin();
		string getMin();
		int getSize();
		int parent(int i);
		int left(int i);
		int right(int i);
		void siftup(int k);
		void siftdown(int k);
		void swap(string& a, string& b);
		void heapSort();
};

// The function below was adapted from the following link: 
// https://stackoverflow.com/questions/16329358/remove-spaces-from-a-string-in-c
string Normalise(string str);

bool isprime(int cap);

string getcityName(string str);
 void invocationError();