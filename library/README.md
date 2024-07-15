# LoboMQ

<p align="center">
	<img src="https://rubnium.github.io/LoboMQ/LoboMQ_icon.png" width="90"/>
</p>

[![PlatformIO Registry](https://badges.registry.platformio.org/packages/rubnium/library/LoboMQ.svg)](https://registry.platformio.org/libraries/rubnium/LoboMQ)

LoboMQ is a lightweight protocol based on [MQTT](https://mqtt.org/) that runs over ESP-NOW on ESP32 boards, without the need for an Internet connection! 
It allows the creation of topic-based message queues where messages are posted to a broker and subscribers receive them.

Note: LoboMQ stands for \"<b>L</b>oboMQ <b>o</b>ffers (the) <b>b</b>est <b>o</b>f <b>M</b>essage <b>Q</b>ueues\"

This library provides the necessary functions to create nodes that are:
- Broker, an intermediary which process the received messages and redirect the publications to the appropriate subscribers.
- Clients, allowing to create publish, subscribe and unsubscribe messages, and also offering the ease to identify the type of message and extract the content.

You should see the examples to get a better idea of how to use it.

## Features
- Communication through ESP-NOW, inheriting its benefits, such as distance and the absence of Wi-Fi and Bluetooth networks. 
- Light message queues.
- Ease of use.
- Non-blocking communication, subscriber clients do not wait for messages, they only process them when they are received.
- Support for wildcard characters in topics.
- Broker security through a whitelist of MAC addresses with authorized access.
- Detailed log messages.
- Log filtering according to log level and log storage on SD card.
- Ability to persist topics and subscribers of the broker on SD card. 

## Message types and formats

There are 3 types of messages exchanged depending on the action performed: SubscribeAnnouncement, UnsubscribeAnnouncement and PublishContent.

<p align="center">
	<img src="https://rubnium.github.io/LoboMQ/LoboMQ_packets.png" width="600"/>
</p>

- `type`: the type of message.
- `topic`: the topic, limited to 24 characters.
- `contentSize`: the size of the content.
- `content`: the content, limited to 120 bytes.

These messages are created and transmitted automatically with the `publish`, `subscribe` and `unsubscribe` functions.

## Why "Lobo"?
A lobo or wolf is an animal known for its ability to communicate effectively with its pack, such as this protocol, that can convey messages quickly to multiple "canine" companions located at far distances.
