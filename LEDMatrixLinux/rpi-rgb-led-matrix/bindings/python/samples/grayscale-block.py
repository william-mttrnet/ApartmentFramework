#!/usr/bin/env python
from samplebase import SampleBase
import time


class GrayscaleBlock(SampleBase):
    def __init__(self, *args, **kwargs):
        super(GrayscaleBlock, self).__init__(*args, **kwargs)

    def run(self):
        sub_blocks = 16
        width = self.matrix.width
        height = self.matrix.height
        x_step = max(1, width / sub_blocks)
        y_step = max(1, height / sub_blocks)
        count = 0

        while True:
            for y in range(0, height):
                for x in range(0, width):
                    self.matrix.SetPixel(x, y, x*3, y*4, y*4)
                    time.sleep(.001)
            
            for y in range(0, height):
                for x in range(0, width):
                    self.matrix.SetPixel(x, y, 0, 0, 0)
                    time.sleep(.001)
            
            for y in range(0, height):
                for x in range(0, width):
                    self.matrix.SetPixel(x, y, x*3, x*3, x*3)
                    time.sleep(.001)
            
            for y in range(0, height):
                for x in range(0, width):
                    self.matrix.SetPixel(x, y, 0, 0, 0)
                    time.sleep(.001)
                    
            for y in range(0, height):
                for x in range(0, width):
                    self.matrix.SetPixel(x, y, x*3, y*2, x*3)
                    time.sleep(.001)
            
            for y in range(0, height):
                for x in range(0, width):
                    self.matrix.SetPixel(x, y, 0, 0, 0)
                    time.sleep(.001)
                        
            
            for y in range(0, height):
                for x in range(0, width):
                    self.matrix.SetPixel(x, y, y*2, y*2, x*3)
                    time.sleep(.001)
            
            for y in range(0, height):
                for x in range(0, width):
                    self.matrix.SetPixel(x, y, 0, 0, 0)
                    time.sleep(.001)
            time.sleep(1)
# Main function
if __name__ == "__main__":
    grayscale_block = GrayscaleBlock()
    if (not grayscale_block.process()):
        grayscale_block.print_help()
