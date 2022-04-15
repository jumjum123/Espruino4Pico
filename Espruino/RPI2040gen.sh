# user pico
cd /home/pico/pico-examples/Espruino

# to be done BOARD=RPI2040 make boardjson >gen/boardjson.txt

# ??? BOARD=RPI2040 make docs >gen/docs.txt

#copy wrapperfiles from gen/boardjson.txt(see above how to create this file)
python scripts/build_jswrapper.py src/jswrap_array.c src/jswrap_arraybuffer.c src/jswrap_dataview.c src/jswrap_date.c src/jswrap_error.c src/jswrap_espruino.c src/jswrap_flash.c src/jswrap_functions.c src/jswrap_interactive.c src/jswrap_io.c src/jswrap_json.c src/jswrap_modules.c src/jswrap_pin.c src/jswrap_number.c src/jswrap_object.c src/jswrap_onewire.c src/jswrap_pipe.c src/jswrap_process.c src/jswrap_promise.c src/jswrap_regexp.c src/jswrap_serial.c src/jswrap_storage.c src/jswrap_spi_i2c.c src/jswrap_stream.c src/jswrap_string.c src/jswrap_waveform.c libs/compression/jswrap_heatshrink.c libs/math/jswrap_math.c -BRPI2040 -Fgen/jswrapper.c

python scripts/build_pininfo.py RPI2040 gen/jspininfo.c gen/jspininfo.h

python scripts/build_platform_config.py RPI2040 gen/platform_config.h

cp gen/jswrapper.c jswrapper.c

cd
./buildExample.sh Espruino