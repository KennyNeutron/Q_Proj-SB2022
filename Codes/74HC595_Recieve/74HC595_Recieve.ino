//74HC595 Rcv
//by: KennyNeutron
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

#define ser   5   //d_in
#define rclk  7   //lat
#define srclk 6   //clk


void setup() {
  pinMode(ser, OUTPUT);
  pinMode(rclk, OUTPUT);
  pinMode(srclk, OUTPUT);


  digitalWrite(ser, 0);
  digitalWrite(rclk, 0);
  digitalWrite(srclk, 0);

  printSEG(8);

  Serial.begin(115200);
  Serial.println("START");
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  delay(1000);
}

void loop() {
  if (radio.available()) {
    char text[7] = "";
    radio.read(&text, sizeof(text));
    //Serial.print(String(text));

    //    byte data;
    //    for (byte a = 0; a <= 14; a++) {
    //      data = text[a];
    //      Serial.println(a + ":" + String(data));
    //    }
    //    delay(50);
    if(text[0]=='A' && text[6]=='B'){
      int val_sc=int(text[4]);
      int sc_ones=val_sc%10;
      
      int sc_millis=int(text[5]);

      Serial.println("MS:"+String(sc_millis));
      printSEG(sc_millis);

    }


  }
}

void printSEG(int segNum) {
  switch (segNum) {
    case 0:
      shiftOut(ser, srclk, LSBFIRST, 0b00000011);
      break;
    case 1:
      shiftOut(ser, srclk, LSBFIRST, 0b10011111);
      break;
    case 2:
      shiftOut(ser, srclk, LSBFIRST, 0b00100101);
      break;
    case 3:
      shiftOut(ser, srclk, LSBFIRST, 0b00001101);
      break;
    case 4:
      shiftOut(ser, srclk, LSBFIRST, 0b10011001);
      break;
    case 5:
      shiftOut(ser, srclk, LSBFIRST, 0b01001001);
      break;
    case 6:
      shiftOut(ser, srclk, LSBFIRST, 0b01000001);
      break;
    case 7:
      shiftOut(ser, srclk, LSBFIRST, 0b00011111);
      break;
    case 8:
      shiftOut(ser, srclk, LSBFIRST, 0b00000001);
      break;
    case 9:
      shiftOut(ser, srclk, LSBFIRST, 0b00001001);
      break;

  }
  rclk_pulse();
}

void srclk_pulse() {
  digitalWrite(srclk, 1);
  digitalWrite(srclk, 0);
}

void rclk_pulse() {
  digitalWrite(rclk, 1);
  digitalWrite(rclk, 0);
}
