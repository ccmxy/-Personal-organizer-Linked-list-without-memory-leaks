#ifndef TASK
#define TASK

class task
{
public:
        //constructor
       task();

        //destructor
       ~task();

        //accessor functions
        void getCourse( char name[]) const;
        void getTask( char task[]) const;
        void getDue( char due[]) const;

        //mutator functions
        void setCourse( const char course[]);
        void setTask( const char task[]);
        void setDue( const char due[]);
        int matchesFound( int numberMatches);

private:
        char *course;
        char *thisTask;
        char *due;

};

#endif
