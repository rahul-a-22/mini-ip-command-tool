#include <gtest/gtest.h>
#include "IPManager.h"

class IPManagerTest : public ::testing::Test {
protected:
    IPManager* ipManager;

    void SetUp() override {
        ipManager = new IPManager();
    }

    void TearDown() override {
        delete ipManager;
    }
};

TEST_F(IPManagerTest, TestViewCurrentConfiguration) {
    // Assuming the method returns a string representation of the current configuration
    std::string config = ipManager->viewCurrentConfiguration();
    EXPECT_FALSE(config.empty());
}

TEST_F(IPManagerTest, TestSetStaticIP) {
    std::string ip = "192.168.1.100";
    std::string subnetMask = "255.255.255.0";
    std::string gateway = "192.168.1.1";
    
    EXPECT_TRUE(ipManager->setStaticIP(ip, subnetMask, gateway));
}

TEST_F(IPManagerTest, TestEnableDHCP) {
    EXPECT_TRUE(ipManager->enableDHCP());
}

TEST_F(IPManagerTest, TestChangeDNSServers) {
    std::vector<std::string> dnsServers = {"8.8.8.8", "8.8.4.4"};
    EXPECT_TRUE(ipManager->changeDNSServers(dnsServers));
}

TEST_F(IPManagerTest, TestResetFlushDNS) {
    EXPECT_TRUE(ipManager->resetFlushDNS());
}