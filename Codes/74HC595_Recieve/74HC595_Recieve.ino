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


int GTime_Min_Tens = 0;
int GTime_Min_Ones = 0;
int GTime_Sec_Tens = 0;
int GTime_Sec_Ones = 0;
int GTime_Millis = 0;
int SC_Tens = 0;
int SC_Ones = 0;
int SC_millis;

int HScore_Hund = 0;
int HScore_Tens = 0;
int HScore_Ones = 6;
int GScore_Hund = 0;
int GScore_Tens = 0;
int GScore_Ones = 0;

int HFoul = 0;
int GFoul = 0;
int HTOut = 0;
int GTOut = 0;

int Period = 1;
int BallPos = 0;

void setup() {
  pinMode(ser, OUTPUT);
  pinMode(rclk, OUTPUT);
  pinMode(srclk, OUTPUT);


  digitalWrite(ser, 0);
  digitalWrite(rclk, 0);
  digitalWrite(srclk, 0);

  //printSEG(8);

  //Serial.begin(115200);
  //Serial.println("START");
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  delay(1000);

  printSEG(SC_Tens);
  printSEG(SC_Ones);

  printSEG(GTime_Min_Tens);
  printSEG(GTime_Min_Ones);
  printSEG(GTime_Sec_Tens);
  printSEG(GTime_Sec_Ones);

  printSEG(HScore_Tens);
  printSEG(HScore_Ones);

  printSEG(GScore_Tens);
  printSEG(GScore_Ones);
  printSEG(Period);
  printSEG(HFoul);
  printSEG(GFoul);
  printSEG(HTOut);
  printSEG(GTOut);
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
    if (text[0] == 'A' && text[6] == 'B') {
      int TimeMin = int(text[1]);
      int TimeSec = int(text[2]);
      int TimeMil = int(text[3]);
      int SCSec = int(text[4]);
      int SCMil = int(text[5]);

      GTime_Min_Tens = TimeMin / 10;
      GTime_Min_Ones = TimeMin % 10;
      GTime_Sec_Tens = TimeSec / 10;
      GTime_Sec_Ones = TimeSec % 10;

      SC_Tens = SCSec / 10;
      SC_Ones = SCSec % 10;
      SC_millis = SCMil;

      //      int val_sc=int(text[4]);
      //      int sc_ones=val_sc%10;
      //
      //      int sc_millis=int(text[5]);

      //Serial.println("MS:"+String(sc_millis));

      //printSEG(sc_millis);

    } else if (text[0] == 'C' && text[6] == 'D') {
      int BPZ = int(text[1]);
      int HomeFoul = int(text[2]);
      int GuestFoul = int(text[3]);
      int HomeScore = int(text[4]);
      int GuestScore = int(text[5]);

      HScore_Hund = HomeScore / 100;
      HScore_Tens = (HomeScore % 100) / 10;
      HScore_Ones = HomeScore % 10;

      GScore_Hund = GuestScore / 100;
      GScore_Tens = (GuestScore % 100) / 10;
      GScore_Ones = GuestScore % 10;

      HFoul = HomeFoul;
      GFoul = GuestFoul;

      //BallPos = BPZ % 10;
      Period = (BPZ %100)/10;
    }
    
  }

    printSEG(GTOut);
    printSEG(HTOut);
    printSEG(GFoul);
    printSEG(HFoul);
    printSEG(Period);
    printSEG(GScore_Ones);
    printSEG(GScore_Tens);
    printSEG(HScore_Ones);
    printSEG(HScore_Tens);
    printSEG(GTime_Sec_Ones);
    printSEG(GTime_Sec_Tens);
    printSEG(GTime_Min_Ones);
    printSEG(GTime_Min_Tens);
    printSEG(SC_Ones);
    printSEG(SC_Tens);
    
    rclk_pulse();
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
}

void srclk_pulse() {
  digitalWrite(srclk, 1);
  digitalWrite(srclk, 0);
}

void rclk_pulse() {
  digitalWrite(rclk, 1);
  digitalWrite(rclk, 0);
}
