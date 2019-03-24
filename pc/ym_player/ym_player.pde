import drop.*;
import processing.serial.*;

SDrop drop;
Serial serial;
String port = "COM10";
boolean error;
boolean loaded;
int offset = 4;
byte[] in;
int frames;
void setup() {
  size(400, 400);
  frameRate(30);
  drop = new SDrop(this);
  serial = new Serial(this, port, 250000);
  frameRate(50);
}
void draw() {
  background(255);
  textAlign(CENTER, CENTER);
  noStroke();
  fill(0);
  if (error) {
    text("that's not a file...", width/2, height/2);
  } else {
    text("drag file in window to send", width/2, height/2);
  }
  text("current port:"+port, width/2, height/4*3);
  if (loaded) {
    for (int i = 0; i < 14; i++) {
      int adress = 4+(frames*i)+offset;
      if (adress < in.length) {
        serial.write(in[adress]);
      }
    }
    serial.write(0x00);
    serial.write(0x00);
    offset++;
  }
}

void dropEvent(DropEvent theDropEvent) {
  if (theDropEvent.isFile()) {
    in = loadBytes(theDropEvent.file());
    println(in.length);
    println("frames:"+(in.length-4)/14);
    frames = (in.length-4)/14;
    offset = 4;
    loaded = true;
  } else {
    error = true;
  }
}
