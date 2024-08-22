/**@(#)Read wanted bytes from file descriptor fd into buffer buf, allowing for
 * @(#)not all data being available in one go - e.g., if fd is attached to
 * @(#)a pipe
 */

#include <stdio.h>

int     pipe_read(FILE * stream, char *buf, int wanted)
{
    int     nread;

    while (wanted > 0)
    {
	if ((nread = fread(buf, 1, wanted, stream)) == -1)
	    return -1;
	wanted -= nread;
	buf += nread;
    }
    return 0;
}
