/*
 *  Monster.cpp
 *  FYP
 *
 *  Created by Mr.JJ on 09å¹?????
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Monster.h"
#include <string>

Monster::Monster(irr::scene::IAnimatedMeshSceneNode* source, irr::core::vector3df position, irr::core::vector3df scale, float speed)
:_monster(source),_speed(speed){
	_monster->setLoopMode(false);
	_monster->setPosition(position);
	_monster->setScale(scale);
	_monster->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	FSM.initiate();
	original = position; 
	pos = position;
	target=pos;
	moved = false;
	Health = 100;
	timeout = 5.0;
	mon_timer = new boost::timer();
	mon_timer->restart();
	//mon_timer->stop();
	//FSM.test() = "TEST";
}

void Monster::change(char c, Player* _player){
		int num =1;
		switch (c){
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


void Monster::update(Player* _player){

	std::cout<<_player->getPosition().getDistanceFrom(pos)<<"\n";
	if(Health <= 0){//Death
		FSM.process_event( EvDie());
		FSM.reaction(_monster, _player);
	}else if(_player->getPosition().getDistanceFrom(pos)< 2.5f){
		FSM.process_event( EvWithinAttackRange());
		FSM.reaction(_monster, _player);
	
	
	}else if( _player->getPosition().getDistanceFrom(original)< 7.0f || _player->getPosition().getDistanceFrom(pos)< 4.0f ){
		mon_timer->restart();
		irr::core::vector3df targetPos =_monster->getPosition()+((_player->getPosition() - _monster->getPosition())/42.5f);

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

void Monster::Hit(int damage){
	Health-=damage;
	std::cout<<Health<<std::endl;
}
