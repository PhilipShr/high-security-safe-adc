# High security safe
## Vera Loewe und Philip Schwengsbier
Batteriemessung mit dem STM32 über den ADC. 
Damit der ADC durch die zu hohe Spannung nicht beschädigt wird, wird ein externer
Spannungsteiler verwendet, in dem ein 3K Ohm und ein 6,2K Ohm Widerstand eingebaut sind.
Für eine störungsfreie Spannungsversorgung des NUCLEO-F401RE Boards wird die Batterie an den VIN PIN
angeschlossen, da sich dahinter ein Spannungsregler befindet, der die Spannung für den STM 32 
herunterregelt. Damit der Spannungsregler richtig funktioniert, muss der Jumper J5 von Pin 1 und 2
auf Pin 2 und 3 gesteckt werden.

