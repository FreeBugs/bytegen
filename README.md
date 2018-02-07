bytegen
===

A unix dd style byte sequence generator.


What is it for?
===============
Unix style operating systems provide serveral special devices such as
/dev/zero as a source for writing sequences to files or devices.
This, however, lacks the possibility to use values like 0xFF.

bytegen generates a sequence of values specified to standard out.
This can be written to a file or device using the dd utility.

Compile
=======

bytegen requires CMake and the boost library to compile.
To build bytegen simply run this command from the source directory:

    cmake --build . --target bytegen


Usage
=====

bytegen requires the following parameters:

    --value arg           Required. The value to generate (e.g. 0xFF)
    --bs arg              Block size in bytes.
    --count arg           Number of blocks to generate.

Example
=======

To write 100Mb in 4k blocks of repeating 0x40 (the @ character) to /dev/null:

    bytegen --value 0x40 --bs 4096 --count 25600 | dd of=/dev/null bs=4096
    
should return something like:

````
25600+0 records in
25600+0 records out
104857600 bytes transferred in 0.083346 secs (1258101629 bytes/sec)

