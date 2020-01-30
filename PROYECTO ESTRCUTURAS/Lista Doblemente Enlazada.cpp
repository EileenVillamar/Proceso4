#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
using namespace std;

typedef struct nodo
{
   	int valor;
   	struct nodo *siguiente;
   	struct nodo *anterior;
}tipoNodo;

typedef tipoNodo *pNodo,*Lista;

pNodo CrearNodo(void);
void Insertar(Lista *l);
void Borrar(Lista *l);
void Lista_Ascendente(Lista l);
void Lista_Descendente(Lista l);
void BorrarLista(Lista *l);

int main( ) 
{
	//se define el verdadero valor de lista
	Lista lista = NULL;
   	//pNodo p;

	int op=0;
	do{
		system ("cls");
		cout<<"\n\t\t\tLISTAS DOBLEMENTE ENLAZADAS\n\n";
		cout<<"\t\t\t1. Insertar valor\n";
		cout<<"\t\t\t2. Eliminar valor\n";
		cout<<"\t\t\t3. Mostrar lista ascendente\n";
		cout<<"\t\t\t4. Mostrar lista descendente\n";
		cout<<"\t\t\t5. Eliminar lista\n";
		cout<<"\t\t\t6. Salir\n";
		cout<<"\t\t\t\tOpcion: ";
		cin>>op;
		
		switch(op){
			case 1: Insertar (&lista);	//insertar un nodo
					system ("pause");
					break;
			case 2: Borrar (&lista);	//borrar un nodo
					system ("pause");
					break;
			case 3: Lista_Ascendente(lista);
					system ("pause");
					break;
			case 4: Lista_Descendente(lista);
					system ("pause");
					break;
			case 5: BorrarLista(&lista);   //borrar toda la lista
					system ("pause");
					break;
			case 6: cout<<"\nSaliendo del Programa\n";
					break;
		}
	}while (op!=6);
	return 0;
}

pNodo CrearNodo(void){
	//se declara el puntero nuevo
	pNodo nuevo;
	//se pide espacio en memoria y se hace casting
	nuevo = (pNodo)malloc(sizeof(tipoNodo));
	//se pide dato y se almacena
	if(nuevo != NULL){
		cout<<"\n\tIngrese el valor: ";	
		cin>>nuevo->valor;
		return nuevo;
	//no hubo espacio en la RAM
	}else
	    return NULL;	  	
}
//es necesario mandar por referencia
//el verdadero valor de lista está en main
void Insertar(Lista *lista) 
{   //se declaran punteros nuevo y aux 
	pNodo nuevo, aux;
    //invoca a la funcion CrearNodo()
    nuevo=CrearNodo();
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
   	if(aux==NULL || aux->valor > nuevo->valor)		
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
      	while((aux->siguiente!=NULL) && (aux->siguiente->valor <= nuevo->valor)) 
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
}//cierra insertar

//permite borrar un elemento
//lista se vera modificado, entonces manejar referencia
void Borrar(Lista *lista)
{   //define puntero auxiliar
   	pNodo aux;
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
   	
}//se cierra

//mostrar por pantalla toda la lista
//se muestra en orden ascendente
//se envía por valor xq no se modifica puntero lista
void Lista_Ascendente(Lista lista)
{
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
         	printf("%d-> ", aux->valor);	
         	aux = aux->siguiente;
      	}
  		cout<<"NULL"<<endl<<endl;   
	}
}//se cierra 

//permite mostrar por pantalla la lista 
//en forma descendente
void Lista_Descendente(Lista lista)
{
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
         	printf("%d-> ", aux->valor);	
         	aux = aux->anterior;
      	}
   		cout<<"NULL"<<endl<<endl;
	}
}//se cierra
//se elimina toda la lista
void BorrarLista(Lista *lista)
{
//definien	
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
}//se cierra

}
