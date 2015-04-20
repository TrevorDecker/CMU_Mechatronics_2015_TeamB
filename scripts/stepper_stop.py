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

# stop by sending run at 0 speed command
# note that we need to toggle /CS every byte
bp.CS_Low()
bp.bulk_trans(1, [0xA8])
bp.CS_High()
print("stepper stopped")
