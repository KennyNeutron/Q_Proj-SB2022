void DataEncrypt_Time() {
  ch_message[0] = 'A';        //HEADER
  ch_message[1] = TimeMin;    //GameTime MINUTE

  ch_message[2] = TimeSec;    //GameTime SECOND

  ch_message[3] = TimeMil;    //GameTime MILLIS


  ch_message[4] = SC_sec;    //ShotClock SECOND


  ch_message[5] = SC_mil;    //ShotClock MILLIS


  ch_message[6] = 'B';        //FOOTER
}

void DataEncrypt_Other() {
  byte BPZ = 0; //Ballpos Period Buzzer
  byte HGFoul = 0; //Home & Guest Foul
  byte HGTOut = 0; //Home & Guest TOut
  BPZ = (BallPos * 100) + (period * 10) + buzz;

  if (HomeFoul < 10 && GuestFoul == 10) {
    HGFoul = HomeFoul + 200;
  } else if (HomeFoul == 10 && GuestFoul < 10) {
    HGFoul = (HomeFoul * 10) + GuestFoul;
  } else if (HomeFoul < 10 && GuestFoul < 10) {
    HGFoul = (HomeFoul * 10) + GuestFoul;
  } else if (HomeFoul == 10 && GuestFoul == 10) {
    HGFoul = (HomeFoul * 10) + GuestFoul;
  }

  /*
    Serial.println("HF:"+String(HomeFoul));
    Serial.println("GF:"+String(GuestFoul));
    Serial.println("HGF:"+String(HGFoul));
  */
  HGTOut = (HomeTout * 10) + GuestTout;

  ch_message[0] = 'C';         //HEADER

  ch_message[1] = BPZ;         //Ball poss. Period Buzzer

  ch_message[2] = HGFoul;     //Home & Guest Foul


  ch_message[3] = HGTOut;     //Home & Guest Tout

  ch_message[4] = HomeScore;     //Home Score

  ch_message[5] = GuestScore;     //Guest Score

  ch_message[6] = 'D';        //FOOTER

}

void DataEncrypt_SET_Time() {
  ch_message[0] = 'W';        //HEADER
  ch_message[1] = TimeMin;    //GameTime MINUTE

  ch_message[2] = TimeSec;    //GameTime SECOND

  ch_message[3] = TimeMil;    //GameTime MILLIS


  ch_message[4] = SC_sec;    //ShotClock SECOND


  byte ToSet = (SC_mil * 10) + menu_ToSet;
  ch_message[5] = ToSet;    //ShotClock MILLIS
  ch_message[6] = 'X';        //FOOTER
}

void DataEncrypt_Other_WINNER() {
  byte BPZ = 0; //Ballpos Period Buzzer
  byte HGFoul = 0; //Home & Guest Foul
  byte HGTOut = 0; //Home & Guest TOut
  BPZ = (BallPos * 100) + (period * 10) + buzz;

  if (HomeFoul < 10 && GuestFoul == 10) {
    HGFoul = HomeFoul + 200;
  } else if (HomeFoul == 10 && GuestFoul < 10) {
    HGFoul = (HomeFoul * 10) + GuestFoul;
  } else if (HomeFoul < 10 && GuestFoul < 10) {
    HGFoul = (HomeFoul * 10) + GuestFoul;
  } else if (HomeFoul == 10 && GuestFoul == 10) {
    HGFoul = (HomeFoul * 10) + GuestFoul;
  }

  /*
    Serial.println("HF:"+String(HomeFoul));
    Serial.println("GF:"+String(GuestFoul));
    Serial.println("HGF:"+String(HGFoul));
  */
  HGTOut = (HomeTout * 10) + GuestTout;

  ch_message[0] = 'Y';         //HEADER

  ch_message[1] = BPZ;         //Ball poss. Period Buzzer

  ch_message[2] = HGFoul;     //Home & Guest Foul


  ch_message[3] = HGTOut;     //Home & Guest Tout

  ch_message[4] = HomeScore;     //Home Score

  ch_message[5] = GuestScore;     //Guest Score

  ch_message[6] = 'Z';        //FOOTER

}
