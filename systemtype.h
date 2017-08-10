#ifndef SYSTEMTYPE_H
#define SYSTEMTYPE_H

#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WINDOWS__)
#define SYSTEM_WINDOWS
#elif defined(__gnu_linux__) || defined(__linux__)
#define SYSTEM_LINUX
#elif defined(__APPLE__) && defined(__MACH__)
#define SYSTEM_MACOSX
#else
#error "Unknown system!"
#endif

#endif // SYSTEMTYPE_H
