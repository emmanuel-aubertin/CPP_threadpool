/***************************************************************************************/
/*----- Auteur :        Aubertin Emmanuel               |  For: Programation para   ****/
/*----- Description :   Thread Pool                                                 ****/
/*----- Contact :       https://athomisos.fr                                        ****/
/***************************************************************************************/

#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include "threadPool/threadPool.hpp"
#include <CoreFoundation/CoreFoundation.h>
#include <AudioToolbox/AudioToolbox.h>

using namespace std;

std::string PROGNAME="Thread Pool";
std::string FILE_NAME= __FILE__;
std::string RELEASE="Revision 1.0 | Last update 29 december 2021";
std::string AUTHOR="\033[1mAubertin Emmanuel\033[0m";
std::string COPYRIGHT="(c) 2021 "+ AUTHOR + " from https://athomisos.fr";
bool VERBOSE = false;


void print_release() {
    std::cout << RELEASE << endl << COPYRIGHT << endl;
}


void print_usage() {
        std::cout << endl 
        << PROGNAME << " by " << AUTHOR <<endl 
        << "\033[1mUsage: \033[0m"<< FILE_NAME <<" | [-h | --help] | [-v | --version] | [-V | --verbose] | filename" << endl
        << "          -h        help" << endl
        << "          -v        Version" << endl
        << "          -v        Verbose" << endl;
}


void print_help() {
        print_release();
        std::cout << endl;
        print_usage();
        std::cout << endl << endl;
        exit(0);
}


void failure(std::string message){
    std::cerr << "❌ \033[1;31m Error :\033[0m " << message << " ❌" << endl;
    exit(-1);
}

int main(int argc,char** argv){
    if(argc < 0)
		failure("One argument required. \n\t-h for help");
    cout << "Welcome to " << PROGNAME << "." << endl;
    print_release();
    for(int i = 1; i < argc; i++){
        if (!strcmp(argv[i] , "-h") || !strcmp(argv[i] , "--help")){
            print_usage();
            exit(0);
        } else if (!strcmp(argv[i] , "-v") || !strcmp(argv[i] , "--version")){
            print_release();
            exit(0);
         } else if (!strcmp(argv[i] , "-V") || !strcmp(argv[i] , "--verbose")){
            std::cout << "✌  |Welcome in \033[1mVERBOSE\033[0m mode| ✌ " << endl;
            VERBOSE = true;
        } else { // ALL OTHER ARGUMENT
            print_usage();
            std::string err = "Unknow argument : " + *argv[i];
            failure(err);
        }
    }

    // ---------------------------------------------------------------- //
    // Begining of TP2                                                  //
    // ---------------------------------------------------------------- //

    uint32_t thread_local_var = 100;
    ThreadPool* test = new ThreadPool(thread_local_var);

    for(uint32_t i=0; i < thread_local_var; i ++){
        test->addJob([] {
            cout << "Oh my big zob !" << endl;
            return;
         });
    }

    test->start();
    while(test->isPoolBusy()){/* wait for end of pool */}
    test->stop();

    return 0;
    }
