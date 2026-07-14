# Remote-Controller 🎮
A programmable handheld remote compatible with both gaming consoles and unmanned aerial vehicles.

## Hardware Required

|Sr no. | Component | Quantity | Notes |
|---|---|---|---|
| 1 | Arduino Nano | 2 | 1 for transmitter, 1 for receiver |
| 2 | NRF24L01+PA+LNA module | 2 | Long-range variant with external antenna |
| 3 | Analog Joystick module | 2 | X/Y axis + push button |
| 4 | 3.7v Lithium ion battery | 2 | Power source for transmitter |
| 5 | Cell holder | 2 | Holds cells |
| 6 | Toggle Switch | 2 | To turn on/off transmitter and voltage reader |
| 7 | Perfboard | 2 | To place components and solder them |
| 8 | Pushbutton | 1 | Placed on transmitter |
| 9 | Buzzer | 1 | Used as an alarm on transmitter |
| 10 | White led  | 1 | Indicator that voltage reader is on | 
| 11 | Red led | 2 | Turns on when battery voltage level is low |
| 12 | 100μ Capacitor | 2 | To be placed between vcc and gnd of nrf module |
| 13 | nrf adapter | 2 | powers nrf module with steady voltage required |
| 14 | 220Ω resistor | 2 | Regulates current flow to prevent damage when illuminating red LEDs. | 
| 15 | 10kΩ resistor | 1 | turns on white led safely |
| 16 | lm256 buck converter | 2 | safely steps down voltage to 5v to turn on arduino nano |
