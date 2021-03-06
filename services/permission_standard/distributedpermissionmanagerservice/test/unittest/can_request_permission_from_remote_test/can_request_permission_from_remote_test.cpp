/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "can_request_permission_from_remote_test.h"
using namespace testing::ext;
namespace OHOS {
pid_t IPCSkeleton::pid_ = 1;
pid_t IPCSkeleton::uid_ = 1;
std::string IPCSkeleton::localDeviceId_ = "1004";
std::string IPCSkeleton::deviceId_ = "";
namespace Security {
namespace Permission {
namespace {}  // namespace

void CanRequestPermissionFromRemoteTest::SetUpTestCase(void)
{
    OHOS::sptr<OHOS::IRemoteObject> bundleObject = new OHOS::AppExecFwk::BundleMgrService();
    OHOS::sptr<OHOS::IRemoteObject> permissionObject = new PermissionManagerService();
    auto sysMgr = OHOS::SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (sysMgr == NULL) {
        GTEST_LOG_(ERROR) << "fail to get ISystemAbilityManager";
        return;
    }
    sysMgr->AddSystemAbility(Constant::ServiceId::BUNDLE_MGR_SERVICE_SYS_ABILITY_ID, bundleObject);
    sysMgr->AddSystemAbility(Constant::ServiceId::SUBSYS_SECURITY_PERMISSION_SYS_SERVICE_ID, permissionObject);
}
void CanRequestPermissionFromRemoteTest::TearDownTestCase(void)
{}
void CanRequestPermissionFromRemoteTest::SetUp()
{}
void CanRequestPermissionFromRemoteTest::TearDown()
{}

/*
 * Feature: DPMS
 * Function: CanRequestPermissionFromRemoteTest
 * SubFunction: Construct
 * FunctionPoints: construct
 * EnvConditions: NA
 * CaseDescription: verify constructor and destructor
 */
HWTEST_F(CanRequestPermissionFromRemoteTest, can_request_permission_from_remote_test_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "can_request_permission_from_remote_test_001";
    std::shared_ptr<DistributedPermissionManagerService> service =
        std::make_shared<DistributedPermissionManagerService>();
    std::string permission("");
    std::string nodeId("networkId");
    std::string deviceId("deviceId");
    // case deviceId =""
    EXPECT_TRUE(!service->CanRequestPermissionFromRemote(permission, nodeId));
    // case permission =""
    DeviceInfoRepository::GetInstance().SaveDeviceInfo(
        nodeId, "universallyUniqueId", deviceId, "deviceName", "deviceType");
    EXPECT_TRUE(!service->CanRequestPermissionFromRemote(permission, nodeId));
    // case permission is not SensitiveResource
    permission = "notSensitiveResource";
    EXPECT_TRUE(!service->CanRequestPermissionFromRemote(permission, nodeId));
    permission = Constant::LOCATION;
    EXPECT_TRUE(service->CanRequestPermissionFromRemote(permission, nodeId));
}
}  // namespace Permission
}  // namespace Security
}  // namespace OHOS