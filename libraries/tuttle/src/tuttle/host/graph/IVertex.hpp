#ifndef _TUTTLE_IVERTEX_HPP_
#define	_TUTTLE_IVERTEX_HPP_

#include <tuttle/host/INode.hpp>
#include <tuttle/common/utils/global.hpp>

#include <iostream>
#include <set>

namespace tuttle {
namespace host {
namespace graph {

class IVertex
{
public:
	IVertex( const std::string& name = "Undefined" );

	IVertex( const std::string& name, INode& processNode );

	IVertex( const IVertex& v );

	virtual ~IVertex() = 0;

	IVertex& operator=( const IVertex& v )
	{
		if( this == &v )
			return *this;
		_name           = v._name;
		_processNode    = v._processNode;
		_processOptions = v._processOptions;
		_fake           = v._fake;
		_used           = v._used;
		return *this;
	}

	bool                  isFake() const                                     { return _fake; }
	void                  setUsed( const bool used = true )                  { _used = used; }
	bool                  isUsed() const                                     { return _used; }
	const std::string&    getName() const                                    { return _name; }
	INode*                 getProcessNode()                                   { return _processNode; }
	const INode* const     getProcessNode() const                             { return _processNode; }
	void                  setProcessNode( INode* p )                          { _processNode = p; }
	ProcessOptions&       getProcessOptions()                                { return _processOptions; }
	const ProcessOptions& getProcessOptions() const                          { return _processOptions; }
	void                  setProcessOptions( const ProcessOptions& options ) { _processOptions = options; }

	virtual std::ostream& exportDotDebug( std::ostream& os ) const;
	friend std::ostream& operator<<( std::ostream& os, const IVertex& v );

public:
	std::string _name;
	
private:
	INode* _processNode;
	graph::ProcessOptions _processOptions;
	bool _fake;
	bool _used;
	static int _count;

public:
	int _id;

};

}
}
}

#endif

