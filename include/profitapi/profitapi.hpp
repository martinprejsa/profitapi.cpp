#pragma once

#include <string>
#include <vector>
#include <ctime>

namespace profitapi {

    enum class State {
        OK, CURL_ERROR, BAD_REQUEST
    };

    struct Response {
        State state;
        std::string stateDesc;
    };

    struct KeyData {
        std::string userName;
        std::vector<std::string> ipWhitelist;
        std::vector<std::string> ipBlacklist;
    };

    struct KeyDataResponse : public Response, public KeyData {
        std::string key;
        std::string ID;
    };

    struct Credentials {
        std::string key;
        std::string clientID;
        std::string clientSecret;
        std::string companyID;
        std::string api_version = "1.6";
        std::string profitapi_host = "api.profit365.eu";
    };

    struct InvoiceRowData {
        uint64_t quantity;
        float price;
        float priceBrutto;
        std::string itemID;
        std::string code;
        std::string name;
        std::string vatParagraphID;
    };

    struct InvoiceData {
        std::string ordnerID;
        std::string warehouseID;
        std::time_t dateCreated;
        std::vector<InvoiceRowData> rows;
        std::string recordNumber;
        std::vector<std::string> tags;
        std::string partnerID;
        std::string partnerDetail;
        std::string partnerAddress;
        std::string deliveryTypeId;
        std::string paymentTypeId;
        std::string bankAccountId;
        std::string symbolVariable;
        std::string symbolConstant;
        std::string symbolSpecific;
        std::time_t dateAccounting;
        std::time_t dateDelivery;
        std::string periodId;
        std::time_t dateValidTo;
        std::string commentAboveItems;
        std::string commentBelowItems;
        std::string vatParagraphID;
        uint64_t bonusPercent;
        std::string orderRecordNo;
        std::string warehouseRecordNo;
        std::string costCenterId;
        std::string costUnitId;
        std::string personId;
        std::string projectId;
    };

    KeyDataResponse generateKey(const Credentials &credentials, const KeyData &data);
    InvoiceData createInvoice(const Credentials &credentials, InvoiceData &data);
}