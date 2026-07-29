# Stretchable Capacitive Strain Sensor


![Exploded layer stack of the strain sensor (PI backing, top Ecoflex, MWCNT, dielectric layer, MWCNT, bottom Ecoflex, clincher tab) and a photo of the finished sensor with a 1 cm scale bar](images/capsense-fig01-sensor-layer-stack.png)

*Custom strain sensor: spray-coated multiwall carbon nanotubes (MWCNTs) on Ecoflex*

## Using Single PI Connector at the Center of the Sensor

**Step 1**: blade coat Ecoflex on a glass substrate. Next, spray coat the first CNT layer. Then, cover the contact pad with a film or tape. After that, blade coat the middle Ecoflex layer.

![Schematic of the release tape/film placed over the contact pad before the middle Ecoflex layer is coated](images/capsense-fig02-step1-diagram.png)

![Photo of four spray-coated CNT strips on fabric, with the release tape/film over each contact pad highlighted](images/capsense-fig03-step1-photo.png)

**Step 2**: remove the tape to expose the contact pad. Then, spray coat the second CNT Layer.

![Schematic showing the contact pad exposed after removing the release tape](images/capsense-fig04-step2-diagram.png)

![Photo of the sensor strips after the second CNT spray coat, laid out on a cutting mat](images/capsense-fig05-step2-photo.png)

**Step 3**: Blade coat the top Ecoflex layer, but don't cover the exposed contact pad.

![Schematic indicating that both contact pads remain exposed after the top Ecoflex coat](images/capsense-fig06-step3-diagram.png)

![Photo of the sensor strips with the top Ecoflex mask in place, showing where the second contact pad should be covered with film before coating](images/capsense-fig07-step3-photo-mask.png)

![Photo of the finished strips with both contact pads exposed after the top Ecoflex coat](images/capsense-fig08-step3-photo-exposed-pads.png)

**Step 4:** prepare a PCB or PI/electrode with the two electrodes exposed, then bond it to the two CNT contact pads using Ag paste.

![Schematic of the PCB/PI electrode being bonded to the two CNT contact pads with Ag paste](images/capsense-fig09-step4-diagram.png)

![Three photos showing the 126-49 Ag paste bond, the sputtered copper traces on a PI film, and the extra stiffener layer/epoxy added to strengthen the connector when the sensor is stretched](images/capsense-fig10-step4-photos.png)

## CAD Outline and Dimensions Reference



![Full CAD outline of the sensor: cyan trace is the sensor contour, red trace is the CNT region, yellow trace is the PI stiffener/board, dimensioned at 20.0000 x 4.5000](images/capsense-fig11-cad-outline.png)

- **Blue trace:** sensor contour
- **Red trace:** CNT region
- **Yellow trace:** PI stiffener/board

![Zoomed CAD view of the two contact pads, with arrows marking where silver paste contacts the CNT and where the connector attaches to the PCB](images/capsense-fig12-cad-zoom-silverpaste.png)

![Dimensioned CAD drawing of the PI stiffener/board footprint (6.0000 x 4.5000 overall, with 0.7500-3.7500-1.5000 pad spacing)](images/capsense-fig13-cad-dimensions.png)

## Sensor Integrated with CapSense

![Pcap04 eval board with pin labels: VDD, GND, Chip detect, IIC_EN, SSN_PG0, MOSI_SDA, SCK_SCL, MISO_PG1, PG5](images/capsense-fig14-pcap04-eval-board.png)

![The CapSense PCB (I2C wires, PCap04 chip, epoxy strain relief) connected to the strain sensor via silver paste, with a 1 cm scale bar](images/capsense-fig15-pcb-connector-photo.png)

Successful reading from the evaluation board using an STM32 nucleo board via I2C.

![Terminal screenshot of the Pcap04 evaluation board output, showing repeated measured capacitance readings in pF](images/capsense-fig16-terminal-output.png)

![Photos of the CapSense PCB, the wired STM32 nucleo board setup, and a terminal window streaming real-time capacitance readings](images/capsense-fig17-integration-photos.png)

**Instruction:**

- Please upload the "CapMonitor_STM32_V2" code to the STM32L476RG nucleo board.
- The Pcap04 chip on the CapSense PCB has 3 capacitance reading channels. The sensor capacitance will be recorded by the second channel. Open a serial monitor to read the real-time capacitance value.

---
