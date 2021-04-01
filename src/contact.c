/* TODO! */
#include <stdlib.h>
#include <stdio.h>

#include <directory.h>
#include <hash.h>

//creation de structure contact
typedef struct contact contact;
struct contact
{
	//nom=key to navigate hash
	char *nom;
	//numero est la valeur de la case
	char *numero;
}contact;

typedef struct dir dir;

struct dir
{
	//tableau de contacts
	contact **C_table;
	//taille du tableau pour reference
	unsigned int size;
	//compteur count pour 
	unsigned int count;
}

contact* creation_contact (char* name, char* num)
{
	contact* cont = (contact*) malloc (sizeof(contact));
 	contact->nom= (char*) malloc(strlen(name)+1);
 	contact->numero= (char*) malloc(unsigned int);
 	strcpy(cont->nom, name);
 	strcpy(cont->numero, num);
    return cont;
}

void free_contact (contact * cont)
{
	free(contact->nom);
    free(contact->numero);
    free(contact);
}



