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
#include "SimpleList/SimpleList.cpp"


using namespace std;




struct dataSocket{
    int descriptor;
    sockaddr_in info;
};

class SocketServer {
public:

    SocketServer(){};

    void run(){
        if(!crearSocket())
            throw string("Error al crear el socket");
        if(!ligarKernel())
            throw string("Error al ligar kernel");
        cout<<"Se a iniciado el servidor"<<endl;
        while(true){
            cout<<"Esperando cliente..."<<endl;
            dataSocket data;
            socklen_t tam = sizeof(data.info);
            data.descriptor = accept(descriptor,(sockaddr *) &data.info,&tam);
            cout<<"Se conecto un cliente"<<endl;
            if(data.descriptor < 0){
                cout<<"Error al aceptar el cliente"<<endl;
            }else{
                clientes.push_back(data.descriptor);
                string mensaje = controladorCliente((void *) &data);

                Json::Value root;
                Json::Reader reader;
                reader.parse(mensaje, root);

                string instruccion = root["Solicitud"].asString();
                cout << "Solicitud: " << instruccion << endl;
                cout<<"Se recibio el mensaje: "<<mensaje<<endl;

                procesarInstruccion(root);

                cout<<endl;

            }
        }
        close(descriptor);
    }


    void procesarInstruccion(Json::Value json){
        string instruccion = json["Solicitud"].asString();
        if(instruccion == "pedirDato"){
            string strId = json["id"].asString();
            int numId = atoi(strId.c_str());//con esta variable buscamos el dato solicitado

            //Aqui se debe llamar a las funcion que busca el dato mediante
            //el id (numId) que se recibio del cliente

            int dato = pedirDato(numId);//Aqui debe ir el dato que se encuentre en el id solicitado
            Json::Value root;
            string strID = std::to_string(dato);
            string text = "{ \"Dato\": " + strID + "}";

            Json::Reader reader;
            reader.parse(text, root);

            Json::FastWriter fastWriter;
            std::string output = fastWriter.write(root);
            cout <<"Respondiendo con el mensaje: "<< output << endl;

            setMensaje(output.c_str());

            cout<<endl;
            cout<<endl;

        }else if(instruccion == "recerbarMemoria"){
            string strTam = json["tam"].asString();
            int numTam = atoi(strTam.c_str());

            //Aqui es donde se debe llamar a la funcion que hace el malloc y
            //lo hacemos del tamaño de numTam
            bool exito;

            exito = reservarMemoria(numTam);

            string text;
            //verificamos y si se pudo recerbar la memoria respondemos
            if(exito) {
                text = "Exito";
            }else {
                //Y si no respondemos
                text = "Error";
            }

            cout <<"Respondiendo con el mensaje: "<< text << endl;

            setMensaje(text.c_str());

            cout<<endl;
            cout<<endl;

        }else if(instruccion == "recerbarEspacio") {
            string strTam = json["tam"].asString();
            int numTam = atoi(strTam.c_str());
            numTam -= 10;//Esto es porque hay que restarle dies para obtener el
            //verdadero tamaño solicitado
            cout<<numTam<<endl;

            //Aqui se debe llamar a la funcion que busque un espacio de tamaño
            //numTam en el mapa de momoria o donde sea que se busque dentro de
            //la memoria reservada y lo agregue al mapa de memoria y reserve la
            //memoria y nos devuelva el id donde quedo guardado y se lo asigne
            //a la siguiente variable
            int id = reservarEspacio();//si no se pudo reservar la memoria para el MPointer entonces
            //devuelve cero y si se pudo devuelve los id de 1 en adelante


            string strId = std::to_string(id);
            Json::Value root;
            string text = "{ \"Id\": " + strId + "}";

            Json::Reader reader;
            reader.parse(text, root);

            Json::FastWriter fastWriter;
            std::string output = fastWriter.write(root);
            cout << output << endl;

            cout << "Respondiendo con el mensaje: " << text << endl;

            setMensaje(output.c_str());

            cout << endl;
            cout << endl;
        }else if(instruccion == "actualizarDato"){
            string strId = json["id"].asString();
            int numId = atoi(strId.c_str());//con esta variable buscamos el espacio a actualizar

            string strDato = json["dato"].asString();
            int numDato = atoi(strDato.c_str());//reemplazamos el dato que se encuentra
            //en el id buscado por numDato

            bool exito = actualizarDato(numDato,numId);

            //Aqui se debe llamar a las funcion que recibe como parametro el id y el dato
            // busca el campo mediante el id (numId) y lo actualiza con numDato

            string text;
            if(exito) {
                //verificamos y si se pudo actualizar el dato respondemos
                text = "Exito";
            }else {
                //Y si no respondemos
                text = "Error";
            }

            cout <<"Respondiendo con el mensaje: "<< text << endl;

            setMensaje(text.c_str());

            cout<<endl;
            cout<<endl;
        }else if(instruccion == "liberarEspacio"){
            string strIdElim = json["idElim"].asString();
            int numIdElim = atoi(strIdElim.c_str());//con esta variable buscamos el espacio a liberar

            string strIdAum = json["idElim"].asString();
            int numIdAum = atoi(strIdAum.c_str());//y con esta aumentamos las referencias a este id

            bool exito = liberarEspacio(numIdElim,numIdAum);

            string text;
            if(exito) {
                //verificamos y si la accion se realizo correctamente respondemos
                text = "Exito";
            }else {
                //Y si no respondemos
                text = "Error";
            }

            cout <<"Respondiendo con el mensaje: "<< text << endl;

            setMensaje(text.c_str());

            cout<<endl;
            cout<<endl;
        }else if(instruccion == "liberarMemoria"){

            //Aqui es donde se debe llamar a la funcion que hace el malloc y
            //lo hacemos del tamaño de numTam

            bool exito = liberarMemoria();

            string text;
            if(exito) {
                //verificamos y si se pudo recerbar la memoria respondemos
                text = "Exito";
            }else {
                //Y si no respondemos
                text = "Error";
            }

            cout <<"Respondiendo con el mensaje: "<< text << endl;

            setMensaje(text.c_str());

            cout<<endl;
            cout<<endl;

        }
    }



    void setMensaje(const char *msn){
        for(int i = 0; i < clientes.size();i++){
            cout<<"bytes enviados "<<send(clientes[i],msn,strlen(msn),0)<<endl;
        }
        clientes.clear();
    };

private:
    int descriptor;
    sockaddr_in info;
    vector<int> clientes;
    //-----------------------------------------------------------------
    int* ptr = NULL;
    SimpleList list = NULL;
    int tamMax = 0;

    bool reservarMemoria(int tam){
        if(ptr == NULL){
            ptr = (int*)malloc(tam);
            tamMax = (tam/4);
            return true;
        }else{
            return false;
        }
    }

    bool liberarMemoria(){
        if(ptr != NULL){
            free(ptr);
            ptr = NULL;
            list = NULL;
            return true;
        }else{
            return false;
        }
    }

    int reservarEspacio(){
        int id = addEspacio<int>(list,tamMax);
        return id;
        //si id = 0 entoncs no hay memoria
    }

    bool actualizarDato(int dato, int id){
        int pos = searchDato<int>(list, id);
        if(pos == -1){
            return false;
        }else{
            ptr[pos] = dato;
            return true;
        }
    }

    int pedirDato(int id){
        int pos = searchDato<int>(list,id);
        if(pos == -1){
            return NULL;
        }else{
            return ptr[pos];
        }
    }

    bool liberarEspacio(int idElim, int idAum){
        amentarReferencia<int>(list,idAum);
        int posicionElim = deleteSL<int>(list,idElim);
        if(posicionElim == -1){
            return true;
        }else if(posicionElim == -2){
            return false;
        }else{
            int maximo = list->size;
            while(posicionElim < (maximo-1)){
                ptr[posicionElim] = ptr[posicionElim+1];
                posicionElim++;
            }
            return true;
        }
    }

    //-----------------------------------------------------------------

    bool crearSocket(){
        descriptor = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        if(descriptor < 0)
            return false;
        info.sin_family = AF_INET;
        info.sin_addr.s_addr = INADDR_ANY;
        info.sin_port = htons(4050);
        memset(&info.sin_zero,0, sizeof(info.sin_zero));
        return true;

    };
    bool ligarKernel(){
        if((bind(descriptor,(sockaddr *)&info,(socklen_t) sizeof(info))) < 0)
            return false;

        listen(descriptor,10);
        return true;
    };

    string controladorCliente(void * obj){
        dataSocket *data = (dataSocket *)obj;
        while(true) {
            string mensaje;
            while (1) {
                char buffer[10];
                int bytes = recv(data->descriptor, buffer, 10, 0);
                mensaje.append(buffer, bytes);
                /*
                if(bytes <= 0){
                    close(data->descriptor);
                }
                 */
                if (bytes < 10)
                    break;
            }
            return mensaje;
        }
        //close(data->descriptor);
    };

};








//-----------------------------------------------------------------------




SocketServer *server;

void * serverRun(void *){
    try {
        server->run();
    } catch(string ex){
        cout<<ex<<endl;
    }
    //pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    /*server = new SocketServer;
    serverRun(NULL);

    delete server;*/

    

    return 0;
}

