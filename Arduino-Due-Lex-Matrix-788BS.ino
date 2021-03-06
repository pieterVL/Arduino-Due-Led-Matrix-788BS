/*MIT License

Copyright (c) 2017 Pieter Van Leuven

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

/*pin led matrix -> arduino pin*/
byte p1=22;
byte p2=23;
byte p3=24;
byte p4=25;
byte p5=26;
byte p6=27;
byte p7=28;
byte p8=29;
byte p9=30;
byte p10=31;
byte p11=32;
byte p12=33;
byte p13=34;
byte p14=35;
byte p15=36;
byte p16=37;

byte high[8] = {p5,p2,p7,p1,p12,p8,p14,p9};
byte low[8] = {p16,p15,p11,p6,p10,p4,p3,p13};

//led matrix dot cords
int x=0,
    y=0;

int controlX = A9;
int controlY = A8;
int controlSw= 50;

byte width=8;
bool inverted = false;
bool sw_buttonDown = false;

byte loopCount=0;

void setup() {
  Serial.begin(9600);
  pinMode(controlSw,INPUT);
  digitalWrite(controlSw, HIGH);
  
  for(byte i=0; i<width;++i){
    //led matrix
     pinMode(high[i],OUTPUT);
  }
}
void loop() {
  //reading controls
  if(++loopCount%7==1){//only read inputs after 7 cycles, otherwise the speed is incontrolabble
    if(!digitalRead(controlSw)){
       if(!sw_buttonDown){
        sw_buttonDown = true;
        inverted = !inverted;
        }
    }else{
        sw_buttonDown = false;
    }
    //x and y
    short xVal = analogRead(controlX);
    short yVal = analogRead(controlY);
    if(xVal < 500 && x>0) --x;
    else if(xVal > 1000 && x<width-1) ++x;
    if(yVal > 1000 && y>0) --y;
    else if(yVal < 500 && y<width-1) ++y;
  }
  
  for(byte i=0; i<width;++i){
     digitalWrite(high[i],HIGH);
     for(byte j=0; j<width;++j){
        if(lightUp(i,j)){
          pinMode(low[j],OUTPUT);
          digitalWrite(low[j],LOW);
        }
     }
     //turning on
     delay(2);
     //turning off
     digitalWrite(high[i],LOW);
     for(byte j=0; j<width;++j){
        pinMode(low[j],INPUT);
     }
  }
}
bool lightUp(byte i, byte j){
  bool equal = i==x && j==y;
  return inverted ? !equal : equal;
}
