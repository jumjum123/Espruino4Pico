# Espruino for Raspberry PICO RPI2040

## why
Espruino is a welknown Javascript implementation for smallest computer.
RPI2040 boards are cheap and powerful. On the other hand they need power to run.
Gordon focussed Espruino on low power boards. And he needs to make money for his family, which is hard to do with cheap boards like this.
Nevertheless he supported a lot in this project.

## how
Espruino itself uses an impressif make file. PICO-SDk is based on cmake.
Having in mind my experiences with ESP32, the decision was to try it the other way.
There are a lot of examples available in pico-examples. So decision was to give it a try and compile Espruino similiar to examples. This was extremly easy to do, even for somebody like me, with poor or even no knowledge in make/cmake

## installation
Simple way is to install pico sdk, pico examples and toolchain following manual getting-started-with-pico.pdf.
Next create a subdirectory in pico-examples named Espruino.
Copy everything from tis project into Espruino Folder.
Add a line to CMakeLists.txt in folder pico-examples
Last execute buildExample.sh Espruino
Boarspecific files like jswrapper.c are created with RPI2040gen.sh

## work on this
You are welcome to help.
To be open, you are not welcome to tell me what I should do.
Experience like "my boss expects me to do this, I am waiting" brought me to this point.