/**@(#)File handling utilities
 */

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>
#include <tina/file.h>
#include <tina/file_gen.h>

/* Extract directory from pathname, in place. If no directory, return
 * "." */
char   *dirname(char *directory, char *pathname)
{
    char   *slash;

    (void) strncpy(directory, pathname, MAXPATHLEN);
    if ((slash = strrchr(directory, '/')))
	/* Pathname has directory (so truncate at last slash) */
	*slash = '\0';
    else
	/* Pathname is just base, so return "." */
	(void) strcpy(directory, ".");
    return directory;
}

/* Get basename & directory from an environment variable. Returns
 * pointer to basename. If environment variable NOT found, sets
 * basename & directory from default pathname supplied by the user.
 * Usage: if HOME=/disk1/tnew {char base[MAXPATHLEN],dir[MAXPATHLEN];
 * environ_pathname_get(dir, base, "HOME", "/zaphod/john");} Sets dir
 * to "/disk1" & base to "tnew". But environ_pathname_get(dir, base,
 * "ZOME", "/zaphod/john"); Sets dir to "/zaphod" & base to "john". */
char   *environ_pathname_get(char *dir, char *base, char *env_var, char *def_pathname)
{
    char   *slash;
    char   *pathname = getenv(env_var);

    /* If environment variable not found, use default (supplied by
     * user) */
    if (pathname == NULL)
	pathname = def_pathname;

    (void) strncpy(dir, pathname, MAXPATHLEN);

    if ((slash = strrchr(dir, '/')))
    {
	/* Pathname includes directory */
	*slash = '\0';
	(void) strncpy(base, slash + 1, MAXPATHLEN);
    } else
    {
	/* Pathname is just base */
	(void) strncpy(base, pathname, MAXPATHLEN);
	*dir = '\0';
    }
    return (base);
}


/* Is FILE readable? (Strips leading & trailing spaces from pathname.)  */
Bool    file_readable(char *pathname)
{
    Bool    readable = false;
    struct stat buf;
    extern char *strip_spaces(char *string);

    /* File found? */
    if (stat(strip_spaces(pathname), &buf) == 0)
    {
#ifndef _PCC
	mode_t  mode = buf.st_mode;
	if (S_ISREG(mode))
	/* Regular file? */
	{
	    extern uid_t geteuid(void);
	    extern uid_t getegid(void);
	    int     euid = geteuid();	/* effective user id */
	    int     egid = getegid();	/* effective group id */

	    /* user is superuser? */
	    if (euid == 0)
		readable = true;
	    /* file owned by me? */
	    else if (buf.st_uid == euid)
	    {
		/* readable by owner */
		if (mode & S_IRUSR)
		    readable = true;
	    }
	    /* file in same group as me (but not owner) */
	    else if (buf.st_gid == egid)
	    {
		/* readable by group */
		if (mode & S_IRGRP)
		    readable = true;
	    } else
	    {
		/* file neither owned by nor in same group as me */
		/* readable by others? */
		if (mode & S_IROTH)
		    readable = true;
	    }
	}
    }
#else
        unsigned short mode = buf.st_mode;
	if (mode&S_IFMT == S_IFREG)
	/* Regular file? */
	{
            readable = true;
	}
    }
#endif


    return readable;
}


/* Remove all extensions from a pathname. Done in place. */
char   *strip_extensions(char *string)
{
    char   *dot;
    char   *slash = strrchr(string, '/');	/* if no /, slash is
						 * NULL, so address of
						 * any dot found is >
						 * slash */

    while ((dot = strrchr(string, '.')) > slash)
	*dot = '\0';

    return (string);
}


/* Remove leading & trailing spaces (actually all non-visible
 * characters) */
char   *strip_spaces(char *string)
{
    char   *first = string;
    char   *last = string + strlen(string);
    char   *result = string;
    int     chr;

    /* Terminate string after last non-blank (point to last non-blank) */
    while ((last > string) && (chr = *--last) && !isalnum(chr) && !ispunct(chr))
	*last = '\0';

    /* Point to 1st non-blank in string (if string "" *str is '\0') */
    while ((chr = *first) && !isalnum(chr) && !ispunct(chr))
	first++;

    /* Copy stripped string to result (excluding terminating \0) */
    while ((*result++ = *first++));

    /* Terminate result */
    *result = '\0';

    return (string);
}


/* Get exit status of shell command */
Bool    system_exit_status(char *shell_command)
{
    return (Bool) ((system(shell_command) >> 8) == 0);
}
