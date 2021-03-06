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

#include "query_permission_used_request.h"

namespace OHOS {
namespace Security {
namespace Permission {
using namespace std;
bool QueryPermissionUsedRequest::Marshalling(Parcel &out) const
{
    if (!out.WriteString(this->deviceLabel)) {
        return false;
    }
    if (!out.WriteString(this->bundleName)) {
        return false;
    }
    if (!out.WriteStringVector(this->permissionNames)) {
        return false;
    }
    if (!out.WriteInt64(this->beginTimeMillis)) {
        return false;
    }
    if (!out.WriteInt64(this->endTimeMillis)) {
        return false;
    }
    if (!out.WriteInt32(this->flag)) {
        return false;
    }
    return true;
}

QueryPermissionUsedRequest *QueryPermissionUsedRequest::Unmarshalling(Parcel &in)
{
    auto *request = new (nothrow) QueryPermissionUsedRequest();
    if (request == nullptr) {
        delete request;
        request = nullptr;
        return request;
    }
    request->deviceLabel = in.ReadString();
    request->bundleName = in.ReadString();
    if (!in.ReadStringVector(&request->permissionNames)) {
        delete request;
        request = nullptr;
        return request;
    }
    if (!in.ReadInt64(request->beginTimeMillis)) {
        delete request;
        request = nullptr;
        return request;
    }
    if (!in.ReadInt64(request->endTimeMillis)) {
        delete request;
        request = nullptr;
        return request;
    }
    if (!in.ReadInt32(request->flag)) {
        delete request;
        request = nullptr;
        return request;
    }
    return request;
}

nlohmann::json QueryPermissionUsedRequest::to_json(const QueryPermissionUsedRequest &request) const
{
    nlohmann::json jsonObj = nlohmann::json{{"dl", request.deviceLabel},
        {"bn", request.bundleName},
        {"pn", request.permissionNames},
        {"bt", request.beginTimeMillis},
        {"et", request.endTimeMillis},
        {"f", request.flag}};
    return jsonObj;
}

void QueryPermissionUsedRequest::from_json(const nlohmann::json &jsonObj, QueryPermissionUsedRequest &request)
{
    jsonObj.at("dl").get_to(request.deviceLabel);
    jsonObj.at("bn").get_to(request.bundleName);
    jsonObj.at("pn").get_to<std::vector<std::string>>(request.permissionNames);
    jsonObj.at("bt").get_to(request.beginTimeMillis);
    jsonObj.at("et").get_to(request.endTimeMillis);
    jsonObj.at("f").get_to(request.flag);
}

int QueryPermissionUsedRequest::TranslationIntoGenericValues(const QueryPermissionUsedRequest &inQueryRequest,
    GenericValues &outVisitorValues, GenericValues &outRecordAndValues, GenericValues &outRecordOrValues)
{
    if (!inQueryRequest.deviceLabel.empty()) {
        outVisitorValues.Put(FIELD_DEVICE_NAME, inQueryRequest.deviceLabel);
    }
    if (!inQueryRequest.bundleName.empty()) {
        outVisitorValues.Put(FIELD_BUNDLE_NAME, inQueryRequest.bundleName);
    }
    std::string permissionNames;
    for (unsigned int i = 0; i < inQueryRequest.permissionNames.size(); i++) {
        int32_t code = 0;
        std::string perName = inQueryRequest.permissionNames[i];
        if (Constant::PermissionNameToOrFromOpCode(perName, code)) {
            outRecordOrValues.Put(FIELD_OP_CODE + ToString(i), code);
        }
    }
    int64_t begin = inQueryRequest.beginTimeMillis;
    int64_t end = inQueryRequest.endTimeMillis;
    if (begin < 0 || end < 0 || (begin > end && end > 0)) {
        return Constant::FAILURE;
    }
    if (begin != 0) {
        outRecordAndValues.Put(FIELD_TIMESTAMP_BEGIN, begin);
    }
    if (end != 0) {
        outRecordAndValues.Put(FIELD_TIMESTAMP_END, end);
    }
    return Constant::SUCCESS;
}
}  // namespace Permission
}  // namespace Security
}  // namespace OHOS