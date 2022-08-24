void buttonUpdate() {
  if (!StartStop_IsPressed && !status_StartStop()) {
    if (!status_StartStop()) {
      StartStop_IsPressed = true;
    }
  }

  if (!ShotClock_IsPressed && !status_ShotClock()) {
    if (menu_screen == 0) {
      //delay(10);
    }
    if (!status_ShotClock()) {
      ShotClock_IsPressed = true;
    }
  }

  if (!status_buzzer()) {
    buzzer_IsPressed = true;
    buzz=true;
  } else {
    buzzer_IsPressed = false;
    ms_buzzer = 0;
    buzz=false;
  }

  if (!status_HFoul() && !flag_HFoulToggle) {
    HFoul_IsPressed = true;
  } else if (status_HFoul()) {
    HFoul_IsPressed = false;
    flag_HFoulToggle = false;
  }

  if (!status_GFoul() && !flag_GFoulToggle) {
    GFoul_IsPressed = true;
  } else if (status_GFoul()) {
    GFoul_IsPressed = false;
    flag_GFoulToggle = false;
  }

  if (!status_HScore() && !flag_HScoreToggle) {
    HScore_IsPressed = true;
  } else if (status_HScore()) {
    HScore_IsPressed = false;
    flag_HScoreToggle = false;
  }

  if (!status_GScore() && !flag_GScoreToggle) {
    GScore_IsPressed = true;
  } else if (status_GScore()) {
    GScore_IsPressed = false;
    flag_GScoreToggle = false;
  }

  if (!status_BallPos() && !flag_BallPosToggle) {
    BallPos_IsPressed = true;
  } else if (status_BallPos()) {
    BallPos_IsPressed = false;
    flag_BallPosToggle = false;
  }

  if(!status_HTout() && !flag_HToutToggle){
    HTout_IsPressed=true;
  }else if(status_HTout()){
    HTout_IsPressed=false;
    flag_HToutToggle=false;
  }

  if(!status_GTout() && !flag_GToutToggle){
    GTout_IsPressed=true;
  }else if(status_GTout()){
    GTout_IsPressed=false;
    flag_GToutToggle=false;
  }

}


bool status_shift() {
  return digitalRead(pb_shift);
}

bool status_buzzer() {
  return digitalRead(pb_buzzer);
}

bool status_HFoul() {
  return digitalRead(pb_HFoul);
}

bool status_GFoul() {
  return digitalRead(pb_GFoul);
}

bool status_HTout(){
  return digitalRead(pb_HTout);
}

bool status_GTout(){
  return digitalRead(pb_GTout);
}

bool status_HScore() {
  return digitalRead(pb_HScore);
}

bool status_GScore() {
  return digitalRead(pb_GScore);
}

bool status_ShotClock() {
  return digitalRead(pb_ShotClock);
}

bool status_StartStop() {
  return digitalRead(pb_StartStop);
}

bool status_BallPos() {
  return digitalRead(pb_BallPos);
}
