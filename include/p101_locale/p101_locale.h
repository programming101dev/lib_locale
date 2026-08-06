#ifndef LIBP101_LOCALE_P101_LOCALE_H
#define LIBP101_LOCALE_P101_LOCALE_H

/*
 * Copyright 2026 D'Arcy Smith.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LIBP101_LOCALE_SHARED_DECLARATIONS
    #define LIBP101_LOCALE_SHARED_DECLARATIONS
    #include <iconv.h>
    #include <langinfo.h>
    #include <locale.h>
    #include <nl_types.h>
    #include <p101_env/env.h>
    #include <p101_error/attributes.h>
    #if defined(__APPLE__) || defined(__FreeBSD__)
        #include <xlocale.h>
    #endif
#endif    // LIBP101_LOCALE_SHARED_DECLARATIONS

#ifdef __cplusplus
extern "C"
{
#endif

    locale_t p101_duplocale(const struct p101_env *env, struct p101_error *err, locale_t locobj) P101_ATTR_WARN_UNUSED_RESULT;
    void     p101_freelocale(const struct p101_env *env, locale_t locobj);
    locale_t p101_newlocale(const struct p101_env *env, struct p101_error *err, int category_mask, const char *locale, locale_t base) P101_ATTR_WARN_UNUSED_RESULT;
    locale_t p101_uselocale(const struct p101_env *env, struct p101_error *err, locale_t newloc) P101_ATTR_WARN_UNUSED_RESULT;

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_LOCALE_P101_LOCALE_H
