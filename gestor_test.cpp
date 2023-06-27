#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

class Gestor{

    private:
        string nombreArchivo = "";
        int numPaginas = 0;
        int tamanoArchivo = 0; 
        int paginaPrincipal = 0;
        int paginaActual = 0;
        int tamanioPagina = 100;
    public:8
        Gestor(){
            // Constructor vacío
        };

        // Métodos para establecer los valores de las variables privadas
        void setNumPaginas(int num){
            numPaginas = num;
        };
        void setNombre(string nombre){
            nombreArchivo = nombre;
        };
        void setTamanoArchivo(int tamano){
            tamanoArchivo = tamano;
        };
        void setPaginaPrincipal(int pagina){
            paginaPrincipal = pagina;
        };
        void setPaginaActual(int pagina){
            paginaActual = pagina;
        };
        // Métodos para obtener los valores de las variables privadas
        int getPaginaPrincipal(){
            return paginaPrincipal;
        };
        int getTamanoArchivo(){
            return tamanoArchivo;
        };
        int getNumPaginas(){
            return numPaginas;
        };
        int getTamanioPagina(){
            return tamanioPagina;
        };
        int getPaginaActual(){
            return paginaActual;
        };

        // Formatea el número de páginas en un string de tres dígitos
        string formatearNPaginas(){
            string nPag = "";
            if(numPaginas < 10){
                nPag = "00" + to_string(numPaginas);
            }
            else if(numPaginas < 100){
                nPag = "0" + to_string(numPaginas);

            }   
            else{
                nPag = to_string(numPaginas);
            }
            return nPag;
        };

        
        // Actualiza el número de páginas en el archivo
        void actPaginas(string nombre){
            ifstream archivo;
            archivo.open(nombre, ios::in);
            string numeroPaginas = formatearNPaginas();
            string texto = "";
            getline(archivo, texto);
            //Reemplazar el numero de paginas en el archivo
            texto.replace(0, 3, numeroPaginas);
            archivo.close();
            ofstream archivoEscritura;
            archivoEscritura.open(nombre, ios::out);
            archivoEscritura<<texto;
            archivoEscritura.close();

        };
        // Crea un archivo con el nombre especificado y escribe el número de páginas en él
        void crearArchivo(ofstream &archivo)
        {
            string nombre = nombreArchivo + ".txt";
            archivo.open(nombre, ios::out);
            string numeroPaginas = formatearNPaginas();
            cout << "\nNumero de paginas: " << numeroPaginas << endl;
            archivo << numeroPaginas;
            archivo.close();
            setTamanoArchivo(3);
            actPaginas(nombre);
        };

        // Lee el contenido del archivo y lo devuelve como string
        string leerArchivo(){
            ifstream archivo;
            string nombre = nombreArchivo + ".txt";
            archivo.open(nombre, ios::in);
            string texto = "";
            getline(archivo, texto);
            archivo.close();
            return texto;
        };

        // Agrega una página al archivo
        void addPage()
        {
            setNumPaginas(numPaginas + 1);
            tamanoArchivo += tamanioPagina;
            setPaginaPrincipal(1);
            setPaginaActual(numPaginas);
            cout << "Numero de paginas: " << numPaginas << endl;
            cout << "Pagina Actual: " << paginaActual << endl;

            string nombre = nombreArchivo + ".txt";

            // Actualizar el número de páginas en el archivo
            actPaginas(nombre);

            // Abrir el archivo en modo de escritura al final (ios::app)
            ofstream archivo;
            archivo.open(nombre, ios::app);

            // Agregar espacios ( ) a la página actual sin sobrescribir el contenido existente
            for (int i = 0; i < tamanioPagina; i++)
            {
                archivo << " ";
            }

            archivo.close();
        }

        // Escribe el texto en la página actual del archivo
        void escribirPActual(){
            if(numPaginas == 0){
                cout<<"\nNo hay paginas en el archivo"<<endl;
                return;
            }
            else{
                int iterador = 0;
                iterador = 3+(paginaActual-1)*tamanioPagina;
                string texto = "";
                cout<<"\nIngrese el texto a escribir: "<<endl;
                //  Limpiar el buffer antes de leer el texto
                cin.ignore();
                // Capturar todo el texto con espacios incluidos
                getline(cin, texto);
                string lectura = leerArchivo();
                lectura.replace(iterador, texto.length() ,texto);

                // Escribir el texto en el archivo
                ofstream archivoEscritura;
                archivoEscritura.open(nombreArchivo+".txt", ios::out);
                archivoEscritura<<lectura;
                archivoEscritura.close();
                cout<<"\nTamano texto despues de escritura: "<<lectura.length()<<endl;


            }
            
        };

        // Lee el contenido de la página especificada por su número
        void leerPaginaNro(int nroPagina){
            int iterador = 0;
            iterador = 3+(nroPagina-1)*tamanioPagina;
            string lectura = leerArchivo();
            string textoPagina = lectura.substr(iterador, tamanioPagina);
            cout<<"\nTexto de la pagina "<<nroPagina<<": "<<textoPagina<<endl;
            
            
            
            paginaActual = nroPagina;
            cout<<"\nPagina actual: "<<paginaActual<<endl;
        };

        // Escribe en la página especificada por su número
        void escribirPaginaNro(int r_pag){
            setPaginaActual(r_pag);
            escribirPActual();
        };
};

int main(){
    //Abrir documento txt
    ofstream a1;
    Gestor gestor;
    while (true)
    {
        cout<<"\n#############################################"<<endl;
        cout<<"\n\tGESTOR DE ARCHIVOS"<<endl;;
        cout<<"01. Crear Archivo"<<endl;
        cout<<"02. Abrir Archivo"<<endl;
        cout<<"03. Agregar Pagina"<<endl;
        cout<<"04. Tamano del Archivo"<<endl;
        cout<<"05. Escribir en pagina actual"<<endl;
        cout<<"06. Leer pagina numero: X"<<endl;
        cout<<"07. Posicion de la pagina actual"<<endl;
        cout<<"08. Leer primer pagina"<<endl;
        cout<<"09. Leer ultima pagina"<<endl;
        cout<<"10. Leer siguiente pagina"<<endl;
        cout<<"11. Leer pagina anterior"<<endl;
        cout<<"12. Leer bloque actual"<<endl;
        cout<<"13.Escribir en la pagina numero: X"<<endl;
        cout<<"0. Salir"<<endl;
        cout<<"\n#############################################\n"<<endl;
        cout<<"-Ingrese una opcion: ";
        int opcion;
        cin >> opcion;
        int x,x2;
        string nombreArchivo;
        string msg = "";
        int r_pag;
        

        switch (opcion)
        {
            case 1:
                cout<<"Crear Archivo"<<endl;
                cout<<"Ingrese el nombre del archivo: "<<endl;
                cin>>nombreArchivo;
                gestor.setNombre(nombreArchivo);
                gestor.crearArchivo(a1);
                break;
            case 2:
                cout<<"Abrir Archivo"<<endl;
                cout<<"Ingrese el nombre del archivo: "<<endl;
                cin>>nombreArchivo;
                gestor.setNombre(nombreArchivo);
                msg = gestor.leerArchivo();
                if(msg == "" || msg == "000"){
                    cout<<"El archivo no existe"<<endl;
                    break;
                }
                else{
                    cout<<"***********"<<endl;
                    cout<<"\nDATOS DEL ARCHIVO"<<endl;
                    cout<<"Nombre del archivo: "<<nombreArchivo<<".txt "<<endl;
                    // obtener el tamaño del msg
                    x = msg.length();
                    cout << "Tamano del texto: " << x <<".bytes"<< endl;
                    gestor.setTamanoArchivo(x);
                    x2 = (x - 3) / gestor.getTamanioPagina();
                    cout << "Numero de paginas: " << x2 <<" pag"<< endl;
                    gestor.setNumPaginas(x2);
                    gestor.setPaginaActual(x2);
                    gestor.setPaginaPrincipal(1);
                    // Muestra el texto en formato de primera linea de 3 caracteres y luego tamanioPagina caracteres por linea
                    for (int i = 3; i < msg.length(); i++)
                    {
                        if ((i - 3) % gestor.getTamanioPagina() == 0)
                        {
                            cout << endl;
                        }
                        cout << msg[i];
                    }
                    cout<<"\n\n***********"<<endl;
                    system("pause");
                    break;
                }
                
                
            case 3:
                if(gestor.getTamanoArchivo() == 0){
                    cout<<"No hay archivo"<<endl;
                    break;
                }
                else{
                    cout<<"Agregar Pagina"<<endl;
                    gestor.addPage();
                    break;
                }
            case 4:
                if (gestor.getTamanoArchivo() == 0)
                {
                    cout<<"No hay archivo"<<endl;
                    break;
                }
                else{
                    cout<<"\nTamano del Archivo: " << gestor.getTamanoArchivo() <<".bytes"<<endl;
                    break;
                }

            case 5:
                if(gestor.getNumPaginas() == 0){
                    cout<<"No hay paginas"<<endl;
                    break;
                }
                else{
                    cout << "\nEscribiendo en pagina actual......" << endl;
                    gestor.escribirPActual();
                    break;
                }
                
            case 6:
                cout<<"\nIngrese numero de pagina para leer: ";
                cin>>r_pag;
                if(r_pag > gestor.getNumPaginas() || r_pag < 1){
                    cout<<"\nEl numero de pagina no existe"<<endl;
                    break;
                }
                else{
                    gestor.leerPaginaNro(r_pag);
                    break;
                }
                
            case 7:
                if(gestor.getNumPaginas() == 0){
                    cout<<"No hay paginas"<<endl;
                    break;
                }
                else{
                    cout<<"Posicion de la pagina actual: "<<gestor.getPaginaActual()<<endl;
                    break;
                }

            case 8:
                cout<<"Leer primer pagina"<<endl;
                if(gestor.getNumPaginas() == 0){
                    cout<<"No hay paginas"<<endl;
                    break;
                }
                else{
                    gestor.leerPaginaNro(1);
                    break;
                }   
            case 9:
                cout<<"Leer ultima pagina"<<endl;
                if(gestor.getNumPaginas() == 0){
                    cout<<"No hay paginas"<<endl;
                    break;
                }
                else{
                    gestor.leerPaginaNro(gestor.getNumPaginas());
                    break;
                }
                
            case 10:
                cout<<"Leer siguiente pagina"<<endl;
                r_pag = gestor.getPaginaActual() + 1 ;
                if(r_pag > gestor.getNumPaginas()){
                    cout<<"No hay mas paginas"<<endl;
                    break;
                }
                else{
                    gestor.leerPaginaNro(r_pag);
                    break;
                }
            case 11:
                cout<<"Leer pagina anterior"<<endl;
                r_pag = gestor.getPaginaActual() - 1 ;
                if(r_pag < 1){
                    cout<<"No hay mas paginas"<<endl;
                    break;
                }
                else{
                    gestor.leerPaginaNro(r_pag);
                    break;
                }

            case 12:
                cout<<"Leer bloque actual"<<endl;
                if (gestor.getNumPaginas() == 0)
                {
                    cout << "No hay paginas" << endl;
                    break;
                }
                else{
                    gestor.leerPaginaNro(gestor.getPaginaActual());
                    break;
                }
                

            case 13:
                cout<<"Escribir en la pagina numero: X"<<endl;
                cout<<"Ingrese numero de pagina para escribir: "<<endl;
                cin>>r_pag;
                if(r_pag > gestor.getNumPaginas() || r_pag < 1){
                    cout<<"El numero de pagina no existe"<<endl;
                    break;
                }
                else{
                    gestor.escribirPaginaNro(r_pag);
                    break;
                }
            case 0:
                cout<<"Salir"<<endl;
                exit(0);
                break;
            default:
                cout<<"Opcion no valida"<<endl;
                break;
        }
    }

    return 0;
}
