void lcd_scroll(char *scroll_string, uint8_t line, uint8_t &position)
{
  const uint8_t display_size = 16;
  char section[display_size+1]; // +1 for the null character
  
  if(position >= strlen(scroll_string)) position = 0;
  snprintf(section, display_size+1, &scroll_string[position]);
  if(strlen(section) < display_size)
    strncat(section, scroll_string, display_size-strlen(section));

  lcd.setCursor(0, line);
  lcd.print(section);

  position++;
}
