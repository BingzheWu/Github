import re
import os
def normal(fn):
    r=open(fn,'r')
    for line in r:
        if 'service_id' in line:
            continue
        
