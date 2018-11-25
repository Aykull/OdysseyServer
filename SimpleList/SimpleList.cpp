//
// Created by aykull on 25/11/18.
//

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <pthread.h>
#include <vector>
#include <unistd.h>

#include <jsoncpp/json/json.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


struct Node{
    int posicion;
    int referencias = 0;
    int id;
    int idMax;
    int size;
    int tamMax;
    struct Node *next;
};

typedef struct Node *SimpleList;

template<typename T>
void mostrarLista(SimpleList &list) {
    int i = 0;
    if(list == NULL) {
        cout << "Lista Vacia!!"<<endl;
    }else{
        while (list != NULL) {
            cout << ' ' << i + 1 << ") " << "id:" << list->id << " , direccion guarda:" << list->posicion
                 << " , referencias:" << list->referencias << endl;
            list = list->next;
            i++;
        }
    }
}

template <typename T>
int deleteSL(SimpleList &list, int id) {
    SimpleList l1,l2,l3;
    l1 = list;
    int posElim;

    if(list!=NULL) {
        while(l1!=NULL) {
            if(l1->id == id) {
                if (l1->referencias == 1) {
                    posElim = l1->posicion;
                    l3 = l1->next;
                    while(l3 == NULL){
                        l3->posicion--;
                        l3 = l3->next;
                    }
                    //cout<<"OKY"<<endl;
                    if (l1 == list) {
                        (list->next)->size = (list->size)-1;
                        (list->next)->idMax = (list->idMax);
                        list = list->next;
                    }else{
                        l2->next = l1->next;
                    }
                    return posElim;

                }else{
                    //cout<<"OKYDOKY"<<endl;
                    l1->referencias--;
                    return -1;
                }

            }
            l2 = l1;
            l1 = l1->next;
        }
        cout<<"El dato que se desea eliminar no existe"<<endl;
        return -2;
    } else {
        cout << " Lista vacia..!";
        return -2;
    }
}

template<typename T>
int addEspacio(SimpleList &list, int tamMaximo){
    SimpleList l1, l2 = new(struct Node);

    l2->tamMax = tamMaximo;
    l2->next = NULL;

    if(list==NULL){
        list = l2;
        list->id = 1;
        list->referencias=1;
        list->idMax = 1;
        list->size++;
        list->posicion = 0;
        return 1;
    }
    else{
        int indice = 2;
        l1 = list;
        while(l1->next!=NULL){
            l1 = l1->next;
            indice++;
        }
        if(l1->tamMax > indice) {
            //cout<<"Si entramos3"<<endl;
            l2->referencias++;
            l1->next = l2;
            l2->posicion = (l1->posicion)+1;
            list->idMax++;
            l2->id = list->idMax;
            list->size++;
            return l2->id;
        }else{
            //cout<<"Si entramos4"<<endl;
            return 0;
        }

    }
}

template<typename T>
void amentarReferencia(SimpleList &list, int id){

    SimpleList l1 = new(struct Node);

    if(list==NULL){
        cout<<"lista vacia"<<endl;
    }
    else{
        l1 = list;
        while(l1!=NULL){
            if(l1->id == id){
                //cout<<"Si entramos"<<endl;
                l1->referencias++;
                return;
            }else {
                l1 = l1->next;
            }
        }
        cout<<"No existe la posicion a la que se le desea aumentar referencias"<<endl;
    }
}

template <class T>
int searchDato(SimpleList list, int id) {
    SimpleList l1 = list;

    while(l1!=NULL) {
        if(l1->id == id) {
            return l1->posicion;
        }else {
            l1 = l1->next;
        }
    }
    return -1;
}
