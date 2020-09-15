**Copyright © 2020  Philip Lindh** 
**All rights reserved**

###### Shell Script 
```
The shell script is located in "projects" as "FileScript.sh" and may do the following:
1. Change the specified *file extension* by the users choosing
2. *Replace* occurances
3. Append *copyright* to all .h and .cpp files
```

###### CMake Guide
[The main file may be located here](projects/RealTimeEngine/code/RealTimeEngine.cpp)

```cmake
> mkdir build
> cd build
> cmake -DCMAKE_BUILD_TYPE=Release ./projects/RealTimeEngine/
```