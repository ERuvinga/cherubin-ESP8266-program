
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <avr/wdt.h> //include a watchdog Librairie
#include <Wire.h>
#include "lcd.h"
#include "rtc.h"

// Element connectee
//1. APPART 01
#define ELECTROVANNE_01 10
#define GREEN_LED_01 13
#define RED_LED_01 8

//1. APPART 02
#define ELECTROVANNE_02 11
#define GREEN_LED_02 5
#define RED_LED_02 9

//AUTRES
#define BUZZER 3
SoftwareSerial espSerial(2, 4); // Rx and Tx NodeMcu

unsigned long temp_lcd, temp_ledRed_01, temp_ledRed_02, temp_buzzer;
bool state_Buzzer = false, state_ledRed_01 = false, state_ledRed_02 = false; //states to control buzzer and leds

void beginer() {

  // initialisation des afficheurs
  lcd_water_01.init();
  lcd_water_02.init();
  Wire.begin(); //initialisation de la voie i2c

  //Appart 1
  pinMode(ELECTROVANNE_01 , OUTPUT);
  pinMode(GREEN_LED_01, OUTPUT);
  pinMode(RED_LED_01 , OUTPUT);

  //Appart 2
  pinMode(ELECTROVANNE_02 , OUTPUT);
  pinMode(GREEN_LED_02, OUTPUT);
  pinMode(RED_LED_02 , OUTPUT);

  //Autres
  pinMode(BUZZER, OUTPUT);
}

void setup() {
  Serial.begin(57600);
  espSerial.begin(57600);

  wdt_enable(WDTO_8S); //config a WTD
  beginer();

  lcd_water_01.backlight();
  lcd_water_02.backlight();

  //(sec, mins, heur, dow, dom, moi, an) mise a jours de l'heure et de la date
  //update_time(0, 30 ,14, 2, 3, 12, 24);

  download_time( &dateTime ); // telecharge l'heure et la date
  // setup Programme

  initialisation();
  temp_lcd = millis();
  temp_buzzer = millis();
  temp_ledRed_01 = millis();
  temp_ledRed_02 = millis();
  wdt_reset();
}

void loop() {
  //
  appel_fonction();  //and that call a functions (download a times and read searial monitor)
  if (( millis() - temp_lcd) >= 1000) {
    temp_lcd = millis();

    affichage_01();                        // after one seconde , this function update a datas to screen
    affichage_02();                        // after one seconde , this function update a datas to screen
    download_time( &dateTime );

  }
  wdt_reset();
}

void appel_fonction() {
  readSerialsDatas();
  control_ElectroVannes();
  control_buzzer();
  control_leds();
}

String getValue(String value, char car, int TabCase) {
  int indexDatas = value.indexOf(car);
  if (indexDatas >= 0) {
    String leftDatas = value.substring(0, indexDatas);
    String rigthDatas = value.substring(indexDatas + 1);
    switch (TabCase) {
      case 0: {
          return leftDatas;
          break;
        };
      case 1: {
          return rigthDatas;
          break;
        }
    }

  }
  else {
    return "null";
  }

}

// Functions decode datas

const StringToBoolean(String valuedatas) {
  if (valuedatas == "t")
  {
    return true;

  }
  else {

    return false;
  };
}

// save datas Functions
void saveStatesDatas(String states) {
  // get datas states datas;
  Serial.println(states);

  if (states.length() > 1) {
    state_Appart_01 =  StringToBoolean(getValue(states, '~', 0));
    state_Appart_02 = StringToBoolean(getValue(states, '~', 1));
  }
  else if(states.length() == 1) {
    state_Appart_01 = StringToBoolean(states);
  }

}

void saveCounterValuesDatas(String CounterValue) {

  // get datas states datas;

  if (getValue(CounterValue, '~', 0) != "null") {
    Water_01 =  getValue(CounterValue, '~', 0).toFloat();
    Water_02 = getValue(CounterValue, '~', 1).toFloat();
  }
  else {
    Water_01 = CounterValue.toFloat();
  }

}

void CachedDatas(String datas) {

  // subdivise datas;
  states = getValue(datas, '#', 0) != "null" ? getValue(datas, '#', 0) : states;
  ValuesCounter = getValue(datas, '#', 1) != "null" ? getValue(datas, '#', 1) : ValuesCounter;

  // get datas states datas;
  saveStatesDatas(states);
  saveCounterValuesDatas(ValuesCounter);
}

bool validateDatas (char c) {
  switch (c) {
    case '0': {
        return true;
        break;
      };
    case '1': {
        return true;
        break;
      };
    case '2': {
        return true;
        break;
      };
    case '3': {
        return true;
        break;
      };
    case '4': {
        return true;
        break;
      };
    case '5': {
        return true;
        break;
      };

    case '6': {
        return true;
        break;
      };
    case '7': {
        return true;
        break;
      };
    case '8': {
        return true;
        break;
      };
    case '9': {
        return true;
        break;
      };
    case 't': {
        return true;
        break;
      }
    case 'f': {
        return true;
        break;
      };

    case '~': {
        return true;
        break;
      };
    case '#': {
        return true;
        break;
      };
    case '.': {
        return true;
        break;
      };
    case '-': {
        return true;
        break;
      };
    default: {
        return false;
      }
  }
}


void readSerialsDatas() {
  char car;
  String datas = "";
  boolean availableDatas = true;
  //
  if (espSerial.available() > 0) {
    // reading datas
    do {
      car = espSerial.read();
      Serial.print(car);
      if ( car != '\n') {
        datas += car;
      }
      else {
        availableDatas = false;
      }
    }
    while (availableDatas);

  }

  if (datas.length() > 0) {
    //Serial.print(datas);
    CachedDatas(datas);
  }
}

void control_ElectroVannes() {
  // Appart 1
  if (state_Appart_01) {
    digitalWrite(ELECTROVANNE_01, HIGH);
  }

  else {
    digitalWrite(ELECTROVANNE_01, LOW);
  }
  // Appart 2
  if (state_Appart_02) {
    digitalWrite(ELECTROVANNE_02, HIGH);
  }

  else {
    digitalWrite(ELECTROVANNE_02, LOW);
  }
};

void control_leds() {
  // Appart 1
  if (!state_Appart_01) {
    if ((millis() - temp_ledRed_01) >= 1000) {
      temp_ledRed_01 = millis();
      state_ledRed_01 = !state_ledRed_01;
      digitalWrite(RED_LED_01, state_ledRed_01);
      digitalWrite(GREEN_LED_01, LOW);
    }
  }

  else {
    digitalWrite(RED_LED_01, LOW);
    digitalWrite(GREEN_LED_01, HIGH);
  }
  // Appart 1
  if (!state_Appart_02) {
    if ((millis() - temp_ledRed_02) >= 1000) {
      temp_ledRed_02 = millis();
      state_ledRed_02 = !state_ledRed_02;
      digitalWrite(RED_LED_02, state_ledRed_02);
      digitalWrite(GREEN_LED_02, LOW);
    }
  }

  else {
    digitalWrite(RED_LED_02, LOW);
    digitalWrite(GREEN_LED_02, HIGH);
  }
}

void control_buzzer() {

  if (!state_Appart_01 || !state_Appart_02) {
    if ((millis() - temp_buzzer) >= 500) {
      temp_buzzer = millis();
      state_Buzzer = !state_Buzzer;
      digitalWrite(BUZZER, state_Buzzer);
    }
  }

  else {
    digitalWrite(BUZZER, LOW);
  }
}
