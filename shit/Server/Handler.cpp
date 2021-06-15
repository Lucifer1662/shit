#pragma once
#include "handler.h"
#include "CORS.h"

handler::handler()
{
    //ctor
}

handler::handler(utility::string_t url) :m_listener(url)
{
    
    optionsHandler.setNotFoundHandle([](http_request request) {
        http_response res;
        std::cout << "NOT Found OPTIONS" << std::endl;
        addCors(res);
        res.set_status_code(http::status_codes::OK);

        request.reply(res);
    });
   
    m_listener.support(methods::GET,  std::bind(&ApiMethodEndPoint::invoke, &getHandler, std::placeholders::_1));
    m_listener.support(methods::PUT,  std::bind(&ApiMethodEndPoint::invoke, &putHandler, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&ApiMethodEndPoint::invoke, &postHandler, std::placeholders::_1));
    m_listener.support(methods::DEL,  std::bind(&ApiMethodEndPoint::invoke, &deleteHandler, std::placeholders::_1));
    m_listener.support(methods::OPTIONS, std::bind(&ApiMethodEndPoint::invoke, &optionsHandler, std::placeholders::_1));

}
handler::~handler()
{
    //dtor
}

void handler::handle_error(pplx::task<void>& t)
{
    try
    {
        t.get();
    }
    catch (...)
    {
        // Ignore the error, Log it if a logger is available
    }
}

void handler::addHandleGet(Path path, ApiHandle&& handle)
{
    getHandler.addHandle(path, std::move(handle));
}

void handler::addHandlePost(Path path, ApiHandle&& handle)
{
    postHandler.addHandle(path, std::move(handle));
}

void handler::addHandleDelete(Path path, ApiHandle&& handle)
{
    deleteHandler.addHandle(path, std::move(handle));
}


//
// Get Request 
//
void handler::handle_get(http_request message)
{
    ucout << message.to_string() << endl;

    auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));

    message.relative_uri().path();
    //Dbms* d  = new Dbms();
    //d->connect();

    concurrency::streams::fstream::open_istream(U("static/index.html"), std::ios::in).then([=](concurrency::streams::istream is)
        {
            message.reply(status_codes::OK, is, U("text/html"))
                .then([](pplx::task<void> t)
                    {
                        try {
                            t.get();
                        }
                        catch (...) {
                            //
                        }
                    });
        }).then([=](pplx::task<void>t)
            {
                try {
                    t.get();
                }
                catch (...) {
                    message.reply(status_codes::InternalError, U("INTERNAL ERROR "));
                }
            });

        return;

};

//
// A POST request
//
void handler::handle_post(http_request message)
{
    ucout << message.to_string() << endl;
    string rep = "WRITE YOUR OWN DELETE OPERATION";

    //auto json = message.extract_json(true).get();
    
    ucout << message.absolute_uri().path().c_str() << std::endl;
    

    message.reply(status_codes::OK, rep);
    return;
};

//
// A DELETE request
//
void handler::handle_delete(http_request message)
{
    ucout << message.to_string() << endl;

    string rep = "WRITE YOUR OWN DELETE OPERATION";
    message.reply(status_codes::OK, rep);
    return;
};


//
// A PUT request 
//
void handler::handle_put(http_request message)
{
    ucout << message.to_string() << endl;
    string rep = "WRITE YOUR OWN PUT OPERATION";
    message.reply(status_codes::OK, rep);
    return;
};