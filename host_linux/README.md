# Linux Host Software

When plugged into a properly configured Linux machine the device will cause a message at the end of the dmesg list:
```
$ dmesg
[395858.273621] usb 1-1.2.2: new full-speed USB device number 15 using dwc_otg
[395858.383545] usb 1-1.2.2: New USB device found, idVendor=04b4, idProduct=c500
[395858.383582] usb 1-1.2.2: New USB device strings: Mfr=1, Product=12, SerialNumber=128
[395858.383598] usb 1-1.2.2: Product: REDOUBLER Random Number Generator
[395858.383614] usb 1-1.2.2: Manufacturer: Open Source Hardware Copyright (c) 2015 Peter Allan
[395858.383628] usb 1-1.2.2: SerialNumber: 1E0C08F0022E2400
```
It will also appear in the /dev/snd hierarchy, e.g.
```
$ ls -l /dev/snd/by-id
total 0
lrwxrwxrwx 1 root root 12 Mar  8 08:51 usb-Open_Source_Hardware_Copyright__c__2015_Peter_Allan_REDOUBLER_Random_Number_Generator_1E0C08F0022E2400-00 -> ../controlC1
```
Notice that it includes the unique serial number seen before, and is is
registered as "controlC1" or card #1. If there are other sound devices, or other
REDOUBLERs they will also appear here with a different card #.

The REDOUBLER should also be recognized by arecord:
```
$ arecord -l
**** List of CAPTURE Hardware Devices ****
card 1: Generat_1 [REDOUBLER Random Number Generat], device 0: USB Audio [USB Audio]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
```
Again, the REDOUBLER is listed as card 1.

To record some data from the redoubler we refer to it as hw:1,0 where the first
number is the card #. In this case
```
$ arecord -f dat -D hw:1,0 -d 10 > sample.wav
```	
If arecord complains about "overruns" (eg. Raspbery Pi) then you may need an
option like "--buffer-size=192000". The first 44 bytes of the wav file are the
file header. After that there will be 961 bytes of mostly zeroes, which are the
REDOUBLER's buffers before they are filled with random bits. If you want only
random bits try
```
$ arecord -f dat -D hw:1,0 -d 1 | head -c +1005 > sample.bin
```
To listen to the white noise from the REDOUBLER, turn your speaker volume low
and try
```
$ arecord -f dat -D hw:1,0 | aplay
```	
Press Ctrl-C to end it.

To continuously record ALL the data produced by a REDOUBLER try something like
```
$ arecord -f dat -D hw:1,0 -q --max-file-time 600 --buffer-size=192000 --use-strftime /tank/temp/%Y/%m/%d/redoubler1-%H-%M-%S.wav &
```
All the files will have the 44-byte WAV header, but only the first will have the
empty buffer. About 6TB of space will be required for a year of data. Use
"disown" before closing the terminal. Other than disk space, resource use will be
low.

To make things easier, some utilities are included in this directory. They need the Debian (Ubuntu, Raspian) package
```
$ sudo apt-get install libasound2-dev
```
Then
```
$ make
$ sudo make install
$ make clean
```
That creates the utility **doubledown** that pipes REDOUBLER data to stdout, e.g.
```
$ doubledown -l
Available REDOUBLERs:	Card #    	Serial Number       
                    	2         	1E0C08F0022E2400
$ doubledown -c1 -k1 | xxd
0000000: 47bd f192 c35c cc4c 982b 5332 b471 b303  G....\.L.+S2.q..
0000010: 0913 6f96 f9fa 03ea e0c6 4ab0 c11d 252a  ..o.......J...%*
etc.
```
It also creates the filters **oddbits** and **evenbits** which select the bits from just one or the other MEM generator on the REDOUBLER. Putting it together
```
$ doubledown -c1 -k1024 | oddbits | ent
Entropy = 7.907466 bits per byte.

Optimum compression would reduce the size
of this 524800 byte file by 1 percent.

Chi square distribution for 524800 samples is 53993.07, and randomly
would exceed this value 0.01 percent of the times.

Arithmetic mean value of data bytes is 126.9712 (127.5 = random).
Monte Carlo value for Pi is 3.271305422 (error 4.13 percent).
Serial correlation coefficient is -0.005054 (totally uncorrelated = 0.0).
```
