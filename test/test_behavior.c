#include <langinfo.h>
#include <locale.h>
#include <p101_env/env.h>
#include <p101_error/error.h>
#include <p101_locale/locale.h>
#include <stdio.h>
#include <stdlib.h>

static int failures;

#define EXPECT(condition)                                                                                                                                                                                                                                          \
    do                                                                                                                                                                                                                                                             \
    {                                                                                                                                                                                                                                                              \
        if(!(condition))                                                                                                                                                                                                                                           \
        {                                                                                                                                                                                                                                                          \
            fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #condition);                                                                                                                                                                                   \
            failures++;                                                                                                                                                                                                                                            \
        }                                                                                                                                                                                                                                                          \
    } while(0)

int main(void)
{
    struct p101_error *err    = NULL;
    struct p101_env   *env    = NULL;
    locale_t           locale = (locale_t)0;
    char              *text;
    int                status;

    err = p101_error_create(false);
    if(err != NULL)
    {
        env = p101_env_create(err, NULL);
    }
    if(env == NULL)
    {
        failures++;
    }
    else
    {
        locale = p101_newlocale(env, err, LC_ALL_MASK, "C", (locale_t)0);
        EXPECT(locale != (locale_t)0);
        EXPECT(p101_error_has_no_error(err));

        /* P101_TEST_CASE(p101_nl_langinfo) */
        text = p101_nl_langinfo(env, CODESET);
        EXPECT(text != NULL);
        if(locale != (locale_t)0)
        {
            /* P101_TEST_CASE(p101_nl_langinfo_l) */
            text = p101_nl_langinfo_l(env, CODESET, locale);
            EXPECT(text != NULL);
            /* P101_TEST_CASE(p101_freelocale) */
            p101_freelocale(env, locale);
        }
    }
    p101_env_destroy(env);
    p101_error_destroy(err);
    status = failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
    return status;
}
