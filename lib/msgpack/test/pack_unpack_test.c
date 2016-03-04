#include "PCUnit/PCUnit.h"
#include	"pack.h"
#include	"unpack.h"

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


static void test_1_pack_unpack(void)
{
	msgpack_packed	pk;
	msgpack_unpacker	upkr;
	msgpack_unpacked	upkd;

	initPackedMsgpack(&pk);
	initUnpackerMsgpack(&upkr);
	initUnpackedMsgpack(&upkd);

	//[4,[200]]
	packArrayMsgpack(&pk, 2);
	packUnsignedCharMsgpack(&pk, 4);
	packArrayMsgpack(&pk, 1);
	packSignedShortMsgpack(&pk,200);

	int	i;
	for (i=0; i<pk.size; i++ ) {
		pushByteUnpackerMsgpack(*(pk.data + i), &upkr);
	}

	bool	retval;

	retval	= unpackerNextMsgpack(&upkr,&upkd);
	PCU_ASSERT_TRUE(retval);
	PCU_ASSERT_EQUAL(MSGPACK_OBJECT_ARRAY, upkd.data->type);
}


PCU_Suite *pack_unpack_test_suite(void)
{
	static PCU_Test tests[] = {
		PCU_TEST(test_1_pack_unpack),
	};
	static PCU_Suite suite = {
		"pack_unpack_test", tests, sizeof tests / sizeof tests[0],
		setup,
		teardown,
		initialize,
		cleanup,
	};
	return &suite;
}

