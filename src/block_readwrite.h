#ifndef INCLUDE_GUARD_6cff8eb77848cf7a8030bdd9f431d0fa
#define INCLUDE_GUARD_6cff8eb77848cf7a8030bdd9f431d0fa

/* Summary
    In contrast to the difficulty of non-blocking operations on a blocking open-file (see https://cr.yp.to/unix/nonblock.html), the opposite is surprisingly easy -- doing blocking operations on a non-blocking open-file.

    The method boils down to an infinite loop of:
    * wait until ready (eg. poll(2))
    * attempt IO
    * if completed, break and return

    */

#include <sys/types.h>

int poll_fd(int fd, int events, int timeout);
    // - poll and return events
int block_poll_fd(int fd, int events);
    // return: poll_fd(fd, events, -1)

ssize_t block_read(int fd, void *buffer, size_t length);
    // - one successful read of up to length bytes
    // error: -1
    // return: number of bytes read

ssize_t block_write(int fd, void const *data, size_t length);
    // - write all length bytes
    // error: either -1 or less than length
    // return: number of bytes written
ssize_t block_write_some(int fd, void const *data, size_t length);
    // - one successful write of up to length bytes
    // error: -1
    // return: number of bytes written

#endif
