#include "FFMpegWriterPluginFactory.hpp"
#include "FFMpegWriterPlugin.hpp"
#include "FFMpegWriterDefinitions.hpp"

#include <tuttle/plugin/ImageGilProcessor.hpp>
#include <tuttle/plugin/Progress.hpp>
#include <tuttle/plugin/PluginException.hpp>

#include <string>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <ofxsImageEffect.h>
#include <ofxsMultiThread.h>
#include <boost/gil/gil_all.hpp>
#include <boost/scoped_ptr.hpp>

namespace tuttle {
namespace plugin {
namespace ffmpeg {
namespace writer {

using namespace OFX;


/**
 * @brief Function called to describe the plugin main features.
 * @param[in, out]   desc     Effect descriptor
 */
void FFMpegWriterPluginFactory::describe( OFX::ImageEffectDescriptor &desc )
{
	desc.setLabels( "ffmpeg", "ffmpeg",
		            "ffmpeg video io" );
	desc.setPluginGrouping( "tuttle" );

	// add the supported contexts
	desc.addSupportedContext( eContextGeneral );

	// add supported pixel depths
	desc.addSupportedBitDepth( eBitDepthUByte );
	desc.addSupportedBitDepth( eBitDepthUShort );
	desc.addSupportedBitDepth( eBitDepthFloat );

	// plugin flags
	desc.setHostFrameThreading( false );
	desc.setSupportsMultiResolution( false );
	desc.setSupportsTiles( kSupportTiles );
}

/**
 * @brief Function called to describe the plugin controls and features.
 * @param[in, out]   desc       Effect descriptor
 * @param[in]        context    Application context
 */
void FFMpegWriterPluginFactory::describeInContext( OFX::ImageEffectDescriptor &desc,
                                                  OFX::ContextEnum context )
{
	OFX::ClipDescriptor *srcClip = desc.defineClip( kOfxImageEffectSimpleSourceClipName );
	srcClip->addSupportedComponent( ePixelComponentRGBA );
	srcClip->addSupportedComponent( ePixelComponentAlpha );
	srcClip->setSupportsTiles( kSupportTiles );

	// Create the mandated output clip
	OFX::ClipDescriptor *dstClip = desc.defineClip( kOfxImageEffectOutputClipName );
	dstClip->addSupportedComponent( ePixelComponentRGBA );
	dstClip->addSupportedComponent( ePixelComponentAlpha );
	dstClip->setSupportsTiles( kSupportTiles );

	// Controls
	StringParamDescriptor* filename = desc.defineStringParam( kOutputFilename );
	filename->setLabels( kOutputFilenameLabel, kOutputFilenameLabel, kOutputFilenameLabel );
	filename->setStringType( eStringTypeFilePath );
	filename->setCacheInvalidation( eCacheInvalidateValueAll );

	OFX::PushButtonParamDescriptor *helpButton = desc.definePushButtonParam( kFFMpegHelpButton );
	helpButton->setScriptName( "help" );
}

/**
 * @brief Function called to create a plugin effect instance
 * @param[in] handle  effect handle
 * @param[in] context    Application context
 * @return  plugin instance
 */
OFX::ImageEffect* FFMpegWriterPluginFactory::createInstance( OfxImageEffectHandle handle,
                                                            OFX::ContextEnum context )
{
	return new FFMpegWriterPlugin(handle);
}

}
}
}
}
