//���� ��� �������� �������� ������� ������ Settings � ��� ������ getInstance
#include "pch.h"
#include "../Design_patterns/settings.h"
TEST(SettingsTest, getInstance) {
    Settings* settings = Settings::getInstance();
    EXPECT_NE(settings, nullptr);
}