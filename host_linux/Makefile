TARGETS = doubledown oddbits evenbits
BINDIR = /usr/local/bin
all: $(TARGETS)

doubledown: doubledown.c
	gcc -Wall doubledown.c -lasound -o doubledown

oddbits: oddbits.c
	gcc -Wall oddbits.c -o oddbits

evenbits: oddbits
	ln -f oddbits evenbits

install: all
	install -m 0755 $(TARGETS) $(BINDIR)
.PHONY: install

clean:
	-rm -f *.o
	-rm -f $(TARGETS)
	-rm -f *~

