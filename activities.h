/*
Activities hierarchy for Program 2
Ben Rimedio - 10/26/2021
CS202 - Fall 2021
Instructor: Karla Fant
This is the core hierarchy of activities.
The abstract base class is Activity. The derived classes are In_person, Remote, and Online
*/

#ifndef ACT_H
#define ACT_H

#include <string>
#include <vector>

#define MAX_STREAM 1024

enum priority {HIGH, MED, LOW};

//Activity (base):
class Activity
{
public:
    Activity();
    Activity(const Activity& source);
    virtual ~Activity();
    virtual void display(void) const = 0;
    virtual void set_name(char* a_name) = 0;
    virtual void set_priority(priority a_prior) = 0;
    virtual void input(void) = 0;
    unsigned short generate_index(void);
    bool compare_name(char* a_name);
protected:
    char* name;
    priority prior;
};

//In person:
class In_person : public Activity
{
public:
    In_person();
    In_person(const In_person& source);
    ~In_person();
    void display(void) const;
    void set_name(char* a_name);
    void set_priority(priority a_prior);
    void input(void);
    bool consult(void);
    bool consult(std::string a_cons);
    void set_room(std::string a_room);
    bool remove_consult(unsigned short index);
protected:
    std::string room;
    std::vector<std::string> consults;
};

//Remote:
class Remote : public Activity
{
public:
    Remote();
    Remote(const Remote& source);
    ~Remote();
    void display(void) const;
    void set_name(char* a_name);
    void set_priority(priority a_prior);
    void input(void);
    void set_zoom(std::string a_zoom);
protected:
    std::string zoom_id;
};

//Online:
class Online : public Activity
{
public:
    Online();
    Online(const Online& source);
    ~Online();
    void display(void) const;
    void set_name(char* a_name);
    void set_priority(priority a_prior);
    void input(void);
    void set_url(std::string a_url);
protected:
    std::string url;
};

#endif
