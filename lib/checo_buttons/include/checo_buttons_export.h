
#ifndef CHECO_BUTTONS_EXPORT_H
#define CHECO_BUTTONS_EXPORT_H

#ifdef CHECO_BUTTONS_STATIC_DEFINE
#  define CHECO_BUTTONS_EXPORT
#  define CHECO_BUTTONS_NO_EXPORT
#else
#  ifndef CHECO_BUTTONS_EXPORT
#    ifdef checo_buttons_EXPORTS
        /* We are building this library */
#      define CHECO_BUTTONS_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define CHECO_BUTTONS_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef CHECO_BUTTONS_NO_EXPORT
#    define CHECO_BUTTONS_NO_EXPORT 
#  endif
#endif

#ifndef CHECO_BUTTONS_DEPRECATED
#  define CHECO_BUTTONS_DEPRECATED __declspec(deprecated)
#endif

#ifndef CHECO_BUTTONS_DEPRECATED_EXPORT
#  define CHECO_BUTTONS_DEPRECATED_EXPORT CHECO_BUTTONS_EXPORT CHECO_BUTTONS_DEPRECATED
#endif

#ifndef CHECO_BUTTONS_DEPRECATED_NO_EXPORT
#  define CHECO_BUTTONS_DEPRECATED_NO_EXPORT CHECO_BUTTONS_NO_EXPORT CHECO_BUTTONS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CHECO_BUTTONS_NO_DEPRECATED
#    define CHECO_BUTTONS_NO_DEPRECATED
#  endif
#endif

#endif /* CHECO_BUTTONS_EXPORT_H */
