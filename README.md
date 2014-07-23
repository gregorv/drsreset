drsreset
========

A small utility to reset DRS4 Evaluation Boards (or connected USB Devices with a specific VID/PID).

Installation
------------

The libusb-1.0 library is required to compile drsreset. CMake is used to generate the Makefiles.

In a nutshell, execute the following commands to download, compile and install drsreset

    git clone https://github.com/gregorv/drsreset.git
    mkdir drsreset/build
    cd drsreset/build
    cmake ..
    make
    sudo make install


How To Use
----------

Whenever your DRS4 Evaluation Board decides to be unavailable, just type `drsreset` and try again!

Licensing
---------

drsreset ist distributed under the GPL3 license.
