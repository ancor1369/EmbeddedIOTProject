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
P 3450 1750
F 0 "U?" H 3475 2465 50  0000 C CNN
F 1 "TPS61090RSAR" H 3475 2374 50  0000 C CNN
F 2 "" H 3500 1850 50  0001 C CNN
F 3 "" H 3500 1850 50  0001 C CNN
	1    3450 1750
	1    0    0    -1  
$EndComp
$Comp
L pspice:INDUCTOR L?
U 1 1 5F14E60C
P 2400 1400
F 0 "L?" H 2400 1615 50  0000 C CNN
F 1 "VLC5045" H 2400 1524 50  0000 C CNN
F 2 "" H 2400 1400 50  0001 C CNN
F 3 "~" H 2400 1400 50  0001 C CNN
	1    2400 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F14F852
P 1000 1900
F 0 "C?" H 1115 1946 50  0000 L CNN
F 1 "C" H 1115 1855 50  0000 L CNN
F 2 "" H 1038 1750 50  0001 C CNN
F 3 "~" H 1000 1900 50  0001 C CNN
	1    1000 1900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F14FE73
P 1400 1900
F 0 "C?" H 1515 1946 50  0000 L CNN
F 1 "C" H 1515 1855 50  0000 L CNN
F 2 "" H 1438 1750 50  0001 C CNN
F 3 "~" H 1400 1900 50  0001 C CNN
	1    1400 1900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F1506FC
P 1800 1800
F 0 "R?" H 1870 1846 50  0000 L CNN
F 1 "1.87Mohm" H 1870 1755 50  0000 L CNN
F 2 "" V 1730 1800 50  0001 C CNN
F 3 "~" H 1800 1800 50  0001 C CNN
	1    1800 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F150DE7
P 1800 2250
F 0 "R?" H 1870 2296 50  0000 L CNN
F 1 "340k" H 1870 2205 50  0000 L CNN
F 2 "" V 1730 2250 50  0001 C CNN
F 3 "~" H 1800 2250 50  0001 C CNN
	1    1800 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 1850 2700 1850
Wire Wire Line
	2700 1850 2700 2000
Wire Wire Line
	2950 2000 2700 2000
Connection ~ 2700 2000
Wire Wire Line
	2700 2000 2700 2300
$Comp
L power:GND #PWR?
U 1 1 5F153C84
P 2700 2300
F 0 "#PWR?" H 2700 2050 50  0001 C CNN
F 1 "GND" H 2705 2127 50  0000 C CNN
F 2 "" H 2700 2300 50  0001 C CNN
F 3 "" H 2700 2300 50  0001 C CNN
	1    2700 2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F154143
P 1800 2550
F 0 "#PWR?" H 1800 2300 50  0001 C CNN
F 1 "GND" H 1805 2377 50  0000 C CNN
F 2 "" H 1800 2550 50  0001 C CNN
F 3 "" H 1800 2550 50  0001 C CNN
	1    1800 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F154451
P 1400 2200
F 0 "#PWR?" H 1400 1950 50  0001 C CNN
F 1 "GND" H 1405 2027 50  0000 C CNN
F 2 "" H 1400 2200 50  0001 C CNN
F 3 "" H 1400 2200 50  0001 C CNN
	1    1400 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F15496C
P 1000 2200
F 0 "#PWR?" H 1000 1950 50  0001 C CNN
F 1 "GND" H 1005 2027 50  0000 C CNN
F 2 "" H 1000 2200 50  0001 C CNN
F 3 "" H 1000 2200 50  0001 C CNN
	1    1000 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 2200 1000 2050
Wire Wire Line
	1400 2050 1400 2200
Wire Wire Line
	1800 1950 1800 2000
Wire Wire Line
	1800 2400 1800 2550
Wire Wire Line
	1800 1650 1800 1600
Wire Wire Line
	1800 1600 1400 1600
Wire Wire Line
	1000 1600 1000 1750
Connection ~ 1800 1600
Wire Wire Line
	1400 1750 1400 1600
Connection ~ 1400 1600
Wire Wire Line
	1400 1600 1000 1600
Wire Wire Line
	2650 1400 2950 1400
Wire Wire Line
	2150 1400 1800 1400
Wire Wire Line
	1800 1400 1800 1500
Wire Wire Line
	1800 1500 2950 1500
Connection ~ 1800 1500
Wire Wire Line
	1800 1500 1800 1600
Wire Wire Line
	1800 2000 2150 2000
Wire Wire Line
	2150 2000 2150 1700
Wire Wire Line
	2150 1700 2950 1700
Connection ~ 1800 2000
Wire Wire Line
	1800 2000 1800 2100
Text Label 2650 1600 0    50   ~ 0
Enable
Wire Wire Line
	2950 1600 2650 1600
$Comp
L Device:R R?
U 1 1 5F15B76B
P 4550 1750
F 0 "R?" H 4620 1796 50  0000 L CNN
F 1 "1.87MOhm" H 4620 1705 50  0000 L CNN
F 2 "" V 4480 1750 50  0001 C CNN
F 3 "~" H 4550 1750 50  0001 C CNN
	1    4550 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F15BD62
P 4550 2150
F 0 "R?" H 4620 2196 50  0000 L CNN
F 1 "200k" H 4620 2105 50  0000 L CNN
F 2 "" V 4480 2150 50  0001 C CNN
F 3 "~" H 4550 2150 50  0001 C CNN
	1    4550 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 1550 4550 1550
Wire Wire Line
	4550 1550 4550 1600
Wire Wire Line
	4000 1700 4150 1700
Wire Wire Line
	4150 1700 4150 1950
Wire Wire Line
	4150 1950 4550 1950
Wire Wire Line
	4550 1900 4550 1950
Connection ~ 4550 1950
Wire Wire Line
	4550 1950 4550 2000
$Comp
L power:GND #PWR?
U 1 1 5F15DEF4
P 4550 2450
F 0 "#PWR?" H 4550 2200 50  0001 C CNN
F 1 "GND" H 4555 2277 50  0000 C CNN
F 2 "" H 4550 2450 50  0001 C CNN
F 3 "" H 4550 2450 50  0001 C CNN
	1    4550 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F15E2F1
P 5300 1750
F 0 "C?" H 5415 1796 50  0000 L CNN
F 1 "2.2uF" H 5415 1705 50  0000 L CNN
F 2 "" H 5338 1600 50  0001 C CNN
F 3 "~" H 5300 1750 50  0001 C CNN
	1    5300 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F15E8C5
P 5750 1750
F 0 "C?" H 5865 1796 50  0000 L CNN
F 1 "100uF/6V" H 5865 1705 50  0000 L CNN
F 2 "" H 5788 1600 50  0001 C CNN
F 3 "~" H 5750 1750 50  0001 C CNN
	1    5750 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 1550 5300 1550
Wire Wire Line
	5300 1550 5300 1600
Connection ~ 4550 1550
Wire Wire Line
	5300 1550 5750 1550
Wire Wire Line
	5750 1550 5750 1600
Connection ~ 5300 1550
$Comp
L power:GND #PWR?
U 1 1 5F15F9FD
P 5300 2050
F 0 "#PWR?" H 5300 1800 50  0001 C CNN
F 1 "GND" H 5305 1877 50  0000 C CNN
F 2 "" H 5300 2050 50  0001 C CNN
F 3 "" H 5300 2050 50  0001 C CNN
	1    5300 2050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F15FCFD
P 5750 2050
F 0 "#PWR?" H 5750 1800 50  0001 C CNN
F 1 "GND" H 5755 1877 50  0000 C CNN
F 2 "" H 5750 2050 50  0001 C CNN
F 3 "" H 5750 2050 50  0001 C CNN
	1    5750 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 1900 5300 2050
Wire Wire Line
	5750 1900 5750 2050
Wire Wire Line
	4000 2000 4150 2000
Wire Wire Line
	4150 2000 4150 1950
Connection ~ 4150 1950
Wire Wire Line
	4550 2300 4550 2450
$Comp
L power:+BATT #PWR?
U 1 1 5F1710A3
P 1800 1200
F 0 "#PWR?" H 1800 1050 50  0001 C CNN
F 1 "+BATT" H 1815 1373 50  0000 C CNN
F 2 "" H 1800 1200 50  0001 C CNN
F 3 "" H 1800 1200 50  0001 C CNN
	1    1800 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 1200 1800 1400
Connection ~ 1800 1400
$EndSCHEMATC
