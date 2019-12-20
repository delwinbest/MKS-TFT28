#ifndef __sdcard_H
#define __sdcard_H

#include <SD.h>

class SDCard {
    public:
        Sd2Card card;
        SdVolume volume;
        File root;
        void init();
        void printDirectory(File dir, int numTabs);
};


#endif 