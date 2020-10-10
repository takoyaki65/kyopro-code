# kyopro-code
競技プログラミングで書いたコードを記録するレポジトリ

[template.cpp](template.cpp)のvectors構文は、
kimiyukiさんのを使うことにしました。本当にありがとうございます。

[ACM-ICPC 2016 国内予選 D: ダルマ落とし うさぎ小屋](https://kimiyuki.net/writeup/algo/etc/icpc-2016-domestic-d/)

# メモ
- 非再帰拡張ユークリッドの互除法についてはこの記事がわかりやすかった
    - [超わかりやすい拡張ユークリッドの互除法](https://qnighy.hatenablog.com/entry/20091230/1262173513)
    - [拡張ユークリッド互除法を非再帰ベースで理解する (C++)](https://noshi91.hatenablog.com/entry/2019/04/01/184957)
    - [拡張 Euclid の互除法による逆元計算](https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a#3-5-%E6%8B%A1%E5%BC%B5-euclid-%E3%81%AE%E4%BA%92%E9%99%A4%E6%B3%95%E3%81%AB%E3%82%88%E3%82%8B%E9%80%86%E5%85%83%E8%A8%88%E7%AE%97)
    これについては、上記の二つの記事のように's=a\*sx+b\*sy'と't=a\*tx+b\*ty'の二つの式をたてているが、sをaに、tをb、そして、sxをu,txをvとしている。sy,tyについては、常に(1,0)->(0,1)->...と交互に変化していくだけなので、いらない。