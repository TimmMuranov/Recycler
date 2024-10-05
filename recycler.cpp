/*
https://github.com/GyverLibs/GyverButton 
 Описание кнопочной библиотеки 
*/
#include “GyverButton.h”

#define reductor 1 // редуктор
#define heater 2 // нагреватель
#define termometre 3 // термометр
#define led 4 // светодиод служит для обратной связи
#define button 5 // кнопка для управления

GButton butt1 (button);

int motor_speed = 0;
int temp = 0;

//____функция мигания светодиодом___
void led_on_off (int pin, int repeat, int time_on, int time_off) {
  for (int x = 0; x < repeat; x++) {
	digitalWrite(pin, HIGH);
	delay (time_on);
	digitalWrite(pin, LOW);
	delay(time_off);
  }
}
//_________________________________

void setup(){
pinMode (reductor, OUTPUT);
pinMode (heater, OUTPUT);
pinMode (termometre, INPUT);
pinMode (led, OUTPUT);
pinMode (button, INPUT);
}

void loop(){
butt1.tick(); //опрос кнопки
 
if (butt1.isSingle()==true){
//Действие при одиночном нажатии
//Переход в состояние “работа”
   while (butt1.isSingle() != true){
   digitalWrite (led, HIGH);
   //Цикл будет продолжаться пока не   
   //произойдет одиночное нажатие

   //Включение мотора
   analogWrite (reductor, motor_speed);

   //нагрев до “temp”
   if(analogRead (termometre) > temp){
      digitalWrite (heater, LOW)
   }
   else {digitalWrite (heater, HIGH);}
}
//Завершение произойдет при нажатии
analogWrite (reductor, 0);
digitalWrite (led, LOW);
digitalWrite (heater, LOW);
//Выключение всей периферии
}
  if (butt1.isDouble()==true){
//Действие при двойном клике

//цикл настройки температуры
while (butt1.isDouble() != true){
   led_on_off ( 3, 500, 500);
   if (butt1.isClick() == true){
      temp += 20;
      led_on_off (4, 100, 100);
      delay(500);
      }
   if (butt1.isHolded() == true){
     temp -=20;
     led_on_off (2, 100, 100);
     delay(500);
      }
   if (temp < 0 || temp > 255) {
      temp = 0;
      led_on_off ( 3, 250, 250);
      }
   }
}

  if (butt1.isTriple()){
// Действие при тройном клике

while (butt1.isTriple() != true){
      if (butt1.isClick() == true){
         motor_speed += 20;
         }
   if (butt1.isHolded() == true){
     motor_speed -=20;
         }
   if (motor_speed < 0 || 
       motor_speed > 255){
         motor_speed = 0;
         led_on_off ( 3, 250, 250);
         }
      }
   }
}
