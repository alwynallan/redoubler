# REDOUBLER

REDOUBLER is a Random Number Generator based on Modular Entropy Multiplication. It is Open Source Hardware. The device plugs into a host's USB port, and ennumerates as a standard microphone. When the microphone is sampled it produces white noise which contains a high proportion of random entropy. The digital data behind that white noise is random numbers, and they can be recorded and used for any purpose that requires a non-deterministic entropy source.

![REDOUBLERs, Shucked and Not](images/REDOUBLERs.jpg?raw=true "REDOUBLERs")

By ennumerating as a standard USB microphone (sound card with one input) REDOUBLER does not require drivers on any major operating system. This simplifies development, and reduces the "attack surfacce" that an adversary can use to compromise security. Moreover, the data paths used by microphones are highly optimized for efficiency.

### Modular Entropy Modulation

Non-deterministic random number generators use various methods to gather entropy. Avalance noise from a reverse-biased semiconductor junction is popular, but others include video of Lava Lamps, radios tuned away from stations, quantum effects, digital logic race conditions, and radioactive decay events. Modular Entropy Modulation (MEM) is a new method.

Invented by the author, [Peter Allan], in the late 1990's and independantly by Bill Cox in the early 2010's, MEM repeatedly compares a voltage with the midpoint of its range, then doubles either the voltage or excess over the midpoint as appropriate, and stores the result. Depending on the comparison, either a '0' or a '1' bit is output.

As a circuit, the analog part of MEM looks like this

![Analog part of MEM Circuit](images/MEM_Circuit.png?raw=true "Circuit")

The Track and Holds store the voltages, one for the source voltage and one for the result. The Comarators compare the stored voltages with the midpoint of their range, and produce a digital output based on the result. The Opamps double the input voltage and, depending on the result of the comparison, shift it by the voltage range. The clocks q and qp are symmetric and non-overlapping and control the pace of the circuit. When recorded over time, the two voltages have characteristic time traces like this.

![MEM Traces](images/Traces.png?raw=true "Traces")

In the REDOUBLER, all of the components except the resistors are reconfigurable analog blocks on a Cypress Semiconductor PSoC 5LP chip. It has two such generators operating simultaneously at 768,000 bps, for a combined output of 1,536,000 bps. The bitstream has about 7.9 bits/byte of entropy, and is unwhitened, leaving the host to apply a whitening filter if required. Here is one second worth of data as an image (click twice to see it full-scale).

![One Second of Data](images/one_sec.png?raw=true "One Second")

Modular Entropy Multiplication has advantages over all other methods because it is simultaeously simple, efficient, fast, and robust. It uses common components, used within their specified ranges. It is ammenable to implementation on silicon, and has proven resistant to external electrical influence, even when unshielded. Bill and I hope that REDOUBLER and his [Infinite Noise TRNG] are just the beginning for this method, and we have disclaimed any patent rights to the technology.

### The Circuit

The REDOUBLER circuit is designed in the latest free version of Cadsoft Eagle and files are in the [circuit](circuit) branch of this repository.

![Schematic](images/Schematic.png?raw=true "Schematic")

The PSoC chip contains both reconfigurable analog components and digital logic, so the only components unique to REDOUBLER are the eight resistors at top-right.

![Board](images/Board.png?raw=true "Board")

A Bill Of Materials is also disclosed. Boards are available from [OSH Park].

### The Firmware

The firmware for REDOUBLER is written in the highly itegrated and free-to-use [Cypress PSoC Creator] development environment. The source code is in the [psoc_creator_firmware](psoc_creator_firmware) branch of this repository. I highly recommend this toolchain and microcontroller product line. The current state of the firmware source is efficient and reliable, but a litle rough looking. The USB audio fuctions were culled from an [example project], and much of that code remains in comments.

Once the firmware is built, it can be programmed onto a REDOUBLER using the $90 [MiniProg3](http://www.cypress.com/?rID=38154) or the left portion of the $10 [CY8CKIT-059](http://www.cypress.com/?rid=108038). [Pogo Pins] are useful for connecting to the 5 pads on the REDOUBLER board.

### Host Software

[Peter Allan]: mailto:alwynallan@gmail.com
[Infinite Noise TRNG]: https://github.com/waywardgeek/infnoise
[Cypress PSoC Creator]: http://www.cypress.com/psoccreator/
[Pogo Pins]: https://www.sparkfun.com/products/9174
[example project]: http://www.element14.com/community/thread/28830/l/psoc-4-pioneer-kit-community-project102-usb-audio-using-the-psoc-5lp?displayFullThread=true
[OSH park]: https://oshpark.com/shared_projects/GZnEjhlQ
