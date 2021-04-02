#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <directory.h>
#include <contact.h>
#include <hash.h>

/*
  Crée un nouvel annuaire contenant _len_ listes vides.
*/
struct dir *dir_create(uint32_t len)
{
    struct dir * directory =  (struct dir*) malloc(sizeof(struct dir));
    directory->size=len;
    directory->count=0;
    directory->C_table = (contact**) calloc (directory->size, sizeof(contact*));
    for (uint32_t i;i<len;i++)
    {
      directory->C_table[i]=NULL;
    }
    return directory;
};
/*
  Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
  Sinon, la fonction retourne NULL.
*/
char *dir_insert(struct dir *dir,  char *name,  char *num)
{
   struct contact * contact_item = creation_contact(name, num);
    uint32_t index=hash(name);


    struct contact * contact_test=dir->C_table[index];
    if (contact_test==NULL)
    {
      if (dir->size==dir->count)
      {
        printf ("Error: directory full\n");
        free_contact (contact_item);
      }
      else
      dir->C_table[index] = contact_item; 
      dir->count++;
       return NULL;
    }
    else
    {
      if (strcmp(dir->C_table[index]->nom,name)==0)
      {  
        if (dir->size==dir->count)
        {
          printf ("Error: directory full\n");
          free_contact (contact_item);
        }
        else
       {
        char *ancien_numero;
        strcpy(ancien_numero,dir->C_table[index]->numero);
        strcpy(dir->C_table[index]->numero,num); 
        dir->count++;
        return ancien_numero;
       }
     }
     else
     { 
      struct contact *cont;
      cont=dir->C_table[index];
      while(cont->suivant!=NULL)
      {
        if (strcmp(cont->suivant->nom,contact_item->nom)==0)
      {
        char * ancien_numero=cont->suivant->numero;

        cont->suivant->numero=contact_item->numero;
        return  ancien_numero;
      }
        cont=cont->suivant;
        
      }
      
      cont->suivant=contact_item;
      dir->count++;
      return NULL;
      }
    }
    return NULL;  
};

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
const char *dir_lookup_num(struct dir *dir, const char *name)
{
   uint32_t index=hash(name);
    struct contact *contact_item= dir->C_table[index];
    while (contact_item != NULL) {
        if (strcmp(contact_item->nom, name) == 0)
            return contact_item->numero;
        else contact_item=contact_item->suivant;  
    }
    printf ("Nom Inexistant !\n");
    return NULL;
};

/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
void dir_delete(struct dir *dir, const char *name)
{
    uint32_t index=hash(name);
    struct contact *contact_item=dir->C_table[index];
    struct contact *contact_pres;
    if (strcmp(contact_item->nom,name)==0)
      {
        dir->C_table[index]=dir->C_table[index]->suivant;
        free_contact(contact_item);
        contact_item= NULL;
      }
    while (contact_item!=NULL)
    {
      if (strcmp(contact_item->nom,name)==0)
      {
        contact_pres->suivant=contact_item->suivant;
        free_contact(contact_item);
      }
      contact_pres=contact_item;
      contact_item=contact_item->suivant;
    }
};

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
void dir_free(struct dir *dir)
{
   for (uint32_t i=0; i<dir->size; i++) 
    {
        struct contact* contact_item = dir->C_table[i];
        while (dir->C_table[i]!=NULL)
        {
          while (contact_item!=NULL)
          {
            dir->C_table[i]=contact_item->suivant;
            free_contact(contact_item);
            contact_item=dir->C_table[i];
          }
          contact_item=dir->C_table[i];

        }
    }
 
    free(dir->C_table);
    free(dir);
    dir=NULL;
};
/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
void dir_print(struct dir *dir)
{
    struct contact * parc;
  printf("\n-------------------\n");
  for (uint32_t i=0;i<dir->size;i++)
  {

    parc=dir->C_table[i];
    while (parc!=NULL)
    {
    printf("Index:%d, Nom:%s, Numéro:%s\n", i, parc->nom, parc->numero);
    parc=parc->suivant;
    }

  
  }
  printf("\n-------------------\n");
};
