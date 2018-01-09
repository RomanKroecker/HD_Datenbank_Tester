/*
 * 
 * Autor: Roman Kröcker
 * Datum: 18.12.2017
 * 
 * Programm zum automatisieren der Anmeldung und Freischaltung bei HD-Geräten (M-Box)
 * 
 * Microcontroller:
 * Digispark Attiny85
 * 
 * Der µC wird als HID erkannt
 * 
 */


#include <DigiMouse.h>

#define wait_ms 50 //50
#define max_right 127
#define max_left -127
#define max_down 127
#define max_up -127



void setup() //Einmalig, beim Start
{
  //Output und Input Pins setzen
  pinMode(0, OUTPUT); //LED on Model B    
  pinMode(1, INPUT); //LED on Model A //Spannung die der Taster durchschaltet  
  pinMode(2, OUTPUT);  //Für den Taster 
  //Pin 3 & 4 werden für die USB-Kommunikation verwendet


  //Mouse Initialisieren
  DigiMouse.begin();


  //digitalWrite(1,HIGH); //LED on Model A //Hier für den Taster
  //digitalWrite(0,HIGH); //LED on Model B
  digitalWrite(2,HIGH);
  
  //analogRead(2,255); //Pin 2 ist ein Analog Input. Min.: 0 bis Max.: 255
  //DigiMouse.delay(wait);  //Nach jedem Mouse Event ein Delay einfügen, bzw. update() alle 50 ms
}


void loop() //Dauerhaft, nach dem Start. Quasi die "Main" Funktion
{
  DigiMouse.update();  

  digitalWrite(0,LOW); //LED on Model B

  //Beim Tasterdruck 
  if(digitalRead(1)==HIGH)
  {
    digitalWrite(0,HIGH); //LED on Model B
    changed_settings();
    init_navigationbar();  
    registration();
    unlock_coinhandler();
    info();
  }
  
  
}

//Funktionen


//startposition: 
//Mauszeiger wird an den äusseren Rand gebracht
void startposition(int x, int y)
{
    for(int i = 0; i<7; i++)
    {
      DigiMouse.move(x, y, 0); //x, y, scroll
      DigiMouse.delay(wait_ms);
    }
}
//-startposition-


//changed_settings: 
//Beim wechseln der Datenbanken (z.B. von Magie 117 zu Magie 138) kommt ein Fenster mit Hinweisen zu veränderten Einstellungen

void changed_settings()
{
  
  startposition(max_left, max_up);
  
  moveXY(127, 127);
  moveXY(127, 60);
  leftclick();
  moveXY(0, -24); //Von -10 auf -30
  leftclick();
  
}
//-changed_settings-


//init_navigationbar: 
//Die Navigationsleiste wird auf einen Anfangswert gesetzt (z.B. falls jemand vorher rumgedrückt hat)

void init_navigationbar()
{
  startposition(max_left, max_up);

  moveXY(95, 15);
  leftclick();

  moveXY(-70, 0);
  leftclick();

  moveXY(0, 127);
  moveXY(0, 93); 
  leftclick();
  
  moveXY(0, 25);
  leftclick();

  moveXY(0, 25);
  leftclick();

}
//-navigationbar-


//registration: 
//Anmeldung als Administrator

void registration()
{
  startposition(max_right, max_up);
  
  access();
  select_user();
  
  
  
  password();
}

void access()
{
  
  moveXY(-105, 15);
  leftclick();
  
}

void select_user()
{
  
  moveXY(max_left, max_down);
  moveXY(max_left, 0);
  moveXY(-100, 30); //Um +5 geändert
  leftclick();
  
  moveXY(0, 20); 
  leftclick();
  
  moveXY(0, 15);
  leftclick();
  
}

void password()
{
  //Passwort Eingabe für M138
  startposition(max_right, max_down);

  moveXY(-45, -75);
  leftclick();
    
  moveXY(0, 6);
  leftclick();
  
  //Passwort Eingabe für alle anderen
  startposition(max_right, max_down);
  
  moveXY(-95, -120);
  leftclick();
  
  moveXY(0, 65);
  leftclick();
 
}
//-registration-

//unlock_coinhandler:
//Freischaltung des Münzprüfers

void unlock_coinhandler()
 {
  
  startposition(max_left, max_up);

  moveXY(25, 50);
  leftclick();

  moveXY(0, 20);
  leftclick();
  
  moveXY(127, 15); 
  moveXY(127, 0);
  leftclick();
  
  moveXY(0, 20);
  leftclick();

  startposition(max_right, max_up);

  moveXY(-105, 15);
  leftclick();
  moveXY(-60, 0);
  leftclick();
  DigiMouse.delay(2500);
  
  
 }
//-unlock_coinhandler-

//info:
//Geht zum Informationsbereich

void info()
{
  startposition(max_left, max_up);

  moveXY(25, 127);
  moveXY(0,127);
  moveXY(0,33); 
  leftclick();

}
//-info-

//Mausklicks
void leftclick()
{
  DigiMouse.setButtons(1<<0); //linke Maustaste auf 1 setzen
  DigiMouse.delay(wait_ms);
  DigiMouse.setButtons(0); //unclick all
  DigiMouse.delay(wait_ms);
}

void rightclick()
{
  DigiMouse.setButtons(1<<1); //rechte Maustaste auf 1 setzen
  DigiMouse.delay(wait_ms);
  DigiMouse.setButtons(0); //unclick all
  DigiMouse.delay(wait_ms);
}
//-Mausklicks-

//moveXY

void moveXY(int x, int y)
{
  DigiMouse.move(x, y, 0);
  DigiMouse.delay(wait_ms);
}

//-moveXY-


//test
void test()
{
  rightclick();
  DigiMouse.delay(10000);
}
//-test-
