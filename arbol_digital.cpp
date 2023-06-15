
#include <iostream>
#include <vector>

template<typename T>
class Node {//creamos el 
public:
    std::vector<Node<T>*> children;
    std::string character;
    bool isFinal;
     T value;

    Node(const std::string& character, bool isFinal, const T& value) :
        character(character),
        isFinal(isFinal),
        value(value) {}

    ~Node() {
        for (Node<T>* child : children) {
            delete child;
        }
    }
};

template<typename T>

class Hoja : public Node<T> {//
public:
    Hoja(const std::string& character, const T& value) ://inicializamos los
        Node<T>(character, true, value) {}              // valores de caracter y value
};      //static_cast[<typename hoja*>()

template<typename T>
class Trie {
private:
    Node<T>* root;

    void removeHelper(Node<T>* currentNode, const std::string& key, int depth) {//funcion para eliminar un nodo
        if (currentNode == nullptr) {//si no hay nada
            return;
        }

        if (depth == key.length()) {//verificamos si a alcanzado la profundidad del string
            currentNode->isFinal = false;// le indicamos que ya no es nodo final
            return;
        }

        char currentChar = key[depth];// obtenmos el caracter de la posicion actual del depht

        for (int i = 0; i < currentNode->children.size(); i++) {
            if (currentNode->children[i]->character == std::string(1, currentChar)) {
                removeHelper(currentNode->children[i], key, depth + 1);// lo removemos recursivamente
                                                                        // y aumentamos la profundidad

                if (currentNode->children[i]->children.empty() && !currentNode->children[i]->isFinal) {//si se verifica que ya no hay nodos hijos 
                                                                                                        //y no es nodo final
                    delete currentNode->children[i];//eliminamos el nodo y sus hijos
                    currentNode->children.erase(currentNode->children.begin() + i);
                }

                return;
            }
        }
    }

public:
    Trie() {
        root = new Node<T>("", false, T());//el operador new, se reserva memoria en el montón (heap)
                                        // para crear un objeto y se devuelve un puntero a la dirección
                                        // de memoria donde se encuentra ese objeto.
    }
    ~Trie() {
        delete root;
    }
    void print_Values(){
        return printValues(root);
    }
    void print_values_cabezera(){
        return print_cabezera(root);
    }
    //void print_cabezera(auto aux){
        //for(auto child : aux->children){
            
        //}
    //}

    void printValues(Node<T>* currentNode) {
    if (currentNode == nullptr) {
        return;
    }

    if (currentNode->isFinal!=true) {
        std::cout << currentNode->character <<"-";
        }
        std::cout<<std::endl;

    for (Node<T>* child : currentNode->children) {
        printValues(child);
    }
    }   

    void insert(const std::string& key, const T& value) {//hola
        Node<T>* currentNode = root;//lo empezamos a usar, le asignamos los mismos valores que root

        for (const char& c : key) {//recorre la palabra
            Node<T>* nextNode = nullptr;//creamos un puntero para cada caracter des string
            //se recorre la clave carácter por carácter. 
            //Para cada carácter, se busca si hay un nodo hijo existente en 
            //el nodo actual que tenga el mismo carácter. Si se encuentra un nodo
             //hijo correspondiente, se avanza al siguiente nodo. 
            for (Node<T>* child : currentNode->children) {//lo recorremos 
                if (child->character == std::string(1, c)) {//lo comparamos // el 1 significa el num de veces q se repite
                    nextNode = child;// si se verifica que es igual le asignamos el nodo hijo nextNode
                    break;
                }
            }

            //Si no se encuentra, 
             //se crea un nuevo nodo hijo con el carácter y se agrega al vector de nodos 
             //hijos del nodo actual.
            if (nextNode == nullptr) {
                nextNode = new Node<T>(std::string(1, c), false, T());//le asignamos el caracter
                currentNode->children.push_back(nextNode);//le asignamos el nodo hijo
            }

            currentNode = nextNode;// le asignamos nextNode para que pueda avanzar en el arbol
        }

        currentNode->isFinal = true;//al finalizar el bucle le asignamos como nodo terminal
        currentNode->value = value;
    }

    T search(const std::string& key) {
        Node<T>* currentNode = root;//le asignamos un puntero al root

        for (const char& c : key) {//recorremos el string
            bool found = false;

            for (Node<T>* child : currentNode->children) {//recorremos los hijos del root
                if (child->character == std::string(1, c)) {//si lo encuentra lo marcamos
                    currentNode = child;
                    found = true;
                    break;
                }
            }

            if (!found) {//si no se encontro la palabra deseada retorna un valor predeterminado de tipo T
                return T();
            }
        }

        if (currentNode->isFinal) {//si se logro recorrer exitoasamente tod la string 
                                    // y la bandera esta en true
            return currentNode->value;// podemos retornar la llave
        } else {
            return T();
        }
    }

    void remove(const std::string& key) {
        removeHelper(root, key, 0);
    }

};
int main() {
    Trie<int> trie;

    trie.insert("oso", 1);
    trie.insert("osito", 2);
    trie.insert("ave", 3);

    std::cout << trie.search("oso") << std::endl;  // Output: 1
    std::cout << trie.search("osito") << std::endl;  // Output: 2
    std::cout << trie.search("ave") << std::endl;  // Output: 3
    std::cout << trie.search("oso2") << std::endl;  // Output: 0
    std::cout << trie.search("avesota") << std::endl; // Output:4
    //trie.print_Values();
    trie.remove("ave");

    std::cout << trie.search("ave") << std::endl;  // Output: 0


    return 0;
}
