#include "barrel.hpp"


Bochka::Bochka(double volume, double degree) 
    : volumeLiters_(volume), 
      alchPercent_(volume*degree/100), 
      waterPercent_(volumeLiters_ - alchPercent_) {}

void Bochka::pour(Bochka& other) { // not a good code actually...
    double partTaken = 1 / other.volumeLiters_; // How much liquid we take (%)
    other.volumeLiters_--; // get Liter of liquid from other Bochka
    double alchBefore = other.alchPercent_; // save the alch value before taking liquid
    double waterBefore = other.waterPercent_; // same for water
    other.alchPercent_ *= (1-partTaken); // how much alch left (alchPercent_ is %; we do 100% - taken liquid %) 
    other.waterPercent_ *= (1-partTaken); // how much water left (waterPercent_ is %; we do 100% - taken liquid %)
    double alchTaken = alchBefore - other.alchPercent_; // how much alch (%) taken (% before - % after)
    double waterTaken = waterBefore - other.waterPercent_; // how much water (%) taken (% before - % after)
    waterPercent_ += waterTaken; // water (%) in current Bochka
    alchPercent_ += alchTaken; // alch (%) in current Bochka
    volumeLiters_++; // volume (L) in current Bochka
}

double Bochka::getDegree() { return alchPercent_ / volumeLiters_ * 100; }