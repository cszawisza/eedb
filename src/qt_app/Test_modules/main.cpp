#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QApplication>

using namespace testing;

class TestCoreApp : public QApplication
{
public:
    TestCoreApp(int& argc, char** argv);
    void InitGMockAndGTest(int& argc, char** argv) const;
};

void TestCoreApp::InitGMockAndGTest(int& argc, char** argv) const
{
    InitGoogleMock(&argc, argv);
    InitGoogleTest(&argc, argv);
}

TestCoreApp::TestCoreApp(int& argc, char** argv)
    : QApplication(argc, argv)
{
    InitGMockAndGTest(argc, argv);
}

int main(int argc, char **argv)
{
    printf("Running main() from gtest_main.cc\n");
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    TestCoreApp app(argc, argv);
    return RUN_ALL_TESTS();
    //app.exec();
}
