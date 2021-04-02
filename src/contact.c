/* TODO! */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <directory.h>
#include <hash.h>

//creation de structure contact


struct contact
{
  //nom=key to navigate hash
  char *nom;
  //numero est la valeur de la case
  char *numero;

  struct contact * suivant;
};

struct contact * creation_contact (const char* name ,const char* num)
{
	struct contact* cont = (struct contact*) malloc (sizeof(struct contact*));
  cont->nom = (char*) malloc(strlen(name) + 1);
  cont->numero= (char*) malloc(strlen(num) + 1);
  cont->suivant=NULL;
  strcpy(cont->nom, name);
  strcpy(cont->numero, num);
  printf ("//");
    return cont;
};

void free_contact (struct contact * cont)
{
	free(cont->nom);
    free(cont->numero);
    free(cont);
};



