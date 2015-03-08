# REDOUBLER

REDOUBLER is a Random Number Generator based on Modular Entropy Multiplication. It is Open Source Hardware. The device plugs into a host's USB port, and ennumerates as a standard microphone. When the microphone is sampled it produces white noise which contains a high proportion of random entropy. The digital data behind that white noise is random numbers, and they can be recorded and used for any purpose that requires a non-deterministic entropy source.

![REDOUBLERs, Shucked and Not](images/REDOUBLERs.jpg?raw=true "REDOUBLERs")

By ennumerating as a standard USB microphone (sound card with one input) REDOUBLER does not require drivers on any major operating system. This simplifies development, and reduces the "attack surfacce" that an adversary can use to compromise security. Moreover, the data paths used by microphones are highly optimized for efficiency.

### Modular Entropy Modulation

Non-deterministic random number generators use various methods to gather entropy. Avalance noise from a reverse-biased semiconductor junction is popular, but others include video of Lava Lamps, radios tuned away from stations, quantum effects, digital logic race conditions, and radioactive decay events. Modular Entropy Modulation (MEM) is a new method.

Invented by the author, Peter Allan, in the late 1990's and independantly by Bill Cox in the early 2010's, MEM repeatedly compares a voltage with the midpoint of its range, then doubles either the voltage or excess over the midpoint as appropriate, and stores the result. Depending on the comparison, either a '0' or a '1' bit is output.

As a circuit, the analog part of MEM looks like this

![Analog part of MEM Circuit](images/MEM_Circuit.png?raw=true "Circuit")

The Track & Holds are where the voltages are stored, one for the source voltage and one for the result. The Comarators compare the stored voltages with the midpoint of their range, and produce a digital output based on the result. The Opamps double the input voltage and, depending on the result of the comparison, shift it by the voltage range. The clocks q and qp are symmetric and non-overlapping and control the pace of the circuit. In the REDOUBLER, all of the components except the resistors are reconfigurable analog blocks on a Cypress Semiconductor PSoC 5LP chip. It has two such generators operating simultaneously at 768,000 bps, for a combined output of 1,536,000 bps. The bitstream has about 7.9 bits/byte of entropy, and is unwhitened, leaving the host to apply a whitening filter if required. Here is one second worth of data as an image (click twice to see it full-scale).

![One Second of Data](images/one_sec.png?raw=true "One Second")

Modular Entropy Multiplication has advantages over all other methods because it is simultaeously simple, efficient, fast, and robust. It uses common components, used within their specified ranges. It is ammenable to implementation on silicon, and has proven resistant to external electrical influence, even when unshielded. Bill and I hope that REDOUBLER and his Infinite Noise Multiplier are just the beginning for this method, and we have disclaimed any patent rights to the technology.
