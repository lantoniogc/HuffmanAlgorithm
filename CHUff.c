//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Librerias utilizadas //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
#include <stdio.h>  // Biblioteca estandar de las funciones de (entrada y salida)
#include <ctype.h>  // se utilizo para la funcion(isdigit)
#include <stdlib.h> // se utilizo para las funciones (atoi, exit, system)
#include <string.h> // Biblioteca estandar de las funciones de (Arreglo de caracteres)
#include <unistd.h> // Biblioteca para el uso de sleep en la seccion grafica del programa

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Definiciones//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
#define Max_Reg 255 //Maximo Numero de Registros

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Estructuras //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
typedef struct nodohof
{
	float value;						 /* La cantidad de veces que se repite el caracter */
	char bin[2];						 /* El valor binario del nodo (0 o 1) */
	char caracter;						 /* El caracter almacenado en el nodo */
	char codigo[1000];					 /* Codigo de la codificacion */
	struct nodohof *left, *right, *next; /* Nodo izquierdo - Nodo derecho - Nodo siguiente */
} Nodohof;

struct ordenar
{
	float value;   /* La cantidad de veces que se repite el caracter */
	char caracter; /* El caracter almacenado en el nodo */
} hojas[255];

struct base
{
	float value;	  /*La cantidad de veces que se repite el caracter */
	char caracter;	/* El caracter almacenado en el nodo */
	char codigo[100]; /* Codigo de la codificacion */
	int valido;		  /* Si ha sido usado este valor del arreglo (Utilizado para organizar) */
} Base[255];

struct
{
	char Character[10]; /* El caracter almacenado del diccionario */
	char Code[100];		/* El codigo proveniente del diccionario */
} Registro[Max_Reg];

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Declaracion de funciones & Variables Globales //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int nhojas, nbase;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// to continue... //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void PreesEnter(void)
{
	setbuf(stdin, NULL); // limpia el Buffer
	printf("\n\tPress 'Enter' to continue...");
	getchar();
	system("clear");
	system("clear"); //clear scream
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~// Titulo del proyecto (Diseño) //~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void Titulo(void)
{

	printf("\t╔═╗┬  ┌─┐┌─┐┬─┐┬┌┬┐┌┬┐┌─┐  ┌┬┐┌─┐  ╦ ╦┬ ┬┌─┐┌─┐┌┬┐┌─┐┌┐┌\n\t╠═╣│  │ ┬│ │├┬┘│ │ ││││ │   ││├┤   ╠═╣│ │├┤ ├┤ │││├─┤│││\n\t╩ ╩┴─┘└─┘└─┘┴└─┴ ┴ ┴ ┴└─┘  ─┴┘└─┘  ╩ ╩└─┘└  └  ┴ ┴┴ ┴┘└┘\n");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~// Menu principal del proyecto (Diseño) //~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void Menu(char *op)
{
	Titulo();
	printf("\n    -Seleccione la opcion:\n");
	printf("\n                          -> 1  Codificar   : Codifica un archivo\n");
	printf("\n                          -> 2  Decodificar : Decodifica un archivo\n");
	printf("\n\t-Opcion (1-2) => ");
	setbuf(stdin, NULL); // limpia el Buffer
	scanf("%[^\n]s", op);
	setbuf(stdin, NULL); // limpia el Buffer
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Borra los Espacios de un String //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void Remove_Spaces(char *String)
{
	int i, j;

	for (i = 0, j = 0; String[i] != '\0'; i++)
	{

		if (String[i] != 32)
			String[j++] = String[i];
	}
	String[j] = '\0';
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Borra n-1 Caracteres de un String //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void Remove_Character(char *String, char Character)
{
	int i, j, flag = 0;

	for (i = 0, j = 0; String[i] != '\0'; i++)
	{

		if ((String[i] == Character) && (flag == 0))
		{
			flag = 1;
			String[j++] = String[i];
		}

		if (String[i] != Character)
			String[j++] = String[i];
	}
	String[j] = '\0';
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Si los caracteres de una string son solo espacios //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/
int sonEspacios(char c[])
{
	int i = 0;

	while (c[i] != '\0')
	{

		if (c[i] != 32)
			return 0;
		i++;
	}
	return 1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Cargar Archivo //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void Upload_File(char *File)
{
	printf("\n  Archivo de Prueba: Seed.txt\n");
	printf("\n  Upload File: ");
	setbuf(stdin, NULL); // limpia el Buffer
	scanf("%s", File);   // Selecciona Archivo...
	PreesEnter();		 //Press 'Enter' to continue...
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Cargar Archivo //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void Upload_Encode(char *Encode)
{
	printf("\n  Archivo de Prueba: Encode.txt\n");
	printf("\n  Upload File Encode: ");
	setbuf(stdin, NULL); // limpia el Buffer
	scanf("%s", Encode); // Selecciona Archivo...
	PreesEnter();		 //Press 'Enter' to continue...
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Cargar Archivo //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void Upload_Dictionary(char *Dictionary)
{
	printf("\n  Archivo de Prueba: Dictionary.txt\n");
	printf("\n  Upload Dictionary: ");
	setbuf(stdin, NULL);	 // limpia el Buffer
	scanf("%s", Dictionary); // Selecciona Archivo...
	PreesEnter();			 //Press 'Enter' to continue...
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~// Imprime el registro de la posicion i //~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void imprime_registro(int reg, int Num_Reg)
{

	if (reg < 0 || reg >= Num_Reg)
	{
		fprintf(stderr, "Registro no encontrado\n");
		return;
	}
	printf("\n");
	printf("   %s:%s", Registro[reg].Character, Registro[reg].Code);
	printf("\n");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~// Llena los registros necesarios para leer el diccionario //~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int LlenarRegistros(char buffer[], int *NR)
{
	int i = 0, flag = 1, val = 0;
	char c[100];

	*NR = 0;

	while (buffer[i] != '\0')
	{
		if (buffer[i] == ':')
		{
			c[val] = '\0';
			if (sonEspacios(c) == 1)
				Remove_Character(c, 32);
			else
				Remove_Spaces(c);
			strcpy(Registro[*NR].Character, c);
			c[0] = '\0';
			val = 0;
			flag = 0;
			i++;
		}

		if (buffer[i] == '\n' && !flag)
		{
			c[val] = '\0';
			Remove_Spaces(c);
			strcpy(Registro[*NR].Code, c);
			(*NR)++;
			c[0] = '\0';
			val = 0;
			flag = 1;
			i++;
		}

		if (flag && buffer[i] == '\n' && buffer[i + 1] == ':')
		{
			c[val] = buffer[i];
			val++;
		}

		if (flag && buffer[i] == '\n' && buffer[i + 1] == '\n')
		{
			c[val] = buffer[i];
			val++;
		}

		if (flag && buffer[i] != '\n')
		{
			c[val] = buffer[i];
			val++;
		}

		if (!flag && buffer[i] != '1' && buffer[i] != '0' && buffer[i] != ' ')
			return 0;

		if (!flag && buffer[i] != ':')
		{
			c[val] = buffer[i];
			val++;
		}

		if (buffer[i + 1] == '\0')
		{
			c[val] = '\0';
			Remove_Spaces(c);
			strcpy(Registro[*NR].Code, c);
			(*NR)++;
			c[0] = '\0';
			val = 0;
			flag = 1;
		}

		i++;
	}
	return 1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~// Lee los registros de un archivo //~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int Read_Dictionary(char *Dictionary, int *Num_Reg)
{
	FILE *fd;
	int x, tam;
	char *buffer, c;

	if ((fd = fopen(Dictionary, "r")) == NULL)
	{
		fprintf(stderr, "\n  ERROR: No se Pudo Abrir El Archivo Para su Lectura\n");
		exit(1);
	}

	*Num_Reg = 0;

	while ((c = fgetc(fd)) != EOF)
		x++;

	rewind(fd);
	buffer = (char *)malloc((x + 1) * sizeof(char));
	x = 0;
	while ((c = fgetc(fd)) != EOF)
	{
		buffer[x] = c;
		x++;
	}
	tam = strlen(buffer);
	buffer[tam - 1] = '\0';

	fclose(fd);

	if (LlenarRegistros(buffer, Num_Reg))
	{
		free(buffer);
		return 1;
	}
	else
	{
		free(buffer);
		return 0;
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Codifica el archivo //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void Encode(char *File, char *encode, int Num_Reg)
{
	FILE *fd, *C;
	char Character;
	int i = 0;

	if ((fd = fopen(File, "r")) == NULL)
	{
		fprintf(stderr, "\n  ERROR: No se Pudo Abrir El Archivo Para su Lectura\n");
		exit(1);
	}
	if ((C = fopen(encode, "w")) == NULL)
	{
		fprintf(stderr, "\n  ERROR: No se Pudo Abrir El Archivo Para su Lectura\n");
		exit(1);
	}
	while ((Character = fgetc(fd)) != EOF)
		for (i = 0; i < Num_Reg; i++)
			if (Character == Registro[i].Character[0])
				fprintf(C, "%s", Registro[i].Code);

	fclose(fd);
	fclose(C);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Decodifica el archivo //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void Decode(char *encode, char *decode, int Num_Reg)
{
	FILE *fd, *D;
	char Character, Aux[100];
	int i = 0, j = 0;

	if ((fd = fopen(encode, "r")) == NULL)
	{
		fprintf(stderr, "\n  ERROR: No se Pudo Abrir El Archivo Para su Lectura\n");
		exit(1);
	}
	if ((D = fopen(decode, "w")) == NULL)
	{
		fprintf(stderr, "\n  ERROR: No se Pudo Abrir El Archivo Para su Lectura\n");
		exit(1);
	}
	while ((Character = fgetc(fd)) != EOF)
	{

		Aux[j] = Character;
		j++;
		Aux[j] = '\0';

		for (i = 0; i < Num_Reg; i++)
			if (strcmp(Aux, Registro[i].Code) == 0)
			{
				fprintf(D, "%s", Registro[i].Character);
				j = 0;
			}
	}
	fclose(fd);
	fclose(D);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Muestra un arbol dado un nodo, y el nivel se incia en 0 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void imprime(Nodohof *arbol, int nivel)
{
	int i;

	if (arbol == NULL)
		return;
	imprime(arbol->right, nivel + 1);
	for (i = 0; i < nivel; i++)
		printf("  ");
	printf("[%.2f '%c']\n", arbol->value, arbol->caracter);
	imprime(arbol->left, nivel + 1);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Muestra una lista dado un nodo //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void Mostrar(Nodohof *listp)
{

	printf("\n\n");
	if (listp == NULL)
		return;
	while (listp != NULL)
	{
		printf("    ('%.2f', '%c')\n", listp->value, listp->caracter);
		listp = listp->next;
		if (listp == NULL)
			printf("NULL\n");
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Llena el archivo de diccionario //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void CrearDiccionario(FILE *fd)
{
	int i, j, pos;
	float org;

	for (i = 0; i < nbase; i++)
		Base[i].valido = -1;

	for (i = 0; i < nbase; i++)
	{
		org = 0;
		pos = -1;
		for (j = 0; j < nbase; j++)
		{
			if (Base[j].valido == -1 && Base[j].value > org)
			{
				org = Base[j].value;
				pos = j;
			}
		}
		fprintf(fd, "%c:%s\n", Base[pos].caracter, Base[pos].codigo);
		Base[pos].valido = 1;
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Crea las bases del diccionario para ser creado //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void CrearBaseDiccionario(Nodohof *arbol)
{

	if (!arbol)
		return;

	if ((!arbol->left) && (!arbol->right))
	{
		Base[nbase].value = arbol->value;
		Base[nbase].caracter = arbol->caracter;
		Base[nbase].codigo[0] = '\0';
		strcpy(Base[nbase].codigo, arbol->codigo);
		nbase++;
	}
	CrearBaseDiccionario(arbol->left);
	CrearBaseDiccionario(arbol->right);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Se encarga de hacer el proceso de crear diccionario //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void LlenarDiccionario(Nodohof *arbol)
{
	FILE *fd;

	if ((fd = fopen("Dictionary.txt", "w")) == NULL)
	{
		fprintf(stderr, "\n  ERROR: No se pudo abrir el archivo para su lectura\n");
		exit(1);
	}
	nbase = 0;
	CrearBaseDiccionario(arbol);
	CrearDiccionario(fd);
	fclose(fd);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Crear el codigo que se utilizara en el diccionario //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void CrearCodigos(Nodohof *arbol, char code[], int nivel)
{
	char *rcode, *lcode;

	if (!arbol)
		return;

	strcat(arbol->codigo, code);

	if ((!arbol->left) && (!arbol->right))
	{
		arbol->codigo[0] = '\0';
		strcat(arbol->codigo, code);
	}

	lcode = (char *)malloc(strlen(code) + 2);
	rcode = (char *)malloc(strlen(code) + 2);
	sprintf(lcode, "%s0", code);
	sprintf(rcode, "%s1", code);

	CrearCodigos(arbol->left, lcode, nivel + 1);
	CrearCodigos(arbol->right, rcode, nivel + 1);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Insertar ordenado en listas //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Nodohof *Insert(Nodohof *listp, Nodohof *ap)
{
	Nodohof *p, *prev = NULL;

	for (p = listp; p != NULL && p->value < ap->value; p = p->next)
		prev = p;
	ap->next = p;
	if (prev == NULL)
		return ap;
	prev->next = ap;
	return listp;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Crea un arbol a partir de una lista //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void CrearArbol(Nodohof *listp, Nodohof **arbol)
{
	float primero, segundo;

	if (listp == NULL)
		return;

	while (listp->next != NULL)
	{
		// Actualiza la lista mediante los valores de un nodo nuevo.
		Nodohof *ap = (Nodohof *)malloc(sizeof(Nodohof));
		listp->bin[0] = '0';
		listp->bin[1] = '\0';
		listp->next->bin[0] = '1';
		listp->next->bin[1] = '\0';
		primero = listp->value;
		segundo = listp->next->value;
		ap->value = primero + segundo;
		ap->left = listp;
		ap->right = listp->next;
		Insert(listp, ap);
		listp = listp->next->next;
		// Se le asigna el Nodo de la lista que tenga el arbol a la nodo del arbol.
		if (listp)
			*arbol = listp;
	}
	return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Crea la lista para el arbol //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Nodohof *LlenarLista(Nodohof *listp)
{
	int x;

	for (x = 0; x < nhojas; x++)
	{
		Nodohof *a = (Nodohof *)malloc(sizeof(Nodohof));

		a->value = hojas[x].value;
		a->caracter = hojas[x].caracter;
		a->left = a->right = NULL;
		listp = Insert(listp, a);
	}
	return listp;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Calcula si se encuentra un caracter repetido //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int ExisteHoja(char tbas)
{
	int i;

	for (i = 0; i < nhojas; i++)
		if (tbas == hojas[i].caracter)
			return i;
	return -1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Crea las bases para la lista //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void InfoCod(char Nom_archivo[])
{
	FILE *cod;
	char c, *tbas;
	int x = 0, exs, tam;

	if ((cod = fopen(Nom_archivo, "r")) == NULL)
	{
		fprintf(stderr, "No se puede abrir el archivo\n");
		exit(EXIT_FAILURE);
	}

	while ((c = fgetc(cod)) != EOF)
		x++;
	rewind(cod);
	tbas = (char *)malloc((x + 1) * sizeof(char));
	x = 0;
	while ((c = fgetc(cod)) != EOF)
	{
		tbas[x] = c;
		x++;
	}

	tam = strlen(tbas);
	x = 0;
	while (x < tam)
	{
		if ((exs = ExisteHoja(tbas[x])) != -1)
			hojas[exs].value++;
		else
		{
			hojas[nhojas].value = 1;
			hojas[nhojas].caracter = tbas[x];
			nhojas++;
		}
		x++;
	}
	for (x = 0; x < nhojas; x++)
		hojas[x].value = (hojas[x].value / (nhojas - 1));

	free(tbas);
	fclose(cod);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Anula una lista //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void Anula(Nodohof *listp)
{
	Nodohof *act;

	if (listp == NULL)
		return;

	for (act = listp->next; act; act = listp->next)
	{
		listp->next = act->next;
		free(act);
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Crea una nueva lista //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Nodohof *Newlist()
{
	Nodohof *listp;

	if ((listp = (Nodohof *)malloc(sizeof(Nodohof))) == NULL)
		exit(1);

	listp = listp->next = listp->left = listp->right = NULL;
	return listp;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//  Main  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int main(int argc, char *argv[])
{

	Nodohof *arbol = NULL;
	Nodohof *listp = Newlist();

	char op[] = "No Ha Entrado";
	char code[100];
	code[0] = '\0';
	char File[20], Dictionary[20] = "Dictionary.txt", encode[20] = "Encode.txt", decode[20] = "Decode.txt";

	int Num_Reg = 0;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
op:
	Menu(op);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	if (strcmp(op, "1") == 0)
	{
		system("clear");
		printf("\t╔═╗┌─┐┌┬┐┬┌─┐┬┌─┐┌─┐┌─┐┬┌─┐┌┐┌\n\t║  │ │ │││├┤ ││  ├─┤│  ││ ││││\n\t╚═╝└─┘─┴┘┴└  ┴└─┘┴ ┴└─┘┴└─┘┘└┘\n");
		Upload_File(File);
		printf("\t╔═╗┌─┐┌┬┐┬┌─┐┬┌─┐┌─┐┌─┐┬┌─┐┌┐┌\n\t║  │ │ │││├┤ ││  ├─┤│  ││ ││││\n\t╚═╝└─┘─┴┘┴└  ┴└─┘┴ ┴└─┘┴└─┘┘└┘\n");
		InfoCod(File);
		listp = LlenarLista(listp);
		CrearArbol(listp, &arbol);
		CrearCodigos(arbol, code, 0);
		LlenarDiccionario(arbol);
		Read_Dictionary(Dictionary, &Num_Reg);
		Encode(File, encode, Num_Reg);
		Anula(listp);
		printf("\n  Archivo Codificado con Exito \n");
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	if (strcmp(op, "2") == 0)
	{
		system("clear");
		printf("\t╔╦╗┌─┐┌─┐┌┬┐┬┌─┐┬┌─┐┌─┐┌─┐┬┌─┐┌┐┌\n\t║║├┤ │ │ │││├┤ ││  ├─┤│  ││ ││││\n\t═╩╝└─┘└─┘─┴┘┴└  ┴└─┘┴ ┴└─┘┴└─┘┘└┘\n");
		Upload_Dictionary(Dictionary);
		printf("\t╔╦╗┌─┐┌─┐┌┬┐┬┌─┐┬┌─┐┌─┐┌─┐┬┌─┐┌┐┌\n\t║║├┤ │ │ │││├┤ ││  ├─┤│  ││ ││││\n\t═╩╝└─┘└─┘─┴┘┴└  ┴└─┘┴ ┴└─┘┴└─┘┘└┘\n");
		if (!Read_Dictionary(Dictionary, &Num_Reg))
		{
			printf("\n  ERROR! Diccionario invalido... Saliendo del programa\n");
			return EXIT_FAILURE;
		}
		Upload_Encode(encode);
		printf("\t╔╦╗┌─┐┌─┐┌┬┐┬┌─┐┬┌─┐┌─┐┌─┐┬┌─┐┌┐┌\n\t║║├┤ │ │ │││├┤ ││  ├─┤│  ││ ││││\n\t═╩╝└─┘└─┘─┴┘┴└  ┴└─┘┴ ┴└─┘┴└─┘┘└┘\n");
		Decode(encode, decode, Num_Reg);
		printf("\n  Archivo Decodificado con Exito \n");
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	if ((strcmp(op, "1") != 0) && (strcmp(op, "2") != 0))
	{
		printf("\n\t\tError en la opcion\n");
		PreesEnter();
		goto op;
	}

	return EXIT_SUCCESS;
}
