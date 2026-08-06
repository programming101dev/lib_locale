# Project metadata
set(PROJECT_NAME "p101_locale")
set(PROJECT_VERSION "0.0.1")
set(PROJECT_DESCRIPTION "Locales, message catalogs, language information, and conversion")
set(PROJECT_LANGUAGE "C")

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(STANDARD_FLAGS
        -D_POSIX_C_SOURCE=200809L
        -D_XOPEN_SOURCE=700
        -Werror
)
set(DARWIN_STANDARD_FLAGS -D_DARWIN_C_SOURCE)
set(LINUX_STANDARD_FLAGS -D_GNU_SOURCE)
set(BSD_STANDARD_FLAGS -D_BSD_SOURCE -D__BSD_VISIBLE)

set(LIBRARY_TARGETS p101_locale)
set(p101_locale_SOURCES
        src/iconv.c
        src/langinfo.c
        src/locale.c
        src/nl_types.c
)
set(p101_locale_HEADERS
        include/p101_locale/p101_iconv.h
        include/p101_locale/p101_langinfo.h
        include/p101_locale/p101_locale.h
        include/p101_locale/p101_nl_types.h
)
set(p101_locale_LINK_LIBRARIES
        p101_error
        p101_env
        p101_c
        iconv
)

