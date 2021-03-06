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

#ifndef PERMISSION_CALLBACK_H
#define PERMISSION_CALLBACK_H

#include "nocopyable.h"
#include "on_permission_changed_callback_host.h"

namespace OHOS {
namespace Security {
namespace Permission {

/**
 * Fetcher which used to get application information and then post-process.
 *
 */
class PermissionCallback : public OHOS::AppExecFwk::OnPermissionChangedCallbackHost {
public:
    PermissionCallback() = default;
    virtual ~PermissionCallback() = default;
    virtual void OnChanged(const int32_t uid) override;

private:
};

}  // namespace Permission
}  // namespace Security
}  // namespace OHOS
#endif