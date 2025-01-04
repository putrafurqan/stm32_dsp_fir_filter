% Step 1: Extract coefficient of FIR Filter

sampling_period =  50 * 10^-3; % 7ms
sampling_frequency = 1/sampling_period;

% Design the lowpass FIR filter
LPFilter = designfilt('lowpassfir', ...
                       'Filterorder', 10, ...
                       'StopbandFrequency', 6, ...  % Adjust as needed
                       'PassbandFrequency', 5, ...
                       'SampleRate', sampling_frequency);

% Step 2: Import the data from the CSV file
data = readtable('TFMINI_DATA.csv', 'Delimiter', ';');

% Extract time and distance data
time_ms = data.time_ms; % Time in milliseconds
distance_cm = data.distance_cm; % Distance in centimeters

% Step 3: Apply the filter to the distance data
filtered_distance = filter(LPFilter, distance_cm);

% Step 4: Display the original and filtered data
figure;

% Plot original data
subplot(2, 2, 1);
plot(time_ms, distance_cm, 'b-', 'LineWidth', 1.5);
title('Original Distance Data');
xlabel('Time (ms)');
ylabel('Distance (cm)');
grid on;

% Plot filtered data
subplot(2, 2, 2);
plot(time_ms, filtered_distance, 'r-', 'LineWidth', 1.5);
title('Filtered Distance Data');
xlabel('Time (ms)');
ylabel('Distance (cm)');
grid on;

% Step 5: Frequency Analysis
N = length(distance_cm); % Number of samples
f = (0:N-1)*(sampling_frequency/N); % Frequency range

% FFT of original data
Y_original = fft(distance_cm);
P2_original = abs(Y_original/N); % Two-sided spectrum
P1_original = P2_original(1:N/2+1); % Single-sided spectrum
P1_original(2:end-1) = 2*P1_original(2:end-1); % Correct amplitude

% FFT of filtered data
Y_filtered = fft(filtered_distance);
P2_filtered = abs(Y_filtered/N); % Two-sided spectrum
P1_filtered = P2_filtered(1:N/2+1); % Single-sided spectrum
P1_filtered(2:end-1) = 2*P1_filtered(2:end-1); % Correct amplitude

% Plot frequency analysis
subplot(2, 2, 3);
plot(f(1:N/2+1), P1_original, 'b-', 'LineWidth', 1.5);
title('Frequency Spectrum of Original Data');
xlabel('Frequency (Hz)');
ylabel('|P1(f)|');
grid on;

subplot(2, 2, 4);
plot(f(1:N/2+1), P1_filtered, 'r-', 'LineWidth', 1.5);
title('Frequency Spectrum of Filtered Data');
xlabel('Frequency (Hz)');
ylabel('|P1(f)|');
grid on;

% Display the coefficients of the filter
disp('Filter Coefficients:');
disp(LPFilter.Coefficients);
