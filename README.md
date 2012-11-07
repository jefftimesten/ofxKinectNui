
## A Note from Jeff about this fork 

This fork of the ofxKinectNui addon by [sadmb](https://github.com/sadmb) was made for the Kinect Workshop 
at [Kitchen Table Coders](http://kitchentablecoders.com) on June 16, 2012. It is slightly simplified and doesn't use the ofxKinectNuiDrawTexture system set up in the newer versions of the addon.  Otherwise, it is identical.

### Requirements 

1. [Visual Studio 2010](http://www.microsoft.com/visualstudio/eng/downloads)  (Make sure to get 2010 and not 2012 -- there are still some compatibility problems!)
1. [Microsoft Kinect SDK, version 1.0+](http://www.microsoft.com/en-us/kinectforwindows/)
(Works with 1.5)  
1. [openFrameworks for VS2010](http://www.openframeworks.cc/download/)  

### Notes

1. To compile Kinect apps in Debug mode, you must install [SP1 for VisualStudio 2010](http://www.microsoft.com/en-us/download/details.aspx?id=23691)  (also works with Express edition)
[check out this stackOverflow thread for more info](http://stackoverflow.com/questions/10888391/link-fatal-error-lnk1123-failure-during-conversion-to-coff-file-invalid-or-c)  
1. This, in turn, causes a problem in addons\ofxOsc\src\ofxOscArg.h (which is used by some of the examples that use ofxOSC) line 76  
You can simply comment out `typedef long int32_t;` to fix it.
1. The project generator doesn't yet **fully** work with this addon. [I've submitted an issue to try to resolve this](https://github.com/ofZach/projectGeneratorSimple/issues/24), but I doubt it'll be fixed any time soon. In the mean time, open up one of the included examples, open the properties, make sure "Configuration: All Configurations" is selected, and then take a look at the following sections:
    1. C/C++ > Additional Include Directories
    1. Linker >  Additional Library Directories
    1. Linker > Input > Additional Dependencies

### Examples
1. 01_Inputs - This example simply shows the different types of data that you can get from the camera: RGB, depth, calibrated RGB (aligned to depth) player labels, and skeleton data
1.  02_RGB_Depth - This example shows how you can map RGB information onto the 

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

## Requirement
1: You must install Visual C++ 2010, openFrameworks and Kinect SDK 1.0 before using this sample.  
2: Place this to openframeworks addons folder.


