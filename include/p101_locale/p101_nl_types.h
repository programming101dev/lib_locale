#ifndef LIBP101_LOCALE_P101_NL_TYPES_H
#define LIBP101_LOCALE_P101_NL_TYPES_H

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

    int     p101_catclose(const struct p101_env *env, struct p101_error *err, nl_catd catd);
    char   *p101_catgets(const struct p101_env *env, struct p101_error *err, nl_catd catd, int set_id, int msg_id, const char *s);
    nl_catd p101_catopen(const struct p101_env *env, struct p101_error *err, const char *name, int oflag);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_LOCALE_P101_NL_TYPES_H
