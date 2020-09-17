**Copyright © 2020  Philip Lindh**\
**All rights reserved**

## CMake Guide
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ./projects/RealTimeEngine/
```
###### Arguments
**-i**: Prints out the amount of total processors supported by the CPU\
**-f**: Followed by an integer, performs heavy computation on X forks by provided integer value\
**-t**: Followed by an integer, performs heavy computation on X threads by provided integer value\

## Shell Script 
```
The shell script is located in "projects" as "FileScript.sh" and may do the following:
Change the specified file extension by the users choosing
Replace occurances
Append copyright to all .h and .cpp files
```