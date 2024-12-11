#ifndef proto
#define proto

//Structure pour permettant de bien gerer le temps creation d'une variable personalisee
struct dateTime_t {

  byte sec;
  byte mins;
  byte hours;
  byte dow;   //dayOfWeek(1-7)
  byte dom;  //dayOfMonth(1-30/31)
  byte month;
  byte year;
  byte incremente_hours; //deadline hour

} dateTime;

//QUELQUES VARIABLES GLOBALES DU PROGRAMME

//variable pour la gestion d'eau
float Water_01 = 0.0;
float Water_02 = 0.0;
bool state_Appart_01 = false;
bool state_Appart_02 = false;

// datas filtered
String states;
String ValuesCounter;

void control_leds();
void control_buzzer();
void control_ElectroVannes();
void readSerialsDatas();
void CachedDatas(String datas);

//pour l'affichage
void affichage_01();
void affichage_02();
void appel_fonction();

//Fonctions pour le module RTC
bool Clock(int);//controle de l'horloge du module

//fonction de mise ajour du temp
void update_time(byte, byte, byte, byte, byte, byte, byte);
void update_time_reglage(byte, byte);
void download_time(dateTime_t *);
void update_deadline_Hours(int);

//convertisseur des donnees
byte decimal_hexa(byte);
byte hexa_decimal(byte);

// fonction pour le decodage du jour de la semaine et celui du moi
String decode_dow(byte);
String decode_month(byte);

// fonction d'initialisation
void initialisation();
#endif //prototype
