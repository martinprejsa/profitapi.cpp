#include <profitapi/profitapi.hpp>
#include <fmt/format.h>
#include <boost/beast.hpp>
#include <boost/asio.hpp>


namespace we
profitapi::KeyDataResponse
profitapi::generateKey(const profitapi::Credentials &credentials, const profitapi::KeyData &data) {
    std::string url = fmt::format(
            "https://{0}/{1}/{2}",
            credentials.profitapi_host,
            credentials.api_version,
            "company/security/apikeys"
            );

    boost::asio::io_context context;
    boost:asio::net::ip::tcp::resolver resolver;

    const
}