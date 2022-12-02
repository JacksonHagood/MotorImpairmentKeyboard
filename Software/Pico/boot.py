import storage
import board, digitalio
import time

button = digitalio.DigitalInOut(board.GP2)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.UP

if button.value:
   storage.disable_usb_drive()

led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT

for i in range(10):
    led.value = not led.value
    time.sleep(0.5)