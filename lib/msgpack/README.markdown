#MessagePack for embedded-c
###Ver 0.1.5

組み込み系C言語用のMessagePackライブラリ

##動作確認済みコンパイラ
* XC16 (PIC18F,24F,dsPIC)

##使用方法
###インストール（？）
1. msgpack-embedded-c/src/　以下のソースファイルを一緒にコンパイルする
2. msgpack-embedded-c/src/msgpack.h をインクルードする

###シリアライズ

	[serialize.c]
	#include	<stdio.h>
	#include	<stddef.h>	//size_t使用のため
	#include	"msgpack-embedded-c/src/msgpack.h"

	void main(void)
	{
		static	msgpack_packed	pk;
		size_t	i;

		initPackedMsgpack(&pk);		//パッカー初期化

		//[8, 3000, ["msgpack", -4]]というパケットを生成
		packArrayMsgpack(&pk, 3);	//3要素の配列
		packUnsignedCharMsgpack(&pk, 8);
		packUnsignedShortMsgpack(&pk, 3000);
		packArrayMsgpack(&pk,2);
		packRawMsgpack(&pk, 7, "msgpack");
		packSignedCharMsgpack(&pk, -4);

		printf("packet_size:%d\n", pk.size);	//シリアライズされたパケットのバイト数を表示
		
		for(i=0; i<pk.size; i++){
			printf("data[%d] : %x\n", i, *(pk.data + i));	//シリアライズ結果表示
		}
	}

###デシリアライズ

	[deserialize.c]
	#include	<stdio.h>
	#include	<stddef.h>	//size_t使用のため
	#include	"msgpack-embedded-c/src/msgpack.h"

	void	main(void)
	{
		static	msgpack_unpaker	upk;		//デシリアライズするデータ
		static	msgpack_unpacked	unpacked;	//デシリアライズされたデータ
		size_t	i;

		initUnpackerMsgpack(&upk);
		initUnpackedMsgpack(&unpacked);

		unsigned char	data;
		while( data = getc(strem) ){
			pushByteUnpackerMsgpack(data, &upk);	//デシリアライズ対象のデータを1バイトセット
		}

		if (unpackerNextMsgpack(&upk, &unpacked) == true) {
			printf("アンパック成功");
		}

		//デシリアライズされたデータにアクセス
		msgpack_object_type	type;
		type	= unpacked.data->type;		//タイプ取得(object.h::msgpack_object_type)
		
		switch(type) {
		case	MSGPACK_OBJECT_POSITIVE_INTEGER:
		{
			unsigned short data;
			data = (unsigned short)unpacked.data->val.u64;
			break;
		}
		//的な感じで取得した型に応じてキャストしてデータを取得
		}
	}


##現在の仕様・バグ
###仕様
* 小数点型にはたぶん対応してません
* Boolean型、アンパックできるけどパックできない

###バグ
* 特定の条件が揃うと、unpackでフリーズする(raw型の直後にarrayがくるとだめっぽい？)


##変更履歴
* Ver 0.1.5 2014/02/06
	+ packSignedXX()に正の数を渡すと、余計な値が後ろにひっつくのを修正

* Ver 0.1.4 2014/02/04
	+ packSignedXX()に正の数を渡しても大丈夫にした
	+ unpackerNextMsgpack()の戻り値を変更　状態が取得できるように

* Ver 0.1.3 2014/02/04
	+ READMEがきちんと更新されていなかったのを直しただけ

* Ver 0.1.2 2014/02/04
	+ 負の数がきちんとアンパックされるようになった

* Ver 0.1.1 2014/02/03  
	+ テスト環境の整備
	(テストフレームワーク PCUnitを用いてテストするように変更)
	+ 型チェックモードのときに、型以外の値がくるとハングアップしていたのを修正


* Ver 0.1 xx/xx/xx



