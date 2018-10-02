#ifndef LOGGEREXPORT_H
#define LOGGEREXPORT_H

#ifdef _WIN32
    #define DECL_EXPORT __declspec(dllexport)
    #define DECL_IMPORT __declspec(dllimport)
#elif __GNUC__
    #define DECL_EXPORT __attribute__((visibility("default")))
#else
    #define DECL_EXPORT
    #define DECL_IMPORT
#endif

#ifdef BUILD_LOGGER
    //We are building this library
    #define LOGGER_API DECL_EXPORT
#else
    //We are using this library
    #define LOGGER_API DECL_IMPORT
#endif

#endif  //LOGGEREXPORT_H
