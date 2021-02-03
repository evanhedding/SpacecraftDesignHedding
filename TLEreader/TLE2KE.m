%%TLE Reader

format long
ID = fopen('TLE.txt');
file = textscan(ID, '%s', 21);
fclose(ID);
data = file{1,1};

mu_e = 3.986*10^5;

i = str2double(data{16,1});  %degrees
RAAN = str2double(data{17,1}); %degrees
e = str2double(data{18,1})*10^-7;
w = str2double(data{19,1});  %degrees
M = str2double(data{20,1}); %degrees
n = str2double(data{21,1})*2*pi/24/3600; %Converts rev/day to rad/s

%Calculate True Anomaly from eccentricity and Mean Anomaly
E = calc_eccentric_anomaly(M*pi/180, e);
v = calc_true_anomaly(E, e);

%Calculate a from mean motion
a = (mu_e/(n^2))^(1/3);

state_vector = OE2ECI(a, e, i, RAAN, w, v);

fileID = fopen('KERV.txt','w');
fprintf(fileID,'%s\n','Orbital Elements:');
fprintf(fileID,'%s %f %s\n','i = ', i, ' (deg)');
fprintf(fileID,'%s %f %s\n','RAAN = ', RAAN, ' (deg)');
fprintf(fileID,'%s %f\n','e = ', e);
fprintf(fileID,'%s %f\n','a = ', a);
fprintf(fileID,'%s %f %s\n','Argument of Perigee (w) = ', w, ' (deg)');
fprintf(fileID,'%s %f %s\n','Mean Anomaly (M) = ', M, ' (deg)');
fprintf(fileID,'%s %f\n','Mean Motion (n) = ', n);
fprintf(fileID,'%s %f %s\n','True Anomaly (v) = ', v, ' (deg)');
fprintf(fileID,'%s\n',' ');
fprintf(fileID,'%s %f %f %f %s\n','r_vec = [', state_vector(1:3), '] (km)');
fprintf(fileID,'%s %f %f %f %s\n','v_vec = [', state_vector(4:6), '] (km/s)');

