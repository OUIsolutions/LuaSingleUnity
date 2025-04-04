
#if defined(LUA_SINGLE_UNITY_IMPLEMENT_MATH)


// Floor function - returns the largest integer less than or equal to x
double floor(double x) {
    int i = (int)x;
    
    // If x is already an integer, return it
    if (x == (double)i) return x;
    
    // For positive numbers, floor is the integer part
    // For negative numbers, we need to decrease the integer part by 1 if there's a fractional part
    return (x >= 0) ? (double)i : (double)(i - 1);
}


// Power function: x^y
double pow(double x, double y) {
    // Handle special cases
    if (y == 0.0) return 1.0;
    if (x == 0.0) return 0.0;
    if (y == 1.0) return x;
    
    // Use exp(y*ln(x)) for the general case
    return exp(y * log(x));
}

// Floating-point remainder function
double fmod(double x, double y) {
    // Handle special cases
    if (y == 0.0) return 0.0; // Undefined behavior, return 0
    
    double quotient = x / y;
    int truncated = (int)quotient;
    
    if (quotient < 0 && quotient != truncated) {
        truncated--; // Adjust for negative numbers
    }
    
    return x - truncated * y;
}

// Sine function
double sin(double x) {
    // Reduce x to interval [0, 2π)
    x = fmod(x, 2 * 3.14159265358979323846);
    
    // Use Taylor series approximation: sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ...
    double term = x;
    double sum = term;
    double x_squared = x * x;
    
    for (int i = 1; i <= 10; i++) {
        term = -term * x_squared / (2 * i * (2 * i + 1));
        sum += term;
        
        // Stop when precision is good enough
        if (term < 0.0000000001 && term > -0.0000000001) break;
    }
    
    return sum;
}

// Cosine function
double cos(double x) {
    // cos(x) = sin(x + π/2)
    return sin(x + 3.14159265358979323846 / 2);
}

// Tangent function
double tan(double x) {
    // tan(x) = sin(x) / cos(x)
    double cosine = cos(x);
    if (cosine == 0) {
        // Handle division by zero
        return (x > 0) ? 1e308 : -1e308; // Return very large value as approximation
    }
    return sin(x) / cosine;
}

// Arc sine function
double asin(double x) {
    // Domain check
    if (x < -1.0 || x > 1.0) {
        return 0.0; // Domain error
    }
    
    // Use Taylor series: asin(x) = x + (1/2)(x^3/3) + (1·3/2·4)(x^5/5) + ...
    double term = x;
    double sum = term;
    double x_squared = x * x;
    
    for (int n = 1; n <= 20; n++) {
        double coef = 1.0;
        for (int i = 1; i <= n; i++) {
            coef *= (2 * i - 1);
            coef /= (2 * i);
        }
        
        term = coef * pow(x, 2 * n + 1) / (2 * n + 1);
        sum += term;
        
        if (term < 0.0000000001 && term > -0.0000000001) break;
    }
    
    return sum;
}

// Arc cosine function
double acos(double x) {
    // acos(x) = π/2 - asin(x)
    return 3.14159265358979323846 / 2 - asin(x);
}

// Arc tangent of y/x
double atan2(double y, double x) {
    // Special cases
    if (x == 0.0) {
        if (y > 0.0) return 3.14159265358979323846 / 2;
        if (y < 0.0) return -3.14159265358979323846 / 2;
        return 0.0; // atan2(0,0) is undefined, return 0
    }
    
    double atan_value = atan(y / x);
    
    // Adjust for quadrant
    if (x < 0.0) {
        if (y >= 0.0) return atan_value + 3.14159265358979323846;
        else return atan_value - 3.14159265358979323846;
    }
    
    return atan_value;
}

// Ceiling function
double ceil(double x) {
    int i = (int)x;
    if (x == (double)i) return x;
    return (x > 0) ? i + 1.0 : (double)i;
}

// Square root function
double sqrt(double x) {
    // Error case
    if (x < 0) return 0.0; // Imaginary result
    if (x == 0.0) return 0.0;
    
    // Newton's method: x(n+1) = 0.5 * (x(n) + S/x(n))
    double guess = x;
    for (int i = 0; i < 20; i++) {
        guess = 0.5 * (guess + x / guess);
    }
    
    return guess;
}

// Natural logarithm
double log(double x) {
    // Error case
    if (x <= 0) return -1e308; // Return very large negative value
    
    // For 0 < x < 2, use Taylor series: ln(1+y) = y - y^2/2 + y^3/3 - ...
    if (x < 2) {
        double y = x - 1;
        double term = y;
        double sum = term;
        double y_power = y;
        
        for (int n = 2; n <= 100; n++) {
            y_power *= -y;
            term = y_power / n;
            sum += term;
            
            if (term < 0.0000000001 && term > -0.0000000001) break;
        }
        
        return sum;
    }
    
    // For x >= 2, use relation ln(x) = ln(x/2) + ln(2)
    int k = 0;
    while (x >= 2) {
        x /= 2;
        k++;
    }
    
    return log(x) + k * 0.6931471805599453; // ln(2) ≈ 0.693
}

// Base-2 logarithm
double log2(double x) {
    // log2(x) = log(x) / log(2)
    return log(x) / 0.6931471805599453;
}

// Base-10 logarithm
double log10(double x) {
    // log10(x) = log(x) / log(10)
    return log(x) / 2.302585092994046;
}

// Exponential function e^x
double exp(double x) {
    // Handle special cases
    if (x == 0.0) return 1.0;
    
    // Split x into integer and fractional parts for better precision
    int int_part = (int)x;
    double frac_part = x - int_part;
    
    // Calculate e^int_part
    double result = 1.0;
    double e = 2.718281828459045;
    
    for (int i = 0; i < (x < 0 ? -int_part : int_part); i++) {
        result *= (x < 0) ? 1.0/e : e;
    }
    
    // Calculate e^frac_part using Taylor series
    double term = 1.0;
    double sum = term;
    
    for (int i = 1; i <= 20; i++) {
        term *= frac_part / i;
        sum += term;
        
        if (term < 0.0000000001) break;
    }
    
    return result * sum;
}

// Arc tangent function
double atan(double x) {
    // For |x| < 1, use Taylor series
    if (x > -1.0 && x < 1.0) {
        double x_squared = x * x;
        double term = x;
        double sum = term;
        double x_power = x;
        
        for (int n = 1; n <= 50; n++) {
            x_power *= -x_squared;
            term = x_power / (2 * n + 1);
            sum += term;
            
            if (term < 0.0000000001 && term > -0.0000000001) break;
        }
        
        return sum;
    }
    
    // For |x| >= 1, use atan(x) = π/2 - atan(1/x)
    if (x >= 1.0) {
        return 3.14159265358979323846 / 2 - atan(1.0 / x);
    } else {
        return -3.14159265358979323846 / 2 - atan(1.0 / x);
    }
}

#endif
