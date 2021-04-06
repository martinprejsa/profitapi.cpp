//
// MIT License
//
// Copyright (c) 2021 WattMann
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#include <profitapi/profitapi.hpp>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <fmt/format.h>

size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    size_t realsize = size * nmemb;
    data->append((char*) ptr, realsize);
    return realsize;
}

profitapi::KeyDataResponse profitapi::generateKey(const profitapi::Credentials &credentials, const profitapi::KeyData &data) {
    auto handle = curl_easy_init();
    KeyDataResponse response {};

    if(handle) {
        std::string url = fmt::format("https://{host}/{version}/{context}",
                                      fmt::arg("host", credentials.host),
                                      fmt::arg("version", credentials.version),
                                      fmt::arg("context", "company/security/apikeys"));
        std::string response_str;

        curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response_str);
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, writeFunction);

        curl_slist *headers {};

        headers = curl_slist_append(headers, fmt::format("Authorization: basic {}", credentials.key).c_str());
        headers = curl_slist_append(headers, fmt::format("ClientID: {}", credentials.clientID).c_str());
        headers = curl_slist_append(headers, fmt::format("ClientSecret: {}", credentials.clientSecret).c_str());
        headers = curl_slist_append(headers, fmt::format("CompanyID: {}", credentials.companyID).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, true);
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, false);

        auto json = nlohmann::json::object();
        json["userName"] = data.userName;
        json["ipAllowed"] = data.ipWhitelist;
        json["ipDenied"] = data.ipBlacklist;
        auto json_str = json.dump(4);

        curl_easy_setopt(handle, CURLOPT_POSTFIELDS, json_str.c_str());

        auto code = curl_easy_perform(handle);
        if(code != CURLE_OK) {
            response.state = State::CURL_ERROR;
            response.stateDesc = "Failed to perform the request";
        } else {
            try {
                nlohmann::json response_json = nlohmann::json::parse(response_str);
                response.state = State::OK;
                response.stateDesc = "OK";
                response.key = response_json["key"].get<std::string>();
                response.ID = response_json["id"].get<std::string>();
                response.userName = data.userName;
                // response.userName = response_json["userName"].get<std::string>(); Mysteriously disappeared
                response.ipWhitelist = response_json["ipAllowed"].get<std::vector<std::string>>();
                response.ipBlacklist = response_json["ipDenied"].get<std::vector<std::string>>();
            } catch (...) {
                response.state = State::BAD_REQUEST;
                response.stateDesc = response_str;
            }

        }

        curl_easy_cleanup(handle);
        curl_slist_free_all(headers);
    } else {
        response.state = State::CURL_ERROR;
        response.stateDesc = "Failed to init CURL handle";
    }

    return response;
}