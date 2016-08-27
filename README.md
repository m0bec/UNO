# UNO

あのUNOです。東京理科大学ITCと東京理科大学神楽坂一丁目通信局の有志による共同制作

# 依存関係

- DxLib 3.16d以降
http://dxlib.o.oo7.jp/
- DxLibEx
https://github.com/Nagarei/DxLibEx

# 対応コンパイラ

- Visual Studio 2015 update 3
- Visual Studio 2015 Clang with Microsoft CodeGen(July 2016)

minw-gccとかmingw-clangでもきっと動く

Visual Studio 2013には対応していない

# 環境設定

VSでは環境変数が必要。

- ``DXLIB_ROOT`` : DxLibの``プロジェクトに追加すべきファイル_VC用``のパス
- ``DXLIBEX_ROOT`` : DxLibExのcloneしたリポジトリのパス

