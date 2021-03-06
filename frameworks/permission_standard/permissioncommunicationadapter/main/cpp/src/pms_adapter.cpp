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

#include "pms_adapter.h"

#include "permission_log.h"
#include "ipc_skeleton.h"

#include "if_system_ability_manager.h"
#include "iservice_registry.h"

namespace OHOS {
namespace Security {
namespace Permission {
namespace {
static constexpr OHOS::HiviewDFX::HiLogLabel LABEL = {LOG_CORE, SECURITY_DOMAIN_PERMISSION, "PmsAdapter"};
}
sptr<Permission::IPermissionManager> PmsAdapter::GetPermissionManager()
{
    if (iPermissionManager_ == nullptr) {
        auto permissionObj = GetSystemAbility(Constant::SUBSYS_SECURITY_PERMISSION_SYS_SERVICE_ID);
        if (permissionObj == nullptr) {
            PERMISSION_LOG_ERROR(LABEL, "failed to get permission manager service.");
            return nullptr;
        }
        iPermissionManager_ = iface_cast<Permission::IPermissionManager>(permissionObj);
    }

    return iPermissionManager_;
}

sptr<IRemoteObject> PmsAdapter::GetSystemAbility(const Constant::ServiceId systemAbilityId)
{
    if (saMgr_ == nullptr) {
        std::lock_guard<std::mutex> lock(saMutex_);
        if (saMgr_ == nullptr) {
            saMgr_ = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
            if (saMgr_ == nullptr) {
                PERMISSION_LOG_ERROR(LABEL, "fail to get Registry.");
                return nullptr;
            }
        }
    }
    return saMgr_->GetSystemAbility(systemAbilityId);
}
}  // namespace Permission
}  // namespace Security
}  // namespace OHOS
