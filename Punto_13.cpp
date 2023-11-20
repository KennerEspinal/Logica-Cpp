#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Libro {
    int referencia;
    string titulo;
    string autor;
    int numEjemplares;
    Libro* izquierda;
    Libro* derecha;

    Libro(int referencia, const string& titulo, const string& autor, int numEjemplares)
        : referencia(referencia), titulo(titulo), autor(autor), numEjemplares(numEjemplares), izquierda(NULL), derecha(NULL) {}
};

class ArbolBinarioLibros {
private:
    Libro* raiz;

    Libro* insertar(Libro* libro, int referencia, const string& titulo, const string& autor, int numEjemplares) {
        if (libro == NULL) {
            return new Libro(referencia, titulo, autor, numEjemplares);
        }

        if (referencia < libro->referencia) {
            libro->izquierda = insertar(libro->izquierda, referencia, titulo, autor, numEjemplares);
        } else if (referencia > libro->referencia) {
            libro->derecha = insertar(libro->derecha, referencia, titulo, autor, numEjemplares);
        }

        return libro;
    }

    void listarLibros(Libro* libro) {
        if (libro != NULL) {
            listarLibros(libro->izquierda);
            cout << "Referencia: " << libro->referencia << ", Titulo: " << libro->titulo
                 << ", Autor: " << libro->autor << ", Ejemplares: " << libro->numEjemplares << endl;
            listarLibros(libro->derecha);
        }
    }

    Libro* buscarPorReferencia(Libro* libro, int referencia) {
        if (libro == NULL || libro->referencia == referencia) {
            return libro;
        }

        if (referencia < libro->referencia) {
            return buscarPorReferencia(libro->izquierda, referencia);
        } else {
            return buscarPorReferencia(libro->derecha, referencia);
        }
    }

public:
    ArbolBinarioLibros() : raiz(NULL) {}

    void insertar(int referencia, const string& titulo, const string& autor, int numEjemplares) {
        raiz = insertar(raiz, referencia, titulo, autor, numEjemplares);
    }

    void listarLibros() {
        cout << "\nListado de Libros:\n";
        listarLibros(raiz);
    }

    Libro* buscarPorReferencia(int referencia) {
        return buscarPorReferencia(raiz, referencia);
    }
};

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausarConsola() {
    cout << "Presiona Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void mostrarMenu() {
    cout << "\nMenu:\n";
    cout << "1. Registrar Libro\n";
    cout << "2. Listar Libros\n";
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

int obtenerReferencia() {
    int referencia;
    cout << "Ingrese la referencia: ";
    cin >> referencia;
    return referencia;
}

string obtenerTexto(const string& mensaje) {
    string texto;
    cout << mensaje;
    cin.ignore();
    getline(cin, texto);
    return texto;
}

int obtenerNumeroEjemplares() {
    int numEjemplares;
    cout << "Ingrese el numero de ejemplares: ";
    cin >> numEjemplares;
    return numEjemplares;
}

int main() {
    ArbolBinarioLibros arbolLibros;

    int opcion;
    do {
        limpiarPantalla();
        mostrarMenu();
        opcion = obtenerOpcion();

        switch (opcion) {
            case 1: {
                limpiarPantalla();
                int referencia = obtenerReferencia();

                // Verificar si la referencia ya existe en el árbol
                Libro* existente = arbolLibros.buscarPorReferencia(referencia);
                if (existente != NULL) {
                    mostrarMensaje("Error: Ya existe un libro con esa referencia.");
                    break;
                }

                string titulo = obtenerTexto("Ingrese el titulo: ");
                string autor = obtenerTexto("Ingrese el autor: ");
                int numEjemplares = obtenerNumeroEjemplares();

                arbolLibros.insertar(referencia, titulo, autor, numEjemplares);
                mostrarMensaje("Libro registrado exitosamente.");
                break;
            }
            case 2:
                limpiarPantalla();
                arbolLibros.listarLibros();
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

