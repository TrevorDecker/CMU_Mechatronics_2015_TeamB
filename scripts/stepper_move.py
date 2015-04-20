import time
from pyBusPirateLite.SPI import *

# setup bus pirate for fast SPI mode
bp = SPI('/dev/tty.usbserial-A601ZXYJ', 115200)
bp.BBmode()
bp.enter_SPI()
bp.set_speed(SPISpeed._1MHZ)
bp.cfg_spi(SPICfg.OUT_TYPE)
bp.timeout(0.05)

# enable power
bp.cfg_pins(PinCfg.POWER)

while(True):
  # move in one direction
  # note that we need to toggle /CS every byte
  bp.CS_Low()
  bp.bulk_trans(1, [0x40])
  bp.CS_High()
  bp.CS_Low()
  bp.bulk_trans(1, [0x00])
  bp.CS_High()
  bp.CS_Low()
  bp.bulk_trans(1, [0x03])
  bp.CS_High()
  bp.CS_Low()
  bp.bulk_trans(1, [0xFF])
  bp.CS_High()
  print("moving 0x003FFF in direction 0")

  time.sleep(3)

  # move in other direction
  bp.CS_Low()
  bp.bulk_trans(1, [0x41])
  bp.CS_High()
  bp.CS_Low()
  bp.bulk_trans(1, [0x00])
  bp.CS_High()
  bp.CS_Low()
  bp.bulk_trans(1, [0x03])
  bp.CS_High()
  bp.CS_Low()
  bp.bulk_trans(1, [0xFF])
  bp.CS_High()
  print("moving 0x003FFF in direction 1")
