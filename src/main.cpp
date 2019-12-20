#include "includes.h"



LCD lcd;
EEPROM eeprom;
URTouch  myTouch(PIN_SPI1_SCK , TOUCH_CS, PIN_SPI1_MOSI,PIN_SPI1_MISO, TOUCH_DI);
EEPROMConfig eeprom_config;

Sd2Card card;
SdVolume volume;
SdFile root;
int data_address=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  //TX=PA9,RX=PA10
  Serial.println("Booting");
  BUZZER_Init();
  // Setup the LCD
  lcd.start_lcd();
  lcd.lcd_console_log("Booting...");
  lcd.lcd_console_log("LCD Register Read Test...");
  // serialprint_lcd_registers();
  lcd.lcdprint_lcd_registers();
  //Touch
  lcd.lcd_console_log("URTouch Init...");
  myTouch.InitTouch(1);
  myTouch.setPrecision(PREC_MEDIUM);
  lcd.lcd_console_log("Load EEPROM Config..");
  eeprom.init();
  eeprom_config.loadConfig();
  lcd.lcd_console_log("Config Ver: " + String(eeprom_config.settings.config_version));
  lcd.lcd_console_log("a: " + String(eeprom_config.settings.a));
  lcd.lcd_console_log("b: " + String(eeprom_config.settings.b));
  
  if (!card.init(SPI_HALF_SPEED, SDCARD_CS)) {
    lcd.lcd_console_log("initialization failed. Things to check:");
    lcd.lcd_console_log("* is a card inserted?");
    lcd.lcd_console_log("* is your wiring correct?");
    lcd.lcd_console_log("* did you change the chipSelect pin to match your shield or module?");
    while (1);
  } else {
    lcd.lcd_console_log("Wiring is correct and a card is present.");
  }

    lcd.lcd_console_log("Card type:");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      lcd.lcd_console_log("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      lcd.lcd_console_log("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      lcd.lcd_console_log("SDHC");
      break;
    default:
      lcd.lcd_console_log("Unknown");
  }

  if (!volume.init(card)) {
    lcd.lcd_console_log("Could not find FAT16/FAT32 partition.");
    while (1);
  }
  delay(500);
  lcd.consoleLine = 1;
  lcd.lcd_console_log("Clusters: " + String(volume.clusterCount()));
  lcd.lcd_console_log("Blocks x Cluster: " + String(volume.blocksPerCluster()));
  lcd.lcd_console_log("Total Blocks: " + String(volume.blocksPerCluster() * volume.clusterCount()));

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  lcd.lcd_console_log("Volume type is: FAT" + String(volume.fatType(), DEC));
  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
  lcd.lcd_console_log("Volume size (Kb): " + String(volumesize));
  volumesize /= 1024;
  lcd.lcd_console_log("Volume size (Mb): " + String(volumesize));
  lcd.lcd_console_log("Volume size (Gb): " + String((float)volumesize / 1024.0));
  lcd.lcd_console_log("End Setup");
  lcd.consoleLine = 1;
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  
  if(myTouch.dataAvailable()){
    myTouch.read();
    lcd.lcd_console_log("X " + String(myTouch.getX()) + " Y " + String(myTouch.getX()));
  }

}