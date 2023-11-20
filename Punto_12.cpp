#include <iostream>
#include <string>
#include <limits> 
#include <cstdlib> 

using namespace std;

struct Persona {
    int cedula;
    string nombre;
    int edad;
    char tipoViolencia;
    Persona* izquierda;
    Persona* derecha;

    Persona(int cedula, const string& nombre, int edad, char tipoViolencia)
        : cedula(cedula), nombre(nombre), edad(edad), tipoViolencia(tipoViolencia), izquierda(NULL), derecha(NULL) {}
};

class ArbolBinario {
private:
    Persona* raiz;

    Persona* insertar(Persona* persona, int cedula, const string& nombre, int edad, char tipoViolencia) {
        if (persona == NULL) {
            return new Persona(cedula, nombre, edad, tipoViolencia);
        }

        if (cedula < persona->cedula) {
            persona->izquierda = insertar(persona->izquierda, cedula, nombre, edad, tipoViolencia);
        } else if (cedula > persona->cedula) {
            persona->derecha = insertar(persona->derecha, cedula, nombre, edad, tipoViolencia);
        }

        return persona;
    }

    void listarPersonas(Persona* persona) {
        if (persona != NULL) {
            listarPersonas(persona->izquierda);
            cout << "Cedula: " << persona->cedula << ", Nombre: " << persona->nombre
                 << ", Edad: " << persona->edad << ", Tipo de Violencia: " << persona->tipoViolencia << endl;
            listarPersonas(persona->derecha);
        }
    }

    int calcularPromedioPorTipoViolencia(Persona* persona, char tipoViolencia, int& totalPersonas) {
        if (persona == NULL) {
            return 0;
        }

        int cantidadIzquierda = calcularPromedioPorTipoViolencia(persona->izquierda, tipoViolencia, totalPersonas);
        int cantidadDerecha = calcularPromedioPorTipoViolencia(persona->derecha, tipoViolencia, totalPersonas);

        if (persona->tipoViolencia == tipoViolencia) {
            totalPersonas++;
        }

        return cantidadIzquierda + cantidadDerecha + 1;
    }

public:
    ArbolBinario() : raiz(NULL) {}

    void insertar(int cedula, const string& nombre, int edad, char tipoViolencia) {
        raiz = insertar(raiz, cedula, nombre, edad, tipoViolencia);
    }

    void listarPersonas() {
        listarPersonas(raiz);
    }

    void calcularPromedioPorTipoViolencia() {
        int totalPersonasPsicologica = 0;
        int totalPersonasFisica = 0;
        int totalPersonasAbusoSexual = 0;

        int cantidadPsicologica = calcularPromedioPorTipoViolencia(raiz, 'S', totalPersonasPsicologica);
        int cantidadFisica = calcularPromedioPorTipoViolencia(raiz, 'F', totalPersonasFisica);
        int cantidadAbusoSexual = calcularPromedioPorTipoViolencia(raiz, 'A', totalPersonasAbusoSexual);

        cout << "\nPromedio de Personas por Tipo de Violencia:\n";
        cout << "Psicologica: " << static_cast<double>(totalPersonasPsicologica) / cantidadPsicologica << " personas en promedio\n";
        cout << "Fisica: " << static_cast<double>(totalPersonasFisica) / cantidadFisica << " personas en promedio\n";
        cout << "Abuso Sexual: " << static_cast<double>(totalPersonasAbusoSexual) / cantidadAbusoSexual << " personas en promedio\n";
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
    cout << "1. Crear Persona\n";
    cout << "2. Listar Personas\n";
    cout << "3. Calcular Promedio por Tipo de Violencia\n";
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

int obtenerEdad() {
    int edad;
    cout << "Ingrese la edad: ";
    cin >> edad;
    return edad;
}

char obtenerTipoViolencia() {
    char tipoViolencia;
    cout << "Ingrese el tipo de violencia (S: Psicologica, F: Fisica, A: Abuso Sexual): ";
    cin >> tipoViolencia;

    tipoViolencia = toupper(tipoViolencia);

    return tipoViolencia;
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
                int edad = obtenerEdad();
                char tipoViolencia = obtenerTipoViolencia();

                arbol.insertar(cedula, nombre, edad, tipoViolencia);
                mostrarMensaje("Persona creada exitosamente.");
                break;
            }
            case 2:
                limpiarPantalla();
                cout << "\nListado de Personas:\n";
                arbol.listarPersonas();
                break;
            case 3:
                limpiarPantalla();
                arbol.calcularPromedioPorTipoViolencia();
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

