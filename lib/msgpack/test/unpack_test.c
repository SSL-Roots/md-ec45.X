#include "PCUnit/PCUnit.h"
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


static void test_unpacker(void)
{
	msgpack_unpacker	upkr;
	int	i;

	//初期化テスト
	initUnpackerMsgpack(&upkr);
	PCU_ASSERT_EQUAL(0, upkr.size);
	PCU_ASSERT_EQUAL(0, upkr.parsed);

	for (i=0; i<128; i++){
		pushByteUnpackerMsgpack((unsigned char)i, &upkr);
		PCU_ASSERT_EQUAL(i+1, upkr.size);	//データ数がきちんと増加しているか
		PCU_ASSERT_EQUAL(0, upkr.parsed);	//parsedが増加していないか
		PCU_ASSERT_EQUAL(i, upkr.data[i]);	//値がきちんと保存できているか
	}
	PCU_ASSERT_FALSE(pushByteUnpackerMsgpack(i, &upkr));	//オーバーフローしないか

	upkr.parsed	= 16;
	deleteReadByteUnpacker(&upkr);
	PCU_ASSERT_EQUAL(0, upkr.parsed);
	PCU_ASSERT_EQUAL(128-16, upkr.size);
	PCU_ASSERT_EQUAL(0x10, upkr.data[0]);
}


static void test_0_unpackerNextMsgpack(void)
{
	msgpack_unpacker	upkr;
	msgpack_unpacked	upkd;
	bool	retval;
	initUnpackerMsgpack(&upkr);
	initUnpackedMsgpack(&upkd);

	//[0x03, [0x10]] データセット
	pushByteUnpackerMsgpack(0x92, &upkr);
	pushByteUnpackerMsgpack(0x03, &upkr);
	pushByteUnpackerMsgpack(0x91, &upkr);
	pushByteUnpackerMsgpack(0x10, &upkr);

	retval	= unpackerNextMsgpack(&upkr, &upkd);
	PCU_ASSERT_TRUE(retval);
	PCU_ASSERT_EQUAL(MSGPACK_OBJECT_ARRAY, upkd.data->type);

	msgpack_object*	obj = upkd.data->via.array.ptr;
	PCU_ASSERT_EQUAL(MSGPACK_OBJECT_POSITIVE_INTEGER, obj[0].type);
	PCU_ASSERT_EQUAL(0x03, (unsigned char)obj[0].via.u64);

	PCU_ASSERT_EQUAL(MSGPACK_OBJECT_ARRAY, obj[1].type);

}


static void test_1_unpackerNextMsgpack(void)
{
	//パース途中でバッファが空になるパターン
	msgpack_unpacker	upkr;
	msgpack_unpacked	upkd;
	Err_unpackerNextMsgpack	retval;
	initUnpackerMsgpack(&upkr);
	initUnpackedMsgpack(&upkd);

	//[0x03, [0x10]] データセット
	pushByteUnpackerMsgpack(0x92, &upkr);
	pushByteUnpackerMsgpack(0x03, &upkr);
	retval	= unpackerNextMsgpack(&upkr, &upkd);
	PCU_ASSERT_EQUAL(UNPACKING_UNPACKER_NEXT_MSGPACK_, retval);	//まだ途中

	pushByteUnpackerMsgpack(0x91, &upkr);
	pushByteUnpackerMsgpack(0x10, &upkr);
	pushByteUnpackerMsgpack(0x92, &upkr);

	retval	= unpackerNextMsgpack(&upkr, &upkd);
	PCU_ASSERT_EQUAL(SUCCEEDED_UNPACKER_NEXT_MSGPACK_, retval);
	PCU_ASSERT_EQUAL(MSGPACK_OBJECT_ARRAY, upkd.data->type);
	PCU_ASSERT_EQUAL(2, upkd.data->via.array.size);

	msgpack_object*	obj = upkd.data->via.array.ptr;
	PCU_ASSERT_EQUAL(MSGPACK_OBJECT_POSITIVE_INTEGER, obj[0].type);
	PCU_ASSERT_EQUAL(0x03, (unsigned char)obj[0].via.u64);

	PCU_ASSERT_EQUAL(MSGPACK_OBJECT_ARRAY, obj[1].type);
	PCU_ASSERT_EQUAL(1, obj[1].via.array.size);

	msgpack_object*	data = obj[1].via.array.ptr;
	PCU_ASSERT_EQUAL(MSGPACK_OBJECT_POSITIVE_INTEGER, data[0].type);
	PCU_ASSERT_EQUAL(0x10, (unsigned char)data[0].via.u64);
}

static void test_2_unpackerNextMsgpack(void)
{
	//型データじゃないやつが来るパターン
	msgpack_unpacker	upkr;
	msgpack_unpacked	upkd;
	Err_unpackerNextMsgpack	retval;
	initUnpackerMsgpack(&upkr);
	initUnpackedMsgpack(&upkd);

	pushByteUnpackerMsgpack(0xc6, &upkr);
	pushByteUnpackerMsgpack(0x92, &upkr);

	retval	= unpackerNextMsgpack(&upkr, &upkd);	//へんちくりんなデータはパースできない
	PCU_ASSERT_EQUAL(FAILED_UNPACKER_NEXT_MSGPACK_, retval);

	pushByteUnpackerMsgpack(0x03, &upkr);
	pushByteUnpackerMsgpack(0x91, &upkr);
	pushByteUnpackerMsgpack(0x10, &upkr);
	retval	= unpackerNextMsgpack(&upkr, &upkd);	//へんちくりんなデータを弾いて、パースする
	PCU_ASSERT_EQUAL(SUCCEEDED_UNPACKER_NEXT_MSGPACK_, retval);

	PCU_ASSERT_EQUAL(MSGPACK_OBJECT_ARRAY, upkd.data->type);
	PCU_ASSERT_EQUAL(2, upkd.data->via.array.size);

	msgpack_object*	obj = upkd.data->via.array.ptr;
	PCU_ASSERT_EQUAL(MSGPACK_OBJECT_POSITIVE_INTEGER, obj[0].type);
	PCU_ASSERT_EQUAL(0x03, (unsigned char)obj[0].via.u64);

	PCU_ASSERT_EQUAL(MSGPACK_OBJECT_ARRAY, obj[1].type);
	PCU_ASSERT_EQUAL(1, obj[1].via.array.size);

	msgpack_object*	data = obj[1].via.array.ptr;
	PCU_ASSERT_EQUAL(MSGPACK_OBJECT_POSITIVE_INTEGER, data[0].type);
	PCU_ASSERT_EQUAL(0x10, (unsigned char)data[0].via.u64);
}



static void test_3_unpackerNextMsgpack(void)
{
	//負の数のアンパック
	msgpack_unpacker	upkr;
	msgpack_unpacked	upkd;
	Err_unpackerNextMsgpack	retval;
	initUnpackerMsgpack(&upkr);
	initUnpackedMsgpack(&upkd);

	pushByteUnpackerMsgpack(0xFF, &upkr);	//-1
	pushByteUnpackerMsgpack(0xF5, &upkr);	//-11
	pushByteUnpackerMsgpack(0xD0, &upkr);	//-36
	pushByteUnpackerMsgpack(-36, &upkr);
	pushByteUnpackerMsgpack(0xD1, &upkr);	//-46255
	pushByteUnpackerMsgpack(0x4B, &upkr);
	pushByteUnpackerMsgpack(0x51, &upkr);

	retval	= unpackerNextMsgpack(&upkr, &upkd);
	PCU_ASSERT_EQUAL(SUCCEEDED_UNPACKER_NEXT_MSGPACK_, retval);
	PCU_ASSERT_EQUAL(MSGPACK_OBJECT_NEGATIVE_INTEGER, upkd.data->type);
	PCU_ASSERT_EQUAL(-1, upkd.data->via.i64);

	retval	= unpackerNextMsgpack(&upkr, &upkd);
	PCU_ASSERT_EQUAL(SUCCEEDED_UNPACKER_NEXT_MSGPACK_, retval);
	PCU_ASSERT_EQUAL(MSGPACK_OBJECT_NEGATIVE_INTEGER, upkd.data->type);
	PCU_ASSERT_EQUAL(-11, upkd.data->via.i64);

	retval	= unpackerNextMsgpack(&upkr, &upkd);
	PCU_ASSERT_EQUAL(SUCCEEDED_UNPACKER_NEXT_MSGPACK_, retval);
	PCU_ASSERT_EQUAL(MSGPACK_OBJECT_NEGATIVE_INTEGER, upkd.data->type);
	PCU_ASSERT_EQUAL(-36, upkd.data->via.i64);

	retval	= unpackerNextMsgpack(&upkr, &upkd);
	PCU_ASSERT_EQUAL(SUCCEEDED_UNPACKER_NEXT_MSGPACK_, retval);
	PCU_ASSERT_EQUAL(MSGPACK_OBJECT_NEGATIVE_INTEGER, upkd.data->type);
	PCU_ASSERT_EQUAL(-46255, upkd.data->via.i64);
}



PCU_Suite *unpack_test_suite(void)
{
	static PCU_Test tests[] = {
		PCU_TEST(test_unpacker),
		PCU_TEST(test_0_unpackerNextMsgpack),
		PCU_TEST(test_1_unpackerNextMsgpack),
		PCU_TEST(test_2_unpackerNextMsgpack),
		PCU_TEST(test_3_unpackerNextMsgpack),
	};
	static PCU_Suite suite = {
		"unpack_test", tests, sizeof tests / sizeof tests[0],
		setup,
		teardown,
		initialize,
		cleanup,
	};
	return &suite;
}

