/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "Reader.h"
#include "Writer.h"
#include <cstdlib>

/* global variables if needed go here */
int main(int argc, char** argv) {
    /* check command line arguments */
    std::string inFilePath = argv[1];
    std::string outFilePath = argv[2];

    Writer writer(outFilePath);
    Reader reader(inFilePath, writer);

    reader.run();
    writer.run();

    return EXIT_SUCCESS;
}
