#include "TBS/JsonValueGetter.h"
#include <stdexcept>

namespace TBS {

	JsonValueGetter::JsonValueGetter():
		root(),
		path(".")
	{ }

	JsonValueGetter::JsonValueGetter(std::shared_ptr<const Json::Value> root, const std::string& path):
		root(root),
		path(path)
	{}

	const Json::Value& JsonValueGetter::get(const std::string& name, Json::ValueType check) const {
		if (!root) throw std::logic_error("no root in JSonValueGetter");
		const Json::Value& target(Json::Path(path).resolve(*root));
		if (!target.isMember(name)) {
			throw std::runtime_error("JsonValueGetter cannot find " + name + " in " + path);
		}
		if (!target[name].isConvertibleTo(check)) {
			throw std::runtime_error("JsonValueGetter cannot convert " + name + " in " + path + " to given type");
		}

		return target[name];
	}


	JsonValueGetter JsonValueGetter::subtree(const std::string& name) const {
		if (!root) throw std::logic_error("no root in JSonValueGetter");
		if (name[0] == '.') {
			return JsonValueGetter(root, path+name);
		} else {
			return JsonValueGetter(root, path+"."+name);
		}
	}

} // namespace
