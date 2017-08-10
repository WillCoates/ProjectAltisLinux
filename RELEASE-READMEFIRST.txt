Before using this launcher, you need to make sure the following packages are installed:
* libqt5

i386 (32-bit) versions of the following packages must also be installed:
* libx11
* libfreetype
* libxcursor
* libxrandr
* libxinerama
* libpulse
* libopenal
* libglu1-mesa
* libjpeg

On 64-bit systems, multilib must also be installed (gcc-multilib on Ubuntu)

To install these packages on Ubuntu or Mint, run the following in a terminal:
sudo apt install libx11:i386 libfreetype6:i386 libxcursor:i386 libxrandr:i386 \
libxinerama:i386 libpulse:i386 libopenal:i386 libglu1-mesa:i386 libjpeg:i386 \
qt5-default
