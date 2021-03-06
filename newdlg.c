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

#include <winsock2.h>
#include <windows.h>

#include "cfg.h"
#include "opennakenres.h"
#include "network.h"
#include "newdlg.h"

static INT_PTR CALLBACK
NewDlg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  char servername[150];  /* Server name */
  struct new_dlg *dlg;

  dlg = (struct new_dlg *)GetProp(hwnd, "DLG_CTX");

  switch(msg) {
  case WM_INITDIALOG:
    SetProp(hwnd, "DLG_CTX", (HANDLE)lParam);
    SetDlgItemText(hwnd, IDN_NAME, cfg.nickname);
    SetDlgItemText(hwnd, IDN_SERVER, cfg.server);
    return 1;
    break;
  case WM_CLOSE:
    EndDialog(hwnd,0);
    return 1;
  case WM_COMMAND:
    switch (LOWORD(wParam)) {
    case IDCANCEL:
      EndDialog(hwnd,1);
      return 1;
    case IDCONNECT:
      if (!GetDlgItemText(hwnd,IDN_SERVER, servername, sizeof(servername))) {
        MessageBox(hwnd, "Please enter a server name", "OpenNaken Chat",
            MB_OK | MB_ICONERROR);
        break;
      }
      if (!GetDlgItemText(hwnd, IDN_NAME, dlg->username,
          sizeof(dlg->username))) {
        MessageBox(hwnd, "Please enter a user name", "OpenNaken Chat",
            MB_OK | MB_ICONERROR);
        break;
      }
      EndDialog(hwnd, IDOK);
      net_resolv(dlg->net, servername);
      break;
    }
    break;
  }
  return 0;
}

void new_dlg_show(struct new_dlg *dlg)
{
  DialogBoxParam(dlg->hInst, MAKEINTRESOURCE(IDD_NEW), dlg->parent,
      NewDlg, (LPARAM)dlg);
}

