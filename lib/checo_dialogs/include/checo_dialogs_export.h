
#ifndef CHECO_DIALOGS_EXPORT_H
#define CHECO_DIALOGS_EXPORT_H

#ifdef CHECO_DIALOGS_STATIC_DEFINE
#  define CHECO_DIALOGS_EXPORT
#  define CHECO_DIALOGS_NO_EXPORT
#else
#  ifndef CHECO_DIALOGS_EXPORT
#    ifdef checo_dialogs_EXPORTS
        /* We are building this library */
#      define CHECO_DIALOGS_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define CHECO_DIALOGS_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef CHECO_DIALOGS_NO_EXPORT
#    define CHECO_DIALOGS_NO_EXPORT 
#  endif
#endif

#ifndef CHECO_DIALOGS_DEPRECATED
#  define CHECO_DIALOGS_DEPRECATED __declspec(deprecated)
#endif

#ifndef CHECO_DIALOGS_DEPRECATED_EXPORT
#  define CHECO_DIALOGS_DEPRECATED_EXPORT CHECO_DIALOGS_EXPORT CHECO_DIALOGS_DEPRECATED
#endif

#ifndef CHECO_DIALOGS_DEPRECATED_NO_EXPORT
#  define CHECO_DIALOGS_DEPRECATED_NO_EXPORT CHECO_DIALOGS_NO_EXPORT CHECO_DIALOGS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CHECO_DIALOGS_NO_DEPRECATED
#    define CHECO_DIALOGS_NO_DEPRECATED
#  endif
#endif

#endif /* CHECO_DIALOGS_EXPORT_H */
