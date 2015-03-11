TARGETS = doubledown oddbits evenbits whiten
BINDIR = /usr/local/bin
all: $(TARGETS)

doubledown: doubledown.c
	gcc -Wall doubledown.c -lasound -o doubledown

oddbits: oddbits.c
	gcc -Wall oddbits.c -o oddbits

evenbits: oddbits
	ln -f oddbits evenbits

whiten: whiten.c chacha.o
	gcc -Wall whiten.c chacha.o -o whiten

chacha.o: chacha.c
	gcc -Wall -c chacha.c

install: all
	install -m 0755 $(TARGETS) $(BINDIR)
.PHONY: install

clean:
	-rm -f *.o
	-rm -f $(TARGETS)
	-rm -f *~

