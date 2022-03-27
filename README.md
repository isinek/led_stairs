# LED Stairs
This is a weekend project with which you can transform your regular stairs
to colorful and interesting ones.

Mode 1:<br>
![mode1](https://media3.giphy.com/media/pCiAbg1STxCVZDqOvM/giphy.gif)

Mode 2:<br>
![mode2](https://media2.giphy.com/media/ZirmPwlMluUNjLOXdL/giphy.gif)

## Hardware
You will need:
 * LED strips
 * Controller
 * Sensors
 * Power source
 * Wires

### LED Strips
You will need one LED strip per step. Also, the number of LEDs depends on how
wide is each stair and how dense LED strip is.

In my case there are 15 stairs and I used WS2812B LED strip with a density of
30 LEDs/m. I've decided that's enough to cover around 80% of stair width with
LEDs, so I used 26 LEDs on each stair.

Optional, but I highly recommend to use aluminum profiles for LED strips with
light diffusers. If you plan to use different colors, or you have reflective
stairs (like I have), I would say that it is required.

### Controller
For controlling LED strips you can use Arduino/ESP/Raspberry Pi or something
else.

I had Arduino Nano at home, and it is just big enough for my stairs.
In some time I'll probably switch Arduino Nano for ESP32 that has more memory
and I'll be able to control it with phone and home assistant.

### Sensors
If you want a simple animation that will run when you power up stairs, you will
not need any sensors. I've used PIR sensor on top and on the bottom of the
stairs. It notices motion and triggers animation.

### Power Source
Depends on how many LEDs you need to power. In my case there's a total of 390
LEDs, 390 LEDs * 0.06A = 23.4A power source.

### Wires
There's no much to say, I used slim stranded wires. To hide wires use simple
wire channels.

### Scheme
Scheme is actually pretty basic. Connect all LED strips to power supply in
parallel (beginning of each LED strip directly to power supply).
Don't connect LED strips in series (the end of one LED strip to the beginning of
next one) because power drop will cause LEDs to not work properly.

Connect controler to power supply, but pay attention that LED strips and
controler MUST USE common GND. If you use same power supply for LED strips and
controler as I did, then you should not have any issues.

![scheme](https://i.imgur.com/oSfle5k.png)

## Software
All software is written in Arduino studio.
This project depends on FastLED.h, so make sure that you have library downloaded
in Arduino studio.

Use defined values to configure number of stairs, LEDs, pins, sensors...
By default code works in "Mode 1". If you want to see the rainbow, use define
RAINBOW.
