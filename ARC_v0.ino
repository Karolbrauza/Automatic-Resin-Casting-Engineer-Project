#include <Stepper.h> //Biblioteka odpowiedzialna za silniki krokowe
#include <Servo.h> //Biblioteka odpowiedzialna za serwa
 
Servo serwomechanizm;  //Tworzymy obiekt, dzięki któremu możemy odwołać się do serwa 
int pozycja = 10; //Pozycja serwa przy otwartym zaworze
int zmiana = 6; //Co ile ma się zmieniać pozycja serwa?

int Index;//Pomocnicza zmienna

int step_x = 2; //Deklaracja pinu dla sygnału kroku dla pierwszego silnika
int dir_x = 5; //Deklaracja pinu dla sygnału kierunku kroku dla pierwszego silnika

int step_y = 3; //Deklaracja pinu dla sygnału kroku dla drugiego silnika
int dir_y = 6; //Deklaracja pinu dla sygnału kierunku kroku dla drugiego silnika

int step_z = 4; //Deklaracja pinu dla sygnału kroku dla trzeciego silnika
int dir_z = 7; //Deklaracja pinu dla sygnału kierunku kroku dla trzeciego silnika

int przekaznik_pompa = 10;               //przekaznik1 podłączamy do pinu 10
int przekaznik_nawiew = 11;               //przekaznik2 podłączamy do pinu 11

bool sp1 = true;                    //zmienna boolowska sp1 do steowania stanem przekaznika pompy
bool sp2 = true;                    //zmienna boolowska sp2 do steowania stanem przekaznika nawiewu

void setup() 
{
  serwomechanizm.attach(9);  //Serwomechanizm podłączony do pinu 9
  
  /* Ustawienia pinów sygnału kroku i kierunku kroku */
  pinMode(8, OUTPUT); 
  pinMode(step_x, OUTPUT); 
  pinMode(dir_x, OUTPUT); 
  pinMode(step_y, OUTPUT); 
  pinMode(dir_y, OUTPUT); 
  pinMode(step_z, OUTPUT); 
  pinMode(dir_z, OUTPUT);
  digitalWrite(8,LOW);

  pinMode(przekaznik_pompa, OUTPUT);       //przekaznik od pompy jako wyjście
  pinMode(przekaznik_nawiew, OUTPUT);       //przekaznik od nawiewu jako wyjście
  digitalWrite(przekaznik_pompa, HIGH);    //stan początkowy przekaznika pompy wysoki
  digitalWrite(przekaznik_nawiew, HIGH);    //stan początkowy przekaznika nawiewu wysoki
}

void loop() 
{
  delay(30000); //Po uruchomieniu cyklu poczekaj 30 sec przed zwolnieniem zaworu
   if (pozycja = 0) { //Jeśli zawór zamknięty otwórz
    serwomechanizm.write(pozycja); 
  } else { //Jeśli nie, to powrót na początek
    pozycja = 0;
  }
  delay(120000); //Odczekaj 2 min na rozlanie żywicy do form
      
  digitalWrite(dir_x,HIGH);
  digitalWrite(dir_y,HIGH);

  for(Index = 0; Index < 800; Index++) //Przesunięcie na pozycje drugiego etapu
  {
    digitalWrite(step_x,HIGH);
    digitalWrite(step_y,HIGH);
    delayMicroseconds(1000);
    digitalWrite(step_x,LOW);
    digitalWrite(step_y,LOW);
    delayMicroseconds(1000);
  }
  delay(60000);

  digitalWrite(dir_z,HIGH);

  for(Index = 0; Index < 800; Index++) //Opuszczenie komory
  {
    digitalWrite(step_z,HIGH);
    delayMicroseconds(1000);
    digitalWrite(step_z,LOW);
    delayMicroseconds(1000);
  }
  
  delay(10000); //Odczekaj 10 sec na poprawne ułożenie komory
  
  digitalWrite(przekaznik_pompa, sp1); //Właczenie pompy próżniowej
  delay(120000); //Pompa próżniowa działa 2 min
  sp1=!sp1; //zaneguj zmienna sterwania pompom
  digitalWrite(przekaznik_pompa, sp1);// Wyłączenie pompy
  delay(40000);// Przerwa 40 sec na to żeby operator wyrównał cisnienie w komorze
  
  digitalWrite(dir_z,LOW);

  for(Index = 0; Index < 800; Index++) //Podniesienie komory
  {
    digitalWrite(step_z,HIGH);
    delayMicroseconds(1000);
    digitalWrite(step_z,LOW);
    delayMicroseconds(1000);
  }

   digitalWrite(dir_x,HIGH);
  digitalWrite(dir_y,HIGH);

  for(Index = 0; Index < 800; Index++) //Przesunięcie na pozycje trzeciego etapu
  {
    digitalWrite(step_x,HIGH);
    digitalWrite(step_y,HIGH);
    delayMicroseconds(1000);
    digitalWrite(step_x,LOW);
    digitalWrite(step_y,LOW);
    delayMicroseconds(1000);
  }

    digitalWrite(przekaznik_nawiew, sp2);// Wyłączenie nawiewu
    delay(60000); // Czas działania nawiewu wynosi minute
    sp2=!sp2;   
    digitalWrite(przekaznik_nawiew, sp2);// Wyłączenie pompy
    delay(120000); //Przerwa na wyciagniecie formy i włożenie nowej platformy równa 2 min


}
