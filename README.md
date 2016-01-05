#Mashberry
MashBerry is a Raspberry PI based beer-brewing controller. It is designed to automate the mashing-process for the homebrewer. MashBerry can be operated via a Web-interface or via a Display and an IR-remote. The temperature is controlled using a PID-controller, the temperature-measurement is done with a PT1000 or a Dallas 18B20. For power-control an external Solid-State-Relay is used.

##How to build
MashBerry depends on Qt for Embedded Linux. Before you can build MashBerry, you have to set up a cross-compiler toolchain and compile Qt from source.

###1. Set up cross-compiler toolchain
Clone the latest revision of raspberrypi tools to */opt/raspberry/*:  
`sudo mkdir /opt/raspberry`  
`cd /opt/raspberry`  
`sudo git clone --depth 1 https://github.com/raspberrypi/tools.git`
  
###2. Add the toolchain to the PATH
Add the following directory to the PATH environment variable:   
`/opt/raspberry/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin`

###3. Download the Qt Everywhere 4.8 source files
Download *qt-everywhere-opensource-src-4.8.6.zip* from http://download.qt.io/archive/qt/4.8/4.8.6/ and unzip it wherever you want.
 
###4. Create Qt Everywhere mkspecs
Navigate to the mkspecs folder (inside the Qt Everywhere folder).  
Copy the *linux-arm-gnueabi-g++* folder and name it *linux-arm-gnueabihf-g++*.

Then edit the *qmake.conf* file in the copied folder and replace all the tools' names according to those in */opt/raspberry/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin*.
Basically you have to replace all occurrences of *linux-arm-gnueabi-* with *linux-arm-gnueabihf-*.

###5. Configure and install Qt for Embedded Linux
Make sure your toolchain is accessible from your current shell session (maybe you have to restart your shell, so that the updated PATH is applied).

Run the configure script in the Qt Everywhere folder:  
`./configure -embedded arm -xplatform linux-arm-gnueabihf-g++ -little-endian -opensource -qt-kbd-tty -qt-kbd-linuxinput -qt-mouse-pc -qt-mouse-linuxinput -no-qt3support -no-opengl -no-cups -silent`

The *-xplatform* option must be set to the name of the mkspec you created in step 4.  
You can list all of the configuration system's options by typing:  
`./configure -embedded -help`

Finally, build and install the library:  
`make`  
`sudo make install`

It will be installed to the default directory:  
`/usr/local/Trolltech/`

###6. Add an alias for qmake (optional)
If you're lazy and don't want to type such a long path over and over again, you may want to define an alias for qmake.

Just add the following line to your *.bashrc*:  
`alias qmake-embedded='/usr/local/Trolltech/QtEmbedded-4.8.6-arm/bin/qmake`

*Hint:* This is especially useful, if you have already installed a non-embedded-version of qmake, in which case you shouldn't add the QtEmbedded binaries to your PATH.

###7. Build MashBerry
In your MashBerry folder, run the QtEmbedded version of qmake:  
`qmake-embedded`

This should create a Makefile which can be used to build MashBerry:  
`make`

Finally, you can copy the MashBerry executable and the Qt for Embedded Linux library (`/usr/local/Trolltech/QtEmbedded-4.8.6-arm/`) to your raspberry pi.