# RecreateWhiteNoiseStimuliWithMatlab
Matlab code to recreate random number lists for white noise stimuli in the lab

This repository contains Matlab code to recreate the lists of random numbers used in white-noise experiments in the Gollisch lab.
The random-number sequences are needed for analyzing the spike responses of recorded cells under white-noise stimulation.

Binary white noise (as sequences of 1 and -1) is recreated via the function 
stimulus = recreateBinaryWhiteNoiseStimulus(Nx, Ny, Nframes, seed),
where Nx, Ny, and Nframes are required parameters that specify the number of pixels in x and y and the number of frames (time).
The optional parameter seed can be used to specify the seed for the random number generator (default is -10000).
The output is a Ny-by-Nx-by-Nframes where, for example, stim(3,4,5) would be the pixel contrast (1 or -1) in the 3rd horizontal row
(from the bottom of the screen) and 4th vertical column during the 5th presented frame.
The procedure is contained in the binary mex file recreateBinaryWhiteNoiseStimulus.mexw64. This should run as is under Windows 64-bit.
If not or if a different operating system is used, the mex file might need to be created by compiling the corresponding cpp file in Matlab:
mex recreateBinaryWhiteNoiseStimulus.cpp
An example of how to use it is given in sample_code_for_recreating_white_noise_stimuli.m.

Gaussian white noise (zero mean, unity standard deviation) is handled in essentially the same way by the function
stimulus = recreateGaussianWhiteNoiseStimulus(Nx, Ny, Nframes, seed).
