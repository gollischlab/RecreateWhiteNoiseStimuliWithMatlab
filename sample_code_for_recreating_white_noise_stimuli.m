% sample usage of routines for recreating stimulus random number lists

% set mode to 1 for full-field Gaussian flicker
% and to 2 for spatiotemporal binary white noise
mode = 1;

% writing files disabled by default
% set to true to write files as specified below
save_to_file = false;

if( mode == 1 )
    % full-field Gaussian white noise for 1000 frames; seed set to -1000
    Nframes = 1000;
    seed = -1000;
    stim = squeeze(recreateGaussianWhiteNoiseStimulus(1, 1, Nframes, seed));
    % squeeze turns the 3dim object into a 1dim array
    
    % stim is an array of Gaussian random numbers, which could now be used
    % in a program for analysis
    % or saved to file, see below

    % save to file
    if( save_to_file )
        filename = 'stimulus_fff_Gaussian_seed_m1000.txt';
        dlmwrite(filename, stim); % saves one number per line
    end;
end;

if( mode == 2 )
    % spatiotemporal binary white noise with 80 pixels in x, 60 pixels in y,
    % and 10 frames; seed set to -1000
    Nx = 80;
    Ny = 60;
    Nframes = 10;
    seed = -1000;
    stim = recreateBinaryWhiteNoiseStimulus(Nx, Ny, Nframes, seed);

    % stim is a 3d object of binary random numbers (-1 or 1), which could
    % now be used in a program for analysis
    % or saved to file, see below

    % save frame-by-frame to files (be careful: many files if Nframes is large
    if( save_to_file )
        for i=1:Nframes
            filename = sprintf('stimulus_spatiotemporal_binary_frame%06d.txt', i );
            dlmwrite(filename, stim(:,:,1));
            % saves the intensity values for each row (horizontal line on the screen)
            % as one line in the file, with values for different vertical columns separated by commas
            % different lines correspond to different horizontal lines on
            % the screen
        end;
    end;
end;
