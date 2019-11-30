#include <SoftwareSerial.h>
SoftwareSerial mySerial(A0, A1); // RX, TX

void setup() {
  Serial.begin(115200);
  mySerial.begin(1200);

}

void loop() {
  mySerial.listen();
  String input = mySerial.readStringUntil(char(10));
  bool flag = false;
  if (input[0] == 'S') {
    flag = true;
    Serial.println(input);
  }
}
