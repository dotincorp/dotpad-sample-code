# C# Sample Code for DotPadSDK-1.4.0


## Overview
* An Sample Applicaton using the DotPadSDK from [dotpad-sdk-guide](https://github.com/dotincorp/dotpad-sdk-guide)
* Can perform controls on a Dot Pad connected via Serial Port

## Install
* Unzip the Japanese dictionary file used by Dotjeom Station. (DemoApp/bin/Debug/ipadic.zip)
* Unzip the table file used in liblouis Station. (DemoApp/bin/Debug/tables.zip)
* liblouis table environment variable settings
```
  setx LOUIS_TABLEPATH "D:\DemoApp\tables" /M
  echo %LOUIS_TABLEPATH%
```

## Build
1. Run DevmoApp.sin
2. Visual Studio > Build > DemoApp Build
3. Run DemoApp/bin/Debug/DemoApp.exe