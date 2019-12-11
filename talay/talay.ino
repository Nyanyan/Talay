#include <SoftwareSerial.h>
SoftwareSerial serial0(3, 2); // RX, TX
SoftwareSerial serial1(4, 2); // RX, TX
/*
SoftwareSerial serial2(5, 2); // RX, TX
SoftwareSerial serial3(6, 2); // RX, TX
SoftwareSerial serial4(7, 2); // RX, TX
SoftwareSerial serial5(8, 2); // RX, TX
SoftwareSerial serial6(9, 2); // RX, TX
SoftwareSerial serial7(10, 2); // RX, TX
SoftwareSerial serial8(11, 2); // RX, TX
SoftwareSerial serial9(12, 2); // RX, TX
*/
const int numoftimer = 2;
bool flag[numoftimer];

void setup() {
  Serial.begin(9600);
  serial0.begin(1200);
  serial1.begin(1200);
  /*
  serial2.begin(1200);
  serial3.begin(1200);
  serial4.begin(1200);
  serial5.begin(1200);
  serial6.begin(1200);
  serial7.begin(1200);
  serial8.begin(1200);
  serial9.begin(1200);
  */
  for (int i = 0; i < numoftimer; i++)
    flag[i] = true;
}

void loop() {
  serial0.listen();
  mainprocessing(0, serial0.readStringUntil(char(10)));
  serial1.listen();
  mainprocessing(1, serial1.readStringUntil(char(10)));
  /*
  serial2.listen();
  mainprocessing(2, serial2.readStringUntil(char(10)));
  serial3.listen();
  mainprocessing(3, serial3.readStringUntil(char(10)));
  serial4.listen();
  mainprocessing(4, serial4.readStringUntil(char(10)));
  serial5.listen();
  mainprocessing(5, serial5.readStringUntil(char(10)));
  serial6.listen();
  mainprocessing(6, serial6.readStringUntil(char(10)));
  serial7.listen();
  mainprocessing(7, serial7.readStringUntil(char(10)));
  serial8.listen();
  mainprocessing(8, serial8.readStringUntil(char(10)));
  serial9.listen();
  mainprocessing(9, serial9.readStringUntil(char(10)));
  */
}

void mainprocessing(int num, String input) {
  bool f = true;
  if (input[0] == 'S' and flag[num]) {
    int checksum = 64;
    for (int i = 0; i < 6; i++)
      checksum += int(input[i + 1]) - 48;
    if (char(checksum) == input[7]) {
      f = false;
      flag[num] = false;
      for (int i = 0; i < 10; i++) {
        Serial.print(char(48 + num));
        Serial.print(char(48 + i));
        Serial.println(input);
        delay(10);
        if (Serial.available() > 0) {
          if (char(Serial.read()) == 'y')
            break;
        }
      }
    }
  } else if (input[0] == ' ' || input[0] == 'I' || input[0] == 'R' || input[0] == 'L' || input[0] == 'A')
    flag[num] = true;

  if (f)
    Serial.println(num);
}
