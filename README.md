[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![GPL3 License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]
[![Ask Me Anything][ask-me-anything]][personal-page]

<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/stiliajohny/hardware-sms-temperature-sensor">
    <img src="https://raw.githubusercontent.com/stiliajohny/hardware-sms-temperature-sensor/main/.assets/logo.png" alt="Main Logo" width="80" height="80">
  </a>

  <h3 align="center">hardware-sms-temperature-sensor</h3>

  <p align="center">
    A temperature sensore using DHT11 and SIM800L that replies back to you with SMS.
    <br />
    <a href="./README.md"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/stiliajohny/hardware-sms-temperature-sensor/issues/new?labels=i%3A+bug&template=1-bug-report.md">Report Bug</a>
    ·
    <a href="https://github.com/stiliajohny/hardware-sms-temperature-sensor/issues/new?labels=i%3A+enhancement&template=2-feature-request.md">Request Feature</a>
  </p>
</p>

<!-- TABLE OF CONTENTS -->

## Table of Contents

- [Table of Contents](#table-of-contents)
- [About The Project](#about-the-project)
  - [Built With](#built-with)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Roadmap](#roadmap)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)
- [Acknowledgements](#acknowledgements)

<!-- ABOUT THE PROJECT -->

## About The Project


[![Product Name Screen Shot][product-screenshot]](./.assets/screenshot.png)

This project is a POC  while researching for a bigger project that will be a GPS tracker.
The idea is to have a device that will be able to send SMS messages with the current temperature and humidity of the place where it is installed.
It can be connected to a solar panel and a battery to be able to work off the grid.


We are using a simple GSM module (SIM800L) and a temperature sensor (DHT11) to get the temperature and humidity of the place where the device is installed.

The simplicity of the SIM800L is that is using RX/TX serial communication  and it is small in size that can be easily integrated in a small device.

The DHT11 is a simple temperature sensor that is using a single wire to communicate with the microcontroller. Worth mentioning that the readings are not very accurate. It can be updated with a DHT22 sensor that is more accurate.


### Built With

- [Arduino](https://www.arduino.cc/)
- [ESP8266](https://www.ebay.co.uk/b/NodeMCU-Development-Kits-Boards/65507/bn_7028724683)
- [DHT11](https://www.ebay.co.uk/itm/303365781568)
- [SIM800L](https://www.ebay.co.uk/sch/i.html?_from=R40&_trksid=p2510209.m570.l2632&_nkw=sim800l&_sacat=92074)

---

<!-- GETTING STARTED -->

## Getting Started



### Prerequisites

- Hardware
  - ESP8266
  - SIM800L
  - DHT11
  - USB ( for the ESP8266 )
  - Jumper wires
  - Breadboard (optional but recommended)
- Software
  - Arduino IDE
  - Arduino ESP8266 Core
  - DHT Sensor Library


### Installation

Clone the repo

```sh
git clone git@github.com:stiliajohny/hardware-sms-temperature-sensor.git
```

Then open the project in the Arduino IDE make some edits as follows:

- In the SIM800L_DHT.ino file change the phone number to your phone number:

> The number needs to follow the international format. For example: +447123456789

```c
const String PHONE = "+447572785067";
```

- In the SIM800L_DHT.ino file change the serial baud rate to the one that you are using:
> The SIM800L module is using 9600 baud rate by default. If you are using a different baud rate you need to change it in the code.

> The default baud rate for the ESP8266 is 115200


```c
int SerialBaudRate = 115200;
int sms800BaudRate = 9600;
```



---

<!-- USAGE EXAMPLES -->

## Usage

After uploading the codet othe ESP8266 you can connect to the serial port and see the output of the device.
Now you need to observe the reception LED on the SIM800L module.

<!-- add an HTML table with no borders -->

<table border=0>
  <tr >
    <td align="center"><img src="./.assets/Netlight-LED-Blinking-Finding-Network-Connection.gif" alt="Reception LED" width="200" height="200"></td>
    <td align="center"><img src="./.assets/Netlight-LED-Blinking-Active-GPRS-Connection.gif" alt="SMS" width="200" height="200"></td>
    <td align="center"><img src="./.assets/Netlight-LED-Blinking-Network-Connection-Established.gif" alt="SMS" width="200" height="200"></td>
  </tr>
  <tr>
    <td align="center">The module is running but the connection to the cellular network has not yet been made.</td>
    <td align="center">The GPRS data connection you requested is active.</td>
    <td align="center">The module has made contact with the cellular network and can send/receive voice and SMS.</td>
</table>


After the device is connected to the cellular network you can send an SMS to the device with the following message:
```
get temperature
```

The device will reply back with the current temperature and humidity.

<img src="./.assets/sms-respond.jpeg" width=50%>


## Roadmap

See the [open issues](https://github.com/stiliajohny/hardware-sms-temperature-sensor/issues) for a list of proposed features (and known issues).

---

<!-- CONTRIBUTING -->

## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

---

<!-- LICENSE -->

## License

Distributed under the GPLv3 License. See `LICENSE` for more information.

<!-- CONTACT -->

## Contact

John Stilia - stilia.johny@gmail.com

<!--
Project Link: [https://github.com/your_username/repo_name](https://github.com/your_username/repo_name)
-->

---

<!-- ACKNOWLEDGEMENTS -->

## Acknowledgements

- [GitHub Emoji Cheat Sheet](https://www.webpagefx.com/tools/emoji-cheat-sheet)
- [Img Shields](https://shields.io)
- [Choose an Open Source License](https://choosealicense.com)
- [GitHub Pages](https://pages.github.com)

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[contributors-shield]: https://img.shields.io/github/contributors/stiliajohny/hardware-sms-temperature-sensor.svg?style=for-the-badge
[contributors-url]: https://github.com/stiliajohny/hardware-sms-temperature-sensor/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/stiliajohny/hardware-sms-temperature-sensor.svg?style=for-the-badge
[forks-url]: https://github.com/stiliajohny/hardware-sms-temperature-sensor/network/members
[stars-shield]: https://img.shields.io/github/stars/stiliajohny/hardware-sms-temperature-sensor.svg?style=for-the-badge
[stars-url]: https://github.com/stiliajohny/hardware-sms-temperature-sensor/stargazers
[issues-shield]: https://img.shields.io/github/issues/stiliajohny/hardware-sms-temperature-sensor.svg?style=for-the-badge
[issues-url]: https://github.com/stiliajohny/hardware-sms-temperature-sensor/issues
[license-shield]: https://img.shields.io/github/license/stiliajohny/hardware-sms-temperature-sensor?style=for-the-badge
[license-url]: https://github.com/stiliajohny/hardware-sms-temperature-sensor/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/johnstilia/
[product-screenshot]: .assets/screenshot.png
[ask-me-anything]: https://img.shields.io/badge/Ask%20me-anything-1abc9c.svg?style=for-the-badge
[personal-page]: https://github.com/stiliajohny
