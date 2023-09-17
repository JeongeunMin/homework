#include <stdio.h>
#include <stdlib.h>
#define CAD 1.35
#define LITER 3.785
#define GALLON 31.5

int main(void)
{
  // Declare
  int star_cur;
  int star_unit;
  double cur_price;
  double usd_to_Cad;
  double gal_to_Lit_usd;
  double gal_to_Lit_cad;
  double gal_to_Bar_usd;
  double gal_to_Bar_cad;
  
  char cur_price_unit;
  char star_cur1;
  char star_cur2;
  char star_cur3;

  // Statements
  printf("Enter starting currency (1-USD, 2-CAD) -> ");
  scanf("%d", &star_cur);
  printf("Enter starting unit (1-g, 2-l, 3-b) -> ");
  scanf("%d", &star_unit);
  //cur_price = 
  star_cur1 = 85 * (((3 - star_cur) %3)/2) + 67 * abs((star_cur %2)-1);
  star_cur2 = 83 * (((3 - star_cur) %3)/2) + 65 * abs((star_cur %2)-1);
  star_cur3 = 68 * (((3 - star_cur) %3)/2) + 68 * abs((star_cur %2)-1);

  cur_price_unit = 'g' * ((3  - star_unit)/2) + 'l' * (1 - (star_unit%2)) + 'b' * (star_unit/3);

  printf("Enter current price per %c (%c%c%c) -> ",cur_price_unit , star_cur1, star_cur2, star_cur3);
  scanf("%lf", &cur_price);

  double cur_dol = cur_price*(1-(1-star_cur%2)) + (cur_price*(1-star_cur%2))/CAD;
  double cur_cad = CAD*cur_price*(1-(1-star_cur%2)) + cur_price*(1-star_cur%2);

  printf("cur_dol : %5.2f , cur_cad: %5.2f \n", cur_dol, cur_cad);

//  double cur_price_g = cur_price * ((3  - star_unit)/2) + cur_price * (1 - (star_unit%2))*LITER + (cur_price * (star_unit/3))/GALLON;
//  double cur_price_l = (cur_price * ((3  - star_unit)/2))/LITER + cur_price * (1 - (star_unit%2)) + ((cur_price * (star_unit/3))/GALLON)/LITER;
//  double cur_price_b = cur_price * ((3  - star_unit)/2)*GALLON + ((cur_price * (1 - (star_unit%2)))*GALLON)*LITER + cur_price * (star_unit/3);
  
  double cur_price_g = (3  - star_unit)/2 + (1 - (star_unit%2))*LITER + (star_unit/3)/GALLON;
  double cur_price_l = ((3  - star_unit)/2)/LITER + (1 - (star_unit%2)) + ((star_unit/3)/GALLON)/LITER;
  double cur_price_b = ((3  - star_unit)/2)*GALLON + ((1 - (star_unit%2))*GALLON)*LITER + star_unit/3;

  printf("cur_price_g : %5.2f , cur_price_l: %5.2f, cur_price_b: %5.2f \n", cur_price_g, cur_price_l, cur_price_b);

//  usd_to_Cad = cur_price * CAD;
//  gal_to_Lit_usd = cur_price / LITER;
//  gal_to_Lit_cad = gal_to_Lit_usd * CAD;
//  gal_to_Bar_usd = cur_price * GALLON;
//  gal_to_Bar_cad = gal_to_Bar_usd * CAD;
  
  // print the result
  printf("\n --- Unit --- USD --- CAD --\n");
  printf("Gallon:  $ %5.2f   $ %5.2f\n", cur_dol*cur_price_g, cur_cad * cur_price_g);
  printf("Liter:   $ %5.2f   $ %5.2f\n", cur_dol*cur_price_l, cur_cad * cur_price_l);
  printf("Barrel:  $ %5.2f   $ %5.2f\n", cur_dol*cur_price_b, cur_cad * cur_price_b);
  //printf("Liter:   $ %5.2f   $ %5.2f\n", cur_price * gal_to_Lit_usd, cur_price *  gal_to_Lit_cad);
  //printf("Barrel:  $ %5.2f   $ %5.2f\n", cur_price *  gal_to_Bar_usd, cur_price *  gal_to_Bar_cad);
  printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

  return(0);
}