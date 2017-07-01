# Zedboard-face-detection  
The code is modified from https://github.com/cornell-zhang/facedetect-fpga.  

Develope Environment: SDSoC 2016.2

## How to Build

1. Open SDSoc -> create new SDSoC project -> enter project name, set Target Platform as zed. -> choose Empty Application and click Finish.  

2. Right click the 'src' folder under the newly create project -> Choose Import -> File System -> Browse to this project's src folder and import all of the file into the project.  

3. Right click the icon 'left' next to haar.cpp and it will show the funcitons in the haar.cpp -> left click detectFaces and toggle it as HW function.  

4. Click the navigation bar on the top and choose Build Project.  

5. After building finished, it will generate the SDCard_image folder under the SDDebug.Pull all of the things under SDCard_image to your SDCard. And boot the Zedboard form the SDCard.
