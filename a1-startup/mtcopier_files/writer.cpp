/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "writer.h"
#include "reader.h" //Check for cyclic condition

/**Defining static variables*/
std::deque<std::string> writer::queue;
std::ofstream writer::out;
pthread_mutex_t* writer::lock;
/**
 * implement these functions requred for the writer class
 **/
writer::writer(int NUM_THREADS, std::string outFile):
NUM_THREADS(NUM_THREADS),
outFile(outFile)
{}

void writer::setLock(pthread_mutex_t* uniLock){
    lock = uniLock;
}

void writer::init(const std::string& outFile){
    out.open(outFile, std::ios::out);
}

pthread_t* writer::run(){
    init(outFile);
    pthread_t* threads = new pthread_t[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++){
        pthread_create(&threads[i], NULL, runner, NULL);
    }
    return threads;
}

bool writer::isQueueEmpty(){
    return queue.empty();
}
void writer::closeFile(){
    out.close();
}

void* writer::runner(void* arg) { 
    std::cout<< "Writer: runner()"<<std::endl; //DELETE !!!!
    bool cond;
    do{
        pthread_mutex_lock(lock);
        cond = isQueueEmpty();
        std::cout <<"Value of cond: " << cond <<std::endl;
        if(cond){
            /**If file isn't empty then change status to true*/
            if(!reader::getFileStatus()){
                /**Checkout if we need to use conditional variable
                 * here or not.
                */
                cond = true;
            }
        }else{
            std::cout<<"Wrote: "<<queue.front()<<std::endl;
            std::string tmp = queue.front();
            queue.pop_front();
            if(isQueueEmpty() && reader::getFileStatus())
            {
                out << tmp;

            }else{
                out << tmp << std::endl;
            }
        }
        pthread_mutex_unlock(lock);
    }while(!cond);

    pthread_exit(NULL);
}

writer::~writer(){

}

void writer::append(const std::string& line){
    queue.push_back(line);
}
