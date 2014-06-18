ip link set can0 down

ip link set can0 type can bitrate 500000
#ip link set can0 type can tq 500 prop-seg 6 phase-seg1 7 phase-seg2 2

ip link set can0 up

ip link set can0 txqueuelen 1000
