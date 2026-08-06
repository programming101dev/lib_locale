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

#include "p101_locale/p101_iconv.h"
#include "p101_locale/p101_langinfo.h"
#include "p101_locale/p101_locale.h"
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
