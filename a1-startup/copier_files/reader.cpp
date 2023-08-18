/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "Reader.h"

Reader::Reader(const std::string& inFilePath, Writer& writer) : 
inPath(inFilePath),
thewriter(writer)
{
}

void Reader::run(){
    in.open(inPath);
    if(in.is_open()){
        std::string line;
        while(getline(in, line)){
            thewriter.append(line);
        }
        in.close();
    }
}
