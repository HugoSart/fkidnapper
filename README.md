# INTRODUCTION
This is a simple program that I wrote to test my hacking skills. <br>
This program is capable of encrypt/decrypt an entire folder recursivaly with a symbolical (very weak) simetric encryption algorithm.

# BUILD
This program should compile and run on any operation system without any problems.<br>
For example, to compile the source code using g++ on Linux, go to the source folder ("fkidnapper/src") and type:
```
g++ -c fkidnapper.cpp -o fkidnapper
```

# USAGE
With the executable in hands, type:<br>
```
fkidnapper <MODE> <FOLDER_NAME>
```
Where <MODE> is the operation mode ("kidnap" for encryption or "rescue" for decryption) and <FOLDER_NAME> is the folder name to be encrypted recursivaly.

