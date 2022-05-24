#project(Espruino DESCRIPTION "Espruino for RPI2040")

pico_sdk_init()

add_definitions(-DJSVAR_MALLOC -DUSB -DUSE_HEATSHRINK)

add_executable(Espruino main.c
	targets/RPI2040/jshardwareConsole.c
	targets/RPI2040/jshardware.c
	targets/RPI2040/jshardwarePin.c
	targets/RPI2040/jshardwareAnalog.c
	targets/RPI2040/jshardwareFlash.c
	targets/RPI2040/jshardwareSPI.c
	targets/RPI2040/jshardwareI2C.c
	targets/RPI2040/jshardwarePulse.c
	targets/RPI2040/jshardwarePWM.c
	targets/RPI2040/jshardwareTimer.c
    targets/RPI2040/jshardwareUart.c
	targets/RPI2040/jshardwareTools.c
	src/jslex.c
	src/jsflags.c 
	src/jsflash.c 
	src/jsvar.c 
	src/jsvariterator.c 
	src/jsutils.c 
	src/jsnative.c 
	src/jsparse.c 
	src/jspin.c 
	src/jsinteractive.c 
	src/jsdevices.c 
	src/jstimer.c 
	src/jsi2c.c 
	src/jsserial.c 
	src/jsspi.c 
	src/jshardware_common.c 
	jswrapper.c 
	libs/compression/heatshrink/heatshrink_encoder.c 
	libs/compression/heatshrink/heatshrink_decoder.c 
	libs/compression/compress_heatshrink.c 
	libs/compression/compress_rle.c
	gen/jspininfo.c 
	src/jswrap_array.c 
	src/jswrap_arraybuffer.c 
	src/jswrap_dataview.c 
	src/jswrap_date.c 
	src/jswrap_error.c 
	src/jswrap_espruino.c 
	src/jswrap_flash.c 
	src/jswrap_functions.c 
	src/jswrap_interactive.c 
	src/jswrap_io.c 
	src/jswrap_json.c 
	src/jswrap_modules.c 
	src/jswrap_pin.c 
	src/jswrap_number.c 
	src/jswrap_object.c 
	src/jswrap_onewire.c 
	src/jswrap_pipe.c 
	src/jswrap_process.c 
	src/jswrap_promise.c 
	src/jswrap_regexp.c 
	src/jswrap_serial.c 
	src/jswrap_storage.c 
	src/jswrap_spi_i2c.c 
	src/jswrap_stream.c 
	src/jswrap_string.c 
	src/jswrap_waveform.c  
	libs/compression/jswrap_heatshrink.c 
	libs/math/jswrap_math.c
	libs/graphics/jswrap_graphics.c
	libs/graphics/graphics.c
)

target_link_libraries(Espruino 
  pico_stdlib
  hardware_adc
  hardware_flash
  hardware_i2c
  hardware_spi
  hardware_pwm
)

add_subdirectory(targets)
include_directories(
  targets/RPI2040
  src
  gen
  libs/compression
  libs/compression/heatshrink
  libs/math
  libs/graphics
  libs/
)

pico_enable_stdio_usb(Espruino 1)
pico_enable_stdio_uart(Espruino 0)

pico_add_extra_outputs(Espruino)

example_auto_set_url(Espruino)


