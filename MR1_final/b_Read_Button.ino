void Read_button() {

  if (ps2.Button(PSB_START)) {
    ps2.read_gamepad();
    delay(30);
    return;
  }

  if ((ps2.Button(PSB_R1)) && (ps2.Button(PSB_PAD_UP)) && !(r_flag || l_flag)){
    Curve_Clockwise();
    Serial.println("CURVE CLOCKWISE");
  }
  else if ((ps2.Button(PSB_L1)) && (ps2.Button(PSB_PAD_UP)) && !(r_flag || l_flag)){
    Curve_Anti();
    Serial.println("CURVE ANTI-CLOCKWISE");
  }

  else if (ps2.Button(PSB_R1)) {
    run_motors(m1c,  0.40 * spd, m2c,  0.40 * spd, m3c,  0.40 * spd);
    Serial.println("Clockwise");
  }

  else if (ps2.Button(PSB_L1)) {
    run_motors(m1ac,  0.40 * spd, m2ac,  0.40 * spd, m3ac, 0.40 * spd);
    Serial.println("Anti-Clockwise");
  }

  //  else if (ps2.ButtonReleased(PSB_SELECT)) {
  //    ps2.read_gamepad();
  //    Serial.println(" Virtual Resetting");
  //    EEPROM.update(0, 2);                    //Byte 0 holds reset info. 0 - Connection failure 2 - User Reset
  //    EEPROM.update(4, 150);                  //Byte 4 holds motor speed (Set to default in this condition)
  //    EEPROM.update(8, 0);                    //Byte 8 holds the throwing mechanism statusu
  //    resetFunc();
  //  }

  //Timer Control
  else if (ps2.ButtonReleased(PSB_SELECT)) {
    lcd_flag++;
    if (lcd_flag == 1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SPEED : " + String(spd));   //Print Speed to LCD
      lcd.setCursor(0, 2);

      lcd.print("TEAM ASTROS");
    }

    else if (lcd_flag == 3) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SPEED : " + String(spd));   //Print Speed to LCD
      lcd.setCursor(0, 2);
      last = millis() - last;
      double d = (double)last / 1000;
      lcd.print("TIME : " + String(d));
      Serial.println(last);
      lcd_flag = 0;
    }
    Serial.println("LCD :" + String(lcd_flag));
  }

  else if (ps2.ButtonReleased(PSB_R2) ) {
    flag = 1;
    ps2.read_gamepad();
    spd += 5;
    spd = constrain(spd, 0, 255);
    EEPROM.update(4, spd);            //Update the value of motor speed in EEPROM
    Serial.println("Speed Increased :  " + String(spd));
  }

  else if (ps2.ButtonReleased(PSB_L2)) {
    flag = 1;
    ps2.read_gamepad();
    spd -= 5;
    spd = constrain(spd, 0, 255);
    EEPROM.update(4, spd);            //Update the value of motor speed in EEPROM
    Serial.println("Speed Decreased : " + String(spd));
  }

  //Forward
  else if (ps2.Button(PSB_PAD_UP) && !(r_flag || l_flag)) {
    if (lcd_flag == 1) {
      last = millis();
      lcd_flag = 2;
    }
    
    forward_12();
    Serial.println("Forward");
  }

  //Right
  else if (ps2.Button(PSB_PAD_RIGHT)) {
    r_flag = 1;
    right_12();
    Serial.println("Right");
  }

  //Left
  else if (ps2.Button(PSB_PAD_LEFT) ) {
    left_12();
    l_flag = 1;

    Serial.println("Left");
  }
  
  //Backward
  else if (ps2.Button(PSB_PAD_DOWN) && !(r_flag || l_flag)) {
    backward_12();
    Serial.println("Down");
  }
  
  //Eight directions
  else if (( ps2.Analog(PSS_LX) != 128 ||  ps2.Analog(PSS_LY) != 127)) {
    eight_directions();
  }

  //Kiwi Drive (Active only when right joystick moved)
  else if (( ps2.Analog(PSS_RX) != 128 ||  ps2.Analog(PSS_RY) != 127)) {
    kiwi();
  }

  else {
    i = j = spd - 70;
    px = 0; py = 0;
    r_flag = 0;
    l_flag = 0;
    stop_motors();
    stop_arm();
    Serial.println("Stop");
  }

  //Throwing Logic

  //Arm forward
  if (ps2.Button(PSB_TRIANGLE) ) {
    digitalWrite(throw_D, HIGH);
    analogWrite(throw_P, 100);
    Serial.println("Arm Forward");
  }

  //Arm backward
  else if (ps2.Button(PSB_CIRCLE)) {
    Serial.println("Arm Backward");
    digitalWrite(throw_D, LOW);
    analogWrite(throw_P, 180);
  }

  //Piston1 open or close
  else if (ps2.ButtonReleased(PSB_CROSS)) {
    ps2.read_gamepad();
    Serial.println("Piston 1 Switching");
    count = ++count % 2;
    (count == 1) ? (piston1open()) : (piston1close());
  }

  //Piston2 open or close
  else if (ps2.ButtonReleased(PSB_SQUARE)) {
    ps2.read_gamepad();
    Serial.println("Piston 2 Switching");
    count1 = ++count1 % 2;
    (count1 == 1) ? (piston2open()) : (piston2close());
  }

  else {
    stop_arm();
    analogWrite(throw_P, 0);
  }
}

void waiting() {
  lcd.print("WAITING");
  Serial.println("Waiting");
  while (error) {
    error = ps2.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
    if (error)  delay(500);
  }
  pinMode(PS2_DAT, INPUT_PULLUP);
  lcd.clear();
  Serial.println("Connections Alright !");
}

