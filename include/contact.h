#ifndef _CONTACT_H_
#define _CONTACT_H_

/*
  Un contact représente une association {nom, numéro}.
*/
typedef struct contact contact;



struct contact* creation_contact (char* name, char* num);

void free_contact (struct contact * cont);

/* TOUT DOUX: à compléter */
/* Profitez de cette période sombre pour braver les interdits et rétablir le contact. */

#endif /* _CONTACT_H_ */
