#include <cpu.h>
#include <inttypes.h>
#include <screen.h>
#include <traitant.h>
#include <horloge.h>
#include <check.h>
#include <processus.h>

void traitant_IT_32();

void kernel_start(void)
{
  //initialisations
  efface_ecran();
  init_traitant_IT(32, traitant_IT_32);
  masque_IRQ(0,0);
  init_horloge();
  init_table_processus();

  //demarrage du processus pa defaut
  idle();
  

    // on ne doit jamais sortir de kernel_start
    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}
