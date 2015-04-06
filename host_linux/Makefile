TARGETS = doubledown oddbits evenbits xorbits runs bang24 whiten
BINDIR = /usr/local/bin
all: $(TARGETS)

doubledown: doubledown.c
	gcc -Wall doubledown.c -lasound -o doubledown

oddbits: oddbits.c
	gcc -Wall oddbits.c -o oddbits

evenbits: oddbits
	ln -f oddbits evenbits

xorbits: oddbits
	ln -f oddbits xorbits

whiten: whiten.c chacha.o
	gcc -Wall whiten.c chacha.o -o whiten

chacha.o: chacha.c
	gcc -Wall -c chacha.c

runs: runs.c chi_sq2.o
	gcc -Wall runs.c chi_sq2.o -lm -o runs

bang24: bang24.c
	gcc -Wall bang24.c -o bang24
  
ch_sq2.o: chi_sq2.c
	gcc -Wall -c ch_sq2.c

install: all
	install -m 0755 $(TARGETS) $(BINDIR)
.PHONY: install

clean:
	-rm -f *.o
	-rm -f $(TARGETS)
	-rm -f *~
