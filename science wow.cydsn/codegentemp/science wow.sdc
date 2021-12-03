# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\mewin\OneDrive\Documents\PSoC Creator\Science_Board_2021-2022\science wow.cydsn\science wow.cyprj
# Date: Fri, 03 Dec 2021 01:46:37 GMT
#set_units -time ns
create_clock -name {I2C_Servo_SCBCLK(FFB)} -period 625 -waveform {0 312.5} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {I2C_Spectrometer_SCBCLK(FFB)} -period 625 -waveform {0 312.5} [list [get_pins {ClockBlock/ff_div_5}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFClk} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {I2C_Servo_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 31 61} [list]
create_generated_clock -name {Debug_IntClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 105 209} -nominal_period 2166.6666666666665 [list [get_pins {ClockBlock/udb_div_0}]]
create_generated_clock -name {I2C_Spectrometer_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 31 61} [list]


# Component constraints for C:\Users\mewin\OneDrive\Documents\PSoC Creator\Science_Board_2021-2022\science wow.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\mewin\OneDrive\Documents\PSoC Creator\Science_Board_2021-2022\science wow.cydsn\science wow.cyprj
# Date: Fri, 03 Dec 2021 01:46:30 GMT
