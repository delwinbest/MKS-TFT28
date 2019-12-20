#include "includes.h"


Sd2Card card;
SdVolume volume;
File root;

extern LCD lcd;
extern URTouch myTouch;

void SDCard::init(){
  lcd.lcd_console_log("SDCard Init..");
  if (!card.init(SPI_HALF_SPEED, SDCARD_CS)) {
    lcd.lcd_console_log("SDCard init failed.");
    delay(1000);
    return;
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
    delay(1000);
    return;
  }
  //lcd.lcd_console_log("Clusters: " + String(volume.clusterCount()));
  //lcd.lcd_console_log("Blocks x Cluster: " + String(volume.blocksPerCluster()));
  //lcd.lcd_console_log("Total Blocks: " + String(volume.blocksPerCluster() * volume.clusterCount()));

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  lcd.lcd_console_log("Volume type is: FAT" + String(volume.fatType(), DEC));
  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
  //lcd.lcd_console_log("Volume size (Kb): " + String(volumesize));
  volumesize /= 1024;
  lcd.lcd_console_log("Volume size (Mb): " + String(volumesize));
  //lcd.lcd_console_log("Volume size (Gb): " + String((float)volumesize / 1024.0));
  SD.begin(SDCARD_CS);
  root = SD.open("/");
}

void SDCard::printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      lcd.lcd_console_log("EOF");
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      lcd.lcd_console_log(" ");
    }
    lcd.lcd_console_log(entry.name());
    if (entry.isDirectory()) {
      //lcd.lcd_console_log("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      //lcd.lcd_console_log("\t\t");
      lcd.lcd_console_log(String(entry.size(), DEC));
    }
    entry.close();
  }
}
