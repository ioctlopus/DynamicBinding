/*
Activities hierarchy implementations
Ben Rimedio - 10/26/2021
CS202 - Fall 2021
Instructor: Karla Fant
These are the implementations of the functions in the Activity (base) and derived classes.
Classes are largely self-similar, lending themselves to dynamic binding.
*/

#include <cstring>
#include <string>
#include <iostream>
#include "activities.h"

//-------------------------------Activity (abstract base class)---------------------------------------
//Default constructor:
Activity::Activity(){
    name = nullptr;
    prior = LOW;
}

//Copy constructor:
Activity::Activity(const Activity& source)
{
    name = nullptr;
    if(source.name)
    {
        name = new char[strlen(source.name) + 1];
        strcpy(name, source.name);
    }
}

//Destructor:
Activity::~Activity()
{
    if(name)
        delete [] name;
    name = nullptr;
}

//Generate index based on priority:
unsigned short Activity::generate_index(void)
{
    return static_cast<unsigned short>(prior);
}

//Compare name with an argument:
bool Activity::compare_name(char* a_name)
{
    return (!(strcmp(a_name, name)));
}

//----------------------------------In_person---------------------------------------------------------
//Default constructor:
In_person::In_person() : Activity()
{
    room.clear();
    consults.clear();
}

//Copy constructor:
In_person::In_person(const In_person& source) : Activity(source)
{
    room = source.room;
    consults = source.consults;
}

//Destructor:
In_person::~In_person()
{
    room.clear();
    consults.clear();
}

//Display function:
void In_person::display(void) const
{
    std::cout << "\nIn person session: " << name
              << "\nin room: " << room << ", with the following consultation appointments:" << std::endl;
    for(size_t i = 0; i < consults.size(); i++)
    {
        std::cout << '\t' << i << ": " << consults[i] << std::endl;
    }
}

//Set name of in-person activity:
void In_person::set_name(char* a_name)
{
    if(name)
        delete [] name;
    name = new char[strlen(a_name) + 1];
    strcpy(name, a_name);
}

//Set room of in-person activity with string as arg:
void In_person::set_room(std::string a_room){
    room = a_room;
}

//Set priority of in-person activity with priority as arg:
void In_person::set_priority(priority a_prior)
{
    prior = a_prior;
}

//Input new name, room, and set priority:
void In_person::input(void)
{
    std::string new_room;
    int new_prior;
    char* buff = new char[MAX_STREAM + 1];
    
    std::cout << "\nEnter the name of the in-person activity: ";
    std::cin.get(buff, MAX_STREAM, '\n');
    std::cin.clear();
    std::cin.ignore(MAX_STREAM, '\n');
    std::cout << "Enter the room the in-person activity is in: ";
    std::getline(std::cin, new_room);
    set_room(new_room);
    std::cout << "Enter the priority for the task: 0) High 1) Med 2)Low: ";
    while(!(std::cin >> new_prior) || new_prior < 0 || new_prior > 2)
    {
        std::cout << "\nInvalid input.\n" << std::endl;
        std::cin.clear();
        std::cin.ignore(MAX_STREAM, '\n');
        std::cout << "Enter the priority for the task: 0)High 1)Med 2)Low: ";
    }
    std::cin.clear();
    std::cin.ignore(MAX_STREAM, '\n');

    set_priority(static_cast<priority>(new_prior));
    set_name(buff);

    delete [] buff;
}

//Add a professor consultation/meeting with string as arg:
bool In_person::consult(std::string a_cons)
{
    if(a_cons.size() <= 0)
        return false;
    consults.push_back(a_cons);
    return true;
}

//Input consultation. Return false if empty:
bool In_person::consult(void)
{
    std::string new_cons;
    std::cout << "Enter a description of the professor meeting: ";
    std::getline(std::cin, new_cons);
    if(new_cons.size() <= 0)
        return false;
    return consult(new_cons);
}

bool In_person::remove_consult(unsigned short index)
{
    if(index > consults.size() - 1)
        return false;
    consults.erase(consults.begin() + index);
    return true;
}

//--------------------------------Remote-------------------------------------------------------------
//Default constructor:
Remote::Remote() : Activity()
{
    zoom_id.clear();
}

//Copy constructor:
Remote::Remote(const Remote& source) : Activity(source)
{
    zoom_id = source.zoom_id;
}

//Destructor:
Remote::~Remote()
{
    zoom_id.clear();
}

//Display remote activity:
void Remote::display(void) const
{
    std::cout << "\nRemote session: " << name << " with Zoom ID: " << zoom_id << std::endl;
}

//Set name with char* as arg:
void Remote::set_name(char* a_name)
{
    if(name)
        delete [] name;
    size_t size_name = strlen(a_name);
    name = new char[size_name + 1];
    strcpy(name, a_name);
}

//Set Zoom ID with string as arg:
void Remote::set_zoom(std::string a_zoom)
{
    zoom_id = a_zoom;
}

//Set priority level with priority as arg:
void Remote::set_priority(priority a_prior)
{
    prior = a_prior;
}

//Input a new remote activity:
void Remote::input(void)
{
    std::string new_zoom;
    int new_prior;
    char* buff = new char[MAX_STREAM + 1];

    std::cout << "\nEnter the name of the remote activity: ";
    std::cin.get(buff, MAX_STREAM, '\n');
    std::cin.clear();
    std::cin.ignore(MAX_STREAM, '\n');
    std::cout << "Enter the Zoom ID of the remote activity: ";
    std::getline(std::cin, new_zoom);
    set_zoom(new_zoom);
    std::cout << "Enter the priority for the task: 0)High 1)Med 2)Low: ";
    while(!(std::cin >> new_prior) || new_prior < 0 || new_prior > 2)
    {
        std::cout << "\nInvalid input.\n" << std::endl;
        std::cin.clear();
        std::cin.ignore(MAX_STREAM, '\n');
        std::cout << "Enter the priority for the task: 0)High 1)Med 2)Low: ";
    }
    std::cin.clear();
    std::cin.ignore(MAX_STREAM, '\n');
    set_priority(static_cast<priority>(new_prior));
    set_name(buff);

    delete [] buff;
}

//--------------------------------Online-------------------------------------------------------------
//Default constructor:
Online::Online() : Activity()
{
    url.clear();
}

//Copy constructor:
Online::Online(const Online& source) : Activity(source)
{
    url = source.url;
}

//Destructor:
Online::~Online()
{
    url.clear();
}

//Display:
void Online::display(void) const
{
    std::cout << "\nOnline class/activity: " << name << " accessible at: " << url << std::endl;
}

//Set new name with char* as arg:
void Online::set_name(char* a_name)
{
    if(name)
        delete [] name;
    size_t size_name = strlen(a_name);
    name = new char[size_name + 1];
    strcpy(name, a_name);
}

//Set new priority with priority as arg:
void Online::set_priority(priority a_prior)
{
    prior = a_prior;
}

//Set URL with string as arg:
void Online::set_url(std::string a_url)
{
    url = a_url;
}

//Input new online activity:
void Online::input(void)
{
    std::string new_url;
    int new_prior;
    char* buff = new char[MAX_STREAM + 1];

    std::cout << "\nEnter the name of the online activity: ";
    std::cin.get(buff, MAX_STREAM, '\n');
    std::cin.clear();
    std::cin.ignore(MAX_STREAM, '\n');
    std::cout << "Enter the URL to access the online activity: ";
    std::getline(std::cin, new_url);
    set_url(new_url);
    std::cout << "Enter the priority for the task: 0)High 1)Med 2)Low: ";
    while(!(std::cin >> new_prior) || new_prior < 0 || new_prior > 2)
    {
        std::cout << "\nInvalid input.\n" << std::endl;
        std::cin.clear();
        std::cin.ignore(MAX_STREAM, '\n');
        std::cout << "Enter the priority for the task: 0)High 1)Med 2)Low: ";
    }
    std::cin.clear();
    std::cin.ignore(MAX_STREAM, '\n');
    set_priority(static_cast<priority>(new_prior));
    set_name(buff);

    delete [] buff;
   
}
