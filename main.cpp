/*
Main driver for Program 2
Ben Rimedio - 11/01/2021
CS202 - Fall 2021
Instructor: Karla Fant
This is the main driver for Program 2. There is a simple menu system allowing for testing the
data structures and main hierarchy. Basic error handling is implemented in main().
*/

#include <iostream>
#include <cstdlib>
#include "activities.h"
#include "datastructures.h"

int main(void){
    int ret = EXIT_SUCCESS;
    char choice = '\0';
    char* rem_name = nullptr;
    char* rem_cons = nullptr;
    unsigned short cons_index = 0;
    a_llist* copy_test = nullptr;
    a_llist acts;

    std::cout << "\nWelcome! Manage your school activities using the following menu:\n" << std::endl;

    while(toupper(choice) != 'Q')
    {
        std::cout << "(A)dd a new activity.\n(D)isplay activities\n(R)emove activity by name\n(E)rase a consultation\n(C)opy table and display\n(Q)uit\n>>> ";
        while(!(std::cin >> choice))
        {
            std::cout << "\n\nStandard input stream closed unexpectedly. Exiting...\n" << std::endl;
            ret = EXIT_FAILURE;
            std::cin.clear();
            std::cin.ignore(MAX_STREAM, '\n');
            delete [] rem_name;
            return ret;
        }
        std::cin.clear();
        std::cin.ignore(MAX_STREAM, '\n');
        switch(toupper(choice))
        {
            case 'A':
                acts.insert();
                break;
            case 'D':
                acts.display();
                std::cout << std::endl << std::endl;
                break;
            case 'R':
                rem_name = new char[MAX_STREAM + 1];
                
                std::cout << "\nWhat activity would you like to remove?: ";
                std::cin.get(rem_name, MAX_STREAM, '\n');
                if(!(acts.remove(rem_name)))
                    std::cout << "\nName not found.\n";
                
                delete [] rem_name;
                std::cout << std::endl;
                break;
            case 'E':
                rem_cons = new char[MAX_STREAM];
                std::cout << "\nWhich activity would you like to remove the consult from?: ";
                std::cin.get(rem_cons, MAX_STREAM, '\n');
                std::cout << "Enter the index to remove: ";
                while(!(std::cin >> cons_index))
                {
                    std::cout << "Invalid input. Enter a valid index: ";
                    std::cin.clear();
                    std::cin.ignore(MAX_STREAM, '\n');
                }
                std::cin.clear();
                std::cin.ignore(MAX_STREAM, '\n');
                if(acts.remove_consult(rem_cons, cons_index))
                    std::cout << "Consult removed." << std::endl;
                else
                    std::cout << "Unable to remove consult." << std::endl;
                std::cout << std::endl;
                delete [] rem_cons;
                break;
            case 'C':
                copy_test = new a_llist(acts);
                copy_test->display();
                std::cout << std::endl;
                delete copy_test;
                break;
            case 'Q':
                std::cout << "\nGoodbye!\n" << std::endl;
                break;
            default:
                std::cout << "\nInvalid choice.\n" << std::endl;
                break;
        }
    }

    return ret;
}
