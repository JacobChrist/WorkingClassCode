# Working Class Chess Timer

![]([/home/jacob/pontech/pontech/WorkingClassCode/WorkingClassChessTimer/images/IMG_20230527_210255.jpg](https://github.com/JacobChrist/WorkingClassCode/blob/master/WorkingClassChessTimer/images/IMG_20230527_210255.jpg?raw=true))
The motivation for this project came from spending too much time talking
to my friend Patrick when we should have been working. Patrick suggested 
that we needed a chess timer to keep track of who was talking more.  I 
ran with the idea and thought that we need a chess timer that has three
buttons. One for keeping grake of how much time we spend working and two
other buttons to keep track of who is talking. Additionally, we decided 
that we needed a rule that lets us know when we spend more than 10% of 
our time talking.  This rule triggers either a RED (too much talking) or
a GREEN (too much working) LED lights up.

## Prototype Demonstration
<iframe width="560" height="315" src="https://www.youtube.com/embed/DWMZuCngSyw" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

## The circuit:
  LCD Connections
   LCD VSS pin to ground
   LCD VCC pin to 5V
   LCD V0 pin to 3.3K Ohm R to ground (use 10K Ohm pot for more control)
   LCD RS pin to digital pin 12
   LCD R/W pin to ground
   LCD Enable pin to digital pin 11
   LCD D0-D3 pin No Connect
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD A pin to 5V
   LCD K pin to 390 Ohm R to ground

  Pico Pi W Inputs:
   GPIO 6 10k Ohm pull-up to Working Button
   GPIO 7 10k Ohm pull-up to Worker 1 Button
   GPIO 8 10k Ohm pull-up to Worker 2 Button
   GPIO 9 10k Ohm pull-up to Worker 3 Button

  Pico Pi W Outputs:
   GPIO 16 Get to work LED A
   GPIO 17 Okay to talk LED A
