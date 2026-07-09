# ESP32 Music Keyboard
A simple electronic music keyboard built using an ESP32. 
The device allows users to play notes using physical pushbuttons, switch octaves using a potentiometer, and provides LED feedback and startup & shutdown audio sequences. 

## Demonstration: 
<video src="https://github.com/user-attachments/assets/fab6a7f1-baaf-4898-b4c3-22661c3728d6"
controls
style="max-width: 500px; width: 100%; display: block; margin: 10px 0;">
</video>

<video src="https://github.com/user-attachments/assets/99546f6b-2acd-4c57-a835-44497ccba4ea"
controls
style="max-width: 500px; width: 100%; display: block; margin: 10px 0;">
</video>

## Features: 
- 8-button playable musical keyboard
- 3-octave switching using potentiometer
- LED indicator for current octave 
- On/Off toggle
- Startup and shutdown audio sequences 

## How it works:
1. Continuously scans all button inputs 
2. Identifies which button is currenly pressed
3. Uses a lookup table to map musical notes to base frequencies. 
4. Reads the potentiometer to determine octave selection
5. Updates LED indicators to reflect the current octave state
6. Applies octave scaling (0.5×, 1×, 2×) to the base frequency. 
7. Outputs the final frequency using PWM (LEDC) to a passive buzzer / speaker
8. Pressing the power button plays a fixed startup/shutdown  music before turning the device on/off

## Hardware used: 
- ESP32 microcontroller
- Passive Buzzer (later replaced with small speaker due to component failure)
- 9 pushbuttons
- Potentiometer
- 3 LEDs 

During development, the original passive buzzer got damaged and I replaced it with a small speaker, powered it by batteries, driven through a transistor circuit..  
