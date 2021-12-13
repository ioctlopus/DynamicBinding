/*
Data structures for Program 2
Ben Rimedio - 10/26/2021
CS202 - Fall 2021
Instructor: Karla Fant
These are the definitions for the data structures (clients) for Program 2.
There is a node class, derived from activity and an array of doubly linked lists of these nodes.
*/

#ifndef DATA_H
#define DATA_H

#define NUM_PRIORITIES 3

class node
{
public:
    node();
    node(In_person*& inp);
    node(Remote*& rem);
    node(Online*& onl);
    node(const node& source);
    ~node();
    node*& go_next(void);
    node*& go_prev(void);
    void set_next(node*& a_node);
    void set_prev(node*& a_node);
    void display(void) const;
    void input(void);
    void set_name(char* a_name);
    void set_priority(priority a_prior);
    bool consult(void);
    unsigned short generate_index(void);
    bool compare_name(char* a_name);
    bool remove_consult(unsigned short index);
protected:
    node* next;
    node* prev;
    Activity* data;
};

class a_llist
{
public:
    a_llist();
    a_llist(const a_llist& source);
    ~a_llist();
    void insert(void);
    void insert(node*& a_node);
    bool remove(node*& a_node);
    bool remove(char* rem_name);
    void display();
    node* retrieve(char* a_name);
    bool remove_consult(char* a_name, unsigned short index);
protected:
    node** data;

    void r_array_display(node** begin, size_t index);
    void list_display(node*& head);
    void r_insert(node*& a_head, node*& a_node);
    void r_array_destroy(node** begin, size_t index);
    void list_destroy(node*& head);
    bool r_remove(node*& a_head, node*& a_node);
    node* r_array_retrieve(node** begin, unsigned short index, char*& a_name);
    node* list_retrieve(node*& head, char*& a_name);
    void list_copy(node*& dest, node*& src);

};

#endif
