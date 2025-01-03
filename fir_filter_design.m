% Extract coefficient of FIR Filter

sampling_period =  7 * 10^-3; % 7ms
sampling_frequency = 1/sampling_period;

% Design the lowpass FIR filter
LPFilter = designfilt('lowpassfir', ...
                       'Filterorder', 8, ...
                       'StopbandFrequency', 20, ...
                       'PassbandFrequency', 5, ...
                       'SampleRate', sampling_frequency);

fvtool(LPFilter)
LPFilter.Coefficients
