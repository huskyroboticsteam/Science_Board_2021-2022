# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\write\Documents\PSoC Creator\Science_Board_2021-2022\science wow.cydsn\science wow.cyprj
# Date: Wed, 26 Jan 2022 02:30:38 GMT
#set_units -time ns
create_clock -name {ADC_intClock(FFB)} -period 166.66666666666666 -waveform {0 83.3333333333333} [list [get_pins {ClockBlock/ff_div_10}]]
create_clock -name {I2C_SCBCLK(FFB)} -period 625 -waveform {0 312.5} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFClk} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {ADC_intClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 9 17} [list]
create_generated_clock -name {I2C_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 31 61} [list]
create_generated_clock -name {Debug_IntClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 105 209} -nominal_period 2166.6666666666665 [list [get_pins {ClockBlock/udb_div_0}]]


# Component constraints for C:\Users\write\Documents\PSoC Creator\Science_Board_2021-2022\science wow.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\write\Documents\PSoC Creator\Science_Board_2021-2022\science wow.cydsn\science wow.cyprj
# Date: Wed, 26 Jan 2022 02:30:25 GMT