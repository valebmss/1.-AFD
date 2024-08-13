#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ESTADOS 100
#define MAX_SIMBOLOS 100

// Estructura para representar una transición
typedef struct {
    char *estadoActual;
    char simbolo;
    char *estadoSiguiente;
} Transicion;

// Estructura para representar el DFA
typedef struct {
    char *estados[MAX_ESTADOS];
    char simbolos[MAX_SIMBOLOS];
    char *estadoInicial;
    char *estadosAceptacion[MAX_ESTADOS];
    Transicion transiciones[MAX_ESTADOS * MAX_SIMBOLOS];
    int numEstados;
    int numSimbolos;
    int numEstadosAceptacion;
    int numTransiciones;
} DFA;

// Función para duplicar una cadena
char *duplicate_string(const char *str) {
    char *copy = malloc(strlen(str) + 1); // +1 para el carácter nulo
    if (copy == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    strcpy(copy, str);
    return copy;
}

// Función para cargar la configuración del DFA desde un archivo
void cargarConfiguracionDFA(DFA *dfa) {
    const char *nombreArchivo = "./config.txt";
    printf("Loading configuration from %s...\n", nombreArchivo);

    FILE *archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        perror("Error al abrir el archivo de configuración");
        exit(EXIT_FAILURE);
    }

    char buffer[256];

    // Leer los estados
    if (fgets(buffer, sizeof(buffer), archivo)) {
        printf("Estados: %s\n", buffer);
        char *token = strtok(buffer, ",\n");
        while (token) {
            dfa->estados[dfa->numEstados++] = duplicate_string(token);
            token = strtok(NULL, ",\n");
        }
    } else {
        perror("Error al leer los estados");
        exit(EXIT_FAILURE);
    }

    // Leer el alfabeto (símbolos)
    if (fgets(buffer, sizeof(buffer), archivo)) {
        printf("Símbolos: %s\n", buffer);
        char *token = strtok(buffer, ",\n");
        while (token) {
            dfa->simbolos[dfa->numSimbolos++] = token[0];
            token = strtok(NULL, ",\n");
        }
    } else {
        perror("Error al leer los símbolos");
        exit(EXIT_FAILURE);
    }

    // Leer el estado inicial
    if (fgets(buffer, sizeof(buffer), archivo)) {
        buffer[strcspn(buffer, "\n")] = 0;
        printf("Estado inicial: %s\n", buffer);
        dfa->estadoInicial = duplicate_string(buffer);
    } else {
        perror("Error al leer el estado inicial");
        exit(EXIT_FAILURE);
    }

    // Leer los estados de aceptación
    if (fgets(buffer, sizeof(buffer), archivo)) {
        printf("Estados de aceptación: %s\n", buffer);
        char *token = strtok(buffer, ",\n");
        while (token) {
            dfa->estadosAceptacion[dfa->numEstadosAceptacion++] = duplicate_string(token);
            token = strtok(NULL, ",\n");
        }
    } else {
        perror("Error al leer los estados de aceptación");
        exit(EXIT_FAILURE);
    }

    // Leer las transiciones
// Leer las transiciones
while (fgets(buffer, sizeof(buffer), archivo)) {
    // Saltar líneas vacías
    if (buffer[0] == '\n' || buffer[0] == '\0') {
        continue;
    }

    Transicion t;
    printf("Transición: %s\n", buffer);
    char *token = strtok(buffer, ",\n");
    if (token == NULL) {
        printf("Advertencia: Se encontró una línea vacía en las transiciones.\n");
        continue;
    }
    t.estadoActual = duplicate_string(token);

    token = strtok(NULL, ",\n");
    if (token == NULL) {
        perror("Error al leer el símbolo de la transición");
        exit(EXIT_FAILURE);
    }
    t.simbolo = token[0];

    token = strtok(NULL, ",\n");
    if (token == NULL) {
        perror("Error al leer el estado siguiente de la transición");
        exit(EXIT_FAILURE);
    }
    t.estadoSiguiente = duplicate_string(token);

    dfa->transiciones[dfa->numTransiciones++] = t;
}

    fclose(archivo);
}
// Función para obtener el siguiente estado dado un estado actual y un símbolo
char* obtenerEstadoSiguiente(DFA *dfa, const char *estadoActual, char simbolo) {
    for (int i = 0; i < dfa->numTransiciones; i++) {
        if (strcmp(dfa->transiciones[i].estadoActual, estadoActual) == 0 &&
            dfa->transiciones[i].simbolo == simbolo) {
            return dfa->transiciones[i].estadoSiguiente;
        }
    }
    return NULL; // Si no se encuentra una transición válida
}

// Función para procesar una cadena de entrada y determinar si es aceptada
int procesarCadena(DFA *dfa, const char *entrada) {
    char *estadoActual = dfa->estadoInicial;

    for (int i = 0; entrada[i] != '\0'; i++) {
        estadoActual = obtenerEstadoSiguiente(dfa, estadoActual, entrada[i]);
        if (!estadoActual) {
            return 0; // Rechazar si no hay una transición válida
        }
    }

    // Verificar si el estado final es un estado de aceptación
    for (int i = 0; i < dfa->numEstadosAceptacion; i++) {
        if (strcmp(estadoActual, dfa->estadosAceptacion[i]) == 0) {
            return 1; // Aceptar si es un estado de aceptación
        }
    }

    return 0; // Rechazar si no es un estado de aceptación
}

// Función principal
int main() {
    DFA dfa = {0};




    cargarConfiguracionDFA(&dfa);

    char entrada[256];
    printf("Ingrese la cadena de entrada: ");
    scanf("%s", entrada);

    if (procesarCadena(&dfa, entrada)) {
        printf("Resultado: La cadena fue aceptada.\n");
    } else {
        printf("Resultado: La cadena fue rechazada.\n");
    }

    // Liberar memoria
    for (int i = 0; i < dfa.numEstados; i++) {
        free(dfa.estados[i]);
    }
    for (int i = 0; i < dfa.numEstadosAceptacion; i++) {
        free(dfa.estadosAceptacion[i]);
    }
    for (int i = 0; i < dfa.numTransiciones; i++) {
        free(dfa.transiciones[i].estadoActual);
        free(dfa.transiciones[i].estadoSiguiente);
    }

    return 0;
}

