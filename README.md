# MSP432_iBUS
Set up serial communication between an MSP432 microcontroller and a FlySky iBUS receiver.


Learned about:

Timers - special counting registers in a microcontroller which can be used to produce PWM signals.

PWM (Pulse Width Modulation) - can be used to control motor speed(BLDC) or angle(servo).

UART - Serial communication protocol. 8N1 (8 data bits, No parity, 1 stop bit) baudrate 115200

FIFO queues (ringBuffer) - Used as a buffer between devices. Store data recieved via UART in a FIFO so it can be used later.

State Machines - used to decode an iBUS packet
