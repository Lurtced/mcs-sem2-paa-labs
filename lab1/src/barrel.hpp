#pragma once


class Bochka {
private:
    // TODO☑: подобрать имя, чтобы было понятно - это объем, отношение, процентаж?
    double volumeLiters_;
    double waterPercent_;
    double alchPercent_;

public:
    Bochka(double volume, double degree);
    void pour(Bochka& other);
    double getDegree();
};