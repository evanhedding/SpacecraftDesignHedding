function STATE = OE2ECI(a, e, i, RAAN, w, v)
    i = i*pi/180; %radians
    RAAN = RAAN*pi/180; %radians
    w = w*pi/180; %radians
    v = v*pi/180; %radians
    
    mu_e = 3.986*10^5; %earthz
    r_mag = a*(1-e^2)/(1+e*cos(v));
    p = r_mag*(1 + e*cos(v));
    vel_vec_perifocal = (sqrt(mu_e/p)).*[-sin(v); (e+cos(v)); 0];
    r_vec_perifocal = [r_mag*cos(v); r_mag*sin(v); 0];
    
    if e == 0 && i ~= 0 %Circular but inclined
        R = rotz(RAAN)*rotx(i);
    elseif e > 0 && i == 0 %Elliptical equatorial
        R = rotz(w); %w here must be input as the argument of longitude
    elseif e == 0 && i == 0 %Circular equatorial
        R = [1 0 0;0 1 0;0 0 1];
    else
        R = rotz(RAAN)*rotx(i)*rotz(w);
    end
    r_eci = R*r_vec_perifocal;
    vel_eci = R*vel_vec_perifocal;
    STATE = [r_eci; vel_eci];
end

function R = rotx(theta) %passive rot
    R = [1  0            0;
         0  cos(-theta)  sin(-theta);
         0  -sin(-theta) cos(-theta)];
end

function R = rotz(theta) %passive rot
    R = [cos(-theta) sin(-theta) 0; 
        -sin(-theta) cos(-theta) 0;
           0          0          1]; 
end