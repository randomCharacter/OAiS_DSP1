for i = 1:4
    fprintf("%d Hz\n", f(i));
    A(1) = round(1 * c);
    A(2) = round(-cos(2*PI*f(i)/fs) * c);
    A(3) = round(1 * c);
    A(4) = round(1 * c);
    A(5) = round(-r(i)*cos(2*PI*f(i)/fs) * c);
    A(6) = round(r(i)*r(i) * c);
    fprintf("\t%d, \n", A');
end
