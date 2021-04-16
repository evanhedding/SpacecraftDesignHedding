format long

ID = fopen('vibeTestBONUS.txt');
file1 = textscan(ID, '%f'); %%Reads the data up until the completion statement
data1 = file1{1,1};
useless_1 = textscan(ID, '%s', 4); %%Removes the sentence after each run

file2 = textscan(ID, '%f');
data2 = file2{1,1};
useless_2 = textscan(ID, '%s', 4);

file3 = textscan(ID, '%f');
data3 = file3{1,1};
useless_3 = textscan(ID, '%s', 4);

file4 = textscan(ID, '%f');
data4 = file4{1,1};
useless_4 = textscan(ID, '%s', 4);

file5 = textscan(ID, '%f');
data5 = file5{1,1};
fclose(ID);

vibeAnal1 = zeros(length(data1)/2, 2);
vibeAnal2 = zeros(length(data1)/2, 2);
vibeAnal3 = zeros(length(data1)/2, 2);
vibeAnal4 = zeros(length(data1)/2, 2);
vibeAnal5 = zeros(length(data1)/2, 2);
for i = 1:length(vibeAnal1)
    vibeAnal1(i,1) = data1(i*2-1);
    vibeAnal1(i,2) = data1(i*2);
    
    vibeAnal2(i,1) = data2(i*2-1);
    vibeAnal2(i,2) = data2(i*2);
    
    vibeAnal3(i,1) = data3(i*2-1);
    vibeAnal3(i,2) = data3(i*2);
    
    vibeAnal4(i,1) = data4(i*2-1);
    vibeAnal4(i,2) = data4(i*2);
    
    vibeAnal5(i,1) = data5(i*2-1);
    vibeAnal5(i,2) = data5(i*2);
end


figure(1)
plot(vibeAnal1(:,1), vibeAnal1(:,2))
hold on
plot(vibeAnal2(:,1), vibeAnal2(:,2))
hold on
plot(vibeAnal3(:,1), vibeAnal3(:,2))
hold on
plot(vibeAnal4(:,1), vibeAnal4(:,2))
hold on
plot(vibeAnal5(:,1), vibeAnal5(:,2))

[Peak, PeakIdx] = findpeaks(vibeAnal1(:,2));
times = vibeAnal1(PeakIdx,1);
tot = 0;
for i = 2:length(times)
    tot = tot + (times(i) - times(i-1));
end
freq_avg1 = tot/(length(times)-1)

[Peak2, PeakIdx2] = findpeaks(vibeAnal2(:,2));
times2 = vibeAnal2(PeakIdx2,1);
tot = 0;
for i = 2:length(times2)
    tot = tot + (times2(i) - times2(i-1));
end
freq_avg2 = tot/(length(times2)-1)



