# Power Consumption Monitor

A small measurement device that records the power consumption of a connected device (DUT, device under test) and streams the data to a PC for analysis.

> **Status:** work in progress. See [Status and roadmap](#status-and-roadmap).

## Overview

The firmware runs on an STM32F302 (Nucleo-F302R8). It reads current, bus voltage, power and temperature from an INA228 power monitor over I2C, timestamps each sample, adds the state of four digital marker inputs, and sends everything as CSV through the ST-LINK virtual COM port (UART) to the PC.

The marker inputs let you tag events of the DUT (for example "Wi-Fi on" or "sleep entered") directly in the data, so you can correlate them with the current waveform.

## Features

- Current, bus voltage, power and temperature measurement with the INA228
- Microsecond timestamps from a hardware timer
- 4 digital marker inputs (`GPIO_MARK_0..3`) recorded with every sample
- Calibration (zero offset, gain, temperature compensation) stored in flash
- Non-blocking CSV streaming over UART with DMA
- Overflow detection: samples lost when the PC cannot keep up are counted
- Control from the PC with serial commands

## Hardware

| Part | Purpose |
| --- | --- |
| Nucleo-F302R8 (STM32F302R8) | MCU and ST-LINK programmer with a virtual COM port |
| INA228 module | Current / voltage / power / temperature sensor, connected over I2C |
| DUT | The device being measured, connected through the INA228 shunt |

Connections:

- **INA228:** I2C (`INA228_I2C_SCL`, `INA228_I2C_SDA`)
- **Markers:** `GPIO_MARK_0` to `GPIO_MARK_3` are inputs for digital signals from the DUT
- **PC:** USART TX/RX routed to the ST-LINK virtual COM port, so only the Nucleo USB cable is needed

Shunt resistor value and measurement range: TBD.

## How it works

1. Read a measurement from the INA228.
2. Apply calibration (offset, gain, temperature compensation).
3. Add a timestamp and the marker state to form a sample.
4. Store the sample in a ring buffer.
5. Format samples as CSV lines.
6. Send the lines to the ST-LINK over UART using DMA.

Acquisition and transmission are decoupled by the ring buffer, so UART speed does not affect the sampling timing. If the buffer overflows, the loss is counted and not silent.

A detailed description with class diagrams is in [docs/architecture.md](docs/architecture.md).

## Data format

Each sample is one CSV line preceded by a single header line:

| Column | Unit | Description |
| --- | --- | --- |
| `t_us` | µs | Timestamp from the hardware timer |
| `current_A` | A | Calibrated current |
| `vbus_V` | V | Bus voltage |
| `power_W` | W | Power |
| `temp_C` | °C | Sensor temperature |
| `marks` | bit mask | State of `GPIO_MARK_0..3` |

The exact column order and number formatting are defined by `CsvLogFormatter`.

Sampling rate and UART baud rate: TBD.

## Commands

The device is controlled with text commands over the same virtual COM port. The following operations are supported:

- start measurement
- stop measurement
- zero calibration (measure the offset with no load)
- gain calibration (against a known reference current)

The exact command syntax: TBD.

## Calibration

1. **Zero:** disconnect the load and run the zero calibration to store the current offset.
2. **Gain:** connect a known reference current and run the gain calibration with that value.

Parameters (offset, gain, temperature coefficient, reference temperature) are saved to flash with a version and CRC and are loaded on start-up.

## Repository layout

| Path | Content |
| --- | --- |
| `Core/` | STM32CubeMX-generated startup and peripheral code |
| `App/` | Main application business logic (`MeasurementController`) |
| `Modules/` | Classes that implement separate parts of the business logic (for example `SampleBuilder`, `Transmitter`, `Calibrator`) |
| `Drivers/` | Drivers for hardware components |
| `ThirdParty/` | External modules developed by third parties |
| `Docs/` | Architecture description and diagrams |

## Status and roadmap

The project is under development. Done or in progress:

- [x] Project skeleton and peripheral configuration (CubeMX)
- [ ] INA228 sensor integration
- [ ] Sampling, timestamps and marker inputs
- [ ] Ring buffer and CSV transmission over UART DMA
- [ ] Calibration with flash storage
- [ ] Serial command interface
- [ ] Final sampling rate, baud rate and measurement range
- [ ] PC-side example script for plotting the data
