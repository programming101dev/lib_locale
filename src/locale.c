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

#include "p101_locale/locale.h"
#include <p101_env/wrapper.h>

size_t p101_iconv(const struct p101_env *env, struct p101_error *err, iconv_t cd, char **restrict inbuf, size_t *restrict inbytesleft, char **restrict outbuf, size_t *restrict outbytesleft)
{
    size_t ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, (size_t)-1);
    errno   = 0;
    ret_val = iconv(cd, inbuf, inbytesleft, outbuf, outbytesleft);

    if(ret_val == (size_t)-1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_iconv_close(const struct p101_env *env, struct p101_error *err, iconv_t cd)
{
    char resource_id[P101_ENV_POINTER_RESOURCE_ID_SIZE];
    int  ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, -1);
    p101_env_pointer_resource_id(resource_id, sizeof(resource_id), cd);
    errno   = 0;
    ret_val = iconv_close(cd);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }
    else
    {
        P101_TRACK_RESOURCE_RELEASE(env, "iconv-descriptor", resource_id, NULL);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

iconv_t p101_iconv_open(const struct p101_env *env, struct p101_error *err, const char *tocode, const char *fromcode)
{
    iconv_t ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, (iconv_t)-1);    // NOLINT(performance-no-int-to-ptr)
    errno   = 0;
    ret_val = iconv_open(tocode, fromcode);

    if(ret_val == (iconv_t)-1)    // NOLINT(performance-no-int-to-ptr)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }
    else
    {
        P101_TRACK_POINTER_RESOURCE_ACQUIRE(env, "iconv-descriptor", ret_val, 0U, NULL);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

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

char *p101_nl_langinfo(const struct p101_env *env, nl_item item)
{
    char *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = nl_langinfo(item);

    P101_TRACE_EXIT(env);
    return ret_val;
}

char *p101_nl_langinfo_l(const struct p101_env *env, nl_item item, locale_t locale)
{
    char *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = nl_langinfo_l(item, locale);

    P101_TRACE_EXIT(env);
    return ret_val;
}

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
        P101_TRACK_POINTER_RESOURCE_ACQUIRE(env, "locale", ret_val, 0U, "duplicate");
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

void p101_freelocale(const struct p101_env *env, locale_t locobj)
{
    char resource_id[P101_ENV_POINTER_RESOURCE_ID_SIZE];

    P101_TRACE(env);
    p101_env_pointer_resource_id(resource_id, sizeof(resource_id), locobj);
    errno = 0;
    freelocale(locobj);
    P101_TRACK_RESOURCE_RELEASE(env, "locale", resource_id, NULL);
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
        P101_TRACK_POINTER_RESOURCE_ACQUIRE(env, "locale", ret_val, 0U, "new");
    }
    else
    {
        P101_TRACK_POINTER_RESOURCE_REPLACE(env, "locale", base, ret_val, 0U, "newlocale-base");
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

static char *mutable_fallback(const struct p101_env *env, const char *fallback)
{
    /*
     * POSIX gives catgets() a const fallback argument but a mutable return
     * type. This cast is the exact system-interface boundary; callers must
     * still treat the fallback as immutable when catgets() returns it.
     */
    P101_TRACE_SCOPE(env);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    return (char *)fallback;
#pragma GCC diagnostic pop
}

int p101_catclose(const struct p101_env *env, struct p101_error *err, nl_catd catd)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, -1);
    if(catd == (nl_catd)0 || catd == (nl_catd)-1)    // NOLINT(performance-no-int-to-ptr)
    {
        P101_ERROR_RAISE_ERRNO(err, EBADF);
        ret_val = -1;
        goto p101_wrapper_done_;
    }
    errno   = 0;
    ret_val = catclose(catd);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

char *p101_catgets(const struct p101_env *env, struct p101_error *err, nl_catd catd, int set_id, int msg_id, const char *s)
{
    char *ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, mutable_fallback(env, s));
    if(s == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, EINVAL);
        ret_val = NULL;
        goto p101_wrapper_done_;
    }
    if(catd == (nl_catd)0 || catd == (nl_catd)-1)    // NOLINT(performance-no-int-to-ptr)
    {
        P101_ERROR_RAISE_ERRNO(err, EBADF);
        ret_val = mutable_fallback(env, s);
        goto p101_wrapper_done_;
    }
    errno   = 0;
    ret_val = catgets(catd, set_id, msg_id, s);

    if(ret_val == s)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

nl_catd p101_catopen(const struct p101_env *env, struct p101_error *err, const char *name, int oflag)
{
    nl_catd ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, (nl_catd)-1);    // NOLINT(performance-no-int-to-ptr)
    if(name == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, EINVAL);
        ret_val = (nl_catd)-1;    // NOLINT(performance-no-int-to-ptr)
        goto p101_wrapper_done_;
    }
    errno   = 0;
    ret_val = catopen(name, oflag);

    if(ret_val == (nl_catd)-1)    // NOLINT(performance-no-int-to-ptr)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}
