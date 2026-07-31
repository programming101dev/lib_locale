#ifndef LIBP101_LOCALE_LOCALE_H
#define LIBP101_LOCALE_LOCALE_H

/*
 * Copyright 2026 D'Arcy Smith.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 */

#include <iconv.h>
#include <langinfo.h>
#include <locale.h>
#include <nl_types.h>
#include <p101_env/env.h>
#include <p101_error/attributes.h>
#if defined(__APPLE__) || defined(__FreeBSD__)
    #include <xlocale.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    int      p101_catclose(const struct p101_env *env, struct p101_error *err, nl_catd catd);
    char    *p101_catgets(const struct p101_env *env, struct p101_error *err, nl_catd catd, int set_id, int msg_id, const char *s);
    nl_catd  p101_catopen(const struct p101_env *env, struct p101_error *err, const char *name, int oflag);
    locale_t p101_duplocale(const struct p101_env *env, struct p101_error *err, locale_t locobj) P101_ATTR_WARN_UNUSED_RESULT;
    void     p101_freelocale(const struct p101_env *env, locale_t locobj);
    size_t   p101_iconv(const struct p101_env *env, struct p101_error *err, iconv_t cd, char **restrict inbuf, size_t *restrict inbytesleft, char **restrict outbuf, size_t *restrict outbytesleft);
    int      p101_iconv_close(const struct p101_env *env, struct p101_error *err, iconv_t cd);
    iconv_t  p101_iconv_open(const struct p101_env *env, struct p101_error *err, const char *tocode, const char *fromcode);
    locale_t p101_newlocale(const struct p101_env *env, struct p101_error *err, int category_mask, const char *locale, locale_t base) P101_ATTR_WARN_UNUSED_RESULT;
    char    *p101_nl_langinfo(const struct p101_env *env, nl_item item);
    char    *p101_nl_langinfo_l(const struct p101_env *env, nl_item item, locale_t locale);
    locale_t p101_uselocale(const struct p101_env *env, struct p101_error *err, locale_t newloc) P101_ATTR_WARN_UNUSED_RESULT;

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_LOCALE_LOCALE_H
