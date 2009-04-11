#include "DebugInfo.hpp"

bool DebugInfo::enabledDebugBBox = false;

void DebugInfo::enableDebugBBox( GameWorld& world )
{
	if( enabledDebugBBox )
		return;

	enabledDebugBBox = true;
	std::transform(
		&((world.GetActors())[0]),
		&((world.GetActors())[world.GetActors().size()-1]),
		&((world.GetActors())[0]),
		DebugInfo::showDebugBox
	);
	std::transform(
		&((world.GetBlocking())[0]),
		&((world.GetBlocking())[world.GetBlocking().size()-1]),
		&((world.GetBlocking())[0]),
		DebugInfo::showDebugBox2
	);
}

void DebugInfo::disableDebugBBox( GameWorld& world )
{
	if( enabledDebugBBox )
	{
		enabledDebugBBox = false;
		std::transform(
			&((world.GetActors())[0]),
			&((world.GetActors())[world.GetActors().size()-1]),
			&((world.GetActors())[0]),
			DebugInfo::hideDebugBox
		);
		std::transform(
			&((world.GetBlocking())[0]),
			&((world.GetBlocking())[world.GetBlocking().size()-1]),
			&((world.GetBlocking())[0]),
			DebugInfo::hideDebugBox2
		);
	}
}
