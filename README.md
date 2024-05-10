
Mocking Bird Telephone Exchange Master Controller

![alt text](https://github.com/hwstar/fw-mockingbird-telephone-exchange-master-controller/assets/mess-o-wires-jpg "Prototype hardware")

Features:

* Runs on a STM32F767ZI Nucleo board
* Perform 2 channels of Multi-Frequency (MF) decoding using the Goertzel algorithm using an ADC input. (70 mS min tone on and off times)
* Communicates with Subscriber line and E&M trunk cards designed by me. (More information forthcoming on them).
* Interfaces with 2 Zarlink MT88L70 DTMF decoders
* Tone Plant
  - Call progress tones
  - DTMF and MF tone generation
  - Audio samples support one-shot sequences and loops. Can be used to send nostalgic network sounds.
  - 4 channels. 
  - Uses 2 TI PCM5102A DAC's to accomplish this.
* Calls are connected in analog form through 2 8X16 Zarlink crosspoint switches
* Retreives the audio samples from an SD Card hooked up to a SPI BUS.
* Supports up to 8 subscriber lines using 4 dual line cards.
* Supports up to 3 E&M trunk cards.

