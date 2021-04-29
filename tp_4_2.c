#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Tarea {
    int TareaID; //Numerada en ciclo iterativo
    char * Descripcion;
    int Duracion; //entre 10 - 100
} Tarea;

void CargarTareas(Tarea ** ListaDeTareas, Tarea ** TareasRealizadas, int CantTareas);
void MoverRealizadas(Tarea ** ListaDeTareas, Tarea ** TareasRealizadas, int CantTareas);
void ListarTareas(Tarea ** ListaDeTareas, Tarea ** TareasRealizadas, int CantTareas);
Tarea BusquedaPorPalabra(Tarea * Lista, char * palabra, int CantTareas);
Tarea BusquedaPorID(Tarea * Lista, int ID, int CantTareas);

int main () {
    char PalabraClave[MAX/5];
    int CantTareas, ID;
    Tarea ** ToDo, ** Realizadas, buscada1, buscada2;

    printf("Cuantas tareas desea ingresar?\n");
    scanf("%d", &CantTareas);
    fflush(stdin);
    ToDo = (Tarea **) malloc(sizeof(Tarea*) * CantTareas);
    Realizadas = (Tarea **) malloc(sizeof(Tarea*) * CantTareas);

    CargarTareas(ToDo, Realizadas, CantTareas);
    ListarTareas(ToDo, Realizadas, CantTareas);
    MoverRealizadas(ToDo, Realizadas, CantTareas);
    ListarTareas(ToDo, Realizadas, CantTareas);

    printf("\nIngrese una palabra para buscar una tarea:\n");
    fflush(stdin);
    gets(PalabraClave);
    buscada1 = BusquedaPorPalabra(*ToDo, PalabraClave, CantTareas);

    printf("\nIngrese un ID (numero entero) para buscar una tarea:\n");
    scanf("%d", &ID);
    buscada2 = BusquedaPorID(*ToDo, ID, CantTareas);

    for (int i = 0; i < CantTareas; i++)
    {
        if (ToDo[i] != NULL)
        {
            free(ToDo[i]->Descripcion);
            free(ToDo[i]);
        } else
        {
            free(Realizadas[i]->Descripcion);
            free(Realizadas[i]);
        } //if end
    }//for end

    free(ToDo);
    free(Realizadas);

    getchar();
    return 0;
}

void CargarTareas(Tarea ** ListaDeTareas, Tarea ** TareasRealizadas, int CantTareas) {
    for (int i = 0; i < CantTareas; i++)
    {
        ListaDeTareas[i] = (Tarea *) malloc(sizeof(Tarea));
        ListaDeTareas[i]->TareaID = i + 1;
        ListaDeTareas[i]->Descripcion = (char*) malloc(sizeof(char) * MAX);
        printf("Ingrese una breve descripcion de la tarea:\n");
        gets(ListaDeTareas[i]->Descripcion);
        ListaDeTareas[i]->Duracion = 10 + rand() % 91;
        TareasRealizadas[i] = NULL;
    } //for end
}

void MoverRealizadas(Tarea ** ListaDeTareas, Tarea ** TareasRealizadas, int CantTareas) {
    int check;

    printf("\n---------- Tareas Pendientes ----------\n");
    for (int i = 0; i < CantTareas; i++)
    {
        if (*(ListaDeTareas + i) != NULL)
        {
            printf("----------------------------------------\n");
            printf("Tarea ID: %d\n", ListaDeTareas[i]->TareaID);
            printf("Descripcion: %s\n", ListaDeTareas[i]->Descripcion);
            printf("Duracion: %d\n", ListaDeTareas[i]->Duracion);
            printf("\n----- Mover a realizadas? (1 = SI; 0 = NO)-----\n");
            scanf("%d", &check);

            if (check == 1)
            {
                *(TareasRealizadas + i) = *(ListaDeTareas + i);
                *(ListaDeTareas + i) = NULL;
            } //if end        
        } //if end
    } //for end    
}

void ListarTareas(Tarea ** ListaDeTareas, Tarea ** TareasRealizadas, int CantTareas) {
    
    printf("\n---------- TAREAS REALIZADAS ----------\n");
    for (int i = 0; i < CantTareas; i++)
    {
        if (TareasRealizadas[i] != NULL)
        {
            printf("----------------------------------------\n");
            printf("Tarea ID: %d\n", TareasRealizadas[i]->TareaID);
            printf("Descripcion: %s\n", TareasRealizadas[i]->Descripcion);
            printf("Duracion: %d\n", TareasRealizadas[i]->Duracion);
        } //if end
    } //for end

    printf("\n---------- TAREAS PENDIENTES ----------\n");
    for (int i = 0; i < CantTareas; i++)
    {
        if (ListaDeTareas[i] != NULL)
        {
            printf("----------------------------------------\n");
            printf("Tarea ID: %d\n", ListaDeTareas[i]->TareaID);
            printf("Descripcion: %s\n", ListaDeTareas[i]->Descripcion);
            printf("Duracion: %d\n", ListaDeTareas[i]->Duracion);
        } //if end 
    } //for end    
}

Tarea BusquedaPorPalabra(Tarea * Lista, char * palabra, int CantTareas) {
    for (int i = 0; i < CantTareas; i++)
    {
        if ((Lista + i) != NULL && strstr(Lista[i].Descripcion, palabra))
        {
            printf("\n------- TAREA ENCONTRADA -------\n");
            printf("Tarea ID: %d\n", Lista[i].TareaID);
            printf("Descripcion: %s\n", Lista[i].Descripcion);
            printf("Duracion: %d\n", Lista[i].Duracion);
            return *(Lista + i);
        } //if end
    } //for end
}

Tarea BusquedaPorID(Tarea * Lista, int ID, int CantTareas) {
    for (int i = 0; i < CantTareas; i++)
    {
        if ((Lista + i) != NULL && (Lista + i)->TareaID == ID)
        {
            printf("\n------- TAREA ENCONTRADA -------\n");
            printf("Tarea ID: %d\n", Lista[i].TareaID);
            printf("Descripcion: %s\n", Lista[i].Descripcion);
            printf("Duracion: %d\n", Lista[i].Duracion);
            return *(Lista + i);
        } //if end
    } //for end
}