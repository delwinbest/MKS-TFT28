#ifndef _MYFATFS_H_
#define _MYFATFS_H_

#include "stdbool.h"

#ifdef __cplusplus
extern "C" {
#endif

bool mountSDCard(void);
bool mountUDisk(void);
bool scanPrintFilesFatFs(void);

#ifdef __cplusplus
}
#endif

#endif 
