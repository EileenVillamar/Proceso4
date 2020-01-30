//NOMBRRE: VARGAS MENDEZ KIMBERLY 
//CURSO:SOF-MA-3-1 
//ASIGNATURA: ESTRUCTURA DE DATOS
//FECHA:24-11-2019
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

struct Producto{
	int codigo;
	char descripcion[50];
	char marca[15];
	char modelo[10];
	float costo;
	float pventa;
	int stock;
	struct Producto *siguiente;
};
typedef Producto *lista,*nodo;

int menu();
nodo crearproducto(void);
void insertarproducto (lista *inicio, lista *fin);
void eliminarproducto (lista *inicio, lista *fin);
void actualizarproducto(lista *inicio);
void consultarproducto (lista *inicio);
void mostrarproducto (lista *inicio);
void eliminarlista(lista *inicio);
nodo buscar(lista lista, int cod);
float cambiarprecioventa();
int cambiarstock();
float calcularprecioventa(nodo aux);

main(){
	int opc=0;
	lista inicio=NULL,fin=NULL;
	do{
		system("cls");
		printf("\n\t***INVENTARIO DE PRODUCTOS***\n");
		printf("\n\t1.Insertar producto");
		printf("\n\t2.Eliminar producto");
		printf("\n\t3.Actualizar producto");
		printf("\n\t4.Consultar un producto");
		printf("\n\t5.Mostrar todos los productos");
		printf("\n\t6.Eliminar todos los productos");
		printf("\n\t7.Salir");
		printf("\n\tElija una opcion (1-7): ");
		scanf("%d",&opc);
		switch(opc){
			case 1: insertarproducto(&inicio, &fin);
			break;
			case 2: eliminarproducto(&inicio,&fin);
			break;
			case 3: actualizarproducto(&inicio);
			break;
			case 4: consultarproducto(&inicio);
			break;
			case 5: mostrarproducto(&inicio);
			break;
			case 6: eliminarlista(&inicio);
			break;
		}
	}while(opc>0 &&opc<7);
}
	nodo crearproducto(){
	nodo nuevo;
	int stock=0, codigo=0;
	float costo=0,pventa=0;
	nuevo=(nodo)malloc(sizeof(struct Producto));
	if(nuevo!=NULL){
		printf("\nIngrese el codigo del producto: ");
		scanf("%d",&codigo);
		nuevo->codigo=codigo;
		fflush(stdin);
		printf("\nIngrese la descripcion del producto: \n");
		gets(nuevo->descripcion);
		fflush(stdin);
		printf("\nIngrese la marca del producto: ");
		gets(nuevo->marca);
		fflush(stdin);
		printf("\nIngrese el modelo del producto: ");
		gets(nuevo->modelo);
		fflush(stdin);
		printf("\nIngrese el costo del producto: ");
		scanf("%f",&costo);
		nuevo->costo=costo;
		nuevo->pventa=calcularprecioventa(nuevo);
		printf("\nIngrese el stock del producto: ");
		scanf("%d",&stock);
		nuevo->stock=stock;
		return nuevo;
	}else{
		return NULL;
	}
}
float pventa(){
	float p=0, cant=0;
	printf("Ingrese la ganancia: ");
	scanf("%d",&p);
	if(p>0){
		return p;
	}else{
		printf("\n*Ingrese un valor valido*");
		system("cls");
		pventa();
	}
}
void insertarproducto(lista *inicio, lista *fin){
	nodo aux=NULL,nuevo=NULL;
	nuevo=crearproducto();
	if(nuevo!=NULL){
		if(*inicio==NULL){
			*inicio=nuevo;
			(*inicio)->siguiente=NULL;
			*fin=nuevo;	
		}else{
			if(nuevo->codigo > (*fin)->codigo){
				(*fin)->siguiente=nuevo;
				nuevo->siguiente=NULL;
				*fin=nuevo;
			}else if((*inicio)->codigo > nuevo->codigo){
				nuevo->siguiente=*inicio;
				*inicio=nuevo;
			}else{
				aux=*inicio;
				while(aux->siguiente!=NULL && (aux->siguiente->codigo)<=nuevo->codigo){
					aux=aux->siguiente;
				}
				nuevo->siguiente=aux->siguiente;
				aux->siguiente=nuevo;
			}
		}
	}else{
		printf("\n*No se pueden ingresar el producto*\n");
	}
	system("pause");
}
void eliminarproducto(lista *inicio, lista *fin){
	nodo aux=*inicio,anterior=NULL;
	if(*inicio!=NULL){
		int codigo=0;
		bool encontrado=false;
		system("cls");
		printf("\nIngrese el codigo del producto que desea eliminar: ");
		printf("\nCodigo: ");
		scanf("%d",&codigo);
		while( aux!=NULL && encontrado!=true ){
			if(aux->codigo==codigo){
				if(aux == *inicio){
					*inicio=(*inicio)->siguiente;
					}else if(aux==*fin){
						anterior->siguiente=NULL;
						*fin=anterior;
					}else{
						anterior->siguiente=aux->siguiente;
					}
					encontrado=true;
			}
			anterior=aux;
			aux=aux->siguiente;
		}
		if(encontrado==true){
			printf("\n*Producto eliminado*\n");
			free(anterior);
		}else{
			printf("\n*Producto no encontrado*\n");
		}
	}else{
		printf("\n No hay productos,no se puede eliminar\n");
	}
	system("pause");
}
void actualizarproducto(lista *inicio){
	system("cls");
	if(inicio!=NULL){
		int cod=0;
		nodo aux;
		printf("\nIngrese el codigo del producto que desea actualizar: ");
		printf("\n\t Codigo: ");
		scanf("%d",&cod);
		aux=buscar(*inicio, cod);
		if(aux!=NULL){
			int op=0;
			printf("\n\tElija la opcion que desea modificar");
			printf("\n\t1.Precio de venta");
			printf("\n\t2.Stock");
			printf("\n\t3.Ambos");
			printf("\n\tIngrese la opcion: ");
			scanf("%d",&op);
			switch(op){
				case 1: aux->pventa=aux->costo+(aux->costo*cambiarprecioventa());
				break;
				case 2: aux->stock=cambiarstock();
				break;
				case 3:{
					aux->pventa=aux->costo+(aux->costo*cambiarprecioventa());
					aux->stock=cambiarstock();
					break;
				}
			}
		}else{
			printf("\n*El producto no existe*\n");
		}
	}else{
		printf("\n*No hay productos ingresados*\n");
	}
	system("pause");
}
float cambiarprecioventa(){
	float nuevo=0;
	printf("Ingrese la nueva ganancia del producto: ");
	scanf("%f",&nuevo);
	return nuevo/10;
}
int cambiarstock(){
	int nuevo=0;
	printf("\nIngrese la nueva cantidad en stock: ");
	scanf("%d",&nuevo);
	return nuevo;
}
nodo buscar(lista inicio, int cod){
	nodo aux=inicio;
	while(aux->codigo!=cod && aux->siguiente!=NULL){
		aux=aux->siguiente;
	}
	return aux;
}
void consultarproducto(lista *inicio){
	nodo aux;
	system("cls");
	if(inicio!=NULL){
		int cod=0;
		printf("\n\tIngrese el codigo del producto que desea consultar: ");
		scanf("%d",&cod);
		aux=buscar(*inicio,cod);
		if(aux!=NULL){
			printf("\n\tCodigo: %d",aux->codigo);
			printf("\n\tDescripcion: %s",aux->descripcion);
			printf("\n\tMarca: %s",aux->marca);
			printf("\n\tModelo: %s",aux->modelo);
			printf("\n\tCosto: %.2f",aux->costo);
			printf("\n\tPrecio de venta: %.2f",aux->pventa);
			printf("\n\tStock: %d \n",aux->stock);
		}else{
			printf("\n*El producto no existe*\n");
		}
	}else{
		printf("\n*No existen productos*\n");
	}
	system("pause");
}
void mostrarproducto(lista *inicio){
	nodo aux=*inicio;
	system("cls");
	if(inicio!=NULL){
		while(aux!=NULL){
			printf("\n\tCodigo: %d",aux->codigo);
			printf("\n\tDescripcion: %s",aux->descripcion);
			printf("\n\tMarca: %s",aux->marca);
			printf("\n\tModelo: %s",aux->modelo);
			printf("\n\tCosto: %.2f",aux->costo);
			printf("\n\tPrecio de venta: %.2f",aux->pventa);
			printf("\n\tStock: %d \n",aux->stock);
			aux=aux->siguiente;
		}
	}else{
		printf("\n*No existen productos*\n");
	}
	system("pause");
}
void eliminarlista(lista *inicio){
	nodo aux;
	system("cls");
	if(*inicio!=NULL){
	
		int cont=1;
		while(*inicio!=NULL){
			aux=*inicio;
			*inicio=(*inicio)->siguiente;
			printf("\n\tEliminando producto %d", cont);
			free(aux);
			cont++;
		}
		printf("\n*Productos eliminados*\nTotal: %d\n",cont);
	}else{
		printf("\n*No existen productos*\n");
	}
	system("pause");
}

float calcularprecioventa(nodo aux){
	float resultado=0;
	resultado=aux->costo +aux->costo*0.3;
	return resultado;
	
	
}

