void lcd_func() {

  if (flag) {
    lcd.begin(20, 4);
    lcd.clear();
    flag = 0;
  }
  lcd.setCursor(0, 0);
  lcd.print("SPEED : " + String(spd));   //Print Speed to LCD
}
