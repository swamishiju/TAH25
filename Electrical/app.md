## General Questionnaire

1. India as a country is famously plagued with headache inducing traffic. As an 18 year long Banlore resident I couldn't agree more. The metro system in Banglore has over the years managed to some what mitigate this issue.   

2.

3. I want to work on the PCB and embedded software aspects of the Electrical Subsystem. I am passionate about low-level programming and working close to hardware.  

4.

5. I am a DC in Math Club wokring on a 3D rendering mini-project and a DC is Programming Club under the CPP dev vertical. I can dedicate  

6. I am familiar with Python and C. I aim to learn CPP, VHDL and Matlab this semester. I have been programming in Python for 4 years from personal projects and minor scipting and C for over a year mainly from learning kernel development.

## Question 1

Resisto can adjust the motor speed using the switch to create a pulse width modulated (PWM) signal. This setup needs Resisto to quickly flip the switch to create the signal.

This works because the PWM signal can control power delivered using the duty cycle. Though the flipping needs to take place quick enough for the motor to work as though on the average power.
This however is better than other methods like using a rheostat which would cause significant power depletion across the resistor. 

This has several issues namely
- Motor speed control is not precise 
- Motor will not run smoothly
- Flipping switch is annoying




## Question 2

1. The pre-charge relay is added to the circuit to make sure there is no in-rush of current on the load(inverter). 
If the pre-charge relay was not added to operate the circuit both main relays are closed and the capacitor charges up with no resistance in a very small time period. This sudden voltage spike across the inverter can cause damage to the components. 
To fix this we add a pre-charge relay. We start by closing main relay(-) and the pre-charge relay, this is then simply an RC circuit that gradually charges. After a sufficient amount of time we can then open the pre-charge relay and close main relay(+) to begin usual operation.

2.

3.

**Sources**
    - [TI Pre-Charge application brief](https://www.ti.com/lit/ab/slvafb0/slvafb0.pdf)

## Question 3


## Question 4 

A)
- Traces:
PCB trace refers to the network of copper, wiring, insulation and fuses that make up a board. The trace width is an import parameter to keep in mind while designing since passing high current through thin traces can lead to overheating and damage.

- Vias: 
Vias are holes drilled in a PCB with conducting walls. They allow the transfer of signals and power from one layer to another in a multilayer PCB. Via "covering" is usually done to make sure solder paste doesn't get into it and cause short circuits. The simplest way being to simply cover it with a layer of solder mask.

- Polygon pours:


- Silkscreen:
The PCB silkscreen is the text and images that we see on a PCB. The ink used is a non-conductive epoxy and comes in a lot of colours thought the commonly seen one is white. It is usually seen on the component side but having it on the solder side is not uncommon. 

- Pads:
- Solder mask:
Solder mask is a thin layer of polymer applied to copper traces and vias for protection against oxidation and solder bridging. Green solder mask is commonly used as the industry standard most manufactures have been accustomed to it.

- Differential pair:
Differential pair refers to a pair of signal traces commonly used it high-speed circuits to cancel out noise and enhance signal strength. Both traces carry the same signal but with opposite phase and the receiver samples the signal by taking the difference between the two signals. This has the advantage of removing any common noise and amplifying the signal.

C) A thermistor is a resistor made of material with resitivity that is strongly dependant on temperature. They change resistance in response to a change in temperature which alters the potential difference across it which we can measure to calculate temperature. If we know the R/T curve for the thermistor we can use it to find temperature.

Steinhart–Hart equation is commonly used as a third order approximation for practical devices of large ranges of temperature. 

$$\frac1T=a+b\log R+c(\log R)^3$$ where $a,b,c$ are parameters


Code for data processing

[Github Link TODO]()

**Sources**
   - [PCB GoGO](https://www.pcbgogo.com/knowledge-center/Printed_Circuit_Board_Prototype.html)

## Question 6

**A)** OSI has 7 layers namely

1. Physical Layer
2. Data Link Layer
3. Network Layer
4. Transport Layer
5. Session Layer
6. Presentation Layer
7. Application Layer

The function of the physical layer is to send and recieve bits over the network. This includes modulation, demodulation and channel coding. 

The function of the data link layer is to ensure reliable communication between the ends of a link. Link layer offers frames to the physical layer for transmission. We achieve error control by attaching error-correction bits to the frame. At the receiving end the error-correction bits are used to check if the received message is accurate. The issues of multiplexing is handled in this layer. If the physical link is shared between several devices the sharing of the link is viewed as belonging to this layer. This is called medium access control (MAC).

The network layer ties together the links into a network. Each device is provided a unique network address at this link. Its primary function is routing packets between these addresses. Technically these 3 layers are enough for a packet switch. A distributed routing protocol is implemented in this layer to learn good good routes. These route computations are stored in a routing table at each switch. When the layer gets a packet the table is looked up and the packet is then sent to the link layer and queued at the appropriate output port.

The tansport layer controls the reliability of a given link between source and destination through flow and error control. It provides acknowledgement of the succesful data transmission and sends the next packet if no errors occured.

The session layer provides services for dialog management between users. For instance continuing the communication incase of an error.

The presentation layer handles functions like data encryption and file conversions.

The application layer handles functions like file transfer and is the layer that directly interacts with the user. 


CAN uses the physical, data link and application layers. The physical layer is the transceiver, the data link layer functions as the embedded controller and the application layer funtions a DSP.

**B)** Standard CAN bit fields have a 11 bit identifier (extended CAN has 29 bits).
If two nodes try to access the node at the same time access is implemented with a nondestructive bit-wise arbitration.
CAN messages have priority based on the identifier. The lower identifier has higher priority.
A standard CAN frame starts with a dominant SOF (Start Of Frame) followed by its identifier. Then there is a RTR (Remote Transmission Request) bit which differentiates between a data frame (dominant 0) or a remote request frame (dominant 1) then there is an IDE(IDentifier Extension) bit which denotes whether we are using standard or extended CAN frame format. Then there is a reserved bit that might be used in further updates of the frame standard. Then we have a 4 bit DLC (Data Length Code) segment which says how many bytes of data we are transmitting (0-8 bytes sending DLC 9-15 is physically possible but most controllers limit data to 8 bytes). We then have the data segment which ranges from 0 to 64 bits depending on DLC. Then we have 15 bits of CRC and then a recessive delim followed by a bit each of ACK, ACK delim(recessive) and a 7 bit EOF(End Of Frame all recessive) and 3 bits of IFS(Inter-Frame spacing all recessive). 

**C)** Nodes access the CAN bus randomly. The bus's idle state is high which is the recessive bit.Nodes can monitor the bus while transmitting.
When nodes start transmitting they send a low SOF signal followed by their id and they keep monitoring the bus. If it reads a bit that doesn't match what it is transmitting then it stops transmitting and goes to reciever mode. This works since if it reads a dominant low when it is trasmitting a high it means another node is transmitting with higher priority so to avoid a collision it stops transmitting. This is refered to as bus arbitration. After the end of transmission nodes that recieve an accurate message trasmit a dominant bit to overwrite the data frame's designated ACK bit (technically 2 bits but one is delim) indicating a succesful transmission. If the bit is still recessive then the transmission failed and after rearbitrating the node tries to transmit again.

**D)** The CAN bus is a brodcast bus i.e all nodes recieve all messages. Some nodes might care only about certain critical messages. For example if we have a battery controller connected to the bus we care about battery health messages more than the speed of the pod. If the controller recieves the useless messages the software needs to process it. To fix this issue we can implement Hardware filtering in the CAN network.
Hardware filtering just filters out messages a particular node requires, this lessens the work software has to do. Not filtering messages uses up node resources for messages it won't process anyway. 

```py
FilterID: 0x15203424 | 0b10101001000000011010000100100 
MaskID  : 0x1FAB677E | 0b11111101010110110011101111110
Accepted: 0x-------- | 0b101010_1_0_00_01__100_010010_
```

It accepts all identifiers of the form Accepted where each `_` can be 0 or 1. So there are a total of $2^8$ or $256$ accepted IDs.


i) 
```py
FilterID: 0x00000000 | 0b00000000000000000000000000000
MaskID  : 0x00000000 | 0b00000000000000000000000000000
Accepted: 0x-------- | 0b_____________________________
```

ii) 
```py
FilterID: 0x00000000 0b00000000000000000000000000000
MaskID  : 0x00000000 0b11111111111111111111111111111
Accepted: 0x00000000 0b00000000000000000000000000000
```
As far as I am aware it is not possible to make a CAN node accept no messages the minimum is 1. So I chose it to only accept the highest priority message.

E) The CAN frame has designated 16 bit (15+delim) bits of CRC (cyclic redundancy check) at the end of the frame before the ACK bit. CRC is a common error detection code used in networks and data storage. If any bit of the transmitted data is altered its CRC changes. So a node sends the frame with a pre-calculated CRC. If external stimuli like say noise alters the message the CRC will no longer match which lets the reciever know the message is invalid. Upon recieving an invalid message the reciever doesn't overwrite ACK which the sender recognises as saying the data integrity is compromised and tries to brodcast again after rearbitration.


**Sources**:
	- Anurag Kumar  - Communication Networking: An Analytical Approach 
    - [TI Introduction to CAN](https://www.ti.com/lit/an/sloa101b/sloa101b.pdf)



## Question 8 

**A)** A process is an instance of an executing program which include the values in its program counter, registers and variables. 
Each process has its own program counter independant to the others. When a process is running it loads its program counter into the the CPU's physical program counter and when the process is suspended (for the time being) the current program counter is saved in the process's program counter in memory. This is not true parallelism when running on a single core but multi-core processors can achieve true parallelism.



**Bonus:** Intel Pentium 4 introduced multithreading (hyperthreading) to the x86 processor. This allowed CPUs to store the states of two (or more) threads and allowed the CPU to switch between them on a very small time scale.
This feature can increase the execution speed in general. For example when the current process requests uncached data from memory which takes several clock cycles to complete the CPU can just switch to another thread to use the unused computing resources.
The OS sees the number of "logical threads" which is the total number of threads that can be scheduled and executed by the CPU. Since task manager simply displays the thread count seen by the OS the counts different from the one reported by the CPU manufacturer which is the physical thread count.   

**B)**


**Sources:** 
 - Andrew S Tanenbaum - Modern Operating Systems
 - [IBM AIX docs](https://www.ibm.com/docs/en/aix/7.3)
 - [Multithreading wikipedia](https://en.wikipedia.org/wiki/Multithreading_(computer_architecture))

