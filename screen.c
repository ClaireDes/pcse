
#include <screen.h>


/* Prend en parametres les coordonnees d'un point
retoune l'adresse memoire de ce point */
uint16_t* ptr_mem (uint32_t lig, uint32_t col) {

	uint16_t * addr_pos = (uint16_t*)(MEM_VIDEO + 2*(lig*NB_COL+col));
	return addr_pos;
}

/* Prend en  parametres les coordonnees d'un point, un charactere et le format de la police et du fond
Ecrit ce charactere dans ce format au point indique
deplace le curseur d'un cran apres en appelant place_curseur */
void ecrit_car(uint32_t lig, uint32_t col, char c, uint8_t color_font, uint8_t color_back ) {

	uint16_t* ptr = ptr_mem(lig, col);
	uint16_t car = c | (color_back << 4 | color_font) << 8;
	*ptr = car;
}

/* Parcours l'ecran et ecrit un espace sur fond noir sur chaque case avec ecrit_car
place le curseur en 0,0 avec place_curseur */
void efface_ecran(void) {

	for(uint32_t i=0; i<NB_LINE; i++) {
		for(uint32_t j=0; j<NB_COL; j++) {
			ecrit_car(i,j,ESPACE,FONT_COLOR,BACK_COLOR);
		}
	}
	place_curseur(0,0);
}

/* Prend en parametres les coordonnees d'un point de l'ecran
met a jour les variables globales de position du curseur
met a jour la position reelle du curseur en prenant en compte le retour a la ligne*/
void place_curseur(uint32_t lig, uint32_t col) {

	// mise a jour des variables de position du curseur
	x_curs = col;
	y_curs = lig;

	// On restreint la position du curseur à l'ecran
	if (x_curs > NB_COL-1) {
		y_curs += 1;
		x_curs = 0;
	}
	if (y_curs >= NB_LINE-1) {
		y_curs = NB_LINE-1;
		x_curs = 0;
		defilement();
	}

	uint16_t pos = col + NB_COL * lig;
	outb(PARTIE_B, P_COM);
	outb(pos, P_DATA);
	outb(PARTIE_H, P_COM);
	outb(pos>>8, P_DATA);
}

/* traite les cas particuliers de charactere a prendre en compte
appelle ecrit_car si rien de special */
void traite_car(char c) {


	switch (c) {

		case '\b' : //retour
			if ( x_curs != 0) {
				place_curseur(y_curs, x_curs - 1);
				break;
			}

		case '\t' : //tabulation
			if (x_curs < NB_COL - TAILLE_TAB) {
				place_curseur(y_curs, (x_curs/TAILLE_TAB+1)*TAILLE_TAB);
				break;
			}

		case '\n' : //retour a la ligne
			place_curseur(y_curs+1,0);
			break;

		case '\f' : //efface ecran
			efface_ecran();
			place_curseur(0,0);
			break;

		case '\r' : //retour debut de ligne
				place_curseur(y_curs, 0);
				break;

		default :
				ecrit_car(y_curs, x_curs, c,FONT_COLOR, BACK_COLOR);
				place_curseur(y_curs, x_curs+1);
	}
}


/* prend en parametres une chaine de characteres et la taille de cette chaine
et l'affiche sur l'ecran en faisant appel a traite_car  */
void console_putbytes(char *chaine, uint32_t taille) {

	for(int i=0; i < taille; i++) {
		traite_car(chaine[i]);
	}
}

/* remonte toute les lignes d'un cran, efface la première et ecrit une ligne "vide" en bas */
void defilement() {

	memmove(ptr_mem(0,0), ptr_mem(1,0),2*NB_COL*(NB_LINE-1));
	for(int i=0; i < NB_COL; i++) {
		ecrit_car(y_curs, i, ' ',FONT_COLOR, BACK_COLOR);
	}
}
