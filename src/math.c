double pow(double x, double y) {
    double result = 1.0;
    for (int i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

double floor(double x) {
    int result = (int)x;
    if (x < 0 && x != result) {
        result--;
    }
    return result;
}

double fmod(double x, double y) {
    return x - y * floor(x / y);
}

double sin(double x) {
    // Taylor series approximation
    double result = x;
    double term = x;
    for (int i = 1; i <= 10; i++) {
        term *= -x * x / ((2 * i) * (2 * i + 1));
        result += term;
    }
    return result;
}

double cos(double x) {
    // Taylor series approximation
    double result = 1.0;
    double term = 1.0;
    for (int i = 1; i <= 10; i++) {
        term *= -x * x / ((2 * i - 1) * (2 * i));
        result += term;
    }
    return result;
}

double tan(double x) {
    return sin(x) / cos(x);
}

double asin(double x) {
    // Taylor series approximation
    double result = x;
    double term = x;
    for (int i = 1; i <= 10; i++) {
        term *= (2 * i - 1) * (2 * i - 1) * x * x / (2 * i * (2 * i + 1));
        result += term;
    }
    return result;
}

double acos(double x) {
    return M_PI / 2 - asin(x);
}

double atan2(double y, double x) {
    if (x > 0) {
        return atan(y / x);
    } else if (x < 0 && y >= 0) {
        return atan(y / x) + M_PI;
    } else if (x < 0 && y < 0) {
        return atan(y / x) - M_PI;
    } else if (x == 0 && y > 0) {
        return M_PI / 2;
    } else if (x == 0 && y < 0) {
        return -M_PI / 2;
    } else {
        return 0;
    }
}

double ceil(double x) {
    int result = (int)x;
    if (x > result) {
        result++;
    }
    return result;
}

double sqrt(double x) {
    double result = x;
    for (int i = 0; i < 10; i++) {
        result = 0.5 * (result + x / result);
    }
    return result;
}

double log(double x) {
    // Taylor series approximation
    double result = 0.0;
    double term = (x - 1) / x;
    for (int i = 1; i <= 10; i++) {
        result += term / i;
        term *= (x - 1) / x;
    }
    return result;
}

double log2(double x) {
    return log(x) / log(2);
}

double log10(double x) {
    return log(x) / log(10);
}

double exp(double x) {
    // Taylor series approximation
    double result = 1.0;
    double term = 1.0;
    for (int i = 1; i <= 10; i++) {
        term *= x / i;
        result += term;
    }
    return result;
}

double atan(double x) {
    // Taylor series approximation
    double result = x;
    double term = x;
    for (int i = 1; i <= 10; i++) {
        term *= -x * x * (2 * i - 1) / (2 * i + 1);
        result += term;
    }
    return result;
}