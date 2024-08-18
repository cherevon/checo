
#ifndef CHECO_OS_UI_EXPORT_H
#define CHECO_OS_UI_EXPORT_H

#ifdef CHECO_OS_UI_STATIC_DEFINE
#  define CHECO_OS_UI_EXPORT
#  define CHECO_OS_UI_NO_EXPORT
#else
#  ifndef CHECO_OS_UI_EXPORT
#    ifdef checo_os_ui_EXPORTS
        /* We are building this library */
#      define CHECO_OS_UI_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define CHECO_OS_UI_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef CHECO_OS_UI_NO_EXPORT
#    define CHECO_OS_UI_NO_EXPORT 
#  endif
#endif

#ifndef CHECO_OS_UI_DEPRECATED
#  define CHECO_OS_UI_DEPRECATED __declspec(deprecated)
#endif

#ifndef CHECO_OS_UI_DEPRECATED_EXPORT
#  define CHECO_OS_UI_DEPRECATED_EXPORT CHECO_OS_UI_EXPORT CHECO_OS_UI_DEPRECATED
#endif

#ifndef CHECO_OS_UI_DEPRECATED_NO_EXPORT
#  define CHECO_OS_UI_DEPRECATED_NO_EXPORT CHECO_OS_UI_NO_EXPORT CHECO_OS_UI_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CHECO_OS_UI_NO_DEPRECATED
#    define CHECO_OS_UI_NO_DEPRECATED
#  endif
#endif

#endif /* CHECO_OS_UI_EXPORT_H */
