When plugged into a properly configured Linux machine the device will cause
a message at the end of the dmsg list:
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
