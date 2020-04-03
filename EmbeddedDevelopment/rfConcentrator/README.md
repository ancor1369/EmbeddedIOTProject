# IOT Concentrator

This software implements a concentrator that listens to many nodes asking for updates on their information

This node connects to a bigger node over UART to send messages back and fort. It receives messages which are up to 512 Bits long and chuch them to send as up to 5 packets to send a bigger message. The sending payload is limited to 128 bytes, So the algorithm needs to do everythink needed to create the packages as needed.

## Behaviour

1. The concentrator is listening for cycles, if a node speaks and this does not listen, it will try again untils this concentrator listens
2. The received message is transmited to the UART interface for further processing in an upper layer
3. An ackowledgement message is sent to the requester node
4. When the resposnse to the message sent over UART arrives, the concentrator will send it to the original requester.

Thid node manages the addressses to send acknowledgement automatically. The address to send responses back and forht are completelly managed by the upper level system. That system will interface with a RESTFul API to get informtiaon and will keep track of the messages pending to send answers to.

This concentrator does not keep track of the messages received or sent, this is only a gateway that passes the infromation from lication to lication.

The upper level program is responsable to provide the address where the message needs to be sent, The first byte of every message to be sent is the destination address of the package on this network.

## Payload package structure
 _______________________________________________________________________________________________
|		    |	                    |                 |                  |              |
| 1B Sender Address |1B Destination Address |1B Total packages|1B Sequence number| 124B Payload |
|___________________|_______________________|_________________|__________________|______________|
   
### Frame Structure for the physical layer
The EasyLink implements a basic header for transmitting and receiving data. This header supports
addressing for a star or point-to-point network with acknowledgements.

Packet structure:

     _________________________________________________________
    |           |                   |                         |
    | 1B Length | 1-64b Dst Address |         Payload         |
    |___________|___________________|_________________________|


