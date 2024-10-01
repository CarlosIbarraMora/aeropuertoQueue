#include <stdio.h>
#include <stdlib.h>

#define NUM_PISTAS 3 // Cantidad de pistas disponibles
#define MAX_COLA 10  // Tamaño máximo de la cola de espera

// Estructura para representar una aeronave
typedef struct Aeronave {
    int id;
} Aeronave;

// Estructura para manejar la cola de espera
typedef struct Cola {
    Aeronave *aeronaves[MAX_COLA];
    int front;
    int rear;
} Cola;

// Función para inicializar la cola
void inicializarCola(Cola *cola) {
    cola->front = -1;
    cola->rear = -1;
}

// Función para verificar si la cola está vacía
int estaVacia(Cola *cola) {
    return cola->front == -1;
}

// Función para verificar si la cola está llena
int estaLlena(Cola *cola) {
    return (cola->rear + 1) % MAX_COLA == cola->front;
}

// Función para encolar una aeronave
void enQueue(Cola *cola, Aeronave *aeronave) {
    if (estaLlena(cola)) {
        printf("La cola de espera está llena.\n");
        return;
    }
    if (estaVacia(cola)) {
        cola->front = 0;
    }
    cola->rear = (cola->rear + 1) % MAX_COLA;
    cola->aeronaves[cola->rear] = aeronave;
    printf("Aeronave %d agregada a la cola de espera.\n", aeronave->id);
}

// Función para desencolar una aeronave
Aeronave* deQueue(Cola *cola) {
    if (estaVacia(cola)) {
        printf("La cola de espera está vacía.\n");
        return NULL;
    }
    Aeronave *aeronave = cola->aeronaves[cola->front];
    if (cola->front == cola->rear) {
        cola->front = -1; // La cola está vacía
        cola->rear = -1;
    } else {
        cola->front = (cola->front + 1) % MAX_COLA;
    }
    return aeronave;
}

// Función para registrar una aeronave en una pista
void asignarPista(Aeronave *aeronave, int *pistas, Cola *cola) {
    for (int i = 0; i < NUM_PISTAS; i++) {
        if (pistas[i] == -1) { // Pista libre
            pistas[i] = aeronave->id;
            printf("Aeronave %d asignada a la pista %d.\n", aeronave->id, i + 1);
            return;
        }
    }
    // Si no hay pistas disponibles, encolar la aeronave
    enQueue(cola, aeronave);
}

// Función para liberar una pista
void liberarPista(int pista, int *pistas, Cola *cola) {
    printf("Liberando pista %d.\n", pista + 1);
    pistas[pista] = -1; // Marcar la pista como libre
    if (!estaVacia(cola)) {
        Aeronave *aeronave = deQueue(cola);
        if (aeronave != NULL) {
            pistas[pista] = aeronave->id; // Asignar la pista liberada
            printf("Aeronave %d asignada a la pista %d desde la cola.\n", aeronave->id, pista + 1);
        }
    }
}

int main() {
    // Inicializamos las pistas y la cola de espera
    int pistas[NUM_PISTAS] = {-1, -1, -1}; // Pistas vacías (-1 indica pista libre)
    Cola cola;
    inicializarCola(&cola);

    // Simulación de llegada de aeronaves
    Aeronave a1 = {1}, a2 = {2}, a3 = {3}, a4 = {4}, a5 = {5};

    asignarPista(&a1, pistas, &cola); // Asignar aeronave 1
    asignarPista(&a2, pistas, &cola); // Asignar aeronave 2
    asignarPista(&a3, pistas, &cola); // Asignar aeronave 3
    asignarPista(&a4, pistas, &cola); // Aeronave 4 a la cola (pistas ocupadas)
    asignarPista(&a5, pistas, &cola); // Aeronave 5 a la cola

    liberarPista(1, pistas, &cola); // Liberar pista 2
    liberarPista(0, pistas, &cola); // Liberar pista 1

    return 0;
}