#include <catch2/catch.hpp>
#include "device-handling.h"

#include <iostream>

SCENARIO("We should be able to create and control cameras connected by USB", "[camera]") {
    /*
    GIVEN("Multiple plugged devices") {
        WHEN("I ask for the connected cameras") {
            const auto list = USBCam::GetDevicesList();

            THEN("I should get a list of names and port numbers") {
                REQUIRE(list.size() > 0);
                REQUIRE(list.at(0).name != "");
            }
        }
    }
    */

    GIVEN("A plugged camera") {
        auto camera0 = USBCam::CreateCamera(0);

        WHEN("I change its capture format") {
            auto resolutions = camera0->GetSupportedFormats();

            THEN("I should get what is possible") {
                REQUIRE(resolutions.size() > 0);
                REQUIRE(resolutions.at(0).frameRate > 0);
                REQUIRE(resolutions.at(0).height > 0);
            }

            THEN("The size of the saved images should be changed") {
                REQUIRE_NOTHROW(camera0->SetFormat(resolutions.at(0)));
                auto frame0 = camera0->GetLastFrame();
                REQUIRE_NOTHROW(camera0->SetFormat(resolutions.at(1)));
                auto frame1 = camera0->GetLastFrame();

                REQUIRE(frame0.byteWidth != frame1.byteWidth);
            }
        }

        WHEN("I change its settings") {
            auto settings = camera0->GetSupportedSettings();
            
            REQUIRE(camera0->SetSetting(USBCam::ICamera::CameraSetting::AUTO_EXPOSURE, 0));
            REQUIRE(camera0->SetSetting(USBCam::ICamera::CameraSetting::EXPOSURE, 100));

            THEN("The settings should be changed") {
                REQUIRE(camera0->GetSetting(USBCam::ICamera::CameraSetting::EXPOSURE) == 100);
            }
        }
        /*

        WHEN("I take 2 pictures with different settings") {
            REQUIRE(camera0->SetSetting(USBCam::ICamera::CameraSetting::AUTO_EXPOSURE, 0));
            REQUIRE(camera0->SetSetting(USBCam::ICamera::CameraSetting::EXPOSURE, 10000));
            REQUIRE_NOTHROW(camera0->SaveLastFrame());
            REQUIRE(camera0->SetSetting(USBCam::ICamera::CameraSetting::EXPOSURE, 1000));
            REQUIRE_NOTHROW(camera0->SaveLastFrame());

            THEN("The two pictures should be different") {
                REQUIRE(true); // Manual check needed
            }
        }
        */
    }

   /*
    GIVEN("3 cameras") {
        auto camera1 = USBCam::CreateCamera(1);
        auto camera2 = USBCam::CreateCamera(2);
        auto camera3 = USBCam::CreateCamera(3);

        WHEN("I take a lot of pictures in 4k") {
            auto resolutions = camera1->GetSupportedFormats();
            camera1->SetFormat(resolutions.at(12));
            camera2->SetFormat(resolutions.at(12));
            camera3->SetFormat(resolutions.at(12));

            THEN("It should work") {
                for (size_t i = 0; i < 30; i++) {
                    REQUIRE_NOTHROW(camera1->SaveLastFrame());
                    REQUIRE_NOTHROW(camera2->SaveLastFrame());
                    REQUIRE_NOTHROW(camera3->SaveLastFrame());
                }
            }
        }
    }
    */
}
