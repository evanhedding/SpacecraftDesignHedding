function v = calc_true_anomaly(E, e)
    v = 2*atan(sqrt((1+e)/(1-e))*tan(E/2));
end