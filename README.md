# Microsoft Kinect SDK 1.0 addon for openFrameworks

## License
built by sadmb  
facebook: sadmb  
twitter: @sadmb  
mail: sadam@sadmb.com

MIT license  
http://ja.wikipedia.org/wiki/MIT_License

## Disclaimer
Users must take full responsibility while using this software.  
We will not be liable for any loss or damage caused by this program.

## Requirements 

1. [Visual Studio 2012](http://www.microsoft.com/visualstudio/eng/downloads)  
1. [Microsoft Kinect SDK, version 1.0+](http://www.microsoft.com/en-us/kinectforwindows/)
(Works with 1.5)  
1. [openFrameworks for VS2012](http://www.openframeworks.cc/download/)  


-----


# About this fork 


This fork of the ofxKinectNui addon by [sadmb](https://github.com/sadmb) was made by [jefftimesten](https://github.com/jefftimesten) for the Kinect Workshop 
at [Kitchen Table Coders](http://kitchentablecoders.com) on June 16, 2012. It is slightly simplified and doesn't use the ofxKinectNuiDrawTexture system set up in the newer versions of the addon.  Otherwise, it is identical.



## projectGenerator Help

If you are using the project generator to create your ofxKinectNui projects, you may notice that your projects don't compile and throw errors about "Cannot open include file "NuiApi.h", etc. This is because there are a few additional settings that you must add to the Visual Studio project after generating that the projectGenerator currently can't add for you.

So, once you have generated a project that includes ofxKinectNui:

- Right click on the name of your solution in the Solution Explorer in Visual studio and select "Properties" at the bottom.
- Ensure that "All Configurations" is selected in the Configuration drop down on the top left

- Under **VC++ Directories > All Options**
  - Add the following to *Include Directories*
  
    ```
    $(KINECTSDK10_DIR)inc
    $(KINECT_TOOLKIT_DIR)inc
    ```
        
  - Add the following to *Library Directories*
  
    ```
    $(KINECTSDK10_DIR)\lib\x86
    ````
    
- Under **Linker > All Options**
    
  - add the following under *Additional Dependencies*
  
		````
		Kinect10.lib
		WinMM.lib
		amstrmid.lib
		msdmo.lib
		dmoguids.lib
		````

- Lastly, notice in the examples that you must add the following line as the first line in main.cpp:

		#include "ofxKinectNui.h"


## Examples

If you have any suggestions for more helpful examples, please submit an issue and I'll see what I can do!

### 01_Inputs
This example simply shows the different types of data that you can get from the camera: RGB, depth, calibrated RGB (aligned to depth) player labels, and skeleton data

![Inputs Screenshot](http://4u.jeffcrouse.info/of/kinect/01_Inputs.png)

### 02_RGB_Depth
This example shows how you can map RGB information onto the depth data  

![Depth Screenshot](http://4u.jeffcrouse.info/of/kinect/02_RGB_Depth.png)

### 03_Record_Playback
One truly awesome feature of this addon is the ability to record and playback data. This is extremely useful when testing applications.

### 04_SendSkeleton and 05_ReceiveSkeleton
These examples show how you can send skeleton data using the ofxOSC addon that comes with openFrameworks  

![Send and Receive Screenshot](http://4u.jeffcrouse.info/of/kinect/04_05_Send_Receive.png)

### 06_ValidSkeleton
Sometimes the Kinect will send questionable skeleton data, especially as a person is entering or leaving the interaction area.  This example shows a strategy for filtering out "invalid" skeletons  

###07_Painting
This example shows a simple application that uses the Kinect to "paint" circles into a 3D space. It also uses the filtering method described above.  

![Painting Screenshot](http://4u.jeffcrouse.info/of/kinect/07_Painting.png)


