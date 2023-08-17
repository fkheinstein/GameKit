@rem rmdir  build\build.windows /s /q

echo ######################################################## Start

set START_TIME=%time%
echo ########################################################
echo Build This Application
echo ########################################################
echo




mkdir  build
cd build
mkdir  build.windows
cd build.windows

del CMakeCache.txt

echo ******
@rem cmake -G"Visual Studio 15 2017 Win64" ../../   -DCMAKE_BUILD_TYPE=Debug
cmake -G "Visual Studio 16 2019"   ../../   -DCMAKE_BUILD_TYPE=Release 

echo ######################################################## END

echo Start Time: %START_TIME%
echo End Time: %TIME%

pause
