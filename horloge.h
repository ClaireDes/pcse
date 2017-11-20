#include <stdio.h>
#include <screen.h>
#include <debug.h>
#include <stdbool.h>


#define TAILLE_HORLOGE 8
#define CLOCKFREQ 50
#define QUARTZ 0x1234dd

void affiche_coin_droite(char *str, uint32_t taille);
void init_horloge();
void tic_PIT();
void masque_IRQ(uint32_t num_IT, bool);
void ordonnance();
int nbr_sec();
