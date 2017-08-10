# Unofficial Altis launcher for Linux
A Toontown Project Altis launcher using QT. Relies on a patched version of wine to function.

## Requirements
The launcher only requires QT in order to function

```bash
# Ubuntu/Mint
sudo apt install qt5-default qttool5-dev-tools
```

A custom build of wine with dummy methods however is required to launch Project
Altis. The patch provided should provide these methods.

```bash
# Ubuntu/Mint
sudo apt install flex bison libx11-dev:i386 libfreetype6-dev:i386 \
libxcursor-dev:i386 libxrandr-dev:i386 libxinerama-dev:i386 libpulse-dev:i386 \
libopenal-dev:i386 libglu1-mesa-dev:i386 libjpeg-dev:i386
```

gcc-multilib must also be installed on 64-bit systems

Due to how the launcher currently works, wine has to be installed in a
directory named wine along side the launcher, as well as the contents of the
pythonpath directory.
