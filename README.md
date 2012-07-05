# Perfume Global Site Project #001 -Real Stop Motion-
[perfume global site]( http://www.perfume-global.com/ )

EVERYONE CAN DANCE PERFUME by using this application. :-)

## Requirement
* Connected device that can be used through [OpenNI]( http://www.openni.org/ "OpenNI").

## Usage
### Get BVH files and Sound file
1. Download from [here]( http://www.perfume-global.com/ "perfume global site")

### Create sequenced image files
1. Double click /Bin/PrfmRSM.exe
1. Select a BVH file.
1. Select a folder to save image files.
1. Application window will open and there will be showing a T-posed model.
1. Make sure that your bone(skeleton) is recognized and displayed.
1. Conform your bone to displayed model. EVERY frame...

#### In PrfmRSM...
* Left Arrow: \-1 frame
* Right Arrow: \+1 frame
* Down Arrow: \-50 frame
* Up Arrow: \+50 frame
* Enter Key: Grab image and \+1 frame (even though your pose is fake.)
* z: lower match rate
* x: upper match rate
* Space Bar: random frame

### Make movie
1. Double click /Bin/VideoMaker.exe
1. Select "image" folder created automaticaly under the folder you selected to save images.
1. Select a sound file.
1. Select a path to save movie.
_You can skip this step if you had any other way to make movie from sequenced images and sound._  

### For Programmers
* You can reduce BVH file's frame rate with /Tools/conv_bvh_frame_rate.pl
* If you use Visual Studio /Tools/start_vs.bat may save steps of project setup. Anyway open it with a texteditor. :)

## License
built by nariakiiwatani  
facebook: nariakiiwatani  
twitter: @nariakiiwatani  
mail: nariakiiwatani@annolab.com  

----------------------------------------------------------

The MIT License

Copyright (c) 2012 nariakiiwatani and [anno lab]( http://www.annolab.com/ "anno lab")

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

----------------------------------------------------------
