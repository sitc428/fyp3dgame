#include "Actor.h"
#include "Check.h"

// constructor
	Actor::Actor( GameWorld& gameWorld )
	: world(gameWorld)
	, state(state_ACTOR_ALIVE)
	  , attachActorParent(NULL)
{
}

// static function that should be used to destroy actors, makes sure that Cleanup gets called before the actor is deleted
// cleanup is a virtual function, and you shouldn't call virtual functions in the destructor
void Actor::DestroyActor( Actor*& actorToDestroy )
{
	check(actorToDestroy);
	actorToDestroy->Cleanup();
	delete actorToDestroy;
	actorToDestroy = NULL;
}

// cleans up the actor state right before destruction, you can call virtual functions from here
void Actor::Cleanup()
{
	// if we are attached, detach ourselves from the parent
	if( attachActorParent )
	{
		attachActorParent->DetachActor(*this);
	}
	// the parent should have cleared our parent pointer
	check(attachActorParent == NULL);

	// if we have any attached children, detach them
	for( irr::s32 i = attachActorChildren.size()-1; i >= 0; --i )
	{
		DetachActor( *attachActorChildren[i] );
	}
	attachActorChildren.clear();
}

// interface for attaching and detaching external actors
void Actor::AttachActor( Actor& actorToAttach, const irr::c8* nodeName/*=NULL*/ )
{
	// if the actor was already attached, detach it
	if(actorToAttach.attachActorParent != NULL)
	{
		actorToAttach.attachActorParent->DetachActor(actorToAttach);
	}

	// remember that we attached this node in the attachedNodes irr::core::array
	attachActorChildren.push_back( &actorToAttach );
	actorToAttach.attachActorParent = this;
}

void Actor::DetachActor( Actor& actorToDetach )
{
	// verify that we're attached
	check( actorToDetach.attachActorParent == this );

	// find the node in the attached nodes irr::core::array
	irr::s32 index = -1;
	for( irr::u32 i = 0; i < attachActorChildren.size(); ++i )
	{
		if( attachActorChildren[i] == &actorToDetach )
		{
			index = i;
			break;
		}
	}
	// make sure we've found the actor
	check(index >= 0);
	// remove the element from the list
	attachActorChildren.erase( (irr::u32)index, 1 );

	actorToDetach.attachActorParent = NULL;
}

