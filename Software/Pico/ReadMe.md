# Pico Software

## Prerequisites

- Install CircuitPython environment on Rapsberry Pi Pico

## Components

### adafruit_hid

Formerly used to send MENA data from Pico to Pi.

### boot.py

Specifies code to run when the Pico boots. The green LED is currently set to flash 5 times on boot, and the Pico is set to not be recognized as a mass storage device by the host machine.  In order to make modifications to the code on the Pico, GPIO pin 2 must be grounded prior to booting. This prevents the pico from disabling the mass storage device mode. If unable to recognize as a mass storage device, [this link](https://learn.adafruit.com/getting-started-with-raspberry-pi-pico-circuitpython/circuitpython) provides instructions to wipe the Pico.

### code.py

CircuitPython searches for code.py prior to boot and immediately runs. Key scanning logic, MENA code generation, and sending of MENA data all occur in code.py.
