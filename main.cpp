#include <iostream>
#include <iomanip>
#include <libusb.h>
#include "drs.h"

int main(int argc, char **argv) {
    int ret = 0;
    if((ret = libusb_init(nullptr)) < 0) {
        std::cerr << argv[0] << ": Cannot initialize libusb! Code "
                  << ret << std::endl;
        return 1;
    }
    libusb_device** dev_list = nullptr;
    auto cnt = libusb_get_device_list(nullptr, &dev_list);
    if(cnt < 0) {
        std::cerr << argv[0] << ": Cannot retrieve USB device list! Code "
                    << cnt << std::endl;
        return 1;
    }
    libusb_device_descriptor desc;
    libusb_device_handle* handle = nullptr;
    size_t num_drs_boards = 0;
    size_t num_reseted_devices = 0;
    for(ssize_t i=0; i<cnt; i++) {
        if(handle) {
            libusb_close(handle);
            handle = nullptr;
        }
        auto dev = dev_list[i];
        if((ret = libusb_get_device_descriptor(dev, &desc)) < 0) {
            std::cerr <<  ": Cannot get device descriptor for Bus "
//                       << std::setfill(" ") << std::setw(3)
//                       << libusb_get_bus_number(dev)
//                       << " Device " << std::setw(3)
//                       << libusb_get_port_number(dev)
//                       << "! Code " << ret
                      << std::endl;
            continue;
        }
        if(desc.idVendor == DRS4_EVAL_VID &&
           desc.idProduct == DRS4_EVAL_PID) {
            num_drs_boards++;
            if((ret = libusb_open(dev, &handle)) < 0) {
                std::cerr << argv[0]
                          << ": Cannot open USB Port of DRS4 EvalBoard!"
                          << " Code " << ret
                          << std::endl;
                continue;
            }
            if((ret = libusb_reset_device(handle)) < 0) {
                std::cerr << argv[0]
                          << ": Cannot reset DRS4 EvalBoard!"
                          << " Code " << ret
                          << std::endl;
                continue;
            }
            num_reseted_devices++;
        }
    }
    if(handle) {
        libusb_close(handle);
        handle = nullptr;
    }
    if (num_reseted_devices == 0) {
        std::cout << "No DRS Boards were reseted!" << std::endl;
    } else if(num_drs_boards == num_reseted_devices) {
        if(num_drs_boards == 1) {
            std::cout << "Reseted connected DRS4 Board." << std::endl;
        } else if(num_drs_boards == 2) {
            std::cout << "Reseted both connected DRS4 Boards." << std::endl;
        } else {
            std::cout << "Reseted all " << num_drs_boards
                      << " connected DRS4 Boards." << std::endl;
        }
    } else {
        std::cout << "Reseted " << num_reseted_devices
                  << " from " << num_drs_boards
                  << "connected DRS4 Boards." << std::endl;
    }
    return 0;
}
