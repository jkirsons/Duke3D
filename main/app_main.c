
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "game.h"
#include "assert.h"


void dukeTask(void *pvParameters)
{
    char *argv[]={"duke3d", "/nm", NULL};
    main(2, argv);

    // no sound
//    char *argv[]={"duke3d", "/ns", "/nm", NULL};
//    main(3, argv);
   
}


void app_main(void)
{
	xTaskCreatePinnedToCore(&dukeTask, "dukeTask", 32000, NULL, 5, NULL, 0/*tskNO_AFFINITY*/);
}
