#include <iostream>
#include <string>
#include <limits>  
#include <cstdlib> 

using namespace std;

struct Nodo {
    int cedula;
    string nombre;
    string telefono;
    string direccion;
    Nodo* izquierda;
    Nodo* derecha;

    Nodo(int cedula, const string& nombre, const string& telefono, const string& direccion)
        : cedula(cedula), nombre(nombre), telefono(telefono), direccion(direccion), izquierda(NULL), derecha(NULL) {}
};

class ArbolBinario {
private:
    Nodo* raiz;

    Nodo* insertar(Nodo* nodo, int cedula, const string& nombre, const string& telefono, const string& direccion) {
        if (nodo == NULL) {
            return new Nodo(cedula, nombre, telefono, direccion);
        }

        if (cedula < nodo->cedula) {
            nodo->izquierda = insertar(nodo->izquierda, cedula, nombre, telefono, direccion);
        } else if (cedula > nodo->cedula) {
            nodo->derecha = insertar(nodo->derecha, cedula, nombre, telefono, direccion);
        }

        return nodo;
    }

    Nodo* buscarPorCedula(Nodo* nodo, int cedula) {
        if (nodo == NULL || nodo->cedula == cedula) {
            return nodo;
        }

        if (cedula < nodo->cedula) {
            return buscarPorCedula(nodo->izquierda, cedula);
        } else {
            return buscarPorCedula(nodo->derecha, cedula);
        }
    }

    void listarNodos(Nodo* nodo) {
        if (nodo != NULL) {
            listarNodos(nodo->izquierda);
            cout << "Cedula: " << nodo->cedula << ", Nombre: " << nodo->nombre
                 << ", Telefono: " << nodo->telefono << ", Direccion: " << nodo->direccion << endl;
            listarNodos(nodo->derecha);
        }
    }

public:
    ArbolBinario() : raiz(NULL) {}

    void insertar(int cedula, const string& nombre, const string& telefono, const string& direccion) {
        raiz = insertar(raiz, cedula, nombre, telefono, direccion);
    }

    Nodo* buscarPorCedula(int cedula) {
        return buscarPorCedula(raiz, cedula);
    }

    void listarNodos() {
        listarNodos(raiz);
    }
};

void limpiarPantalla() {
#ifdef _WIN32
    system("cls"); //Limpiar windows
#else
    system("clear"); //Limpiar Linux o Unix
#endif
}

void pausarConsola() {
    cout << "Presiona Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void mostrarMenu() {
    cout << "\nMenu:\n";
    cout << "1. Crear Usuario\n";
    cout << "2. Consultar por Cedula\n";
    cout << "3. Listar Usuarios\n";
    cout << "0. Salir\n";
}

int obtenerOpcion() {
    int opcion;
    cout << "Ingrese su opcion: ";
    cin >> opcion;
    return opcion;
}

void mostrarMensaje(const string& mensaje) {
    cout << mensaje << endl;
}

int obtenerCedula() {
    int cedula;
    cout << "Ingrese la cedula: ";
    cin >> cedula;
    return cedula;
}

string obtenerTexto(const string& mensaje) {
    string texto;
    cout << mensaje;
    cin.ignore(); 
    getline(cin, texto);
    return texto;
}

int main() {
    ArbolBinario arbol;

    int opcion;
    do {
        limpiarPantalla();
        mostrarMenu();
        opcion = obtenerOpcion();

        switch (opcion) {
            case 1: {
                limpiarPantalla();
                int cedula = obtenerCedula();
                string nombre = obtenerTexto("Ingrese el nombre: ");
                string telefono = obtenerTexto("Ingrese el telefono: ");
                string direccion = obtenerTexto("Ingrese la direccion: ");

                arbol.insertar(cedula, nombre, telefono, direccion);
                mostrarMensaje("Usuario creado exitosamente.");
                break;
            }
            case 2: {
                limpiarPantalla();
                int cedulaConsulta = obtenerCedula();

                Nodo* nodoBuscado = arbol.buscarPorCedula(cedulaConsulta);

                limpiarPantalla();
                if (nodoBuscado != NULL) {
                    cout << "Usuario encontrado: Cedula: " << nodoBuscado->cedula << ", Nombre: " << nodoBuscado->nombre
                         << ", Telefono: " << nodoBuscado->telefono << ", Direccion: " << nodoBuscado->direccion << endl;
                } else {
                    cout << "Usuario no encontrado para la cedula " << cedulaConsulta << endl;
                }
                break;
            }
            case 3:
                limpiarPantalla();
                cout << "\nListado de Usuarios:\n";
                arbol.listarNodos();
                break;
            case 0:
                limpiarPantalla();
                mostrarMensaje("Saliendo del programa.");
                break;
            default:
                limpiarPantalla();
                mostrarMensaje("Opcion no valida. Intente de nuevo.");
        }
        pausarConsola();
    } while (opcion != 0);

    return 0;
}

