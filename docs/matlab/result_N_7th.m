% Step 1: Load the data from the CSV file
data = readtable('post_filtering_ord7th_PB5_SB30.csv', 'Delimiter', ';'); % Load the CSV file with semicolon delimiter

% Display the variable names to check for discrepancies
disp('Variable names in the dataset:');
disp(data.Properties.VariableNames);

% Step 2: Generate a time vector
num_samples = height(data); % Number of samples in the dataset
total_time = 15; % Total time in seconds for the second dataset
time_ms = linspace(0, total_time * 1000, num_samples)'; % Time in milliseconds

% Step 3: Calculate the phase delay
% Check if the expected variable names exist
if all(ismember({'x_f', 'y_f', 'z_f', 'x', 'y', 'z'}, data.Properties.VariableNames))
    % Calculate the phase of the filtered and non-filtered data
    phase_x_f = angle(fft(data.x_f)); % Phase of filtered X
    phase_x = angle(fft(data.x));       % Phase of non-filtered X
    phase_y_f = angle(fft(data.y_f));   % Phase of filtered Y
    phase_y = angle(fft(data.y));       % Phase of non-filtered Y
    phase_z_f = angle(fft(data.z_f));   % Phase of filtered Z
    phase_z = angle(fft(data.z));       % Phase of non-filtered Z

    % Calculate the phase delay (in radians)
    phase_delay_x = phase_x_f - phase_x; % Phase delay for X
    phase_delay_y = phase_y_f - phase_y; % Phase delay for Y
    phase_delay_z = phase_z_f - phase_z; % Phase delay for Z

    % Step 4: Add the time vector as a new column to the dataset
    data.time_ms = time_ms; % Add the time vector to the table

    % Step 5: Save the modified dataset to a new CSV file
    writetable(data, 'post_filtering_second_with_time.csv'); % Save to new CSV file

    % Display the phase delays
    disp('Phase Delay (in radians):');
    disp('X:');
    disp(phase_delay_x);
    disp('Y:');
    disp(phase_delay_y);
    disp('Z:');
    disp(phase_delay_z);

    % Step 6: Frequency Analysis
    % Calculate the magnitude spectrum
    mag_x_f = abs(fft(data.x_f)); % Magnitude of filtered X
    mag_x = abs(fft(data.x));      % Magnitude of non-filtered X
    mag_y_f = abs(fft(data.y_f));  % Magnitude of filtered Y
    mag_y = abs(fft(data.y));      % Magnitude of non-filtered Y
    mag_z_f = abs(fft(data.z_f));  % Magnitude of filtered Z
    mag_z = abs(fft(data.z));      % Magnitude of non-filtered Z

    % Frequency vector for plotting
    N = length(data.x_f); % Number of samples
    f = (0:N-1)*(200/N);   % Frequency range based on the sampling frequency (200 Hz)

    % Create a new figure for frequency analysis
    figure;

    % Plot magnitude spectrum for X
    subplot(3, 1, 1);
    plot(f, mag_x, 'b-', 'LineWidth', 1.5); % Non-filtered
    hold on;
    plot(f, mag_x_f, 'r-', 'LineWidth', 1.5); % Filtered
    title('Magnitude Spectrum for X Axis');
    xlabel('Frequency (Hz)');
    ylabel('Magnitude');
    xlim([1 195]); % Set x-axis limits to remove below 1 Hz and above 195 Hz
    legend('Non-Filtered', 'Filtered');
    grid on;

    % Plot magnitude spectrum for Y
    subplot(3, 1, 2);
    plot(f, mag_y, 'b-', 'LineWidth', 1.5); % Non-filtered
    hold on;
    plot(f, mag_y_f, 'r-', 'LineWidth', 1.5); % Filtered
    title('Magnitude Spectrum for Y Axis');
    xlabel('Frequency (Hz)');
    ylabel('Magnitude');
    xlim([1 195]); % Set x-axis limits
    legend('Non-Filtered', 'Filtered');
    grid on;

    % Plot magnitude spectrum for Z
    subplot(3, 1, 3);
    plot(f, mag_z, 'b-', 'LineWidth', 1.5); % Non-filtered
    hold on;
    plot(f, mag_z_f, 'r-', 'LineWidth', 1.5); % Filtered
    title('Magnitude Spectrum for Z Axis');
    xlabel('Frequency (Hz)');
    ylabel('Magnitude');
    xlim([1 195]); % Set x-axis limits
    legend('Non-Filtered', 'Filtered');
    grid on;

    % Step 7: Plot the phase delays
    % Create a new figure for phase delays
    figure;

    % Plot phase delay for X
    subplot(3, 1, 1);
    plot(f, phase_delay_x, 'b-', 'LineWidth', 1.5);
    title('Phase Delay for X Axis');
    xlabel('Frequency (Hz)');
    ylabel('Phase Delay (radians)');
    xlim([1 195]); % Set x-axis limits
    grid on;

    % Plot phase delay for Y
    subplot(3, 1, 2);
    plot(f, phase_delay_y, 'r-', 'LineWidth', 1.5);
    title('Phase Delay for Y Axis');
    xlabel('Frequency (Hz)');
    ylabel('Phase Delay (radians)');
    xlim([1 195]); % Set x-axis limits
    grid on;

    % Plot phase delay for Z
    subplot(3, 1, 3);
    plot(f, phase_delay_z, 'g-', 'LineWidth', 1.5);
    title('Phase Delay for Z Axis');
    xlabel('Frequency (Hz)');
    ylabel('Phase Delay (radians)');
    xlim([1 195]); % Set x-axis limits
    grid on;

else
    error('One or more expected variable names are missing from the dataset.');
end
