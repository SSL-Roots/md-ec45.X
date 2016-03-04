ASSERTマクロ
Ver 1.1.0

2013/01/29 20:13
石倉万希斗


1.概要
dsPICのライブラリに，assert()関数が標準で用意されていますが，
よくわからないけど使えませんでした．（たぶん容量不足）
そこで，自分で作りました．

3.使い方
 1.assert.cを，プロジェクトにぶちこみます．
 2.assert.hをインクルードするより前に，#define _DEBUG をしておきます．
 3.defineAssertPutsマクロを用いて，puts関数をassertに教えておきます
	例) defineAssertPuts( putsUart );
 3.assert.hをインクルードします
 4.ASSERT(条件文); という書式で使います．
	例) ASSERT( buf == 'a' );
 5.GRNもしくはRED(成功/失敗)，実行されたファイル名，行数が表示されます．

