function E = calc_eccentric_anomaly(M, e)
    dE = 1.0;
    E = pi;
    tol = 10^-10;
    while abs(dE) > tol
        dE = -(E-e*sin(E)-M)/(1-e*cos(E));
        E = E + dE;
    end
end