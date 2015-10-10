#include "taskList.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <assert.h>
using namespace std;


/*
Default constructor. It initializes the list to be empty. It is not used in this program.
*/
taskList::taskList()
{
       head = NULL;
       tail = NULL;
       size = 0;
}

/*
The taskList constructor with fileName as parameter.
*/
taskList::taskList(const char fileName [])
{
       head = NULL;
       tail = NULL;
       size = 0;
       loadMemory( fileName);
}

/*
Destructor.
*/
taskList::~taskList()
{
        node *temp; //create node pointer called temp
        while (head != NULL) //as long as head points to something...
       {
              temp = head; //set temp to point to what head is pointing to
              head = head->link; //set head to point to whatever it is currently pointing at links to
               delete temp;
       }
       tail = NULL;
       size = 0;
}

/*
loadMemory opens and reads a line from the the file, loads it into a task object, sends the address of that object to addEntry, and repeats until the end of the file is reached.
*/
void taskList ::loadMemory(const char fileName[])
{
        ifstream inFile;
        char course[101];
        char thisTask[101];
        char due[101];
        task anEntry;

       inFile.open( fileName);
        if (inFile.good() != true)
       {
              cout << "The file " << fileName << " failed to open: "
                     << strerror( errno) //This shows the error if file fails to open.
                     << endl;
               return;
       }

       inFile.get(course, 101, ';');
        while (inFile.eof() != true)
       {
              inFile.get();
              inFile.get(thisTask, 101, ';');
              inFile.get();
              inFile.get(due, 101, '\n');
              inFile.ignore(100, '\n');

              anEntry.setCourse(course);
              anEntry.setTask(thisTask);
              anEntry.setDue(due);

              insertTask(anEntry);

              inFile.get(course, 101, ';');
       }
       inFile.close();
}

/*
insertTask inserts a task before the first matching course that it finds after traversing the list from head.
*/
void taskList ::insertTask(const task &newTask)
{
        char course[101]; //char array to hold "course" after it is read from the task object that was passed in
        char currCourse[101]; //char array to hold the course of each node for comparison
        node *curr, *prev;

        newTask.getCourse(course); //call getCourse to read course from newTask into local char array

       newNode = new node( newTask); //a new node is initialized from the passed in task object, and *newNode now points to it.

       prev = NULL; //prev is set to point to nothing
       curr = head; //curr now points to the same node that head points to


        while (curr != NULL)
       {
              curr->taskInfo.getCourse(currCourse); //Copy course from the node that curr is pointing at into a local char array.
               if (strcmp(course, currCourse) < 0) //If course and currCourse match, break the while loop.
              {
                      break;
              }

              prev = curr; //prev now points to the same node that curr points to
              curr = curr->link; //curr now points to the node the node it was just pointing to was linked to.
       }



       newNode->link = curr; //the new node now links to the node that curr is pointing to


        if (prev == NULL) //if the while loop didn't execute, because head is still null (meaning the list is blank)...
       {
              head = newNode; //head and tail point to the new node
              tail = newNode;
       }
        else //if prev does point to something...
       {
              prev->link = newNode; //prev links to the new node.
       }

       size++;

       prev = NULL;
       curr = head; // *curr now points to the same node that *head does

        while (curr != NULL)
       {
              prev = curr;
              curr = curr->link;
       }

       tail = prev->link; //once curr has traversed the list, prev should point to the node that points to the last item on the list, the tail.
}

/*
searchEntry displays entry matches and returns the number of times that "course" was matched.
*/
int taskList ::searchEntry(const char course[], task &match) const
{
        node *curr; //a node pointer named curr is declared
        char currentCourse[101];
        char currentTask[101];
        char currentDue[101];
        int loopIndex = 0;
        int matchIndex = 1;

        for (curr = head; curr != NULL; curr = curr->link)
       {
              curr->taskInfo.getCourse(currentCourse);
              curr->taskInfo.getTask(currentTask);
              curr->taskInfo.getDue(currentDue);
               while (strcmp( course, currentCourse) == 0)
              {
                      if (loopIndex == 0){
                           cout << endl << "The tasks found for course " << course << " are: " << endl << endl;
                     }

                      match.setTask(currentTask);
                     cout << setw(20) << "Task " << matchIndex << ": " << currentTask;
                      match.setDue(currentDue);
                     cout << setw(20) << "Due: " << currentDue << endl;
                     matchIndex++;
                     loopIndex++;
                      break;
              }
       }
        if (matchIndex == 1){
              cout << endl << endl << "No course matches were found for course " << course << ". "
                     << endl << endl << "You will now be returned to the main menu." << endl << endl;
       }
        if (matchIndex > 1){
              cout << endl << "You will now be returned to the main menu." << endl;
       }
        return matchIndex;
}

/*
printAll prints all tasks into the console window
*/
void taskList ::printAll() const
{
        node *current;
        char course[101];
        char task[101];
        char due[101];

       cout << setw(20) << "COURSE:" << setw(20) << "TASK:" << setw(20) << "DUE:" << endl;
        for (current = head; current != NULL; current = current->link) //first set current to head, then traverse the list until current points to nothing (the last link points to null)
       {
              current->taskInfo.getCourse(course);
              current->taskInfo.getTask(task);
              current->taskInfo.getDue(due);
              cout << setw(20) << course << setw(25) << task << setw(25) << due << endl;
       }
       cout << endl << "You will now be returned to the main menu." << endl << endl;
}

/*
saveAll retreives the task info from each node and writes it to an output file.
*/
void taskList ::saveAll(const char fileName[]) const
{
        ofstream out;
        node *curr;
        char course[101];
        char task[101];
        char due[101];

       out.open( fileName);
        if (out.good() != true)
       {
              cout << "The file " << fileName << "failed to open: "
                     << strerror( errno) //This shows the error if file fails to open.
                     << endl;
               return;
       }

        for (curr = head; curr != NULL; curr = curr->link) //curr is set to head, and as long as curr doesn't contain NULL (like the last node's link does) the list continues
       {
              curr->taskInfo.getCourse(course); //task variables are retreived from the node that curr points to to be printed into the output file
              curr->taskInfo.getTask(task);
              curr->taskInfo.getDue(due);

              out << course << ';' << task << ';' << due << endl;
       }
       out.close();
}
