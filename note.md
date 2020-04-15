# video

macoview from sourceforge did not working, use that :
git@github.com:gdbinit/MachOView.git
https://github.com/gdbinit/MachOView/issues/18



## Link from the video

### first link https://developer.apple.com/library/archive/documentation/Performance/Conceptual/CodeFootprint/Articles/MachOOverview.html
Mach-o is the native executable format of binaries in osx.
It determine the order in which the code and the data in the binary are read
into the memory.

This file is organized into segments, each segment contain one or more sections.
Code and data of different type goes into section.

Segment always start by a page boundary, but section are not necessarily page-aligned.
The size of a segment is equal to the number of bytes of all sections it contain
and rounded up to the next virtual memory page. = getpagesize.

Convention :
The segment and section are named according to their intended use.
The convention for segment name is __TEXT,
The convention for section name is __text.

There are several possible segment, but only two of them ar of interest
in relation to performance: __TEXT & __DATA.


to do : 
make the fatbinary working,
relaunch test with all program








anwserthepublic pour avoir ce que les gens search.
utiliser google alert with feedly


