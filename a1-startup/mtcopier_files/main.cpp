/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include "writer.h"
#include <cstdlib>
/**
 * these need to be global variables as you'll need handle cleaning them up in
 *cleanup which will automatically be called on program exit
 **/
reader* readers;
writer* writers;
pthread_t* reader_threads;
pthread_t* writer_threads;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void cleanup() {
    /**
     * perform any cleanup you need to do here for global pointers
     **/
    reader::closeFile();
    writer::closeFile();
    delete readers;
    delete writers;
    delete[] reader_threads;
    delete[] writer_threads;
}

int main(int argc, char** argv) {
    atexit(cleanup);
    /**
     * check command line arguments
     **/


    /**
     * process command line arguments
     **/
    std::cout<< "Got the Files"<<std::endl;
    const int NUM_THREADS = static_cast<int>(*argv[1]);
    std::string inFile = argv[2];
    std::string outFile = argv[3];

    /**
     * initiliaze the reader and writer classes
     **/
    reader::setLock(&lock);
    writer::setLock(&lock);


    std::cout<< "Created the classes"<<std::endl;
    readers = new reader(NUM_THREADS, inFile);
    writers = new writer(NUM_THREADS, outFile);


    /**
     * initialize the running of each thread. Note you just call run() on each
     * object here, you'll call pthread_create itself in the run function.
     **/
    std::cout<< "Reader: RUN"<<std::endl;
    reader_threads = readers->run();
    std::cout<< "Writer: RUN"<<std::endl;
    writer_threads = writers->run();

    /**
     *
     * have loop here waiting for the threads to complete. Please see
     * section on avoiding busy waiting on the assignment specification to see
     * what need to be done here.
     * What we have do here is just use a CV to check if the condition
     * that the file is empty and the queue is empty are met and then
     * we are good to continue with the main file.
      **/

    for(int i = 0; i < NUM_THREADS; i++){
        pthread_join(reader_threads[i], NULL);
    }
    
    for(int i = 0; i < NUM_THREADS; i++){
        pthread_join(writer_threads[i], NULL);
    }

    return EXIT_SUCCESS;
}
