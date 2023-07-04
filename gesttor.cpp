#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#define TAMANIO 4096
struct Registro {
    int id;
    std::string nombre;
    int edad;
};

class Gestor{
private:
    int numPag;
public:
    Gestor(){}
    void iniciarGestor();
    void AgregarBloqueVacio();
    void pesoBase();
    void LeerBloque(int);
    void escribirBloque(int);

};
void Gestor::iniciarGestor(){
    std::ofstream archivo("recurso.txt", std::ios::binary | std::ios::app);

    if (archivo.is_open()) {
        archivo.seekp(0, std::ios::end); // Mover el puntero de escritura al final del archivo

        
        const int TAMANIO_ESCRITO = archivo.tellp();
        std::cout << "PESO INICIAL "<<TAMANIO_ESCRITO<<std::endl;
        const int BYTES_RESTANTES = TAMANIO*(numPag+1) - TAMANIO_ESCRITO;

        for (int i = 0; i < BYTES_RESTANTES; i++) {
        char cero = '0';
            archivo.write(&cero, sizeof(cero));
        }
        

        archivo.close();
        std::cout << "El archivo se ha rellenado con ceros." << std::endl;
    } else {
        std::cout << "No se pudo abrir el archivo." << std::endl;
    }

}
void Gestor::LeerBloque(int numeroPagina){
std::ifstream archivo("recurso.txt");
    if(numeroPagina>numeroPagina){
        exit(1);
    }
    if(!archivo.is_open()){
        exit(1);
    }
    archivo.seekg(numeroPagina*TAMANIO,std::ios::beg);
    const int bufferSize = TAMANIO+1;  // Tamaño del buffer de lectura
    char buffer[bufferSize];
    archivo.read(buffer, bufferSize - 1);  // Leer 51 bytes desde la posición actual

    buffer[archivo.gcount()] = '\0';  // Agregar un carácter nulo al final del buffer para convertirlo en una cadena
    archivo.seekg((numeroPagina+1)*TAMANIO,std::ios::beg);
    std::streampos cont=archivo.tellg();
    std::cout << "Contenido leido  " << buffer << std::endl;
    std::cout<<"cantidad de bytes "<<cont;

    archivo.close();
    

}
void Gestor::escribirBloque(int numeroPagina){
    std::fstream archivo("recurso.txt",std::ios::in | std::ios::out  | std::ios::binary);
    if(!archivo.is_open()){
        exit(1);
    }
     archivo.seekg(0, std::ios::end);
    int longitud = archivo.tellg();
    archivo.seekg(0, std::ios::beg);

    // Leer el contenido del archivo en un buffer
    char* buffer = new char[longitud];
    archivo.read(buffer, longitud);

    // Encontrar la posición del carácter nulo
    int posicionNulo = -1;
    for (int i = 0; i < longitud; i++) {
        if (buffer[i] == '\0') {
            posicionNulo = i;
            break;
        }
    }

    if (posicionNulo == -1) {
        std::cout << "La pagina no tiene mas capacidad para ingresar mas data" << std::endl;
    } else {
        std::string texto_nuevo;
        std::cout << "La cantidad de bytes hasta el carácter nulo es: " << posicionNulo << std::endl;
        archivo.seekp(posicionNulo, std::ios::beg);
        std::cout<<"ingrese el nuevo contenido"<< std::endl;
        std::cin>>texto_nuevo;
        archivo>>" ">>texto_nuevo;



    }

    // Liberar la memoria del buffer
    delete[] buffer;
}
void Gestor::AgregarBloqueVacio() {
    std::fstream archivo("recurso.txt", std::ios::in | std::ios::out | std::ios::binary|std::ios::app);  // Abrir el archivo en modo lectura y escritura binaria

    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo." << std::endl;
        exit(1);
    }

    archivo.seekg(0, std::ios::end);  // Mover el puntero de lectura al final del archivo
    std::streampos fileSize = archivo.tellg();  // Obtener el tamaño actual del archivo

    if (fileSize == 0) {
        for (int i = 0; i < TAMANIO; i++) {
            archivo.write("0", 1);  // Escribir el caracter "0" TAMANIO veces al final del archivo
        }
    } else {
        archivo.seekp(TAMANIO * numPag, std::ios::beg);  // Mover el puntero de escritura a la posición específica
        archivo <<"\n";
        for (int i = 0; i < TAMANIO; i++) {
            archivo.write("0", 1);  // Escribir el caracter "0" TAMANIO veces en la posición específica
        }
    }

    archivo.close();
}

void Gestor::pesoBase(){
    std::ifstream file("recurso.txt", std::ios::binary | std::ios::ate);

    std::streampos fileSize = file.tellg();//ontenemos el tamanio
    int tamanio_total=static_cast<int>(fileSize);
    numPag=tamanio_total/TAMANIO ;
    file.close();

    std::cout << "El tamanio del archivo es: "<< fileSize <<" bytes"<< std::endl;
    std::cout << "El tamanio del archivo si la pag estuviera completa: "<< TAMANIO*(numPag+1) <<" bytes"<< std::endl;
    std::cout <<" el numero de paginas son "<<numPag<<std::endl;
}
int main() {
    Gestor prueba;
    //prueba.pesoBase();
    //prueba.iniciarGestor();
    //prueba.pesoBase();
    //prueba.AgregarBloqueVacio();
    //prueba.pesoBase();
    prueba.LeerBloque(3);
    //prueba.iniciarGestor();
    //prueba.pesoBase();

    
    

   
}
