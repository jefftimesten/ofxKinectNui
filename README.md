
## A Note from Jeff about this fork 

This fork of the ofxKinectNui addon by sadmb was made for the Kinect Workshop 
at kitchentablecoders.com on June 16, 2012.  

### REQUIREMENTS:  

**Microsoft Kinect SDK, version 1.0+** 
http://www.microsoft.com/en-us/kinectforwindows/  
Works with 1.5 also  

**Visual Studio 2010**  
*Note:* to compile in Debug mode, you must install [SP1 for VisualStudio 2010](http://www.microsoft.com/en-us/download/details.aspx?id=23691)  (also works with Express edition)
[check out this stackOverflow thread for more info](http://stackoverflow.com/questions/10888391/link-fatal-error-lnk1123-failure-during-conversion-to-coff-file-invalid-or-c)
 
*WARNING:* This, in turn, causes a problem in addons\ofxOsc\src\ofxOscArg.h (which is used by some of the examples that use ofxOSC) line 76  
You can simply comment out "typedef long int32_t;" to fix it.


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


