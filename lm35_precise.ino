/*
  Термометър

  Прочита повторително входните данни от LM35, след което се изчислява
  средната стойност и се отпечатва на комютъра.

  Схема:
      LM35 закачен на аналогов вход

  Създаден на 05 Януари 2016
  От Христо Стоянов <icaknewton@gmail.com>


*/
// Начална конфигурация

const int inputPin = A0;          // Входящия пин на Ардуино
const int numReadings = 100;       // Броя на прочитанията на входящия пин
const int delayMs = 10;          // Време за изчакване

float readings[numReadings];      // Масив съдържащ данните
float total = 0;                  // Сумата на прочитанията
float average = 0;                // Средната стойност
float tempC = 0;                  // Температарура в градуси по С

int readIndex = 0;                // Текущият индекст на масива
int readInput = 0;                // Прочитане на стойността на входящия пин


void setup() {
  analogReference(INTERNAL);

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  Serial.begin(9600);
}

void loop() {
  // Цикъл за превъртане на масива
  for (readIndex; readIndex < numReadings; readIndex++) {
    // Изваждане на предходното прочитане
    total = total - readings[readIndex];

    // Прочитане стойността от сензора, превръщане в градуси и запазване в масива
    readInput = analogRead(inputPin);
    tempC = readInput / 9.30925;
    readings[readIndex] = tempC;

    // Добавяне на стойността към сумата
    total = total + readings[readIndex];

    // Закъснение преди следващото прочитане
    delay(delayMs);
  }

  // Връщане на масива от начало
  readIndex = 0;

  // Изчисляване на средната стойност
  average = total / numReadings;

  // Отпечатване на стойността на компютъра
  Serial.println(average);
}
