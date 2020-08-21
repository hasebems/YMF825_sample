# YMF825Board Sample Module

## About this Sample Module

This is a software module for using YMF825 as a MIDI tone generator. It supports the following MIDI Commands.
+ Note On / Note Off
+ Program Change
+ Control Change #1
+ Control Change #7
+ Control Change #64
+ Pitch Bend
+ System Exclusive(YMF825 Tone Data)

## How to run on Arduino

+ Create a folder and copy all files in /common and files in /arduino to the folder.
+ Open the .ino file from Arduino IDE.
+ Each file will appear on the tab area, after loading. Verify and Upload as is, Arduino will work.
+ ymf825board_sample2.ino is a sketch that automatically plays ascending semitones for an octave.

## How to run on Raspberry Pi

+ Requires the bcm2835 library.
+ (If note installed)Install the bcm2835 library.
+ Please configure setting of makefile so that all files in /common and files in /raspi are compiled.


## Module Interface
| Function Name | details | When it's called | include file |
|---|---|---|---|
|initSPI()|initialize SPI|in an application initialization section|fmsd1.h|
|initSD1()|initialize YMF825(SD1)|in an application initialization section(after initSPI())|fmsd1.h|
|Fmdriver_init()|initialize the module|after initSD1()|fmif.h|
|Fmdriver_sendMidi()|send MIDI messages to the module|when it recieves a MIDI message|fmif.h|

+ In the case of Arduino, please wrap '#include fmif.h' in 'extern "C"{}'.


## このサンプルについて

本サンプルプログラムは、YMF825をMIDI音源化するためのソフトウェアモジュールです。以下のMIDI Commandに対応しています。
+ Note On / Note Off
+ Program Change
+ Control Change #1
+ Control Change #7
+ Control Change #64
+ Pitch Bend
+ System Exclusive(YMF825音色データ)

## Arduinoでの使い方

+ 開発用のフォルダを作り、そこに /common 内のファイルと、 /arduino 内のファイルを全てそのフォルダにコピーします。
+ その状態で、Arduino IDE から .ino ファイルを開きます。
+ 正常に読み込めたら、各ファイルがタブ上に現れます。そのまま検証と書き込みを行えば、Arduinoが動作します。
+ ymf825board_sample2.ino は半音単位で1octaveを自動に発音するプログラムです。


## Raspberry Piでの使い方

+ bcm2835ライブラリの使用が前提となっていますので、bcm2835ライブラリをインストールしてください。
+ /common 内のファイルと、/raspi 内のファイルが全部コンパイルされるように、makefileの設定を行ってください。


## Module Interface
| 関数名 | 処理内容 | コールするタイミング | include file |
|---|---|---|---|
|initSPI()|SPIの初期化|アプリの初期化処理|fmsd1.h|
|initSD1()|YMF825(SD1)の初期化|アプリの初期化処理(initSPI()の後)|fmsd1.h|
|Fmdriver_init()|このモジュールの初期化|initSD1()の後|fmif.h|
|Fmdriver_sendMidi()|このモジュールにMIDIを送る|MIDIメッセージ受信時|fmif.h|

+ Arduinoで使用する場合 '#include fmif.h' は 'extern "C"{}'で囲んでください。


