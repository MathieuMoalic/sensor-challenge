run:
    sudo chmod 777 /dev/ttyACM0
    arduino-cli compile --upload -p /dev/ttyACM0 --fqbn arduino:avr:uno .