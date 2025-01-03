# Ethernet Large W5100
Ethernet library for Arduino with compatibility for the [SSLClient](https://github.com/OPEnSLab-OSU/SSLClient) library for using HTTPS connections.

Only compatible with W5100. W5500 support has been removed. To continue using the W5500 chip, use the EthernetLarge library (https://github.com/MicSG-dev/EthernetLarge)

Library was based on the Arduino Ethernet Library: https://github.com/arduino-libraries/Ethernet

## Instructions for Generating Certificate
To generate the certificate (which will be stored in `trust_anchors.h`, file located next to the sketch), access https://openslab-osu.github.io/bearssl-certificate-utility/ and enter the websites you will access.

## License

Copyright (c) 2010 Arduino LLC. All right reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
