# arduino-multicell-battery-monitoring
collects voltage data from individual cells using internal 10-bit ADC  

# description
When analyzing old multi-cell battery packs this tool helps to find malicious cells by monitoring all individual cell voltages simultaneously - also during load. By finding and replacing these cells with a conspicious drop in voltage the battery should become more capable again.

# setup
I used an Arduino Uno and its internal ADC. (Not optimal regarding its 10 bit resolution) Apart from that there are no constraints, use an external ADC unit in combination with a noise free power supply - if possible.

As the internal 10-bit 6 channel ADC of the Uno can measure only absolute voltages from 0 - 5V, external voltage dividers have to be used. These should be selected in a way so that as much as possible of the ADC range can be used to not loose 'resolution', i.e. aim for the max voltage to be near 5V. (Applies also to other microcontrollers/external ADCs, although the respective logic voltage might be 3.3V) The factor by which the voltage is reduced has to be carefully measured externally (DMM) and adjusted for afterwards.

# how the software works
The code is array-based to be as dynamic as possible. In the current form only cells in series are supported, but using a two-dimensional array this could easily be adapted. 
The voltages are printed to the serial monitor and can then be copied to excel or similar to be graphed out. (Note that the current Arduino IDE 2.2.1 has this bug where copying everything from the serial monitor is not possible, the legacy version 1.8x works though)

# limitations
-  Readings can become noisy very fast
-  many analog inputs needed
