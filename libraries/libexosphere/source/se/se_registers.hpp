/*
 * Copyright (c) Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <exosphere.hpp>

namespace ams::se {

    struct SecurityEngineRegisters {
        u32 SE_SE_SECURITY;
        u32 SE_TZRAM_SECURITY;
        u32 SE_OPERATION;
        u32 SE_INT_ENABLE;
        u32 SE_INT_STATUS;
        u32 SE_CONFIG;
        u32 SE_IN_LL_ADDR;
        u32 SE_IN_CUR_BYTE_ADDR;
        u32 SE_IN_CUR_LL_ID;
        u32 SE_OUT_LL_ADDR;
        u32 SE_OUT_CUR_BYTE_ADDR;
        u32 SE_OUT_CUR_LL_ID;
        u32 SE_HASH_RESULT[0x10];
        u32 SE_CTX_SAVE_CONFIG;
        u32 SE_CTX_SAVE_AUTO;
        u32 _0x78[0x62];
        u32 SE_SHA_CONFIG;
        u32 SE_SHA_MSG_LENGTH[0x4];
        u32 SE_SHA_MSG_LEFT[0x4];
        u32 _0x224[0x17];
        u32 SE_CRYPTO_SECURITY_PERKEY;
        u32 SE_CRYPTO_KEYTABLE_ACCESS[0x10];
        u32 _0x2C4[0x10];
        u32 SE_CRYPTO_CONFIG;
        u32 SE_CRYPTO_LINEAR_CTR[0x4];
        u32 SE_CRYPTO_LAST_BLOCK;
        u32 SE_CRYPTO_KEYTABLE_ADDR;
        u32 SE_CRYPTO_KEYTABLE_DATA;
        u32 _0x324[0x3];
        u32 SE_CRYPTO_KEYTABLE_DST;
        u32 _0x334[0x3];
        u32 SE_RNG_CONFIG;
        u32 SE_RNG_SRC_CONFIG;
        u32 SE_RNG_RESEED_INTERVAL;
        u32 _0x34C[0x2D];
        u32 SE_RSA_CONFIG;
        u32 SE_RSA_KEY_SIZE;
        u32 SE_RSA_EXP_SIZE;
        u32 SE_RSA_SECURITY_PERKEY;
        u32 SE_RSA_KEYTABLE_ACCESS[0x2];
        u32 _0x418[0x2];
        u32 SE_RSA_KEYTABLE_ADDR;
        u32 SE_RSA_KEYTABLE_DATA;
        u32 SE_RSA_OUTPUT[0x40];
        u32 _0x528[0x6];
        u32 SE_TZRAM_OPERATION;
        u32 _0x544[0xAF];
        u32 SE_STATUS;
        u32 SE_ERR_STATUS;
        u32 SE_MISC;
        u32 SE_SPARE;
        u32 SE_ENTROPY_DEBUG_COUNTER;
        u32 _0x814;
        u32 _0x818;
        u32 _0x81C;
        u32 _0x820[0x5F8];
    };
    static_assert(util::is_pod<SecurityEngineRegisters>::value);
    static_assert(sizeof(SecurityEngineRegisters) == secmon::MemoryRegionPhysicalDeviceSecurityEngine.GetSize());

    static_assert(AesKeySlotCount == util::size(SecurityEngineRegisters{}.SE_CRYPTO_KEYTABLE_ACCESS));
    static_assert(RsaKeySlotCount == util::size(SecurityEngineRegisters{}.SE_RSA_KEYTABLE_ACCESS));

    #define SE_REG_BITS_MASK(NAME)                                      REG_NAMED_BITS_MASK    (SE, NAME)
    #define SE_REG_BITS_VALUE(NAME, VALUE)                              REG_NAMED_BITS_VALUE   (SE, NAME, VALUE)
    #define SE_REG_BITS_ENUM(NAME, ENUM)                                REG_NAMED_BITS_ENUM    (SE, NAME, ENUM)
    #define SE_REG_BITS_ENUM_SEL(NAME, __COND__, TRUE_ENUM, FALSE_ENUM) REG_NAMED_BITS_ENUM_SEL(SE, NAME, __COND__, TRUE_ENUM, FALSE_ENUM)

    #define DEFINE_SE_REG(NAME, __OFFSET__, __WIDTH__)                                                                                                                  REG_DEFINE_NAMED_REG           (SE, NAME, __OFFSET__, __WIDTH__)
    #define DEFINE_SE_REG_BIT_ENUM(NAME, __OFFSET__, ZERO, ONE)                                                                                                         REG_DEFINE_NAMED_BIT_ENUM      (SE, NAME, __OFFSET__, ZERO, ONE)
    #define DEFINE_SE_REG_TWO_BIT_ENUM(NAME, __OFFSET__, ZERO, ONE, TWO, THREE)                                                                                         REG_DEFINE_NAMED_TWO_BIT_ENUM  (SE, NAME, __OFFSET__, ZERO, ONE, TWO, THREE)
    #define DEFINE_SE_REG_THREE_BIT_ENUM(NAME, __OFFSET__, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN)                                                               REG_DEFINE_NAMED_THREE_BIT_ENUM(SE, NAME, __OFFSET__, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN)
    #define DEFINE_SE_REG_FOUR_BIT_ENUM(NAME, __OFFSET__, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, ELEVEN, TWELVE, THIRTEEN, FOURTEEN, FIFTEEN) REG_DEFINE_NAMED_FOUR_BIT_ENUM (SE, NAME, __OFFSET__, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, ELEVEN, TWELVE, THIRTEEN, FOURTEEN, FIFTEEN)

    #define DEFINE_SE_REG_BIT_ENUM_WITH_SW_CLEAR(NAME, __OFFSET__) \
        REG_DEFINE_NAMED_REG(SE, NAME, __OFFSET__, 1);             \
                                                                   \
        enum SE_##NAME {                                           \
            SE_##NAME##_##CLEAR    = 0,                            \
            SE_##NAME##_##ACTIVE   = 1,                            \
            SE_##NAME##_##SW_CLEAR = 1,                            \
        };

    /* SE_STATUS. */
    DEFINE_SE_REG_TWO_BIT_ENUM(STATUS_STATE, 0, IDLE, BUSY, WAIT_OUT, WAIT_IN);
    DEFINE_SE_REG_BIT_ENUM(STATUS_MEM_INTERFACE, 2, IDLE, BUSY);

    /* SE_SECURITY */
    DEFINE_SE_REG_BIT_ENUM(SECURITY_HARD_SETTING,      0,  SECURE, NONSECURE);
    DEFINE_SE_REG_BIT_ENUM(SECURITY_ENG_DIS,           1, DISABLE,    ENABLE);
    DEFINE_SE_REG_BIT_ENUM(SECURITY_PERKEY_SETTING,    2,  SECURE, NONSECURE);
    DEFINE_SE_REG_BIT_ENUM(SECURITY_CTX_SAVE_TZ_LOCK,  4,  SECURE, NONSECURE);
    DEFINE_SE_REG_BIT_ENUM(SECURITY_CTX_TZ_LOCK_SOFT,  5,  SECURE, NONSECURE);
    DEFINE_SE_REG_BIT_ENUM(SECURITY_SOFT_SETTING,     16,  SECURE, NONSECURE);

    /* SE_TZRAM_SECURITY */
    DEFINE_SE_REG(TZRAM_SETTING, 0, BITSIZEOF(u32));
    constexpr inline u32 SE_TZRAM_SETTING_SECURE = 0;

    /* SE_TZRAM_OPERATION */
    DEFINE_SE_REG_BIT_ENUM(TZRAM_OPERATION_REQ,  0, IDLE, INITIATE);
    DEFINE_SE_REG_BIT_ENUM(TZRAM_OPERATION_MODE, 1, SAVE, RESTORE);
    DEFINE_SE_REG_BIT_ENUM(TZRAM_OPERATION_BUSY, 2, NO, YES);
    DEFINE_SE_REG(TZRAM_OPERATION_CURR_ADDR, 16, 16);

    /* SE_OPERATION */
    DEFINE_SE_REG_THREE_BIT_ENUM(OPERATION_OP, 0, ABORT, START, RESTART_OUT, CTX_SAVE, RESTART_IN, RESERVED_5, RESERVED_6, RESERVED_7);

    /* SE_INT_ENABLE */
    DEFINE_SE_REG_BIT_ENUM(INT_ENABLE_IN_LL_BUF_RD,           0, DISABLE, ENABLE);
    DEFINE_SE_REG_BIT_ENUM(INT_ENABLE_IN_DONE,                1, DISABLE, ENABLE);
    DEFINE_SE_REG_BIT_ENUM(INT_ENABLE_OUT_LL_BUF_WR,          2, DISABLE, ENABLE);
    DEFINE_SE_REG_BIT_ENUM(INT_ENABLE_OUT_DONE,               3, DISABLE, ENABLE);
    DEFINE_SE_REG_BIT_ENUM(INT_ENABLE_SE_OP_DONE,             4, DISABLE, ENABLE);
    DEFINE_SE_REG_BIT_ENUM(INT_ENABLE_RESEED_CNTR_EXHAUSTED,  5, DISABLE, ENABLE);
    DEFINE_SE_REG_BIT_ENUM(INT_ENABLE_ERR_STAT,              16, DISABLE, ENABLE);

    /* SE_INT_STATUS */
    DEFINE_SE_REG_BIT_ENUM_WITH_SW_CLEAR(INT_STATUS_IN_LL_BUF_RD,           0);
    DEFINE_SE_REG_BIT_ENUM_WITH_SW_CLEAR(INT_STATUS_IN_DONE,                1);
    DEFINE_SE_REG_BIT_ENUM_WITH_SW_CLEAR(INT_STATUS_OUT_LL_BUF_WR,          2);
    DEFINE_SE_REG_BIT_ENUM_WITH_SW_CLEAR(INT_STATUS_OUT_DONE,               3);
    DEFINE_SE_REG_BIT_ENUM_WITH_SW_CLEAR(INT_STATUS_SE_OP_DONE,             4);
    DEFINE_SE_REG_BIT_ENUM_WITH_SW_CLEAR(INT_STATUS_RESEED_CNTR_EXHAUSTED,  5);
    DEFINE_SE_REG_BIT_ENUM_WITH_SW_CLEAR(INT_STATUS_ERR_STAT,              16);

    /* SE_CONFIG */
    DEFINE_SE_REG(CONFIG_DEC_MODE, 16, 8);
    DEFINE_SE_REG(CONFIG_ENC_MODE, 24, 8);

    DEFINE_SE_REG_THREE_BIT_ENUM(CONFIG_DST, 2, MEMORY, HASH_REG, KEYTABLE, SRK, RSA_REG, RESERVED5, RESERVED6, RESERVED7);
    DEFINE_SE_REG_FOUR_BIT_ENUM(CONFIG_DEC_ALG,  8, NOP, AES_DEC, RESERVED2, RESERVED3, RESERVED4, RESERVED5, RESERVED6, RESERVED7, RESERVED8, RESERVED9, RESERVED10, RESERVED11, RESERVED12, RESERVED13, RESERVED14, RESERVED15);
    DEFINE_SE_REG_FOUR_BIT_ENUM(CONFIG_ENC_ALG, 12, NOP, AES_ENC, RNG, SHA, RSA, RESERVED5, RESERVED6, RESERVED7, RESERVED8, RESERVED9, RESERVED10, RESERVED11, RESERVED12, RESERVED13, RESERVED14, RESERVED15);

    enum SE_CONFIG_DEC_MODE {
        SE_CONFIG_DEC_MODE_AESMODE_KEY128 = 0,
        SE_CONFIG_DEC_MODE_AESMODE_KEY192 = 1,
        SE_CONFIG_DEC_MODE_AESMODE_KEY256 = 2,
    };

    enum SE_CONFIG_ENC_MODE {
        SE_CONFIG_ENC_MODE_AESMODE_KEY128 = 0,
        SE_CONFIG_ENC_MODE_AESMODE_KEY192 = 1,
        SE_CONFIG_ENC_MODE_AESMODE_KEY256 = 2,

        SE_CONFIG_ENC_MODE_SHA1   = 1,
        SE_CONFIG_ENC_MODE_SHA224 = 4,
        SE_CONFIG_ENC_MODE_SHA256 = 5,
        SE_CONFIG_ENC_MODE_SHA384 = 6,
        SE_CONFIG_ENC_MODE_SHA512 = 7,
    };

    /* SE_CTX_SAVE_CONFIG */
    DEFINE_SE_REG_TWO_BIT_ENUM(CTX_SAVE_CONFIG_AES_WORD_QUAD, 0, KEYS_0_3, KEYS_4_7, ORIGINAL_IVS, UPDATED_IVS);
    DEFINE_SE_REG(CTX_SAVE_CONFIG_PKA1_WORD_QUAD_L,  0, 4);
    DEFINE_SE_REG(CTX_SAVE_CONFIG_AES_KEY_INDEX,     8, 4);
    DEFINE_SE_REG(CTX_SAVE_CONFIG_RSA_WORD_QUAD,    12, 4);
    DEFINE_SE_REG(CTX_SAVE_CONFIG_PKA1_WORD_QUAD_H, 12, 4);
    DEFINE_SE_REG_TWO_BIT_ENUM(CTX_SAVE_CONFIG_RSA_KEY_INDEX, 16, SLOT0_EXPONENT, SLOT0_MODULUS, SLOT1_EXPONENT, SLOT1_MODULUS);
    DEFINE_SE_REG_BIT_ENUM(CTX_SAVE_CONFIG_STICKY_WORD_QUAD, 24, WORDS_0_3, WORDS_4_7);
    DEFINE_SE_REG_THREE_BIT_ENUM(CTX_SAVE_CONFIG_SRC, 29, STICKY_BITS, RSA_KEYTABLE, AES_KEYTABLE, PKA1_STICKY_BITS, MEM, RESERVED5, SRK, PKA1_KEYTABLE);

    /* SE_CTX_SAVE_AUTO */
    DEFINE_SE_REG_BIT_ENUM(CTX_SAVE_AUTO_ENABLE, 0, NO, YES);
    DEFINE_SE_REG_BIT_ENUM(CTX_SAVE_AUTO_LOCK, 8, NO, YES);
    DEFINE_SE_REG(CTX_SAVE_AUTO_CURR_CNT, 16, 10);

    /* SE_SHA_CONFIG */
    DEFINE_SE_REG(SHA_CONFIG_HW_INIT_HASH, 0, 1);


    /* SE_CRYPTO_KEYTABLE_ADDR */
    DEFINE_SE_REG(CRYPTO_KEYTABLE_ADDR_KEYIV_WORD,     0, 4);
    DEFINE_SE_REG(CRYPTO_KEYTABLE_ADDR_KEYIV_IV_WORD,  0, 2);
    DEFINE_SE_REG(CRYPTO_KEYTABLE_ADDR_KEYIV_KEY_WORD, 0, 3);

    enum SE_CRYPTO_KEYTABLE_ADDR_KEYIV_WORD {
        SE_CRYPTO_KEYTABLE_ADDR_KEYIV_WORD_KEY_0 =  0u,
        SE_CRYPTO_KEYTABLE_ADDR_KEYIV_WORD_KEY_1 =  1u,
        SE_CRYPTO_KEYTABLE_ADDR_KEYIV_WORD_KEY_2 =  2u,
        SE_CRYPTO_KEYTABLE_ADDR_KEYIV_WORD_KEY_3 =  3u,
        SE_CRYPTO_KEYTABLE_ADDR_KEYIV_WORD_KEY_4 =  4u,
        SE_CRYPTO_KEYTABLE_ADDR_KEYIV_WORD_KEY_5 =  5u,
        SE_CRYPTO_KEYTABLE_ADDR_KEYIV_WORD_KEY_6 =  6u,
        SE_CRYPTO_KEYTABLE_ADDR_KEYIV_WORD_KEY_7 =  7u,
        SE_CRYPTO_KEYTABLE_ADDR_KEYIV_WORD_OIV_0 =  8u,
        SE_CRYPTO_KEYTABLE_ADDR_KEYIV_WORD_OIV_1 =  9u,
        SE_CRYPTO_KEYTABLE_ADDR_KEYIV_WORD_OIV_2 = 10u,
        SE_CRYPTO_KEYTABLE_ADDR_KEYIV_WORD_OIV_3 = 11u,
        SE_CRYPTO_KEYTABLE_ADDR_KEYIV_WORD_UIV_0 = 12u,
        SE_CRYPTO_KEYTABLE_ADDR_KEYIV_WORD_UIV_1 = 13u,
        SE_CRYPTO_KEYTABLE_ADDR_KEYIV_WORD_UIV_2 = 14u,
        SE_CRYPTO_KEYTABLE_ADDR_KEYIV_WORD_UIV_3 = 15u,
    };

    DEFINE_SE_REG_BIT_ENUM(CRYPTO_KEYTABLE_ADDR_KEYIV_IV_SEL,    2, ORIGINAL_IV, UPDATED_IV);
    DEFINE_SE_REG_BIT_ENUM(CRYPTO_KEYTABLE_ADDR_KEYIV_KEYIV_SEL, 3,         KEY,         IV);

    DEFINE_SE_REG(CRYPTO_KEYTABLE_ADDR_KEYIV_KEY_SLOT, 4, 4);

    /* SE_RSA_CONFIG */
    DEFINE_SE_REG(RSA_CONFIG_KEY_SLOT, 24, 1);

    /* SE_RSA_KEYTABLE_ADDR */
    DEFINE_SE_REG(RSA_KEYTABLE_ADDR_WORD_ADDR, 0, 6);
    DEFINE_SE_REG_BIT_ENUM(RSA_KEYTABLE_ADDR_EXPMOD_SEL, 6, EXPONENT, MODULUS);
    DEFINE_SE_REG(RSA_KEYTABLE_ADDR_KEY_SLOT, 7, 1);
    DEFINE_SE_REG_BIT_ENUM(RSA_KEYTABLE_ADDR_INPUT_MODE, 8, REGISTER, MEMORY);

    /* SE_RSA_KEYTABLE_ACCESS */
    DEFINE_SE_REG_BIT_ENUM(RSA_KEYTABLE_ACCESS_KEYREAD,   0, DISABLE, ENABLE);
    DEFINE_SE_REG_BIT_ENUM(RSA_KEYTABLE_ACCESS_KEYUPDATE, 1, DISABLE, ENABLE);
    DEFINE_SE_REG_BIT_ENUM(RSA_KEYTABLE_ACCESS_KEYUSE,    2, DISABLE, ENABLE);

    /* SE_CRYPTO_CONFIG */
    DEFINE_SE_REG_BIT_ENUM(CRYPTO_CONFIG_HASH_ENB, 0, DISABLE, ENABLE);
    DEFINE_SE_REG_TWO_BIT_ENUM(CRYPTO_CONFIG_XOR_POS, 1, BYPASS, RESERVED, TOP, BOTTOM);
    DEFINE_SE_REG_TWO_BIT_ENUM(CRYPTO_CONFIG_INPUT_SEL, 3, MEMORY, RANDOM, INIT_AESOUT, LINEAR_CTR);
    DEFINE_SE_REG_TWO_BIT_ENUM(CRYPTO_CONFIG_VCTRAM_SEL, 5, MEMORY, RESERVED, INIT_AESOUT, INIT_PREV_MEMORY);
    DEFINE_SE_REG_BIT_ENUM(CRYPTO_CONFIG_IV_SELECT, 7, ORIGINAL, UPDATED);
    DEFINE_SE_REG_BIT_ENUM(CRYPTO_CONFIG_CORE_SEL, 8, DECRYPT, ENCRYPT);
    DEFINE_SE_REG_BIT_ENUM(CRYPTO_CONFIG_KEYSCH_BYPASS, 10, DISABLE, ENABLE);
    DEFINE_SE_REG(CRYPTO_CONFIG_CTR_CNTN, 11, 8);
    DEFINE_SE_REG(CRYPTO_CONFIG_KEY_INDEX, 24, 4);
    DEFINE_SE_REG_BIT_ENUM(CRYPTO_CONFIG_MEMIF, 31, AHB, MCCIF);

    /* SE_CRYPTO_KEYTABLE_DST */
    DEFINE_SE_REG_TWO_BIT_ENUM(CRYPTO_KEYTABLE_DST_WORD_QUAD, 0, KEYS_0_3, KEYS_4_7, ORIGINAL_IV, UPDATED_IV);
    DEFINE_SE_REG(CRYPTO_KEYTABLE_DST_KEY_INDEX, 8, 4);

    /* SE_RNG_CONFIG */
    DEFINE_SE_REG_TWO_BIT_ENUM(RNG_CONFIG_MODE, 0, NORMAL, FORCE_INSTANTIATION, FORCE_RESEED, RESERVED3);
    DEFINE_SE_REG_TWO_BIT_ENUM(RNG_CONFIG_SRC,  2, NONE, ENTROPY, LFSR, RESERVED3);

    /* SE_RNG_SRC_CONFIG */
    DEFINE_SE_REG_BIT_ENUM(RNG_SRC_CONFIG_RO_ENTROPY_SOURCE_LOCK, 0, DISABLE, ENABLE);
    DEFINE_SE_REG_BIT_ENUM(RNG_SRC_CONFIG_RO_ENTROPY_SOURCE, 1, DISABLE, ENABLE);
    DEFINE_SE_REG_BIT_ENUM(RNG_SRC_CONFIG_HW_DISABLE_CYA, 2, DISABLE, ENABLE);
    DEFINE_SE_REG(RNG_SRC_CONFIG_RO_ENTROPY_SUBSAMPLE, 4, 3);
    DEFINE_SE_REG(RNG_SRC_CONFIG_RO_ENTROPY_DATA_FLUSH, 8, 1);

}
