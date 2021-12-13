import utime
from neopixel import NeoPixel
from machine import Pin
import time

class Clock:
    def __init__(self, leds):
        self.leds = leds
        self.num_leds = 60
        self.led_pin = Pin(13, Pin.OUT)
        
    def get_time(self):
        time = []
        (year, month, mday, hour, minute, second, weekday, yearday) = utime.localtime()
        if hour > 12:
            hour = hour - 12
        print('time at boot is {}:{}:{}'.format(hour, minute, second))
        time = [hour, minute, second]
        
        return(time)
    
    def set_time(self, time):
        self.time = time
        
    def update_leds(self):
        now = self.get_time()
        
        hour = now[0]
        minute = now[1]
        second = now[2]
        
        for i in range(self.num_leds):
            self.leds[i] = (0, 0, 0)
        
        self.leds[hour] = (255, 255, 255)
        self.leds[hour-1] = (255, 255, 255)
        self.leds[hour+1] = (255, 255, 255)
        self.leds[minute] = (255, 0, 0)
        self.leds[second] = (0, 255, 255)
        self.leds.write()
        #self.led_pin.off()
        #time.sleep(0.0003)
    

