This repository contains design details of JSMU - source measure unit.


## What is SMU?
In case you don't know what is SMU, take a look [here](https://en.wikipedia.org/wiki/Source_measure_unit)
Basically, it's glorified power supply, able to both source voltage (and measure current) or source current (and measure voltage), usually in wide range of voltages and currents. It usually works in four quadrants, meaning it's able to both sink and source power. When set to zero output voltage, SMU acts as ammeter and when set to zero current, acts as voltmeter.

## What is in this repository?
- BOM - Bill Of Material. Contains list of components and materials used in this device. Separated by PCBs.
- firmware - firmware for two microcontrollers running in JSMU
- mechanical - mechanical parts I designed for this SMU
- media - minimal amount of pictures
- pcb
-- pcb_gerber - gerber data in zip files, ready to be manufactured
-- pcb_ibom - interactive BOM files, helping when populating the boards, also helpful to get familiar with the project
-- pcb_kicad - PCB source files, made in Kicad 5.10
-- schematics_pdf - all schematics in PDF format, for easy viewing or printing

## What is JSMU?
JSMU is open source implementation of SMU, inspired by Keithley 236 and Dave Erickson's [DIY SMU](http://www.djerickson.com/diy_smu/index.html)

![](https://github.com/jaromir-sukuba/J-SMU/blob/master/media/IMG_9784.JPG)

Parameters:
- Voltage ranges 12 and 120V
- Current ranges 1uA, 10uA, 100uA, 1mA, 10mA, 100mA
- Minimal set voltage step - 1mV
- Minimal set current step - 100pA
- Voltage resolution - 100uV
- Current resolution - 1pA

JSMU is designed to work as standalone device, but can be connected to computer via USB, and controlled via simple commands in ASCII text form. SCPI commands are not yet implemented, but I'm strongly considering it.

More pictures can be found in [imgur gallery](https://imgur.com/a/rR8cIFG)

## FAQ
Q: I noticed you used AT90S4434, made in 1998 as controller for your analog board.
A: Yes, that is correct observation. Two reasons led me to this decision; first of all, I like to do weird design choices from a time to time. Let's call it design dissonances. Secondly, when this design was born (Winter2020/2021-Summer 2021) component crisis was quite strong and I was limited by what components were available. I tried to choose as much components as were available in my junkbox as possible. AT90S4434 can be replaced by AtMega8535 after minor source touchup and recompiling.

Q: dsPIC33FJ128GP306 is also weird choice here
A: Yes, again, I was fishing in my junkbox. Usually, most of open-source project go with STM32, but at the time of designing, majority of component suppliers had more-less zero stock of more common STM32's. Once the situation changes, I can think of respinning the D1 board for STM32 and port the code. I already did porting from MC689S08BG60 to dsPIC; perhaps I'll manage another port too.

Q: What is the point of using 14-segment alphanumeric display in 2021, when many test instruments are using graphic LCDs with touchscreens?
A: Apart from the fact I don't like touch screens on test instruments, I tried to keep the design in kin-of-similar shape than Keithley 236. It's a thing of personal taste.
