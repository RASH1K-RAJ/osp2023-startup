/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/

#include "Writer.h"

/**
 * provide your implementation for the writer functions here
 **/
Writer::Writer(const std::string& outFilePath) :
outPath(outFilePath)
{

}

void Writer::run(){
    out.open(outPath);
    std::deque<std::string>::iterator it = queue.begin();
    if(out.is_open()){
        while(it != queue.end()){
            if(it == --queue.end()){
                out << *it;
            }else{
                out << *it << std::endl;
            }
            ++it;
        }
        out.close();
    }
}

void Writer::append(const std::string& line) {
        queue.push_back(line);
}
