## REDOUBLER

REDOUBLER is a Random Number Generator based on Modular Entropy Multiplication. The device plugs
into a hosts's USB port, and ennumerates as a standard microphone. When the microphone is sampled it produces
white noise which contains a high proportion of random entropy. The digital data behind that white noise
is random numbers, and they can be recorded and used for any purpose that requires a non-deterministic entropy
source.

By ennumerating as a standard USB microphone (sound card with one input) REDOUBLER does not require drivers
on any major operating system. This simplifies developments, and reduces the "attack surfacce" that an
adversary can use to compromise security.

# Modular Entropy Modulation

Non-deterministic random number generators use various methods to gather entropy. Avalance noise from a
reverse-biased semiconductor junction is popular, but others include video of Lava Lamps, radios tuned 
away from stations, quantum effects, and radioactive decay events. Modular Entropy Modulation (MEM) is
a new method.

Invented by the author, Peter Allan, in the late 1990's and independantly by Bill Cox in the early 2010's,
MEM repeatedly compares a voltage with the midpoint of its range, then doubles either the voltage or excess
over the midpoint as appropriate, and stores the result. Depending on the comparison, either a '0' or a
'1' bit is output. The redoubler has two such generators operating simultaneously at 768,000 bps, for a
combined output of 1,536,000 bps. The bitstream has about 7.9 bits/byte of entropy, and is unwhitened,
leaving the host to apply a whitening filter if required.

As a circuit, the analog part of MEM looks like this
![Analog part of MEM Circuit](images/MEM_Circuit.png?raw=true "Circuit")
