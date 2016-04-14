96Board library test files

There are 3 files here, they all do exactly the same thing which is to
turn on/off a GPIO pin when a different GPIO pin is toggled.  GPIO-A is 
the pin to be toggled and GPIO-C is the pin that changes state when GPIO-A
is toggled.  They do it in slightly different ways using different librarys
to activate the GPIO pins.  

The libraries used are: 
96BoardsGPIO
libsoc
mraa

They are all avalible on github.

The test files are:

AC-ledGPIO.c
AC-ledSOC.c
AC-ledMRAA.cpp

All three files are under the MIT license.

AC-ledGPIO. uses the 96BoardsGPIO library and the libsoc library.  Both 
must be installed for this sample program to compile and link.

$ gcc AC-ledGPIO.c -o AC-ledGPIO -lsoc -l96BoardsGPIO<Enter>
$ sudo ./AC_ledGPIO<Enter>

AC-ledSOC.c uses the libsoc library only, and it must be installed for
this sample program to compile and link.

$ gcc AC-ledSOC.c -o AC-ledSOC -lsoc<Enter>
$ sudo ./AC-ledSOC<Enter>

AC-ledMRAA.cpp uses the Intel MRAA c++ library, and it must be installed
for this sample program to compile and link. 

$ g++ AC-ledMRAA.cpp -o AC-ledMRAA -lmraa<Enter>
$ sudo ./AC-ledMRAA<Enter>


If you have a 96Board (Dragonboard 410, Hikey or something else) and you 
have either the Arrow LinkerSprite mezzinane board or you have a 
Seeed Studios Sensor Starter Kit mezzinane board, you can hook up the 
touch switch to GPIO-A and the led to GPIO-C and all of these programs 
should toggle on and off the led when you touch the touch switch.

