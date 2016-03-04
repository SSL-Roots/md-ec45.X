#include "PCUnit/PCUnit.h"
#include	"static_zone.h"

static int initialize(void)
{
	return 0;
}

static int cleanup(void)
{
	return 0;
}

static int setup(void)
{
	return 0;
}

static int teardown(void)
{
	return 0;
}


static void test_mallocZone(void)
{
	int	max_num = 128, i;
	StaticZone	zone;
	initZone(&zone);

	PCU_ASSERT_EQUAL(zone.num_used, 0);

	for (i=0; i<max_num; i++) {
		PCU_ASSERT_PTR_NOT_NULL(mallocZone(&zone, 1));
	}
	PCU_ASSERT_EQUAL(max_num, zone.num_used);
	PCU_ASSERT_PTR_NULL(mallocZone(&zone, 1));

}


PCU_Suite *static_zone_test_suite(void)
{
	static PCU_Test tests[] = {
		PCU_TEST(test_mallocZone),
	};
	static PCU_Suite suite = {
		"static_zone_test", tests, sizeof tests / sizeof tests[0],
		setup,
		teardown,
		initialize,
		cleanup,
	};
	return &suite;
}

