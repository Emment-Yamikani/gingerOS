#ifndef _FBTERM_H
#define _FBTERM_H

#include <stdint.h>
#include <fbterm/tinyfont.h>
#include <fbterm/vterm.h>

struct fbterm_ctx
{
    unsigned rows; /* Number of rows */
    unsigned cols; /* Number of cols */

    unsigned cr, cc; /* Cursor position */

    char *wallpaper;   /* Wallpaper buffer */
    char *textbuf;     /* Rendered text buffer */
    char *backbuf;     /* Back buffer for terminal */
    struct font *font; /* Font used */

    unsigned char op; /* Opacity 0-255 */

    uint32_t txt_fg;
    VTerm *vt;
    VTermScreen *screen;
};

void fbterm_set_cursor(struct fbterm_ctx *ctx, int cc, int cr);
size_t fbterm_write(struct fbterm_ctx *ctx, const char *buf, size_t size);
size_t fbterm_clear(struct fbterm_ctx *ctx);

#endif
