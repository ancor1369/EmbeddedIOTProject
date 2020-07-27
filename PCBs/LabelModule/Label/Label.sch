EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Label Main"
Date ""
Rev "1"
Comp "Bits in action"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L PowerManagement:TPS61090RSAR U?
U 1 1 5F14CED7
P 3050 1350
F 0 "U?" H 3075 2065 50  0000 C CNN
F 1 "TPS61090RSAR" H 3075 1974 50  0000 C CNN
F 2 "" H 3100 1450 50  0001 C CNN
F 3 "" H 3100 1450 50  0001 C CNN
	1    3050 1350
	1    0    0    -1  
$EndComp
$Comp
L pspice:INDUCTOR L?
U 1 1 5F14E60C
P 2000 1000
F 0 "L?" H 2000 1215 50  0000 C CNN
F 1 "VLC5045" H 2000 1124 50  0000 C CNN
F 2 "" H 2000 1000 50  0001 C CNN
F 3 "~" H 2000 1000 50  0001 C CNN
	1    2000 1000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F14F852
P 600 1500
F 0 "C?" H 715 1546 50  0000 L CNN
F 1 "C" H 715 1455 50  0000 L CNN
F 2 "" H 638 1350 50  0001 C CNN
F 3 "~" H 600 1500 50  0001 C CNN
	1    600  1500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F14FE73
P 1000 1500
F 0 "C?" H 1115 1546 50  0000 L CNN
F 1 "C" H 1115 1455 50  0000 L CNN
F 2 "" H 1038 1350 50  0001 C CNN
F 3 "~" H 1000 1500 50  0001 C CNN
	1    1000 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F1506FC
P 1400 1400
F 0 "R?" H 1470 1446 50  0000 L CNN
F 1 "1.87Mohm" H 1470 1355 50  0000 L CNN
F 2 "" V 1330 1400 50  0001 C CNN
F 3 "~" H 1400 1400 50  0001 C CNN
	1    1400 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F150DE7
P 1400 1850
F 0 "R?" H 1470 1896 50  0000 L CNN
F 1 "340k" H 1470 1805 50  0000 L CNN
F 2 "" V 1330 1850 50  0001 C CNN
F 3 "~" H 1400 1850 50  0001 C CNN
	1    1400 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 1450 2300 1450
Wire Wire Line
	2300 1450 2300 1600
Wire Wire Line
	2550 1600 2300 1600
Connection ~ 2300 1600
Wire Wire Line
	2300 1600 2300 1900
$Comp
L power:GND #PWR?
U 1 1 5F153C84
P 2300 1900
F 0 "#PWR?" H 2300 1650 50  0001 C CNN
F 1 "GND" H 2305 1727 50  0000 C CNN
F 2 "" H 2300 1900 50  0001 C CNN
F 3 "" H 2300 1900 50  0001 C CNN
	1    2300 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F154143
P 1400 2150
F 0 "#PWR?" H 1400 1900 50  0001 C CNN
F 1 "GND" H 1405 1977 50  0000 C CNN
F 2 "" H 1400 2150 50  0001 C CNN
F 3 "" H 1400 2150 50  0001 C CNN
	1    1400 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F154451
P 1000 1800
F 0 "#PWR?" H 1000 1550 50  0001 C CNN
F 1 "GND" H 1005 1627 50  0000 C CNN
F 2 "" H 1000 1800 50  0001 C CNN
F 3 "" H 1000 1800 50  0001 C CNN
	1    1000 1800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F15496C
P 600 1800
F 0 "#PWR?" H 600 1550 50  0001 C CNN
F 1 "GND" H 605 1627 50  0000 C CNN
F 2 "" H 600 1800 50  0001 C CNN
F 3 "" H 600 1800 50  0001 C CNN
	1    600  1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	600  1800 600  1650
Wire Wire Line
	1000 1650 1000 1800
Wire Wire Line
	1400 1550 1400 1600
Wire Wire Line
	1400 2000 1400 2150
Wire Wire Line
	1400 1250 1400 1200
Wire Wire Line
	1400 1200 1000 1200
Wire Wire Line
	600  1200 600  1350
Connection ~ 1400 1200
Wire Wire Line
	1000 1350 1000 1200
Connection ~ 1000 1200
Wire Wire Line
	1000 1200 600  1200
Wire Wire Line
	2250 1000 2550 1000
Wire Wire Line
	1750 1000 1400 1000
Wire Wire Line
	1400 1000 1400 1100
Wire Wire Line
	1400 1100 2550 1100
Connection ~ 1400 1100
Wire Wire Line
	1400 1100 1400 1200
Wire Wire Line
	1400 1600 1750 1600
Wire Wire Line
	1750 1600 1750 1300
Wire Wire Line
	1750 1300 2550 1300
Connection ~ 1400 1600
Wire Wire Line
	1400 1600 1400 1700
Text Label 2250 1200 0    50   ~ 0
Enable
Wire Wire Line
	2550 1200 2250 1200
$Comp
L Device:R R?
U 1 1 5F15B76B
P 4150 1350
F 0 "R?" H 4220 1396 50  0000 L CNN
F 1 "1.1Mohm" H 4220 1305 50  0000 L CNN
F 2 "" V 4080 1350 50  0001 C CNN
F 3 "~" H 4150 1350 50  0001 C CNN
	1    4150 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F15BD62
P 4150 1750
F 0 "R?" H 4220 1796 50  0000 L CNN
F 1 "200k" H 4220 1705 50  0000 L CNN
F 2 "" V 4080 1750 50  0001 C CNN
F 3 "~" H 4150 1750 50  0001 C CNN
	1    4150 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 1150 4150 1150
Wire Wire Line
	4150 1150 4150 1200
Wire Wire Line
	3600 1300 3750 1300
Wire Wire Line
	3750 1300 3750 1550
Wire Wire Line
	3750 1550 4150 1550
Wire Wire Line
	4150 1500 4150 1550
Connection ~ 4150 1550
Wire Wire Line
	4150 1550 4150 1600
$Comp
L power:GND #PWR?
U 1 1 5F15DEF4
P 4150 2050
F 0 "#PWR?" H 4150 1800 50  0001 C CNN
F 1 "GND" H 4155 1877 50  0000 C CNN
F 2 "" H 4150 2050 50  0001 C CNN
F 3 "" H 4150 2050 50  0001 C CNN
	1    4150 2050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F15E2F1
P 4900 1350
F 0 "C?" H 5015 1396 50  0000 L CNN
F 1 "2.2uF" H 5015 1305 50  0000 L CNN
F 2 "" H 4938 1200 50  0001 C CNN
F 3 "~" H 4900 1350 50  0001 C CNN
	1    4900 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F15E8C5
P 5350 1350
F 0 "C?" H 5465 1396 50  0000 L CNN
F 1 "100uF/6V" H 5465 1305 50  0000 L CNN
F 2 "" H 5388 1200 50  0001 C CNN
F 3 "~" H 5350 1350 50  0001 C CNN
	1    5350 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 1150 4900 1150
Wire Wire Line
	4900 1150 4900 1200
Connection ~ 4150 1150
Wire Wire Line
	4900 1150 5350 1150
Wire Wire Line
	5350 1150 5350 1200
Connection ~ 4900 1150
$Comp
L power:GND #PWR?
U 1 1 5F15F9FD
P 4900 1650
F 0 "#PWR?" H 4900 1400 50  0001 C CNN
F 1 "GND" H 4905 1477 50  0000 C CNN
F 2 "" H 4900 1650 50  0001 C CNN
F 3 "" H 4900 1650 50  0001 C CNN
	1    4900 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F15FCFD
P 5350 1650
F 0 "#PWR?" H 5350 1400 50  0001 C CNN
F 1 "GND" H 5355 1477 50  0000 C CNN
F 2 "" H 5350 1650 50  0001 C CNN
F 3 "" H 5350 1650 50  0001 C CNN
	1    5350 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 1500 4900 1650
Wire Wire Line
	5350 1500 5350 1650
Wire Wire Line
	3600 1600 3750 1600
Wire Wire Line
	3750 1600 3750 1550
Connection ~ 3750 1550
Wire Wire Line
	4150 1900 4150 2050
$Comp
L power:+BATT #PWR?
U 1 1 5F1710A3
P 1400 800
F 0 "#PWR?" H 1400 650 50  0001 C CNN
F 1 "+BATT" H 1415 973 50  0000 C CNN
F 2 "" H 1400 800 50  0001 C CNN
F 3 "" H 1400 800 50  0001 C CNN
	1    1400 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 800  1400 1000
Connection ~ 1400 1000
$Comp
L power:+3.3V #PWR?
U 1 1 5F173EEA
P 5350 950
F 0 "#PWR?" H 5350 800 50  0001 C CNN
F 1 "+3.3V" H 5365 1123 50  0000 C CNN
F 2 "" H 5350 950 50  0001 C CNN
F 3 "" H 5350 950 50  0001 C CNN
	1    5350 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 950  5350 1150
Connection ~ 5350 1150
$Comp
L Radiocontrolli:RC-CC1310R-XXX U?
U 1 1 5F1E30A7
P 3000 5100
F 0 "U?" H 3050 5765 50  0000 C CNN
F 1 "RC-CC1310R-XXX" H 3050 5674 50  0000 C CNN
F 2 "" H 2600 5650 50  0001 C CNN
F 3 "" H 2600 5650 50  0001 C CNN
	1    3000 5100
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:DMC3071LVT Q?
U 1 1 5F1F1763
P 6450 1600
F 0 "Q?" H 6555 1646 50  0000 L CNN
F 1 "IRLML6346TRPBF" H 6555 1555 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:TSOT-23" H 6400 1125 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/DMC3071LVT.pdf" H 6350 1600 50  0001 C CNN
	1    6450 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:L L?
U 1 1 5F1F9478
P 6450 1100
F 0 "L?" H 6503 1146 50  0000 L CNN
F 1 "COILCRAFT LPS3015-140MRC 3.4 OHM, 100 uH 240 mA" H 6503 1055 50  0000 L CNN
F 2 "" H 6450 1100 50  0001 C CNN
F 3 "~" H 6450 1100 50  0001 C CNN
	1    6450 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 1250 6450 1300
$Comp
L Diode:MBR0530 D?
U 1 1 5F1FB3E4
P 7450 2900
F 0 "D?" V 7496 2820 50  0000 R CNN
F 1 "MBR0530" V 7405 2820 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-123" H 7450 2725 50  0001 C CNN
F 3 "http://www.mccsemi.com/up_pdf/MBR0520~MBR0580(SOD123).pdf" H 7450 2900 50  0001 C CNN
	1    7450 2900
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C?
U 1 1 5F20BDF0
P 7450 1850
F 0 "C?" H 7565 1896 50  0000 L CNN
F 1 "50 v 1 uF" H 7565 1805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric" H 7488 1700 50  0001 C CNN
F 3 "~" H 7450 1850 50  0001 C CNN
	1    7450 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F20DC63
P 7450 2500
F 0 "C?" H 7565 2546 50  0000 L CNN
F 1 "50 V 1uF" H 7565 2455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric" H 7488 2350 50  0001 C CNN
F 3 "~" H 7450 2500 50  0001 C CNN
	1    7450 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 2650 7450 2700
Wire Wire Line
	6450 1300 6700 1300
Connection ~ 6450 1300
Wire Wire Line
	6450 1300 6450 1400
$Comp
L Device:C C?
U 1 1 5F210FED
P 6700 2300
F 0 "C?" H 6815 2346 50  0000 L CNN
F 1 "50 v 1 uF" H 6815 2255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric" H 6738 2150 50  0001 C CNN
F 3 "~" H 6700 2300 50  0001 C CNN
	1    6700 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 2150 6700 1300
Wire Wire Line
	6700 3200 7450 3200
Wire Wire Line
	7450 3200 7450 3050
$Comp
L Diode:MBR0530 D?
U 1 1 5F21312B
P 6700 3500
F 0 "D?" V 6746 3420 50  0000 R CNN
F 1 "MBR0530" V 6655 3420 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-123" H 6700 3325 50  0001 C CNN
F 3 "http://www.mccsemi.com/up_pdf/MBR0520~MBR0580(SOD123).pdf" H 6700 3500 50  0001 C CNN
	1    6700 3500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6700 3200 6700 3350
Connection ~ 6700 3200
$Comp
L power:GND #PWR?
U 1 1 5F2145EB
P 6700 3800
F 0 "#PWR?" H 6700 3550 50  0001 C CNN
F 1 "GND" H 6705 3627 50  0000 C CNN
F 2 "" H 6700 3800 50  0001 C CNN
F 3 "" H 6700 3800 50  0001 C CNN
	1    6700 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F214D16
P 7250 2350
F 0 "#PWR?" H 7250 2100 50  0001 C CNN
F 1 "GND" H 7255 2177 50  0000 C CNN
F 2 "" H 7250 2350 50  0001 C CNN
F 3 "" H 7250 2350 50  0001 C CNN
	1    7250 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F2150BC
P 7450 2050
F 0 "#PWR?" H 7450 1800 50  0001 C CNN
F 1 "GND" H 7455 1877 50  0000 C CNN
F 2 "" H 7450 2050 50  0001 C CNN
F 3 "" H 7450 2050 50  0001 C CNN
	1    7450 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 3650 6700 3800
$Comp
L Device:R R?
U 1 1 5F21DDA6
P 6450 2100
F 0 "R?" H 6520 2146 50  0000 L CNN
F 1 "0.47 1%" H 6520 2055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6380 2100 50  0001 C CNN
F 3 "~" H 6450 2100 50  0001 C CNN
	1    6450 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 1800 6450 1950
Text GLabel 5900 1600 0    50   Input ~ 0
GDR
Wire Wire Line
	5900 1600 6050 1600
$Comp
L power:+3.3V #PWR?
U 1 1 5F22B85B
P 6450 750
F 0 "#PWR?" H 6450 600 50  0001 C CNN
F 1 "+3.3V" H 6465 923 50  0000 C CNN
F 2 "" H 6450 750 50  0001 C CNN
F 3 "" H 6450 750 50  0001 C CNN
	1    6450 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 750  6450 950 
$Comp
L power:GND #PWR?
U 1 1 5F22DB2D
P 6450 2500
F 0 "#PWR?" H 6450 2250 50  0001 C CNN
F 1 "GND" H 6455 2327 50  0000 C CNN
F 2 "" H 6450 2500 50  0001 C CNN
F 3 "" H 6450 2500 50  0001 C CNN
	1    6450 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 2500 6450 2250
$Comp
L Device:R R?
U 1 1 5F2495C7
P 6050 1950
F 0 "R?" H 6120 1996 50  0000 L CNN
F 1 "100K" H 6120 1905 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5980 1950 50  0001 C CNN
F 3 "~" H 6050 1950 50  0001 C CNN
	1    6050 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 1600 6050 1800
Connection ~ 6050 1600
Wire Wire Line
	6050 1600 6150 1600
$Comp
L power:GND #PWR?
U 1 1 5F24AD9C
P 6050 2250
F 0 "#PWR?" H 6050 2000 50  0001 C CNN
F 1 "GND" H 6055 2077 50  0000 C CNN
F 2 "" H 6050 2250 50  0001 C CNN
F 3 "" H 6050 2250 50  0001 C CNN
	1    6050 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 2100 6050 2250
Text GLabel 6050 3200 0    50   Input ~ 0
RESE
Wire Wire Line
	6700 2450 6700 3200
Wire Wire Line
	6050 3200 6700 3200
Wire Wire Line
	7450 1750 7450 1800
Wire Wire Line
	6700 1300 7450 1300
Connection ~ 6700 1300
Wire Wire Line
	7450 2350 7250 2350
Wire Wire Line
	7450 2000 7450 2050
$Comp
L Diode:MBR0530 D?
U 1 1 5F1FA6D1
P 7450 1450
F 0 "D?" V 7496 1370 50  0000 R CNN
F 1 "MBR0530" V 7405 1370 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-123" H 7450 1275 50  0001 C CNN
F 3 "http://www.mccsemi.com/up_pdf/MBR0520~MBR0580(SOD123).pdf" H 7450 1450 50  0001 C CNN
	1    7450 1450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7450 1600 7450 1650
Text GLabel 7900 1650 2    50   Input ~ 0
PREVGH
Wire Wire Line
	7900 1650 7450 1650
Connection ~ 7450 1650
Wire Wire Line
	7450 1650 7450 1700
Text GLabel 7950 2700 2    50   Input ~ 0
PREVGL
Wire Wire Line
	7950 2700 7450 2700
Connection ~ 7450 2700
Wire Wire Line
	7450 2700 7450 2750
$Comp
L CrystalFontz:CrystalFontz24-pinCFAP-ePaper CONN?
U 1 1 5F2E7680
P 10350 4600
F 0 "CONN?" H 10325 5825 50  0000 C CNN
F 1 "CrystalFontz24-pinCFAP-ePaper" H 10325 5734 50  0000 C CNN
F 2 "" H 10200 5800 50  0001 C CNN
F 3 "" H 10200 5800 50  0001 C CNN
	1    10350 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR?
U 1 1 5F2E9BC7
P 11000 3700
F 0 "#PWR?" H 11000 3500 50  0001 C CNN
F 1 "GNDPWR" H 11004 3546 50  0000 C CNN
F 2 "" H 11000 3650 50  0001 C CNN
F 3 "" H 11000 3650 50  0001 C CNN
	1    11000 3700
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR?
U 1 1 5F2EA2C0
P 11000 5950
F 0 "#PWR?" H 11000 5750 50  0001 C CNN
F 1 "GNDPWR" H 11004 5796 50  0000 C CNN
F 2 "" H 11000 5900 50  0001 C CNN
F 3 "" H 11000 5900 50  0001 C CNN
	1    11000 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	10850 3600 11000 3600
Wire Wire Line
	11000 3600 11000 3700
Wire Wire Line
	10850 5900 11000 5900
Wire Wire Line
	11000 5900 11000 5950
Text GLabel 9500 3700 0    50   Input ~ 0
GDR
Wire Wire Line
	9500 3700 9800 3700
Text GLabel 9500 3800 0    50   Input ~ 0
RESE
Wire Wire Line
	9500 3800 9800 3800
$Comp
L Device:C C?
U 1 1 5F2F52B8
P 8250 4050
F 0 "C?" H 8365 4096 50  0000 L CNN
F 1 "50 V 1uF" H 8365 4005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric" H 8288 3900 50  0001 C CNN
F 3 "~" H 8250 4050 50  0001 C CNN
	1    8250 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 3900 9800 3900
$Comp
L Device:C C?
U 1 1 5F2F7CA0
P 8850 4150
F 0 "C?" H 8965 4196 50  0000 L CNN
F 1 "50 V 1uF" H 8965 4105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric" H 8888 4000 50  0001 C CNN
F 3 "~" H 8850 4150 50  0001 C CNN
	1    8850 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 4000 9800 4000
$Comp
L power:GND #PWR?
U 1 1 5F2F9888
P 8250 4300
F 0 "#PWR?" H 8250 4050 50  0001 C CNN
F 1 "GND" H 8255 4127 50  0000 C CNN
F 2 "" H 8250 4300 50  0001 C CNN
F 3 "" H 8250 4300 50  0001 C CNN
	1    8250 4300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F2F9E70
P 8850 4300
F 0 "#PWR?" H 8850 4050 50  0001 C CNN
F 1 "GND" H 8855 4127 50  0000 C CNN
F 2 "" H 8850 4300 50  0001 C CNN
F 3 "" H 8850 4300 50  0001 C CNN
	1    8850 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 4200 8250 4300
NoConn ~ 9650 3600
NoConn ~ 9650 4100
NoConn ~ 9650 4200
Wire Wire Line
	9650 3600 9800 3600
Wire Wire Line
	9650 4100 9800 4100
Wire Wire Line
	9650 4200 9800 4200
$Comp
L power:GND #PWR?
U 1 1 5F3044FD
P 9050 4300
F 0 "#PWR?" H 9050 4050 50  0001 C CNN
F 1 "GND" H 9055 4127 50  0000 C CNN
F 2 "" H 9050 4300 50  0001 C CNN
F 3 "" H 9050 4300 50  0001 C CNN
	1    9050 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 4300 9800 4300
Text GLabel 9450 4400 0    50   Input ~ 0
BUSY
Wire Wire Line
	9450 4400 9800 4400
Text GLabel 9450 4500 0    50   Input ~ 0
~RST
Wire Wire Line
	9450 4500 9800 4500
Text GLabel 9450 4600 0    50   Input ~ 0
D~C
Wire Wire Line
	9450 4600 9800 4600
Text GLabel 9450 4700 0    50   Input ~ 0
~CS
Wire Wire Line
	9450 4700 9800 4700
Text GLabel 9450 4800 0    50   Input ~ 0
SCK
Wire Wire Line
	9450 4800 9800 4800
Text GLabel 9450 4900 0    50   Input ~ 0
MOSI
Wire Wire Line
	9450 4900 9800 4900
$Comp
L Device:C C?
U 1 1 5F322EA8
P 9600 6100
F 0 "C?" H 9715 6146 50  0000 L CNN
F 1 "25 V 1uF" H 9715 6055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric" H 9638 5950 50  0001 C CNN
F 3 "~" H 9600 6100 50  0001 C CNN
	1    9600 6100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F3234B4
P 9600 6250
F 0 "#PWR?" H 9600 6000 50  0001 C CNN
F 1 "GND" H 9605 6077 50  0000 C CNN
F 2 "" H 9600 6250 50  0001 C CNN
F 3 "" H 9600 6250 50  0001 C CNN
	1    9600 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 5950 9600 5900
Wire Wire Line
	9600 5900 9800 5900
$Comp
L Device:C C?
U 1 1 5F330B45
P 9050 6100
F 0 "C?" H 9165 6146 50  0000 L CNN
F 1 "25 V 1uF" H 9165 6055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric" H 9088 5950 50  0001 C CNN
F 3 "~" H 9050 6100 50  0001 C CNN
	1    9050 6100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F331179
P 8500 6100
F 0 "C?" H 8615 6146 50  0000 L CNN
F 1 "25 V 1uF" H 8615 6055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric" H 8538 5950 50  0001 C CNN
F 3 "~" H 8500 6100 50  0001 C CNN
	1    8500 6100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F3315FE
P 7950 6100
F 0 "C?" H 8065 6146 50  0000 L CNN
F 1 "25 V 1uF" H 8065 6055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric" H 7988 5950 50  0001 C CNN
F 3 "~" H 7950 6100 50  0001 C CNN
	1    7950 6100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F33197F
P 6750 6100
F 0 "C?" H 6865 6146 50  0000 L CNN
F 1 "25 V 1uF" H 6865 6055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric" H 6788 5950 50  0001 C CNN
F 3 "~" H 6750 6100 50  0001 C CNN
	1    6750 6100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F331F3B
P 9050 6250
F 0 "#PWR?" H 9050 6000 50  0001 C CNN
F 1 "GND" H 9055 6077 50  0000 C CNN
F 2 "" H 9050 6250 50  0001 C CNN
F 3 "" H 9050 6250 50  0001 C CNN
	1    9050 6250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F33234C
P 8500 6250
F 0 "#PWR?" H 8500 6000 50  0001 C CNN
F 1 "GND" H 8505 6077 50  0000 C CNN
F 2 "" H 8500 6250 50  0001 C CNN
F 3 "" H 8500 6250 50  0001 C CNN
	1    8500 6250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F33258E
P 7950 6250
F 0 "#PWR?" H 7950 6000 50  0001 C CNN
F 1 "GND" H 7955 6077 50  0000 C CNN
F 2 "" H 7950 6250 50  0001 C CNN
F 3 "" H 7950 6250 50  0001 C CNN
	1    7950 6250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F3328A8
P 6750 6250
F 0 "#PWR?" H 6750 6000 50  0001 C CNN
F 1 "GND" H 6755 6077 50  0000 C CNN
F 2 "" H 6750 6250 50  0001 C CNN
F 3 "" H 6750 6250 50  0001 C CNN
	1    6750 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 5950 6750 5000
Wire Wire Line
	6750 5000 9500 5000
Wire Wire Line
	9800 5100 9500 5100
Wire Wire Line
	9500 5100 9500 5000
Connection ~ 9500 5000
Wire Wire Line
	9500 5000 9800 5000
$Comp
L power:+3.3V #PWR?
U 1 1 5F336E98
P 6750 5000
F 0 "#PWR?" H 6750 4850 50  0001 C CNN
F 1 "+3.3V" H 6765 5173 50  0000 C CNN
F 2 "" H 6750 5000 50  0001 C CNN
F 3 "" H 6750 5000 50  0001 C CNN
	1    6750 5000
	1    0    0    -1  
$EndComp
Connection ~ 6750 5000
Wire Wire Line
	9050 5950 9050 5700
Wire Wire Line
	9050 5700 9800 5700
Wire Wire Line
	8500 5950 8500 5500
Wire Wire Line
	8500 5500 9800 5500
Wire Wire Line
	7950 5950 7950 5400
Wire Wire Line
	7950 5400 9800 5400
$Comp
L Device:C C?
U 1 1 5F33EC0A
P 7400 6100
F 0 "C?" H 7515 6146 50  0000 L CNN
F 1 "25 V 1uF" H 7515 6055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric" H 7438 5950 50  0001 C CNN
F 3 "~" H 7400 6100 50  0001 C CNN
	1    7400 6100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F33F3F4
P 7400 6250
F 0 "#PWR?" H 7400 6000 50  0001 C CNN
F 1 "GND" H 7405 6077 50  0000 C CNN
F 2 "" H 7400 6250 50  0001 C CNN
F 3 "" H 7400 6250 50  0001 C CNN
	1    7400 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 5950 7400 5300
Wire Wire Line
	7400 5300 9800 5300
$Comp
L power:GND #PWR?
U 1 1 5F3420BB
P 7050 6250
F 0 "#PWR?" H 7050 6000 50  0001 C CNN
F 1 "GND" H 7055 6077 50  0000 C CNN
F 2 "" H 7050 6250 50  0001 C CNN
F 3 "" H 7050 6250 50  0001 C CNN
	1    7050 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 6250 7050 5200
Wire Wire Line
	7050 5200 9800 5200
Text GLabel 9450 5600 0    50   Input ~ 0
PREVGH
Text GLabel 9450 5800 0    50   Input ~ 0
PREVGL
Wire Wire Line
	9450 5800 9800 5800
Wire Wire Line
	9450 5600 9800 5600
Text GLabel 2950 6400 3    50   Input ~ 0
BUSY
Text GLabel 2850 6400 3    50   Input ~ 0
~RST
Text GLabel 2750 6400 3    50   Input ~ 0
DC
Text GLabel 2650 6400 3    50   Input ~ 0
~CS
Text GLabel 1850 5950 0    50   Input ~ 0
SCK
Text GLabel 1850 5850 0    50   Input ~ 0
MOSI
$Comp
L power:GND #PWR?
U 1 1 5F36BA30
P 1250 5650
F 0 "#PWR?" H 1250 5400 50  0001 C CNN
F 1 "GND" H 1255 5477 50  0000 C CNN
F 2 "" H 1250 5650 50  0001 C CNN
F 3 "" H 1250 5650 50  0001 C CNN
	1    1250 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 5650 1250 5550
Wire Wire Line
	1250 5550 2000 5550
$Comp
L power:GND #PWR?
U 1 1 5F36FC67
P 1200 4800
F 0 "#PWR?" H 1200 4550 50  0001 C CNN
F 1 "GND" H 1205 4627 50  0000 C CNN
F 2 "" H 1200 4800 50  0001 C CNN
F 3 "" H 1200 4800 50  0001 C CNN
	1    1200 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 4800 1200 4750
Wire Wire Line
	1200 4750 2000 4750
$Comp
L power:+3.3V #PWR?
U 1 1 5F3738E9
P 1700 5650
F 0 "#PWR?" H 1700 5500 50  0001 C CNN
F 1 "+3.3V" V 1715 5778 50  0000 L CNN
F 2 "" H 1700 5650 50  0001 C CNN
F 3 "" H 1700 5650 50  0001 C CNN
	1    1700 5650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1700 5650 2000 5650
Wire Wire Line
	1850 5850 2000 5850
Wire Wire Line
	1850 5950 2000 5950
Wire Wire Line
	2650 6400 2650 6250
Wire Wire Line
	2750 6400 2750 6250
Wire Wire Line
	2850 6400 2850 6250
Wire Wire Line
	2950 6400 2950 6250
$EndSCHEMATC
