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


byte GTime_Min_Tens = 0;
byte GTime_Min_Ones = 0;
byte GTime_Sec_Tens = 0;
byte GTime_Sec_Ones = 0;
byte GTime_Millis = 0;
byte SC_Tens = 0;
byte SC_Ones = 0;
byte SC_millis;


byte HomeScore = 0;
byte GuestScore = 0;
byte HScore_Hund = 0;
byte HScore_Tens = 0;
byte HScore_Ones = 6;
byte GScore_Hund = 0;
byte GScore_Tens = 0;
byte GScore_Ones = 0;

byte HFoul = 0;
byte GFoul = 0;
byte HTOut = 0;
byte GTOut = 0;

byte Period = 1;
byte BallPos = 0;

void setup() {
  pinMode(ser, OUTPUT);
  pinMode(rclk, OUTPUT);
  pinMode(srclk, OUTPUT);


  digitalWrite(ser, 0);
  digitalWrite(rclk, 0);
  digitalWrite(srclk, 0);

  //printSEG(8);

  Serial.begin(115200);
  Serial.println("START");
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  delay(1000);

  printSEG0(SC_Tens);
  printSEG0(SC_Ones);

  printSEG0(GTime_Min_Tens);
  printSEG0(GTime_Min_Ones);
  printSEG0(GTime_Sec_Tens);
  printSEG0(GTime_Sec_Ones);

  printSEG0(HScore_Tens);
  printSEG0(HScore_Ones);

  printSEG0(GScore_Tens);
  printSEG0(GScore_Ones);
  printSEG0(Period);
  printSEG0(HFoul);
  printSEG0(GFoul);
  printSEG0(HTOut);
  printSEG0(GTOut);
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
      byte TimeMin = int(text[1]);
      byte TimeSec = int(text[2]);
      byte TimeMil = int(text[3]);
      byte SCSec = int(text[4]);
      byte SCMil = int(text[5]);

      Serial.println("text[0]:" + String(text[0]));
      Serial.println("text[1]:" + String(int(text[1])));
      Serial.println("text[2]:" + String(int(text[2])));
      Serial.println("text[3]:" + String(int(text[3])));
      Serial.println("text[4]:" + String(int(text[4])));
      Serial.println("text[5]:" + String(int(text[5])));
      Serial.println("text[6]:" + String(text[6]));

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

      Serial.println("text[0]:" + String(text[0]));
      Serial.println("text[1]:" + String(int(text[1])));
      Serial.println("text[2]:" + String(int(text[2])));
      Serial.println("text[3]:" + String(int(text[3])));
      Serial.println("text[4]:" + String(byte(text[4])));
      Serial.println("text[5]:" + String(byte(text[5])));
      Serial.println("text[6]:" + String(text[6]));

      byte BPZ = byte(text[1]);
      byte HGFoul = byte(text[2]);
      byte HGTOut = byte(text[3]);
      HomeScore = byte(text[4]);
      GuestScore = byte(text[5]);


      HScore_Hund = HomeScore / 100;
      HScore_Tens = (HomeScore % 100) / 10;
      HScore_Ones = HomeScore % 10;

      GScore_Hund = GuestScore / 100;
      GScore_Tens = (GuestScore % 100) / 10;
      GScore_Ones = GuestScore % 10;

      if (HGFoul ==110) {
        HFoul=10;
        GFoul=10;
      }else if(HGFoul>=200){
        HFoul=HGFoul-200;
        GFoul=10;
      }else {
        HFoul = HGFoul / 10;
        GFoul = HGFoul % 10;
      }

      HTOut = HGTOut / 10;
      GTOut = HGTOut % 10;

      BallPos = BPZ / 100;
      Period = (BPZ % 100) / 10;

      //Serial.println("BPZ:" + String(BPZ));
      //Serial.println("BP:" + String(BallPos));
    }

  }

  printSEG0(GTOut);
  printSEG0(HTOut);
  printSEG0(GFoul);
  printSEG0(HFoul);

  if (Period == 5) {
    printSEG0(11);
  } else {
    printSEG0(Period);
  }

  if (GScore_Hund == 1) {
    printSEG1(GScore_Ones);
    printSEG1(GScore_Tens);
  } else {
    if (GuestScore < 10) {
      printSEG0(GScore_Ones);
      printSEG0(12);
    } else {
      printSEG0(GScore_Ones);
      printSEG0(GScore_Tens);
    }
  }

  if (HScore_Hund == 1) {
    printSEG1(HScore_Ones);
    printSEG1(HScore_Tens);
  } else {
    if (HomeScore < 10) {
      printSEG0(HScore_Ones);
      printSEG0(12);
    } else {
      printSEG0(HScore_Ones);
      printSEG0(HScore_Tens);
    }
  }

  if (BallPos == 2) {
    printSEG1(GTime_Sec_Ones);
  } else {
    printSEG0(GTime_Sec_Ones);
  }

  printSEG0(GTime_Sec_Tens);
  printSEG0(GTime_Min_Ones);
  if (BallPos == 1) {
    printSEG1(GTime_Min_Tens);
  } else {
    printSEG0(GTime_Min_Tens);
  }
  printSEG0(SC_Ones);
  printSEG0(SC_Tens);

  rclk_pulse();
}
