# Sample code for using iOS SDK 2.2.0

## Directory
```
├── DemoApp
│   ├── DotPadDemoApp
│   ├── Framekworks
│   │   ├── BrailleEngine
│   │   ├── DotPadFrameworks.framework
│   └── DotPadDemoApp.xcodeproj
└── README.md
```

## Execution Order
1. Download the source. (dotpad-sample-code/iOS/2.2.0)  
2. Run DemoApp/DotPadDemoApp.xcodeproj.
3. Connect your device (iPhone, iPad) to your MacBook.
4. In xcode, specify the target as the connected device and Build.  
    ![Xcode](images/xcode.png)    

## Demo app screen
- dotpad 320
  ![Screen DotPad-320](images/screen-320.png)
  ![Device DotPad-320](images/device-320.png)  
- km2-20
  ![Screen Km2-20](images/screen-20.png)  
  ![Device km2-20](images/device-20.png)  

## Error Resolution
* Module not found error  
  - message : Could not find module 'DotPadFrameworks' for target 'arm64-apple-ios-simulator'   
  - resolution : In Xcode, you need to set the target to the actual device, not the emulator.  
