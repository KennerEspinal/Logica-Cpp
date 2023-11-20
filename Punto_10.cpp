#include <iostream>
#include <string>
#include <limits>  
#include <cstdlib> 

using namespace std;

struct Estudiante {
    int cedula;
    string nombre;
    char sexo;
    char programa;
    Estudiante* izquierda;
    Estudiante* derecha;

    Estudiante(int cedula, const string& nombre, char sexo, char programa)
        : cedula(cedula), nombre(nombre), sexo(sexo), programa(programa), izquierda(NULL), derecha(NULL) {}
};

class ArbolBinario {
private:
    Estudiante* raiz;

    Estudiante* insertar(Estudiante* nodo, int cedula, const string& nombre, char sexo, char programa) {
        if (nodo == NULL) {
            return new Estudiante(cedula, nombre, sexo, programa);
        }

        if (cedula < nodo->cedula) {
            nodo->izquierda = insertar(nodo->izquierda, cedula, nombre, sexo, programa);
        } else if (cedula > nodo->cedula) {
            nodo->derecha = insertar(nodo->derecha, cedula, nombre, sexo, programa);
        }

        return nodo;
    }

    void listarEstudiantes(Estudiante* nodo) {
        if (nodo != NULL) {
            listarEstudiantes(nodo->izquierda);
            cout << "Cedula: " << nodo->cedula << ", Nombre: " << nodo->nombre
                 << ", Sexo: " << nodo->sexo << ", Programa: " << nodo->programa << endl;
            listarEstudiantes(nodo->derecha);
        }
    }

    void listarPorSexo(Estudiante* nodo, char sexo) {
        if (nodo != NULL) {
            listarPorSexo(nodo->izquierda, sexo);
            if (nodo->sexo == sexo) {
                cout << "Cedula: " << nodo->cedula << ", Nombre: " << nodo->nombre
                     << ", Sexo: " << nodo->sexo << ", Programa: " << nodo->programa << endl;
            }
            listarPorSexo(nodo->derecha, sexo);
        }
    }

    void listarPorPrograma(Estudiante* nodo, char programa) {
        if (nodo != NULL) {
            listarPorPrograma(nodo->izquierda, programa);
            if (nodo->programa == programa) {
                cout << "Cedula: " << nodo->cedula << ", Nombre: " << nodo->nombre
                     << ", Sexo: " << nodo->sexo << ", Programa: " << nodo->programa << endl;
            }
            listarPorPrograma(nodo->derecha, programa);
        }
    }

public:
    ArbolBinario() : raiz(NULL) {}

    void insertar(int cedula, const string& nombre, char sexo, char programa) {
        raiz = insertar(raiz, cedula, nombre, sexo, programa);
    }

    void listarEstudiantes() {
        listarEstudiantes(raiz);
    }

    void listarPorSexo(char sexo) {
        cout << "\nListado de Estudiantes por Sexo '" << sexo << "':\n";
        listarPorSexo(raiz, sexo);
    }

    void listarPorPrograma(char programa) {
        cout << "\nListado de Estudiantes por Programa '" << programa << "':\n";
        listarPorPrograma(raiz, programa);
    }
};

void limpiarPantalla() {
#ifdef _WIN32
    system("cls"); // Limpiar la pantalla Windows
#else
    system("clear"); // Limpiar la pantalla tipo Unix
#endif
}

void pausarConsola() {
    cout << "Presiona Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void mostrarMenu() {
    cout << "\nMenu:\n";
    cout << "1. Crear Estudiante\n";
    cout << "2. Consultar por Sexo\n";
    cout << "3. Consultar por Programa\n";
    cout << "4. Listar Estudiantes\n";
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

char obtenerSexo() {
    char sexo;
    cout << "Ingrese el sexo (M -> (Masculino)/F -> (Femenino)): ";
    cin >> sexo;
    
    sexo = toupper(sexo);
    
    return sexo;
}

char obtenerPrograma() {
    char programa;
    cout << "Ingrese el programa de estudio (S -> (Sistema)/E -> (Electrónica)/A -> (Ambiental)/I -> (Agroindustrial)): ";
    cin >> programa;
    
    programa = toupper(programa);
    
    return programa;
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
                char sexo = obtenerSexo();
                char programa = obtenerPrograma();

                arbol.insertar(cedula, nombre, sexo, programa);
                mostrarMensaje("Estudiante creado exitosamente.");
                break;
            }
            case 2: {
                limpiarPantalla();
                char sexoConsulta = obtenerSexo();
                arbol.listarPorSexo(sexoConsulta);
                break;
            }
            case 3: {
                limpiarPantalla();
                char programaConsulta = obtenerPrograma();
                arbol.listarPorPrograma(programaConsulta);
                break;
            }
            case 4:
                limpiarPantalla();
                cout << "\nListado de Estudiantes:\n";
                arbol.listarEstudiantes();
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

