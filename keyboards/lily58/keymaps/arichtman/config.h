/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define SSD1306OLED
#define OLED_SCROLL_TIMEOUT 1000
#define OLED_DISABLE_TIMEOUT
#define OLED_CUSTOM_TIMEOUT 10000
#define OLED_FONT_H "lib/glcdfont.c"

#define USE_SERIAL_PD2

#define PERMISSIVE_HOLD
#define AUTO_SHIFT_TIMEOUT 170
#define GRAVE_ESC_CTRL_OVERRIDE
#define DYNAMIC_MACRO_NO_NESTING

#define ALT_TAB_TIMER 700

#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 500
#define TAP_CODE_DELAY 10 //required to stop tap_code from triggering multiple times

#ifdef TAPPING_TERM
#undef TAPPING_TERM
#define TAPPING_TERM 150
#endif

//No keycodes using this yet...
#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 5000
