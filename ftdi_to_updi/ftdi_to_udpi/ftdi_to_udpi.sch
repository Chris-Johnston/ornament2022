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
L Connector_Generic:Conn_01x03 J2
U 1 1 635F2616
P 4500 2000
F 0 "J2" H 4580 2042 50  0000 L CNN
F 1 "Conn_01x03" H 4580 1951 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4500 2000 50  0001 C CNN
F 3 "~" H 4500 2000 50  0001 C CNN
	1    4500 2000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 635F2BB5
P 2350 2100
F 0 "J1" H 2268 1575 50  0000 C CNN
F 1 "Conn_01x06" H 2268 1666 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 2350 2100 50  0001 C CNN
F 3 "~" H 2350 2100 50  0001 C CNN
	1    2350 2100
	-1   0    0    1   
$EndComp
Text Notes 1450 1050 0    50   ~ 0
Based on https://teddywarner.org/Projects/SerialUPDI/\nThis is a super cheap version which doesn't depend on the switch from UDPI to monitoring mode. I don't need the feature.\n
Text GLabel 2750 2300 2    50   Input ~ 0
ftdi_3v3
Text GLabel 2750 2100 2    50   Input ~ 0
ftdi_gnd
Text GLabel 2750 1900 2    50   Input ~ 0
ftdi_rx
Text GLabel 2750 2000 2    50   Input ~ 0
ftdi_tx
Text GLabel 4000 1900 0    50   Input ~ 0
ftdi_3v3
Text GLabel 4000 2000 0    50   Input ~ 0
ftdi_gnd
Text GLabel 3400 2300 0    50   Input ~ 0
ftdi_rx
Text GLabel 3400 2200 0    50   Input ~ 0
ftdi_tx
Wire Wire Line
	4000 1900 4300 1900
Wire Wire Line
	4000 2000 4300 2000
$Comp
L Device:D D1
U 1 1 635F6C66
P 3650 2200
F 0 "D1" H 3650 2417 50  0000 C CNN
F 1 "D" H 3650 2326 50  0000 C CNN
F 2 "Diode_THT:D_T-1_P5.08mm_Horizontal" H 3650 2200 50  0001 C CNN
F 3 "~" H 3650 2200 50  0001 C CNN
	1    3650 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 635F732E
P 4050 2200
F 0 "R1" V 3843 2200 50  0000 C CNN
F 1 "R" V 3934 2200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 3980 2200 50  0001 C CNN
F 3 "~" H 4050 2200 50  0001 C CNN
	1    4050 2200
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 2200 3500 2200
Wire Wire Line
	3400 2300 3800 2300
Wire Wire Line
	3800 2300 3800 2200
Wire Wire Line
	3800 2200 3900 2200
Connection ~ 3800 2200
Wire Wire Line
	4200 2200 4300 2200
Wire Wire Line
	4300 2200 4300 2100
Wire Wire Line
	2550 1900 2750 1900
Wire Wire Line
	2550 2000 2750 2000
Wire Wire Line
	2550 2100 2750 2100
Wire Wire Line
	2550 2300 2750 2300
$EndSCHEMATC
