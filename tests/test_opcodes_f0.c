#include <aiv_unit_test.h>
#include <aiv_gb.h>

TEST(pop_af)
{
    aiv_gameboy gb;
    aiv_gb_init(&gb);

    gb.sp = 0xff;
    aiv_gb_memory_write8(&gb, gb.sp - 1, 0xf0);
    gb.sp -= 1;

    gb.cartridge[0] = 0xf1;
    aiv_gb_tick(&gb);

    ASSERT_THAT(gb.sp == 0xff);
    ASSERT_THAT(gb.af == 0xf0);
    ASSERT_THAT(gb.ticks == 12);
    ASSERT_THAT(gb.pc == 1);
}

TEST(push_af)
{
    aiv_gameboy gb;
    aiv_gb_init(&gb);
    gb.sp = 0xff;

    gb.af = 0xf0;

    gb.cartridge[0] = 0xf5;
    aiv_gb_tick(&gb);

    u16_t value = aiv_gb_memory_read8(&gb, gb.sp + 1);
    
    ASSERT_THAT(gb.sp == 0xfe);
    ASSERT_THAT(value == 0xf0);
    ASSERT_THAT(gb.pc == 1);
    ASSERT_THAT(gb.ticks == 16);
}

void aiv_gb_tests_run_opcodes_f0()
{
    RUN_TEST(pop_af);
    RUN_TEST(push_af);
}
