#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <string.h>
using namespace std;

struct Tipocarga{
	int tiempocompleto;
	int mediotiempo;
};
struct Tipocontrato{
	Tipocarga tg;
	int contrato;
	int nombramiento;
};
struct Tiponombramiento{
	Tipocontrato tp;
	int auxiliar;
	int agregado;
	int principal;	
};
struct Pagodocente{
	Tiponombramiento tn;
	float sueldomensual; 
	float horastrabajo;
	float horasfalta; 
};
struct Datosdocente{
	Pagodocente pg;
	char cedula[10];
	char nombres[30];
	char apellidos[30];
	char direccion[30];
	char correo[30];
	char telefono[10];
};
typedef struct nodo
{
	Datosdocente dc;
	struct nodo *siguiente;
	struct nodo *anterior;
}tipoNodo;
typedef tipoNodo *pNodo,*Lista;

int menu();
pNodo Creardocente(void);
void ingresardocente(Lista *l);
//bool validarnumero(char numero[]);
//bool validarletra(char letra[]);
void pagodocente(Lista *l);
void consultardocente(Lista *l);
pNodo buscar(Lista l, int cdl);
void mostrardocenteAscendente(Lista l);
void mostrardocenteDescendente(Lista l);
void eliminardocente(Lista *l);
void eliminarRegistro(Lista *l);
int main( ) 
{
	Lista lista = NULL;

	int op=0;
	do{
		system ("cls");
		cout<<"\n";
		cout<<"\t\t\t\t*****PAGOS DE SALARIOS*****\n";
		cout<<"\t_____________________________________________________________________________________\n";
		cout<<"\n\t1.Ingresar datos del docente\n";
		cout<<"\t2.Realizar el pago respectivo al docente\n";
		cout<<"\t3.Consultar los datos y salario de un docente registrado\n";
		cout<<"\t4.Mostrar un reporte de todos los docentes ingresados(Ordenados de forma ascendente)\n";
		cout<<"\t5.Mostrar un reporte de todos los docentes ingresados(Ordenados de forma ascendente)\n";
		cout<<"\t6.Eliminar el registro de un docente\n";
		cout<<"\t7.Eliminar el registro de todos los docentes\n";
		cout<<"\t8.Salir\n";
		cout<<"\t_____________________________________________________________________________________\n";
		cout<<"\n\tEscoja una opcion (1-7): ";
		cin>>op; 
		
		switch(op){
			case 1: ingresardocente (&lista);
					system ("pause");
					break;
			case 2: pagodocente (&lista);
					system ("pause");
					break;
			case 3: consultardocente (&lista);
					system ("pause");
					break;
			case 4: mostrardocenteAscendente(lista);
					system ("pause");
					break;
			case 5: mostrardocenteDescendente(lista);
					system ("pause");
					break;
			case 6: eliminardocente (&lista);
					system ("pause");
					break;
			case 7: eliminarRegistro(&lista);  
					system ("pause");
					break;
			case 8: cout<<"\n***Usted esta saliendo del programa***\n";
					break;
		}
	}while (op!=8);
	return 0;
}
pNodo Creardocente(void){
	//se declara el puntero nuevo
	pNodo nuevo;
	//se pide espacio en memoria y se hace casting
	nuevo = (pNodo)malloc(sizeof(struct Datosdocente));
	//se pide dato y se almacena
	if(nuevo != NULL){
		cout<<"\n\t\t\t\t*****INGRESO DE DATOS DEL DOCENTE*****\n";	
		fflush(stdin);		
		cout<<"\n\tIngrese el numero de cedula: ";	
		cin>>nuevo->dc.cedula;
		fflush(stdin);
		cout<<"\n\tIngrese los nombres: ";	
		gets(nuevo->dc.nombres);
		fflush(stdin);
		cout<<"\n\tIngrese los apellidos: ";	
		gets(nuevo->dc.apellidos);
		fflush(stdin);
		cout<<"\n\tIngrese la direccion domiciliaria: ";	
		gets(nuevo->dc.direccion);
		fflush(stdin);
		cout<<"\n\tIngrese el correo: ";	
		gets(nuevo->dc.correo);
		fflush(stdin);
		cout<<"\n\tIngrese el numero de telefono: ";	
		gets(nuevo->dc.telefono);
		return nuevo;
	//no hubo espacio en la RAM
	}else
	    return NULL;	  	
}
//es necesario mandar por referencia
//el verdadero valor de lista está en main
void ingresardocente(Lista *lista){  
	//se declaran punteros nuevo y aux 
	pNodo nuevo, aux;
    //invoca a la funcion CrearNodo()
    nuevo=Creardocente();
	//malloc si dio espacio de la RAM	
if(nuevo != NULL){
	//Colocamos aux en la primera posición de la lista
   	aux = *lista;
	//permite evaluar que aux sea != NULL
	//verifica si aux tiene que desplazarce por anterior   			
   	if(aux!=NULL){
   		while(aux->anterior!=NULL)
   			aux = aux->anterior;
	}
   	
	//Si la lista está vacía o se inserta al inicio
   	if(aux==NULL || strcmp(aux->dc.apellidos, nuevo->dc.apellidos)<=0)//compara	
   	{	//Añadimos la lista a continuación del nuevo nodo
      	nuevo->siguiente = aux;			
      	nuevo->anterior = NULL;
        //lista ya tiene elementos, se inserta inicio
	  	if(aux!=NULL)
	  		aux->anterior = nuevo;
	    //lista no tiene elementos, se inserta inicio
      	if(*lista==NULL)
	  		*lista = nuevo;
   	} else {
      	/*Avanzamos hasta el nodo anterior al nodo a insertar */
      	while((aux->siguiente!=NULL) && strcmp(aux->siguiente->dc.apellidos , nuevo->dc.apellidos)>=0) 
        {
			aux = aux->siguiente;
		}
      	/*Insertamos el nuevo nodo después del nodo anterior,
      	  se inserta nodo intermedio o nodo final */
      	nuevo->siguiente = aux->siguiente;
      	aux->siguiente = nuevo;
      	nuevo->anterior = aux;
        //se finaliza insercción nodo intermedio
	  	if(nuevo->siguiente != NULL)
	  		nuevo->siguiente->anterior = nuevo;
   	}	
}
else
	printf("\n No se puede insertar ");	
						system ("pause");

}

void pagodocente(Lista *lista){
}
pNodo buscar(Lista lista, char cdl[10]){
	pNodo aux=lista;
	while(aux->dc.cedula!=cdl && aux->siguiente!=NULL){
		aux=aux->siguiente;
	}
	return aux;
}
void consultardocente(Lista *lista){
	pNodo aux;
	system("cls");
	if(lista!=NULL){
		char cdl[10];
		cout<<"\n\tIngrese el numero de cedula:";
		cin>>cdl;
		aux=buscar(*lista,cdl);
		if(aux!=NULL){
			cout<<"\nCedula: "<<aux->dc.cedula;
			cout<<"\nNombre: "<<aux->dc.nombres;
			cout<<"\nApellido: "<<aux->dc.apellidos;
			cout<<"\nDireccion: "<<aux->dc.direccion;
			cout<<"\nCorreo: "<<aux->dc.correo;
			cout<<"\nTelefono: "<<aux->dc.telefono;
			//cout<<"\nSalario: "<<aux->dc.pg;

	
		}else{
			printf("\n*El docente no esta registrado*\n");
		}
	}else{
		printf("\n*No existen dicentes registrados*\n");
	}
	system("pause");
}
void mostrardocenteAscendente(Lista lista){
   	pNodo aux = lista;
   	if(lista==NULL)
   		printf("\tLista vacia\n");
	else
	{
     	//para empezar desde el fin
		 while(aux->siguiente!=NULL)
	  		aux = aux->siguiente;
	  	
      	cout<<"\n\tLista Descendente: \t";
      	while(aux!=NULL)
	  	{
         	cout<<"\nCedula: "<<aux->dc.cedula;
			cout<<"\nNombre: "<<aux->dc.nombres;	
         	cout<<"\nApellidos: "<<aux->dc.apellidos;	
		    cout<<"\nDireccion: "<<aux->dc.direccion;
			cout<<"\nCorreo: "<<aux->dc.correo;
			cout<<"\nTelefono: "<<aux->dc.telefono;
         	aux = aux->siguiente;

			 
			 
         	aux = aux->anterior;
      	}
   		cout<<"NULL"<<endl<<endl;
	}
		system("pause");

}//se cierra

void mostrardocenteDescendente(Lista lista){
	//se define el puntero aux
   	//aux inicia en lista
	pNodo aux = lista; 
    //valide que lista tenga elementos
   	if(lista==NULL)
   		printf("\tLista vacia\n");
    //la lista si tiene elementos
	else
	{
      	//para empezar aux desde el inicio
      	//de la lista
		while(aux->anterior!=NULL)
	  		aux = aux->anterior;
			      
      	cout<<"\n\tLista Ascendente: \t";
      	//imprime los valores de la lista
      	while(aux!=NULL)
	  	{
			cout<<"\nCedula: "<<aux->dc.cedula;
			cout<<"\nNombre: "<<aux->dc.nombres;	
         	cout<<"\nApellidos: "<<aux->dc.apellidos;	
		    cout<<"\nDireccion: "<<aux->dc.direccion;
			cout<<"\nCorreo: "<<aux->dc.correo;
			cout<<"\nTelefono: "<<aux->dc.telefono;
         	aux = aux->siguiente;

      	}
	}
		system("pause");

}//se cierra 

void eliminardocente(Lista *lista){
	  //define puntero auxiliar
   	/*pNodo aux;
   	//variable local temporal
   	int v = 0;

if(*lista != NULL){
	cout<<"\nIngrese el valor a eliminar: ";
	cin>>v;
	
   	//Buscar el nodo de valor v
   	aux = *lista;
   	
   	while(aux!=NULL && aux->valor<v)
   		aux = aux->siguiente;
   		
   	while(aux!=NULL && aux->valor>v)
   		aux = aux->anterior;

   	//El valor v no está en la lista
   	if(aux==NULL || aux->valor!=v)
   	{
   		cout<<"\n\tElemento no encontrado\n";
   		return;  //sale del procedimiento
   	}
   
   	//Para borrar el nodo
   	//Si lista apunta al nodo que queremos borrar, desplazamos a lista
   	if(aux == *lista)
   	{
    	if(aux->anterior)
	 		*lista = aux->anterior;
     	else
	 		*lista = aux->siguiente;
	}
	
   	if(aux->anterior!=NULL)	//cuando no es el primer nodo
      	aux->anterior->siguiente = aux->siguiente;
      	
   	if(aux->siguiente!=NULL) 				//cuando no es el último nodo
      	aux->siguiente->anterior = aux->anterior;
   	
	free(aux);
   	cout<<"\n\tElemento eliminado\n";
}else
  printf("\n No hay elementos en lista");
   	*/
}//se cierra

void eliminarRegistro(Lista *lista){/*
	pNodo nodo, aux;
   	
if(*lista == NULL)
  printf("\n lista vacia");
else{
	aux = *lista;
   	if(aux == NULL)
		printf("\tLista vacia\n");
	else
	{
		//buscando el nodo inicio de la lista
   		while(aux->anterior!=NULL) 
   			aux = aux->anterior;
        //empieza el proceso de borrado
   		while(aux!=NULL)
   		{
      		nodo = aux;
      		aux = aux->siguiente;
      		free(nodo);
   		}
   		*lista = NULL;
   		cout<<"\n\tLista Eliminada\n";
	}
}*/
}
