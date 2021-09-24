// Console input and output.
// Input is from the keyboard or serial port.
// Output is written to the screen and serial port.

#include <stdarg.h>

#include "types.h"
#include "defs.h"
#include "param.h"
#include "traps.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "x86.h"
#include "vga.h"

static struct {
  int offset;
} disp;

int
displayioctl(struct file *f, int param, int value)
{
  int index, r, g, b;

  if (param == 1) {
    // set the the monitor to vga mode
    vgaMode13();
    return 0;
  } else if (param == 2) { // set palatte color
    b = value & 0xff;
    value = value >> 8;
    g = value & 0xff;
    value = value >> 8;
    r = value & 0xff;
    value = value >> 8;
    index = value & 0xff;

    vgaSetPalette(index, r, g, b);
    return 0;
  } else {
    cprintf("Got unknown display ioctl request. %d = %d\n", param, value);
    return -1;
  }
}

int
displaywrite(struct file *f, char *buf, int n)
{
  // cprintf("In displaywrite()");
  memcpy(KERNBASE + 0xa0000 + disp.offset, buf, n);
  disp.offset += n;
  return n; 
}

  void
displayinit(void)
{
  devsw[DISPLAY].write = displaywrite;
}
