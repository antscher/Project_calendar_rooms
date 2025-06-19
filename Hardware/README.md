# Hardware Components Selection

## ESP32-S2 Microcontroller : ESP32-S2 Dev kit from waveshare
- **Why this choice?**
  - Built-in WiFi capabilities for network connectivity
  - Low power consumption with deep sleep modes
  - Sufficient GPIO pins for e-ink display interface
  - Cost-effective solution for IoT applications
  - Native USB support for easy programming
  - Enough RAM for rendering the image before displaying it

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

## Power Considerations
- E-ink display only draws power during updates
- ESP32-S2 deep sleep mode < 10µA
- Expected battery life: 2-3 years between replacing battery
