#ifndef TASK_LIST
#define TASK_LIST

#include "task.h"

class taskList
{
public:
        //constructors
       taskList();
       taskList( const char fileName[]);

        //destructor
       ~taskList();

        //accessor functions
        int searchEntry( const char course[], task &match) const;
        void printAll() const;
        void saveAll( const char fileName[]) const;

        //mutator functions
        void loadMemory( const char fileName[]);
        void insertTask( const task& newTask);

private:
        struct node
       {

               node *link; //link stores the address of the next node
               task taskInfo; //taskInfo is the task object with the necessary data

               //constructor for node when task object is passed in
              node( const task& taskData)
              {
                      char course[101];
                      char task[101];
                      char due[101];

                      taskData.getCourse(course); //the task object accesses getCourse, which copies the course from the instance variable into the allocated char array that was sent in from this function.
                      taskData.getTask(task);
                      taskData.getDue(due);
                     taskInfo.setCourse(course); //course is copied from the local char array into the task object belonging to the node
                     taskInfo.setTask(task);
                     taskInfo.setDue(due); //WHY CANT I JUST GO STRAIGHT TO SET WHY DO I HAVE TO GET COURSE FROM INSTANCE VARIABLE FIRST)
                     link = 0;
              }
       };

        node *head; //node to point to the first node
        node *tail; //node the point to the last node
        node *newNode; //node to create new node with
        int	size; //node index
};

#endif
