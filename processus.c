#include <processus.h>

Processus table_processus[TAILLE_TABLE_PROCESSUS];
Processus* proc_actif;

void init_table_processus() {

  //Initialisation du processus idle
  table_processus[IDLE].pid = 0;//Pas besoin d'initialiser la pile ou les registres
  strcpy(table_processus[IDLE].nom, "idle");
  //fait une vériatble copie au lieu de passer par un pointeur !
  table_processus[IDLE].etat = ELU;

  table_processus[PROC1].pid = 1;
  strcpy(table_processus[PROC1].nom, "proc1");
  table_processus[PROC1].etat = ACTIVABLE;
  table_processus[PROC1].pile_execution[TAILLE_PILE-1] = (int) proc1;
  table_processus[PROC1].regs[esp] = &(table_processus[PROC1].pile_execution[511]);

   table_processus[PROC2].pid = 2;
  strcpy(table_processus[PROC2].nom, "proc2");
  table_processus[PROC2].etat = ACTIVABLE;
  table_processus[PROC2].pile_execution[TAILLE_PILE-1] = (int) proc2;
  table_processus[PROC2].regs[esp] = &(table_processus[PROC2].pile_execution[511]);

  table_processus[PROC3].pid = 3;
  strcpy(table_processus[PROC3].nom, "proc3");
  table_processus[PROC3].etat = ACTIVABLE;
  table_processus[PROC3].pile_execution[TAILLE_PILE-1] = (int) proc3;
  table_processus[PROC3].regs[esp] = &(table_processus[PROC3].pile_execution[511]);

  proc_actif = &(table_processus[IDLE]);
}


void idle() {

  for(;;) {
    printf("[%s] pid = %i\n", mon_nom(), mon_pid());
    sti(); //démasque interruptions
    hlt(); //wait
    cli(); //masque
    ordonnance();
  }
}

void proc1() {

  for(;;){
    printf("[%s] pid = %i\n", mon_nom(), mon_pid() );
    sti();
    hlt();
    cli();
    ordonnance();
  }
}

void proc2() {

  for(;;){
    printf("[%s] pid = %i\n", mon_nom(), mon_pid());
    sti();
    hlt();
    cli();
    ordonnance();
  }
}
void proc3() {

  for(;;){
    printf("[%s] pid = %i\n", mon_nom(), mon_pid() );
    sti();
    hlt();
    cli();
    ordonnance();
  }
}




void ordonnance(void) {
  Processus* ancien_proc = proc_actif;
  Processus* futur_proc = &(table_processus[(proc_actif->pid+1)%TAILLE_TABLE_PROCESSUS]);
  proc_actif = futur_proc;
  ctx_sw(ancien_proc->regs, futur_proc->regs);
}

char * mon_nom(){
  return proc_actif->nom;
}
int16_t mon_pid(){
  return proc_actif->pid;
}
