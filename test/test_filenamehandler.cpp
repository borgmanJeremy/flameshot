#include "../src/utils/filenamehandler.h"
#include <QDebug>
#include <QStandardPaths>
#include <catch2/catch.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

TEST_CASE("Clean data specifiers", "[specifier]")
{
    REQUIRE(cleanDateSpecifier("") == "%F_%H-%M");
    REQUIRE(cleanDateSpecifier("%F_%H-%M%") == "%F_%H-%M");
    REQUIRE(cleanDateSpecifier("%F_%H-%M%%%%") == "%F_%H-%M");
    REQUIRE(cleanDateSpecifier("%F_%H-%M") == "%F_%H-%M");
}

TEST_CASE("Parse filename", "[filename]")
{
    auto parsedString = FileNameHandler().parseFilename("%F_%H:%M");
    // Test that colons are removed
    // any more complicated tests will need to mock the clock function
    REQUIRE(parsedString.contains(":") == false);

    // This formats to just include the century so it will pass for the next
    // 80 years (2100)
    parsedString = FileNameHandler().parseFilename("%C");
    REQUIRE(parsedString == "20");
}

TEST_CASE("Fix Path", "[path]")
{
    auto path = fs::temp_directory_path();
    fs::current_path(path);
    fs::create_directories("flameshot_test");

    path += "/flameshot_test";

    auto fixed =
      FileNameHandler().fixPath(QString::fromStdString(path.string()), "test");
    REQUIRE(fixed == QString::fromStdString(path.string() + "/test"));

    fixed = FileNameHandler().fixPath(
      QString::fromStdString(path.string() + '/'), "test");
    REQUIRE(fixed == QString::fromStdString(path.string() + "/test"));

    std::ofstream output_1(path.string() + "/test.png");
    output_1 << " ";
    fixed =
      FileNameHandler().fixPath(QString::fromStdString(path.string()), "test");
    REQUIRE(fixed == QString::fromStdString(path.string() + "/test_1"));

    std::ofstream output_2(path.string() + "/test_1.png");
    output_2 << " ";
    fixed =
      FileNameHandler().fixPath(QString::fromStdString(path.string()), "test");
    REQUIRE(fixed == QString::fromStdString(path.string() + "/test_2"));

    fs::remove(path.string() + "/test.png");
    fs::remove(path.string() + "/test_1.png");
    fs::remove(path.string());
}

TEST_CASE("Generate Path", "[path]")
{
    auto path = FileNameHandler().generateAbsolutePath("/test", "%C");

    REQUIRE(path == "/test/20");
}

TEST_CASE("Absolute Path", "[path]")
{
    auto path = FileNameHandler().absoluteSavePath("/dev/null", "test.png");
    QString standard_path =
      QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) +
      "/test.png";
    REQUIRE(path == standard_path);

    auto tmp_path = fs::temp_directory_path();
    path = FileNameHandler().absoluteSavePath(
      QString::fromStdString(tmp_path.string()), "test.png");
    REQUIRE(path == QString::fromStdString(tmp_path.string() + "/test.png"));
}