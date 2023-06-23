#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>

#define PAG_SIZE 10 //tamanio maximo por pagina(bloque)
class Pagina{

    public:
  
    int NroPag;
    int PosPag;
    char* contenido;
    Pagina* siguiente;
    Pagina* anterior;

    Pagina(int NroPag) {
        this->PosPag =PosPag;
        this->NroPag = NroPag;
        this->contenido =new char[PAG_SIZE];
        this->siguiente = nullptr;
        this->anterior = nullptr;
    }
};
class gestor{
private:
    Pagina* Head;
    Pagina* Tail;
    int nroPagina;
    std::ifstream archivo;
public:
    gestor(int nroPag,const std::string& nombreArchivo){
        this->nroPagina = nroPagina;
        this->Head = nullptr;
        this->Tail = nullptr;
        archivo.open(nombreArchivo);  // Abre el archivo en modo de lectura
           if (!archivo) {
            throw std::runtime_error("No se pudo abrir el archivo: " + nombreArchivo);
        }

    }
    void iniciarGestor();
    void leerBloque(int);
    void agregarBloqueVacio(int);
    void leernropag();
    void leer2();
};
void gestor::iniciarGestor() {

    archivo.seekg(0, std::ios::end);
    std::streampos fileSize = archivo.tellg();
    archivo.seekg(0, std::ios::beg);

    int currentPositionInt = static_cast<int>(fileSize);

    int numBlocks = (currentPositionInt + PAG_SIZE - 1) / PAG_SIZE;

    // Limpiar la lista existente
    if (Head != nullptr) {
        Pagina* recorredor = Head;
        Pagina* nodoSiguiente;
        while (recorredor != nullptr) {
            nodoSiguiente = recorredor->siguiente;
            delete[] recorredor->contenido; // Liberar la memoria asignada para el contenido
            delete recorredor; // Liberar el nodo
            recorredor = nodoSiguiente;
        }
        Head = nullptr;
        Tail = nullptr;
    }

    // Leer y almacenar cada bloque
    for (int i = 0; i < numBlocks; ++i) {
        char* block = new char[PAG_SIZE];
        archivo.read(block, PAG_SIZE);

        Pagina* nuevaPagina = new Pagina(i);
        nuevaPagina->contenido = block;

        if (Head == nullptr) {
            Head = nuevaPagina;
            Tail = nuevaPagina;
        } else {
            nuevaPagina->anterior = Tail;
            Tail->siguiente = nuevaPagina;
            Tail = nuevaPagina;
        }
    }

    // Cerrar el archivo
    archivo.close();
}


void gestor::leer2(){
     archivo.seekg(0, std::ios::end);
    std::streampos fileSize = archivo.tellg();
    archivo.seekg(0, std::ios::beg);
    
    int currentPositionInt = static_cast<int>(fileSize);
    //int blockSize = 1024; // 1 KB (actualizado el valor del tamaño de bloque a 1024)

    // Calcular la cantidad de bloques necesarios
    int numBlocks = (currentPositionInt + PAG_SIZE - 1) / PAG_SIZE;

    Pagina* NewPagina;
       
        this->Head = NewPagina;
        this->Tail = NewPagina;
            //NewPagina->PosPag=contador;
            //contador++;
        Pagina* recorredor=this->Head;

        while(recorredor->siguiente!=nullptr){
            recorredor=recorredor->siguiente;
            //contador++;
        }
        //NewPagina->PosPag=contador;
        recorredor->siguiente=NewPagina;
        NewPagina->anterior=recorredor;
        Tail=NewPagina;
        for (int i = 0; i < numBlocks; ++i) {
        char* block = new char[PAG_SIZE];
        archivo.read(block, PAG_SIZE);

        Pagina* nuevaPagina = new Pagina(i);
        nuevaPagina->contenido = block;
        nuevaPagina->anterior = Tail;
        Tail = nuevaPagina;
    }

}
void gestor::leernropag(){
    auto aux=this->Head;
    while(aux!=nullptr){
        std::cout << aux->NroPag<<std::endl;
        aux = aux->siguiente;
    }
}
void gestor::agregarBloqueVacio(int nroPag){
    if(nroPag>nroPagina){
        return;
    }
    auto new_pagina= new Pagina(nroPag);
    std::fill(new_pagina->contenido, new_pagina->contenido + PAG_SIZE, '\0');//contenido vacio
        Pagina* recorredor=this->Head;
        while(recorredor->siguiente!=nullptr){
            recorredor=recorredor->siguiente;
        }
        recorredor->siguiente=new_pagina;
        new_pagina->anterior=recorredor;
        this->Tail=new_pagina;
    
};
void gestor::leerBloque(int numPag){
    std::ifstream inputFile("textoprueba.txt", std::ios::in | std::ios::binary);
    if (!inputFile) {
        std::cout << "Error al abrir el archivo." << std::endl;
        return ;
    }

    // Obtener el tamaño total del archivo
    inputFile.seekg(0, std::ios::end);
    std::streampos fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);
    
    int currentPositionInt = static_cast<int>(fileSize);
    
    int blockSize = 10; // 1 KB

    int numBlocks = (currentPositionInt + blockSize - 1)/ blockSize;
    
    // Crear un vector para almacenar el bloque actual
    std::vector<char> block(blockSize);

    // Leer y procesar cada bloque
    for (int i = 0; i < numBlocks; ++i) {
        // Leer el bloque actual
        inputFile.read(block.data(), blockSize);

        // Determinar la cantidad de bytes leídos en el bloque actual
        std::streamsize bytesRead = inputFile.gcount();

        // Procesar los datos del bloque actual
        // Aquí puedes realizar cualquier operación que desees con los datos del bloque

        // Imprimir los datos del bloque actual
        std::cout << "Bloque " << i + 1 << ":" << std::endl;
        std::cout.write(block.data(), bytesRead);
        std::cout << std::endl;
    }

    // Cerrar el archivo
    inputFile.close();
}

int main(){
    gestor prueba(10,"textoprueba.txt");
    prueba.iniciarGestor();
    prueba.leernropag();
    std::cout<<"----------"<<std::endl;
    prueba.agregarBloqueVacio(9);
    prueba.agregarBloqueVacio(7);
    prueba.agregarBloqueVacio(8);
    prueba.leernropag();

}
