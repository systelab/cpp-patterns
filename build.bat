md build
cd build
conan install .. -s build_type=%1 -s compiler="Visual Studio" -s compiler.version=15 -s compiler.toolset=v141 -s arch=x86 -o gtest=1.10.0 --build=gtest
cmake .. -G "Visual Studio 15 2017" -A Win32 
msbuild Patterns.sln /p:Configuration=%1 /p:Platform="Win32" 
cd ..
