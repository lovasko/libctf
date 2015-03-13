libctf
======

libctf is a C99 BSD-licensed implementation of the second version of the 
Compact C Type Format - CTF.  Initially developed as a part of the Google
Summer of Code 2014, supported and mentored by the FreeBSD Project. Code is
written with multiple platforms in mind and can be used in BSD, illumos and
Linux worlds.

CTF describes a reduced set of debugging data similar to DWARF or stabs. The
data can be found in the `.SUNW_ctf` ELF section of the executable, optionally
compressed. The format focuses mainly on the C types used in the corresponding
binary file with a minor focus on the symbol table. 

Principal objective of the format is to shrink the data size as much as
possible so that it could be included in a production environment. Therefore
the data is saved in a binary form with bit-level attention. To satisfy the
size reduction ambition even more, a concept of parent-child relationship was
introduced, where the parent contains the common type information and the child
references this data.

The library, it's practical usage and implementation, and musings on possible
usage are topics of my on-going [bachelor thesis](https://github.com/lovasko/bc_thesis).

Current status
--------------
 * :white_check_mark: reading and parsing the CTF data
 * :white_check_mark: user-space
 * :white_check_mark: kernel-space
 * :white_check_mark: manipulation API

Goals
-----
 * writing
 * unit testing
 * integration testing
 * code coverage measuring during tests
 * ARM support
 * MIPS support
 * Linux support
 * illumos support

Related projects
----------------
 * [ctfdump](https://github.com/lovasko/ctfdump)
 * [ctfstats](https://github.com/lovasko/ctfstats)
 * [ctfquery](https://github.com/lovasko/ctfquery)
 * [ddb_ctf](https://github.com/lovasko/ddb_ctf)
 * :soon: [ctfconvert](https://github.com/lovasko/ctfconvert)
 * :soon: [ctfmerge](https://github.com/lovasko/ctfmerge)

Authors
------
 * Daniel Lovasko lovasko@freebsd.org

Thanks
------
 * George Neville-Neil
 * Pedro Giffuni
 * Robert Mustacchi
 * John-Mark Gurney


More information
----------------
For more information please refer to files [LICENSE](LICENSE),
[AUTHORS.md](AUTHORS.md), [THANKS.md](THANKS.md), [INSTALL.md](INSTALL.md), 
[TUTORIAL.md](TUTORIAL.md) and [PERF.md](PERF.md).
Automatically generated Doxygen documentation can be found [here](doc/doxygen).

