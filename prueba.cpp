#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

//----------------------------
// Definición de la estructura Nodo
//----------------------------
struct Nodo {
    int id;            // ID del miembro
    string nombre;     // Nombre
    int edad;          // Edad
    int padre_id;      // ID del padre
    int madre_id;      // ID de la madre
    Nodo* izq;         // Hijo izquierdo
    Nodo* der;         // Hijo derecho
};

//----------------------------
// Declaración de funciones (solo nombres, sin implementación)
//----------------------------

// Registrar nuevo miembro
Nodo* insertarRec(Nodo* raiz, int id, string nombre, int edad, int padre_id, int madre_id);

// Buscar miembro por ID
Nodo* buscarRec(Nodo* raiz, int id);

// Buscar miembro por nombre
Nodo* buscarPorNombreRec(Nodo* raiz, string nombre);

// Recorrido inorden
void inordenRec(Nodo* raiz);

// Recorrido preorden
void preordenRec(Nodo* raiz);

// Recorrido postorden
void postordenRec(Nodo* raiz);

// Visualización tipo ASCII
void imprimirASCII(Nodo* n, const string& titulo = "Arbol");

// Mostrar menú de usuario
void mostrarMenu();

int main() {
    setlocale(LC_ALL, "Spanish"); // Configura el idioma local para mostrar acentos y caracteres especiales
    
    Nodo* raiz = NULL;
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        if(cin.fail()){ cin.clear(); cin.ignore(256,'\n'); opcion=-1; }

        if(opcion == 1) {
            int id, edad, padre_id, madre_id;
            string nombre;
            cout << "ID: "; cin >> id;
            cout << "Nombre: "; cin.ignore(); getline(cin, nombre);
            cout << "Edad: "; cin >> edad;
            cout << "ID Padre (-1 si desconoce): "; cin >> padre_id;
            cout << "ID Madre (-1 si desconoce): "; cin >> madre_id;
            raiz = insertarRec(raiz, id, nombre, edad, padre_id, madre_id);
        }
        else if(opcion == 2) {
            int id;
            cout << "ID a buscar: "; cin >> id;
            Nodo* res = buscarRec(raiz, id);
            if(res) cout << "Encontrado: " << res->nombre << endl;
            else cout << "No encontrado." << endl;
        }
        else if(opcion == 3) {
            string nombre;
            cout << "Nombre a buscar: "; cin.ignore(); getline(cin, nombre);
            Nodo* res = buscarPorNombreRec(raiz, nombre);
            if(res) cout << "Encontrado ID " << res->id << endl;
            else cout << "No encontrado." << endl;
        }
        else if(opcion == 4) {
            cout << "Recorrido Inorden:" << endl;
            inordenRec(raiz);
        }
        else if(opcion == 5) {
            cout << "Recorrido Preorden:" << endl;
            preordenRec(raiz);
        }
        else if(opcion == 6) {
            cout << "Recorrido Postorden:" << endl;
            postordenRec(raiz);
        }
        else if(opcion == 7) {
            cout << "Visualización del árbol (ASCII):" << endl;
            imprimirASCII(raiz);
        }
        else if(opcion == 0) {
            cout << "Saliendo..." << endl;
        }
        else {
            cout << "Opción inválida." << endl;
        }
    } while(opcion != 0);

    return 0;
}

//-----------------------------
// Aquí irían las implementaciones de cada función declarada arriba
//-----------------------------

Nodo* buscarRec(Nodo* raiz, int id) {    // Busca un nodo específico por su ID de manera eficiente O(log n)
    if (raiz == NULL || raiz->id == id) {   //nodo vacío (no encontrado) o ID encontrado
        return raiz;
    }

    if (id < raiz->id) {                // Si el ID buscado es menor, buscar en subárbol izquierdo
        return buscarRec(raiz->izq, id);
    } else {                            // Si el ID buscado es mayor, buscar en subárbol derecho
        return buscarRec(raiz->der, id);
    }
}

Nodo* buscarPorNombreRec(Nodo* raiz, string nombre) {   // Busca un nodo por nombre - debe revisar todo el árbol O(n)
    if (raiz == NULL) return NULL;    //si llegamos a NULL, no hay más nodos que revisar

    if (raiz->nombre == nombre) {     // Si encontramos el nombre buscado, retornar el nodo
        return raiz;
    }

    Nodo* izquierda = buscarPorNombreRec(raiz->izq, nombre);  // Buscar recursivamente en el subárbol izquierdo
    if (izquierda != NULL) return izquierda;   // Si encontró algo en la izquierda, retornarlo

    return buscarPorNombreRec(raiz->der, nombre);   // Si no encontró nada en la izquierda, buscar en el subárbol derecho
}

void inordenRec(Nodo* raiz) {    // Recorre el árbol en orden: izquierda -> raíz -> derecha
    if (raiz == NULL) return;    //si el nodo es NULL, terminar recursión
    inordenRec(raiz->izq);    // Primero recorrer subárbol izquierdo
    cout << raiz->id << " - " << raiz->nombre << " (Edad: " << raiz->edad << ")" << endl;   // Luego imprimir los datos del nodo actual
    inordenRec(raiz->der);    // Finalmente recorrer subárbol derecho
}

void preordenRec(Nodo* raiz) {    // Recorre el árbol en preorden: raíz -> izquierda -> derecha
    if (raiz == NULL) return;   //si el nodo es NULL, terminar recursión
    cout << raiz->id << " - " << raiz->nombre << " (Edad: " << raiz->edad << ")" << endl;   // Primero imprimir el nodo actual
    preordenRec(raiz->izq);    // Luego recorrer subárbol izquierdo
    preordenRec(raiz->der);    // Finalmente recorrer subárbol derecho
}

void postordenRec(Nodo* raiz) {    // Recorre el árbol en postorden: izquierda -> derecha -> raíz
    if (raiz == NULL) return;   //si el nodo es NULL, terminar recursión
    postordenRec(raiz->izq);   // Primero recorrer subárbol izquierdo
    postordenRec(raiz->der);   // Luego recorrer subárbol derecho
    cout << raiz->id << " - " << raiz->nombre << " (Edad: " << raiz->edad << ")" << endl;   // Finalmente imprimir el nodo actual
}

// Muestra el árbol de forma vertical usando ramas con '/' y '\\'
static void imprimirASCIIRec(Nodo* n, const string& prefijo, bool esIzq) {
    if (n == NULL) return;

    cout << prefijo << (esIzq ? "|-- " : "\\-- ") << n->id << " (" << n->nombre << ")" << endl;

    string nuevoPrefijo = prefijo + (esIzq ? "|   " : "    ");
    if (n->izq)  imprimirASCIIRec(n->izq, nuevoPrefijo, true);
    if (n->der)  imprimirASCIIRec(n->der, nuevoPrefijo, false);
}

// Función pública para imprimir el árbol con una cabecera
void imprimirASCII(Nodo* n, const string& titulo) {
    if (n == NULL) {
        cout << "(árbol vacío)" << endl;
        return;
    }

    cout << titulo << endl;
    cout << n->id << " (" << n->nombre << ")" << endl;
    if (n->izq)  imprimirASCIIRec(n->izq, "", true);
    if (n->der)  imprimirASCIIRec(n->der, "", false);
}

void mostrarMenu() {         // Muestra la interfaz de usuario con todas las opciones disponibles
    cout << "\n--- GESTIÓN GENEALÓGICA ---\n";
    cout << "1. Registrar nuevo miembro\n";
    cout << "2. Buscar miembro por ID\n";
    cout << "3. Buscar miembro por nombre\n";
    cout << "4. Recorrido inorden\n";
    cout << "5. Recorrido preorden\n";
    cout << "6. Recorrido postorden\n";
    cout << "7. Visualización ASCII\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opción: ";
}
// Inserta un nuevo nodo en el árbol de búsqueda binaria por ID
Nodo* insertarRec(Nodo* raiz, int id, string nombre, int edad, int padre_id, int madre_id) {
    if (raiz == NULL) {
        Nodo* nuevo = new Nodo;
        nuevo->id = id;
        nuevo->nombre = nombre;
        nuevo->edad = edad;
        nuevo->padre_id = padre_id;
        nuevo->madre_id = madre_id;
        nuevo->izq = nuevo->der = NULL;
        return nuevo;
    }

    if (id < raiz->id) {
        raiz->izq = insertarRec(raiz->izq, id, nombre, edad, padre_id, madre_id);
    } else if (id > raiz->id) {
        raiz->der = insertarRec(raiz->der, id, nombre, edad, padre_id, madre_id);
    } else {
        cout << "ID duplicado. No se insertó." << endl;
    }
    return raiz;
}

