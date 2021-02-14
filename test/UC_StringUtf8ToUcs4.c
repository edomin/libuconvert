#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "uc/uc.h"

void UC_StringUtf8ToUcs4_Utf8null_MaxLen6_Ucs4zeros_Len0(
 __attribute__((unused)) void **state) {
    uint32_t ucs4[7] = {0};
    size_t   len = UC_StringUtf8ToUcs4(NULL, ucs4, 6u);
    uint32_t test_value[] = {
     0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
     0x00000000u, 0x00000000u
    };

    assert_int_equal(len, 0u);
    assert_memory_equal(ucs4, test_value, sizeof(uint32_t) * 7);
}

void UC_StringUtf8ToUcs4_Utf8Privet_MaxLen6_Ucs4null_Len0(
 __attribute__((unused)) void **state) {
    uint8_t utf8[] = {0xD0, 0x9F, 0xD1, 0x80, 0xD0, 0xB8, 0xD0, 0xB2, 0xD0,
     0xB5, 0xD1, 0x82, 0x00}; /* Привет */
    size_t  len = UC_StringUtf8ToUcs4(utf8, NULL, 6u);

    assert_true(len == 0u);
}

void UC_StringUtf8ToUcs4_Utf8Privet_MaxLen6_Ucs4Privet_Len6(
 __attribute__((unused)) void **state) {
    uint8_t  utf8[] = {0xD0, 0x9F, 0xD1, 0x80, 0xD0, 0xB8, 0xD0, 0xB2, 0xD0,
     0xB5, 0xD1, 0x82, 0x00}; /* Привет */
    uint32_t ucs4[7] = {0};
    size_t   len = UC_StringUtf8ToUcs4(utf8, ucs4, 6u);
    uint32_t test_value[] = {
     0x0000041Fu, 0x00000440u, 0x00000438u, 0x00000432u, 0x00000435u,
     0x00000442u, 0x00000000u
    };

    assert_int_equal(len, 6u);
    assert_memory_equal(ucs4, test_value, sizeof(uint32_t) * 7);
}

void UC_StringUtf8ToUcs4_Utf8Privet_MaxLen6_Ucs4Prive_Len5(
 __attribute__((unused)) void **state) {
    uint8_t  utf8[] = {0xD0, 0x9F, 0xD1, 0x80, 0xD0, 0xB8, 0xD0, 0xB2, 0xD0,
     0xB5, 0x00}; /* Приве */
    uint32_t ucs4[7] = {0};
    size_t   len = UC_StringUtf8ToUcs4(utf8, ucs4, 6u);
    uint32_t test_value[] = {
     0x0000041Fu, 0x00000440u, 0x00000438u, 0x00000432u, 0x00000435u,
     0x00000000u, 0x00000000u
    };

    assert_int_equal(len, 5u);
    assert_memory_equal(ucs4, test_value, sizeof(uint32_t) * 7);
}

void UC_StringUtf8ToUcs4_Utf8Privet_MaxLen5_Ucs4Prive_Len5(
 __attribute__((unused)) void **state) {
    uint8_t  utf8[] = {0xD0, 0x9F, 0xD1, 0x80, 0xD0, 0xB8, 0xD0, 0xB2, 0xD0,
     0xB5, 0xD1, 0x82, 0x00}; /* Привет */
    uint32_t ucs4[7] = {0};
    size_t   len = UC_StringUtf8ToUcs4(utf8, ucs4, 5u);
    uint32_t test_value[] = {
     0x0000041Fu, 0x00000440u, 0x00000438u, 0x00000432u, 0x00000435u,
     0x00000000u, 0x00000000u
    };

    assert_int_equal(len, 5u);
    assert_memory_equal(ucs4, test_value, sizeof(uint32_t) * 7);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_StringUtf8ToUcs4_Utf8null_MaxLen6_Ucs4zeros_Len0),
    cmocka_unit_test(UC_StringUtf8ToUcs4_Utf8Privet_MaxLen6_Ucs4null_Len0),
    cmocka_unit_test(UC_StringUtf8ToUcs4_Utf8Privet_MaxLen6_Ucs4Privet_Len6),
    cmocka_unit_test(UC_StringUtf8ToUcs4_Utf8Privet_MaxLen6_Ucs4Prive_Len5),
    cmocka_unit_test(UC_StringUtf8ToUcs4_Utf8Privet_MaxLen5_Ucs4Prive_Len5),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
