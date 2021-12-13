/*
Data structure implementations for program 1
Ben Rimedio - 10/26/2021
CS202 - Fall 2021
Instructor: Karla Fant
These are the implementations of the data structures (clients) for the activities.
Insert, remove, display, and destroy are all supported.
*/

#include <iostream>
#include "activities.h"
#include "datastructures.h"

//-------------------------------------node----------------------------------------------------
//Default constructor:
node::node()
{
    next = nullptr;
    prev = nullptr;
    data = nullptr;
}

//Constructor for In_person:
node::node(In_person*& inp)
{
    next = nullptr;
    prev = nullptr;
    data = inp;
}

//Constructor for Remote:
node::node(Remote*& rem)
{
    next = nullptr;
    prev = nullptr;
    data = rem;
}

//Constructor for Online:
node::node(Online*& onl)
{
    next = nullptr;
    prev = nullptr;
    data = onl;
}

//Copy constructor. Uses RTTI to determine data type:
node::node(const node& source)
{
    In_person* inp_test = dynamic_cast<In_person*>(source.data);
    Remote* rem_test = dynamic_cast<Remote*>(source.data);
    Online* onl_test = dynamic_cast<Online*>(source.data);
    
    if(!source.data)
        data = nullptr;
    else if(inp_test)
        data = new In_person(*inp_test);
    else if(rem_test)
        data = new Remote(*rem_test);
    else if(onl_test)
        data = new Online(*onl_test);
    else
        data = nullptr;

    next = nullptr;
    prev = nullptr;
}

//Destructor:
node::~node()
{
    next = nullptr;
    prev = nullptr;
    delete data;
}

//Get next:
node*& node::go_next(void)
{
    return next;
}

//Get previous:
node*& node::go_prev(void)
{
    return prev;
}

//Set next with node* as arg:
void node::set_next(node*& a_node){
    next = a_node;
}

//Set previous with node* as arg:
void node::set_prev(node*& a_node)
{
    prev = a_node;
}

//Display wrapper:
void node::display(void) const
{
    if(data)
        data->display();
}

//Input wrapper
void node::input(void)
{
    data->input();;
}

//Name wrapper with char* as arg:
void node::set_name(char* a_name)
{
    data->set_name(a_name);
}

//Prioroty wrapper with priority as arg:
void node::set_priority(priority a_prior)
{
    data->set_priority(a_prior);
}

//Consult wrapper (for In_person only). Uses simple RTTI to check types before continuing:
bool node::consult(void)
{
    In_person* test_ptr = dynamic_cast<In_person*>(data);
    if(test_ptr)
    {
        test_ptr->consult();
        return true;
    }
    else
    {
        return false;
    }
}

//Resturn index as an unsigned short:
unsigned short node::generate_index(void)
{
    return data->generate_index();
}

//Wrapper for compare name with char* as arg:
bool node::compare_name(char* a_name)
{
    return data->compare_name(a_name);
}

bool node::remove_consult(unsigned short index)
{
    In_person* test_ptr = dynamic_cast<In_person*>(data);
    if(test_ptr)
    {
        test_ptr->remove_consult(index);
        return true;
    }
    else
    {
        return false;
    }
}
//-------------------------------Array of doubly linked lists----------------------------------
//Default constructor:
a_llist::a_llist()
{
    data = new node*[NUM_PRIORITIES];
    for(int i = 0; i < NUM_PRIORITIES; i++)
        data[i] = nullptr;
}

//Copy constructor:
a_llist::a_llist(const a_llist& source)
{
    data = new node*[NUM_PRIORITIES];
    for(int i = 0; i < NUM_PRIORITIES; i++)
        data[i] = nullptr;

    for(int i = 0; i < NUM_PRIORITIES; i++)
        list_copy(data[i], source.data[i]);
}

//Destructor:
a_llist::~a_llist()
{
    r_array_destroy(data, 0);
    delete [] data;
}

//Copy one list recursively with a destination node* and a source node* as args:
void a_llist::list_copy(node*& dest, node*& src)
{
    if(!src)
        return;
    dest = new node(*src);
    list_copy(dest->go_next(), src->go_next());
}

//Destroy each list with array of node* as args and an index as an arg:
void a_llist::r_array_destroy(node** begin, size_t index)
{
    if(index >= NUM_PRIORITIES)
        return;
    list_destroy(*(begin + index));
    r_array_destroy(begin, index + 1);
}

//Destroy a single list with head node* as arg:
void a_llist::list_destroy(node*& head)
{
    if(!head)
        return;
    list_destroy(head->go_next());
    delete head;
}

//Display entire structure:
void a_llist::display(void)
{
    r_array_display(data, 0);
    std::cout << std::endl;
}

//Move through the list and display each list with node** and index as args:
void a_llist::r_array_display(node** begin, size_t index)
{
    if(index >= NUM_PRIORITIES)
        return;
    std::cout << "\n=======================================================\nPRIORITY: ";
    switch(index)
    {
        case 0:
            std::cout << "HIGH\n=======================================================";
            break;
        case 1:
            std::cout << "MEDIUM\n=======================================================";
            break;
        case 2:
            std::cout << "LOW\n=======================================================";
            break;
        default:
            std::cout << std::endl;
            break;
    }
    list_display(*(begin + index));
    r_array_display(begin, index + 1);
}

//Display each list in the array with head node* as arg:
void a_llist::list_display(node*& head)
{
    if(!head)
        return;
    head->display();
    list_display(head->go_next());
}

//Insert by node with new node* as arg:
void a_llist::insert(node*& a_node)
{
    unsigned short ind = a_node->generate_index();
    r_insert(data[ind], a_node);
}

//Recursive insert into one list with head node* and new node* as args:
void a_llist::r_insert(node*& a_head, node*& a_node)
{
    //Empty list:
    if(!a_head)
    {
        a_head = a_node;
        return;
    }
    //Insert at end:
    if(!a_head->go_next())
    {
        a_node->set_prev(a_head);
        a_head->set_next(a_node);
        return;
    }
    //Keep going:
    r_insert(a_head->go_next(), a_node);
}

//Insert via user input:
void a_llist::insert(void)
{
    node* new_activity;
    unsigned short choice;
    char consult_choice;
    bool another = true;

    //Menu for type:
    std::cout << "\n1) New in person activity\n2) New remote activity\n3) New online activity\n>>> ";
    while(!(std::cin >> choice) || choice < 1 || choice > 3)
    {
        std::cout << "Invalid input." << std::endl;
        std::cin.clear();
        std::cin.ignore(MAX_STREAM, '\n');
        std::cout << "\n1) New in person activity\n2) New remote activity\n3) New online activity\n>>> ";
    }
    std::cin.clear();
    std::cin.ignore(MAX_STREAM, '\n');
    
    //Assign proper type to new_activity:
    if(choice == 1)
    {
        In_person* new_inp = new In_person;
        new_inp->input();
        new_activity = new node(new_inp);
    }
    else if(choice == 2)
    {
        Remote* new_rem = new Remote;
        new_rem->input();
        new_activity = new node(new_rem);
    }
    else if(choice == 3)
    {
        Online* new_onl = new Online;
        new_onl->input();
        new_activity = new node(new_onl);
    }
    
    //Add consultations (if possible) until user says no more:
    while(another)
    {
        std::cout << "Add any associated meetings or consultations? (Y/N): ";
        while(!(std::cin >> consult_choice) || (toupper(consult_choice) != 'Y' && toupper(consult_choice) != 'N'))
        {
            std::cout << "\nInvalid choice.\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(MAX_STREAM, '\n');
            std::cout << "Add any associated meetings or consultations? (Y/N):";
        }
        std::cin.clear();
        std::cin.ignore(MAX_STREAM, '\n');
        if(toupper(consult_choice) == 'Y')
        {
            if(!(new_activity->consult()))
            {
                std::cout << "\nConsults must be a non-empty string and can only be added to in-person activities.\n" << std::endl;
                another = false;
            }
        }
        else
        {
            another = false;
        }
    }

    //Insert the new data:
    insert(new_activity);
    std::cout << std::endl;
}

//Retrieve a node based on its char* name:
node* a_llist::retrieve(char* a_name)
{
    if(!a_name)
        return nullptr;
    return r_array_retrieve(data, 0, a_name);
}

//Move through array and search each list until name is found or not with array of node*, index, and char* name as args:
node* a_llist::r_array_retrieve(node** begin, unsigned short index, char*& a_name)
{
    node* ret = nullptr;
    if(index >= NUM_PRIORITIES)
    {
        return nullptr;
    }
    else
    {
        ret = list_retrieve(*(data + index), a_name);
        if(ret)
            return ret;
        else
            return r_array_retrieve(begin, index + 1, a_name);
    }
}

//Retrieve from individual list with node* head and char* name as args:
node* a_llist::list_retrieve(node*& head, char*& a_name)
{
    if(!head)
        return nullptr;
    if(head->compare_name(a_name))
        return head;
    return list_retrieve(head->go_next(), a_name);
}


//Remove by node. Returns false if node isn't found with node* as arg:
bool a_llist::remove(node*& a_node)
{
    if(!a_node)
        return false;
    return r_remove(data[a_node->generate_index()], a_node);
}

//Recursive removal:
bool a_llist::r_remove(node*& a_head, node*& a_node)
{
    //Empty list/not in list:
    if(!a_head)
        return false;
    //First element:
    if(a_head->go_prev() == nullptr && a_head == a_node)
    {
        node* tmp = a_head;
        a_head = a_head->go_next();
        delete tmp;
        return true;
    }
    //Match:
    if(a_head == a_node)
    {
        if(a_head && a_head->go_prev())
            a_head->go_prev()->set_next(a_head->go_next());
        if(a_head && a_head->go_next())
            a_head->go_next()->set_prev(a_head->go_prev());
        delete a_head;
        a_head = nullptr;
        return true;
    }
    //Keep going:
    return r_remove(a_head->go_next(), a_node);
}

//Remove by name with char* as arg:
bool a_llist::remove(char* rem_name)
{
    node* to_remove = retrieve(rem_name);
    return remove(to_remove);
}

//Remove consultation by name with char* name and short index as args:
bool a_llist::remove_consult(char* a_name, unsigned short index)
{
    node* to_remove = nullptr;
    to_remove = retrieve(a_name);
    if(to_remove)
    {
        return to_remove->remove_consult(index);
    }
    else
    {
        return false;
    }
}
