#include <aiv_unit_test.h>
#include <aiv_gb.h>

TEST(pop_af)
{
    aiv_gameboy gb;
    aiv_gb_init(&gb);

    gb.sp = 0xff;
    aiv_gb_memory_write16(&gb, gb.sp - 1, 0xff00);
    gb.sp -= 2;

    gb.cartridge[0] = 0xf1;
    aiv_gb_tick(&gb);

    ASSERT_THAT(gb.af == 0xff00);
    ASSERT_THAT(gb.ticks == 12);
    ASSERT_THAT(gb.pc == 3);
}

void aiv_gb_tests_run_opcodes_f0()
{
    RUN_TEST(pop_af);
}
