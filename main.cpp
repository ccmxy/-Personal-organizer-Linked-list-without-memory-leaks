/*
Name: Colleen Minor
SSID: G02312462
Assignment: Lab 5
Date: March 01, 2014
*/

#include <iostream>
#include <cerrno>


#include "task.h"
#include "taskList.h"


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

void displayMenu();
char readInCommand();
void processCommand(char command, taskList &processList);
void readInEntry(task &anEntry);
void readCourse(char course[]);
void readString(const char prompt[], char inputString[], int maxChar);

int main()
{
       _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

        char command;
        char fileName[] = "tasks.txt";
        taskList list(fileName);
       cout << "Welcome to your virtual task organizer. Choose an option below to get started." << endl << endl;
       displayMenu();
       command = readInCommand();
        while (command != 'q')
       {
              processCommand(command, list);
              displayMenu();
              command = readInCommand();
       }
       list.saveAll(fileName);

       _CrtDumpMemoryLeaks(); //dumps all the memory blocks in the debug heap when a memory leak has occurred
        return 0;
}

/*
displayMenu does exactly that.
*/
void displayMenu()
{
       cout << "\ta: Add a new task, along with its course and due date." << endl
              << "\tl: List all of the data you've entered so far." << endl
              << "\ts: Search a course for a list of task(s) and due date(s)." << endl
              << "\tq: Exit this program and write data to output file." << endl;
        return;
}

/*
readInCommand does exactly that.
*/
char readInCommand()
{
        char   command;

       cout << endl << "Please enter the command (a, l, s, or q): " ;
       cin >> command;
       cin.ignore(100, '\n');
        return tolower(command);
}

/*
processCommand receives the command from main and uses it to choose a switch statement
*/
void processCommand(char command , taskList &processList )
{
        task  entry;
        char course[101];
        char task[101];
        char due[101];

        switch ( command)
       {
        case 'a':
              readInEntry(entry);
               processList.insertTask(entry); //sends entry, just populated by readInEntry, to insertTask.
               break;

        case 'l':
               processList.printAll();
               break;

        case 's':
              readCourse(course);
               processList.searchEntry(course, entry);
               break;

        default: cout << endl << "Command not recognized. You will now be returend to the main menu." << endl;
               break;
       }
}

/*
readInEntry reads from user-input into a task object called entry declared in processCommand.
*/
void readInEntry(task &anEntry )
{
        char course[101];
        char task[101];
        char due[101];

       readString( "Please enter the course: ", course, 101);
       readString( "Please enter the task: ", task, 101);
       readString( "Please enter the due date: ", due, 101);

        anEntry.setCourse(course);
        anEntry.setTask(task);
        anEntry.setDue(due);

       cout << "\nData received. You will now be returned to the main menu. \n" << endl;
}

void readCourse(char course [])
{
       readString( "Enter the name of the course that you wish to search: " , course, 101);
}

/*
readString prompts the user for data and reads into the inputString array that's sent in.
*/
void readString(const char prompt [], char inputString [], int maxChar )
{
        char *myCourse;
       cout << endl << prompt;

       cin.get( inputString, maxChar , '\n' );
       myCourse = new char[strlen( inputString) + 1];
       strcpy(myCourse, inputString);
        while (!cin)
       {
              cin.clear();
              cin.ignore(100, '\n');
              cout << endl << prompt;
              cin.get(myCourse, maxChar, '\n');
       }

       cin.ignore(100, '\n');
}
