formq
=====
Command line URL encoded form parser.

... | **formq** [**-n**] [_key_]

Description
-----------
Reads a URL encoded form from standard input and prints the decoded value of
the given _key_. No trailing newline character is printed if **-n** is set.

If no _key_ is given, all keys and values are printed, one per line.

Examples
--------
Decode a form:

    $ echo 'From=Dennis&Message=Hello%2C+World%21' | formq
    From=Dennis
    Message=Hello, World!

Extract just the _Message_ key:

    $ echo 'From=Dennis&Message=Hello%2C+World%21' | formq Message
    Hello, World!

Running
-------
To compile, install and uninstall from source:

    make
    make install   [DESTDIR=] [PREFIX=/usr/local] [MANPREFIX=PREFIX/man]
    make uninstall [DESTDIR=] [PREFIX=/usr/local] [MANPREFIX=PREFIX/man]

Author
------
Sijmen J. Mulder (<ik@sjmulder.nl>)
