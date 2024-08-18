
#ifndef CHECO_TILE_VIEW_EXPORT_H
#define CHECO_TILE_VIEW_EXPORT_H

#ifdef CHECO_TILE_VIEW_STATIC_DEFINE
#  define CHECO_TILE_VIEW_EXPORT
#  define CHECO_TILE_VIEW_NO_EXPORT
#else
#  ifndef CHECO_TILE_VIEW_EXPORT
#    ifdef checo_tile_view_EXPORTS
        /* We are building this library */
#      define CHECO_TILE_VIEW_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define CHECO_TILE_VIEW_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef CHECO_TILE_VIEW_NO_EXPORT
#    define CHECO_TILE_VIEW_NO_EXPORT 
#  endif
#endif

#ifndef CHECO_TILE_VIEW_DEPRECATED
#  define CHECO_TILE_VIEW_DEPRECATED __declspec(deprecated)
#endif

#ifndef CHECO_TILE_VIEW_DEPRECATED_EXPORT
#  define CHECO_TILE_VIEW_DEPRECATED_EXPORT CHECO_TILE_VIEW_EXPORT CHECO_TILE_VIEW_DEPRECATED
#endif

#ifndef CHECO_TILE_VIEW_DEPRECATED_NO_EXPORT
#  define CHECO_TILE_VIEW_DEPRECATED_NO_EXPORT CHECO_TILE_VIEW_NO_EXPORT CHECO_TILE_VIEW_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CHECO_TILE_VIEW_NO_DEPRECATED
#    define CHECO_TILE_VIEW_NO_DEPRECATED
#  endif
#endif

#endif /* CHECO_TILE_VIEW_EXPORT_H */
