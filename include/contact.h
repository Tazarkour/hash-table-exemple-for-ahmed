#ifndef _CONTACT_H_
#define _CONTACT_H_

/*
  Un contact représente une association {nom, numéro}.
*/
struct contact;

contact* creation_contact (char* name, char* num);

void free_contact (contact * cont);

/* TOUT DOUX: à compléter */
/* Profitez de cette période sombre pour braver les interdits et rétablir le contact. */

#endif /* _CONTACT_H_ */