% FIR Filter Design and Acceleration Data Processing
% This program designs a lowpass FIR filter based on frequency analysis
% and processes acceleration data from a CSV file. The filter coefficients
% are intended for implementation in an STM32 microcontroller.

% Step 1: Define the sampling frequency and design the FIR filter
sampling_frequency = 200; % Sampling frequency in Hz

% Design a lowpass FIR filter
LPFilter = designfilt('lowpassfir', ...
                       'Filterorder', 10, ...          % Order of the filter
                       'StopbandFrequency', 50, ...    % Frequency at which the filter starts to attenuate
                       'PassbandFrequency', 15, ...     % Frequency at which the filter allows signals to pass
                       'SampleRate', sampling_frequency); % Sampling rate for the filter

% Step 2: Import acceleration data from a CSV file
data = readtable('raw_cmps_acc_x_y_z.csv', 'Delimiter', ';'); % Read data from CSV

% Extract acceleration and time data for each axis (X, Y, Z)
acc_x = data.acc_x(120:end); % Acceleration in X, starting from index 120
time_ms_x = data.time_ms(120:end); % Time in milliseconds for X

acc_y = data.acc_y(120:end); % Acceleration in Y, starting from index 120
time_ms_y = data.time_ms(120:end); % Time in milliseconds for Y

acc_z = data.acc_z(120:end); % Acceleration in Z, starting from index 120
time_ms_z = data.time_ms(120:end); % Time in milliseconds for Z

% Step 3: Apply the FIR filter to the acceleration data
filtered_acc_x = filter(LPFilter, acc_x); % Filtered acceleration in X
filtered_acc_y = filter(LPFilter, acc_y); % Filtered acceleration in Y
filtered_acc_z = filter(LPFilter, acc_z); % Filtered acceleration in Z

% Function to process and plot acceleration data
function process_and_plot_acceleration(acc, filtered_acc, time_ms, axis_label)
    % This function processes the acceleration data and plots the original
    % and filtered data along with their frequency spectra.

    % Frequency Analysis
    N = length(acc); % Number of samples in the acceleration data
    f = (0:N-1)*(200/N); % Frequency range based on the sampling frequency

    % FFT of original acceleration data
    Y_original = fft(acc); % Compute the FFT
    P2_original = abs(Y_original/N); % Two-sided spectrum
    P1_original = P2_original(1:N/2+1); % Single-sided spectrum
    P1_original(2:end-1) = 2*P1_original(2:end-1); % Correct amplitude for single-sided spectrum

    % Remove the 0 Hz component from the frequency spectrum
    P1_original(1) = 0; % Set the 0 Hz component to 0

    % FFT of filtered acceleration data
    Y_filtered = fft(filtered_acc); % Compute the FFT of the filtered data
    P2_filtered = abs(Y_filtered/N); % Two-sided spectrum
    P1_filtered = P2_filtered(1:N/2+1); % Single-sided spectrum
    P1_filtered(2:end-1) = 2*P1_filtered(2:end-1); % Correct amplitude for single-sided spectrum

    % Remove the 0 Hz component from the frequency spectrum
    P1_filtered(1) = 0; % Set the 0 Hz component to 0

    % Create a new figure for the current axis
    figure('Name', ['Acceleration Data - ' axis_label]);

    % Plot original acceleration data
    subplot(2, 2, 1);
    plot(time_ms, acc, 'b-', 'LineWidth', 1.5); % Plot original data in blue
    title(['Original Acceleration ' axis_label]);
    xlabel('Time (ms)');
    ylabel(['Acceleration (' axis_label ')']);
    grid on;

    % Plot filtered acceleration data
    subplot(2, 2, 2);
    plot(time_ms, filtered_acc, 'r-', 'LineWidth', 1.5); % Plot filtered data in red
    title(['Filtered Acceleration ' axis_label]);
    xlabel('Time (ms)');
    ylabel(['Acceleration (' axis_label ')']);
    grid on;

    % Plot frequency analysis for original data
    subplot(2, 2, 3);
    plot(f(1:N/2+1), P1_original, 'b-', 'LineWidth', 1.5); % Plot original frequency spectrum in blue
    title(['Frequency Spectrum of Original Acceleration ' axis_label]);
    xlabel('Frequency (Hz)');
    ylabel('Magnitude |P1(f)|'); % Magnitude of the frequency spectrum
    grid on;

    % Plot frequency analysis for filtered data
    subplot(2, 2, 4);
    plot(f(1:N/2+1), P1_filtered, 'r-', 'LineWidth', 1.5); % Plot filtered frequency spectrum in red
    title(['Frequency Spectrum of Filtered Acceleration ' axis_label]);
    xlabel('Frequency (Hz)');
    ylabel('Magnitude |P1(f)|'); % Magnitude of the frequency spectrum
    grid on;
end

% Process and plot for each axis (X, Y, Z)
process_and_plot_acceleration(acc_x, filtered_acc_x, time_ms_x, 'X');
process_and_plot_acceleration(acc_y, filtered_acc_y, time_ms_y, 'Y');
process_and_plot_acceleration(acc_z, filtered_acc_z, time_ms_z, 'Z');

% Display the coefficients of the filter for implementation in STM32
disp('Filter Coefficients:');
disp(LPFilter.Coefficients);

