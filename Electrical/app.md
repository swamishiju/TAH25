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

-

The session layer provides services for dialog management between users. For instance continuing the communication incase of an error.

The presentation layer handles functions like data encryption and file conversions.

The application layer handles functions like file transfer and is the layer that directly interacts with the user. 


CAN uses the physical, data link and application layers. The physical layer is the transceiver, the data link layer functions as the embedded controller and the application layer funtions a DSP.

**B)** Standard CAN bit fields have a 11 bit identifier. If two nodes try to access the node at the same time access is implemented with a nondestructive bit-wise arbitration.
CAN messages have priority based on the identifier. The lower identifier has higher priority.

**C)** Nodes access the CAN bus randomly. The bus's idle state is high which is the recessive bit.Nodes can monitor the bus while transmitting. When nodes start transmitting they send a low SOF(start of frame) signal followed by their id. If two nodes are transmitting at the same time the id with 0 (low) will overwrite the bus at the conflicting id bit will win the arbitration (higher priority) and the node that loses the arbitration halts transmission and    

**D)** 

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

