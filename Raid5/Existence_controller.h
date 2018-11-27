//
// Created by aykull on 27/11/18.
//

#ifndef TECMFSSERVER_EXISTENCE_CONTROLLER_H
#define TECMFSSERVER_EXISTENCE_CONTROLLER_H


#include <zconf.h>
#include <pwd.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;
class Existence_controller {
public:
    static bool disk_oneok();
    static bool disk_twook();
    static bool disk_threeok();
    static bool firsttime();

};



#endif //TECMFSSERVER_EXISTENCE_CONTROLLER_H
