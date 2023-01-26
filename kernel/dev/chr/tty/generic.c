#include <sys/system.h>
#include <dev/tty.h>
#include <sys/_signal.h>
#include <sys/proc.h>
#include <arch/i386/cpu.h>
#include <bits/errno.h>
#include <sys/sched.h> // XXX
#include <lib/string.h>
#include <mm/kalloc.h>
#include <printk.h>

long tty_master_write(struct tty *tty, size_t size, void *buf)
{
    long ret = size;

    /* Process Slave Input */
    if (tty->tios.c_lflag & ICANON) /* Canonical mode */
    {
        int echo = tty->tios.c_lflag & ECHO;
        char *c = buf;

        while (size)
        {
            if (*c == tty->tios.c_cc[VEOF])
            {
            }
            else if (*c == tty->tios.c_cc[VEOL])
            {
            }
            else if (*c == tty->tios.c_cc[VERASE] || *c == '\b')
            {
                if (tty->pos > 0)
                {
                    --tty->pos;
                    tty->cook[tty->pos] = '\0';

                    if (tty->tios.c_lflag & ECHOE)
                        tty_slave_write(tty, 3, "\b \b");
                }

                goto skip_echo;
            }
            else if (*c == tty->tios.c_cc[VINTR])
            {
                proc_lock(proc);
                pgroup_lock(proc->pgroup);
                signal_pgrp_send(tty->fg, SIGINT, NULL);
                proc_unlock(proc);
                pgroup_unlock(proc->pgroup);
                char cc[] = {'^', *c + '@', '\n'};
                tty_slave_write(tty, 3, cc);
                goto skip_echo;
            }
            else if (*c == tty->tios.c_cc[VKILL])
            {
            }
            else if (*c == tty->tios.c_cc[VQUIT])
            {
            }
            else if (*c == tty->tios.c_cc[VSTART])
            {
            }
            else if (*c == tty->tios.c_cc[VSUSP])
            {
            }
            else if (*c == '\n' || (*c == '\r' && (tty->tios.c_iflag & ICRNL)))
            {
                tty->cook[tty->pos++] = '\n';

                if (echo)
                    tty_slave_write(tty, 1, "\n");

                tty->slave_write(tty, tty->cook, tty->pos);

                tty->pos = 0;
                ret = ret - size + 1;
                return ret;
            }
            else
            {
                tty->cook[tty->pos++] = *c;
            }

            if (echo)
            {
                if (*c < ' ')
                { /* Non-printable */
                    char cc[] = {'^', *c + '@'};
                    tty_slave_write(tty, 2, cc);
                }
                else
                {
                    tty_slave_write(tty, 1, c);
                }
            }
        skip_echo:
            ++c;
            --size;
        }
    }
    else
    {
        return tty->slave_write(tty, buf, size);
    }

    return ret;
}

int tty_ioctl(struct tty *tty, int request, void *argp)
{
    switch (request)
    {
    case TCGETS:
        memcpy(argp, &tty->tios, sizeof(struct termios));
        break;
    case TCSETS:
        memcpy(&tty->tios, argp, sizeof(struct termios));
        break;
    case TIOCGPGRP:
        *(pid_t *)argp = tty->fg->pg_id;
        break;
    case TIOCSPGRP:
        /* XXX */
        tty->fg = proc->pgroup;
        panic("%s:%d: TIOCSPGRP\n", __FILE__, __LINE__);
        break;
    case TIOCGWINSZ:
        memcpy(argp, &tty->ws, sizeof(struct winsize));
        break;
    case TIOCSWINSZ:
        memcpy(&tty->ws, argp, sizeof(struct winsize));
        break;
    default:
        return -EINVAL;
    }
    return 0;
}

long tty_slave_write(struct tty *tty, size_t size, void *buf)
{

    if (tty->tios.c_oflag & OPOST)
    {
        size_t written;
        for (written = 0; written < size; ++written)
        {
            char c = ((char *)buf)[written];
            if (c == '\n' && (tty->tios.c_oflag & ONLCR))
            {
                tty->master_write(tty, "\r\n", 2);
            }
            else if (c == '\r' && (tty->tios.c_oflag & OCRNL))
            {
                tty->master_write(tty, "\n", 1);
            }
            else if (c == '\r' && (tty->tios.c_oflag & ONOCR))
            {
                /* TODO */
            }
            else if (c == '\n' && (tty->tios.c_oflag & ONLRET))
            {
                /* TODO */
            }
            else
            {
                tty->master_write(tty, &c, 1);
            }
        }
        return written;
    }
    else
    {
        return tty->master_write(tty, buf, size);
    }
}

int tty_new(proc_t *proc, size_t buf_size, ttyio master, ttyio slave, void *p, struct tty **ref)
{
    struct tty *tty = NULL;

    if (!(tty = kmalloc(sizeof(struct tty))))
        return -ENOMEM;
    memset(tty, 0, sizeof(struct tty));
    if (!buf_size)
        buf_size = TTY_BUF_SIZE;

    tty->cook = kmalloc(buf_size);
    tty->pos = 0;

    /* Defaults */

    tty->tios.c_iflag = ICRNL | IXON;
    tty->tios.c_oflag = OPOST | ONLCR;
    tty->tios.c_lflag = ISIG | ICANON | ECHO | ECHOE | ECHOK;

    tty->tios.c_cc[VMIN] = 1;
    tty->tios.c_cc[VTIME] = 0;
    tty->tios.c_cc[VEOF] = CTRL('D');
    tty->tios.c_cc[VEOL] = CTRL('L');
    tty->tios.c_cc[VINTR] = CTRL('C'); /* ^C */
    tty->tios.c_cc[VKILL] = CTRL('U'); /* ^U */
    tty->tios.c_cc[VSUSP] = CTRL('Z'); /* ^Z */
    tty->tios.c_cc[VERASE] = CTRL('H');
    tty->tios.c_cc[VSTART] = CTRL('Q'); /* ^Q */
    tty->tios.c_cc[VQUIT] = CTRL('\\'); /* ^\ */

    tty->ws.ws_row = 24;
    tty->ws.ws_col = 80;

    tty->fg = proc->pgroup;

    /* Interface */
    tty->master_write = master;
    tty->slave_write = slave;
    tty->p = p;

    if (ref)
        *ref = tty;
    return 0;
}

int tty_free(struct tty *tty)
{
    kfree(tty->cook);
    kfree(tty);
    return 0;
}