/* 
 * File:   main.cpp
 * Author: najaomar
 *
 * Created on November 21, 2019, 4:34 PM
 */

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "TreeDB.h"

// Function to print message if the entry specified by the user 
// already exists in the tree
void entryExists();

// Function to print message after a successful operation
void success();

// Function to print message if the entry specified by the user 
// does not exist
void doesNotExist();

int main() 
{
    TreeDB newTree;
    
    string line;
    string command;
    
    string name;
    unsigned int IPaddress;
    string active;
    
    cout << "> "; // Prompt for input
    getline(cin, line); // Get a line from standard input
    
    while (!cin.eof())
    {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;
        
        // Check for the command and act accordingly
        if (command == "insert")
        {
            lineStream >> name;
            lineStream >> IPaddress;
            lineStream >> active;
            
            DBentry* newEntry = new DBentry(name, IPaddress, false);
            
            // If the entry being inserted already exists in the tree,
            // delete the entry. 
            if (!newTree.insert(newEntry))
            {
                entryExists();
                delete newEntry;
            } 
            else 
            {
                if (active == "active")
                {
                    newEntry->setActive(true);
                }
                else if (active == "inactive")
                {
                    newEntry->setActive(false);
                }
                
                // Insert the entry into the tree
                newTree.insert(newEntry);
                success(); 
            }
        } 
        else if (command == "find")
        {            
            lineStream >> name;
            
            // If the entry could not be found
            if (newTree.find(name) == NULL)
            {
                doesNotExist();
            }
            else 
            {
                // Find the entry
                DBentry* searchedEntry = newTree.find(name);
                
                cout << *searchedEntry;
            }
        } 
        else if (command == "remove")
        { 
            lineStream >> name;
            
            // If the entry could not be found
            if (!newTree.remove(name)) 
            {
                doesNotExist();
            }
            else
            {
                // Remove the entry from the tree
                newTree.remove(name);
                success();
            }
        } 
        else if (command == "printall")
        {
            // Print all entries in the tree
            cout << newTree;
        }
        else if (command == "printprobes")
        {
            lineStream >> name;
            
            // If the entry could not be found
            if (newTree.find(name) == NULL)
            {
                doesNotExist();
            }
            else
            {
                // Print the number of comparisons made to find the entry
                newTree.printProbes();
            }
        } 
        else if (command == "removeall")
        {
            // Delete the tree
            newTree.clear();
            success();
        } 
        else if (command == "countactive")
        {
            // Count the number of active entries in the tree
            // and print the number.
            newTree.countActive();
        } 
        else if (command == "updatestatus")
        {
            lineStream >> name;
            lineStream >> active;
            
            // If the entry could not be found
            if (newTree.find(name) == NULL)
            {
                doesNotExist();
            }
            else 
            {
                DBentry* searchedEntry = newTree.find(name);

                if (active == "active")
                {
                    searchedEntry->setActive(true);
                }
                else if (active == "inactive")
                {
                    searchedEntry->setActive(false);
                }
                
                success();
            }
        }
        
        // Once the command has been processed, prompt for the
        // next command.
        cout << "> ";          // Prompt for input.
        getline(cin, line);   // Get the command line.
        
    } // End input loop until EOF.
    
    // Delete the tree
    newTree.clear();

    return 0;
}

void entryExists()
{
    cout << "Error: entry already exists" << endl;
}

void success()
{
    cout << "Success" << endl;
}

void doesNotExist()
{
    cout << "Error: entry does not exist" << endl;
}


