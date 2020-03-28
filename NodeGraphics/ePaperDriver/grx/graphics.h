#pragma once
#include <stdio.h>
//for memset
#include <string.h>
#include "graphic_types.h"
#include "../Driver/ePaper.h"
#include "../fonts/resources.h"


#define CHARACTER_SPACING_PIXELS 2 //number of pixels between characters

void gfxInit(void);
void gfxPlaceBitmap(const bitmap_t *bitmap, uint16_t pos_x, uint16_t pos_y);
void gfxWriteText(const font_t *font, uint16_t pos_x, uint16_t pos_y, const char *text);
uint16_t gfxGetTextWidth(const font_t *font, const char *text);
uint8_t gfxGetGlyphWidth(const font_t *font, char c);
uint8_t gfxGetGlyphHeight(const font_t *font);
const glyph_t * gfxGetGlyph(const font_t *font, char c);
