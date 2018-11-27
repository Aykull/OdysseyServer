//
// Created by aykull on 27/11/18.
//

#include "GOD_controller.h"
#include <dirent.h>
#include "Existence_controller.h"
#include "file_controller.h"

long GOD_controller::size = 0;

void GOD_controller::check() {

    bool is_1_ok= Existence_controller::disk_oneok();
    bool is_2_ok = Existence_controller::disk_twook();
    bool  is_3_ok = Existence_controller::disk_threeok();
    if(is_1_ok==false&&is_2_ok==false&&is_3_ok==false){
        cout<<"MEMEMEMEME"<<endl;
        return file_controller::create_disks();
    }
    if(is_1_ok== false){
        cout<<"Senor stark no me siento bien : 1"<<endl;
        file_controller::create_1_disk(1);
        reconstruct_disk(1);
        return;
    }
    if(is_2_ok==false){
        cout<<"Senor stark no me siento bien : 2"<<endl;
        file_controller::create_1_disk(2);
        reconstruct_disk(2);
        return;
    }
    if(is_3_ok==false){
        cout<<"Senor stark no me siento bien : 3"<<endl;

        file_controller::create_1_disk(3);

        reconstruct_disk(3);
        return;
    }
    else{
        cout<<"LELE no se cayo nada"<<endl;
    }

}
void GOD_controller::reconstruct_disk(int failure) {
    string * directory;
    if(failure!= 3){
        directory = file_controller::filepath(3);
    }
    else{
        directory = file_controller::filepath(1);
    }
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (directory->c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            char* cosa = ent->d_name;
            cout<<cosa<<endl;
            if(failure==3){
                file_controller::createfile3(cosa);
            }
            else{
                cout<<"________________RECONS____________"<<endl;
                file_controller::Recontruct_file(cosa,failure);
            }

        }
        closedir (dir);
    }

}
void GOD_controller::saveFile(char *file, char *filename, long size) {
    check();
    file_controller::save_file(file,filename,size);
}
char* GOD_controller::get_file(string filename) {
    check();

    return file_controller::getfile(filename);
}
void GOD_controller::editfilename(char *file_anterior, char *filename_nuevo) {
    check();

    file_controller::rename_file(file_anterior,filename_nuevo);
}
void GOD_controller::deletefile(char *filename) {
    check();
    file_controller::borrar(filename);
}