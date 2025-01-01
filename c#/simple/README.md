```
dotnet run
```

Domain層でゲームの状態と設定を定義して、Business層でそれら活用してゲームを管理する。

Business層はPresentation層に依存しておらず、Interfaceにのみ依存している。

そのInterfaceを実装することでUIとそれらを管理するFactoryを生成している。

こうすることで依存関係の逆転ができていて、Business層の実装を知らずにPresentation層に追加実装ができる。

右から左に向かって依存の流れができている（InterfaceとGameManagerはまとめて1つ考える）。
![Qiita](class_mermaid.png "Qiita")
