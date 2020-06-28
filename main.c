#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct{
    char nombre[20]; //"Biblia", "Copa de vino", "Doll"
    int falla; //puede tener 0...2 fallas
    float costo;
    char calidad; //según la calidad de la materia, será la calidad del producto
    int usado; ///si fue usada para ensamble =1 sino se encuentra en 0
   }stComponente;

#define MAX_ARREGLO 30///para cambiar los arreglos desde aca directamente
#define nombreA "doll"
#define nombreC "copa de vino"
#define nombreB "biblia"
#define ESC 27
#define FALLAS_MAX 2

void cargarVariasPerdidas(stComponente a[], int v);
void cargarPerdida(stComponente a);
int bajarArchCdV (stComponente copadevino[]);
int bajarArchDoll (stComponente doll[]);
int bajarArchBiblia (stComponente Biblia[]);
void cargarMasCompArch(stComponente a[]);
stComponente cargarUnaComp();
void mostrarMenu();
void guardaUnCliente(stComponente a);
void cargarVariosClientesar();
void mostrarUnComp (stComponente a);
void mostrarArchivo ();
void mostrarUnArreglo (stComponente a[], int v);


int main()
{
    stComponente Biblia [MAX_ARREGLO];
    stComponente CdV [MAX_ARREGLO];
    stComponente Doll [MAX_ARREGLO];

    int vBiblia = 0, vCdV = 0, vDoll = 0;
    int vGral = 0;

    char opcion;

    do
    {
    system("cls");
    mostrarMenu();
    fflush(stdin);
    opcion = getch();
    system("cls");

        switch(opcion)
        {
        case 'a':
        vGral = cargarVariosClientesar();
        break;
        case 'b':
        mostrarArchivo();
        break;
        case 'c':
        vBiblia=bajarArchBiblia(Biblia);
        vCdV=bajarArchCdV(CdV);
        vDoll=bajarArchDoll(Doll);
        break;
        case 'd':
        mostrarUnArreglo(Biblia,vBiblia);
        mostrarUnArreglo(CdV,vCdV);
        mostrarUnArreglo(Doll,vDoll);
        break;
        case 'e':
        cargarVariasPerdidas()
        break;
        }
    system("pause");
    }while (opcion != ESC);


    return 0;
}

void mostrarMenu()
{
    printf("Cargar Componentes (a)\n");
    printf("Mostrar Componentes (b)\n");
    printf("Pasar todo a arreglos (c)\n");
    printf("Mostrar todos los arreglos (d)\n");
}



stComponente cargarUnaComp()
{
    stComponente dato;

    printf("Ingrese el nombre del producto\n");
    fflush(stdin);
    gets(dato.nombre);
    printf("\nIngrese la falla del producto\n");
    scanf("%d", &dato.falla);
    printf("\nIngrese el costo del producto\n");
    scanf("%f", &dato.costo);
    printf("\nIngrese la calidad del producto\n");
    fflush(stdin);
    scanf("%c",&dato.calidad);
    dato.usado = 0;
    return dato;
}

void cargarMasCompArch(stComponente a[])
{

   char continuar ;
   int i =0;

    do
    {
        a[i]=cargarUnaComp();
        i++;
        printf("\nDesea continuar? ESC para salir\n");
        fflush(stdin);
        continuar = getch();
        system("cls");
    }   while (continuar != ESC && i< MAX_ARREGLO);

}


int bajarArchBiblia (stComponente Biblia[])
{
    stComponente b;
    int i = 0;
    FILE *archComp = fopen("componentes.bin", "rb");
    if (archComp)
        {
            while (i<MAX_ARREGLO && fread(&b,sizeof(stComponente),1,archComp)>0)
                {
                    if (strcmpi(b.nombre,nombreB) == 0){
                    Biblia[i]=b;
                    i++;
                    }
                }

        fclose(archComp);
        }
        return i;

}

int bajarArchDoll (stComponente doll[])
{
    stComponente b;
    int i = 0;
    FILE *archComp = fopen("componentes.bin", "rb");
    if (archComp)
        {
            while (i<MAX_ARREGLO && fread(&b,sizeof(stComponente),1,archComp)>0)
                {
                    if (strcmpi(b.nombre,nombreA) == 0){
                    doll[i]=b;
                    i++;
                    }
                }

        fclose(archComp);
        }
        return i;

}

int bajarArchCdV (stComponente copadevino[])
{
    stComponente b;
    int i = 0;
    FILE *archComp = fopen("componentes.bin", "rb");
    if (archComp)
        {
            while (i<MAX_ARREGLO && fread(&b,sizeof(stComponente),1,archComp)>0)
                {
                    if (strcmpi(b.nombre,nombreC) == 0){
                    copadevino[i]=b;
                    i++;
                    }
                }

        fclose(archComp);
        }
        return i;

}

void mostrarUnComp (stComponente a)
{
    printf("-------------------------------------------------------\n");
    printf("El componente es: \t");
    puts(a.nombre);
    printf("\nLa falla del producto es: \t%d",a.falla);
    printf("\nEl costo del producto es: \t%.2f",a.costo);
    printf("\nLa calidad del producto es: \t%c",a.calidad);
    if(a.usado == 0){
    printf("\nEl componente NO ha sido utilizado");
    }else{
    printf("\nEl componente ha sido utilizado");
    }
    printf("\n-------------------------------------------------------\n");
}

void mostrarArchivo ()
{
    stComponente a;
    FILE *archComp = fopen("componentes.bin", "rb");
    if (archComp)
        {
           while (fread(&a,sizeof(stComponente),1,archComp)>0){
           mostrarUnComp(a);
           }
        fclose(archComp);
        }
}

void guardaUnCliente(stComponente a)
{
    FILE *archSubida = fopen("componentes.bin", "ab");
    if (archSubida)
        {
            fwrite(&a,sizeof(stComponente),1,archSubida);

            fclose(archSubida);
        }

}

void cargarVariosClientesar()
{

    int i =0;
    char continuar;
    while (i<MAX_ARREGLO && continuar != ESC)
        {
          guardaUnCliente(cargarUnaComp());
          printf("\nDesea continuar? ESC para salir\n");
          fflush(stdin);
          continuar=getch();
          system("cls");
          i++;
        }

}

void cargarVariasPerdidas(stComponente a[],int v)
{
    int i = 0 ;

    while (i<v){
        cargarPerdida(a[i]);
        i++;
    }

}


void cargarPerdida(stComponente a)
{
    FILE *archPerdidas = fopen("Perdidas.bin", "ab");
    if (archPerdidas)
    {
       if(a.falla >= FALLAS_MAX){
        fwrite(&a.costo,sizeof(float),1,archPerdidas);
        a.usado = 1;
       }


       fclose(archPerdidas);
    }
}

void mostrarUnArreglo (stComponente a[], int v)
{

    int i =0;
    while (i<v){
        mostrarUnComp(a[i]);
        i++;
    }

}

