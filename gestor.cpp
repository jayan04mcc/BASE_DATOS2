#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>

#define PAG_SIZE 4096 //tamanio maximo por pagina(bloque)
int contador=0;
class Pagina {
public:
  
    int NroPag;
    int PosPag;
    char* contenido= new char[PAG_SIZE];
    Pagina* siguiente;
    Pagina* anterior;

    Pagina(int NroPag) {
        this->PosPag =PosPag;
        this->NroPag = NroPag;
        this->siguiente = nullptr;
        this->anterior = nullptr;
    }

};

class Gestor { // seria como nuestra lista enlazada
private:
    Pagina* Head;
    Pagina* Tail;
    int  NroPaginas;
public:
    
	Gestor(int NroPaginas) {
        this->Head = nullptr;
        this->Tail = nullptr;
        this->NroPaginas = NroPaginas;
	}
    void InsertarBloque_prueba(int NroPagActual,std::ifstream& archivo) {
        if (NroPaginas < NroPagActual) {
            exit(0);
        }
        else {
            auto NewPagina = new Pagina(NroPagActual);
            NewPagina->siguiente = this->Head;
            archivo.seekg(0, std::ios::end);
            std::streampos tamano = archivo.tellg();// sacamos el tamanio
            archivo.seekg(0, std::ios::beg);
            archivo.read(NewPagina->contenido, tamano);//escribimos en el bloque que queramos)
            Head = NewPagina;
        }

    }
    void LeerBloque(int NroPagActual,std::ifstream& archivo){// creamos un bloque y le asignamos un txt
        Pagina* NewPagina= new Pagina(NroPagActual);
        archivo.seekg(0, std::ios::end);
        std::streampos tamano = archivo.tellg();
        archivo.seekg(0, std::ios::beg);
        archivo.read(NewPagina->contenido, tamano);
        
        if(this->Head==nullptr){
            this->Head = NewPagina;
            this->Tail = NewPagina;
            NewPagina->PosPag=contador;
            contador++;
        }
        else{
        Pagina* recorredor=this->Head;
        while(recorredor->siguiente!=nullptr){
            recorredor=recorredor->siguiente;
            contador++;
        }
        NewPagina->PosPag=contador;
        recorredor->siguiente=NewPagina;
        NewPagina->anterior=recorredor;
        Tail=NewPagina;
        }
        

    }
    void escribirBloque(int NroPag,char* contenidoNuevo) {
 
        std::size_t longitud = std::strlen(contenidoNuevo);
        while (longitud < PAG_SIZE) {
         
            auto corredor = Head;
            while (corredor->NroPag != NroPag) {
                corredor = corredor->siguiente;
            }
            if (corredor->contenido == nullptr) {
                strcpy(corredor->contenido, contenidoNuevo);//si es la primera vez
            }
            strcat(corredor->contenido, contenidoNuevo);// le asignamos nuevo contenido
            
        }
    }
    void leerPrimerBloque(){
        if(this->Head==nullptr){
            return ;
        }
        auto primerBloque=Head;
        std::cout<<primerBloque->contenido<<std::endl;
    }
    void leerUltimoBloque(){
        if(this->Head==nullptr){
            return ;
        }
        auto ultimoBloque=Tail;
        std::cout<<ultimoBloque->contenido<<std::endl;
    }
    void GetPosBloque(){
        auto aux = Head;
        while (aux != nullptr) {
            aux=aux->siguiente;
        } 
        std::cout << aux->PosPag << std::endl;
    }
    void leerBloqueActual(int num){
        int PAGINA_ACTUAL= num;
         auto corredor = Head;
        while(corredor->NroPag != num){
            corredor = corredor->siguiente;
        }
       std::cout<<corredor->contenido<<std::endl;
    }
    void leerBloqueSiguiente(){
        
    }
    void leerBloqueAnterior(){

    }
    void agregarBloqueVacio(int NroPagActual){
        Pagina* NewPagina= new Pagina(NroPagActual);
        
        if(this->Head==nullptr){
            this->Head = NewPagina;
            this->Tail = NewPagina;
            NewPagina->PosPag=contador;
            contador++;
        }
        else{
        Pagina* recorredor=this->Head;
        while(recorredor->siguiente!=nullptr){
            recorredor=recorredor->siguiente;
            contador++;
        }
        NewPagina->PosPag=contador;
        recorredor->siguiente=NewPagina;
        strcpy(NewPagina->contenido,"\0");
        NewPagina->anterior=recorredor;
        Tail=NewPagina;
        }

    }
    
    void test_nropag() {
        auto aux = Head;
        while (aux != nullptr) {
            std::cout << aux->NroPag << std::endl;
            aux=aux->siguiente;
        } 
    }
};



int main() {
    std::ifstream archivo("textoprueba.txt");
    std::ifstream archivo2("text2.txt");
    std::ifstream archivo3("text3.txt");
    char* nuevocontent = new char[20];
    strcpy(nuevocontent,"textonuevo");
    int numero_de_paginas_totales = 20;
    Gestor prueba(numero_de_paginas_totales);
    prueba.LeerBloque(1, archivo);
    prueba.LeerBloque(2, archivo2);
    prueba.LeerBloque(3, archivo3);
    prueba.agregarBloqueVacio(4);
    prueba.leerBloqueActual(2);
    //prueba.leerBloque(2);
    //prueba.leerUltimoBloque();
    //prueba.escribirBloque(1,nuevocontent);
    //prueba.busqueda_nropag(3);
    return 0;
    //nueva tarea insertar
    //leer archivo csv  y 
}
