void Read_button() {

  if (ps2.Button(PSB_START)) {
    ps2.read_gamepad();
    delay(30);
    return;
  }

  if (ps2.Button(PSB_R1)) {
    run_motor(m1c,  0.40 * spd, m2c,  0.40 * spd, m3c,  0.40 * spd);
    Serial.println("Clockwise");
  }

  else if (ps2.Button(PSB_L1)) {
    run_motor(m1ac,  0.40 * spd, m2ac,  0.40 * spd, m3ac, 0.40 * spd);
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




  //forward
  else if (ps2.Button(PSB_PAD_UP) && !(r_flag || l_flag)) {
    if (lcd_flag == 1) {
      last = millis();
      lcd_flag = 2;
    }
    forward_12();
    //    check++;
    //    if (check == 4)
    //      check = 1;
    //    forward_12();
    //    //run_motor(m1c, 0, m2ac, 180, m3c, 121);
    Serial.println("Forward");
  }
  //right
  else if (ps2.Button(PSB_PAD_RIGHT)) {
    r_flag = 1;
    right_12();
    //    if (check == 1)
    //      right_1();
    //    else if (check == 2)
    //      right_2();
    //    else if (check == 3)
    //      right_3();
    //
    //    Serial.println("Left");
    Serial.println("Right");
  }
  //left
  else if (ps2.Button(PSB_PAD_LEFT) ) {
    left_12();
    l_flag = 1;
   
    Serial.println("Left");
  }
  //backward
  else if (ps2.Button(PSB_PAD_DOWN) && !(r_flag || l_flag)) {
    backward_12();
    Serial.println("Down");
  }
  //eight directions
  else if (( ps2.Analog(PSS_LX) != 128 ||  ps2.Analog(PSS_LY) != 127)) {
    eight_directions();
  }

  //Kiwi Drive (Active only when right joystick moved)
  else if (( ps2.Analog(PSS_RX) != 128 ||  ps2.Analog(PSS_RY) != 127)) {
    kiwi();
    //    run_motor(md1, w1, md2, w2, md3, w3);
  }

  else {
    i = j = spd - 70;
    px = 0; py = 0;
    r_flag = 0;
    l_flag = 0;
    stop_motor();
    stop_();
    Serial.println("stop");
  }

  //  ps2.read_gamepad();
  //  delay(50);

  //Throwing Logic

  //arm forward
  if (ps2.Button(PSB_TRIANGLE) ) {
    digitalWrite(throw_D1, HIGH);
    analogWrite(throw_P1, 80);
    Serial.println("Triangle");
  }

  //Arm backward
  else if (ps2.Button(PSB_CIRCLE)) {
    //Serial.println(digitalRead(ir1));
    Serial.println("Circle");
    digitalWrite(throw_D1, LOW);
    analogWrite(throw_P1, 180);
    //      if (digitalRead(ir1) == 0) {
    //        piston1close();
    //      }
    ir1_flag = 1;
  }

  //Piston1 open or close
  else if (ps2.ButtonReleased(PSB_CROSS)) {
    ps2.read_gamepad();
    Serial.println("Cross");

    ir1_flag = 0;
    count = ++count % 2;
    (count == 1) ? (piston1open()) : (piston1close());
  }

  //Piston2 open or close
  else if (ps2.ButtonReleased(PSB_SQUARE)) {
    ps2.read_gamepad();
    Serial.println("Square");
    count1 = ++count1 % 2;
    (count1 == 1) ? (piston2open()) : (piston2close());
  }

  else {
    stop_();
    ir1_flag = 0;
    analogWrite(throw_P1, 0);
  }
}

void waiting() {
  lcd.print("WAITING");
  Serial.println("Waiting");
  while (error) {
    error = ps2.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
    if (error)
      delay(500);
  }
  pinMode(PS2_DAT, INPUT_PULLUP);
  lcd.clear();
  Serial.println("Connections Alright !");
}
