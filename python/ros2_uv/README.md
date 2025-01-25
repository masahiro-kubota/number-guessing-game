rosdepを使わないので、複数パッケージに対してrosdep installでまとめて依存をインストールすることができなくなってしまう。
ガチガチにバージョンを管理した方が良さそうなもの(pytorchとか)だけuvで管理して、READMEとかにuv syncするのを忘れないようにする必要がある。

シェルスクリプトをros2 run <package> <sh file>をpythonファイルでやっている感じ。
https://qiita.com/GesonAnko/items/510eeade1f8ada302b9b
