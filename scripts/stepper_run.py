import time
import sys
from pyBusPirateLite.SPI import *

if(len(sys.argv) < 3):
  print("Please specify a speed and direction to run at:")
  print("stepper_run.py speed direction")
  sys.exit(-1)

# setup bus pirate for fast SPI mode
bp = SPI('/dev/tty.usbserial-A601ZXYJ', 115200)
bp.BBmode()
bp.enter_SPI()
bp.set_speed(SPISpeed._1MHZ)
bp.cfg_spi(SPICfg.OUT_TYPE)
bp.timeout(0.05)

# enable power
bp.cfg_pins(PinCfg.POWER)

# read args
stepper_speed = abs(int(sys.argv[1]))
if(stepper_speed > 0xFFFFF):
  stepper_speed = 0xFFFFF
stepper_direction = int(sys.argv[2])

# stop by sending run at 0 speed command
# note that we need to toggle /CS every byte
bp.CS_Low()
bp.bulk_trans(1, [0x50|stepper_direction])
bp.CS_High()
bp.CS_Low()
bp.bulk_trans(1, [(stepper_speed >> 16) & 0xF])
bp.CS_High()
bp.CS_Low()
bp.bulk_trans(1, [(stepper_speed >> 8) & 0xFF])
bp.CS_High()
bp.CS_Low()
bp.bulk_trans(1, [(stepper_speed) & 0xFF])
bp.CS_High()
print("stepper set to run at 0x%x in direction %d" % (stepper_speed, stepper_direction))
