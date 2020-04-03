# Reverse IOT Node

This software implements a node that requests information from a concentrator. The concentrator will forward the message and get the final response to send to this device.

This implements the network layer to request and receivie actualisation messages. It is a very simple last mile communiocation setting, but what it implements is enough for the purposes of this project.

The messages support to be chunked so that it is possible to send large messages over the limited 128 bytes payload.

## Behaviour

1. Over UART the node listens to any key, when detected it fires a message to the contrator asking for updates.
2. After the message is sent, an answer is expected. If the answer does not arrive, the system will send the update message until an acknowledgement messages arrives.
3. Once the ACK arrives, the node remains in listen mode indefininetwlly until the answer to the response arrives to it.

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


