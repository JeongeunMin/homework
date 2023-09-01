#include <stdio.h>

typedef enum {
  gal = 0,
  lit,
  bar,
} VolType;

typedef struct {
  float dol_price;
  float cad_price;
}OilPrice;

OilPrice cal_price_of_oil(float dol_per_gal, VolType type) {
  OilPrice oil_price;
  
  const float cad = 1.35;
  const float liter = 3.785;
  const float barrel = 31.5;

  if (type > bar || type < gal) {
    printf("it's wrong type ~~");
  }

  switch (type) {
    case gal:
      oil_price.dol_price = dol_per_gal;
      oil_price.cad_price = dol_per_gal * cad;
    break;
    case lit:
       oil_price.dol_price = dol_per_gal / liter;
       oil_price.cad_price = oil_price.dol_price * cad ;
    break;
    case bar:
       oil_price.dol_price = dol_per_gal*barrel;
       oil_price.cad_price = oil_price.dol_price * cad;
    break;
    default:
      oil_price.dol_price = dol_per_gal;
      oil_price.cad_price = dol_per_gal * cad;
    break;
  }
  
  return oil_price;
}

int main(void) {
  float dollar_per_gallon;
  OilPrice oil_price;
  char* vol_type[3] = {"Gallon", "Liter", "Barrel"};
  printf("Enter current price per gallon (USD) -> ");
  scanf("%f", &dollar_per_gallon);

  printf("--- Unit --- USD ----- CAD ---\n");
  for(int i = 0 ; i < 3 ; i++) {
    oil_price = cal_price_of_oil(dollar_per_gallon, i);
    printf("%s:  $   %7.2f  $  %7.2f \n",vol_type[i], oil_price.dol_price, oil_price.cad_price);
  }
  printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
  return 0;
}
