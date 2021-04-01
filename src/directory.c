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
      printf ("Error : Collision detected, two indexes have same ASCII code but diffrent names\n");
      return NULL;
      }
    }

   
};

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
const char *dir_lookup_num(struct dir *dir, const char *name)
{
    uint32_t index=hash(name);
    struct contact *contact_item= dir->C_table[index];
    if (contact_item != NULL) {
        if (strcmp(contact_item->nom, name) == 0)
            return contact_item->numero;
    }
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
    if (contact_item != NULL)
    free_contact(contact_item);
};

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
void dir_free(struct dir *dir)
{
    for (uint32_t i=0; i<dir->size; i++) 
    {
        struct contact* contact_item = dir->C_table[i];
        if (contact_item != NULL)
        free_contact(contact_item);
    }
 
    free(dir->C_table);
    free(dir);
};
/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
void dir_print(struct dir *dir)
{
    printf("\n-------------------\n");
    for (uint32_t i=0; i<dir->size; i++) {
        if (dir->C_table[i]) {
            printf("Index:%d, Nom:%s, Numéro:%s\n", i, dir->C_table[i]->nom, dir->C_table[i]->numero);
        }
    }
    printf("----------------------\n");
};
