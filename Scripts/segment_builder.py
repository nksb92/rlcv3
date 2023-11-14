
NUM_LEDS = 144
POSSIBLE_LEDS_PER_SEGMENT = []
START_ADDRESS = 5

for i in range(1, NUM_LEDS+1):
    if NUM_LEDS % i == 0:
        POSSIBLE_LEDS_PER_SEGMENT.append(i)

print(POSSIBLE_LEDS_PER_SEGMENT)

for segment in POSSIBLE_LEDS_PER_SEGMENT:
    segment_size = NUM_LEDS // segment
    leds_addressed = 0
    for i in range(segment):
        for j in range(segment_size):
            leds_addressed += 1
    dmx_channel_needed = segment * 3 + 1
    fixtures_pro_universe = 512 // dmx_channel_needed

    print("Number Seg.: " + str(segment), " Size Seg.: " + str(segment_size), " DMX Channel: " + str(dmx_channel_needed), " DMX Fixtures: " + str(fixtures_pro_universe))
