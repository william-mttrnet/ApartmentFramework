import time
import spidev

class Apa102SpiDriver():
    def __init__(self, num_leds, brightness):
        # Led config stuff
        self.brightness = brightness
        self.num_leds = num_leds
        
        # There is only a single bus
        self.bus = 0
        
        # Can be one or zero, multiple chip selects
        self.cs = 0
        
        # Actual SPI driver class reference
        self.spi_driver = spidev.SpiDev()
 
        # Creating the SPI array that we send out instructions
        # for the APA102s
        self._led_array = None
        
    def begin(self):
        # Setting up the SPI driver
        self.spi_driver.open(self.bus, self.cs)
        self.spi_driver.max_speed_hz = 10000000
        self.spi_driver.bits_per_word = 8
        self.spi_driver.mode = 0b11
        
        # Setting up the array
        self._led_array = [0] * (self.num_leds * 4 + 8)
        
        # LED array init sequence
        for i in range(4):
            self._led_array[i] = 0
        
        # LED Array close sequence 
        for i in range(4):
            self._led_array[len(self._led_array) - (i+1)] = 8
        
        for i in range(self.num_leds):
            self.set_led(0, 0, 0, i)
        
        self.update()
    
    def set_led(self, r, g, b, i):
        led_place = i * 4
        self._led_array[led_place + 9] = b
        self._led_array[led_place + 10] = g
        self._led_array[led_place + 11] = r
        self._led_array[led_place + 8] = 255
        
    def update(self):
        self.spi_driver.xfer(bytearray(self._led_array))
        

led_driver = Apa102SpiDriver(492, 255)

led_driver.begin()

while(1):
    for i in range(492):
        led_driver.set_led(30, 30, 30, i)
        led_driver.update()
        time.sleep(.02)
    
    for i in range(492):
        led_driver.set_led(0, 0, 0, i)
        led_driver.update()
        time.sleep(.02)
        