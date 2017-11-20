#include <horloge.h>

static int secondes = 0;
static int minutes = 0;
static int heures = 0;

void affiche_coin_droite(char *str, uint32_t taille) {
  for (size_t i = 0; i < taille; i++) {
    ecrit_car(0,NB_COL-taille+i,str[i],CLOCKCOLOR,BACK_COLOR);
  }
}

void init_horloge() {
  outb(0x34,0x43);
  outb((QUARTZ / CLOCKFREQ) % 256, 0x40);
  outb((QUARTZ / CLOCKFREQ) >> 8, 0x40);
}

void masque_IRQ(uint32_t num_IT, bool val) {
  uint8_t masque = (uint8_t) inb(0x21);
  if(val){
    outb(masque | (0x01<<num_IT),0x21);
  } else {
    outb(masque & !(0x01<<num_IT),0x21);
  }
}

void tic_PIT() {
  outb(0x20,0x20);
  static int compteur = 0;
  char time_str[TAILLE_HORLOGE];

  if (compteur == 50) {
    compteur = 0;

    if (secondes < 59) {
      secondes += 1;
    } else if (minutes < 59) {
      secondes = 0;
      minutes += 1;
    } else {
      secondes = 0;
      minutes = 0;
      heures += 1;
    }


  } else {
    compteur += 1;
  }
  sprintf(time_str,"%02d:%02d:%02d",heures, minutes, secondes);
  affiche_coin_droite(time_str,TAILLE_HORLOGE);

  //ordonnance();
}

int nbr_sec() {
  return secondes+60*(minutes+60*heures);
}
