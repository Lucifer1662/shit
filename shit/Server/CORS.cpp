#include "CORS.h"
#include "stdfx.h"

void addCors(http_response& res) {

	res.headers().add(U("Access-Control-Allow-Origin"), U("*"));
	res.headers().add(U("Access-Control-Allow-Credentials"), U("true"));
	res.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, OPTIONS, DELETE"));
	res.headers().add(U("Access-Control-Allow-Headers"), U("Origin, Content-Type, Accept, Authorization"));
}