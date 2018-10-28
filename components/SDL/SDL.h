#ifndef SDL_h_
#define SDL_h_
#include <stdint.h>
#include <stdio.h>
#include "SDL_keycode.h"
#include "SDL_stdinc.h"
#include "SDL_endian.h"
#include "SDL_audio.h"
#include "SDL_TFT.h"

typedef int SDLMod;
typedef int SDL_Joystick;

#define SDLK_FIRST 0
#define SDLK_LAST 1024

#define SDLK_KP4 SDLK_LEFT
#define SDLK_KP6 SDLK_RIGHT
#define SDLK_KP8 SDLK_UP
#define SDLK_KP2 SDLK_DOWN
#define SDLK_KP5 SDLK_BACKSLASH
#define SDLK_KP0 SDLK_RETURN
#define SDLK_KP9 SDLK_PAGEUP
#define SDLK_KP3 SDLK_PAGEDOWN

#define AUDIO_S16SYS 16
#define AUDIO_S8 8

#define SDL_BUTTON_LEFT 0
#define SDL_BUTTON_RIGHT 1
#define SDL_BUTTON_MIDDLE 2
#define SDLK_NUMLOCK 999
#define SDLK_SCROLLOCK 1000

#define SDL_strlcpy strlcpy


#endif
