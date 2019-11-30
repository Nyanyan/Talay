#include <SoftwareSerial.h>
SoftwareSerial serial0(A0, A1); // RX, TX
//SoftwareSerial serial1(A2, A3); // RX, TX
//SoftwareSerial serial2(A4, A5); // RX, TX

bool flag = true;
int num = 0;

void setup() {
  Serial.begin(115200);
  serial0.begin(1200);

}

void loop() {
  serial0.listen();
  String input = serial0.readStringUntil(char(10));
  if (input[0] == 'S' and flag) {
    int checksum = 64;
    for (int i = 0; i < 6; i++)
      checksum += int(input[i + 1]) - 48;
    if (char(checksum) == input[7]) {
      flag = false;
      Serial.print(char(48));
      Serial.print(',');
      Serial.println(input);
    }
  } else if (input[0] == 'I')
    flag = true;
}
