#!/usr/bin/env python
from samplebase import SampleBase
import time

# Main function
if __name__ == "__main__":
    pulsing_colors = PulsingColors()
    if (not pulsing_colors.process()):
        pulsing_colors.print_help()
