# Flocon

Directly inspired by [Jiří Praus - Arduinoflake! @ hackster.io](https://www.hackster.io/jiripraus/arduinoflake-139a82)

Here is mine:
![](https://github.com/Marcussacapuces91/Flocon/blob/master/images/flocon.gif?raw=true)

I change some details:
- no resistors -> using PWM to reduce power ;
- mesuring Vcc in case of battery (LiPo) discharge, then shutdown (sleep) device ;
- at the moment, no capacitiv touch to change the program (see [Remember](#remember) ).

## Licence
My own software under MIT Licence : https://opensource.org/licenses/MIT

Any issues, pull requests welcome.

## Remember
Pins A6 & A7 CAN NOT deliver current :-)

## References
- https://www.hackster.io/jiripraus/arduinoflake-139a82
- http://www.gammon.com.au/power
- https://provideyourown.com/2012/secret-arduino-voltmeter-measure-battery-voltage/
