#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char descripcion[4][MAX] = 
{
    "Tarea uno",
    "Tarea dos",
    "Tarea tres",
    "Tarea cuatro"
};

typedef struct Tarea
{
    int TareaID; //Numerada en ciclo iterativo
    char *Descripcion;
    int Duracion; //entre 10 - 100
} Tarea;

typedef struct nodo
{
    Tarea T;
    struct nodo *siguiente;
} nodo;

//Operaciones de la lista enlazada
nodo * crearListaVacia();
nodo * crearNodo(Tarea T);
void insertarNodo(nodo ** start, nodo * nodoLibre);
//---------------------------------------------------

void CargarTareas(nodo ** ToDo, int CantTareas);
void MoverRealizadas(nodo ** ToDo, nodo ** realizadas);
void mostrarTarea(Tarea T);
void ListarTareas(nodo * toDo, nodo * realizadas);
nodo BusquedaPorPalabra(nodo * listaDeTareas, char * palabra);
nodo BusquedaPorID(nodo * listaDeTareas, int ID);
void liberarMemoria(nodo * listaDeTareas);

int main()
{
    char PalabraClave[MAX/5];
    int CantTareas = 4, ID;
    nodo * ToDo, * realizadas; //Cabeceras de las listas
    nodo buscada1, buscada2;

    //Crear las dos listas vacías
    ToDo = crearListaVacia();
    realizadas = crearListaVacia();

    //Cargar tareas en lista ToDo

    // printf("Cuantas tareas desea ingresar?\n");
    // scanf("%d", &CantTareas);
    CargarTareas(&ToDo, CantTareas);
    
    // MoverRealizadas(&ToDo, &realizadas);
    ListarTareas(ToDo, realizadas);

    // printf("\nIngrese una palabra para buscar una tarea:\n");
    // fflush(stdin);
    // gets(PalabraClave);

    //Casos de prueba para las funciones de búsqueda
    printf("\nBusqueda por palabra:\n");
    buscada1 = BusquedaPorPalabra(ToDo, "prueba");
    buscada1 = BusquedaPorPalabra(ToDo, "tres");    

    // printf("\nIngrese un ID (numero entero) para buscar una tarea:\n");
    // scanf("%d", &ID);

    printf("\nBusqueda por ID:\n");
    buscada2 = BusquedaPorID(ToDo, 8);
    buscada2 = BusquedaPorID(ToDo, 1);

    //Liberar memoria
    liberarMemoria(ToDo);
    liberarMemoria(realizadas);

    getchar();
    return 0;
}

nodo * crearListaVacia()
{
    return NULL;
}

nodo * crearNodo(Tarea T)
{
    nodo * nuevoNodo = (nodo *) malloc(sizeof(nodo));

    nuevoNodo->T = T;
    nuevoNodo->siguiente = NULL;

    return nuevoNodo;
}

void insertarNodo(nodo ** start, nodo * nodoLibre)
{
    if (start)
    {
        nodoLibre->siguiente = * start;
        * start = nodoLibre;
    } else
    {
        * start = nodoLibre;
    }
}

void mostrarTarea(Tarea T)
{
    printf("Tarea ID: %d\n", T.TareaID);
    printf("Descripcion: %s\n", T.Descripcion);
    printf("Duracion: %d\n", T.Duracion);
}

void CargarTareas(nodo ** ToDo, int CantTareas)
{
    Tarea tareaNueva;
    nodo *nuevoNodo;

    for (int i = 0; i < CantTareas; i++)
    {
        tareaNueva.TareaID = i + 1;
        tareaNueva.Descripcion = (char *)malloc(sizeof(char) * MAX);
        // printf("Ingrese una breve descripcion de la tarea:\n");
        // fflush(stdin);
        // gets(tareaNueva.Descripcion);
        strcpy(tareaNueva.Descripcion, descripcion[i]);
        tareaNueva.Duracion = 10 + rand() % 91;

        nuevoNodo = crearNodo(tareaNueva);

        insertarNodo(ToDo, nuevoNodo);
    }
}

void MoverRealizadas(nodo ** ToDo, nodo ** realizadas)
{
    int check;
    nodo * nodoAux = * ToDo, * nodoAnterior = NULL;

    printf("\n---------- Tareas Pendientes ----------\n");

    while (nodoAux != NULL)
    {
        mostrarTarea(nodoAux->T);

        printf("\n----- Mover a realizadas? (1 = SI; 0 = NO)-----\n");
        scanf("%d", &check);

        if (check == 1)
        {
            if (nodoAnterior == NULL)
            {
                * ToDo = nodoAux->siguiente;
                insertarNodo(realizadas, nodoAux);                
                nodoAux = * ToDo;
            } else
            {
                nodoAnterior->siguiente = nodoAux->siguiente;
                insertarNodo(realizadas, nodoAux);
                nodoAux = nodoAnterior->siguiente;
            } //if end
        } else
        {
            nodoAnterior = nodoAux;
            nodoAux = nodoAux->siguiente;
        } //if end
        
    } //while end
}

void ListarTareas(nodo * toDo, nodo * realizadas) {
    
    printf("\n---------- TAREAS REALIZADAS ----------\n");
    while (realizadas != NULL)
    {
        printf("----------------------------------------\n");
        mostrarTarea(realizadas->T);
        realizadas = realizadas->siguiente;
        printf("----------------------------------------\n");
    }
    
    printf("\n---------- TAREAS PENDIENTES ----------\n");
    while (toDo != NULL)
    {
        printf("----------------------------------------\n");
        mostrarTarea(toDo->T);
        toDo = toDo->siguiente;
        printf("----------------------------------------\n");
    }    
}

nodo BusquedaPorPalabra(nodo * listaDeTareas, char * palabra) {
    nodo aux;

    while (listaDeTareas != NULL)
    {
        if (strstr(listaDeTareas->T.Descripcion, palabra))
        {
            printf("\n---------- TAREA ENCONTRADA ----------\n");
            mostrarTarea(listaDeTareas->T);
            printf("----------------------------------------\n");
            aux = *listaDeTareas;
            aux.siguiente = NULL;
            return aux;
        } //if end
        listaDeTareas = listaDeTareas->siguiente;
    } //while end
    
    printf("\nNo se encontraron coincidencias con la palabra ingresada\n");
}

nodo BusquedaPorID(nodo * listaDeTareas, int ID) {
    nodo aux;

    while (listaDeTareas != NULL)
    {
        if (listaDeTareas->T.TareaID == ID)
        {
            printf("\n---------- TAREA ENCONTRADA ----------\n");
            mostrarTarea(listaDeTareas->T);
            printf("----------------------------------------\n");
            aux = *listaDeTareas;
            aux.siguiente = NULL;
            return aux;
        } //if end
        listaDeTareas = listaDeTareas->siguiente;
    } //while end

    printf("\nNo se encontraron coincidencias con el ID ingresado\n");
}

void liberarMemoria(nodo * listaDeTareas) {
    nodo * aux;

    while (listaDeTareas != NULL)
    {
        aux = listaDeTareas;
        listaDeTareas = listaDeTareas->siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }    
}