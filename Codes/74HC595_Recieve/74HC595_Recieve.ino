//74HC595 Rcv
//by: KennyNeutron

#define ser   2   //d_in
#define rclk  4   //lat
#define srclk 5   //clk


void setup() {
  pinMode(ser, OUTPUT);
  pinMode(rclk, OUTPUT);
  pinMode(srclk, OUTPUT);


  digitalWrite(ser, 0);
  digitalWrite(rclk, 0);
  digitalWrite(srclk, 0);
  delay(1000);
}

void loop() {
  
    shiftOut(ser, srclk, LSBFIRST, 0b01111111);
    rclk_pulse();
    delay(1000);
    
    shiftOut(ser, srclk, LSBFIRST, 0b11111111);
    rclk_pulse();
    delay(1000);

}


void srclk_pulse() {
  digitalWrite(srclk, 1);
  digitalWrite(srclk, 0);
}

void rclk_pulse() {
  digitalWrite(rclk, 1);
  digitalWrite(rclk, 0);
}
