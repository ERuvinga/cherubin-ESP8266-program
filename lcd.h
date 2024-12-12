
// FICHIER POUR AFFICHAGE DES DONNEES.
#ifndef lcd
#define lcd
#include "prototypes.h"

//LCD Adresses
#define LCD_ADDR_01 0x27
#define LCD_ADDR_02 0x26

LiquidCrystal_I2C lcd_water_01(LCD_ADDR_01, 16, 2);
LiquidCrystal_I2C lcd_water_02(LCD_ADDR_02, 16, 2);

void affichage_01() {
  lcd_water_01.clear();
  lcd_water_01.setCursor(1, 0);
  lcd_water_01.print("Qnt: ");
  lcd_water_01.setCursor(7, 0);
  lcd_water_01.print(Water_01, 1);
  lcd_water_01.print(" L");


  //affichage du temps et de la date
  lcd_water_01.setCursor(0, 1);
  lcd_water_01.print(decode_dow(dateTime.dow));
  lcd_water_01.print(" ");
  if (dateTime.dom < 10)
    lcd_water_01.print("0");

  lcd_water_01.print(dateTime.dom);
  lcd_water_01.print(" ");
  lcd_water_01.print(decode_month(dateTime.month));
  
  lcd_water_01.setCursor(11, 1);

  if (dateTime.hours < 10)
    lcd_water_01.print("0");

  lcd_water_01.print(dateTime.hours);
  lcd_water_01.print(":");

  if (dateTime.mins < 10) {
    lcd_water_01.print("0");
  }
  lcd_water_01.print(dateTime.mins);

}

void affichage_02() {

  lcd_water_02.clear();
  lcd_water_02.setCursor(1, 0);
  lcd_water_02.print("Qnt: ");
  lcd_water_02.setCursor(7, 0);
  lcd_water_02.print(Water_02, 1);
  lcd_water_02.print(" L");


  //affichage du temps et de la date
  lcd_water_02.setCursor(0, 1);
  lcd_water_02.print(decode_dow(dateTime.dow));
  lcd_water_02.print(" ");
  if (dateTime.dom < 10)
    lcd_water_02.print("0");

  lcd_water_02.print(dateTime.dom);
  lcd_water_02.print(" ");
  lcd_water_02.print(decode_month(dateTime.month));
  lcd_water_02.print(" ");

  lcd_water_02.setCursor(11, 1);

  if (dateTime.hours < 10)
    lcd_water_02.print("0");

  lcd_water_02.print(dateTime.hours);
  lcd_water_02.print(":");

  if (dateTime.mins < 10) {
    lcd_water_02.print("0");
  }
  lcd_water_02.print(dateTime.mins);

}


void initialisation()
{
  int j, i;

  for (i = 0; i < 2; i++) {
    lcd_water_01.clear();
    lcd_water_02.clear();

    lcd_water_01.setCursor(3, 0);
    lcd_water_02.setCursor(3, 0);
    lcd_water_01.print("Setup");
    lcd_water_02.print("Setup");

    delay(250);
    for (j = 0; j <= 3; j++) {
      lcd_water_01.print(".");
      lcd_water_02.print(".");
      delay(500);
    }
  }
  lcd_water_01.clear();
  lcd_water_02.clear();
}


#endif //lcd
