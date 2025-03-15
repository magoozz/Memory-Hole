prog=test

ldflags:=-lreadline -lncurses

include ../GNUmakefile

try: $(objs) libdeq.so
	gcc -o -g $@ $(objs) $(ldflags) -L. -ldeq -Wl,-rpath=.

trytest: try
	Test/run

test: $(prog)
	Test/run