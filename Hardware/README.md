# Hardware Components Selection

## ESP32-S2 Microcontroller : ESP32-S2 Dev kit from waveshare
- **Why this choice?**
  - Built-in WiFi capabilities for network connectivity
  - Low power consumption with deep sleep modes
  - Sufficient GPIO pins for e-ink display interface
  - Cost-effective solution for IoT applications
  - Native USB support for easy programming
  - Enough RAM for rendering the image before displaying it

  Can be power supply between 10V and 1.8V theorically in reality it is needed to be superior to 2.65V

## Waveshare E-Ink Display : Spectra 7.3" from Waveshare
- **Why this choice?**
  - Ultra-low power consumption - only uses power when refreshing
  - Excellent readability in various lighting conditions
  - Maintains display without power
  - Available SPI interface for easy integration with ESP32
  - 6 colors 

## Battery Selection : Roomz display battery
- **Why not rechargeable Li-primary**
  - High energy density
  - Low self-discharge rate
  - Long cycle life
  - Safe for fire problems

  Normally the battery will stay really close to 3V during all it live cycle but a varation can cause effects.
  Capacity (%)	Voltage (V)
  100%	        3.0 – 3.2 V
  90%	          3.0 – 3.1 V
  80%	          2.95 – 3.1 V
  50%	          2.9 – 3.0 V
  20%	          2.8 – 2.9 V
  10%	          2.7 – 2.8 V
  0%          	~2.0 – 2.5 V

  Note : After testing with different input voltage, the results are : 
  - > 2.65V : work normally
  - between 2.65 and 2.4 : work but risk of losing is SPRAM
  - < 2.4 V : not working at all

  Conclusion : we can use even if we consider there is risk of malfounctionning at the end of life
  (Possibility utilising NVS memory but there is a limit in R/W cycle)

## Power Considerations
- E-ink display only draws power during updates
- ESP32-S2 deep sleep mode < 10µA
- Expected battery life: 2-3 years between replacing battery


## The PCB 

The pcb is made on Kicad
So you need it to open it (it is quite a simple design)

## The support of the cadre 

It is made in fusion 360, you have access to the stl to print the design
Use M3 screws to attach it

## The cadre

The cadre is made with inskape, it is a .svg
It is desin for wood of 3mm
It need to be cut (red lines) and engrave (blue lines)