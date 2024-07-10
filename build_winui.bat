@echo off
REM Use "Developer command prompt for VS 2022" shell
REM Install: https://developer.microsoft.com/en-gb/windows/downloads/windows-sdk/
REM Install depot_tools and add it to the %PATH%
REM Install python3. if you have no python3 binary just rename the python v3 version exe to python3 

REM make sure it uses our repo
REM call gclient config git@github.com:1SpatialGroupLtd/angle.git

REM Clone our repo, set up the required build tools, download our repo and setup everything, it will take ages!
REM gclient sync

SET DEPOT_TOOLS_WIN_TOOLCHAIN=0

REM Generates some winui bindings
call python scripts/winappsdk_setup.py

REM finicky cmd string path escaping ..
gn gen out/Release --args="angle_is_winappsdk=true is_debug=false is_component_build=false is_clang=false winappsdk_dir=\"%cd%/third_party/WindowsAppSDK\""

REM build it
autoninja -C out/Release