#include "SDL_event.h"
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

typedef struct {
	int gpio;
	SDL_Scancode scancode;
    SDL_Keycode keycode;
} GPIOKeyMap;

int keyMode = 1;
//Mappings from buttons to keys
static const GPIOKeyMap keymap[2][6]={{
// Game    
	{CONFIG_HW_BUTTON_PIN_NUM_UP, SDL_SCANCODE_UP, SDLK_UP},
	{CONFIG_HW_BUTTON_PIN_NUM_DOWN, SDL_SCANCODE_DOWN, SDLK_DOWN},
	{CONFIG_HW_BUTTON_PIN_NUM_LEFT, SDL_SCANCODE_LEFT, SDLK_LEFT},
	{CONFIG_HW_BUTTON_PIN_NUM_RIGHT, SDL_SCANCODE_RIGHT, SDLK_RIGHT},

	{CONFIG_HW_BUTTON_PIN_NUM_BUTTON1, SDL_SCANCODE_LCTRL, SDLK_LCTRL},			
	{CONFIG_HW_BUTTON_PIN_NUM_BUTTON2, SDL_SCANCODE_SPACE, SDLK_SPACE},		
},
// Menu
{
	{CONFIG_HW_BUTTON_PIN_NUM_UP, SDL_SCANCODE_UP, SDLK_UP},
	{CONFIG_HW_BUTTON_PIN_NUM_DOWN, SDL_SCANCODE_DOWN, SDLK_DOWN},
	{CONFIG_HW_BUTTON_PIN_NUM_LEFT, SDL_SCANCODE_LEFT, SDLK_LEFT},
	{CONFIG_HW_BUTTON_PIN_NUM_RIGHT, SDL_SCANCODE_RIGHT, SDLK_RIGHT},

	{CONFIG_HW_BUTTON_PIN_NUM_BUTTON2, SDL_SCANCODE_ESCAPE, SDLK_ESCAPE},			
	{CONFIG_HW_BUTTON_PIN_NUM_BUTTON1, SDL_SCANCODE_SPACE, SDLK_SPACE},		
}};

typedef struct {
    Uint32 type;        /**< ::SDL_KEYDOWN or ::SDL_KEYUP */
    SDL_Scancode scancode;
    SDL_Scancode keycode;
} GPIOEvent;

static xQueueHandle gpio_evt_queue = NULL;

int SDL_PollEvent(SDL_Event * event)
{
    if(gpio_evt_queue == NULL )
        inputInit();

    GPIOEvent ev;
    if(xQueueReceive(gpio_evt_queue, &ev, 0)) {
        event->key.keysym.sym = ev.keycode;
        event->key.keysym.scancode = ev.scancode;
        event->key.type = ev.type;
        event->key.keysym.mod = 0;
        event->key.state = ev.type == SDL_KEYDOWN ? SDL_PRESSED : SDL_RELEASED;     /**< ::SDL_PRESSED or ::SDL_RELEASED */ 
        return 1;
    }
    return 0;
}

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    GPIOEvent event;
    event.type = gpio_get_level(gpio_num) == 0 ? SDL_KEYDOWN : SDL_KEYUP;
    for (int i=0; i < NELEMS(keymap[keyMode]); i++)
        if(keymap[keyMode][i].gpio == gpio_num)
        {
            event.scancode = keymap[keyMode][i].scancode;
            event.keycode = keymap[keyMode][i].keycode;
            xQueueSendFromISR(gpio_evt_queue, &event, NULL);
        }
}
/*
void gpioTask(void *arg) {
    uint32_t io_num;
	int level;
    for(;;) {
        if(xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
        }
    }
}
*/
void inputInit()
{
	gpio_config_t io_conf;
    io_conf.pull_down_en = 0;

    //interrupt of rising edge
    io_conf.intr_type = GPIO_INTR_ANYEDGE;

    //bit mask of the pins, use GPIO... here
	for (int i=0; i < NELEMS(keymap[0]); i++)
    	if(i==0)
			io_conf.pin_bit_mask = (1ULL<<keymap[0][i].gpio);
		else
			io_conf.pin_bit_mask |= (1ULL<<keymap[0][i].gpio);

	io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    //create a queue to handle gpio event from isr
    gpio_evt_queue = xQueueCreate(10, sizeof(GPIOEvent));
    //start gpio task
	//xTaskCreatePinnedToCore(&gpioTask, "GPIO", 1500, NULL, 7, NULL, 0);

    //install gpio isr service
    gpio_install_isr_service(ESP_INTR_FLAG_SHARED);

    //hook isr handler
	for (int i=0; i < NELEMS(keymap[0]); i++)
    	gpio_isr_handler_add(keymap[0][i].gpio, gpio_isr_handler, (void*) keymap[0][i].gpio);

	printf("keyboard: GPIO task created.\n");
}