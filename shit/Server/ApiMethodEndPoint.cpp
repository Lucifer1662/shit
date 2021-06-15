#include "ApiMethodEndPoint.h"
#include "stdfx.h"


void NotFound(http_request msg) {
    msg.reply(web::http::status_codes::NotFound);
}

ApiMethodEndPoint::ApiMethodEndPoint(ApiHandle&& notFoundHandle) : notFoundHandle(notFoundHandle)
{

}

ApiMethodEndPoint& ApiMethodEndPoint::addHandle(Path path, ApiHandle&& handle)
{
    ucout << "inserting " << path << std::endl;
    paths.insert_or_assign(path, std::move(handle));
    return *this;
}

void ApiMethodEndPoint::invoke(http_request request)
{
    auto path = request.absolute_uri().path();

    ucout << path << std::endl;
    std::cout << paths.size() << std::endl;

    auto it = paths.find(path);

    if (it != paths.end()) {
        it->second(request);
    }
    else {
        notFoundHandle(request);
    }
}

void ApiMethodEndPoint::setNotFoundHandle(ApiHandle&& handle)
{
    notFoundHandle = std::move(handle);
}
