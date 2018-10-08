/********************************************************************
*                        SISTEMA DE INVENTARIO                      *
*                       EMPRESA COMPUTECH S.A                       *
* Este es un programa con Sistema de Inventario con E/S de ficheros *
*                           Creado por                              *
*                      Gabriela Astudillo                           *
*                     PROYECTO DE PROGRAMACION                      *
********************************************************************/
//----------LIBRERIAS UTILIZADAS EN ESTE PROGRAMA
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <string>

//----------DECLARACION DE COLORES

#define Color 509//508 letra roja o fucsia
#define Color_Def 496//COLOR DE LETRA NEGRO Y FONDO BLANCO----- 499: color letra turqueza
#define Color_Verde 498//498-506
#define Letra_Azul_fb 505//505-497:--- COLOR DE LETRA AZUL Y FONDO BLANCO
#define Cursor 16
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27

using namespace std;
//----------------DEFINICION DE ESTRUCTURAS 
//----------PROVEEDOR	 
struct Proveedor
    {
     int cod_prov ;
     char rsocial[40];
	 char ruc[15] ;
	 char dir[40] ;
	 char tel[10] ;
	 char tipo_p[10];
	 char regvalido_P;
    }PROVEEDOR;//Nombre del objeto que representa a la estructura
    FILE *Cod_p, *R_Social, *Ruc, *Direccion, *Telefono, *Tipo_art;//Definicion de punteros para cada uno de los campos de la estructura Proveedor
//----------ARTÍCULOS
struct Articulo
    {
	 int cod_art ;
	 char nomb_art[30] ;
	 char marca[20] ;
	 char modelo[20] ;
     char stock;
     char tipo_art;
     }ARTICULO;
     FILE *Cod_a;
//----------TRANSACCIONES:COMPRA
struct Compra
	 {
     int cod_t ;
	 char FechaCompra[8];
	 float  CostoUni, PrecioUni, CostoTotal, CantArt;
     }COMPRA;
     FILE *Cod_c;
//**************** DECLARACION DE VARIABLES GLOBALES ********************
     COORD coord = {0,0};
     char KEY_PAD;   
//----------DECLARACION DE FUNCIONES
void gotoxy(int x,int y);
void Titulo (void);
void menu();
void barra_inferior();
void nuevo_proveedor();
void proveedor();
void articulos();
void nuevo_producto();
void transacciones();
void compra();
void nueva_compra();
void devolucion();
void lineadoble();
bool validacion_ruc(char ruc[13]);
bool val_palabras(char palabra[40]);
int Obtener_cod_p();
int Obtener_cod_a();
int Obtener_cod_t();
void leer_proveedor();
void modificar_proveedor();
void eliminar_proveedor();
/********************************************************************
*                            FUNCION MAIN                           *
*     Es la funcion que se incia cuando se ejecuta el programa      *
********************************************************************/
int main()
{
	
    system("color F1");//F(Blanco brillante) -> define el color de la pantalla, 1(Azul)-> Define el color de las letras 
    system("cls");//Limpiar la pantalla
	menu();      
}

/********************************************************************
*                       Función:  gotoxy                            *
* Input Arguments:                                                  *
*- Integers: Coordenates X and Y in screen.                         *
* Output Arguments:                                                 *
* -----------------                                                 *
* Esta función mueve el cursor a una coordenada específica          *
********************************************************************/
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

/********************************************************************
*                    Función: Logo de la empresa                    *
*           Esta función presenta el nombre de la empresa           *
********************************************************************/
void Titulo (void)
{
    int X = 0;
    int Y = 0;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Letra_Azul_fb);
cout<<" ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ ";
cout<<"                                  COMPUTECH S.A.                                ";
cout<<"                                                                                ";
cout<<"                              SISTEMA DE INVENTARIO                             ";
cout<<" ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ ";
gotoxy (X,Y+5);
}

//--------------------LINEA DOBLE HORIZONTAL
void lineadoble()
{ 
cout<<" ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ ";
}

//-------------- ETIQUETAS DE LA BARRA INFERIOR PARA SELECCIONAR UNA OPCION
void barra_inferior()
{
     int Cursor_Pos=4; 
     gotoxy(Cursor_Pos,23);  
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Verde);
     cout << (char)Cursor;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),Letra_Azul_fb ); 
     gotoxy(0,22);lineadoble();    
     gotoxy(05,23);cout<<"[ NUEVO ]";
     gotoxy(20,23);cout<<"[ BUSCAR ]";
     gotoxy(35,23);cout<<"[MODIFICAR]";
     gotoxy(50,23);cout<<"[ELIMINAR]";
     gotoxy(65,23);cout<<"[IR A MENU]"<<endl;
     lineadoble();
     gotoxy(78,24);
}

/********************************************************************
*                            MENU PRINCIPAL                         *
*     Muestra el menú para administrar las entidades del sistema    *
********************************************************************/
void menu()
{    
	 int Cursor_Pos = 12;
     system("cls");
     Titulo ();
     gotoxy(0,22);lineadoble();
     gotoxy(0,23);cout <<" Use las teclas direccionales - ENTER para elegir una opcion -  ESC para salir" << endl; 
     gotoxy(0,24);lineadoble();
     gotoxy(25,18);    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
	 gotoxy(27,7);cout<<"*** PANTALLA PRINCIPAL ***";
	 gotoxy(25,18);    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Letra_Azul_fb);
	 gotoxy(25,12);    cout << "(1) ADMINISTRAR PROVEEDOR";
     gotoxy(25,14);    cout << "(2) ADMINISTRAR ARTICULOS";
     gotoxy(25,16);    cout << "(3) ADMINISTRAR TRANSACCIONES";
     gotoxy(25,18);    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Verde);
     cout << "(4) SALIR" << endl; 
     gotoxy(22,Cursor_Pos);
     cout << (char)Cursor;
     gotoxy(78,24);
//Control del movimiento de las teclas direccionales arriba-abajo, mientras no se haya pulsado la tecla ENTER
          //Nota: Cuando se pulsa Enter se ingresa a la opción de menú señalada 
    do{
        if (kbhit())
        {
            KEY_PAD = getch();
            switch (KEY_PAD)
            {
                case KEY_UP:
                {if (Cursor_Pos >= 14) Cursor_Pos = Cursor_Pos - 2;}
                break;
                case KEY_DOWN:
                {if (Cursor_Pos <= 16) Cursor_Pos = Cursor_Pos + 2;}
                break;
                case KEY_ENTER:
                {
                    switch (Cursor_Pos)
                    {
                        case 12: proveedor(); break;
                        case 14: articulos(); break;
                        case 16: transacciones();break;
                        case 18: exit(1);break;                        
                    }
                }
                break;
                case KEY_ESC:; break;
            }
            //Muestra un espacio vacio a la derecha de las opciones del menú
            for (int i = 0; i<7 ; i+=2)
            {gotoxy(22,12+i);  cout << (char) 0;}
            //Para mostrar la Flechita verde a la izquierda de la opcion seleccionada mediante las teclas direccionales 
            gotoxy(22,Cursor_Pos);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Verde);
            cout << (char)Cursor;
            gotoxy(78,24);
        }
    }while (KEY_PAD!=27);
    }	

//-------------------PANTALLA ADMINISTRAR PROVEEDOR
void proveedor()
{
     int Cursor_Pos=4;      
     system("cls");
	 Titulo (); barra_inferior();
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),Color );
	 gotoxy(26,6);cout<<"*** ADMINISTRAR PROVEEDOR ***";
	 gotoxy(78,24);
     do{
        if (kbhit())
        {
            KEY_PAD = getch();
            switch (KEY_PAD)
            {
                case KEY_LEFT:
                {if (Cursor_Pos >= 19) Cursor_Pos = Cursor_Pos - 15;}
                break;
                case KEY_RIGHT:
                {if (Cursor_Pos <= 49) Cursor_Pos = Cursor_Pos + 15;}
                break;
                case KEY_ENTER:
                {
                    switch (Cursor_Pos)
                    {
                        case 4: nuevo_proveedor(); break;
                        case 19: leer_proveedor(); break;
                        case 34: modificar_proveedor();break;
                        case 49: eliminar_proveedor(); break;
                        case 64: menu(); break;                        
                    }
                }
                break;
                case KEY_ESC: getch(); break;
            }
            //Muestra un espacio vacio a la derecha de las opciones del menú
            for (int i = 0; i<64 ; i+=15)
            {gotoxy(4+i, 23);  cout << (char) 0;}
            //Para mostrar la Flechita verde a la izquierda de la opcion seleccionada mediante las teclas direccionales 
            gotoxy(Cursor_Pos, 23);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Verde);
            cout << (char)Cursor;
            gotoxy(78,24);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Letra_Azul_fb);
        }
    }while (KEY_PAD!=27);    
}

//------------------INGRESO DE UN NUEVO PROVEEDOR
void nuevo_proveedor()
{
          
     //----------Imprimir en pantalla 
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Letra_Azul_fb);
	 gotoxy(30,8);cout<<">> NUEVO PROVEEDOR <<";	 
	 gotoxy(0,10);cout<<"                                                                  ";
     gotoxy(0,12);cout<<"                                                                  ";
	 gotoxy(0,14);cout<<"                                                                  ";
	 gotoxy(0,16);cout<<"                                                                  ";
	 gotoxy(0,18);cout<<"                                                                  ";
	 gotoxy(0,20);cout<<"                                                                                 ";
	 
     gotoxy(15,10);cout<<"C\242digo:";
	 gotoxy(9,12);cout<<"Raz\242n Social:";
	 gotoxy(18,14);cout<<"RUC:";
	 gotoxy(12,16);cout<<"Direcci\242n:";
	 gotoxy(13,18);cout<<"Telefono:";
	 gotoxy(17,20);cout<<"Tipo:                                  (NATURAL/JURIDICA)";
	 
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
        
    
    Cod_p=fopen("PROVEEDOR.txt","a+");
    //----------Imprimir en archivo 
        PROVEEDOR.cod_prov=Obtener_cod_p();
        gotoxy(24,10);cout<<PROVEEDOR.cod_prov; 
    
        
	do{         
         gotoxy(24,12);cin.ignore(); cin.getline(PROVEEDOR.rsocial, 40); 
        if(!val_palabras(PROVEEDOR.rsocial))
       {gotoxy(24,12);MessageBox(NULL,"Error. Debe ingresar caracteres alfabéticos.","Validación de Palabra", MB_ICONEXCLAMATION|MB_OK);}
       }while(!val_palabras(PROVEEDOR.rsocial));   
	
	do{       
  	   gotoxy(24,14);cin>>PROVEEDOR.ruc; 
         if(!validacion_ruc(PROVEEDOR.ruc))
         {gotoxy(24,14);MessageBox(NULL,"Error. Debe ingresar 13 caracteres numéricos.","Validación del RUC", MB_ICONEXCLAMATION | MB_OK);}
      }while(!validacion_ruc(PROVEEDOR.ruc));      
	
    gotoxy(24,16);cin.ignore(); cin.getline(PROVEEDOR.dir,50);
	gotoxy(24,18);cin>>PROVEEDOR.tel;
	gotoxy(24,20);cin>>PROVEEDOR.tipo_p;
    PROVEEDOR.regvalido_P='S'; 
    fseek(Cod_p, 0, SEEK_END);
    fwrite(&PROVEEDOR, sizeof(struct Proveedor),1,Cod_p);
    fclose(Cod_p);
}

//----------FUNCION: LEER PROVEEDOR
void leer_proveedor()
{
char prov[40];
char cod_prov;
int aux, ban=0 ;
    	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Letra_Azul_fb);
	 gotoxy(29,8);cout<<">> BUSCAR  PROVEEDOR <<";	 
	 gotoxy(0,10);cout<<"                                                                  ";
     gotoxy(0,12);cout<<"                                                                  ";
	 gotoxy(0,14);cout<<"                                                                  ";
	 gotoxy(0,16);cout<<"                                                                  ";
	 gotoxy(0,18);cout<<"                                                                  ";
	 gotoxy(0,20);cout<<"                                                                               ";
	     
     gotoxy(11,10);cout<<"REFERENCIA:  "; cin>>(prov);
             
    Cod_p=fopen("PROVEEDOR.txt", "r");
    if(!Cod_p)
    { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);gotoxy(18,15);cout<<"Error al abrir el archivo"; /*system("pause"); */}        
     else{
        fseek(Cod_p, sizeof (struct Proveedor),SEEK_END);
        while(!feof(Cod_p)){
                            
        aux=ftell(Cod_p)/sizeof(struct Proveedor);   
   for (int i=0;i<=aux; i++) {
        fseek(Cod_p,i*sizeof(struct Proveedor),0);    
        fread(&PROVEEDOR, sizeof(struct Proveedor),1,Cod_p);
        
        if(strcmp(prov,PROVEEDOR.rsocial)==0)
        {ban=1;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Letra_Azul_fb);
        gotoxy(0,10);cout<<"                                    ";
        gotoxy(15,10);cout<<"C\242digo:";
        gotoxy(9,12);cout<<"Raz\242n Social:";
	    gotoxy(18,14);cout<<"RUC:";
	    gotoxy(12,16);cout<<"Direcci\242n:";
	    gotoxy(13,18);cout<<"Telefono:";
	    gotoxy(17,20);cout<<"Tipo:"; 
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
        gotoxy(24,10);cout<<PROVEEDOR.cod_prov;
	    gotoxy(24,12);cout<<PROVEEDOR.rsocial;
	    gotoxy(24,14);cout<<PROVEEDOR.ruc;
	    gotoxy(24,16);cout<<PROVEEDOR.dir;
	    gotoxy(24,18);cout<<PROVEEDOR.tel;
	    gotoxy(24,20);cout<<PROVEEDOR.tipo_p; 	     
	    getch();
        }     
        } if(ban==0) { gotoxy(20,16);cout<<"Este proveedor no esta registrado"; gotoxy(40,18);   system("pause");}proveedor();
        fclose(Cod_p);}              
}    
}
//-----------MODIFICAR PROVEEDOR: IDENTIFICACION
void modificar_proveedor()
{
char prov[40];
char cod_prov, op;
int aux, ban=0;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Letra_Azul_fb);
	 gotoxy(28,8);cout<<">> MODIFICAR PROVEEDOR <<";	 
	 gotoxy(0,10);cout<<"                                                                  ";
     gotoxy(0,12);cout<<"                                                                  ";
	 gotoxy(0,14);cout<<"                                                                  ";
	 gotoxy(0,16);cout<<"                                                                  ";
	 gotoxy(0,18);cout<<"                                                                  ";
	 gotoxy(0,20);cout<<"                                                                                 ";
	 
     
     gotoxy(11,10);cout<<"REFERENCIA:  "; 
     gotoxy(11,12);cout<<"No. de campo a modificar: ";
     gotoxy(11,14);cout<<"   (1) Raz\242n Social";
	 gotoxy(11,15);cout<<"   (2) RUC";
     gotoxy(11,16);cout<<"   (3) Direcci\242n";
     gotoxy(11,17);cout<<"   (4) Telefono";
     gotoxy(11,18);cout<<"   (5) Tipo"; 
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
     gotoxy(23,10);cin>>prov;
     gotoxy(38,12);cin>>op;
     
     gotoxy(0,10);cout<<"                                                                  ";
     gotoxy(0,12);cout<<"                                                                  ";
	 gotoxy(0,14);cout<<"                                                                  ";
	 gotoxy(0,15);cout<<"                                                                  ";
	 gotoxy(0,16);cout<<"                                                                  ";
	 gotoxy(0,17);cout<<"                                                                  ";
     gotoxy(0,18);cout<<"                                                                  ";
	               
    Cod_p=fopen("PROVEEDOR.txt", "r+");
    if(!Cod_p)
    { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);gotoxy(18,15);cout<<"Error al abrir el archivo"; /*system("pause"); */}              
     else{
        fseek(Cod_p, sizeof (struct Proveedor),SEEK_END);
        while(!feof(Cod_p)){
                            
        aux=ftell(Cod_p)/sizeof(struct Proveedor);   
   for (int i=0;i<=aux; i++) {
        fseek(Cod_p,i*sizeof(struct Proveedor),0);    
        fread(&PROVEEDOR, sizeof(struct Proveedor),1,Cod_p);
        
        if(strcmp(prov,PROVEEDOR.rsocial)==0)
        {ban=1;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Letra_Azul_fb);
        gotoxy(0,10);cout<<"                                    ";
        gotoxy(15,10);cout<<"C\242digo:";
        gotoxy(9,12);cout<<"Raz\242n Social:";
	    gotoxy(18,14);cout<<"RUC:";
	    gotoxy(12,16);cout<<"Direcci\242n:";
	    gotoxy(13,18);cout<<"Telefono:";
	    gotoxy(17,20);cout<<"Tipo:"; 
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
        gotoxy(24,10);cout<<PROVEEDOR.cod_prov;
	    gotoxy(24,12);cout<<PROVEEDOR.rsocial;
	    gotoxy(24,14);cout<<PROVEEDOR.ruc;
	    gotoxy(24,16);cout<<PROVEEDOR.dir;
	    gotoxy(24,18);cout<<PROVEEDOR.tel;
	    gotoxy(24,20);cout<<PROVEEDOR.tipo_p; 	     
	    switch(op)
	    {
         case '1':   	do{         
         gotoxy(24,12);cin.ignore(); cin.getline(PROVEEDOR.rsocial, 40); 
         if(!val_palabras(PROVEEDOR.rsocial))
         {gotoxy(24,12);MessageBox(NULL,"Error. Debe ingresar caracteres alfabéticos.","Validación de Palabra", MB_ICONEXCLAMATION|MB_OK);}
         }while(!val_palabras(PROVEEDOR.rsocial));fseek(Cod_p, 0, SEEK_SET); fwrite(&PROVEEDOR, sizeof(struct Proveedor),1,Cod_p);fclose(Cod_p); break;      
         case '2':do{       
  	     gotoxy(24,14);cin>>PROVEEDOR.ruc; 
         if(!validacion_ruc(PROVEEDOR.ruc))
         {gotoxy(24,14);MessageBox(NULL,"Error. Debe ingresar 13 caracteres numéricos.","Validación del RUC", MB_ICONEXCLAMATION | MB_OK);}
         }while(!validacion_ruc(PROVEEDOR.ruc)); fseek(Cod_p, 0, SEEK_SET);fwrite(&PROVEEDOR, sizeof(struct Proveedor),1,Cod_p);fclose(Cod_p); break;
         case '3': gotoxy(24,16);cin.ignore(); cin.getline(PROVEEDOR.dir,50); fseek(Cod_p, 0, SEEK_SET);fwrite(&PROVEEDOR, sizeof(struct Proveedor),1,Cod_p);
         fclose(Cod_p);break;
         case '4': 	gotoxy(24,18);cin>>PROVEEDOR.tel; fseek(Cod_p, 0, SEEK_SET);fwrite(&PROVEEDOR, sizeof(struct Proveedor),1,Cod_p);fclose(Cod_p);break;
         case '5':gotoxy(24,20);cin>>PROVEEDOR.tipo_p; fseek(Cod_p, 0, SEEK_SET);fwrite(&PROVEEDOR, sizeof(struct Proveedor),1,Cod_p);fclose(Cod_p);break;
         }         
        }     
        } if(ban==0) { gotoxy(20,16);cout<<"Este proveedor no esta registrado"; gotoxy(40,18);   system("pause");}proveedor();
        fclose(Cod_p);}              
        }    

    }

//------------ELIMINAR PROVEEDOR
void eliminar_proveedor()
{
char prov[40];
   	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Letra_Azul_fb);
	 gotoxy(28,8);cout<<">> ELIMINAR  PROVEEDOR <<";	 
	 gotoxy(0,10);cout<<"                                                                  ";
     gotoxy(0,12);cout<<"                                                                  ";
	 gotoxy(0,14);cout<<"                                                                  ";
	 gotoxy(0,16);cout<<"                                                                  ";
	 gotoxy(0,18);cout<<"                                                                  ";
	 gotoxy(0,20);cout<<"                                                                                     ";
	      
     do{ gotoxy(11,14);cout<<"REFERENCIA:  "; cin>>prov; }while(prov<0);
     
      Cod_p=fopen("PROVEEDOR.txt", "r+");
    if(!Cod_p)
    { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);gotoxy(18,15);cout<<"Error al abrir el archivo"; /*system("pause"); */}        
     else{
        fseek(Cod_p, sizeof (struct Proveedor), SEEK_SET);
        fread(&PROVEEDOR, sizeof(struct Proveedor),1,Cod_p);
        PROVEEDOR.regvalido_P='N';
        //fseek(Cod_p, 0, SEEK_SET);
        fwrite(&PROVEEDOR, sizeof(struct Proveedor),1,Cod_p);gotoxy(26,18);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);cout<<"Se ha eliminado correctamente";
        fclose(Cod_p);}
        
        
}
//-----------------PANTALLA ARTICULOS
void articulos()
{    int Cursor_Pos=4;      
     system("cls");
	 Titulo (); barra_inferior();
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),Color );
	 gotoxy(26,6);cout<<"*** ADMINISTRAR ARTICULOS ***";  
	 
	 gotoxy(78,24);
     do{
        if (kbhit())
        {
            KEY_PAD = getch();
            switch (KEY_PAD)
            {
                case KEY_LEFT:
                {if (Cursor_Pos >= 19) Cursor_Pos = Cursor_Pos - 15;}
                break;
                case KEY_RIGHT:
                {if (Cursor_Pos <= 49) Cursor_Pos = Cursor_Pos + 15;}
                break;
                case KEY_ENTER:
                {
                    switch (Cursor_Pos)
                    {
                        case 4: nuevo_producto(); break;
                        case 19: /*articulos();*/ break;
                        case 34: /*transacciones();*/break;
                        case 49: /*return 4;*/ break;
                        case 64: menu(); break;                        
                    }
                }
                break;
                case KEY_ESC: getch(); break;
            }
            //Muestra un espacio vacio a la derecha de las opciones del menú
            for (int i = 0; i<64 ; i+=15)
            {gotoxy(4+i, 23);  cout << (char) 0;}
            //Para mostrar la Flechita verde a la izquierda de la opcion seleccionada mediante las teclas direccionales 
            gotoxy(Cursor_Pos, 23);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Verde);
            cout << (char)Cursor;
            gotoxy(78,24);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Letra_Azul_fb);
        }
    }while (KEY_PAD!=27);
}

//-------------REGISTRAR NUEVO PRODUCTO 
void nuevo_producto()
{
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),Letra_Azul_fb );
     gotoxy(24,8);cout<<">> REGISTRO DE NUEVO PRODUCTO <<";   
     gotoxy(15,10);cout<<"C\242digo:";
	 gotoxy(15,12);cout<<"Nombre:";
	 gotoxy(16,14);cout<<"Marca:";
	 gotoxy(15,16);cout<<"Modelo:";
	 gotoxy(16,18);cout<<"Stock:";
	 gotoxy(17,20);cout<<"Tipo:                                  (HARDWARE/SOFTWARE) ";
	 	 
	 gotoxy(24,12);cout<<"                                                           ";
	 gotoxy(24,14);cout<<"                                                           ";
	 gotoxy(24,16);cout<<"                                                           ";
	 gotoxy(24,18);cout<<"                                                           ";
	 gotoxy(24,20);cout<<"                              ";

     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);

	 Cod_a=fopen("ARTICULO.txt","a+b");
    //----------Imprimir en archivo 
     ARTICULO.cod_art=Obtener_cod_a();
     gotoxy(24,10);cout<<ARTICULO.cod_art; 
	
	 gotoxy(24,12); cin.ignore();cin.getline(ARTICULO.nomb_art, 30);
	 gotoxy(24,14);  cin.getline(ARTICULO.marca,20);
	 gotoxy(24,16);  cin.getline(ARTICULO.modelo,20);
	 gotoxy(24,18); cin>>ARTICULO.stock;
	 gotoxy(24,20); cin.ignore(); cin>>ARTICULO.tipo_art;
	 
	 fseek(Cod_a, 0, SEEK_END);
     fwrite(&ARTICULO, sizeof(struct Articulo),1,Cod_a);
     fclose(Cod_a);
	 
}

//------------------PANTALLA TRANSACCIONES
void transacciones()
{
    int Cursor_Pos = 12;
	 system("cls");
	 Titulo ();gotoxy(0,22);lineadoble();
     gotoxy(0,23);cout<<" Use las teclas direccionales - ENTER para elegir una opcion -  ESC para salir" << endl;
     gotoxy(0,24);lineadoble();
     gotoxy(30,16);    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
	 gotoxy(25,7);cout<<"*** ADMINISTRAR TRANSACCIONES ***"<<endl<<endl;
	 gotoxy(30,16);    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Letra_Azul_fb);
	 gotoxy(33,12);cout<<"(1) COMPRA";
	 gotoxy(33,14);cout<<"(2) DEVOLUCION";
	 gotoxy(30,16);    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Verde);
     gotoxy(33,16);cout<<"(3) IR A MENU";
	 gotoxy(30,Cursor_Pos);
     cout << (char)Cursor;
     gotoxy(78,23);
//Control del movimiento de las teclas direccionales arriba-abajo, mientras no se haya pulsado la tecla ENTER
          //Nota: Cuando se pulsa Enter se ingresa a la opción de menú señalada 
    do{
        if (kbhit())
        {
            KEY_PAD = getch();
            switch (KEY_PAD)
            {
                case KEY_UP:
                {if (Cursor_Pos >= 14) Cursor_Pos = Cursor_Pos - 2;}
                break;
                case KEY_DOWN:
                {if (Cursor_Pos <= 14) Cursor_Pos = Cursor_Pos + 2;}
                break;
                case KEY_ENTER:
                {
                    switch (Cursor_Pos)
                    {
                        case 12: compra(); break;
                        case 14: /*articulos()*/; break;
                        case 16: menu(); break;                        
                    }
                }
                break;
                case KEY_ESC: getch(); break;
            }
            //Muestra un espacio vacio a la derecha de las opciones del menú
            for (int i = 0; i<5 ; i+=2)
            {gotoxy(30,12+i);  cout << (char) 0;}
            //Para mostrar la Flechita verde a la izquierda de la opcion seleccionada mediante las teclas direccionales 
            gotoxy(30,Cursor_Pos);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Verde);
            cout << (char)Cursor;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Letra_Azul_fb);
            gotoxy(78,23);
        }
    }while (KEY_PAD!=27); 	 
	 getch();
}

//-------------FUNCION COMPRA (forma parte de la entidad transacciones)
void compra()
{      
	 int Cursor_Pos=4;      
     system("cls");
	 Titulo (); barra_inferior();
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),Color );
	 gotoxy(33,6);cout<<">> COMPRA <<";
	 gotoxy(78, 24);
	 do{
        if (kbhit())
        {
            KEY_PAD = getch();
            switch (KEY_PAD)
            {
                case KEY_LEFT:
                {if (Cursor_Pos >= 19) Cursor_Pos = Cursor_Pos - 15;}
                break;
                case KEY_RIGHT:
                {if (Cursor_Pos <= 49) Cursor_Pos = Cursor_Pos + 15;}
                break;
                case KEY_ENTER:
                {
                    switch (Cursor_Pos)
                    {
                        case 4: nueva_compra(); break;
                        case 19: /*articulos();*/ break;
                        case 34: /*transacciones();*/break;
                        case 49: /*return 4;*/ break;
                        case 64: menu(); break;                        
                    }
                }
                break;
                case KEY_ESC: getch(); break;
            }
            //Muestra un espacio vacio a la derecha de las opciones del menú
            for (int i = 0; i<64 ; i+=15)
            {gotoxy(4+i, 23);  cout << (char) 0;}
            //Para mostrar la Flechita verde a la izquierda de la opcion seleccionada mediante las teclas direccionales 
            gotoxy(Cursor_Pos, 23);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Verde);
            cout << (char)Cursor;
            gotoxy(78,24);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Letra_Azul_fb);
        }
    }while (KEY_PAD!=27);
  
}

//------------------NUEVA COMPRA
void nueva_compra()
{   
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),Letra_Azul_fb );
	 gotoxy(7,10);cout<<"C\242digo de la transacci\242n:";
	 gotoxy(15,11);cout<<"C\242digo Proveedor:";
	 gotoxy(16,12);cout<<"C\242digo articulo:";
	 gotoxy(16,13);cout<<"Fecha de compra:";
	 gotoxy(17,14);cout<<"Costo unitario:";
	 gotoxy(23,15);cout<<"Cantidad:";
	 gotoxy(20,16);cout<<"Costo Total:";
	 gotoxy(10,17);cout<<"Precio venta Unitario:";
	 
	 gotoxy(34,10);cout<<"                                                 ";
	 gotoxy(34,11);cout<<"                                                 ";
	 gotoxy(34,12);cout<<"                                                 ";
	 gotoxy(34,13);cout<<"                                                 ";
	 gotoxy(34,14);cout<<"                                                 ";
	 gotoxy(34,15);cout<<"                                                  ";
	 gotoxy(34,16);cout<<"                                                 ";
	 gotoxy(34,17);cout<<"                                                 ";

     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),Color_Def );
     Cod_c=fopen("COMPRA.txt","a+");
    //----------Imprimir en archivo 
     COMPRA.cod_t=Obtener_cod_t();
     gotoxy(34,10);cout<<COMPRA.cod_t;
	 gotoxy(34,11); cout<<PROVEEDOR.cod_prov;
	 gotoxy(34,12); cout<<ARTICULO.cod_art;
	 gotoxy(34,13); cin>>COMPRA.FechaCompra;
	 gotoxy(34,14); cin>>COMPRA.CostoUni;
	 gotoxy(34,15); cin>>COMPRA.CantArt;
	 COMPRA.CostoTotal=COMPRA.CantArt*COMPRA.CostoUni;
	 gotoxy(34,16); cout<<COMPRA.CostoTotal;
	 //PrecioUni=CostoUni*1.15;
     COMPRA.PrecioUni=COMPRA.CostoUni*1.2;
     gotoxy(34,17); cout<<COMPRA.PrecioUni;
     fseek(Cod_c, 0, SEEK_END);
     fwrite(&COMPRA, sizeof(struct Compra),1,Cod_c);
     fclose(Cod_c);
}


//**********VALIDACION DEL RUC DEL PROVEEDOR

bool validacion_ruc(char ruc[13])
{    
     int i=0;
     int b=0;
     int c=0;
     bool tam=true;       
          for(int i=0; i<13 && tam==true ; i++)
          {          
           if(!isdigit(ruc[i]) )
             { tam=false; }           
          }      
          return(tam);     
}  

//**********VALIDACION De INGRESO DE PALABRAS

bool val_palabras(char palabra[40])
{    
     int i=0;
     bool letra=true;               
          for(int i=0; i<39; i++)
          {          
           if(isdigit(palabra[i]) )
             { letra=false; }           
          }          
          return(letra);     
} 

/*****************FUNCIONES PARA GENERAR EL CÓDIGO SECUENCIAL******************/
//---------Esta función genera el código secuencial para proveedor
int Obtener_cod_p()
{
    if(feof(Cod_p))
    return 1;
    else
    {
    fseek(Cod_p, - sizeof (struct Proveedor), SEEK_END);
    fread(&PROVEEDOR, sizeof(struct Proveedor), 1, Cod_p);
    return(PROVEEDOR.cod_prov+1);
    }
}

//---------Esta función genera el código secuencial para articulo
int Obtener_cod_a()
{
    if(feof(Cod_a))
    return 1;
    else
    {
    fseek(Cod_a, - sizeof (struct Articulo), SEEK_END);
    fread(&ARTICULO, sizeof(struct Articulo), 1, Cod_a);
    return(ARTICULO.cod_art+1);
    }
}

//---------Esta función genera el código secuencial para compra
int Obtener_cod_t()
{
    if(feof(Cod_c))
    return 1;
    else
    {
    fseek(Cod_c, - sizeof (struct Compra), SEEK_END);
    fread(&COMPRA, sizeof(struct Compra), 1, Cod_c);
    return(COMPRA.cod_t+1);
    }
}
