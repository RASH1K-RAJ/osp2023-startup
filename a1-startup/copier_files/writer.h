/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#ifndef WRITER
#define WRITER

#include <fstream>
#include <iostream>
#include <string>
#include <deque>
#include <iostream>

class Writer {
   public:
    /**
     * creates the writer instance that writes out to the file
     **/
    Writer(const std::string& name);
    /**
     * does the actual writing
     **/
    void run();
    /**
     * appends a line from the file read in to be output ... needed by the
     * reader class
     **/
    void append(const std::string& line);

   private:
    std::string outPath;
    std::ofstream out;
    std::deque<std::string> queue;
};
#endif
