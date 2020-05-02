# Embedded IOT Project
This is an implementation of Electronic Shelf Tags aiming to improve operations in retail stores


![image](https://user-images.githubusercontent.com/25968721/79048795-8fe77e00-7bed-11ea-9828-673706acc54b.png)



## Abstract
The project done for the Embedded Systems Engineering Design course resolves a problem that many physical stores have when running their floor operations. We have created a system that solves the problem of ever changing prices by creating a system that allows store managers to update prices easily by just making the update in the system and waiting the prices in each product to change automatically.


## Introduction
Physical retail stores run operations in extensive floors where they expose the merchandise they sell to their customers organized on shelves. The exposition of the products have requirements regarding the information the client needs to be provided with. For example, it is important to show the price of the product, the Stoking Keeping Unit, SKU, model name and, of course, a description of the product being sold. Since pricing is a parameter that is so fluctuant, that stores are making price changes very often, resulting in personal dedicated exclusively to this task, which takes time, resources and prevents those employees from providing customer service when needed. 

The main users for this system are the stores themselves. Their operation will be faster and more straightforward so that they can order their personnel to focus on their regular floor tasks.

The system built have the following features:
1. Use of a very low energy consumption display to optimize battery life
2. Labels need to communicate over a wireless link
3. The system needs to support as many independent labels as possible
4. It shall have a concentrator device that can handle many labels connected
5. The concentrator shall have a software that connects and interacts with a central server to retrieve the information to be shown
6. The system shall have a noSQL data storage to manage the information of products 
7. The system shall have a website where the information of products can be managed

## Our solution

The solution proposed for this project is composed of many different pieces working together.
For the final user, the solution we are proposing will be seen as a simple website where the store’s price or product manager will log in and will manage the characteristics of the products. It is a simple concept where they just have to do what they already do when they send price updates to stores, but instead of the local store manager to allocate personal and print every updated price as it is required with the traditional approach, they will be just notified of the change, because the electronic labels located at each product will be updated when it is necessary.

The proposed solution solves this operative needs by providing all the infrastructure required to enable automatic price updating.

# General architecture

The following diagram shows how this solution is deployed and what are the most important parts that need to be created.

![image](https://user-images.githubusercontent.com/25968721/80862404-d5262b00-8c42-11ea-83f0-0c2e9fc09b52.png)

A large number of labels make a solution. The labels are wirelessly connected to an access point concentrator, where they will ask information about information updates. The concentrator is connected to a dedicated software running on a computer that will receive the messages coming from each label and will make sure each message obtains its answer. For each query, there will be an API call to a Rest server to retrieve the information of each label. Once each query has its answer, the software will send the information back to the requester and will remove the message from the listing.

On the other hand, the final user will connect to the system’s website to manage the product information, so that when the labels request for product updates, the new information is available to be served.

In the cloud part, the solution has a Restful API that connects to a database and exposes the data to both the concentrator software and the web site.

The web site connects to the Restful API for administration purposes so that the final user can change prices and make modifications as desired.


## Messaging schema

![image](https://user-images.githubusercontent.com/25968721/80862420-f5ee8080-8c42-11ea-80e4-350dd00c70cf.png)

All the communication chain is represented with JSON objects no matter what is the physical layer on which the messages are travelling. So each node of the communication chain needs to interpret the message to extract some information.

The messages are chunked between the label and concentrator because the wireless link imposes restrictions in the size of messages that can be sent. So the label needs to take the message and chunk it into smaller pieces, the concentrator, receives the message and reconstructs it to obtain the original message.

The concentrator passes the message received on the wireless interface through its serial interface to the Linux gateway, where the messages are stored in a data structure to be able to ask for each request and keep the solution compliant with the asynchronous nature of Rest calls.

The Linux gateway holds every message sent by the labels, it keeps track of the sender address, the message they sent, and the answer obtained after the API sends back the response. The Linux Gateway will send Rest calls with each message from the labels and will get the answers, once those answers arrive, the Gateway will send the answer-back and will delete the message from its listing.

The message needs to travel again from the API, to the Label passing by the same physical layers.  That means that the response message will be chunked and reconstructed in the label again

### References

I want to thank to some projects that have been on the web and in GitHub that really helped to give a boost to this project.

* E-Paper screen vendor initialization code: https://www.crystalfontz.com/products/document/3967/CFAP104212E00213_bring_up_code.zip
* E-Paper image engine by arturlangner:
http://m0agx.eu/2018/02/10/waveshare-epaper-display-library/
* Creating fonts for E-Paper screens by arturlangner: http://m0agx.eu/2018/02/10/making-graphics-and-fonts-for-embedded-systems/
* cJSON JSON library suitable to use in microcontrollers by Dave Gamble: https://github.com/DaveGamble/cJSON
* Font builder to generate C resource files.
https://github.com/arturlangner/fontbuilder
* E-Paper engine library
https://github.com/arturlangner/Waveshare-ePaper-C-library

