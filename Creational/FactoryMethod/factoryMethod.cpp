#include "factoryMethod.h"
#include <thread>
#include <chrono>
#include <ctime> 

void IVehicleProduct::run(int interval = 10) {
    std::cout << "Go!" << std::endl;
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    distance = 0;
    // 10秒間走った時に進める距離を計測する
    while (true) {
        int duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();
        unsigned int d = speed * duration / 1000;
        for (int i = 0; i < d - distance; i++) {
            // 1m進むたびに"."を表示し、5m進むたびに進んだ距離を表示する
            if (d % 5 == 0) {
                std::cout << 5 * (d / 5) << std::flush;
            } else {
                std::cout << "." << std::flush;
            }
        }
        distance = d;
        if (duration > interval * 1000) {
            break;
        }
    }
    std::cout << std::endl;
}

void IVehicleProduct::showInfo(int interval) {
    std::cout << std::endl;
    std::cout << "[Information]" << std::endl;
    std::cout << "- vehicle:  " << name << std::endl;
    std::cout << "- speed:    " << speed << "[m/sec]" << std::endl;
    std::cout << "- interval: " << interval << "[sec]" << std::endl;
    std::cout << "- distance: " << distance << "[m]" << std::endl;
    std::cout << std::endl;
}

void Walk::setup() {
    name = "walk";
    speed = 1;
}

void Bicycle::setup() {
    name = "bicycle";
    speed = 5;
}

void Car::setup() {
    name = "car";
    speed = 15;
}

void IVehicleCreator::run(int interval) {
    // 乗り物を作成し、走らせ、走行後の情報を表示する
    std::shared_ptr<IVehicleProduct> vehicle = createVehicle();
    vehicle->setup();
    vehicle->run(interval);
    vehicle->showInfo(interval);
}

std::shared_ptr<IVehicleProduct> WalkCreator::createVehicle() {
    return std::make_shared<Walk>();
}

std::shared_ptr<IVehicleProduct> BicycleCreator::createVehicle() {
    return std::make_shared<Bicycle>();
}

std::shared_ptr<IVehicleProduct> CarCreator::createVehicle() {
    return std::make_shared<Car>();
}

int main(int argc, char** argv) {
    // コマンドライン引数で指定された乗り物を作成し、走らせる
    if (argc != 2 && argc != 3) {
        std::cout << "Usage: " << argv[0] << " [vehicle] <interval>" << std::endl;
        return 1;
    }
    std::shared_ptr<IVehicleCreator> creator;
    std::string vehicle = argv[1];
    if (vehicle == "walk") {
        creator = std::make_shared<WalkCreator>();
    } else if (vehicle == "bicycle") {
        creator = std::make_shared<BicycleCreator>();
    } else if (vehicle == "car") {
        creator = std::make_shared<CarCreator>();
    } else {
        std::cout << "Usage: " << argv[0] << " [vehicle]" << std::endl;
        return 1;
    }
    int interval = 10;
    if (argc == 3) {
        interval = std::stoi(argv[2]);
    }
    creator->run(interval);
    return 0;
}
