LeonCam
=======

**Info**: Web version of LeonCam app is implemented: [LeonCam2](https://github.com/gradzka/LeonCam2)

Description
-----------
**LeonCam** is a 64-bit, multi-threaded, desktop application designed to home surveillance with IP network cameras. Written in the C/C++17 programming language, based on the Qt library. Dedicated to the Microsoft Windows operating system and IP cameras supporting the ONVIF standard. Includes face detection and recognition modules implemented using the OpenCV library. The local SQLite database was used to store application data.

Keywords: 64-bit, desktop, multithreading, IP camera, C/C++17, Qt, Microsoft Windows, ONVIF, OpenCV, SQLite

Library, technologies, tools
----------------------------
- C++17,
- Microsoft Visual Studio Enterprise 2017,
- Qt 5.9.1, Qt Creator 4.3.1, Qt Add-in for Visual Studio,
- OpenCV 2.4.13.3,
- OpenSSL 1.0.2,
- SQLite3,
- onvifcpplib (03.03.2017),
- opencv.ffmpeg (03.02.2016),
- FFmpeg 2.8.5,
- gSOAP 2.7.17,
- Wireshark 2.4.2,
- Git 2.11.0, GitHub, GitHub Desktop 3.3.4.0.

Hardware and software requirements
----------------------------------
- computer with a Windows 7+ operating system in the 64-bit version connected to the local network,
- IP camera compatible with ONVIF standard connected to the local network,
- installed video player for playing saved movies,
- minimum of 64 MB of free disk space,
- minimum of 256 MB of RAM,
- installed Visual Studio C++ Redistributable for Visual Studio 2013 and 2015 packages,
- installed H.264 codec.

How to run
----------
Open LeonCam.exe

Selected application windows
----------------------------
<p align="center"><img src="https://github.com/kazimierczak-robert/LeonCam/blob/master/Screenshots/Logowanie.png"></p>
<p align="center"><em>Figure 1. Login window</em></p>

<p align="center"><img src="https://github.com/kazimierczak-robert/LeonCam/blob/master/Screenshots/Zakladka_CAMERAS.png"></p>
<p align="center"><em>Figure 2. Main window - CAMERAS tab</em></p>  

<p align="center"><img src="https://github.com/kazimierczak-robert/LeonCam/blob/master/Screenshots/Wykonywanie_zdjecia.png"></p>
<p align="center"><em>Figure 3. Window for taking a face photo</em></p>

<p align="center"><img src="https://github.com/kazimierczak-robert/LeonCam/blob/master/Screenshots/Zakladka_REPORTS_Green.png">
</p>
<p align="center"><em>Figure 4. Main window - REPORTS tab, green reports</em></p>

Credits
-------
* Monika Grądzka
* Robert Kazimierczak

The LeonCam application was implemented as part of the engineering diploma thesis in the Institute of Control, Robotics and Information Engineering, Poznan University of Technology.

Supervisor: dr Anna Grocholewska-Czuryło

Attributions
------------
- http://doc.qt.io/qt-5.9/index.html
- https://github.com/linkingvision/rapidonvif/tree/onvifcpplib
- https://github.com/peters/opencv.ffmpeg
- https://github.com/Lycycz/onvif_device/blob/master/onvif.cpp
- https://asmaloney.com/2013/11/code/converting-between-cvmat-and-qimage-or-qpixmap
- http://develnoter.blogspot.com/2012/05/integrating-opencv-in-qt-gui.html
- http://www.qtcentre.org/threads/3416-Center-a-widget-in-a-cell-on-a-QTableWidget
- http://qt-project.org/doc/qt-4.8/qimage.html#QImage-6
- https://docs.opencv.org/2.4/modules/contrib/doc/facerec/facerec_tutorial.html
- https://pixabay.com/
- https://stackoverflow.com/ (hyperlinks in the source code)
- https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
- http://www.qtcentre.org/threads/52964-Draw-rectangle-on-QImage?s=e283053d55d3b36ab4616fb2051808c3&p=237304#post237304
- https://github.com/therecipe/qt/wiki/Setting-the-Application-Icon
