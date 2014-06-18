%% This is the simulation file for testing & designing of beat detection
%% algorithm. What we have implemented here is a very simple beat degtetion
%% algorithm. Our entire algorithm operates in the time domain. The
%% algorithm design has been done considering the real time hard deadlines
%% placed by the application.Also,the algorithm has been kept simple
%% keeping in mind the hardware on which the algorithm would run is a
%% typical low end hardware (a simple Android and bluetooth compatible 
%% smartphone, for eg).


%% clear everything 
clc;
clear all;
close all;
%% Initialise data: read the song, set the song, window sizes 
song_array = wavread('1.wav');
size = size(song_array);
size_song = size(1,1);
window = 200;
size_avg_array = floor(size_song/window);

%% Find the average chunk energies
avg_array = zeros(size_avg_array,1);
for i=1:1:size_avg_array
    sum = 0;
    for j=1:1:window
        sum = sum + song_array((i-1)*window+j,1)^2;
    end
    sum = sum/window;
    avg_array(i,1) = sum;
end

%% Perform naive thresholding based on the a threshldng factor of 1/4
max = max(avg_array);
thresh_avg_array = zeros(size_avg_array,1);
thinned_array = zeros(size_avg_array,1);
for i=1:1:size_avg_array
    if(avg_array(i,1) > max/4)
    thresh_avg_array(i,1) = 1;
    end
end
subplot(3,1,1);
plot(song_array);axis tight
title('Waveform');
subplot(3,1,2)
plot(avg_array);axis tight
title('Average Energy');
subplot(3,1,3);

%% Perform naive thresholding based on the maximum beat frequency,( or the min beat interval) 
max_beat_freq = 10;
f_sampling = 44100;
min_beat_repeat_chunks = f_sampling/(max_beat_freq*window);
current_ptr = 1;
num_beats = 0;
for i=1:1:size_avg_array
    if((i > current_ptr) &&(thresh_avg_array(i,1)==1))
    thinned_array(i,1) = 1;
    current_ptr = i + min_beat_repeat_chunks;
    num_beats = num_beats + 1;
    end
end

%% fill in the beat location array, the array containing the location of the beats.
beat_locations_array = zeros(num_beats,1);
count = 1;
for i=1:1:size_avg_array
    if(thinned_array(i,1) == 1)
    beat_locations_array(count,1) = i;
    count= count+1;
    end
end


%% Perform period determination based on the maximum beats per period. We take 10 as the max beats per period
stdev = zeros(10,1);
sum2 = 0;
sum = 0;
for j=1:1:10
    sum = 0;
    sum2 = 0;
    for i=1:1:(num_beats-j)
      sum2 = sum2 + (beat_locations_array(i+j,1) - beat_locations_array(i,1))^2;
      sum = sum + (beat_locations_array(i+j,1) - beat_locations_array(i,1));
    end
    sum2 = sum2/(num_beats-j);
    sum = sum/(num_beats-j);
    std = sum2 - sum^2; 
    stdev(j,1) = std;
end

plot(thinned_array);axis tight
title('Beats Detected');
