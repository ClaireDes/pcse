#include <inttypes.h>
#include <cpu.h>
#include <string.h>

//definition des constantes
#define BACK_COLOR 0
#define FONT_COLOR 15
#define CLOCKCOLOR 5
#define RACLETTECOLOR 8
#define ESPACE 32
#define NB_LINE 25
#define NB_COL 80
#define MEM_VIDEO 0xB8000
#define P_COM 0x3d4
#define P_DATA 0x3d5
#define PARTIE_H 0x0e
#define PARTIE_B 0x0f
#define TAILLE_TAB 8

//definition des variables globales
uint32_t x_curs;
uint32_t y_curs;

//prototypes des fonctions de screen.c
uint16_t* ptr_mem (uint32_t lig, uint32_t col);
void ecrit_car(uint32_t lig, uint32_t col, char c, uint8_t color_font, uint8_t color_back );
void efface_ecran(void);
void place_curseur(uint32_t lig, uint32_t col);
void traite_car(char c);
void console_putbytes(char *chaine, uint32_t taille);
void defilement();
