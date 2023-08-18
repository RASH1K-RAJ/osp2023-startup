/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#ifndef READER
#define READER

#include "Writer.h"
#include <fstream>
#include <iostream>
#include <string>
class Reader {
   public:
    /* create a reader that reads each line of the file and appends it to the
     * writer's queue
     */
    Reader(const std::string& inFilePath, Writer& writer);

    /* perform the reading from the file */
    void run();

   private:
    std::string inPath;
    std::ifstream in;
    Writer& thewriter;
};
#endif
