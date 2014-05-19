#ifndef CLIENTTEMPLATE_CLIENT_H_
#define CLIENTTEMPLATE_CLIENT_H_

#define TEMPLATE_CLIENT_METHOD "\
        <returnType> <methodName>(<parameters>){\n\
            ::Json::Value pIn;\n\
            <parameterAssign>\n\
            <returnStatement>\n\
        }\n\
"

#define TEMPLATE_CLASS "\
<namespaceStart>\
       class <className> : public <interfaceName> {\n\
			public:\n\
				typedef Poco::SharedPtr <<className>> Ptr;\n\
				\n\
				<className>(jsonrpc::AbstractClientConnector* param){\n\
					this->client = std::auto_ptr<jsonrpc::Client>(new jsonrpc::Client(param));\n\
				}\n\
				<className>(const jsonrpc::HttpClientParams & p){\n\
					this->client = std::auto_ptr<jsonrpc::Client>(new jsonrpc::Client(new jsonrpc::HttpInterfaceClient(<interfaceName>::name(), p)));\n\
				}\n\
				virtual ~<className>() {\n\
				 }\n\n\
				\n\
				\n //methods \n\
				<methods>\n\
				\n //signals \n\
				<signals>\n\
				\n\
		private: \n\
				std::auto_ptr<jsonrpc::Client> client;\n\
			};\n\
<namespaceEnd>\n\
\n"


#define TEMPLATE_STUB "\
/**\n\
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!\n\
 */\n\
#ifndef _<STUBNAME>_JSONCLIENT_H_\n\
#define _<STUBNAME>_JSONCLIENT_H_\n\
\n\
#include <Poco/SharedPtr.h>\n\
#include <Poco/BasicEvent.h>\n\
#include <string>\n\
#include <vector>\n\
#include <map>\n\
#include <memory>\n\
#include <jsonrpc/rpc.h>\n\
///includes\n\
<includes>\n\
\n\
\n\
<classes>\n\
#endif //_<STUBNAME>_JSONCLIENT_H_\n\
"


#endif