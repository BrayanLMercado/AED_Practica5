/*
Nombre: Brayan López Mercado
Matrícula: 1280838
Fecha De Entrega: 25 De Septiembre De 2024
Materia: Algoritmos y Estructura De promedios
Grupo: 552
Practica 5: Listas Doblemente Enlazadas
*/

#include <stdio.h>
#include <stdlib.h>

struct Nodo{
    int promedio;
    char* nombre;
    struct Nodo* sigCadena;
    struct Nodo* siguiente;
};

struct Nodo* crearNodo(char* nombre,int promedio);
struct Nodo** insertar(struct Nodo* inicio,struct Nodo* inicioCadena,char* nombre,int promedio);
struct Nodo** eliminar(struct Nodo* inicio,struct Nodo* inicioCadena,char* nombre);
void mostrarPorPromedio(struct Nodo* inicio);
void mostrarPorNombre(struct Nodo* inicio);
void menuOpciones();
int mystrCmp(char* str1, char* str2);
int buscarRepeticiones(struct Nodo* inicioCadena,char* nombre);

int main(){
    int opt=0;
    struct Nodo* inicio=NULL;
    struct Nodo* inicioCadena=NULL;
    struct Nodo** inicios=(struct Nodo**)malloc(2*sizeof(struct Nodo));
        do{
        menuOpciones();
        scanf("%d",&opt);
        switch(opt){
            case 1: // Insertar
                char* nombre=(char*)malloc(20);
                int promedio=0;
                printf("Nombre Del Alumno: ");
                scanf("%s",nombre);
                if(inicio==NULL){
                    printf("Promedio del alumno: ");
                    scanf("%d",&promedio);
                    inicio=crearNodo(nombre,promedio);
                    inicioCadena=inicio;
                }
                else{
                    if(buscarRepeticiones(inicioCadena,nombre))
                        printf("Ya Existe Un Alumno Con Ese Nombre\n");
                    else{
                        printf("Promedio del alumno: ");
                        scanf("%d",&promedio);
                        printf("\n");
                        inicios=insertar(inicio,inicioCadena,nombre,promedio);
                        inicio=inicios[0];
                        inicioCadena=inicios[1];
                    }
                }
                printf("\n");
                break;
            case 2:
                if(inicio!=NULL){
                    char* nombre=(char*)malloc(20);
                    printf("Escribe Nombre A Borrar: ");
                    scanf("%s",nombre);
                    printf("\n");
                    inicios=eliminar(inicio,inicioCadena,nombre);
                    inicio=inicios[0];
                    inicioCadena=inicios[1];
                }
                else    
                    printf("\nNo Hay Alumnos a Borrar\n");
                break;
            case 3:
                if(inicio!=NULL){
                    char* nombre=(char*)malloc(20);
                    printf("Escribe El Nombre Del Alumno a Modificar: ");
                    scanf("%s",nombre);
                    printf("Nuevo Promedio Del Alumno: ");
                    scanf("%d",&promedio);
                    printf("\n");
                    inicios=eliminar(inicio,inicioCadena,nombre);
                    inicios=insertar(inicios[0],inicios[1],nombre,promedio);
                    inicio=inicios[0];
                    inicioCadena=inicios[1];
                }
                break;
            case 4:
                mostrarPorNombre(inicioCadena);
                break;
            case 5:
                mostrarPorPromedio(inicio);
                break;
        }
    }while(opt !=6);
    free(inicios);
    return 0;
}

struct Nodo* crearNodo(char* nombre,int promedio){
    struct Nodo* nuevoNodo=(struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->promedio=promedio;
    nuevoNodo->nombre=nombre;
    nuevoNodo->sigCadena=NULL;
    nuevoNodo->siguiente=NULL;
    return nuevoNodo;
}

int buscarRepeticiones(struct Nodo* inicioCadena,char* nombre){
    struct Nodo* auxiliar=inicioCadena;
    while(auxiliar!=NULL && mystrCmp(auxiliar->nombre,nombre)!=0)
        auxiliar=auxiliar->siguiente;
    if(auxiliar!=NULL)
        return 1;
    else
        return 0;
}

struct Nodo** insertar(struct Nodo* inicio,struct Nodo* inicioCadena,char* nombre,int promedio){
    struct Nodo** inicios=(struct Nodo**)malloc(2*sizeof(struct Nodo));
    struct Nodo* auxiliar=inicio;
    struct Nodo* nuevoNodo=crearNodo(nombre,promedio);
    struct Nodo* nodosig=NULL;
    struct Nodo* auxiliarCadena=inicioCadena;
    struct Nodo* nodosigCadena=NULL;
    //Numeros 
    while(auxiliar!=NULL && promedio<=auxiliar->promedio){ 
        nodosig=auxiliar;
        auxiliar=auxiliar->siguiente;
    }
    if(nodosig==NULL){ // Insertar Al Inicio
        nuevoNodo->siguiente=auxiliar;
        inicio=nuevoNodo;
    }
    else{// Insertar Al Final O En Medio
        nodosig->siguiente=nuevoNodo;
        nuevoNodo->siguiente=auxiliar;
    }// Nombres
    while(auxiliarCadena!=NULL && mystrCmp(nombre,auxiliarCadena->nombre)>0){
        nodosigCadena=auxiliarCadena;
        auxiliarCadena=auxiliarCadena->sigCadena;
    }
    if(nodosigCadena==NULL){ // Insertar Al Inicio
        nuevoNodo->sigCadena=auxiliarCadena;
        inicioCadena=nuevoNodo;
    }
    else{ // Insertar Al Final O En Medio
        nodosigCadena->sigCadena=nuevoNodo;
        nuevoNodo->sigCadena=auxiliarCadena;
    }
    inicios[0]=inicio;
    inicios[1]=inicioCadena;
    return inicios;
}

void mostrarPorPromedio(struct Nodo* inicio){
    struct Nodo* auxiliar;
    if(!inicio)
        printf("\nNo Hay Alumnos Registrados\n");
    else{
        printf("\nAlumnos Ordenados Por Promedio\n");
        auxiliar=inicio;
        do{
            printf("%s: %d \n",auxiliar->nombre,auxiliar->promedio);
            auxiliar=auxiliar->siguiente;
        }while(auxiliar!=NULL);
    }
    printf("\n");
}

void mostrarPorNombre(struct Nodo* inicio){
    struct Nodo* auxiliar;
    if(!inicio)
        printf("\nNo Hay Alumnos Registrados\n");
    else{
        printf("\nAlumnos Ordenados Alfabeticamente\n");
        auxiliar=inicio;
        do{
            printf("%s: %d \n",auxiliar->nombre,auxiliar->promedio);
            auxiliar=auxiliar->sigCadena;
        }while(auxiliar!=NULL);
    }
    printf("\n");
}

struct Nodo** eliminar(struct Nodo* inicio,struct Nodo* inicioCadena,char* nombre){
    struct Nodo** inicios=(struct Nodo**)malloc(2*sizeof(struct Nodo));
    struct Nodo* auxiliar=inicio;
    struct Nodo* nodoAnterior=NULL;
    struct Nodo* auxiliarCadena=inicioCadena;
    struct Nodo* nodoAnteriorCadena=NULL;
    while(auxiliarCadena!=NULL && mystrCmp(auxiliarCadena->nombre,nombre)!=0){
        nodoAnteriorCadena=auxiliarCadena;
        auxiliarCadena=auxiliarCadena->sigCadena;
    }
    if(nodoAnteriorCadena==NULL) //Borrar El Inicio
        inicioCadena=auxiliarCadena->sigCadena;
    else{
        if(auxiliarCadena!=NULL) //Borrar el final o un nodo intermedio
            nodoAnteriorCadena->sigCadena=auxiliarCadena->sigCadena;
        else{
            printf("No Se Encontro El Alumno");
            inicios[0]=inicio;
            inicios[1]=inicioCadena;
            return inicios;
        }
    }
    while(auxiliar!=NULL && mystrCmp(auxiliar->nombre,nombre)!=0){
        nodoAnterior=auxiliar;
        auxiliar=auxiliar->siguiente;
    }
    if(nodoAnterior==NULL) // Borrar nodo inicial
        inicio=auxiliar->siguiente;
    else{
        if(auxiliarCadena!=NULL) //Borrar el final o un nodo intermedio
            nodoAnterior->siguiente=auxiliar->siguiente;
    }
    free(auxiliar);
    inicios[0]=inicio;
    inicios[1]=inicioCadena;
    return inicios;
}

int mystrCmp(char* str1, char* str2){
    int cnt=0;
    char c1,c2;
    do{
        c1=*str1++;
        c2=*str2++;
        if(c1==0) // Salir si la Cadena 1 es más corta que la Cadena 2
            return c1-c2;
    }while(c1 == c2);
    return c1-c2;;
}

void menuOpciones(){
    printf("1) Insertar Alumno\n");
    printf("2) Eliminar Alumno\n");
    printf("3) Modificar Promedio Del Alumno\n");
    printf("4) Mostrar Ordenados Alfabeticamente\n");
    printf("5) Mostrar Ordenados Por Promedio\n");
    printf("6) Salir\n");
    printf("Selecciona Una Opción: ");
}
