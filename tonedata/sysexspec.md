# YMF825 MIDI System Exclusive Format

+ This format is proposed by Yamaha in order to share YMF825 tone data created by the customer.
+ Up to 128 tone data can be transferred.
+ Secured an area to store the tone name for 16 characters.


|No.|Hex|bit7|6|5|4|3|2|1|0|range|definition|notes|
|-|-|-|-|-|-|-|-|-|-|-|-|-|
|0|"F0"|"1"|"1"|"1"|"1"|"0"|"0"|"0"|"0"||||
|1|"43"|"0"|"1"|"0"|"0"|"0"|"0"|"1"|"1"||YAMAHA||
|2|"7F"|"0"|"1"|"1"|"1"|"1"|"1"|"1"|"1"||make,DIY ID||
|3|"02"|"0"|"0"|"0"|"0"|"0"|"0"|"1"|"0"||make,DIY ID||
|4|"00"|"0"|"0"|"0"|"0"|"0"|"0"|"0"|"0"||YMF825||
|5|"00"|"0"|"0"|"0"|"0"|"0"|"0"|"0"|"0"||(reserved)||
|6|nn|"0"|n|n|n|n|n|n|n|0 - 127|Program Change Number||
|7|p0|"0"|BO1|BO0|LFO1|LFO0|ALG2|ALG1|ALG0|0-3, 0-3, 0-7|Voice Common|Basic Octave/ LFO freq./ FM Algorithm|
|8|p1|"0"|FB2|FB1|FB0|XOF|KSR|KSL1|KSL0|0-7, 0/1, 0/1, 0-3|Op.1 Key Control| Feedback/ Ignore Note Off/Key Scale Sens./Key Scale Level|
|9|p2|"0"|"0"|"0"|"0"|AR3|AR2|AR1|AR0|0-15|Op.1 Attack Rate||
|10|p3|"0"|"0"|"0"|"0"|DR3|DR2|DR1|DR0|0-15|Op.1 Decay Rate||
|11|p4|"0"|"0"|"0"|"0"|SR3|SR2|SR1|SR0|0-15|Op.1 Sustain Rate ||
|12|p5|"0"|"0"|"0"|"0"|RR3|RR2|RR1|RR0|0-15|Op.1 Release Rate ||
|13|p6|"0"|"0"|"0"|"0"|SL3|SL2|SL1|SL0|0-15|Op.1 Sustain Level ||
|14|p7|"0"|"0"|TL5|TL4|TL3|TL2|TL1|TL0|0-63|Op.1 Total Level||
|15|p8|"0"|DAM1|DAM0|EAM|"0"|DVB1|DVB0|EVB|0-3,0/1,0-3,0/1|Op.1 Modulation||
|16|p9|"0"|DT2|DT1|DT0|MT3|MT2|MT1|MT0|0-7,0-15|Op.1 Pitch|Detune/ Multi|
|17|p10|"0"|"0"|"0"|WS4|WS3|WS2|WS1|WS0|0-31|Op.1 Wave Shape||
|18|p11|"0"|"0"|"0"|"0"|XOF|KSR|KSL1|KSL0|0/1,0/1,0-3|Op.2 Key Control| Ignore Note Off/ Key Scale Sens./Key Scale Level|
|19|p12|"0"|"0"|"0"|"0"|AR3|AR2|AR1|AR0|0-15|Op.2 Attack Rate||
|20|p13|"0"|"0"|"0"|"0"|DR3|DR2|DR1|DR0|0-15|Op.2 Decay Rate||
|21|p14|"0"|"0"|"0"|"0"|SR3|SR2|SR1|SR0|0-15|Op.2 Sustain Rate ||
|22|p15|"0"|"0"|"0"|"0"|RR3|RR2|RR1|RR0|0-15|Op.2 Release Rate ||
|23|p16|"0"|"0"|"0"|"0"|SL3|SL2|SL1|SL0|0-15|Op.2 Sustain Level ||
|24|p17|"0"|"0"|TL5|TL4|TL3|TL2|TL1|TL0|0-63|Op.2 Total Level||
|25|p18|"0"|DAM1|DAM0|EAM|"0"|DVB1|DVB0|EVB|0-3,0/1,0-3,0/1|Op.2 Modulation||
|26|p19|"0"|DT2|DT1|DT0|MT3|MT2|MT1|MT0|0-7,0-15|Op.2 Pitch|Detune/ Multi|
|27|p20|"0"|"0"|"0"|WS4|WS3|WS2|WS1|WS0|0-31|Op.2 Wave Shape||
|28|p21|"0"|FB2|FB1|FB0|XOF|KSR|KSL1|KSL0|0-7, 0/1, 0/1, 0-3|Op.3 Key Control|Feedback/ Ignore Note Off/ Key Scale Sens./ Key Scale Level|
|29|p22|"0"|"0"|"0"|"0"|AR3|AR2|AR1|AR0|0-15|Op.3 Attack Rate||
|30|p23|"0"|"0"|"0"|"0"|DR3|DR2|DR1|DR0|0-15|Op.3 Decay Rate||
|31|p24|"0"|"0"|"0"|"0"|SR3|SR2|SR1|SR0|0-15|Op.3 Sustain Rate||
|32|p25|"0"|"0"|"0"|"0"|RR3|RR2|RR1|RR0|0-15|Op.3 Release Rate||
|33|p26|"0"|"0"|"0"|"0"|SL3|SL2|SL1|SL0|0-15|Op.3 Sustain Level||
|34|p27|"0"|"0"|TL5|TL4|TL3|TL2|TL1|TL0|0-63|Op.3 Total Level||
|35|p28|"0"|DAM1|DAM0|EAM|"0"|DVB1|DVB0|EVB|0-3,0/1,0-3,0/1|Op.3 Modulation||
|36|p29|"0"|DT2|DT1|DT0|MT3|MT2|MT1|MT0|0-7,0-15|Op.3 Pitch|Detune/ Multi|
|37|p30|"0"|"0"|"0"|WS4|WS3|WS2|WS1|WS0|0-31|Op.3 Wave Shape||
|38|p31|"0"|"0"|"0"|"0"|XOF|KSR|KSL1|KSL0|0/1, 0/1, 0-3|Op.4 Key Control|Ignore Note Off/ Key Scale Sens./ Key Scale Level|
|39|p32|"0"|"0"|"0"|"0"|AR3|AR2|AR1|AR0|0-15|Op.4 Attack Rate||
|40|p33|"0"|"0"|"0"|"0"|DR3|DR2|DR1|DR0|0-15|Op.4 Decay Rate||
|41|p34|"0"|"0"|"0"|"0"|SR3|SR2|SR1|SR0|0-15|Op.4 Sustain Rate||
|42|p35|"0"|"0"|"0"|"0"|RR3|RR2|RR1|RR0|0-15|Op.4 Release Rate||
|43|p36|"0"|"0"|"0"|"0"|SL3|SL2|SL1|SL0|0-15|Op.4 Sustain Level||
|44|p37|"0"|"0"|TL5|TL4|TL3|TL2|TL1|TL0|0-63|Op.4 Total Level||
|45|p38|"0"|DAM1|DAM0|EAM|"0"|DVB1|DVB0|EVB|0-3,0/1,0-3,0/1|Op.4 Modulation||
|46|p39|"0"|DT2|DT1|DT0|MT3|MT2|MT1|MT0|0-7,0-15|Op.4 Pitch|Detune/ Multi|
|47|p40|"0"|"0"|"0"|WS4|WS3|WS2|WS1|WS0|0-31|Op.4 Wave Shape||
|48|s0|"0"|s|s|s|s|s|s|s|32-126|Character0|ASCII code|
|49|s1|"0"|s|s|s|s|s|s|s|32-126|Character1|ASCII code|
|50|s2|"0"|s|s|s|s|s|s|s|32-126|Character2|ASCII code|
|51|s3|"0"|s|s|s|s|s|s|s|32-126|Character3|ASCII code|
|52|s4|"0"|s|s|s|s|s|s|s|32-126|Character4|ASCII code|
|53|s5|"0"|s|s|s|s|s|s|s|32-126|Character5|ASCII code|
|54|s6|"0"|s|s|s|s|s|s|s|32-126|Character6|ASCII code|
|55|s7|"0"|s|s|s|s|s|s|s|32-126|Character7|ASCII code|
|56|s8|"0"|s|s|s|s|s|s|s|32-126|Character8|ASCII code|
|57|s9|"0"|s|s|s|s|s|s|s|32-126|Character9|ASCII code|
|58|s10|"0"|s|s|s|s|s|s|s|32-126|Character10|ASCII code|
|59|s11|"0"|s|s|s|s|s|s|s|32-126|Character11|ASCII code|
|60|s12|"0"|s|s|s|s|s|s|s|32-126|Character12|ASCII code|
|61|s13|"0"|s|s|s|s|s|s|s|32-126|Character13|ASCII code|
|62|s14|"0"|s|s|s|s|s|s|s|32-126|Character14|ASCII code|
|63|s15|"0"|s|s|s|s|s|s|s|32-126|Character15|ASCII code|
|64|"F7"|"1"|"1"|"1"|"1"|"1"|"1"|"1"|"0"|||||


