/*
 *  Monster.cpp
 *  FYP
 *
 *  Created by Mr.JJ on 09???????
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Monster.h"
#include "GameEngine.h"
#include "GameWorld.h"
#include "NodeID.h"

static const irr::c8* MONSTER_MODEL = "media/model/dwarf.x";
static const irr::core::vector3df defaultPosition = irr::core::vector3df(50,0,80);

Monster::Monster(GameWorld& gameWorld, irr::scene::IAnimatedMeshSceneNode* source, irr::core::vector3df position, irr::core::vector3df scale, float speed)
	:Actor(gameWorld),
	_monster(source),
	_speed(speed),
	world(gameWorld),
	collisionAnimator(NULL)
{
	//_monster->setLoopMode(false);
	//SetNodePosition(position);
	//_monster->setScale(scale);
	//_monster->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	FSM.initiate();
	original = position; 
	pos = position;
	target=pos;
	moved = false;
	health = 100;
	timeout = 5.0;
	mon_timer = new boost::timer();
	mon_timer->restart();
	//mon_timer->stop();
	//FSM.test() = "TEST";
	
	
	
}

Monster::Monster(GameWorld& gameWorld, irr::video::IVideoDriver& videoDriver)
	:Actor(gameWorld),
	world(gameWorld)
{
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	_monster = smgr.addAnimatedMeshSceneNode(smgr.getMesh(MONSTER_MODEL), smgr.getRootSceneNode(), ACTOR_ENEMY);
	_monster->setPosition( defaultPosition );
	FSM.initiate();
	original = defaultPosition;
	pos = defaultPosition;
	target = pos;
	moved = false;
	health = 100;
	timeout = 5.0;
	mon_timer = new boost::timer();
	attack_timer = new boost::timer();
	mon_timer->restart();
	attack_timer->restart();
	_monster->setScale(irr::core::vector3df(0.5,0.5,0.5));
	_monster->setLoopMode(false);
	
	// setup player collision with the world
	RecreateCollisionResponseAnimator();
	
	irr::scene::ITriangleSelector* triangleSelector = world.GetSceneManager().createTriangleSelectorFromBoundingBox( _monster );
	//irr::scene::ITriangleSelector* triangleSelector = world.GetSceneManager().createTriangleSelector( node->getMesh()->getMesh(0), node );
	_monster->setTriangleSelector( triangleSelector );
	triangleSelector->drop();
	triangleSelector = NULL;
}

/*
void Monster::change(Player& _player)
{
	int num =1;
	std::cout<<"testing\n";
	/*		switch (c){
			case 't':
			{
			FSM.process_event ( EvDie() );
			FSM.reaction(_monster, _player);
			break;
			}
			case 'w':
			{
			FSM.process_event ( EvPlayerWithinRange() );
			FSM.reaction(_monster,_player);
			break;
			}
			case 'a':
			{
			FSM.process_event ( EvWithinAttackRange() );
			FSM.reaction(_monster, _player);
			break;
			}
			case 'o':
			{
			FSM.process_event ( EvOutOfAttackRange() );
			FSM.reaction(_monster, _player);
			break;
			}
			case 'm':
			{
			std::cout<<"Here1\n";
	//FSM.test(1,2,3);

	std::cout<<FSM.GetName()<<"\n";
	std::cout<<num<<std::endl;
	break;
	}
	}
	
}
*/

void Monster::update(Player& _player)
{
	//CheckActorPosition();
	//std::cout<<world.GetActors().size()<<" size \n";
	pos= _monster->getAbsolutePosition();
	//std::cout<<_player.GetNodePosition().getDistanceFrom(original)<<"\n";
	//std::cout<<_player.GetNodePosition().getDistanceFrom(pos)<<"\n";
	if(health <= 0)
	{
		//Death
		FSM.process_event( EvDie());
		FSM.reaction(_monster, _player);
	}else if(_player.GetNodePosition().getDistanceFrom(pos)< 38.0f)
	{
		//std::cout<<"Attack_timer: "<<attack_timer->elapsed()<<"\n";
		if(FSM.GetName() != "Attacking"){
			FSM.process_event( EvWithinAttackRange());
			if(attack_timer->elapsed() > timeout){
				attack_timer->restart();
				FSM.reaction(_monster, _player);
			}
		}else{
			
			if(attack_timer->elapsed() > timeout){
			//	std::cout<<"Mon_timer:------------"<<"\n";
				attack_timer->restart();
				FSM.reaction(_monster, _player);			
			}
		}
	}
	else if( _player.GetNodePosition().getDistanceFrom(original)< 80.0f
		|| _player.GetNodePosition().getDistanceFrom(pos)< 30.0f )
	{
		mon_timer->restart();
		irr::core::vector3df targetPos =_monster->getPosition()+((_player.GetNodePosition() - _monster->getPosition())/42.5f);

		if( targetPos.getDistanceFrom(original) < 80.0f )
		{
			//Tracing mode
			//if(FSM.GetName() != "Tracing"){
			if(FSM.GetName() == "Attacking")
				FSM.process_event(EvFiniteStateMachineOutOfRange());
				FSM.process_event( EvPlayerWithinRange());
				irr::core::vector3df targetPos = _monster->getPosition()+((_player.GetNodePosition() - _monster->getPosition())/42.5f);
				CheckActorPosition(targetPos);
				FSM.reaction(_monster, _player);
				pos = _monster->getPosition();
				target = pos;
			
		}
		else
		{
			FSM.process_event( EvFiniteStateMachineOutOfRange());
			FSM.reaction(_monster, _player);
		}
	}
	else
	{
		//Idle	
		//std::cout<<"Mon_timer: "<<mon_timer->elapsed()<<"\n";
		//irr::u32 current = mon_timer->getTime();
		if( FSM.GetName() != "Idle" )
		{
			mon_timer->restart();
			//std::cout<<"Mon_timer:Restart "<<"\n";
			
			FSM.process_event( EvFiniteStateMachineOutOfRange());
			FSM.reaction(_monster, _player);

		}
		else
		{
			if( mon_timer->elapsed() > timeout )
			{
				if( (target - pos) < irr::core::vector3df(10.0, 0.0, 10.0) || target ==pos||mon_timer->elapsed() > 7.0  )
				{
					if(!moved )
					{

						srand ( time(NULL) );
						float x = ((float)(rand() % 20 + 1))-10;
						float z = ((float)(rand() % 20 + 1))-10;
						float y = _monster->getPosition().Y;
						target.X = pos.X+x;
						target.Y = y;
						target.Z = pos.Z+z;
						irr::core::vector3df direction = pos-target;
						_monster->setRotation(direction.getHorizontalAngle());
						FSM.IdleTooLong(_monster,_player, target);
						pos = _monster->getPosition();
					}
					else
					{
						moved = false;
						mon_timer->restart();

					}

				}
				else
				{
					//FSM.process_event( EvFiniteStateMachineOutOfRange());
					FSM.IdleTooLong(_monster,_player, target);
					pos = _monster->getPosition();
					target=pos;
					moved = true;
				}
			}
		}
	}
	
	
}


void Monster::RecreateCollisionResponseAnimator()
{
	// drop the current collision response animator
	if( collisionAnimator )  // soft fail which allows us to call RecreateCollisionResponseAnimator to first initialize the non-existing animator
	{
		_monster->removeAnimator( collisionAnimator );
		collisionAnimator->drop();
		collisionAnimator = NULL;
	}
	
	// setup torso collision with the world
	//irr::core::aabbox3df box = node->getBoundingBox();
	irr::core::aabbox3df box = _monster->getMesh()->getMesh(0)->getBoundingBox();
	//irr::core::vector3df radius = box.MaxEdge - box.getCenter();
	irr::core::vector3df radius = box.MaxEdge - box.getCenter();
	
	collisionAnimator = world.GetSceneManager().createCollisionResponseAnimator(
				&world.GetLevelTriangleSelector(), _monster, radius,irr::core::vector3df(0,-.08f,0), // gravity
				irr::core::vector3df(0, 0, 0), // ellipsoid translation
			    0.0001f); // sliding value
	_monster->addAnimator(collisionAnimator);
}


void Monster::ReceiveDamage(irr::f32  damage)
{
	health-=damage;
//	std::cout<<"Health: "<<health<<std::endl;
}

void  Monster::Tick(irr::f32 delta)
{
	update(world.GetCurrentPlayer());

}

void Monster::ReSetPosition(irr::core::vector3df NewPosition){
	original = NewPosition;
	pos = NewPosition;
	target = NewPosition;
	 _monster->setPosition(NewPosition); 
	_monster->updateAbsolutePosition();

}


void Monster::CheckActorPosition(irr::core::vector3df target){
//	for(irr::u32 i =0; i<world.GetActors().size();i++){
//		
//		if(world.GetActors()[i]->GetNode())
//		for(irr::u32 j=0; j<world.GetActors()[i]->attachActorChildren.size();j++)
			//std::cout<<i<<" : "<<world.GetActors()[i].attachActorChildren[j]->GetNode().getPosition().X<<"\n";
			//std::cout<<i<<" : "<<world.GetActors()[i].attachActorChildren[j]->GetNode().getPosition().X<<"\n";
	//}
	
	irr::core::array<irr::scene::ISceneNode*> outNodes;
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	smgr.getSceneNodesFromType( irr::scene::ESNT_MESH, outNodes );
//float min = 9999.99;
	for(irr::u32 i = 0; i< outNodes.size();i++){
		irr::scene::IMeshSceneNode* meshNode = (irr::scene::IMeshSceneNode*)(outNodes[i]);
		if(meshNode->getMesh()){
			if(meshNode->getID() == -1 || meshNode->getID() == 2 )
				
				if(pos.getDistanceFrom(meshNode->getPosition() ) < 40.0){
					
					//std::cout<<"BLOCKED\n";
					//if(min  > pos.getDistanceFrom(meshNode->getPosition() ))
					//	min = pos.getDistanceFrom(meshNode->getPosition() );
					//std::cout<<pos.getDistanceFrom(meshNode->getPosition() )<<"\n";
				}
					
		}
	}
	//std::cout<<min<<"\n";

}

/*

   irr::scene::ISceneNode& Monster::GetNode(){}

   void Monster::AttachActor(Actor& actorToAttach, const irr::c8* nodeName=NULL ){}

   void Monster::DetachActor(Actor& actorToDetach){}
   */



