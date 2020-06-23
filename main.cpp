#include "header.h"

#ifndef HEADER_H
#define HEADER_H
#include<iostream>
#include<fstream>
#include<sstream>
#include<cmath>
#include<list>
#include<algorithm>
#endif

using namespace std;

//======================================================
int main(int argc, char* argv[])
{	
	string fName;
	//check for correct invocation of the application
    if(!(argc == 3))
	{
		invocationError();
        return 0;
    }
	
	string i = argv[1];
	fName = argv[2];

	if(i != "-f"){
		invocationError();
		return 0;
		}

	ifstream fin;
	fin.open(fName);
	if(!fin){
		cout<<"Can not open the file...!";
		exit(-1);
	}

	string line;

	int capacity = 0;
	
	//Get # of lines to set appropriate hash map capacity
	while(!fin.eof())
	{
		getline(fin,line);
		capacity++;
	}
	// find the next prime after adding 25% buffer capacity
	// adding a prime number as a capacity decreases the number of collisions improving spread of the data
	capacity = capacity/0.8;
	while(!isprime(capacity))
	{
		capacity++;
	}


	// sourced from https://stackoverflow.com/questions/5343173/returning-to-beginning-of-file-after-getline
	fin.clear(); //clear eof flag from input stream
	fin.seekg(0, ios::beg);	//set cursor back to start of file


	HashMap myHashMap(capacity);
	HashMap myHashMap2(capacity);
	getline(fin,line);  //skip first line
	while(!fin.eof())
	{
		//order of categories: hotelName,cityName,stars,price,countryName,address
		hotelDetails hotel;
		string temp;
		string temp2;
		
		getline(fin,hotel.hotelName,',');
		getline(fin,hotel.cityName,',');
		getline(fin,temp,',');
		hotel.stars = stof(temp);
		getline(fin,temp,',');
		hotel.price = stof(temp);
		getline(fin,hotel.countryName,',');
		getline(fin,hotel.address);

		// Normalise key to widen variations in search
		temp = Normalise(hotel.hotelName+","+hotel.cityName); // assign key 
		temp2 = Normalise(hotel.cityName); // assign
	
		// insert key and details to hash maps
		myHashMap.insert(temp,hotel,false);
		myHashMap2.insert(temp2,hotel,true);
	}
	fin.close();
	//cout << "Debug4" << endl;
	cout<<"Hash Map size = "<<myHashMap2.getSize()<<endl;
	cout << "Capacity " << capacity << endl;
	//variable storing operation choice of user 
	string choice;
	//while not 5 (quit), loop and continue application
	while(choice != "6")
	{
		
		cout << "   Enter 1 to INSERT a hotel record.\n   Enter 2 to FIND a hotel record.\n   Enter 3 to DELETE a hotel record.\n" ;
		cout << "   Enter 4 to STORE all hotel records to a file in alphabetical order.\n   Enter 5 to LIST all the hotels in a city.\n   Enter 6 to QUIT hotelFinder.\nChoice: ";
		getline(cin,choice);
	
		// INSERT HOTEL DETAILS
		if (choice == "1")
		{
			if (myHashMap.getSize() >= myHashMap.getCapacity())
			{
				cout << "Capacity reached. Error." << endl;
				continue;
			}

			string record;
			cout << "Please enter hotel details in the following format: \n  hotelName,cityName,stars,price,countryName,address\n";
			getline(cin,record); 	//Input strings which might contain spaces
			
			//Adapted from https://stackoverflow.com/questions/1894886/parsing-a-comma-delimited-stdstring
			stringstream ss(record);
			hotelDetails hotel;

			string temp; // store hotelName,cityName (key for myHashMap)
			string temp2; // store cityName (key for myHashMap2)

			getline(ss,hotel.hotelName,',');
			getline(ss,hotel.cityName,',');
			getline(ss,temp,',');
			hotel.stars = stof(temp);
			getline(ss,temp,',');
			hotel.price = stof(temp);
			getline(ss,hotel.countryName,',');
			getline(ss,hotel.address,',');

			temp = Normalise(hotel.hotelName+","+hotel.cityName); // assign key myHashMap
			temp2 = Normalise(hotel.cityName); // assign key for myHashMap2
			// Insert key and details to hash maps
			myHashMap.insert(temp,hotel,false);
			myHashMap2.insert(temp2,hotel,true);
		}

		// FIND HOTEL 
		else if (choice == "2")
		{
			string key;
			cout << "Please enter the key for your search in the following format: hotelName,cityName \n";
			getline(cin,key);		//Input strings which might contain spaces
				
			if (key == "exit")
				break;

			cout << key << endl;
			key = Normalise(key);
			cout<<"Details: "<< myHashMap.search(key)<<endl;
		}
		
		// DELETE HOTEL RECORD
		else if (choice == "3")
		{
			string key;
			string key2;
			cout << "Please enter the key for deletion in the following format: hotelName,cityName \n";
			getline(cin,key);
			key = Normalise(key);
			key2 = getcityName(key);
			cout << "Key2  " << key2 << endl; 
			string del = myHashMap.remove(key);
			myHashMap2.removeSecMap(key2, del);
		}
		
		// DUMP STRUCTURE INTO FILE IN ALPHABETICAL ORDER
		else if (choice == "4")
		{   
			fin.open(fName);
			Heap myheap(capacity);
			string temp;
			string temp2;
			getline(fin, temp2); //remove first line
			while(!fin.eof())
			{
				getline(fin, temp);
				myheap.insert(temp);
			}
			fin.close();
			string filename;
			cout << "Enter filename with the .txt extension (e.g. file.txt) " << endl;
			getline(cin, filename);
			// Adapted from previous project 
			ifstream checkfile(filename);
			if(!checkfile.fail())
			{ //to make sure that an existing file is not tempered with and that the output is saved in new text file.
				throw runtime_error("File " + filename + " already exists. Enter a new file name. ");
			}
			ofstream myfile(filename);
			if(myfile.is_open())
			{
				myfile << temp2 << endl;
				while(myheap.getSize()!=0)
				{
					myfile << myheap.getMin() << endl;
					myheap.removeMin();
				}
				cout << "File Created Successfully. " << endl;
				myfile.close();
			}
		}
		
		// PRINT ALL IN CITY
		else if (choice == "5")
		{
			string cityName;
			cout << "Enter the name of the city" << endl;
			getline(cin, cityName);
			string pri = Normalise(cityName);
			myHashMap2.printLinkedList(pri);
		}
		
		// INVALID CHOICE
		else if (choice != "6")
		{
			choice = "0";
			cout << "Please enter a valid choice between 1 and 5." << endl;
			continue;
		}
		//ELSE, CHOICE = 6 QUIT.
	}
	exit(0);
}

