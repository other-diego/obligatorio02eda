// Programa principal: lee comandos de la entrada estándar, uno por línea,
// separa el comando de sus argumentos y llama a las operaciones de library.hpp.
// No conoce ningún otro módulo ni sus nodos.
//
// Compilar: g++ -std=c++17 -Wall -Wextra -o biblioteca *.cpp
// Usar:     ./biblioteca < entrada.txt > salida.txt

#include "library.hpp"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// El comando con más argumentos (LIBRO_ALTA) usa 5 palabras en total.
const int MAX_PALABRAS = 6;

// Convierte el texto en entero. Devuelve false si no es un entero válido.
// Acepta un '-' inicial para que library informe el error de rango.
// Se limitan los dígitos a 9 para no desbordar un int.
static bool leer_entero(const string& texto, int& valor) {
    size_t i = 0;
    bool negativo = false;
    if (i < texto.size() && texto[i] == '-') {
        negativo = true;
        i++;
    }
    if (i == texto.size() || texto.size() - i > 9) {
        return false;
    }

    int resultado = 0;
    for (; i < texto.size(); i++) {
        if (texto[i] < '0' || texto[i] > '9') {
            return false;
        }
        resultado = resultado * 10 + (texto[i] - '0');
    }

    valor = negativo ? -resultado : resultado;
    return true;
}

static void error_argumentos(const string& comando) {
    cout << "ERROR argumentos invalidos para " << comando << '\n';
}

// Ejecuta un comando ya separado en palabras (palabras[0] es el comando).
static void ejecutar(Library* biblioteca, const string palabras[], int argumentos) {
    const string& comando = palabras[0];
    int a = 0;
    int b = 0;

    if (comando == "LIBRO_ALTA") {
        if (argumentos != 4 || !leer_entero(palabras[1], a) || !leer_entero(palabras[2], b)) {
            error_argumentos(comando);
            return;
        }
        library_add_book(biblioteca, a, b, palabras[3], palabras[4]);
    } else if (comando == "LIBRO_BAJA") {
        if (argumentos != 1 || !leer_entero(palabras[1], a)) {
            error_argumentos(comando);
            return;
        }
        library_remove_book(biblioteca, a);
    } else if (comando == "LIBRO_VER") {
        if (argumentos != 1 || !leer_entero(palabras[1], a)) {
            error_argumentos(comando);
            return;
        }
        library_show_book(biblioteca, a);
    } else if (comando == "CATALOGO") {
        if (argumentos != 0) {
            error_argumentos(comando);
            return;
        }
        library_print_catalog(biblioteca);
    } else if (comando == "AUTOR") {
        if (argumentos != 1) {
            error_argumentos(comando);
            return;
        }
        library_print_author(biblioteca, palabras[1]);
    } else if (comando == "SOCIO_ALTA") {
        if (argumentos != 2 || !leer_entero(palabras[1], a)) {
            error_argumentos(comando);
            return;
        }
        library_add_member(biblioteca, a, palabras[2]);
    } else if (comando == "SOCIO_BAJA") {
        if (argumentos != 1 || !leer_entero(palabras[1], a)) {
            error_argumentos(comando);
            return;
        }
        library_remove_member(biblioteca, a);
    } else if (comando == "SOCIOS") {
        if (argumentos != 0) {
            error_argumentos(comando);
            return;
        }
        library_print_members(biblioteca);
    } else if (comando == "PRESTAR") {
        if (argumentos != 2 || !leer_entero(palabras[1], a) || !leer_entero(palabras[2], b)) {
            error_argumentos(comando);
            return;
        }
        library_lend(biblioteca, a, b);
    } else if (comando == "DEVOLVER") {
        if (argumentos != 2 || !leer_entero(palabras[1], a) || !leer_entero(palabras[2], b)) {
            error_argumentos(comando);
            return;
        }
        library_give_back(biblioteca, a, b);
    } else if (comando == "HISTORIAL") {
        if (argumentos != 1 || !leer_entero(palabras[1], a)) {
            error_argumentos(comando);
            return;
        }
        library_print_history(biblioteca, a);
    } else if (comando == "ESTADISTICAS") {
        if (argumentos != 0) {
            error_argumentos(comando);
            return;
        }
        library_print_stats(biblioteca);
    } else {
        cout << "ERROR comando desconocido " << comando << '\n';
    }
}

int main() {
    Library* biblioteca = library_create();
    string linea;

    while (getline(cin, linea)) {
        istringstream entrada(linea);
        string palabras[MAX_PALABRAS];
        int cantidad = 0;
        string palabra;

        while (entrada >> palabra) {
            if (cantidad < MAX_PALABRAS) {
                palabras[cantidad] = palabra;
            }
            cantidad++;
        }

        if (cantidad == 0) {
            continue;  // línea vacía: se ignora
        }

        int argumentos = cantidad - 1;
        if (palabras[0] == "FIN") {
            if (argumentos == 0) {
                break;
            }
            error_argumentos(palabras[0]);
            continue;
        }

        if (cantidad > MAX_PALABRAS) {
            error_argumentos(palabras[0]);
            continue;
        }

        ejecutar(biblioteca, palabras, argumentos);
    }

    // FIN, o fin de la entrada sin FIN: se libera toda la memoria igual.
    library_destroy(biblioteca);
    return 0;
}
