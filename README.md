# DiffPressute Unit

<img src="https://github.com/akita11/DifferentialPressureUNIT/blob/main/DiffPressureUnit.jpg" width="320px">

空気の動きも検出できるSensirion社の高感度差圧センサ[SDP810-125Pa](https://www.sensirion.com/jp/products/product-catalog/SDP810-125Pa/)で2つの口の差圧を計測し、Groveポートから計測値を送出します。計測値は搭載するATOM S3上のディスプレイで確認できます。計測されたデータは、Core2等で利用できます。（[使用例](https://twitter.com/akita11/status/1758277269104336898)）

## 設定・操作

ATOM S3のボタン（ディスプレイ面）で以下のように設定を変更できます

- シングルクリック: 画面に表示されるグラフの感度（測定値の10倍（初期値：白）→100倍（緑）→1000倍（水色）→戻る）
- ダブルクリック: データ送出周波数（20ms(50Hz)→100ms(10Hz)→5ms(200Hz)→戻る）※グラフの動く速さが変わります


## UIFlowでの使い方

<img src="https://github.com/akita11/DifferentialPressureUNIT/blob/main/UIFlow_sample.png" width="320px">

UIFlow用のカスタムブロックを用意してあります（現時点ではCore2専用ですがピン割当を変更することで他のCore Basic等でも利用可能）。

- Core2のPortAに、本UnitのGroveポート(ATOM S3上)からのGroveケーブルを接続します
- UIFlowの"Custom"の"Open *.m5b"から、UIFlow/DiffPressureUNIT.m5b を開く→Custom内に"DiffPressureUnit"が追加される
- UIFlow/DiffPressureUNIT_sample.m5f"を参考に利用できます
- （得られる数値と実際の圧力との関係は後述）


## UART通信プロトコル

- UARTプロトコル: 115200bps, N81
- データ形式: 計測値（-32768〜+32767:符号付き16bit）の文字列＋LF('\n')

この「計測値」は、SDP810-125Paから出力される計測値です。実際の圧力への換算式はデータシートにあり、「計測値 ÷ 240 [Pa]」となります（例：計測値で"240"が1Pa）。なおSDP810-125Paのデータシートによれば、ゼロ点精度は0.08Pa、ゼロ点再現性は0.04Paです。

## Author

Junichi Akita (akita@ifdl.jp, @akita11)





