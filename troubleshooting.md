# Troubleshooting & Sensor Calibration

## 1. Sensor Calibration
* **Soil Moisture Sensor:** Analog readings range from `0` (completely submerged/wet) to `1023` (completely dry). Depending on your soil type (clay, sandy, potting mix), adjust the `SOIL_DRY_THRESHOLD` constant in the source code.
* **DHT11 Accuracy:** Ensure the sensor is placed away from direct water splashes to prevent permanent hardware damage. Allow a 2-second stabilization delay during startup.

## 2. Environmental Protection
* **Moisture Damage:** Greenhouses feature high humidity levels. It is strongly recommended to apply conformal coating or enclosure protection to the Arduino board and relay terminals to prevent short circuits due to condensation.

## 3. Power Resets (Brownouts)
* If the Arduino unexpectedly resets or freezes when the water pump or fan kicks in, it indicates a voltage drop caused by inductive load spikes. Ensure your actuators are powered by an independent external power supply separate from the logic board.
