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
$Comp
L Switch:SW_DPST SW?
U 1 1 608D4BE4
P 5700 3725
AR Path="/600CEB9B/608D4BE4" Ref="SW?"  Part="1" 
AR Path="/608D4BE4" Ref="SW1"  Part="1" 
F 0 "SW1" H 5700 3350 50  0000 C CNN
F 1 "SW_DPST" H 5700 3500 50  0000 C CNN
F 2 "j_lib:NE18-2P" H 5700 3725 50  0001 C CNN
F 3 "~" H 5700 3725 50  0001 C CNN
	1    5700 3725
	-1   0    0    1   
$EndComp
Wire Wire Line
	6300 3625 5900 3625
Wire Wire Line
	5500 3625 5225 3625
Wire Wire Line
	6300 3825 5900 3825
Wire Wire Line
	5500 3825 4850 3825
$Comp
L Mechanical:MountingHole H1
U 1 1 608C89C4
P 5400 4975
F 0 "H1" H 5500 5021 50  0000 L CNN
F 1 "MountingHole" H 5500 4930 50  0001 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_ISO7380_Pad" H 5400 4975 50  0001 C CNN
F 3 "~" H 5400 4975 50  0001 C CNN
	1    5400 4975
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 608C8BC2
P 5400 5225
F 0 "H2" H 5500 5271 50  0000 L CNN
F 1 "MountingHole" H 5500 5180 50  0001 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_ISO7380_Pad" H 5400 5225 50  0001 C CNN
F 3 "~" H 5400 5225 50  0001 C CNN
	1    5400 5225
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 4025 4850 4025
$Comp
L Connector:Conn_01x05_Male J?
U 1 1 608D4BF2
P 4650 3825
AR Path="/600CEB9B/608D4BF2" Ref="J?"  Part="1" 
AR Path="/608D4BF2" Ref="J2"  Part="1" 
F 0 "J2" H 4622 3849 50  0000 R CNN
F 1 "Conn_01x05_Male" H 4622 3758 50  0001 R CNN
F 2 "Connector_Molex:Molex_KK-396_A-41791-0005_1x05_P3.96mm_Vertical" H 4650 3825 50  0001 C CNN
F 3 "~" H 4650 3825 50  0001 C CNN
	1    4650 3825
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Male J?
U 1 1 608D4BEC
P 6500 3825
AR Path="/600CEB9B/608D4BEC" Ref="J?"  Part="1" 
AR Path="/608D4BEC" Ref="J1"  Part="1" 
F 0 "J1" H 6608 4206 50  0000 C CNN
F 1 "Conn_01x05_Male" H 6608 4115 50  0001 C CNN
F 2 "Connector_Molex:Molex_KK-396_A-41791-0005_1x05_P3.96mm_Vertical" H 6500 3825 50  0001 C CNN
F 3 "~" H 6500 3825 50  0001 C CNN
	1    6500 3825
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4925 3625 4850 3625
$Comp
L Mechanical:MountingHole H3
U 1 1 608D3BC9
P 5800 4975
F 0 "H3" H 5900 5021 50  0000 L CNN
F 1 "MountingHole" H 5900 4930 50  0001 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_ISO7380_Pad" H 5800 4975 50  0001 C CNN
F 3 "~" H 5800 4975 50  0001 C CNN
	1    5800 4975
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 608D3BCF
P 5800 5225
F 0 "H4" H 5900 5271 50  0000 L CNN
F 1 "MountingHole" H 5900 5180 50  0001 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_ISO7380_Pad" H 5800 5225 50  0001 C CNN
F 3 "~" H 5800 5225 50  0001 C CNN
	1    5800 5225
	1    0    0    -1  
$EndComp
$Comp
L Device:Fuse F1
U 1 1 608CAD34
P 5075 3625
F 0 "F1" V 4878 3625 50  0000 C CNN
F 1 "Fuse" V 4969 3625 50  0000 C CNN
F 2 "Fuse:Fuseholder_Cylinder-5x20mm_Schurter_0031_8201_Horizontal_Open" V 5005 3625 50  0001 C CNN
F 3 "~" H 5075 3625 50  0001 C CNN
	1    5075 3625
	0    -1   1    0   
$EndComp
Text Notes 7350 7525 0    79   ~ 16
JSMU - switch board P2
$EndSCHEMATC
