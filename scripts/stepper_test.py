from pyBusPirateLite.SPI import *

bp = SPI('/dev/tty.usbserial-A601ZXYJ', 115200)
bp.BBmode()
bp.enter_SPI()
bp.set_speed(SPISpeed._1MHZ)
bp.cfg_spi(SPICfg.OUT_TYPE)
bp.timeout(0.05)


bp.CS_Low()
resp = bp.bulk_trans(3, [0x2a, 0x00, 0x00])
bp.CS_High()
print " ".join(hex(ord(n)) for n in resp)

bp.CS_Low()
resp = bp.bulk_trans(3, [0xFF, 0xFF, 0xFF])
bp.CS_High()
print " ".join(hex(ord(n)) for n in resp)

bp.CS_Low()
resp = bp.bulk_trans(2, [0x36, 0x00])
bp.CS_High()
print " ".join(hex(ord(n)) for n in resp)


bp.CS_Low()
resp = bp.bulk_trans(4, [0x50, 0x00, 0x00, 0xFF])
bp.CS_High()
print " ".join(hex(ord(n)) for n in resp)


bp.CS_Low()
bp.CS_High()

