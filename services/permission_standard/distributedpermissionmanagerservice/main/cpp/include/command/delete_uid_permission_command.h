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

#ifndef DELETE_UID_PERMISSION_COMMAND_H
#define DELETE_UID_PERMISSION_COMMAND_H

namespace OHOS {
namespace Security {
namespace Permission {
/**
 * Command which used to delete uid permission on other device.
 */
class DeleteUidPermissionCommand : public BaseRemoteCommand {
public:
    void Prepare() override;

    void Execute() override;

    void Finish() override;

    std::string ToJsonPayload() override;

    DeleteUidPermissionCommand(const std::string &json);
    DeleteUidPermissionCommand(const int32_t uid, const std::string &srcDeviceId, const std::string &dstDeviceId);
    virtual ~DeleteUidPermissionCommand() = default;

private:
    /**
     * The command name. Should be equal to class name.
     */
    const std::string COMMAND_NAME = "DeleteUidPermissionCommand";
    int32_t uid_ = 0;
};
}  // namespace Permission
}  // namespace Security
}  // namespace OHOS
#endif