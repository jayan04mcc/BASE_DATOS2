#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Definición de la clase Cliente
class Cliente {
public:
    int PassengerId;
    int survived;
    int pclass;
    std::string name;
    std::string sex;
    int age;
    int sibSp;
    int parch;
    std::string ticket;
    double fare;
    std::string cabin;
    std::string embarked;
};

int main() {
    std::ifstream archivo("titanic.csv",std::ios::binary);//fuente externa
    if (!archivo) {
        std::cout << "Error al abrir el archivo." << std::endl;
        return 1;
    }
    archivo.seekg(0,std::ios::end);
    std::streampos fin= archivo.tellg();
    std::cout<<"TOTAL "<<fin<<std::endl;
    std::vector<Cliente> matriz_titanic;
    archivo.seekg(0,std::ios::beg);

    std::string line;
    std::getline(archivo, line);  // Leer la línea de encabezados y la descartamos la 
                                  // primera linea

    while (std::getline(archivo, line)) {
        std::stringstream ss(line);
        std::string field;//fuente de datos       jerarquia de datos:
                                                    //-ARCHIVO
                                                    //LINE STRING DE LA PRIMERA FILA DEL ARCHIVO
                                                    //FIELD STRING QUE SE ENCUENTRA ENTRE COMAS DE LA LINEA
                                                    //DEL LINE.
        Cliente cliente;

        // Asignar los valores de los campos al objeto Cliente
        std::istringstream iss(field); //lectura de datos 

        std::getline(ss, field, ',');
        iss.str(field); 
        iss.clear();
        iss >> cliente.PassengerId; //cin>> LECTURA de un archivo externo en mi programa


        std::getline(ss, field, ',');
        iss.str(field);
        iss.clear();// limpiar los indicadores de estado
        iss >> cliente.survived; //Finalmente, se realiza la lectura del valor de cliente.
                                //survived desde iss utilizando iss >> cliente.survived.
                                //Esto implica extraer y convertir el siguiente valor disponible en iss y 
                                //almacenarlo en la variable cliente.survived.

        std::getline(ss, field, ',');
        iss.str(field);
        iss.clear();
        iss >> cliente.pclass;

        std::getline(ss, field, ',');
        iss.str(field);
        iss.clear();
        iss >> cliente.name;

        std::getline(ss, field, ',');
        iss.str(field);
        iss.clear();
        iss >> cliente.sex;

        std::getline(ss, field, ',');
        iss.str(field);
        iss.clear();
        iss >> cliente.age;

        std::getline(ss, field, ',');
        iss.str(field);
        iss.clear();
        iss >> cliente.sibSp;

        std::getline(ss, field, ',');
        iss.str(field);
        iss.clear();
        iss >> cliente.parch;

        std::getline(ss, field, ',');
        iss.str(field);
        iss.clear();
        iss >> cliente.ticket;

        std::getline(ss, field, ',');
        iss.str(field);
        iss.clear();
        iss >> cliente.fare;

        std::getline(ss, field, ',');
        iss.str(field);
        iss.clear();
        iss >> cliente.cabin;

        std::getline(ss, field, ',');
        iss.str(field);
        iss.clear();
        iss >> cliente.embarked;
        

        matriz_titanic.push_back(cliente);
    }

    // Imprimir los valores de la matriz_titanic
    if (matriz_titanic.size() >= 2) {
    const Cliente& segundoRegistro = matriz_titanic[1];

    std::cout << "PassengerId: " << segundoRegistro.PassengerId << std::endl;
    std::cout << "Survived: " << segundoRegistro.survived << std::endl;
    std::cout << "Pclass: " << segundoRegistro.pclass << std::endl;
    std::cout << "Name: " << segundoRegistro.name << std::endl;
    std::cout << "Sex: " << segundoRegistro.sex << std::endl;
    std::cout << "Age: " << segundoRegistro.age << std::endl;
    std::cout << "SibSp: " << segundoRegistro.sibSp << std::endl;
    std::cout << "Parch: " << segundoRegistro.parch << std::endl;
    std::cout << "Ticket: " << segundoRegistro.ticket << std::endl;
    std::cout << "Fare: " << segundoRegistro.fare << std::endl;
    std::cout << "Cabin: " << segundoRegistro.cabin << std::endl;
    std::cout << "Embarked: " << segundoRegistro.embarked << std::endl;
} else {
    std::cout << "No hay suficientes registros en la matriz_titanic." << std::endl;
       }
   

    // Cerrar el archivo
    archivo.close();

    return 0;
}
