/*
Program Name: tsalesmen.cpp
Programmer: Alexandru Malos
Class: CS 3335 A 
HW: 05   
Problem: Toy salesmen program given by Dr. Dasgupta.
Date: 12/01/15
This program will help manage toy salesmen and their toy sales.This program will be able to update 
salesman's data periodically with sales and time over which the money was collected.It can also 
show the sales per hour for a particular salesmen. 
*/ 



#include <cstring>
#include <iostream>
using namespace std;


const int MAX_NAME = 20;
const int MAX_SALESMEN = 5;
const int NOT_FOUND = -1;


struct Seller
{
   // Running total of money he collected. 
   float sales; 
      
   // Running total time, in hours.
   float time; 
   
   // Name of the salesman. 
   char name[MAX_NAME + 1]; 
   
};


struct ListOfSalesmen
{

   // Number of salesmen in the list. 
   int num; 
   Seller salesman[MAX_SALESMEN];
   
};


// Prototype declaration for the InitSeller function.
void InitSeller(Seller & s, const char name[]);


// Prototype declaration for the UpdateSeller function.
void UpdateSales(Seller & s, float sales, float time);


// Prototype declaration for the SellerHasName function.
bool SellerHasName(const Seller & s, const char name[]);


// Prototype declaration of the SalesValue function.
float SalesValue(Seller & s);


// Function to initialize salesmen list.
void InitListOfSalesmen(ListOfSalesmen & sl);


// Prototype declarations for the add,output and update functions in the user menu.
void MenuAdd(ListOfSalesmen & sl);
void MenuOutput(ListOfSalesmen & sl);
void MenuUpdate(ListOfSalesmen & sl);


// Prototype declaration of the Find function.
int Find(const ListOfSalesmen & sl, const char name[]);


int main()
{
	// Salesmen list declaration. 
   ListOfSalesmen sl;
   
	// Initialization of the salesmen list. 
   InitListOfSalesmen(sl);
   
   char option = 'X';
   
   // While loop that allows user to add, output, update or quit.
   while (option != 'Q')
   {
   
   	// Reads in user options 
      cin >> option;
      
      switch (option)
      {
      
         case 'A':
            {
            
            // Calls the add function. 
               MenuAdd(sl);
               
               break;
            }
            
         case 'O':
            {
            
            // Calls the output function. 
               MenuOutput(sl);
               
               break;
            }
            
         case 'U':
            {
            
            // Calls the update function 
               MenuUpdate(sl);
               
               break;
            }
            
         case 'Q':
            {
            
            // Does nothing, will exit the program. 
               break;
            }
            
      }
      
   }
   
	// Final program output after termination. 
   cout << "Normal Termination of Sales Program." << endl;
   
   return 0;
}

// List of salesman function to initialize the list. 
void InitListOfSalesmen(ListOfSalesmen &sl)
{
	// Initializes the list to zero.
   sl.num = 0;
}

// Function to initialize sellers.
void InitSeller(Seller & s, const char name[])
{
	 
    // Initializes the Salesman's sales and time to 0.0.
   s.sales = s.time = 0;	
   
   
	// Initializes the Salesman's name to name.
   strcpy(s.name, name);
}


 // Function to check whether or not a given seller has the given name.
bool SellerHasName(const Seller & s, const char name[])
{
	// Returns true if the salesman's name is the same as name; false otherwise.
   return strcmp(s.name, name) == 0;
}


// Function to update the sales of a seller.Adds the money and time to the salesman's accumulated sales and time.
void UpdateSales(Seller & s, float sales, float time)
{
	// This will add the sales amounts.
   s.sales += sales;
   
	// This will add the times.
   s.time += time;
}

 // Function to compute the sales value per hour
float SalesValue(Seller & s)
{
	// Initialize variable.
   float val = 0;
   
	
   // Returns 0.0 if the salesman's time is 0.0.
   val = (s.time > 0) ? s.sales / s.time : 0;	
   
	   
   // It also zeroes the salesman's sales & time when done calculating.
   s.sales = s.time = 0;
   
	// Returns sales per hour for the salesman.
   return val;
}



// Add function for adding a seller.
void MenuAdd(ListOfSalesmen & sl)
{
	// Array which will  store seller name.
   char name[MAX_NAME + 1];
   
	// Reads input from user and saves it. 
   cin >> name;
   
	// index of that name (if exists in the list.
   int ind = Find(sl, name);


   if (sl.num >= MAX_SALESMEN)
   {
   	// Condition if list is full. 
      cout << name << " not added. List is full." << endl;
   }
   
   else if (ind != NOT_FOUND)
   {
   	// Condition if the seller is already in the list. 
      cout << name << " is already in the list." << endl;
   }
   
   else
   {
   	// If above two conditions are met, this will add the seller. 
      Seller s;
      
   	// New seller initialization.
      InitSeller(s, name);
      
   	// StoreS seller in the list. 
      sl.salesman[sl.num] = s;
      
   	// Output statement for the new seller. 
      cout << name << " is salesman " << sl.num << endl;
      
   	// Increases the number of sellers.
      sl.num++;
   }
}


// Output function for the menu 
void MenuOutput(ListOfSalesmen & sl)
{
	// Array which will store the names.
   char name[MAX_NAME + 1];
   
	// This will read in a sellers name. 
   cin >> name;
   
	// This function will search for a seller by that name.
   int ind = Find(sl, name);
   
   if (ind == NOT_FOUND)
   {
   	// Condition if seller was not found.
      cout << "Cannot output. " << name << " is not in the list." << endl;
      
   }
   
   else
   {		
   	// Condition is seller was found and output statement. 
      cout << name << ": $" << SalesValue(sl.salesman[ind]) << " per hour" << endl;
   }
   
}

// Update function for the menu 
void MenuUpdate(ListOfSalesmen & sl)
{
	// Array which will store the names.
   char name[MAX_NAME + 1];
   
   
	// Variables for sales and time.
   float sales, time;
   
	// Reads in the name,sales and time from user.
   cin >> name;
   
   cin >> sales >> time;
   
	// Search for seller by name.
   int ind = Find(sl, name);
   
   if (ind == NOT_FOUND)
   {
   
   	// Condition for when the seller does not exist. 
      cout << "Cannot update. " << name << " is not in the list." << endl;
      
   }
   else
   {
   
   	// Condition for when the seller does exist.
      UpdateSales(sl.salesman[ind], sales, time);
      
   	// This will output the results 
      cout << "Salesperson " << name << " sold $"
         << sales << " of toys in " << time << " Hours" << endl;
   }
}

// Find function to find a seller by their name.
int Find(const ListOfSalesmen & sl, const char name[])
{
   int i;
   
   for (i = 0; i < sl.num; i++)
   {
   
      if (SellerHasName(sl.salesman[i], name))
      {
      
      	// Condition, if we find a seller. 
         return i;
      }
   }
   
   // Condition if seller was not found.
   return NOT_FOUND;
}
