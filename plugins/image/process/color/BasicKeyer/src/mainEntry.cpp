#define OFXPLUGIN_VERSION_MAJOR 0
#define OFXPLUGIN_VERSION_MINOR 0

#include <tuttle/plugin/Plugin.hpp>
#include "BasicKeyerPluginFactory.hpp"

namespace OFX {
namespace Plugin {

void getPluginIDs( OFX::PluginFactoryArray& ids )
{
	mAppendPluginFactory( ids, tuttle::plugin::basicKeyer::BasicKeyerPluginFactory, "fr.tuttle.basickeyer" );
}

}
}
