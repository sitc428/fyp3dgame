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

static const irr::c8*		MONSTER_MODEL  = "media/model/dwarf.x";

Monster::Monster(GameWorld& gameWorld, irr::scene::IAnimatedMeshSceneNode* source, irr::core::vector3df position, irr::core::vector3df scale, float speed)
:Actor(gameWorld),_monster(source),_speed(speed),world(gameWorld){
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
: Actor(gameWorld), world(gameWorld)
{
	irr::scene::ISceneManager& smgr = gameWorld.GetSceneManager();
	_monster = smgr.addAnimatedMeshSceneNode(smgr.getMesh(MONSTER_MODEL), smgr.getRootSceneNode(), ACTOR_ENEMY);
	FSM.initiate();
	original = irr::core::vector3df(10, 40, 20);
	pos = irr::core::vector3df(10, 40, 20);
	target = pos;
	moved = false;
	health = 100;
	timeout = 5.0;
	mon_timer = new boost::timer();
	mon_timer->restart();
	}


void Monster::change(Player& _player){
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
*/	}
 


void Monster::update(Player& _player){

	std::cout<<_player.GetNodePosition().getDistanceFrom(pos)<<"\n";
	if(health <= 0){//Death
		FSM.process_event( EvDie());
		FSM.reaction(_monster, _player);
	}else if(_player.GetNodePosition().getDistanceFrom(pos)< 2.5f){
		FSM.process_event( EvWithinAttackRange());
		FSM.reaction(_monster, _player);
	
	
	}else if( _player.GetNodePosition().getDistanceFrom(original)< 7.0f || _player.GetNodePosition().getDistanceFrom(pos)< 4.0f ){
		mon_timer->restart();
		irr::core::vector3df targetPos =_monster->getPosition()+((_player.GetNodePosition() - _monster->getPosition())/42.5f);

		if(targetPos.getDistanceFrom(original) < 7.0f){
		//Tracing mode
			FSM.process_event( EvPlayerWithinRange());
			FSM.reaction(_monster, _player);
			pos = _monster->getPosition();
			target = pos;
		}else{
			FSM.process_event( EvFiniteStateMachineOutOfRange());
			FSM.reaction(_monster, _player);
		
			
		}
	}else{//Idle	
			std::cout<<mon_timer->elapsed()<<"\n";
			//irr::u32 current = mon_timer->getTime();
		if(FSM.GetName() != "Idle"){
			mon_timer->restart();
			FSM.process_event( EvFiniteStateMachineOutOfRange());
			FSM.reaction(_monster, _player);
			
		}else{
			if(mon_timer->elapsed() > timeout){
				if((target-pos)< irr::core::vector3df(0.15, 0.15, 0.15)|| target ==pos ){
				
					if(!moved){
					
						srand ( time(NULL) );
						float x = ((float)(rand() % 10 + 1)/10)-0.5;
						float z = ((float)(rand() % 10 + 1)/10)-0.5;
						float y = _monster->getPosition().Y;
						target.X = original.X+x;
						target.Y = original.Y;
						target.Z = original.Z+z;
						irr::core::vector3df direction = pos-target;
						_monster->setRotation(direction.getHorizontalAngle());
						FSM.IdleTooLong(_monster,_player, target);
						pos = _monster->getPosition();
					}else{
						moved = false;
						mon_timer->restart();
						
					}
					
				}else{
					//FSM.process_event( EvFiniteStateMachineOutOfRange());
					FSM.IdleTooLong(_monster,_player, target);
					pos = _monster->getPosition(); 
					moved = true;
				
				
				}
			
						}
		}
	}
	

}

void Monster::ReceiveDamage(irr::f32  damage){
	health-=damage;
	std::cout<<health<<std::endl;
}

void  Monster::Tick(irr::f32 delta){
	update(world.GetCurrentPlayer());

}
/*

irr::scene::ISceneNode& Monster::GetNode(){}

void Monster::AttachActor(Actor& actorToAttach, const irr::c8* nodeName=NULL ){}

void Monster::DetachActor(Actor& actorToDetach){}
*/



