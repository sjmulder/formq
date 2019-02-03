DESTDIR   ?=
PREFIX    ?= /usr/local
MANPREFIX ?= $(PREFIX)/man

CFLAGS += -Wall -Wextra

all: formq

install: formq
	install -d $(DESTDIR)$(PREFIX)/bin $(DESTDIR)$(MANPREFIX)/man1
	install -m755 formq   $(DESTDIR)$(PREFIX)/bin/
	install -m755 formq.1 $(DESTDIR)$(MANPREFIX)/man1/

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/formq
	rm -f $(DESTDIR)$(MANPREFIX)/man1/formq.1

clean:
	rm -f formq

.PHONY: all install uninstall clean
