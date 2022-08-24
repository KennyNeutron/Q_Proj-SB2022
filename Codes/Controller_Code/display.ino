void display_SB() {

  if (!winner_avail) {
    if (menu_screen == 0) {
      MenuScreen_MainSB();
    } else if (menu_screen == 1) {
      MenuScreen_SetSB();
      u8g.setFont(u8g_font_helvR08);
      u8g.drawStr(54, 64, "SET");
      switch (menu_ToSet) {
        case 1:
          u8g.drawStr(0, 24, "^^^^");   //Set GameTime-Minute
          break;
        case 2:
          u8g.drawStr(30, 24, "^^^^");  //Set GameTime-Seconds
          break;
        case 3:
          u8g.drawStr(60, 24, "^^");    //Set GameTime-Millis
          break;
        case 4:
          u8g.drawStr(86, 24, "^^^^");  //Set ShotClock-Seconds
          break;
        case 5:
          u8g.drawStr(116, 24, "^^");   //Set ShotClock-Millis
          break;
        case 6:
          u8g.drawStr(59, 49, "^^"); //Set Period
          break;
      }

    }

    //  if (flag_start == true) {
    //    u8g.setFont(u8g_font_helvR08);
    //    u8g.drawStr(64, 64, "S");
    //  } else {
    //    u8g.setFont(u8g_font_helvR08);
    //    u8g.drawStr(64, 64, "P");
    //  }
  } else if (winner_avail == true) {
    MenuScreen_WinnerAvailable();
  }



}

void display_guidelines() {
  u8g.drawLine(0, 32, 128, 32);
  u8g.drawLine(64, 0, 64, 64);
}

void MenuScreen_MainSB() {
  char ch_GameTime[8] = "";
  char ch_ShotClock[5] = "";
  char ch_Period[2] = "";
  char ch_HFoul[2] = "";
  char ch_GFoul[2] = "";
  char ch_HTout[2] = "";
  char ch_GTout[2] = "";
  char ch_HScore[4] = "";
  char ch_GScore[4] = "";

  if (TimeMin >= 10 && TimeSec >= 10) {
    sprintf(ch_GameTime, "%d:%d.%d", TimeMin, TimeSec, TimeMil);
  } else if (TimeMin < 10 && TimeSec >= 10) {
    sprintf(ch_GameTime, "0%d:%d.%d", TimeMin, TimeSec, TimeMil);
  } else if (TimeMin >= 10 && TimeSec < 10) {
    sprintf(ch_GameTime, "%d:0%d.%d", TimeMin, TimeSec, TimeMil);
  } else if (TimeMin < 10 && TimeSec < 10) {
    sprintf(ch_GameTime, "0%d:0%d.%d", TimeMin, TimeSec, TimeMil);
  }

  if (SC_sec < 10) {
    sprintf(ch_ShotClock, "0%d.%d", SC_sec, SC_mil);
  } else {
    sprintf(ch_ShotClock, "%d.%d", SC_sec, SC_mil);
  }

  sprintf(ch_Period, "%d", period);

  if (HomeFoul == 10) {
    ch_HFoul[0] = 'P';
  } else {
    sprintf(ch_HFoul, "%d", HomeFoul);
  }

  if (GuestFoul == 10) {
    ch_GFoul[0] = 'P';
  } else {
    sprintf(ch_GFoul, "%d", GuestFoul);
  }

  sprintf(ch_HTout, "%d", HomeTout);
  sprintf(ch_GTout, "%d", GuestTout);

  sprintf(ch_HScore, "%d", HomeScore);
  sprintf(ch_GScore, "%d", GuestScore);

  u8g.setFont(u8g_font_gdb14r);
  u8g.drawStr(2, 14, ch_GameTime);    //GameTime
  u8g.drawStr(85, 14, ch_ShotClock);  //Shotclock

  u8g.drawStr(2, 39, ch_HFoul);     //HomeFoul
  u8g.drawStr(115, 39, ch_GFoul);   //GuestFoul

  u8g.drawStr(29, 39, ch_HTout);    //Home Time Out
  u8g.drawStr(88, 39, ch_GTout);   //Guest Time Out

  u8g.drawStr(2, 64, ch_HScore);    //HomeScore

  if (String(GuestScore).length() == 1) {
    u8g.drawStr(115, 64, ch_GScore);   //GuestScore
  } else if (String(GuestScore).length() == 2) {
    u8g.drawStr(103, 64, ch_GScore);   //GuestScore
  } else {
    u8g.drawStr(91, 64, ch_GScore);   //GuestScore
  }

  if (period == 5) {
    u8g.drawStr(51, 37, "OT");      //Period
  } else {
    u8g.drawStr(59, 37, ch_Period); //Period
  }

  if (BallPos == 1) {
    u8g.drawTriangle(50, 50, 50, 64, 40, 57); //HomeArrow
  } else if (BallPos == 2) {
    u8g.drawTriangle(78, 50, 78, 64, 88, 57); //GuestArrow
  }


  if (SC_mil == 0 && SC_sec == 0) {
    flag_SCDisplayed = true;
  }

}

void MenuScreen_SetSB() {
  char ch_GameTime[8] = "";
  char ch_ShotClock[5] = "";
  char ch_Period[2] = "";
  char ch_HFoul[2] = "";
  char ch_GFoul[2] = "";
  char ch_HScore[4] = "";
  char ch_GScore[4] = "";

  if (TimeMin >= 10 && TimeSec >= 10) {
    sprintf(ch_GameTime, "%d:%d.%d", TimeMin, TimeSec, TimeMil);
  } else if (TimeMin < 10 && TimeSec >= 10) {
    sprintf(ch_GameTime, "0%d:%d.%d", TimeMin, TimeSec, TimeMil);
  } else if (TimeMin >= 10 && TimeSec < 10) {
    sprintf(ch_GameTime, "%d:0%d.%d", TimeMin, TimeSec, TimeMil);
  } else if (TimeMin < 10 && TimeSec < 10) {
    sprintf(ch_GameTime, "0%d:0%d.%d", TimeMin, TimeSec, TimeMil);
  }

  if (SC_sec < 10) {
    sprintf(ch_ShotClock, "0%d.%d", SC_sec, SC_mil);
  } else {
    sprintf(ch_ShotClock, "%d.%d", SC_sec, SC_mil);
  }

  sprintf(ch_Period, "%d", period);

  sprintf(ch_HFoul, "%d", HomeFoul);
  sprintf(ch_GFoul, "%d", GuestFoul);

  sprintf(ch_HScore, "%d", HomeScore);
  sprintf(ch_GScore, "%d", GuestScore);


  u8g.setFont(u8g_font_gdb14r);
  u8g.drawStr(0, 14, ch_GameTime);    //GameTime
  u8g.drawStr(86, 14, ch_ShotClock);  //Shotclock





  if (period == 5) {
    u8g.drawStr(51, 37, "OT");      //Period
  } else {
    u8g.drawStr(59, 37, ch_Period); //Period
  }

  if (SC_mil == 0 && SC_sec == 0) {
    flag_SCDisplayed = true;
  }

}



void MenuScreen_WinnerAvailable() {
  char ch_GameTime[8] = "";
  char ch_ShotClock[5] = "";
  char ch_Period[2] = "";
  char ch_HFoul[2] = "";
  char ch_GFoul[2] = "";
  char ch_HScore[4] = "";
  char ch_GScore[4] = "";

  if (TimeMin >= 10 && TimeSec >= 10) {
    sprintf(ch_GameTime, "%d:%d.%d", TimeMin, TimeSec, TimeMil);
  } else if (TimeMin < 10 && TimeSec >= 10) {
    sprintf(ch_GameTime, "0%d:%d.%d", TimeMin, TimeSec, TimeMil);
  } else if (TimeMin >= 10 && TimeSec < 10) {
    sprintf(ch_GameTime, "%d:0%d.%d", TimeMin, TimeSec, TimeMil);
  } else if (TimeMin < 10 && TimeSec < 10) {
    sprintf(ch_GameTime, "0%d:0%d.%d", TimeMin, TimeSec, TimeMil);
  }

  if (SC_sec < 10) {
    sprintf(ch_ShotClock, "0%d.%d", SC_sec, SC_mil);
  } else {
    sprintf(ch_ShotClock, "%d.%d", SC_sec, SC_mil);
  }

  sprintf(ch_Period, "%d", period);

  sprintf(ch_HFoul, "%d", HomeFoul);
  sprintf(ch_GFoul, "%d", GuestFoul);

  sprintf(ch_HScore, "%d", HomeScore);
  sprintf(ch_GScore, "%d", GuestScore);

  u8g.setFont(u8g_font_gdb14r);
  u8g.drawStr(0, 14, ch_GameTime);    //GameTime
  u8g.drawStr(86, 14, ch_ShotClock);  //Shotclock

  u8g.drawStr(0, 39, ch_HFoul);     //HomeFoul
  u8g.drawStr(117, 39, ch_GFoul);   //GuestFoul

  if (WINNER) {
    u8g.setFont(u8g_font_helvR08);
    u8g.drawStr(33, 48, "HOME WINS!");
    u8g.setFont(u8g_font_gdb14r);
  } else if (!WINNER) {
    u8g.setFont(u8g_font_helvR08);
    u8g.drawStr(31, 48, "GUEST WINS!");
    u8g.setFont(u8g_font_gdb14r);
  }


  if (millis() - last_millisWIN >= blink_period) {
    last_millisWIN = millis();
    flag_WinnerBlink = !flag_WinnerBlink;
  }

  if (flag_WinnerBlink == true) {
    u8g.drawStr(0, 64, ch_HScore);    //HomeScore

    if (String(GuestScore).length() == 1) {
      u8g.drawStr(117, 64, ch_GScore);   //GuestScore
    } else if (String(GuestScore).length() == 2) {
      u8g.drawStr(105, 64, ch_GScore);   //GuestScore
    } else {
      u8g.drawStr(93, 64, ch_GScore);   //GuestScore
    }

  } else {
    if (!WINNER) {
      u8g.drawStr(0, 64, ch_HScore);    //HomeScore
    } else if (WINNER) {
      if (String(GuestScore).length() == 1) {
        u8g.drawStr(117, 64, ch_GScore);   //GuestScore
      } else if (String(GuestScore).length() == 2) {
        u8g.drawStr(105, 64, ch_GScore);   //GuestScore
      } else {
        u8g.drawStr(93, 64, ch_GScore);   //GuestScore
      }
    }
  }

  if (period == 5) {
    u8g.drawStr(51, 37, "OT");      //Period
  } else {
    u8g.drawStr(59, 37, ch_Period); //Period
  }


  if (BallPos == 1) {
    u8g.drawTriangle(50, 50, 50, 64, 40, 57); //HomeArrow
  } else if (BallPos == 2) {
    u8g.drawTriangle(78, 50, 78, 64, 88, 57); //GuestArrow
  }


  if (SC_mil == 0 && SC_sec == 0) {
    flag_SCDisplayed = true;
  }

}
