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

for reg in range(0, 0x19):
  bp.CS_Low()
  bp.bulk_trans(1, [0x20|reg])
  bp.CS_High()
  bp.CS_Low()
  resp = bp.bulk_trans(1, [0x00])
  bp.CS_High()
  bp.CS_Low()
  resp += bp.bulk_trans(1, [0x00])
  bp.CS_High()
  bp.CS_Low()
  resp += bp.bulk_trans(1, [0x00])
  bp.CS_High()
  print("reg 0x%02x: %02x %02x %02x" % (reg, ord(resp[0]), ord(resp[1]), ord(resp[2])))

