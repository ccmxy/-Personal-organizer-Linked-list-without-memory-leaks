#include "task.h"
#include <iostream>


//Default constructor

task::task()
{
       course = new char[strlen( "no course") + 1]; //course now contains address of an uninitalized char array of 10 chars
       strcpy(course, "no course"); //"no course" + null char are copied into the contents of the char array that course points to
       thisTask = new char[strlen( "no task") + 1];
       strcpy(thisTask, "no task");
       due = new char[strlen( "no course") + 1];
       strcpy(due, "no due");
}


/*
Destructor.
*/
task::~task()
{
        if (course != NULL)
               delete[] course; //the array that course points to is deallocated from main memory. [] needed becaUse course was allocated with new[]
        if (thisTask != NULL)
               delete[] thisTask;
        if (due != NULL)
               delete[] due;
}

/*
The getTaskVariable functions copy from the instance variable into char variables that are sent in.
*/
void task ::getCourse(char course[]) const
{
       strcpy( course, this->course);
}

void task ::getTask(char task[]) const
{
       strcpy( task, this->thisTask);
}

void task ::getDue(char due []) const
{
       strcpy( due, this->due);
}

/*
The setTaskVariable functions delete the default array of the instance variables, allocate one of the proper size, and load it with the contents of the array passed into it.
*/
void task ::setCourse(const char course[])
{
        if ( this->course != NULL){ //deletes the "no course" chars in the instance variable
               delete[] this->course; //calls the destructor
       }
        this->course = new char[strlen( course) + 1]; //allocates a char array the length of the "course" array passed in + 1 for null char
       strcpy( this->course, course); //copies the course array passed into it into the instance variable
}


void task ::setTask(const char task[])
{
        if ( this->thisTask != NULL){
               delete[] this->thisTask;
       }
        this->thisTask = new char[strlen( task) + 1];
       strcpy( this->thisTask, task);
}

void task ::setDue(const char due [])
{
        if ( this->due != NULL){
               delete[] this->due;
       }
        this->due = new char[strlen( due) + 1];
       strcpy( this->due, due);
}
