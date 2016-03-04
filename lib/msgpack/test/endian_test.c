#include	"PCUnit/PCUnit.h"
#include	"endian.h"

static void	test_htonl(void)
{
	PCU_ASSERT_EQUAL(0x78563412, htonl(0x12345678));
}

static void	test_htonll(void)
{
	PCU_ASSERT_EQUAL(0xEFCDAB8967452301, htonll(0x0123456789ABCDEF));
}


/* --- suite --- */
PCU_Suite	*endian_test_suite(void)
{
	static PCU_Test tests[] = {
		{ "test_htonl", test_htonl },
		PCU_TEST(test_htonll),
	};
	static PCU_Suite	suite = {"Endian_Test", tests, sizeof(tests)/sizeof(tests[0])};
	return	&suite;
}