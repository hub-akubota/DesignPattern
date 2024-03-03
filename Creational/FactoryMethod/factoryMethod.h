#ifndef FACTORY_METHOD_H
#define FACTORY_METHOD_H
#include <iostream>
#include <memory>

/*
乗り物Productのインターフェースクラス
- run() : 乗り物を走らせる
- setup() : 乗り物の設定を行う
- showInfo() : 乗り物の情報を表示する
*/
class IVehicleProduct {
public:
    void run(int interval);
    virtual void setup() = 0;
    void showInfo(int interval);
protected:
    IVehicleProduct() = default;
    virtual ~IVehicleProduct() = default;
    std::string name; // 乗り物の名前
    int speed; // 乗り物の速度[m/sec]
    int distance; // 乗り物の走行距離[m]
};

// 乗り物Productの具象クラス: 徒歩
class Walk : public IVehicleProduct {
public:
    void setup() override;
};

// 乗り物Productの具象クラス: 自転車
class Bicycle : public IVehicleProduct {
public:
    void setup() override;
};

// 乗り物Productの具象クラス: 車
class Car : public IVehicleProduct {
public:
    void setup() override;
};

/*
乗り物Creatorのインターフェースクラス
- createVehicle() : 乗り物Productを生成する
- run() : 乗り物を走らせる
*/
class IVehicleCreator {
public:
    virtual std::shared_ptr<IVehicleProduct> createVehicle() = 0;
    void run(int interval);
protected:
    IVehicleCreator() = default;
    ~IVehicleCreator() = default;
};

// 乗り物Creatorの具象クラス: 徒歩
class WalkCreator : public IVehicleCreator {
public:
    std::shared_ptr<IVehicleProduct> createVehicle() override;
};

// 乗り物Creatorの具象クラス: 自転車
class BicycleCreator : public IVehicleCreator {
public:
    std::shared_ptr<IVehicleProduct> createVehicle() override;
};

// 乗り物Creatorの具象クラス: 車
class CarCreator : public IVehicleCreator {
public:
    std::shared_ptr<IVehicleProduct> createVehicle() override;
};

#endif // FACTORY_METHOD_H