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

#include "p101_locale/p101_locale.h"
#include <p101_env/resource_classes.h>
#include <p101_env/wrapper.h>

/*
 * Copyright 2021-2024 D'Arcy Smith.
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

locale_t p101_duplocale(const struct p101_env *env, struct p101_error *err, locale_t locobj)
{
    locale_t ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, (locale_t)0);
    errno   = 0;
    ret_val = duplocale(locobj);

    if(ret_val == (locale_t)0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }
    else
    {
        P101_TRACK_POINTER_RESOURCE_ACQUIRE(env, P101_RESOURCE_CLASS_LOCALE, ret_val, 0U, "duplicate");
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

void p101_freelocale(const struct p101_env *env, locale_t locobj)
{
    P101_TRACE(env);
    errno = 0;
    freelocale(locobj);
    P101_TRACK_POINTER_RESOURCE_RELEASE(env, P101_RESOURCE_CLASS_LOCALE, locobj, NULL);
    P101_TRACE_EXIT(env);
}

locale_t p101_newlocale(const struct p101_env *env, struct p101_error *err, int category_mask, const char *locale, locale_t base)
{
    locale_t ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, (locale_t)0);
    errno   = 0;
    ret_val = newlocale(category_mask, locale, base);

    if(ret_val == (locale_t)0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }
    else if(base == (locale_t)0)
    {
        P101_TRACK_POINTER_RESOURCE_ACQUIRE(env, P101_RESOURCE_CLASS_LOCALE, ret_val, 0U, "new");
    }
    else
    {
        P101_TRACK_POINTER_RESOURCE_REPLACE(env, P101_RESOURCE_CLASS_LOCALE, base, ret_val, 0U, "newlocale-base");
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

locale_t p101_uselocale(const struct p101_env *env, struct p101_error *err, locale_t newloc)
{
    locale_t ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, (locale_t)0);
    errno   = 0;
    ret_val = uselocale(newloc);

    if(ret_val == (locale_t)0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}
