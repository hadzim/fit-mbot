#ifndef CLIENTTEMPLATE_CLIENT_H_
#define CLIENTTEMPLATE_CLIENT_H_

#define TEMPLATE_INTERFACE_METHOD "\n\
		[OperationContract(Name = \"<methodName>\")]\n\
		[WebInvoke(Method = \"GET\", UriTemplate = \"/<methodName>?<urlParameters>\", RequestFormat = WebMessageFormat.Json, ResponseFormat = WebMessageFormat.Json)]\n\
        <returnType> <methodName>(<parameters>);\n\
"



#define TEMPLATE_CLASS "\
<namespaceStart>\n\
       [ServiceContract]\n\
       public interface <className> {\n\
				<methods>\n\
				\n\
			};\n\
<namespaceEnd>\n\
\n"


#define TEMPLATE_STUB "\
/**\n\
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!\n\
 */\n\
\n\
using System;\n\
using System.Collections.Generic;\n\
using System.Linq;\n\
using System.Runtime.Serialization;\n\
using System.ServiceModel;\n\
using System.Text;\n\
using System.ComponentModel;\n\
using System.ServiceModel.Web;\n\
\n\
<classes>\n\
"

#endif
