@echo off
REM Use "Developer command prompt for VS 2022" shell
REM Install: https://developer.microsoft.com/en-gb/windows/downloads/windows-sdk/
REM Install depot_tools and add it to the %PATH%
REM Install python3. if you have no python3 binary just rename the python v3 version exe to python3 

SET DEPOT_TOOLS_WIN_TOOLCHAIN=0

REM make sure it uses our repo, it does the job of "python3 scripts/bootstrap.py" but that has its chrome url hardcoded
call gclient config git@github.com:1SpatialGroupLtd/angle.git

REM Generates some winui bindings
call python scripts/winappsdk_setup.py

REM Sets up the required build tools and libs
REM This will take ages!
call gclient sync

REM finicky cmd string path escaping ..
gn gen out/Release --args="angle_is_winappsdk=true is_debug=false is_component_build=false is_clang=false winappsdk_dir=\"C:/Development/angle/third_party/WindowsAppSDK\""

REM build it
ninja -j 10 -k1 out/Release