#include <math.h>

#define WindowSize 128
int N = WindowSize;
float pi = 3.14159265358979323846;

long double adc_out_1[WindowSize];
long double adc_out_2[WindowSize];
long double adc_out_3[WindowSize];

float Xi_1, Xr_1, Phasor_Magnitude_1, Phasor_Angle_1;
float Xi_2, Xr_2, Phasor_Magnitude_2, Phasor_Angle_2;
float Xi_3, Xr_3, Phasor_Magnitude_3, Phasor_Angle_3;

const int analogPin_1 = A0;  // Analog pin for Phase A
const int analogPin_2 = A1;  // Analog pin for Phase B
const int analogPin_3 = A2;  // Analog pin for Phase C

void setup() {
  Serial.begin(115200);
  // Set analog reference to DEFAULT (5V)
  analogReference(DEFAULT);
}

void loop() {
  calc_phasor();
  plot_phasors();

  delay(1000); // Delay for 1 second before the next iteration
}

void calc_phasor() {
  for (int i = 0; i < N; i++) {
    adc_out_1[i] = analogRead(analogPin_1); // Phase A
    adc_out_2[i] = analogRead(analogPin_2) ;// Phase B
    adc_out_3[i] = analogRead(analogPin_3) ;// Phase C
  }

  Xr_1 = Xi_1 = Xr_2 = Xi_2 = Xr_3 = Xi_3 = 0;

  for (int n = 0; n < N; n++) {
    Xr_1 += adc_out_1[n] * cos((2 * pi * n) / N);
    Xi_1 += adc_out_1[n] * sin((2 * pi * n) / N);

    Xr_2 += adc_out_2[n] * cos((2 * pi * n) / N);
    Xi_2 += adc_out_2[n] * sin((2 * pi * n) / N);

    Xr_3 += adc_out_3[n] * cos((2 * pi * n) / N);
    Xi_3 += adc_out_3[n] * sin((2 * pi * n) / N);
  }

  Phasor_Magnitude_1 = sqrt(Xr_1 * Xr_1 + Xi_1 * Xi_1);
  Phasor_Magnitude_2 = sqrt(Xr_2 * Xr_2 + Xi_2 * Xi_2);
  Phasor_Magnitude_3 = sqrt(Xr_3 * Xr_3 + Xi_3 * Xi_3);

  Phasor_Angle_1 = atan2(Xi_1, Xr_1) * (180.0 / pi);
  Phasor_Angle_2 = atan2(Xi_2, Xr_2) * (180.0 / pi);
  Phasor_Angle_3 = atan2(Xi_3, Xr_3) * (180.0 / pi);
}

void plot_phasors() {
  for (int i = 0; i < N; i++) {
    double sample_1 = Phasor_Magnitude_1 * sin((2 * pi * i) / N + Phasor_Angle_1 * (pi / 180.0));
    double sample_2 = Phasor_Magnitude_2 * sin((2 * pi * i) / N + Phasor_Angle_2 * (pi / 180.0));
    double sample_3 = Phasor_Magnitude_3 * sin((2 * pi * i) / N + Phasor_Angle_3 * (pi / 180.0));

    Serial.print(Phasor_Angle_1);
    Serial.print(",");
    Serial.print( Phasor_Angle_2);
    Serial.print(",");
    Serial.println(Phasor_Angle_3);
  }
}
