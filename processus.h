#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <cpu.h>


#define TAILLE_TABLE_PROCESSUS 2
#define TAILLE_NOM 20
#define TAILLE_PILE 512

enum Reg_type {
    ebx,
    esp,
    ebp,
    esi,
    edi
};

typedef enum State State;
enum State {ELU,ACTIVABLE};

typedef enum Proc Proc;
enum Proc{IDLE, PROC1};

typedef struct Processus {
  int16_t pid;
  char nom[TAILLE_NOM];
  State etat;
  int* regs[5]; // zone de sauvegarde des registres,
  // dans l'ordre : [ebx, esp, edp, esi, edi
  int pile_execution[TAILLE_PILE];
} Processus;

void idle();
void proc1();
void proc2();
void ctx_sw(int**, int**);
void init_table_processus();
void ordonnance(void);
