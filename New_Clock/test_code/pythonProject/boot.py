# This file is executed on every boot (including wake-boot from deepsleep)
#import esp
#esp.osdebug(None)
#import webrepl
#webrepl.start()
import wifi_controller

print('booting')
#TODO currently don't need to connect to network because time on devkitc is accurate. Not sure how this will work on mini-1

#wifi_controller.connect()
