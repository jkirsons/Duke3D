
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "game.h"

void dukeTask(void *pvParameters)
{
    char *argv[]={"", NULL};
    main(1, argv);
}


void app_main(void)
{
	xTaskCreatePinnedToCore(&dukeTask, "dukeTask", 28000, NULL, 5, NULL, 0);
}
