#include "PCUnit/PCUnit.h"
#include	"pack.h"

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


static void test_initPackedMsgpack(void)
{
	msgpack_packed	pk;
	initPackedMsgpack(&pk);

	PCU_ASSERT_EQUAL(0, pk.size);
}

static void	test_packSignedChar(void)
{
	msgpack_packed	pk;
	initPackedMsgpack(&pk);

	packSignedCharMsgpack(&pk, -30);
	PCU_ASSERT_EQUAL(1, pk.size);
	PCU_ASSERT_EQUAL(0xe2, pk.data[0]);
	packSignedCharMsgpack(&pk, -80);
	PCU_ASSERT_EQUAL(3, pk.size);
	PCU_ASSERT_EQUAL(0xd0, pk.data[1]);
}

static void	test_packSignedShort(void)
{
	msgpack_packed	pk;
	initPackedMsgpack(&pk);

	packSignedShortMsgpack(&pk, -30);
	PCU_ASSERT_EQUAL(1, pk.size);
	PCU_ASSERT_EQUAL(0xe2, pk.data[0]);
	packSignedShortMsgpack(&pk, -80);
	PCU_ASSERT_EQUAL(4, pk.size);
	PCU_ASSERT_EQUAL(0xd1, pk.data[1]);
	PCU_ASSERT_EQUAL(0xFF, pk.data[2]);
	PCU_ASSERT_EQUAL(0xB0, pk.data[3]);
	packSignedShortMsgpack(&pk, -256);
	PCU_ASSERT_EQUAL(7, pk.size);
	PCU_ASSERT_EQUAL(0xd1, pk.data[4]);
	PCU_ASSERT_EQUAL(0xFF, pk.data[5]);
	PCU_ASSERT_EQUAL(0x00, pk.data[6]);
}

static void	test_packSignedLong(void)
{
	msgpack_packed	pk;
	initPackedMsgpack(&pk);

	packSignedLongMsgpack(&pk, -30);
	PCU_ASSERT_EQUAL(1, pk.size);
	PCU_ASSERT_EQUAL(0xe2, pk.data[0]);
	packSignedLongMsgpack(&pk, -80);
	PCU_ASSERT_EQUAL(6, pk.size);
	PCU_ASSERT_EQUAL(0xd2, pk.data[1]);
	PCU_ASSERT_EQUAL(0xFF, pk.data[2]);
	PCU_ASSERT_EQUAL(0xFF, pk.data[3]);
	PCU_ASSERT_EQUAL(0xFF, pk.data[4]);
	PCU_ASSERT_EQUAL(0xb0, pk.data[5]);
}


PCU_Suite *pack_test_suite(void)
{
	static PCU_Test tests[] = {
		PCU_TEST(test_initPackedMsgpack),
		PCU_TEST(test_packSignedChar),
		PCU_TEST(test_packSignedShort),
		PCU_TEST(test_packSignedLong),
	};
	static PCU_Suite suite = {
		"pack_test", tests, sizeof tests / sizeof tests[0],
		setup,
		teardown,
		initialize,
		cleanup,
	};
	return &suite;
}

