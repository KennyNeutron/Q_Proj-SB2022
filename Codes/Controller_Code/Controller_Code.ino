//SB Cont by: Kenny Neutron
//07-30-2022


//LAST UPDATE: 09-14-2022 @ 10:06AM


#include "Arduino.h"
#include <EEPROM.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

#include <Wire.h>

#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST); // Fast I2C / TWI
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
//#define u8g_logo_width 38
//#define u8g_logo_height 24
////static unsigned char u8g_logo_bits[] = {
//static unsigned char u8g_logo_bits[] U8G_PROGMEM = {
//   0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xe0, 0xe0,
//   0xff, 0xff, 0x3f, 0xe3, 0xe1, 0xff, 0xff, 0x3f, 0xf3, 0xf1, 0xff, 0xff,
//   0x3f, 0xf3, 0xf1, 0xfe, 0xbf, 0x37, 0xf3, 0x11, 0x1c, 0x1f, 0x30, 0xf3,
//   0x01, 0x08, 0x8c, 0x20, 0xf3, 0x01, 0x00, 0xc0, 0x39, 0xf3, 0x81, 0xc7,
//   0xc1, 0x39, 0xf3, 0xc1, 0xc7, 0xc9, 0x38, 0xf3, 0xc1, 0xc3, 0x19, 0x3c,
//   0xe3, 0x89, 0x01, 0x98, 0x3f, 0xc7, 0x18, 0x00, 0x08, 0x3e, 0x0f, 0x3c,
//   0x70, 0x1c, 0x30, 0x3f, 0xff, 0xfc, 0x87, 0x31, 0xff, 0xff, 0xbf, 0xc7,
//   0x23, 0x01, 0x00, 0x00, 0xc6, 0x23, 0x03, 0x00, 0x00, 0x0e, 0x30, 0xff,
//   0xff, 0x3f, 0x1f, 0x3c, 0xff, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0xff, 0x3f,
//   0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f };

//Buttons
#define pb_shift      4
#define pb_buzzer     5
#define pb_HFoul      6
#define pb_GFoul      7
#define pb_HScore     8
#define pb_GScore     A0
#define pb_ShotClock  A1
#define pb_StartStop  A2
#define pb_BallPos    A3

#define pb_HTout      2
#define pb_GTout      3

#define pb_r12        A6

#define batt_in     A7

#define charging  0
#define testpin   1
//Outputs
//#define buzzer 3

bool buzzer_IsPressed = false;
bool HFoul_IsPressed = false;
bool GFoul_IsPressed = false;
bool HScore_IsPressed = false;
bool GScore_IsPressed = false;
bool ShotClock_IsPressed = false;
bool StartStop_IsPressed = false;
bool BallPos_IsPressed = false;

bool HTout_IsPressed = false;
bool GTout_IsPressed = false;

bool r12_IsPressed = false;

bool WINNER = true; //true= HOME WINNER     false= GUEST WINNER     NOTE: only if the game is doene
bool winner_avail = false; //goes true if a winner is declared;

bool toggle1HZ = false;

//Game Variables (RAW)
byte TimeMin = 10; //GameTime Minute
byte TimeSec = 0; //GameTime Second
byte TimeMil = 0; //GameTime Millis

byte SC_sec = 24; //ShotClock Second
byte SC_mil = 0; //ShotClock Millis

byte HomeScore = 0; //HomeScore
byte GuestScore = 0; //GuestScore

byte HomeFoul = 0; //HomeFoul
byte GuestFoul = 0; //GuestFoul

byte HomeTout = 0; //Home TimeOut
byte GuestTout = 0; // Guest TimeOut

byte period = 1; //Period or Quarter

byte BallPos = 0; //BallPosession 0=NoPossession 1=Home 2=Guest

bool buzz = false;
bool flag_start = false;
bool flag_SSToggle = false;
bool flag_SCToggle = false;
bool flag_SCDisplayed = false;
bool flag_QFinish = false;
bool flag_QFinishToggle = false;
bool flag_HFoulToggle = false;
bool flag_GFoulToggle = false;
bool flag_HScoreToggle = false;
bool flag_GScoreToggle = false;
bool flag_BallPosToggle = false;
bool flag_ChangeMenuToggle = false;
bool flag_WinnerBlink = false;
bool flag_NewGame = false;

bool flag_HToutToggle = false;
bool flag_GToutToggle = false;

bool flag_r12Toggle = false;

bool flag_buzz = false;
bool flag_buzz2 = false;
bool flag_buzzQ = false;


uint32_t last_millis = 0;
uint32_t last_millis2 = 0;
uint32_t SC_last_millis = 0;
uint32_t SC_cnt = 0;

uint32_t batt_last_millis = 0;
uint32_t loading_last_millis = 0;

uint32_t last_millisWIN = 0; //for blinking (winner);
uint16_t blink_period = 500; //blink period


byte menu_screen = 0;
byte menu_ToSet = 0;
byte ms_counter = 0;  //for SHIFT + START/STOP
byte ms_buzzer = 0; //for SHIFT + BUZZER


char ch_message[7] = "FFFFFF";

uint16_t tcounter = 0;

bool loading_sc = false;

unsigned int batt_val = 0;

int batt_percent = 100;

int BuzzCount = 0;

bool flag_battSUB = false;

bool charging_toggle = false;

bool testtoggle = 0;
unsigned int ISR_TMR = 0;

void setup() {
  //EEPROM.write(2, 100);
  //
  //  if(EEPROM.read(1)!=1){
  //    EEPROM.write(2, 100);
  //    EEPROM.write(1,1);
  //  }
  //
  //
  //  batt_percent = EEPROM.read(2);

  // flip screen, if required
  // u8g.setRot180();

  // flip screen, if required
  // u8g.setRot180();

  // set SPI backup if required
  //u8g.setHardwareBackup(u8g_backup_avr_spi);

  // assign default color value
  //Serial.begin(115200);
  //Serial.println("START");

  //SETUP INTERRUPT
  //pinMode(testpin, OUTPUT);
  cli();//stop interrupts
  //set timer2 interrupt at 8kHz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 8khz increments
  OCR2A = 249;// = (16*10^6) / (8000*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 bit for 8 prescaler
  TCCR2B |= (1 << CS21);
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  sei();//allow interrupts


  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();

  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255, 255, 255);
  }

  analogReference(INTERNAL);

  pinMode(pb_shift, INPUT_PULLUP);
  pinMode(pb_buzzer, INPUT_PULLUP);
  pinMode(pb_HFoul, INPUT_PULLUP);
  pinMode(pb_GFoul, INPUT_PULLUP);
  pinMode(pb_HScore, INPUT_PULLUP);
  pinMode(pb_GScore, INPUT_PULLUP);
  pinMode(pb_ShotClock, INPUT_PULLUP);
  pinMode(pb_StartStop, INPUT_PULLUP);
  pinMode(pb_BallPos, INPUT_PULLUP);

  pinMode(pb_HTout, INPUT_PULLUP);
  pinMode(pb_GTout, INPUT_PULLUP);

  pinMode(pb_r12, INPUT);

  pinMode(batt_in, INPUT_PULLUP);
  pinMode(charging, INPUT);

  //pinMode(buzzer, OUTPUT);

  //tone(buzzer, 1000);
  delay(3000);
  //noTone(buzzer);

  batt_val = analogRead(batt_in);
  batt_percent = (batt_val * 100) / 210;

  last_millis = micros();
  batt_last_millis = millis();
  loading_last_millis = millis();
}


ISR(TIMER2_COMPA_vect) { //timer1 interrupt 8kHz toggles pin 9
  //generates pulse wave of frequency 8kHz/2 = 4kHz (takes two cycles for full wave- toggle high then toggle low)

  if (flag_start == true) {
    ISR_TMR++;
    if (ISR_TMR >= 800) {
      TimeMil--;
      SC_mil--;
      ISR_TMR = 0;
    }
  }


  if (TimeMil == 255) {
    TimeSec--;
    TimeMil = 9;
    //1 HZ SIGNAL
    //testtoggle = !testtoggle;
    //digitalWrite(testpin, testtoggle);
  }

  if (TimeSec == 255) {
    TimeMin--;
    TimeSec = 59;
  }

  if (TimeMin == 0 && TimeSec == 0 && TimeMil == 0) {
    flag_start = false;
    flag_QFinish = true;
  }

  if (SC_sec == 255) {
    SC_sec = 24;
  }
  if (SC_mil == 255) {
    toggle1HZ = !toggle1HZ;
    SC_sec--;
    SC_mil = 9;
  }

  if (SC_sec == 0 && SC_mil == 0) {
    flag_start = false;
  }
}

void loop() {

  //Serial.println("Batt:"+String(batt_val));
  //Serial.println("R12: "+String(analogRead(pb_r12)));
  //Serial.println("Batt:"+String(batt_percent));
  while(1){
  }

  if (digitalRead(charging) == 0 && charging_toggle == true) {
    delayMicroseconds(100);
    batt_val = analogRead(batt_in);
    batt_percent = (batt_val * 100) / 210;
    charging_toggle = false;
  }

  //Dito mag BUZZ
  if (SC_sec == 0 && SC_mil == 0 && !flag_buzz) {
    SC_cnt = 0;
    if (TimeMin > 0 || TimeSec > 0 || TimeMil > 0) {
      flag_buzz = true;
    }
  }

  if (SC_sec == 0 && SC_mil == 0 && TimeMin == 0 && TimeSec == 0 && TimeMil == 0 && flag_buzzQ == false) {
    SC_cnt = 0;
    BuzzCount = 0;
    //Serial.println("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    flag_buzzQ = true;
    flag_buzz2 = true;
  }


  if (flag_buzzQ == true) {
    //Serial.println("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");
    buzz = true;
    BuzzCount++;

    if (BuzzCount >= 40) {
      flag_buzzQ = false;
      flag_buzz = false;
      buzz = false;
      QuarterDone();
    }
  }

  //Serial.println("bz2:"+String(flag_buzzQ));
  //Serial.println("SCCNt: " + String(BuzzCount));

  if (flag_buzz == true) {
    buzz = true;
    SC_cnt++;
    if (SC_cnt >= 20) {
      flag_buzz = false;
      buzz = false;
      SC_sec = 24;
    }
    NRF_Broadcast();
  }






  if (flag_NewGame == true) {
    SC_sec = 24;
    SC_mil = 0;
    flag_NewGame = false;
  }

  last_millis2 = millis();

  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
  //Serial.println("diff: " + String(millis() - last_millis2));


  /*
    if (flag_start == true) {
    TimerStarted();
    }
  */

  if (TimeMin == 0 && TimeSec < SC_sec && menu_screen == 0) {
    SC_sec = TimeSec;
    SC_mil = TimeMil;
  }


  NRF_Broadcast();

  //TIME SUBTRACT?
  /*
    if (flag_start == true) {
    TimerStarted();
    }
  */

  buttonUpdate();

  //  if (flag_start == true) {
  //    TimerStarted();
  //  }

  switch (menu_screen) {
    case 0:
      if (!winner_avail) {
        con_StartStop();//Start/Stop Button is Pressed
        con_ShotClock();//ShotClock Button is Pressed
        con_Buzzer();//Buzzer Button is Pressed
        con_HomeFoul();//HomeFoul Button is Pressed
        con_GuestFoul();//GuestFoul Button is Pressed
        con_HScore();//HomeScore Button is Pressed
        con_GScore();//GuestScore Button is Pressed
        con_BallPos();//BallPos Button is Pressed
        con_HTout();//Home TimeOut Button is Pressed
        con_GTout();//Guest TimeOut Button is Pressed
        con_R12();//Reset 12 is Pressed
      } else if (winner_avail == true) {
        con_Buzzer();//Buzzer Button is Pressed
      }
      break;

    case 1:
      con_StartStop();//Start/Stop Button is Pressed
      con_ShotClock();//ShotClock Button is Pressed
      con_BallPos();//BallPos Button is Pressed
      con_HScore();//HomeScore Button is Pressed
      con_GScore();//GuestScore Button is Pressed
      break;

  }

  /*
    if ((millis()-batt_last_millis) >= 2880000) {
      batt_percent -= 10;
      if (batt_percent <= 0) {
        batt_percent = 0;
      }
      //Serial.println("WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
      EEPROM.write(3, batt_percent);
      batt_last_millis = millis();
    }
  */


  if ((millis() - batt_last_millis) >= 60000) {
    batt_val = analogRead(batt_in);
    batt_percent = (batt_val * 100) / 210;

    batt_last_millis = millis();
  }

}

void draw() {
  // graphic commands to redraw the complete screen should be placed here
  //u8g.drawXBMP( 0, 0, u8g_logo_width, u8g_logo_height, u8g_logo_bits);

  //display_guidelines();

  if (loading_sc == false) {
    if ((millis() - loading_last_millis) > 3000) {
      loading_sc = true;
    }
    loading_screen(); 
    batt_val = analogRead(batt_in);
    batt_percent = (batt_val * 100) / 210;
  } else {
    display_SB();
  }
}

void NRF_Broadcast() {
  if (menu_screen == 1) {
    DataEncrypt_SET_Time();
  } else {
    DataEncrypt_Time();
  }

  //Serial.println("MS:"+String(menu_screen));
  //Serial.println(ch_message);
  radio.write(&ch_message, sizeof(ch_message));

  if (!winner_avail) {
    DataEncrypt_Other();
  } else {
    DataEncrypt_Other_WINNER();
  }
  //Serial.print(ch_message);
  radio.write(&ch_message, sizeof(ch_message));
  //  delay(5);
  //  radio.write(&ch_message, sizeof(ch_message));
  //  delay(5);
  //  radio.write(&ch_message, sizeof(ch_message));
}


/*
  void TimerStarted() {
  //Serial.println("act: " + String(millis() - last_millis));
  if ((micros() - last_millis) >= 70000) {
    last_millis = micros();
    TimeMil--;
    SC_mil--;
  }

  if (TimeMil == 255) {
    TimeSec--;
    TimeMil = 9;
  }

  if (TimeSec == 255) {
    TimeMin--;
    TimeSec = 59;
  }

  if (TimeMin == 0 && TimeSec == 0 && TimeMil == 0) {
    flag_start = false;
    flag_QFinish = true;
  }

  if (SC_sec == 255) {
    SC_sec = 24;
  }
  if (SC_mil == 255) {
    toggle1HZ = !toggle1HZ;
    SC_sec--;
    SC_mil = 9;
  }

  if (SC_sec == 0 && SC_mil == 0) {
    flag_start = false;
  }
  }
*/

void reset_AllVariables() {
  TimeMin = 10; //GameTime Minute
  TimeSec = 0; //GameTime Second
  TimeMil = 0; //GameTime Millis

  SC_sec = 24; //ShotClock Second
  SC_mil = 0; //ShotClock Millis

  HomeScore = 0; //HomeScore
  GuestScore = 0; //GuestScore

  HomeFoul = 0; //HomeFoul
  GuestFoul = 0; //GuestFoul

  HomeTout = 0; //Home TOut
  GuestTout = 0; //Guesr TOut

  period = 1; //Period or Quarter

  BallPos = 0; //BallPosession 0=NoPossession 1=Home 2=Guest

  winner_avail = false;
}


void QuarterDone() {
  //tone(buzzer, 1000);

  flag_SCDisplayed = false;

  if (flag_QFinish == true && !winner_avail) {

    //Dito mag buzzer pag 0 na ang time

    for (int a = 0; a <= 3; a++) {
      //delay(100);
      //buzz=true;
      NRF_Broadcast();
    }
    //noTone(buzzer);
    //SC_sec = 24;
    //buzz = false;

    if (period == 4 || period == 5) {
      if (HomeScore != GuestScore) {
        //There is a WINNER!
        if (HomeScore > GuestScore) {
          //Serial.println("HOME WINS!");
          WINNER = true;
        } else if (GuestScore > HomeScore) {
          //Serial.println("GUEST WINS!");
          WINNER = false;
        }
        winner_avail = true;
      } else if (HomeScore == GuestScore) {
        //It's a TIE! Go for OT
        period = 5;
      }
    }

    flag_QFinishToggle = true;
    if (period != 5 && !winner_avail) {
      period++;
      TimeMin = 10;
      TimeSec = 0;
      TimeMil = 0;
      SC_sec = 24;
      SC_mil = 0;
      HomeFoul = 0;
      GuestFoul = 0;
      HomeTout = 0;
      GuestTout = 0;
      BallPos = 0;
    } else if (period == 5 && !winner_avail) {
      TimeMin = 5;
      TimeSec = 0;
      TimeMil = 0;
      SC_sec = 24;
      SC_mil = 0;
      HomeFoul = 0;
      GuestFoul = 0;
      HomeTout = 0;
      GuestTout = 0;
      BallPos = 0;
    }

    flag_QFinish = false;
    flag_QFinishToggle = false;
  }
  //    else {
  //      for (int a = 0; a <= 30; a++) {
  //        //delay(100);
  //        NRF_Broadcast();
  //      }
  //      //noTone(buzzer);
  //      //buzz = false;
  //    }


}
