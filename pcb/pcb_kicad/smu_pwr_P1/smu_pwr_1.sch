EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	4975 1425 4975 1750
Wire Wire Line
	4975 2075 4975 2400
Wire Wire Line
	4675 2075 4475 2075
Wire Wire Line
	4475 2075 4475 1425
Wire Wire Line
	4475 1425 4675 1425
Wire Wire Line
	4675 1750 4525 1750
Wire Wire Line
	4525 1750 4525 2400
Wire Wire Line
	4525 2400 4675 2400
$Comp
L Device:CP C3
U 1 1 5FFDBB1F
P 5225 1575
F 0 "C3" H 5343 1621 50  0000 L CNN
F 1 "390u" H 5343 1530 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D18.0mm_P7.50mm" H 5263 1425 50  0001 C CNN
F 3 "~" H 5225 1575 50  0001 C CNN
	1    5225 1575
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C4
U 1 1 5FFDCAE2
P 5225 2250
F 0 "C4" H 5350 2375 50  0000 L CNN
F 1 "390u" H 5350 2275 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D18.0mm_P7.50mm" H 5263 2100 50  0001 C CNN
F 3 "~" H 5225 2250 50  0001 C CNN
	1    5225 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5225 2400 4975 2400
Wire Wire Line
	4975 1425 5225 1425
Wire Wire Line
	5225 1725 5225 1900
Wire Wire Line
	5225 1900 4225 1900
Connection ~ 5225 1900
Wire Wire Line
	5225 1900 5225 2100
Wire Wire Line
	4475 1425 4300 1425
Connection ~ 4475 1425
Wire Wire Line
	4525 2400 4150 2400
Connection ~ 4525 2400
Connection ~ 5225 1425
Wire Wire Line
	5225 2400 5525 2400
Connection ~ 5225 2400
Wire Wire Line
	4875 4250 4875 4575
Wire Wire Line
	4875 4900 4875 5225
Wire Wire Line
	4575 4900 4375 4900
Wire Wire Line
	4375 4900 4375 4250
Wire Wire Line
	4375 4250 4575 4250
Wire Wire Line
	4575 4575 4425 4575
Wire Wire Line
	4425 4575 4425 5225
Wire Wire Line
	4425 5225 4575 5225
$Comp
L Device:CP C5
U 1 1 5FFE2285
P 5125 4400
F 0 "C5" H 5243 4446 50  0000 L CNN
F 1 "470u" H 5243 4355 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D13.0mm_P5.00mm" H 5163 4250 50  0001 C CNN
F 3 "~" H 5125 4400 50  0001 C CNN
	1    5125 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C6
U 1 1 5FFE228B
P 5125 5075
F 0 "C6" H 5243 5121 50  0000 L CNN
F 1 "470u" H 5243 5030 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D13.0mm_P5.00mm" H 5163 4925 50  0001 C CNN
F 3 "~" H 5125 5075 50  0001 C CNN
	1    5125 5075
	1    0    0    -1  
$EndComp
Wire Wire Line
	5125 5225 4875 5225
Wire Wire Line
	4875 4250 5125 4250
Wire Wire Line
	5125 4550 5125 4725
Connection ~ 5125 4725
Wire Wire Line
	5125 4725 5125 4925
Connection ~ 4375 4250
Connection ~ 4425 5225
Wire Wire Line
	5125 4250 5450 4250
Connection ~ 5125 4250
Wire Wire Line
	5125 5225 5450 5225
Connection ~ 5125 5225
$Comp
L Device:C C1
U 1 1 5FFE58C1
P 4450 2800
F 0 "C1" V 4198 2800 50  0000 C CNN
F 1 "1u" V 4289 2800 50  0000 C CNN
F 2 "Capacitor_THT:C_Rect_L16.5mm_W7.0mm_P15.00mm_MKT" H 4488 2650 50  0001 C CNN
F 3 "~" H 4450 2800 50  0001 C CNN
	1    4450 2800
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 5FFE5F36
P 4450 3400
F 0 "C2" V 4198 3400 50  0000 C CNN
F 1 "1u" V 4289 3400 50  0000 C CNN
F 2 "Capacitor_THT:C_Rect_L16.5mm_W7.0mm_P15.00mm_MKT" H 4488 3250 50  0001 C CNN
F 3 "~" H 4450 3400 50  0001 C CNN
	1    4450 3400
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 5FFE657B
P 4750 2800
F 0 "R1" V 4543 2800 50  0000 C CNN
F 1 "33R" V 4634 2800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P15.24mm_Horizontal" V 4680 2800 50  0001 C CNN
F 3 "~" H 4750 2800 50  0001 C CNN
	1    4750 2800
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5FFE68E6
P 4750 3400
F 0 "R2" V 4543 3400 50  0000 C CNN
F 1 "33R" V 4634 3400 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P15.24mm_Horizontal" V 4680 3400 50  0001 C CNN
F 3 "~" H 4750 3400 50  0001 C CNN
	1    4750 3400
	0    1    1    0   
$EndComp
Wire Wire Line
	4225 3100 4225 1900
Connection ~ 4225 1900
Wire Wire Line
	4300 3400 4150 3400
Wire Wire Line
	4150 3400 4150 2400
Connection ~ 4150 2400
Wire Wire Line
	4300 2800 4300 1425
Connection ~ 4300 1425
$Comp
L Device:D_Zener D13
U 1 1 5FFF091E
P 5600 2950
F 0 "D13" V 5554 3030 50  0000 L CNN
F 1 "15V" V 5645 3030 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 5600 2950 50  0001 C CNN
F 3 "~" H 5600 2950 50  0001 C CNN
	1    5600 2950
	0    1    1    0   
$EndComp
$Comp
L Device:D_Zener D14
U 1 1 5FFF0F7C
P 5600 3250
F 0 "D14" V 5554 3330 50  0000 L CNN
F 1 "15V" V 5645 3330 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 5600 3250 50  0001 C CNN
F 3 "~" H 5600 3250 50  0001 C CNN
	1    5600 3250
	0    1    1    0   
$EndComp
Wire Wire Line
	5525 3400 5600 3400
Wire Wire Line
	5525 2800 5600 2800
$Comp
L Device:CP C8
U 1 1 5FFF4693
P 6025 3250
F 0 "C8" H 6143 3296 50  0000 L CNN
F 1 "470u" H 6143 3205 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D13.0mm_P5.00mm" H 6063 3100 50  0001 C CNN
F 3 "~" H 6025 3250 50  0001 C CNN
	1    6025 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C7
U 1 1 5FFF5036
P 6025 2950
F 0 "C7" H 6143 2996 50  0000 L CNN
F 1 "470u" H 6143 2905 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D13.0mm_P5.00mm" H 6063 2800 50  0001 C CNN
F 3 "~" H 6025 2950 50  0001 C CNN
	1    6025 2950
	1    0    0    -1  
$EndComp
Connection ~ 5600 3100
Wire Wire Line
	5600 3100 6025 3100
Connection ~ 6025 3100
Wire Wire Line
	6025 3400 5600 3400
Connection ~ 5600 3400
Wire Wire Line
	5600 2800 6025 2800
Connection ~ 5600 2800
$Comp
L Connector:Conn_01x03_Male J3
U 1 1 600041B3
P 7800 1675
F 0 "J3" H 7772 1653 50  0000 R CNN
F 1 "Conn_01x03_Male" H 7772 1698 50  0001 R CNN
F 2 "Connector_Molex:Molex_KK-396_A-41791-0003_1x03_P3.96mm_Vertical" H 7800 1675 50  0001 C CNN
F 3 "~" H 7800 1675 50  0001 C CNN
	1    7800 1675
	-1   0    0    1   
$EndComp
Text Label 5550 1425 0    50   ~ 0
HV+
Text Label 5550 1900 0    50   ~ 0
HVG
Text Label 5525 2400 0    50   ~ 0
HV-
Text Label 6650 3400 0    50   ~ 0
15VO-
Text Label 6650 2800 0    50   ~ 0
15VO+
Text Label 6125 4250 0    50   ~ 0
+15V
Text Label 6125 4725 0    50   ~ 0
GND
Text Label 6125 5225 0    50   ~ 0
-15V
Text Label 7625 2900 2    50   ~ 0
+15V
Text Label 7625 2800 2    50   ~ 0
GND
Text Label 7625 2700 2    50   ~ 0
-15V
Text Label 7625 2150 2    50   ~ 0
15VO+
Text Label 7625 2350 2    50   ~ 0
15VO-
Text Label 7625 2250 2    50   ~ 0
HVG
Wire Wire Line
	3525 1700 3775 1700
Wire Wire Line
	3775 1700 3775 1425
Wire Wire Line
	3775 1425 4300 1425
Wire Wire Line
	3525 2100 3775 2100
Wire Wire Line
	3775 2100 3775 2400
Wire Wire Line
	3775 2400 4150 2400
Wire Wire Line
	3550 4625 3550 4250
Wire Wire Line
	3550 5225 4425 5225
Text Label 7600 1575 2    50   ~ 0
HV+
Text Label 7600 1775 2    50   ~ 0
HV-
$Comp
L Connector:Conn_01x03_Male J4
U 1 1 60089947
P 7825 2800
F 0 "J4" H 7797 2778 50  0000 R CNN
F 1 "Conn_01x03_Male" H 7797 2823 50  0001 R CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-03A_1x03_P2.54mm_Vertical" H 7825 2800 50  0001 C CNN
F 3 "~" H 7825 2800 50  0001 C CNN
	1    7825 2800
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x03_Male J2
U 1 1 6008A07C
P 7825 2250
F 0 "J2" H 7797 2228 50  0000 R CNN
F 1 "Conn_01x03_Male" H 7797 2273 50  0001 R CNN
F 2 "Connector_Molex:Molex_KK-396_A-41791-0003_1x03_P3.96mm_Vertical" H 7825 2250 50  0001 C CNN
F 3 "~" H 7825 2250 50  0001 C CNN
	1    7825 2250
	-1   0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D1
U 1 1 600BEFDB
P 4825 1425
F 0 "D1" H 4725 1275 50  0000 C CNN
F 1 "1N4007" H 4625 1350 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 4825 1250 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 4825 1425 50  0001 C CNN
	1    4825 1425
	-1   0    0    1   
$EndComp
Connection ~ 4975 1425
$Comp
L Diode:1N4007 D2
U 1 1 600BF759
P 4825 1750
F 0 "D2" H 4825 1533 50  0000 C CNN
F 1 "1N4007" H 4825 1624 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 4825 1575 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 4825 1750 50  0001 C CNN
	1    4825 1750
	-1   0    0    1   
$EndComp
$Comp
L Diode:1N4007 D3
U 1 1 600BFCC1
P 4825 2075
F 0 "D3" H 4950 2200 50  0000 C CNN
F 1 "1N4007" H 5050 2125 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 4825 1900 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 4825 2075 50  0001 C CNN
	1    4825 2075
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D4
U 1 1 600C0495
P 4825 2400
F 0 "D4" H 4825 2617 50  0000 C CNN
F 1 "1N4007" H 4825 2526 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 4825 2225 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 4825 2400 50  0001 C CNN
	1    4825 2400
	1    0    0    -1  
$EndComp
Connection ~ 4975 2400
Wire Wire Line
	4900 3400 5025 3400
$Comp
L Diode:1N4007 D11
U 1 1 600C21C7
P 5375 2800
F 0 "D11" H 5375 2583 50  0000 C CNN
F 1 "1N4007" H 5375 2674 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 5375 2625 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 5375 2800 50  0001 C CNN
	1    5375 2800
	-1   0    0    1   
$EndComp
Connection ~ 5025 3100
Connection ~ 5025 2800
Wire Wire Line
	5025 3100 5600 3100
Wire Wire Line
	4225 3100 5025 3100
Wire Wire Line
	5025 2800 5225 2800
Wire Wire Line
	4900 2800 5025 2800
$Comp
L Diode:1N4007 D9
U 1 1 600C424A
P 5025 2950
F 0 "D9" V 4979 3030 50  0000 L CNN
F 1 "1N4007" V 5070 3030 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 5025 2775 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 5025 2950 50  0001 C CNN
	1    5025 2950
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4007 D10
U 1 1 600C7ED4
P 5025 3250
F 0 "D10" V 4979 3330 50  0000 L CNN
F 1 "1N4007" V 5050 3325 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 5025 3075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 5025 3250 50  0001 C CNN
	1    5025 3250
	0    1    1    0   
$EndComp
Connection ~ 5025 3400
Wire Wire Line
	5025 3400 5225 3400
$Comp
L Diode:1N4007 D12
U 1 1 600C83CF
P 5375 3400
F 0 "D12" H 5550 3350 50  0000 C CNN
F 1 "1N4007" H 5550 3275 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 5375 3225 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 5375 3400 50  0001 C CNN
	1    5375 3400
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D5
U 1 1 600CA371
P 4725 4250
F 0 "D5" H 4750 4075 50  0000 C CNN
F 1 "1N4007" H 4700 4150 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 4725 4075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 4725 4250 50  0001 C CNN
	1    4725 4250
	-1   0    0    1   
$EndComp
Connection ~ 4875 4250
$Comp
L Diode:1N4007 D6
U 1 1 600CA82D
P 4725 4575
F 0 "D6" H 4750 4425 50  0000 C CNN
F 1 "1N4007" H 4775 4500 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 4725 4400 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 4725 4575 50  0001 C CNN
	1    4725 4575
	-1   0    0    1   
$EndComp
$Comp
L Diode:1N4007 D7
U 1 1 600CB13F
P 4725 4900
F 0 "D7" H 4850 5025 50  0000 C CNN
F 1 "1N4007" H 4950 4950 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 4725 4725 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 4725 4900 50  0001 C CNN
	1    4725 4900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D8
U 1 1 600CB9A7
P 4725 5225
F 0 "D8" H 4600 5100 50  0000 C CNN
F 1 "1N4007" H 4625 5025 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 4725 5050 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 4725 5225 50  0001 C CNN
	1    4725 5225
	1    0    0    -1  
$EndComp
Connection ~ 4875 5225
$Comp
L Mechanical:MountingHole H1
U 1 1 600EBEAB
P 3475 6000
F 0 "H1" H 3575 6000 50  0000 L CNN
F 1 "MountingHole" H 3575 5955 50  0001 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_ISO7380_Pad" H 3475 6000 50  0001 C CNN
F 3 "~" H 3475 6000 50  0001 C CNN
	1    3475 6000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 600EDE40
P 3475 6200
F 0 "H2" H 3575 6200 50  0000 L CNN
F 1 "MountingHole" H 3575 6155 50  0001 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_ISO7380_Pad" H 3475 6200 50  0001 C CNN
F 3 "~" H 3475 6200 50  0001 C CNN
	1    3475 6200
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 600EDFBA
P 3475 6400
F 0 "H3" H 3575 6400 50  0000 L CNN
F 1 "MountingHole" H 3575 6355 50  0001 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_ISO7380_Pad" H 3475 6400 50  0001 C CNN
F 3 "~" H 3475 6400 50  0001 C CNN
	1    3475 6400
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 600EE1EE
P 3475 6575
F 0 "H4" H 3575 6575 50  0000 L CNN
F 1 "MountingHole" H 3575 6530 50  0001 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_ISO7380_Pad" H 3475 6575 50  0001 C CNN
F 3 "~" H 3475 6575 50  0001 C CNN
	1    3475 6575
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Male J1
U 1 1 60108F3F
P 3325 1900
F 0 "J1" H 3433 2281 50  0000 C CNN
F 1 "Conn_01x05_Male" H 3433 2190 50  0001 C CNN
F 2 "Connector_Molex:Molex_KK-396_A-41791-0005_1x05_P3.96mm_Vertical" H 3325 1900 50  0001 C CNN
F 3 "~" H 3325 1900 50  0001 C CNN
	1    3325 1900
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J5
U 1 1 6011A09F
P 3350 4725
F 0 "J5" H 3322 4703 50  0000 R CNN
F 1 "Conn_01x03_Male" H 3322 4748 50  0001 R CNN
F 2 "Connector_Molex:Molex_KK-396_A-41791-0003_1x03_P3.96mm_Vertical" H 3350 4725 50  0001 C CNN
F 3 "~" H 3350 4725 50  0001 C CNN
	1    3350 4725
	1    0    0    1   
$EndComp
$Comp
L Regulator_Linear:L7815 U1
U 1 1 6012BFD3
P 5750 4250
F 0 "U1" H 5750 4492 50  0000 C CNN
F 1 "L7815" H 5750 4401 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 5775 4100 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 5750 4200 50  0001 C CNN
	1    5750 4250
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:L7915 U2
U 1 1 6012CD58
P 5750 5225
F 0 "U2" H 5750 5076 50  0000 C CNN
F 1 "L7915" H 5750 4985 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 5750 5025 50  0001 C CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/c9/16/86/41/c7/2b/45/f2/CD00000450.pdf/files/CD00000450.pdf/jcr:content/translations/en.CD00000450.pdf" H 5750 5225 50  0001 C CNN
	1    5750 5225
	1    0    0    -1  
$EndComp
Wire Wire Line
	5125 4725 5750 4725
Wire Wire Line
	5750 4550 5750 4725
Connection ~ 5750 4725
Wire Wire Line
	5750 4725 6125 4725
Wire Wire Line
	5750 4725 5750 4925
Wire Wire Line
	6050 4250 6125 4250
Wire Wire Line
	6050 5225 6125 5225
$Comp
L Device:CP C10
U 1 1 6013BE75
P 6125 5075
F 0 "C10" H 6250 5175 50  0000 L CNN
F 1 "22u" H 6250 5075 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 6163 4925 50  0001 C CNN
F 3 "~" H 6125 5075 50  0001 C CNN
	1    6125 5075
	1    0    0    -1  
$EndComp
Wire Wire Line
	6125 4925 6125 4725
$Comp
L Device:CP C9
U 1 1 6013E396
P 6125 4400
F 0 "C9" H 6243 4446 50  0000 L CNN
F 1 "22u" H 6243 4355 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 6163 4250 50  0001 C CNN
F 3 "~" H 6125 4400 50  0001 C CNN
	1    6125 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6125 4550 6125 4725
Connection ~ 6125 4725
$Comp
L Device:R R3
U 1 1 60153F1D
P 7150 4325
F 0 "R3" V 7050 4500 50  0000 C CNN
F 1 "22k" V 7050 4325 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0411_L9.9mm_D3.6mm_P15.24mm_Horizontal" V 7080 4325 50  0001 C CNN
F 3 "~" H 7150 4325 50  0001 C CNN
	1    7150 4325
	0    -1   1    0   
$EndComp
Text Label 7900 4225 0    50   ~ 0
HV+
Text Label 7900 4425 0    50   ~ 0
HV-
$Comp
L Relay:Fujitsu_FTR-F1C K1
U 1 1 60161E7D
P 7600 4425
F 0 "K1" H 7600 3908 50  0000 C CNN
F 1 "Fujitsu_FTR-F1C" H 7600 3999 50  0000 C CNN
F 2 "Relay_THT:Relay_DPDT_Fujitsu_FTR-F1C" H 7550 4025 50  0001 C CNN
F 3 "https://www.fujitsu.com/downloads/MICRO/fcai/relays/ftr-f1.pdf" H 7600 4425 50  0001 C CNN
	1    7600 4425
	-1   0    0    1   
$EndComp
$Comp
L Device:R R5
U 1 1 600CD093
P 7150 4525
F 0 "R5" V 7250 4650 50  0000 C CNN
F 1 "22k" V 7250 4500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0411_L9.9mm_D3.6mm_P15.24mm_Horizontal" V 7080 4525 50  0001 C CNN
F 3 "~" H 7150 4525 50  0001 C CNN
	1    7150 4525
	0    -1   1    0   
$EndComp
Text Label 6925 4525 2    50   ~ 0
HVG
Wire Wire Line
	6925 4525 7000 4525
Wire Wire Line
	7000 4525 7000 4325
Connection ~ 7000 4525
Wire Wire Line
	5225 1425 5550 1425
Wire Wire Line
	5225 1900 5550 1900
Wire Wire Line
	6125 4725 7300 4725
Wire Wire Line
	7300 4725 7300 4625
Wire Wire Line
	7900 4625 7900 5550
Wire Wire Line
	7900 5550 5125 5550
Wire Wire Line
	5125 5550 5125 5225
Connection ~ 6025 2800
Connection ~ 6025 3400
Connection ~ 6475 2800
Wire Wire Line
	6475 2800 6650 2800
Wire Wire Line
	6025 2800 6475 2800
$Comp
L Device:R R4
U 1 1 611789A3
P 6475 2950
F 0 "R4" H 6350 2950 50  0000 C CNN
F 1 "10k" H 6325 3025 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P15.24mm_Horizontal" V 6405 2950 50  0001 C CNN
F 3 "~" H 6475 2950 50  0001 C CNN
	1    6475 2950
	-1   0    0    1   
$EndComp
Wire Wire Line
	6475 3100 6025 3100
Wire Wire Line
	6025 3400 6475 3400
$Comp
L Device:R R6
U 1 1 6117E1A4
P 6475 3250
F 0 "R6" H 6350 3175 50  0000 C CNN
F 1 "10k" H 6325 3275 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P15.24mm_Horizontal" V 6405 3250 50  0001 C CNN
F 3 "~" H 6475 3250 50  0001 C CNN
	1    6475 3250
	-1   0    0    1   
$EndComp
Connection ~ 6475 3400
Wire Wire Line
	6475 3400 6650 3400
Connection ~ 6475 3100
Wire Wire Line
	3550 4250 4375 4250
Wire Wire Line
	3550 4725 5125 4725
Wire Wire Line
	3550 4825 3550 5225
Wire Wire Line
	3525 1900 4225 1900
Wire Notes Line
	3125 1050 3125 3650
Wire Notes Line
	3125 3650 7050 3650
Wire Notes Line
	7050 3650 7050 1050
Wire Notes Line
	7050 1050 3125 1050
Wire Notes Line
	3125 3775 3125 5700
Wire Notes Line
	3125 5700 8125 5700
Wire Notes Line
	8125 5700 8125 3775
Wire Notes Line
	8125 3775 3125 3775
Wire Notes Line
	7150 3650 8125 3650
Wire Notes Line
	8125 3650 8125 1050
Wire Notes Line
	8125 1050 7150 1050
Wire Notes Line
	7150 1050 7150 3650
Text Notes 3175 1150 0    50   ~ 0
Power amp high voltage supply, voltage sense floating supply
Text Notes 3175 3875 0    50   ~ 0
Main analog power supply, high voltage discharge relay
Wire Notes Line
	3125 6800 3950 6800
Wire Notes Line
	3950 6800 3950 5800
Wire Notes Line
	3950 5800 3125 5800
Wire Notes Line
	3125 5800 3125 6800
Text Notes 3150 5900 0    50   ~ 0
Mounting holes
Text Notes 7350 7525 0    79   ~ 16
JSMU - power board P1
$EndSCHEMATC
