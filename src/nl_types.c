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

#include "p101_locale/p101_nl_types.h"
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
