/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#ifndef WRITER
#define WRITER

#include <pthread.h>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>

class reader;

class writer {
   public:
    /**
     * Please note that methods and data need to be static as there's a
     * variety of information that needs to be coordinated between writers
     * such as locks and other shared data. Also, as the pthread library
     * is a c library, it does not know about classes so ruuner in particular
     * needs to be static. You can pass in instances into the function as
     * pointers though.
     **/
    writer(int NUM_THREADS, std::string outFile);
    ~writer();
    static void init(const std::string& outFile);
    static void* runner(void*);
    pthread_t*  run();
    static void append(const std::string& line);
    static void setLock(pthread_mutex_t* uniLock);
    static void closeFile();
    static bool isQueueEmpty();

   private:
    static pthread_mutex_t* lock;
    int NUM_THREADS;
    const std::string outFile;
    static std::ofstream out;
    static std::deque<std::string> queue;
};
#endif
