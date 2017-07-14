#pragma once

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
    MainVectorFunction() = default;
    ~MainVectorFunction() = default;

    virtual void Run() override;

private:

};
