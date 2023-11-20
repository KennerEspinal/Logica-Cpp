#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Beneficiario {
    int cedula;
    string nombre;
    string numCuentaBancaria;
    string numTelefono;
    Beneficiario* izquierda;
    Beneficiario* derecha;

    Beneficiario(int cedula, const string& nombre, const string& numCuentaBancaria, const string& numTelefono)
        : cedula(cedula), nombre(nombre), numCuentaBancaria(numCuentaBancaria), numTelefono(numTelefono), izquierda(NULL), derecha(NULL) {}
};

class ArbolBinarioBeneficiarios {
private:
    Beneficiario* raiz;

    Beneficiario* insertar(Beneficiario* beneficiario, int cedula, const string& nombre, const string& numCuentaBancaria, const string& numTelefono) {
        if (beneficiario == NULL) {
            return new Beneficiario(cedula, nombre, numCuentaBancaria, numTelefono);
        }

        if (cedula < beneficiario->cedula) {
            beneficiario->izquierda = insertar(beneficiario->izquierda, cedula, nombre, numCuentaBancaria, numTelefono);
        } else if (cedula > beneficiario->cedula) {
            beneficiario->derecha = insertar(beneficiario->derecha, cedula, nombre, numCuentaBancaria, numTelefono);
        }

        return beneficiario;
    }

    void listarBeneficiarios(Beneficiario* beneficiario) {
        if (beneficiario != NULL) {
            listarBeneficiarios(beneficiario->izquierda);
            cout << "Cedula: " << beneficiario->cedula << ", Nombre: " << beneficiario->nombre
                 << ", Cuenta Bancaria: " << beneficiario->numCuentaBancaria << ", Telefono: " << beneficiario->numTelefono << endl;
            listarBeneficiarios(beneficiario->derecha);
        }
    }

    Beneficiario* buscarPorCedula(Beneficiario* beneficiario, int cedula) {
        if (beneficiario == NULL || beneficiario->cedula == cedula) {
            return beneficiario;
        }

        if (cedula < beneficiario->cedula) {
            return buscarPorCedula(beneficiario->izquierda, cedula);
        } else {
            return buscarPorCedula(beneficiario->derecha, cedula);
        }
    }

public:
    ArbolBinarioBeneficiarios() : raiz(NULL) {}

    void insertar(int cedula, const string& nombre, const string& numCuentaBancaria, const string& numTelefono) {
        raiz = insertar(raiz, cedula, nombre, numCuentaBancaria, numTelefono);
    }

    void listarBeneficiarios() {
        cout << "\nListado de Beneficiarios:\n";
        listarBeneficiarios(raiz);
    }

    Beneficiario* buscarPorCedula(int cedula) {
        return buscarPorCedula(raiz, cedula);
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
    cout << "1. Crear Beneficiario\n";
    cout << "2. Listar Beneficiarios\n";
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
    ArbolBinarioBeneficiarios arbolBeneficiarios;

    int opcion;
    do {
        limpiarPantalla();
        mostrarMenu();
        opcion = obtenerOpcion();

        switch (opcion) {
            case 1: {
                limpiarPantalla();
                int cedula = obtenerCedula();

                Beneficiario* existente = arbolBeneficiarios.buscarPorCedula(cedula);
                if (existente != NULL) {
                    mostrarMensaje("Error: Ya existe un beneficiario con esa cedula.");
                    break;
                }

                string nombre = obtenerTexto("Ingrese el nombre: ");
                string numCuentaBancaria = obtenerTexto("Ingrese el numero de cuenta bancaria: ");
                string numTelefono = obtenerTexto("Ingrese el numero de telefono: ");

                arbolBeneficiarios.insertar(cedula, nombre, numCuentaBancaria, numTelefono);
                mostrarMensaje("Beneficiario creado exitosamente.");
                break;
            }
            case 2:
                limpiarPantalla();
                arbolBeneficiarios.listarBeneficiarios();
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

