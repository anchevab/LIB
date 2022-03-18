#ifndef SHARPDIST_H
#define SHARPDIST_H

// SharpDist is an IR distance sensor.
class SharpDist {
public:
    // Create a SharpDist with the given analog input pin.
    SharpDist(int pin);

    // Create a SharpDist with the given analog input pin which averages a given number of samples.
    SharpDist(int pin, int samples);

    // setSamples sets the number of samples to average (default: 1).
    void setSamples(int samples);

    // distanceInch gets the distance in inches.
    float distanceInches();

    // distanceCentimeter gets the distance in centimeters.
    float distanceCentimeters();

private:
    float dist();
    int pin;
    int samples;
};

#endif
