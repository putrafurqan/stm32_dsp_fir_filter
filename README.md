# Filter Design in STM32 for Filtering IMU Data

This project implements a Lowpass FIR filter on the STM32 microcontroller to filter IMU (Inertial Measurement Unit) data. The filter design is based on the CMSIS DSP library.

## Filter Specifications

### 10th Order Filter
- **Passband**: 15 Hz
- **Stopband**: 50 Hz
- **Coefficients**: 
coeff = [-0.0220, -0.0339, 0.0072, 0.1235, 0.2618, 0.3244, 0.2618, 0.1235, 0.0072, -0.0339, -0.0220]


### 7th Order Filter
- **Passband**: 5 Hz
- **Stopband**: 30 Hz
- **Coefficients**: 
coeff = {0.0714, 0.1030, 0.1455, 0.1711, 0.1711, 0.1455, 0.1030, 0.0714}

1. **Gathering Sensor Data**: 
   - The raw accelerometer data for the 3-axis is located in `docs/data/raw_cmps_acc_x_y_z.csv`.

2. **Processing the Data**: 
   - The data was processed using the script located in `docs/matlab/main_filter_design.m`. 
   - The results of the filter design are saved as images:
     - For the 7th order filter with a passband of 5 Hz and a stopband of 30 Hz: 
       - ![7th Order Filter Design](docs/img/2_filter_design_pb5hz_sb30hz_y.jpg)
     - For the 10th order filter with a passband of 15 Hz and a stopband of 50 Hz: 
       - ![10th Order Filter Design](docs/img/5_filter_design_pb15hz_sb50hz_y.jpg)

3. **Obtaining Filter Coefficients**: 
   - The coefficients of the designed filters have been calculated and will be used in the STM32 code implementation.


