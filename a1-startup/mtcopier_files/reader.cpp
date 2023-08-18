/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include "writer.h"

/**Defining static variables*/
std::ifstream reader::in;
pthread_mutex_t* reader::lock;

/**
 * implement the functions needed for this class
 **/
reader::reader(int NUM_THREADS, std::string inFile):
NUM_THREADS(NUM_THREADS),
inFile(inFile)
{   
}

reader::~reader(){

};

void reader::setLock(pthread_mutex_t* uniLock){
    lock = uniLock;
}

void reader::init(const std::string& inFile) {
    in.open(inFile);
}

pthread_t* reader::run() {
    init(inFile);
    std::cout<< "Created Threads for Reader"<<std::endl;
    pthread_t* threads = new pthread_t[NUM_THREADS]; //remember to delete this.

    for(int i = 0; i < NUM_THREADS; i++){

        pthread_create(&threads[i], NULL, runner, NULL);
    }
    std::cout<< "Returned Threads for Reader"<<std::endl;
    //in.close();  //close it in the main.cp
    return threads;
}

void reader::isFileEmpty(std::string* line, bool& cond){
    cond = (bool)getline(in, *line);
}

void reader::closeFile(){
    in.close();
}

/**Lets the writer class access if the file is empty or not*/
bool reader::getFileStatus(){
    return (in.peek() == std::ifstream::traits_type::eof());
}

void* reader::runner(void* arg) {
    std::string line;
    bool cond = true;
    std::cout<< "Reader: runner()"<<std::endl; //DELETE !!!!
    //Critical Section
    do{
        pthread_mutex_lock(lock);
        isFileEmpty(&line, cond);
        if(cond){
            std::cout<<"Read: "<<line<<std::endl;
            writer::append(line);
        }
        pthread_mutex_unlock(lock);
    }while(cond);

    pthread_exit(NULL); 
}