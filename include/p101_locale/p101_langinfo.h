#ifndef LIBP101_LOCALE_P101_LANGINFO_H
#define LIBP101_LOCALE_P101_LANGINFO_H

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

    char *p101_nl_langinfo(const struct p101_env *env, nl_item item);
    char *p101_nl_langinfo_l(const struct p101_env *env, nl_item item, locale_t locale);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_LOCALE_P101_LANGINFO_H
