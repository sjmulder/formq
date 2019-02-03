/* formq.c - Copyright (c) 2019, Sijmen J. Mulder (see LICENSE.md) */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <err.h>

static int
unhex(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'f')
		return 10 + c - 'a';
	if (c >= 'A' && c <= 'F')
		return 10 + c - 'A';

	errx(1, "not a hex character: %c", c);
}

static bool
skip_through(char *needle)
{
	static char buf[128];

	size_t len;
	size_t ntoread;
	char *chr;

	if ((len = strlen(needle)) > sizeof(buf))
		errx(1, "needle too long");

	ntoread = len;
	while (1) {
		if (fread(buf+len-ntoread, 1, ntoread, stdin) != ntoread)
			return false;
		if (memcmp(buf, needle, len) == 0)
			return true;
		if ((chr = memchr(buf, '&', len))) {
			memmove(buf, chr+1, len - (chr-buf-1));
			ntoread = chr+1-buf;
		} else
			ntoread = len;
	}

	return true;
}

static bool
stream_key(void)
{
	int c;

	while ((c = getchar()) != EOF) {
		putchar(c);
		if (c == '=')
			return true;
	}

	return false;
}

static void
stream_value(void)
{
	int c;
	char hex[2];

	while ((c = getchar()) != EOF && c != '&') {
		if (c == '+')
			putchar(' ');
		else if (c != '%')
			putchar(c);
		else {
			if (fread(hex, 1, 2, stdin) != 2)
				errx(1, "incomplete escape sequence");
			putchar((unhex(hex[0]) << 4) + unhex(hex[1]));
		}
	}
}

int
main(int argc, char **argv)
{
	char query[128];
	bool nolf = false;
	int c;

	while ((c = getopt(argc, argv, "n")) != -1) {
		if (c == 'n')
			nolf = true;
		else
			return 1;
	}

	argc -= optind;
	argv += optind;

	if (argc == 0) {
		while (stream_key()) {
			stream_value();
			putchar('\n');
		}
	} else if (argc == 1) {
		if (snprintf(query, sizeof(query), "%s=", argv[0]) >=
		    (int)sizeof(query))
		    	errx(1, "query too long");
		if (skip_through(query))
			stream_value();
		if (!nolf)
			putchar('\n');
	} else
		errx(1, "usage: formq <key>");

	if (ferror(stdin))
		err(1, "<stdin>");

	return 0;
}
