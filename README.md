# YM2149 adapter
This code is for interfacing a ym2149 (or ay-3-8910, AY-3-8912, or AY-3-8913).
The arduino code is based on code by [Florent Flament](https://github.com/FlorentFlament) ([the code](https://github.com/FlorentFlament/ym2149-test)).
My code is just an adaptation for the arduino mega.

## the wirring
The data lines of the soundchip get connected to port F of the arduino mega (A0-A7)
The clock gets connected to pin 11, reset to pin 10, BC1 to 22 and BDir to 23
Connect BC2 to 5v as well as Vss to 5v and Vss to ground.
Put 1k resistors (or leave them out if you want atari st like sound) on all chanels (Analog Channel a,b,c) and connect them to together.
If you have done all of this, congratulations, you now have a (hopefully) working soundchip interface.

## the code
In the folder 'pc' is a processing script.
For that you will need [processing 3](https://processing.org/) (java based) and the librarys [drop](http://transfluxus.github.io/drop/) and Serial (installed through library manager).
Change the line 'String port = "COM10"' to the COM port of your arduino.
Now run the script, you can now drag'n drop a ym file in the new window.
If all is done correctly, you will now hear your tune.

## how it woks
(aka i want to do it different)
It's verry simple.
The arduino will listen for incomming serial messages.
It will then fill up a buffer with the data received.
When the buffer is full (16 bytes) it will push the buffer out to the chip.
To write your own music streamer you just have to stream the raw register dump data to the arduino and eh voilà, music.

## 'I don't have a arduino mega'
If you don't have a arduino mega use the original code from [Florent Flament](https://github.com/FlorentFlament/ym2149-test).
Look at his [blog posts](http://www.florentflament.com/blog/driving-ym2149f-sound-chip-with-an-arduino.html) if you wan't to know more.
I don't know if it uses the same transmission protocoll, but it might be compatible.
I couldn't get his python script to run, so I realy dont know.
