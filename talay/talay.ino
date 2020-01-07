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
  serial0.setTimeout(200);
  serial1.setTimeout(200);
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
  //Serial.println(digitalRead(3));
  String serialinput[2] = {"", ""};
  serial0.listen();
  delay(100);
  serialinput[0] = serial0.readStringUntil('\n');
  serial1.listen();
  delay(100);
  serialinput[1] = serial1.readStringUntil('\n');
  for (int i = 0; i < 2; i++)
    mainprocessing(i, serialinput[i]);
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
  String inputproc = "";
  int tmp = input.length();
  for (int i = max(0, tmp - 8); i < tmp; i++)
    inputproc += input[i];
  //Serial.println(String(inputproc.length())+"\t" + tmp + "\t" + inputproc);
  if (inputproc.length() == 8) {
    if (inputproc[0] == 'S' and flag[num]) {
      int checksum = 64;
      for (int i = 0; i < 6; i++)
        checksum += int(inputproc[i + 1]) - 48;
      if (char(checksum) == inputproc[7]) {
        bool tmp2 = false;
        for (int i = 0; i < 20; i++) {
          Serial.print(char(48 + num));
          Serial.print(char(48 + i));
          Serial.println(inputproc);
          delay(10);
          if (Serial.available() > 0 && Serial.read() == 'y') {
            tmp2 = true;
            break;
          }
        }
        if (tmp2)
          flag[num] = false;
      }
    } else if (input[0] == ' ' || input[0] == 'I' || input[0] == 'R' || input[0] == 'L' || input[0] == 'A')
      flag[num] = true;
  }
}
