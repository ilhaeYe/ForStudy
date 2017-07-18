#pragma once
#include <queue>

class MainFunction
{
public:
    MainFunction() = default;
    ~MainFunction() = default;

    virtual void Run() = 0;

private:

};

class MainArrayFunction : public MainFunction
{
public :
    MainArrayFunction() = default;
    ~MainArrayFunction() = default;

    virtual void Run() override;

private:

};

class MainVectorFunction : public MainFunction
{
public:
    class Integer
    {
    private:
        int x;

    public:
        Integer() = delete;

        static Integer Create(int x)
        {
            return Integer(x);
        }

    private:
        Integer(int x) : x(x) {}

    };

public:
    MainVectorFunction() = default;
    ~MainVectorFunction() = default;

    virtual void Run() override;

private:

};

class MainUnionFunction : public MainFunction
{
public:
    enum WeatherType { Temperature, Wind };
    struct TemperatureData
    {
        int _stationId;
        double _time;
        double _current;
        double _max;
        double _min;
    };
    struct WindData
    {
        int _stationId;
        double _time;
        double _speed;
        double _direction;
    };
    struct Input
    {
        WeatherType type;
        union
        {
            TemperatureData temperData;
            WindData windData;
        };
    };

public:
    MainUnionFunction() = default;
    ~MainUnionFunction() = default;

    virtual void Run() override;

    void processTemperature(TemperatureData temperData) {};
    void processWind(WindData windData) {};
    void Initialize();

private:
    std::queue<Input> _inputs;
};
