# A simple Arduino-based MIDI controller

## Shopping list
* Sparkfun Pro Micro (or similar)
* OLED display with SSD1306 controller
* 2 pcs. CD4051 multiplexer ICs
* 3 pcs. 10K potentiometer
* some buttons of your choice
* optional: custom pcb

## Introduction

Main goal was to design a very compact MIDI controller for controlling the lighting from my mobile dj setup.
The controller should fit into a standard 19" rack slot with a height of one rack unit. I'm using DASLIGHT as DMX controlling software
(which is full of bugs, but runs quite stable once you're finished programming). I wanted to have some big action buttons for strobe, blinder, bpm an some pre-defined scenes.
Additionally I needed some buttons for changing color chasers, movements and special effects (e.g. switching the laser or uv leds on my KLS Laser Bar).
For controlling speeds and master dimmer I used simple potentiometers (there's no space for big faders available).
For future use I integrated a small OLED display. My ideas are to visualize the current sent MIDI note or to provide some feedback from the controlling software (we'll see...).

