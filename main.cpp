#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <cstring>
#include <fstream>
#include <string>
/*
    Code made by: Jeremy Esau Valenciano Tadeo
    Paged Binary tree.
    30/11/2022
    This code don't support keys with same number and different letter (20A,20Z)
    We use windows 11 to show the txt
*/
using namespace std;
// iniciamos el numero de pagina en 0
int pag = 0;

// estructura de pagina
struct Pagina
{
    int numeroPagina;                 // numero de pagina
    int numeroLlaves;                 // numero de llaves
    int arregloLlaves[3] = {0, 0, 0}; // arreglo de llaves
    vector<int> apuntadores;          // vector de apuntadores
};
// estructura para guardar el numero
struct Pares
{
    int numero; // numero de la llave
    char letra; // letra de la llave
};

list<Pagina> lista; // lista donde guardaremos las paginas
list<Pares> pares;  // lista para mapear las llaves (relacion entre numero y llave)
// funcion para comparar el numero de pagina y ordenarlo
bool compare(const Pagina &first, const Pagina &second)
{
    // si el numero de pagina es menor al segundo
    if (first.numeroPagina < second.numeroPagina)
        return true;
    else
        return false;
}
// imprimimos la letra del mapeo
void imprimirLetraTXT(list<Pares> g, int llave, fstream &fout)
{
    list<Pares>::iterator it;
    for (it = g.begin(); it != g.end(); ++it)
    {
        // si la lleve es igual al numero
        if (it->numero == llave)
        {
            // imprimimos la letra en el txt
            fout << it->letra;
        }
    }
}
// funcion para imprimir en pantalla
void imprimirLetra(list<Pares> g, int llave)
{
    list<Pares>::iterator it;
    // iteramos sobre la lista
    for (it = g.begin(); it != g.end(); ++it)
    {
        // si la lleve es igual al numero
        if (it->numero == llave)
        {
            // imprimimos la letra
            cout << it->letra;
        }
    }
}
// funcion para generar el txt dada una lista de paginas
void generarTXT(list<Pagina> g)
{
    // creamos el archivo txt donde guardaremos la tabla
    fstream arbol("arbol.txt", ios::out);
    list<Pagina>::iterator it;
    // imprimimos la cabecera de la tabla
    arbol << "\t ------------------------------------------------------------------------------------------------\n";
    arbol << "\t| No.Pagina\t| Contador de llaves\t|Arreglo de llaves\t|Arreglo de hijos\t\t\t\t|\n";
    arbol << "\t ------------------------------------------------------------------------------------------------\n";
    // iteramos sobre la lista
    for (it = g.begin(); it != g.end(); ++it)
    {
        // imprimimos el numero de pagina
        arbol << "\t| " << it->numeroPagina << "\t";
        // imprimimos el numero de llaves
        arbol << "\t| " << it->numeroLlaves << "\t\t";
        arbol << "\t\t| ";
        // aqui se imprimen las llaves
        for (int i = 0; i < 3; i++)
        {
            arbol << "[";
            if (it->arregloLlaves[i] == 0)
            {
                arbol << "  ";
            }
            // imprimimos el arreglo de llaves[i] si es != de 0
            if (it->arregloLlaves[i] != 0)
            {

                arbol << it->arregloLlaves[i];
                // se imprime la letra en base a la lista pares
                imprimirLetraTXT(pares, it->arregloLlaves[i], arbol);
            }
            arbol << "]";
        }
        // obtenemos la longitud del vector de arreglos
        unsigned int vecSize = it->apuntadores.size();
        // run for loop from 0 to vecSize
        arbol << " \t\t|\t";
        if (vecSize == 0)
        {
            // iteramos sobre el vector
            for (int i = 0; i < it->numeroLlaves + 1; i++)
            {
                // imprimomos null en el archivo
                arbol << " NULL ";
            }
            // imprimimos saltos de linea
            if (it->numeroLlaves == 1)
                arbol << "\t";
            arbol << "  \t\t|";
        }
        // iteramos sobre el vector de apuntadores
        for (unsigned int i = 0; i < vecSize; i++)
        {
            // imprimimos apuntadores[i]
            arbol << " " << it->apuntadores[i] << "     ";
            // imprimimos tabuladores dependiendo de la longitud
            if (vecSize == 2)
                arbol << "\t ";
            if (vecSize == 3)
                arbol << " ";
            if (i == vecSize - 1)
                arbol << "\t|";
        }
        // imprimimos tabuladores dependiendo de la longitud
        if (it->numeroLlaves == 2)
            arbol << "\t\t\t";
        arbol << '\n';
    }
    arbol << "\t ------------------------------------------------------------------------------------------------\n";
}

// lista que imprime en pantalla
void showlist(list<Pagina> g)
{
    list<Pagina>::iterator it;
    // imprimimos la cabecera de la tabla
    cout << "\t ------------------------------------------------------------------------------------------------------\n";
    cout << "\t| No.Pagina\t| Contador de llaves\t|Arreglo de llaves\t|Arreglo de hijos\t\t\t|\n";
    cout << "\t ------------------------------------------------------------------------------------------------------\n";
    // iteramos sobre la lista
    for (it = g.begin(); it != g.end(); ++it)
    {
        // imprimimos el numero de pagina y numero de llaves
        cout << "\t| " << it->numeroPagina << "\t";
        cout << "\t| " << it->numeroLlaves << "\t";
        cout << "\t\t| ";
        // aqui se imprimen las llaves
        for (int i = 0; i < 3; i++)
        {
            // se imprimen espacios y separadores
            cout << "[";
            if (it->arregloLlaves[i] == 0)
            {
                cout << "  ";
            }
            // se imprimen el arreglo de llaves
            if (it->arregloLlaves[i] != 0)
            {

                cout << it->arregloLlaves[i];
                // se imprime la letra en base a la lista pares
                imprimirLetra(pares, it->arregloLlaves[i]);
                // se imprimen espacios y separadores
                if (it->arregloLlaves[i] < 10)
                    cout << " ";
            }
            cout << "]";
        }
        unsigned int vecSize = it->apuntadores.size();
        // obtenemos longitud de vector de apuntadores
        cout << " \t|\t";
        if (vecSize == 0)
        {
            // iteramos sobre el vector de apuntadores
            for (int i = 0; i < it->numeroLlaves + 1; i++)
            {
                // imprimimos NULL
                cout << " NULL ";
            }
            if (it->numeroLlaves == 1)
                cout << "\t";
            cout << "  \t\t|";
        }
        for (unsigned int i = 0; i < vecSize; i++)
        {
            // se imprimen espacios y separadores
            cout << " " << it->apuntadores[i] << "     ";
            if (vecSize == 2)
                cout << "\t ";
            if (vecSize == 3)
                cout << " ";
            if (i == vecSize - 1)
                cout << "\t|";
        }
        // se imprimen espacios y separadores
        if (it->numeroLlaves == 2)
            cout << "\t\t\t";
        cout << '\n';
    }
    cout << "\t ------------------------------------------------------------------------------------------------------\n";
}
// definimos una template para la clase arbol
template <class T, int order>
class BTree;

// definimos una template para la clase nodo
template <class T, int order>
class BTreeNode
{
private:
    // atributos
    T *keys;              // apuntadores de llaves
    BTreeNode **children; // apuntadores de hijos
    BTreeNode *parent;    // nodo padre
    int currSize;         // Nummero de llaves
    bool leaf;            // es hoja?
    int num;              // numero de pagina

public:
    friend class BTree<T, order>;
    BTreeNode()
    {
        // definimos el constructor del nodo
        parent = NULL; // padre a nulo
        currSize = 0;
        leaf = true; // se convierte en hoja
        keys = new T[order];
        children = new BTreeNode *[order + 1]; // se crea nuevo hijo nodo
        for (int i = 0; i < order; i++)
        {
            // se asigna a null cada nodo hijo
            children[i] = NULL;
        }
        children[order] = NULL;
        num = pag++; // se aumenta el numero de pagina
    }
    ~BTreeNode() // destructor del nodo
    {
        delete[] keys;     // eliminamos el arreglo de llaves
        delete[] children; // eliminamos el arreglo de hijos
    }
    // funcion para dividir los nodos
    void splitNode(BTreeNode *&root)
    {
        if (this->currSize <= order - 1)
        {
            return;
        }
        // se calcula el indice para partir el nodo
        int idx = this->currSize / 2;
        BTreeNode *newNode = new BTreeNode(); // se crea un nuevo nodo
        int i = idx + 1, j = 0;               // agarramos el de la derecha del indice
        while (i < this->currSize)
        {
            // se recorre el nodo y se asignan sus llaves al nuevo nodo
            newNode->keys[j] = this->keys[i];
            newNode->currSize++; // aumentamos el numero de llaves
            i++;
            j++;
        }
        i = idx + 1, j = 0;
        while (i < currSize + 1)
        {
            ////se recorre el nodo y se asignan sus llaves al nuevo nodo
            newNode->children[j] = children[i];
            if (children[i] != NULL)
            {
                // se le asigan el nuevo padre al nodo
                newNode->children[j]->parent = newNode;
            }
            if (children[i] != NULL)
            {
                // pasa a ya no se hoja
                newNode->leaf = false;
            }
            i++;
            j++;
        }
        this->currSize = idx; // indice  = current size
        if (this->parent == NULL)
        {
            // si el padre es null, creamos uno nuevo
            parent = new BTreeNode();
            // el nuevo padre en [0] es igual a este nodo this
            parent->children[0] = this;
            // raiz = padre
            root = parent;
            // ya no es hoja
            root->leaf = false;
        }
        for (i = parent->currSize; i >= 0; i--)
        {
            // iteramos sobre el nodo
            if (i == 0 || parent->keys[i - 1] <= keys[idx])
            {
                // asignamos las llaves al nuevo padre
                parent->keys[i] = keys[idx];
                parent->children[i + 1] = newNode;
                break;
            }
            else if (parent->keys[i - 1] > keys[idx])
            {
                // se  asignan las llaves al nuevo padre y a los hijos
                parent->keys[i] = parent->keys[i - 1];
                parent->children[i + 1] = parent->children[i];
            }
        }
        parent->currSize++;       // aumentamos el numero de llaves
        newNode->parent = parent; // se asigna el nuevo padre
        parent->splitNode(root);  // se llava ahora con la raiz
    }
    // funcion para recorrer el arbol
    void traverse(int level)
    {
        // creamos pagina temporal
        struct Pagina temp;
        for (int i = 0; i < currSize; i++)
        {
            // se obtiene las llaves
            temp.arregloLlaves[i] = keys[i];
            // se obtiene el numero de llaves
            temp.numeroLlaves = currSize;
            // se obtiene el numero de pagina
            temp.numeroPagina = num - 1;
        }
        for (int i = 0; i <= currSize; i++)
        {
            // se obtiene las llaves de los padres
            if (!leaf)
            {
                int value = children[i]->num - 1;
                // agregamos al vector de apuntadores
                temp.apuntadores.push_back(value);
            }
        }
        // agregamos a la lista nuestra pagina
        lista.push_back(temp);

        if (this->leaf)
            return;
        for (int i = 0; i < currSize + 1; i++)
        {
            // recorremos el arbol en sus hijos
            children[i]->traverse(level + 2);
        }
    }
};
// definimos la clase template del arbol
template <class T, int order>
class BTree
{
private:
    // se crea el nodo raiz con el orden del arbol
    BTreeNode<T, order> *root;

public:
    BTree()
    {
        // se define la raiz en NULL
        root = NULL;
    }
    // destructor del arbol
    ~BTree()
    {
        delete root;
    }
    // funcion para insertar en el arbol la llave
    void Insert(int key)
    {
        // se crea nuevo nodo
        BTreeNode<T, order> *currNode = root;
        if (root == NULL)
        {
            // se crea nuevo nodo y se asigna a la raiz
            root = new BTreeNode<T, order>();
            // se asigna la llave
            root->keys[root->currSize] = key;
            // aumentamos en numero de llaves
            root->currSize++;
            // aumentamos en numero de pagina
            root->num = pag++;
        }
        else
        {
            int nodeToTraverse = 0;
            // si el nodo actual no es hoja
            while (!currNode->leaf)
            {
                // iteramos sobre las llaves del nodo
                nodeToTraverse = currNode->currSize;
                for (int i = 0; i < currNode->currSize; i++)
                {
                    // en caso de que la llave[i] sea mayor a la calle
                    if (currNode->keys[i] > key)
                    {
                        // ndodo actual es igual a i
                        nodeToTraverse = i;
                        break;
                    }
                }
                // nodo actual es igual al nodo hijo
                currNode = currNode->children[nodeToTraverse];
            }
            // iteramos sobre el nodo actual dado el numero de llaves
            for (int i = currNode->currSize; i >= 1; i--)
            {
                // en caso de que la llave sea mayor a key >
                if (currNode->keys[i - 1] > key)
                {
                    // se asignan las llaves al nodo actual
                    currNode->keys[i] = currNode->keys[i - 1];
                    currNode->keys[i - 1] = key;
                }
                else
                {
                    currNode->keys[i] = key;
                    break;
                }
            }
            currNode->currSize++;      // aumentamos en numero de llaves
            currNode->splitNode(root); // volvemos a llamar a dividir pero con raiz
        }
    }
    void Print()
    {
        // recorremos el arbol si raiz es  null regresamos
        if (root == NULL)
            return;
        root->traverse(0);
    }
};
// funcion para obtnener las llaves del txt
void obtenerInfo()
{
    // nombre del archivo
    string nombreArchivo = "productos.txt";
    ifstream archivo(nombreArchivo);
    string linea;
    // Obtener línea de archivo, y almacenar contenido en "linea"
    while (getline(archivo, linea))
    {
        // longitud de la linea
        int n = linea.length();

        // declarando arreglo dada la longitud
        char char_array[n + 1];
        // copiamos el contenido al char_array
        strcpy(char_array, linea.c_str());
        // obtenemos el primer numero de la llave
        int x = (char_array[0] - '0');
        // obtenemos el segundo numero de la llave
        int y = (char_array[1] - '0');
        // obtenemos la letra de la llave
        int z = char_array[2];
        // convertimos a string los numeros
        string s = to_string(x);
        string s1 = to_string(y);
        string s3 = s + s1;
        // convertimos el string a int
        int numero = stoi(s3);
        Pares temp;
        // le asignamos numero a la estructura temp
        temp.numero = numero;
        // le asignamos letra a la estructura temp
        temp.letra = z;
        // lo gregamos a la lista pares
        pares.push_back(temp);
    }
}

void llenarArbol(list<Pares> g)
{
    // declaramos el arbol de orden 4
    BTree<int, 4> t1;
    // inicializamos el numero de pagina
    pag = 0;
    list<Pares>::iterator it;
    // iteramos sobre la lista pares
    for (it = g.begin(); it != g.end(); ++it)
    {
        // insertamos el valor it->numero
        t1.Insert(it->numero);
    }
    // recorremos el arbol
    t1.Print();
}

int main()
{
    system("cls");
    int opcion;
    // menu de opciones
    cout << "\n\t\tArboles Binarios Paginados Practica #2\n";
    cout << "\n\t\t1. Generar el indice en forma de arbol binario paginado.";             // aqui solo se mueve el txt
    cout << "\n\t\t2. Mostrar en pantalla el indice en forma de arbol binario paginado."; // aqui se imprime
    cout << "\n\t\t3. Salir";
    cout << "\n\t\tIngrese opcion:";
    fflush(stdin);
    cin >> opcion;
    // opcion 1 y 2
    switch (opcion)
    {
    case 1:
        if (!lista.empty())
        {
            lista.clear();
            pares.clear();
        }
        obtenerInfo();
        llenarArbol(pares);
        lista.sort(compare); // ordenamos por hoja antes de imprimir
        generarTXT(lista);
        cout << "\n\t\tArbol Generado con exito\n\t\t";
        system("pause");
        main();
        break;
    case 2:
        showlist(lista);
        lista.clear();
        pares.clear();
        cout << "\t\t";
        system("pause");
        main();
        break;
    case 3:
        cout << "\n\t\tSaliendo.";
        break;
    }

    return 0;
}
