#ifndef SDL_TFT_H
#define SDL_TFT_H

#include "SDL.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include <errno.h>

#include "driver/gpio.h"
#include "esp_heap_caps.h"
#include "spi_lcd.h"

#define SDL_INIT_VIDEO 1

#define SDL_SWSURFACE 1
#define SDL_HWSURFACE 2

#define SDL_HWPALETTE 1
#define SDL_FULLSCREEN 1


typedef struct{
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 unused;
} SDL_Color;

typedef struct{
  int ncolors;
  SDL_Color *colors;
} SDL_Palette;

typedef struct SDL_PixelFormat {
  SDL_Palette *palette;
  Uint8  BitsPerPixel;
  Uint8  BytesPerPixel;
  Uint8  Rloss, Gloss, Bloss, Aloss;
  Uint8  Rshift, Gshift, Bshift, Ashift;
  Uint32 Rmask, Gmask, Bmask, Amask;
  Uint32 colorkey;
  Uint8  alpha;
} SDL_PixelFormat;

typedef struct{
  Sint16 x, y;
  Uint16 w, h;
} SDL_Rect;

typedef struct SDL_Surface {
        Uint32 flags;                           /* Read-only */
        SDL_PixelFormat *format;                /* Read-only */
        int w, h;                               /* Read-only */
        Uint16 pitch;                           /* Read-only */
        void *pixels;                           /* Read-write */

        /* clipping information */
        SDL_Rect clip_rect;                     /* Read-only */

        /* Reference count -- used when freeing surface */
        int refcount;                           /* Read-mostly */

	/* This structure also contains private fields not shown here */
} SDL_Surface;

typedef struct{
  Uint32 hw_available:1;
  Uint32 wm_available:1;
  Uint32 blit_hw:1;
  Uint32 blit_hw_CC:1;
  Uint32 blit_hw_A:1;
  Uint32 blit_sw:1;
  Uint32 blit_sw_CC:1;
  Uint32 blit_sw_A:1;
  Uint32 blit_fill;
  Uint32 video_mem;
  SDL_PixelFormat *vfmt;
} SDL_VideoInfo;

typedef int SDLKey;

void SDL_WM_SetCaption(const char *title, const char *icon);
void SDL_Delay(Uint32 ms);
Uint32 SDL_WasInit(Uint32 flags);
int SDL_Init(Uint32 flags);
int SDL_InitSubSystem(Uint32 flags);
char *SDL_GetError(void);
int SDL_FillRect(SDL_Surface *dst, SDL_Rect *dstrect, Uint32 color);
SDL_Surface *SDL_CreateRGBSurface(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);
char *SDL_GetKeyName(SDLKey key);
Uint32 SDL_GetTicks(void);
SDL_Keymod SDL_GetModState(void);
void SDL_Quit(void);
SDL_Surface *SDL_GetVideoSurface(void);
Uint32 SDL_MapRGB(SDL_PixelFormat *fmt, Uint8 r, Uint8 g, Uint8 b);
int SDL_SetColors(SDL_Surface *surface, SDL_Color *colors, int firstcolor, int ncolors);
SDL_Surface *SDL_SetVideoMode(int width, int height, int bpp, Uint32 flags);
void SDL_FreeSurface(SDL_Surface *surface);
void SDL_QuitSubSystem(Uint32 flags);
int SDL_Flip(SDL_Surface *screen);
int SDL_VideoModeOK(int width, int height, int bpp, Uint32 flags);
int SDL_LockSurface(SDL_Surface *surface);
void SDL_UnlockSurface(SDL_Surface* surface);
void SDL_UpdateRect(SDL_Surface *screen, Sint32 x, Sint32 y, Sint32 w, Sint32 h);
SDL_Rect **SDL_ListModes(SDL_PixelFormat *format, Uint32 flags);

typedef unsigned char  JE_byte;
//extern JE_byte ** allocateTwoDimenArrayOnHeapUsingMalloc(int row, int col);
JE_byte *** allocateTwoDimenArrayOnHeapUsingMalloc(int row, int col);

#endif
