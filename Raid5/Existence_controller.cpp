//
// Created by aykull on 27/11/18.
//

#include <dirent.h>
#include "Existence_controller.h"

bool Existence_controller::disk_oneok() {
    struct passwd *pw = getpwuid(getuid());
    string homedirectory = pw->pw_dir;
    homedirectory.append("/Disk 1");
    DIR *pDir;
    cout<<homedirectory<<endl;

    bool bExists = false;

    pDir = opendir (homedirectory.c_str());

    if (pDir != NULL)
    {
        bExists = true;
        (void) closedir (pDir);
    }

    return bExists;
};
bool Existence_controller::disk_threeok() {    struct passwd *pw = getpwuid(getuid());
    string homedirectory = pw->pw_dir;
    homedirectory.append("/Disk 3");

    DIR *pDir;
    bool bExists = false;
    cout<<homedirectory<<endl;

    pDir = opendir (homedirectory.c_str());

    if (pDir != NULL)
    {
        bExists = true;
        (void) closedir (pDir);
    }

    return bExists;

};
bool Existence_controller::disk_twook() {    struct passwd *pw = getpwuid(getuid());
    string homedirectory = pw->pw_dir;
    homedirectory.append("/Disk 2");
    DIR *pDir;
    bool bExists = false;
    cout<<homedirectory<<endl;
    pDir = opendir (homedirectory.c_str());

    if (pDir != NULL)
    {
        bExists = true;
        (void) closedir (pDir);
    }

    return bExists;

};
bool Existence_controller::firsttime() {
    struct passwd *pw = getpwuid(getuid());
    string homedirectory = pw->pw_dir;
    homedirectory.append("/Disk 1");
    string homedirectory2 = pw->pw_dir;
    homedirectory2.append("/Disk 2");
    string homedirectory3 = pw->pw_dir;
    homedirectory3.append("/Disk 3");
    DIR * pDir1,*pDir2,*pDir3;
    pDir1 = opendir (homedirectory.c_str());
    pDir2 = opendir(homedirectory2.c_str());
    pDir3 = opendir(homedirectory3.c_str());
    bool existe = false;
    if(pDir1 != NULL&& pDir2!=NULL&&pDir3!=NULL)
    {
        existe = true;
        (void) closedir (pDir1);
        (void) closedir (pDir2);
        (void) closedir (pDir3);
    }
    return existe;

}
