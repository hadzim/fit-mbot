#ifndef CLIENTTEMPLATE_CLIENT_H_
#define CLIENTTEMPLATE_CLIENT_H_
/*
#define TEMPLATE_CLIENT_METHOD "\
        <returnType> <methodName>(<parameters>){\n\
            ::Json::Value p;\n\
            <parameterAssign>\n\
            <returnStatement>\n\
        }\n\
"
*/



#define TEMPLATE_STUB "\
/**\n\
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!\n\
 */\n\
#ifndef _<STUBNAME>_SERVICE_JSON_H_\n\
#define _<STUBNAME>_SERVICE_JSON_H_\n\
\n\
#include <Poco/SharedPtr.h>\n\
#include <Poco/BasicEvent.h>\n\
#include <string>\n\
#include <vector>\n\
#include <map>\n\
#include <memory>\n\
#include <TBS/Services/Services.h>\n\
#include <TBS/Services/Json/JsonServices.h>\n\
///includes\n\
<includes>\n\
\n\
\n\
<namespaceStart>\
       class GEN_SERVICE_API Client {\n\
			public:\n\
				typedef Poco::SharedPtr <Client> Ptr;\n\
				\n\
				Client(const TBS::Services::JsonClientChannel & ch);\n\
				~Client();\n\
				\n\
				\n //methods \n\
				<clients>\n\
				\n\
		private: \n\
				TBS::Services::JsonClientChannel ch;\n\
				<private>\n\
			};\n\
			\n\
			\n\
		class GEN_SERVICE_API Server {\n\
			public:\n\
				typedef Poco::SharedPtr<Server> Ptr;\n\
				Server(const TBS::Services::JsonServerChannel & ch);\n\
				~Server();\n\
				\n\
				void start();\n\
				void stop();\n\
			public:\n\
				<servers>\n\
				\n\
			private:\n\
				TBS::Services::ICommChannelHolder::Ptr channel;\n\
		};\n\
<namespaceEnd>\n\
#endif //_<STUBNAME>_SERVICE_H_\n\
"


#define TEMPLATE_CPP_STUB "\
/**\n\
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!\n\
 */\n\
///includes\n\
<includes>\n\
#include <TBS/Services/Json/JsonServicesImpl.h>\n\
\n\
//convertors\n\
<convertors>\n\
\n\
<namespaceStart>\
	   Client::Client(const TBS::Services::JsonClientChannel & ch) : \n\
	       ch(ch){\n\
	   }\n\
	   Client::~Client(){}\n\
	   <clientMethods>\n\
	   \n\
	   \n\
	   Server::Server(const TBS::Services::JsonServerChannel & ch) : \n\
	   	   channel(new <channel>(ch)){\n\
		   \n\
	    } \n\
	    Server::~Server(){}\n\
	    void Server::start(){ \n\
	   	   channel.cast<<channel>>()->interface.StartListening();\n\
	    } \n\
	    void Server::stop(){ \n\
	   	   channel.cast<<channel>>()->interface.StopListening();\n\
	    } \n\
	    \n\
	   <serverMethods>\n\
<namespaceEnd>\n\
\n\
"

#endif