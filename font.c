/*
 * Copyright (c) 2000-2019 Devin Smith <devin@devinsmith.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <windows.h>

#include <string.h>

#include "font.h"

static struct xpFont g_system_font;

void
xp_font_init(void)
{
  NONCLIENTMETRICS ncm;
  HDC hDC;

  ncm.cbSize = sizeof(NONCLIENTMETRICS);
  SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS),
    &ncm, 0);

  strncpy(g_system_font.faceName, ncm.lfMenuFont.lfFaceName,
      sizeof(g_system_font.faceName) - 1);
  g_system_font.faceName[sizeof(g_system_font.faceName) - 1] = '\0';

  // Convert logical height to point size.
  hDC = CreateCompatibleDC(NULL);
  g_system_font.height = MulDiv(-ncm.lfMenuFont.lfHeight, 72,
      GetDeviceCaps(hDC, LOGPIXELSY));
  DeleteDC(hDC);
}

const struct xpFont *
get_default_font(void)
{
  return &g_system_font;
}
